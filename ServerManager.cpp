// ServerManager.cpp : Implementation of CServerManager

#include "stdafx.h"
#include "P2P.h"
#include "NotifyWindow.h"
#include "ServerManager.h"
#include <wininet.h>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CServerManager


STDMETHODIMP CServerManager::AppInitialize()
{
	InitializeCriticalSection(&m_critObj);

	// Create our notification window
	m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
		
	RECT rect;
	rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
	m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
	
	m_bCancelThreads = FALSE;
	return S_OK;
}

STDMETHODIMP CServerManager::AppUninitialize()
{
//	if (m_critObj.)
//		DeleteCriticalSection(&m_critObj);

	m_wndNotify.DestroyWindow();
	
	m_bCancelThreads = TRUE;
	m_syncRemoteServer.WaitForUnlock(20000);
	m_syncLocalServer.WaitForUnlock(20000);
	
	SerializeServerList();

	return S_OK;
}

STDMETHODIMP CServerManager::LoadLocalServerList(VARIANT_BOOL *pbResult)
{	
	if (m_syncLocalServer.IsLocked())
		return S_OK;
	
	m_permanentList.clear();
	
	DWORD dwThreadID = 0;
	CreateThread(NULL,                  // Security attributes
                 (DWORD) 0,             // Initial stack size
                 LoadLocalServerListThread,     // Thread start address
                 (LPVOID) this,         // Thread parameter
                 (DWORD) 0,             // Creation flags
                 &dwThreadID);          // Thread identifier
	
	if (pbResult)
		*pbResult = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CServerManager::LoadRemoteServerList(VARIANT_BOOL *pbResult)
{
	if (m_syncRemoteServer.IsLocked())
		return S_OK;

	m_recycledList.clear();

	DWORD dwThreadID = 0;
	CreateThread(NULL,                  // Security attributes
                 (DWORD) 0,             // Initial stack size
                 LoadRemoteServerListThread,     // Thread start address
                 (LPVOID) this,         // Thread parameter
                 (DWORD) 0,             // Creation flags
                 &dwThreadID);          // Thread identifier
	
	if (pbResult)
		*pbResult = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CServerManager::AddPermanentServer(BSTR Description, BSTR Address, long nPort, VARIANT_BOOL *pbResult)
{
	USES_CONVERSION;

	ServerInfo server;
	server.bTried = false;
	server.nFiles = 0;
	server.nGigs = 0;
	server.nPort = nPort;
	server.nUsers = 0;
	server.sAddr = W2A(Address);
	server.sDesc = W2A(Description);
	server.sNetw = "Unknown";
	
	if (UpdateServerInList(server, true) == false)
	{
		// Server doesn't exist already
		m_permanentList.push_back(server);
		::SendMessage(m_wndNotify.m_hWnd, WM_SERVER_ADDED, 1, m_permanentList.size() - 1);
		*pbResult = VARIANT_TRUE;
	}
	else
		*pbResult = VARIANT_FALSE;

	return S_OK;
}

//DEL STDMETHODIMP CServerManager::GetFirstServer(BSTR * Description, BSTR * Address,  long * nPort, VARIANT_BOOL * bIsPermanent, VARIANT_BOOL * pResult)
//DEL {
//DEL 	// TODO: Add your implementation code here
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CServerManager::GetNextServer(BSTR * Description, BSTR * Address,  long * nPort, VARIANT_BOOL * bIsPermanent, VARIANT_BOOL * pResult)
{
	std::list<ServerInfo>::iterator iter;
	for (iter=m_permanentList.begin(); iter != m_permanentList.end(); ++iter)
	{
		CComBSTR bstr;
		ServerInfo srv;
		srv = (*iter);

		if (srv.bTried == false)
		{
			(*iter).bTried = true;
			
			bstr = srv.sDesc.c_str();

			bstr.CopyTo(Description);
		
			bstr = srv.sAddr.c_str();
			bstr.CopyTo(Address);

			*nPort = srv.nPort;
			*pResult = VARIANT_TRUE;
			return S_OK;
		}
	}
	
	for (iter=m_recycledList.begin(); iter != m_recycledList.end(); ++iter)
	{
		CComBSTR bstr;
		ServerInfo srv;
		srv = (*iter);

		if (srv.bTried == false)
		{
			(*iter).bTried = true;
			
			bstr = srv.sDesc.c_str();

			bstr.CopyTo(Description);
		
			bstr = srv.sAddr.c_str();
			bstr.CopyTo(Address);

			*nPort = srv.nPort;
			*pResult = VARIANT_TRUE;
			return S_OK;
		}
	}

	*pResult = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CServerManager::SetFileSavePath(BSTR sPath)
{
	USES_CONVERSION;
	m_sPath = W2T(sPath);

	return S_OK;
}

STDMETHODIMP CServerManager::GetServer(int Index, BSTR *Description, BSTR *Address, long *nPort, long * nUsers, long * nGigas,long * nFiles, VARIANT_BOOL *bIsPermanent, VARIANT_BOOL *pResult)
{
	list<ServerInfo>* pLst = &m_permanentList;
	if ((*bIsPermanent) != VARIANT_TRUE)
	{
		pLst = &m_recycledList;
	}
	
	BOOL bFound = FALSE;
	ServerInfo srv;

	// permanent list
	if (Index == pLst->size() - 1)
	{
		// We iterate from the back
		// this case happens all the time
		bFound = TRUE;
		srv = pLst->back();
	}
	else if (Index > (pLst->size() / 2))
	{
		int nIndex = pLst->size();
		std::list<ServerInfo>::const_iterator iter;
		for (iter=pLst->end(); iter != pLst->begin(); iter--)
		{
			if (nIndex == Index)
			{
				bFound = TRUE;
				srv = (*iter);
				break;
			}
			nIndex--;
		}
	}
	else
	{
		// We iterate from the front
		int nIndex = 0;
		std::list<ServerInfo>::const_iterator iter;
		for (iter=pLst->begin(); iter != pLst->end(); ++iter)
		{
			if (nIndex == Index)
			{
				bFound = TRUE;
				srv = (*iter);
				break;
			}
			nIndex++;
		}
	}

	if (bFound == TRUE)
	{
		CComBSTR bstr;
		bstr = srv.sDesc.c_str();
		bstr.CopyTo(Description);
		
		bstr = srv.sAddr.c_str();
		bstr.CopyTo(Address);

		*nPort = srv.nPort;
		*nUsers = srv.nUsers;
		*nGigas = srv.nGigs;
		*nFiles = srv.nFiles;
	}

	*pResult = bFound ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

BOOL CServerManager::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CServerManager* pThis = (CServerManager*)pClass;

	switch (uMsg)
	{
	case WM_SERVER_ADDED:
		pThis->Fire_OnServerAdded(lParam, wParam ? VARIANT_TRUE : VARIANT_FALSE);
		break;
	case WM_PERMSERVERS_LOADED:
		pThis->Fire_OnPermanentServersLoaded();
		break;
	case WM_REMOTEFILES_LOADED:
		pThis->Fire_OnRemoteServersLoaded(VARIANT_FALSE);
		break;
	case WM_REMOTEFILESCACHE_LOADED:
		pThis->Fire_OnRemoteServersLoaded(VARIANT_TRUE);
		break;
	}
	
	return FALSE;
}

#define CHECK_FOR_THREADCANCEL(x) 	pThis->x.Unlock();	if (pThis->m_bCancelThreads){ return 667;} else pThis->x.Lock();
#define CHECK_FOR_THREADCANCEL_REMOTE(x) 	pThis->x.Unlock();	if (pThis->m_bCancelThreads){ InternetCloseHandle(hNet); InternetCloseHandle(hFile); return 666;} else pThis->x.Lock();

DWORD __stdcall CServerManager::LoadRemoteServerListThread(LPVOID lpvThreadParm)
{
	CServerManager* pThis = (CServerManager*)lpvThreadParm;
	
	pThis->m_syncRemoteServer.Lock();
	
	HINTERNET hNet = 0;
	HINTERNET hFile = 0;
	hNet = InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );

	if (hNet != 0)
	{
		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);

		//string sData = "";
		string sUrl  = "http://www.napigator.com/servers.php?version=112&client=SoulShare";
		hFile = InternetOpenUrl( hNet, sUrl.c_str(), NULL, 0, 0, 0 ) ;
		
		CHECK_FOR_THREADCANCEL_REMOTE(m_syncRemoteServer);

		if ( hFile )
		{
			CHAR buffer[1024];
			DWORD dwRead;
			std::fstream file;
			file.open(string(pThis->m_sPath + "servers_nap.txt").c_str(), ios::out);

			if (file.is_open())
			{
				while ( InternetReadFile( hFile, buffer, 1023, &dwRead ) )
				{
					if ( dwRead == 0 )
						break;
					
					CHECK_FOR_THREADCANCEL_REMOTE(m_syncRemoteServer);

					buffer[dwRead] = 0;
					file.write(buffer, dwRead);

					CHECK_FOR_THREADCANCEL_REMOTE(m_syncRemoteServer);
				}
			}
			InternetCloseHandle( hFile );
			file.close();
		}

		InternetCloseHandle( hNet );
		
		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);

		pThis->LoadServerList(string(pThis->m_sPath + "servers_nap.txt").c_str(), FALSE, TRUE);

		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);
	}
	
	if (pThis->m_recycledList.size() < 2)
	{
		// We do not have enough items in our rec list. We
		// load our backup copy, which is the last saved list
		
		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);

		// _ASSERT(FALSE);
		pThis->LoadServerList(string(pThis->m_sPath + "servers_rec.txt").c_str(), FALSE, TRUE);

		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);

		::PostMessage(pThis->m_wndNotify.m_hWnd, WM_REMOTEFILESCACHE_LOADED, 0, 0);
	}
	else
	{
		// We have items in our list, meaning that we received a good list
		// We save this to our servers_rec.txt file as backup for next time.

		CopyFile(string(pThis->m_sPath + "servers_nap.txt").c_str(),
				 string(pThis->m_sPath + "servers_rec.txt").c_str(),
				 FALSE);

		CHECK_FOR_THREADCANCEL(m_syncRemoteServer);

		::PostMessage(pThis->m_wndNotify.m_hWnd, WM_REMOTEFILES_LOADED, 0, 0);
	}
	
	pThis->m_syncRemoteServer.Unlock();
	
	OutputDebugString("Exiting remote server load thread");

	return 0;
}

DWORD __stdcall CServerManager::LoadLocalServerListThread(LPVOID lpvThreadParm)
{
	CServerManager* pThis = (CServerManager*)lpvThreadParm;
	
	pThis->m_syncLocalServer.Lock();

	// Load permanent
	pThis->LoadServerList(string(pThis->m_sPath + "servers_per.txt").c_str(), TRUE, TRUE);
	
	CHECK_FOR_THREADCANCEL(m_syncLocalServer);

	::PostMessage(pThis->m_wndNotify.m_hWnd, WM_PERMSERVERS_LOADED, 0, 0);
	
	pThis->m_syncLocalServer.Unlock();
	
	OutputDebugString("Exiting local server load thread");

	return 0;
}

void CServerManager::ParseAndAddServerLine(TCHAR* pszLine, BOOL bPermanent, BOOL bCheckIfInList)
{
	// This function needs to be made thread safe!
	// Make sure you only insert to the arrays in this 
	// function

	ServerInfo server;
	
	bool bTooManyChars = false;
	int iIndex = 0;
	TCHAR* pch = 0;
	pch = strtok (pszLine," ");
	while (pch != NULL && (iIndex < 8))
	{
		switch (iIndex)
		{
		case 0: // IP
			server.sAddr = pch;
			break;
		case 1: // Port
			 server.nPort = atol(pch);
			//server.nPort = 13409;
			break;
		case 2:  // Network
			server.sNetw = pch;
			break;
		case 3: // Users
			server.nUsers = atol(pch);
			break;
		case 4: // Gigs
			server.nGigs = atol(pch);
			break;
		case 5: // Files
			server.nFiles = atol(pch);
			break;
		case 6:// Server Name
			server.sDesc = pch;
			// server.sDesc = server.sDesc.substr(1, server.sDesc.size() - 2);
			break;
		default:
			bTooManyChars = true;
			break;
		}
		iIndex++;

		// read pch here
		pch = strtok (NULL, " ");
		
	}
	
	if (server.sDesc == "" ||
		server.sAddr == "" ||
	//	inet_addr(server.sAddr.c_str()) == INADDR_NONE ||
		bTooManyChars == true)
	{
		return;
	}
	
	server.bTried = false;

	if (bCheckIfInList)
	{
		if (UpdateServerInList(server, bPermanent ? 1 : 0))
		{
			// server updated
			::SendMessage(m_wndNotify.m_hWnd, WM_SERVER_UPDATED, 0, m_recycledList.size() - 1);		
			
			return;
		}
	}

	if (bPermanent)
	{
		m_permanentList.push_back(server);
		::SendMessage(m_wndNotify.m_hWnd, WM_SERVER_ADDED, 1, m_permanentList.size() - 1);
	}
	else
	{
		m_recycledList.push_back(server);
		::SendMessage(m_wndNotify.m_hWnd, WM_SERVER_ADDED, 0, m_recycledList.size() - 1);
	}	
}

STDMETHODIMP CServerManager::GetServerCount(long *plResult)
{
	*plResult = m_permanentList.size() + m_recycledList.size();

	return S_OK;
}

BOOL CServerManager::LoadServerList(const TCHAR *pszFile, BOOL bPermanent, BOOL bCheckIfInList)
{
	// THIS FUNCTION MUST BE THREADSAFE
	EnterCriticalSection(&m_critObj); 

	std::ifstream file;

	// Temporary
	file.open(pszFile);
	if (file.is_open())
	{
		while (file.good())
		{
			TCHAR szLine[1024];
			file.getline(szLine, 1024);
			ParseAndAddServerLine(szLine, bPermanent, bCheckIfInList);
		}
	}
	else
	{
		LeaveCriticalSection(&m_critObj);
		return FALSE;
	}

	file.close();
	
	LeaveCriticalSection(&m_critObj);

	return TRUE;
}

BOOL CServerManager::UpdateServerInList(CServerManager::ServerInfo srv, BOOL bPermanent)
{
	// Returns true if server in list, else false
	for (int i=0;i<2;i++)
	{
		list<ServerInfo>* pLst = 0;
		if (i == 0)
		{
			pLst = &m_permanentList;
		}
		else
		{
			pLst = &m_recycledList;
		}
			 
		std::list<ServerInfo>::iterator iter;
		for (iter=pLst->begin(); iter != pLst->end(); ++iter)
		{
			if (((*iter).sAddr == srv.sAddr) && ((*iter).nPort == srv.nPort))
			{
				// We update the item
				(*iter).sAddr  = srv.sAddr;
				(*iter).nPort  = srv.nPort;
				(*iter).nGigs  = srv.nGigs;
				(*iter).nFiles = srv.nFiles;
				(*iter).nUsers = srv.nUsers;
				(*iter).sDesc  = srv.sDesc;
				(*iter).sNetw  = srv.sNetw;

				// This item is in list
				return TRUE;
			}
		}

		if (bPermanent)
			break;
	}
	
	return FALSE;
}

STDMETHODIMP CServerManager::LoadAllServerLists()
{
	LoadLocalServerList(0);

	return S_OK;
}


STDMETHODIMP CServerManager::SortLists()
{
	m_recycledList.sort();

	return S_OK;
}


STDMETHODIMP CServerManager::get_State(ServerManagerState *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

void CServerManager::SerializeServerList()
{
	// Write our permanent server file
	std::fstream file;
	file.open(string(m_sPath + "servers_per.txt").c_str(), ios::out);
	
	if (file.is_open())
	{
		list<ServerInfo>* pLst = &m_permanentList;
		std::list<ServerInfo>::iterator iter;
		for (iter=pLst->begin(); iter != pLst->end(); ++iter)
		{
			ostringstream oss;
			oss << (*iter).sAddr.c_str() << " " << (*iter).nPort
										 << " " << (*iter).sNetw.c_str()
										 << " " << (*iter).nGigs
									     <<	" " << (*iter).nFiles
										 << " " << (*iter).nUsers
										 << " " << (*iter).sDesc.c_str()
										 << "\n";

			file.write(oss.str().c_str(), oss.str().size());
		}

		file.close();
	}
	else
		_ASSERT(FALSE);
}

STDMETHODIMP CServerManager::SaveLocalFilesToDisk()
{
	SerializeServerList();

	return S_OK;
}

STDMETHODIMP CServerManager::ResetStatusOfAllServers()
{
	// Returns true if server in list, else false
	for (int i=0;i<2;i++)
	{
		list<ServerInfo>* pLst = 0;
		if (i == 0)
		{
			pLst = &m_permanentList;
		}
		else
		{
			pLst = &m_recycledList;
		}
			 
		std::list<ServerInfo>::iterator iter;
		for (iter=pLst->begin(); iter != pLst->end(); ++iter)
		{
			// We update the item
			(*iter).bTried = FALSE;
		}
	}


	return S_OK;
}

STDMETHODIMP CServerManager::FindServer(BSTR ServerName, VARIANT_BOOL IsPermanent)
{
	// TODO: Add your implementation code here

	return S_OK;
}
