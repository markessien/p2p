// NapsterServer.cpp : Implementation of CNapsterServer

#include "stdafx.h"
#include "P2P.h"
#include "NotifyWindow.h"
#include "NapsterServer.h"
#include "globals.h"

/////////////////////////////////////////////////////////////////////////////
// CNapsterServer



STDMETHODIMP CNapsterServer::AppInitialize(VARIANT_BOOL *pResult)
{
	// Author: Mark A. Essien
	// Date: 16.02.2002
	// Description: 
	
	try
	{
		InitializeCriticalSection(&m_critObj);

		WSADATA	WSAData;
		if (0 != WSAStartup (MAKEWORD(2,0), &WSAData))
		{
			ShootError(err_WSAStartupFailed);
			*pResult = VARIANT_FALSE;
			return S_OK;
		}
		
		// Create our notification window
		m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
			
		RECT rect;
		rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
		m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
		
		*pResult = VARIANT_TRUE;
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CNapsterServer::AppInitialize");
	}

	return S_OK;
}

STDMETHODIMP CNapsterServer::ConnectToServer(BSTR bstrAddress, long nPort, VARIANT_BOOL *pResult)
{
	USES_CONVERSION;
	
	try
	{
		// Perform preliminary checks

		if (m_sckState == socketConnected || m_socket != NULL)
		{
			*pResult = VARIANT_TRUE;
			return S_OK;
		}

		if (m_wndNotify.IsWindow() == FALSE)
		{
			ShootError(err_WSAStartupNotCalled);
			*pResult = VARIANT_FALSE;
			return S_OK;
		}
		
		_ASSERT(m_socket == NULL);

		m_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			ShootError(err_SocketCreationFailed);
			Disconnect();
			*pResult = VARIANT_FALSE;
			return S_OK;
		}

		if (WSAAsyncSelect (m_socket,
							m_wndNotify.m_hWnd, 
							WM_SOCKET_NOTIFY, 
							FD_CONNECT | FD_READ | FD_CLOSE) != 0)
		{
			Disconnect();
			ShootError(err_WSAAsyncSelectFailed);
			Disconnect();
			*pResult = VARIANT_FALSE;
			return S_OK;
		}
		
		sockaddr_in sckAddress;
		sckAddress.sin_family = AF_INET;
		sckAddress.sin_port = htons ((unsigned short)nPort);
		
		char* pszAddr = W2A(bstrAddress);

		//Check if address is an IP or a Domain Name
		int a = pszAddr[0];
		if (a > 47 && a < 58) 
		{
			sckAddress.sin_addr.S_un.S_addr = inet_addr(pszAddr);
		} 
		else
		{
			struct hostent *pHost;
			pHost = gethostbyname(pszAddr);

			if (pHost == 0)
			{
				ShootError(err_HostNameCouldNotBeResolved);
				Disconnect();
				*pResult = VARIANT_FALSE;
				return S_OK;
			}

			sckAddress.sin_addr.S_un.S_addr = *((ULONG*)pHost->h_addr);
		}
		
		Trace("Connecting to server (address=%s, port=%lu)", pszAddr, nPort);
		
		connect(m_socket, (SOCKADDR *) &sckAddress, sizeof (sckAddress));

		if (WSAEWOULDBLOCK != WSAGetLastError ())
		{
			ShootError(err_CouldNotConnect);
			Disconnect();
			*pResult = VARIANT_FALSE;
			return S_OK;
		}
		
		Trace("Connection sequence started");

		*pResult = VARIANT_TRUE;
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CNapsterServer::ConnectToServer");
	}

	return S_OK;
}

BOOL CNapsterServer::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CNapsterServer* pThis = (CNapsterServer*)pClass;

	if (uMsg == WM_SOCKET_NOTIFY)
	{
		WORD wEvent = WSAGETSELECTEVENT (lParam);
		WORD wError = WSAGETSELECTERROR (lParam);

		switch (wEvent)
		{
		case FD_CONNECT:
			{
				Trace("FD_CONNECT");

				if (wError)
				{
					Trace("FD_CONNECT: Error!");
					pThis->ShootError(err_ConnectionError);
					pThis->Disconnect();
				}
				else
				{
					pThis->ChangeSocketState(socketConnected);
					pThis->Fire_OnConnected();
				}

				return TRUE;
			}
			break;
		case FD_READ:
			{
				if (wError)
				{
					Trace("FD_READ Error!");
					return TRUE;
				}

				pThis->RetrieveData();
				
				return TRUE;
			}
			break;
		case FD_CLOSE:
			{
				Trace("FD_CLOSE: Remote server closed connection");
				pThis->Disconnect();
				pThis->Fire_OnRemoteServerClosedConnection();
			}
			break;
		} // switch
	} // if

	return FALSE;
}

//DEL DWORD CNapsterServer::IsDataPending(SOCKET sck)
//DEL {
//DEL 
//DEL 	return dwNumBytes;
//DEL }

void CNapsterServer::RetrieveData()
{
	Trace("CNapsterServer::RetrieveData()");
	
	DWORD dwNumBytes = 0;
	ioctlsocket(m_socket, FIONREAD, &dwNumBytes);

	if (dwNumBytes > 0) 
	{
		Trace("Entering critical section of CNapsterServer::RetrieveData()");

		EnterCriticalSection(&m_critObj);

		///////////////////////////////
		// Get the header

		char szHead[4] = {0};
		int  nSize = 0;
		int  nOldSize = 0;

		// We get the first 4 bytes (cmd and len)
		nSize = recv (m_socket, szHead, 4, 0);
		nOldSize = nSize;
		
		Trace("Received header: %s", szHead);

		//If in between packets while recv'ing,
		//loop till we receive the whole 4 bytes

		while (nSize != 4) 
		{
			Trace("Data Header Mismatch. Looping");

			nSize = recv (m_socket, &szHead[nOldSize], 4 - nOldSize, 0);
			if (nSize != -1) 
			{
				if (nSize + nOldSize == 4) 
				{
					break;
				}
			}
			else if (m_socket == NULL)
			{
				break;
			}

			WaitMessage();
		}
		
		// Copy our length and cmd values
		unsigned short nLen = 0;
		unsigned short nCmd = 0;
		
		memcpy(&nLen, &szHead[0], 2);
		memcpy(&nCmd, &szHead[2], 2);
		
		_ASSERT(nCmd < 1000); // if it larger, we probably have a bug

		Trace("Received data : Length=%lu & Cmd=%lu", nLen, nCmd);
		//////////////////////////////
		//We get out data
		
		char* pszData = 0;
		if (nLen > 0)
		{
			pszData = new char[nLen+1];

			nSize = recv (m_socket, pszData, nLen, 0);
			nOldSize = nSize;

			//If in between packets while recv'ing
			while (nSize != nLen) 
			{
				Trace("Data Mismatch. Looping");
				nSize = recv (m_socket, &pszData[nOldSize], nLen - nOldSize, 0);
				Trace("Received this much on this loop: nSize=%d", nSize);
				if (nSize != -1)
				{
					nSize += nOldSize;
					nOldSize = nSize;
					if (nLen == nSize) 
					{
						Trace("nLen = nSize = %lu", nSize);
						break;
					}
				}
				else if (m_socket == NULL)
				{
					break;
				}

				DoEvents();
			}
			pszData[nLen] = '\0';
		}
		
		Trace("Data received=%s", pszData);
		
		try
		{
            Trace("About to manipulate m_bstrData\n");

			// Potential error problem
			if (pszData)
			{
				m_bstrData = pszData;
			}
			else
				m_bstrData.Empty();

			m_nCmd = nCmd;
            
            Trace("Fire_OnDataReceived()\n");

			Fire_OnDataReceived();
            
            Trace("delete [] pszData;\n");
			delete [] pszData;
			pszData = 0;
		}
		catch (...)
		{
			_ASSERT(FALSE);
			Trace("Exception in napster server");
		}
		
		// end potential error problem

		LeaveCriticalSection(&m_critObj);
		Trace("Left Critical Section of CNapsterServer::RetrieveData");
	}
	else
		Trace("No data in socket buffer");
}

STDMETHODIMP CNapsterServer::SendData(long nCmd, BSTR strData)
{
	// Send a command to the napster server
	
	USES_CONVERSION;
	
	try
	{
		char* pszData = W2A(strData);

		short len = strlen(pszData); 
		short cmd = (short)nCmd;

		send(m_socket, (char *) &len, sizeof(len), 0);
		send(m_socket, (char *) &cmd, sizeof(cmd), 0);
		send(m_socket, pszData, len, 0);
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CNapsterServer::SendData");
	}

	return S_OK;
}

STDMETHODIMP CNapsterServer::Disconnect()
{
	try
	{
		Trace("Disconnect called");

		if ( m_socket ) 
		{
			closesocket (m_socket);
			m_socket = 0;

			Trace("Socket Closed");
		}
		
		ChangeSocketState(socketDisconnected);
		
		Fire_OnDisconnected();
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CNapsterServer::Disconnect");
	}

	return S_OK;
}

STDMETHODIMP CNapsterServer::AppUninitialize()
{
	try
	{
		Disconnect();

		WSACleanup();
		
		if (m_wndNotify.IsWindow())
			m_wndNotify.DestroyWindow();
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CNapsterServer::AppUninitialize");
	}

	return S_OK;
}

//DEL STDMETHODIMP CNapsterServer::get_State(ConnectionState *pVal)
//DEL {
//DEL 	*pVal = m_state;
//DEL 
//DEL 	return S_OK;
//DEL }


STDMETHODIMP CNapsterServer::get_CurrentData(BSTR *pVal)
{
	m_bstrData.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CNapsterServer::get_CurrentCmd(long *pVal)
{
	*pVal = m_nCmd;

	return S_OK;
}

void CNapsterServer::DoEvents()
{
	MSG Message;
	while (PeekMessage(&Message,NULL,(UINT) 0,(UINT) 0, PM_REMOVE))
	{
        // Send the message to the window procedure
		if (Message.message == WM_SOCKET_NOTIFY)
		{
			//
			OutputDebugString("WM_SOCKET_NOTIFY received. Returning to recv loop.\n");
			return;
		}

        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
	
	WaitMessage();
}

void CNapsterServer::ShootError(EnumErrorState err)
{
	ChangeSocketState(socketDisconnected);
	
	CComBSTR bstr = "Socket Error";
	switch (err)
	{
	case err_NoError:
		bstr = "No Error";
		break;
	case err_GenericError:
		bstr = "Error";
		break;
	case err_WSAStartupFailed:
		bstr = "WSAStartup Failed";
		break;
	case err_WSAStartupNotCalled:
		bstr = "Socket not yet intialized";
		break;
	case err_SocketCreationFailed:
		bstr = "Socket Creation Failed";
		break;
	case err_WSAAsyncSelectFailed:
		bstr = "Async selection failed";
		break;
	case err_HostNameCouldNotBeResolved:
		bstr = "Hostname could not be resolved";
		break;
	case err_CouldNotConnect:
		bstr = "Could not connect";
		break;
	case err_ConnectionError:
		bstr = "Connection Error";
		break;
	}

	Fire_OnError(bstr);
}

STDMETHODIMP CNapsterServer::get_SocketState(EnumSocketState *pVal)
{
	*pVal = m_sckState;

	return S_OK;
}


STDMETHODIMP CNapsterServer::get_ErrorState(EnumErrorState *pVal)
{
	*pVal = m_errState;

	return S_OK;
}

void CNapsterServer::ChangeSocketState(EnumSocketState newState)
{
	m_sckState = newState;
}
