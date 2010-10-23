// Listener.cpp : Implementation of CListener

#include "stdafx.h"
#include "P2P.h"
#include "Listener.h"

/////////////////////////////////////////////////////////////////////////////
// CListener


STDMETHODIMP CListener::Listen(long nPort)
{
	
	// We start listening here, so if we come
	// accross any error (like port already used)
	// we can tell the user at once
	
	try
	{
		if (nPort == 0)
			return S_OK;
		
		if (m_wndNotify.IsWindow() == FALSE)
		{
			m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
				
			RECT rect;
			rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
			m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
		}
		

		m_nListenPort = nPort;

		DWORD dwThreadID = 0;
		CreateThread(NULL,                  // Security attributes
					 0,                     // Initial stack size
					 ListenThreadEntry,   // Thread start address
					 (LPVOID) this,         // Thread parameter
					 (DWORD) 0,             // Creation flags
					 &dwThreadID);          // Thread identifier
	}
	catch( ... )
	{
		Fire_FatalError(L"Exception in CListener::Listen");
	}

	return S_OK;
}

DWORD __stdcall CListener::ListenThreadEntry(LPVOID lpvThreadParm)
{
	CListener* pThis = (CListener*)lpvThreadParm;
	
	return pThis->Listen();
}


DWORD CListener::Listen()
{

	m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_listenSocket == INVALID_SOCKET)
	{
	//	StopListenAndTerminate();
		ShootError(err_SocketCreationFailed);
		return err_SocketCreationFailed;
	}
	
	_ASSERT(m_nListenPort);

	SOCKADDR_IN saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;
	saServer.sin_port = htons((unsigned short)m_nListenPort);
	
	int nRet;
    nRet = bind(m_listenSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
	if (nRet == SOCKET_ERROR) 
	{
		// StopListenAndTerminate();
		closesocket(m_listenSocket);
		m_listenSocket = 0;
		ShootError(err_SocketBindFailed);
		return err_SocketBindFailed;
	}

	nRet = listen(m_listenSocket, 10);		// 10 is the number of clients that can be queued
	if (nRet == SOCKET_ERROR) 
	{
		closesocket(m_listenSocket);
		m_listenSocket = 0;
		// StopListenAndTerminate();
		ShootError(err_SocketListenFailed);
		return err_SocketListenFailed;
	}

	//
	// Wait for a client
	//
	SOCKET sckClient;
	while (TRUE)
	{
		if (IsRemoteConnectionAvailable(m_listenSocket, 1))
		{
			sckClient = accept(m_listenSocket, NULL,  NULL);
			if (sckClient != INVALID_SOCKET) 
			{
				// We fire connected event
				m_wndNotify.SendMessage(WM_NEWCONN, sckClient);
			}
		}

		// We check here if the thread has beeen killed
		if (m_syncListen.IsLocked())
		{
			break;
		}
	}


	// Send/receive from the client, and finally:
	if (m_listenSocket)
	{
		closesocket(m_listenSocket);
		m_listenSocket = 0;
	}

	m_syncListen.Unlock();

	return 0;
}

BOOL CListener::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	switch (uMsg)
	{
	case WM_NEWCONN:
		CListener* pThis = (CListener*)pClass;
		pThis->Fire_OnConnection(L"", 0, wParam);
		break;
	}

	return FALSE;
}

BOOL CListener::IsRemoteConnectionAvailable(SOCKET s, int timeout)
{
	FD_SET fdset;
	TIMEVAL defTimeout;
	int result;
	defTimeout.tv_sec = timeout;
	defTimeout.tv_usec = 0;

	FD_ZERO(&fdset);
	FD_SET(s, &fdset);
	result = select(0, &fdset, 0, 0, &defTimeout);
	return (result == 1);
}

STDMETHODIMP CListener::StopListenAndTerminate()
{
	m_syncListen.Lock(); // this causes the listen loop to exit
	m_syncListen.WaitForUnlock(3000); // after 3 secs, we exit anyway

	return S_OK;
}

void CListener::ShootError(EnumErrorState error)
{
}

STDMETHODIMP CListener::OneRingToBindThemAll(BSTR Ring)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CListener::ConvertNumericIP(double nAddr, BSTR *pResult)
{
	return E_NOTIMPL;
}
