// Transfer.cpp : Implementation of CTransfer

#include "stdafx.h"
#include "P2P.h"
#include "Transfer.h"

/////////////////////////////////////////////////////////////////////////////
// CTransfer


STDMETHODIMP CTransfer::CancelTransfer()
{	
	/*
	if (m_stateTrans != trans_TransferComplete)
	{
		m_syncTransfer.Lock();
		m_syncTransfer.WaitForUnlock(2000);
	}
	*/

	m_bAbortRequested = true;
	Disconnect();
	ChangeTransferState(trans_Aborted);

	return S_OK;
}

STDMETHODIMP CTransfer::DownloadFile(BSTR Address, long nPort, BSTR MyNick, BSTR RemoteFilename, BSTR LocalFilename, long FileSize)
{
	USES_CONVERSION;

	_ASSERT(m_trType == type_Unknown);
	
	try
	{
		if (m_wndNotify.IsWindow() == FALSE)
		{
			m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
				
			RECT rect;
			rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
			m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
		}

		m_bAbortRequested = false;
		m_sLocalFile  = W2A(LocalFilename);
		m_sRemoteFile = W2A(RemoteFilename);
		m_sAddress    = W2A(Address);
		m_sMyNick     = W2A(MyNick);
		m_nFilesize   = FileSize;
		m_nPort       = nPort;
		m_trType      = type_DownloadTransfer;

		DWORD dwThreadID = 0;
		CreateThread(NULL,                  // Security attributes
					 0,                     // Initial stack size
					 DownloadThreadEntry,   // Thread start address
					 (LPVOID) this,         // Thread parameter
					 (DWORD) 0,             // Creation flags
					 &dwThreadID);          // Thread identifier
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CTransfer::DownloadFile");
	}

	return S_OK;
}

STDMETHODIMP CTransfer::get_BytesTranferred(double *pVal)
{
	_ASSERT(pVal);
	*pVal = m_nBytesTransferred;

	return S_OK;
}

STDMETHODIMP CTransfer::get_IsRemotelyQueued(VARIANT_BOOL *pVal)
{
	*pVal = m_stateTrans == trans_RemotelyQueued ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CTransfer::put_IsRemotelyQueued(VARIANT_BOOL newVal)
{
	m_stateTrans = (newVal == VARIANT_TRUE) ? trans_RemotelyQueued : trans_Connecting;

	_ASSERT(newVal == VARIANT_TRUE); // you don't set it false manually

	return S_OK;
}

STDMETHODIMP CTransfer::get_ProgressPercent(int *pVal)
{
	if (m_nBytesTransferred && m_nFilesize)
	{
		*pVal = (int)(float)(((float)m_nBytesTransferred / (float)m_nFilesize) * 100.0);
	}
	else
	{
		*pVal = 0;
	}

	return S_OK;
}

STDMETHODIMP CTransfer::get_Speed(int *pVal)
{
	if (m_stateTrans == type_AltDownloadTransfer)
	{
		*pVal = 0;
	}
	else
		*pVal = m_nRate;

	return S_OK;
}

STDMETHODIMP CTransfer::ResumeTransfer()
{
	if (m_stateTrans ==	trans_RemotelyQueued ||
		m_stateTrans ==	trans_Error ||
		m_stateTrans ==	trans_Aborted)
	{
		ChangeTransferState(trans_ContactingServer);
		Fire_NeedTransferReRequest();
	}

	return S_OK;
}

STDMETHODIMP CTransfer::get_StatusString(BSTR *pVal)
{
	CComBSTR bstr = "Contacting server...";

	switch (m_stateTrans)
	{
	case trans_ContactingServer:
		bstr = "Contacting Server";
		break;
	case trans_RemotelyQueued:
		bstr = "Remotely Queued";
		break;
	case trans_Connecting:
		bstr = "Connecting...";
		break;
	case trans_Negotiating:
		bstr = "Negotiating...";
		break;
	case trans_TransferringByteStream:
		{
			switch (m_trType)
			{
			case type_UploadTransfer:
				bstr = "Uploading...";
				break;
			case type_AltUploadTransfer:
				bstr = "Uploading (push) ...";
				break;
			case type_DownloadTransfer:
				bstr = "Downloading...";
				break;
			case type_AltDownloadTransfer:
				bstr = "Downloading (push) ...";
				break;
			default:
				bstr = "Illegal Transfer";
				break;
			}
		}
		break;
	case trans_TransferComplete:
		bstr = "Complete";
		break;
	case trans_Aborted:
		bstr = "Aborted";
		break;
	case trans_Error:
		{
			bstr = TranslateError(m_stateErr);
		}
		break;
	};
	
	bstr.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CTransfer::UploadFile(long hSocket)
{
	_ASSERT(m_trType == type_Unknown);
	
	_ASSERT(hSocket);
	
	try
	{
		if (m_wndNotify.IsWindow() == FALSE)
		{
			m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
				
			RECT rect;
			rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
			m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
		}
		
		m_trType = type_UploadTransfer;

		m_socket = (SOCKET)hSocket;
			
		DWORD dwThreadID = 0;
		CreateThread(NULL,                  // Security attributes
					 0,                     // Initial stack size
					 UploadThreadEntry,   // Thread start address
					 (LPVOID) this,         // Thread parameter
					 (DWORD) 0,             // Creation flags
					 &dwThreadID);          // Thread identifier
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CTransfer::UploadFile");
	}

	return S_OK;
}

STDMETHODIMP CTransfer::get_TransferType(EnumTransferType *pVal)
{
	*pVal = m_trType;

	return S_OK;
}

void CTransfer::ChangeSocketState(EnumSocketState newState)
{
	m_stateSck = newState;
}


DWORD __stdcall CTransfer::DownloadThreadEntry(LPVOID lpvThreadParm)
{
	CTransfer* pThis = (CTransfer*)lpvThreadParm;

	pThis->m_bReadyToUnload = false;
	DWORD dwResult = pThis->NegotiateDownload();
	pThis->m_bReadyToUnload = true;

	return dwResult;
}

void CTransfer::ChangeTransferState(EnumTransferState newVal)
{
	m_stateTrans = newVal;
}

DWORD CTransfer::SendFile()
{
	// Don't forget to check if this path is shared
	
	ChangeTransferState(trans_TransferringByteStream);

	ifstream file;
	file.open(m_sLocalFile.c_str(), ios::in|ios::binary);
	
	DWORD dwBaseTime  = GetTickCount();
	long  nBaseBytes = 0;

	if (file.is_open())
	{
		int iLen = 0;
		int iRet = 0;
		char buffer[1024];
		
		// get length of file:
		file.seekg (0, ios::end);
		m_nFilesize = file.tellg();
		
		// Seek to resume offset
		file.seekg (m_nOffset, ios::beg);
		
		char szSize[100];
		sprintf(szSize, "%.0f", m_nFilesize);

		iRet = send(m_socket, szSize, strlen(szSize), 0);

		while (file.good())
		{
			file.read(buffer, 1023);

			iLen = file.gcount();

			iRet = send(m_socket, buffer, iLen, 0);

			if (iRet == SOCKET_ERROR)
			{
				ShootError(err_ConnectionLost);
				// shoot error
				break;
			}

			m_nBytesTransferred += iRet;

			if (GetTickCount() - dwBaseTime > 2000)
			{
				m_nRate = (m_nBytesTransferred - nBaseBytes) / (GetTickCount() - dwBaseTime);

				nBaseBytes = m_nBytesTransferred;
				dwBaseTime = GetTickCount();
			}

//			if (m_syncTransfer.IsLocked())
//			{
//				ChangeTransferState(trans_Aborted);
//				break;
//			}
		}
	}
	else
	{
		// shoot error
		return 667;
	}
	
	// Disconnect
	closesocket(m_socket);
	m_socket = 0;
	m_stateSck = socketDisconnected;
	
	// Close file
	file.close();
	
	// Return from abort function.
//	m_syncTransfer.Unlock();
	
	if (m_nBytesTransferred == m_nFilesize)
	{
		ChangeTransferState(trans_TransferComplete);
	}
	
	return 0;
}

DWORD CTransfer::NegotiateUpload()
{
	ChangeTransferState(trans_Negotiating);
	
	// Send ascii 49
	char szOne[2] = {49, '\0'};
	send(m_socket, szOne, 1, 0);

	int iLen = 0;

	// get GET
	char szGet[5] = {'\0'};
	iLen = recv(m_socket, szGet, 4, 0);
	szGet[iLen] = '\0';
	
	if (iLen == 0 || szGet[0] == '\0')
	{
			// Could not open file. 
		Disconnect();
		ShootError(err_InvalidDataReceived);
		return 1;
	}

	// We get the request
	char szBuffer[300]; // 256 + some space
	iLen = recv(m_socket, szBuffer, 300, 0);
	szBuffer[iLen] = '\0';
	
	if (iLen == 0 || szBuffer[0] == '\0')
	{
			// Could not open file. 
		Disconnect();
		ShootError(err_InvalidDataReceived);
		return 1;
	}

	string sData = szBuffer;
	
	try
	{
		m_sHisNick = GetFirstWord(sData);
		sData = sData.substr(m_sHisNick.size() + 1);

		string sFile = GetFirstWord(sData);
		sData = sData.substr(sFile.size() + 3);

		if (strcmp(szGet, "SEND") == 0)
		{
			// We change this to a download
			m_nFilesize = atol(sData.c_str());
			m_trType = type_AltDownloadTransfer;
			m_sRemoteFile = sFile;
			send(m_socket, "0", 1, 0); // offset
		}
		else
		{
			m_nOffset = atol(GetFirstWord(sData).c_str());
			m_sLocalFile = sFile;

		}
	}
	catch (...)
	{
		// Invalid data probably
		Disconnect();
		ShootError(err_InvalidDataReceived);
		return 1;
	}

	m_wndNotify.SendMessage(WM_NEGCOMPLETE);
	
	// We start sending or getting our file
	
	DWORD dwResult = 666;
	if (m_trType == type_AltDownloadTransfer)
	{
		dwResult = ReceiveFile();
	}
	else
	{
		dwResult = SendFile();
	}

	return dwResult;
}

HRESULT CTransfer::NegotiateDownload()
{
	USES_CONVERSION;
	
	ChangeTransferState(trans_Connecting);

	WSADATA	WSAData;
	if (WSAStartup (MAKEWORD(2,0), &WSAData) != 0)
	{
		ChangeSocketState(socketDisconnected);
		ShootError(err_WSAStartupFailed);
		return S_OK;
	}

	m_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		ChangeSocketState(socketDisconnected);
		ShootError(err_SocketCreationFailed);
		return S_OK;
	}
	
	sockaddr_in sckAddress;
	sckAddress.sin_family = AF_INET;
	sckAddress.sin_port   = htons ((unsigned short)m_nPort);
	
	const char* pszAddr = m_sAddress.c_str();

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
			Disconnect();
			ShootError(err_HostNameCouldNotBeResolved);
			return S_OK;
		}

		sckAddress.sin_addr.S_un.S_addr = *((ULONG*)pHost->h_addr);
	}
	
	if (connect(m_socket, (SOCKADDR *) &sckAddress, sizeof (sckAddress)) == SOCKET_ERROR)
	{
		Disconnect();
		ShootError(err_CouldNotConnect);
		return S_OK;
	}

	// We are connected
	ChangeSocketState(socketConnected);
	ChangeTransferState(trans_Negotiating);

	// We get the 1 it is supposed to send us
	char szOne[2];
	if ((recv(m_socket, szOne, 1, 0) < 1 || szOne[0] != '1'))
	{
		Disconnect();
		m_sInvalidData = "1 not sent";
		ShootError(err_InvalidDataReceived);
		return S_OK;
	}
	
	if (m_trType == type_AltUploadTransfer)
	{
		// We send the file
		// 

		// We get the filesize
		ifstream file;
		file.open(m_sLocalFile.c_str(), ios::in|ios::binary);
		file.seekg (0, ios::end);
		m_nFilesize = file.tellg();
		file.close();
		
		TCHAR szSize[100];
		sprintf(szSize, " %.0f", m_nFilesize);
		
		// We send the data
		string sSend = m_sMyNick + " " + '\"' + m_sLocalFile + '\"' + szSize;
		send(m_socket, "SEND", 4, 0);
		send(m_socket, sSend.c_str(), sSend.size(), 0);

		// the next packet we get is either an error message
		// or the offset

		int iLen = 0;
		char buffer[60];
		iLen = recv(m_socket, buffer, 59, 0);
		buffer[iLen] = '\0';

		if (atol(buffer) == 0L && strlen(buffer) > 1)
		{
			// we have a textual error
			Disconnect();
			m_sInvalidData = buffer;
			ShootError(err_InvalidDataReceived);
			return S_OK;
		}
		else
		{
			// We have a numeric value
			m_nOffset = atol(buffer);
		}

		return SendFile();
	}
	else
	{
		// We request the file
		string sSend = m_sMyNick + " " + '\"' + m_sRemoteFile + '\"' + " 0";
		
		send(m_socket, "GET", 3, 0);
		send(m_socket, sSend.c_str(), sSend.size(), 0);

		// We will receive the byte stream with the file size
		// prepended to the beginning. We read the number of
		// bytes that should be the file size off the front.
		// If they don't match, problem.

		char szSize[60];
		sprintf(szSize, "%.0f", m_nFilesize);
		int nLen = strlen(szSize);
		
		char szSentSize[60];
		if (recv(m_socket, szSentSize, nLen, 0) < nLen)
		{
			// either 0 data or socket_error
			Disconnect();
			m_sInvalidData = "Filesize does not match";
			ShootError(err_InvalidDataReceived);
			return S_OK;
		}
		
		szSentSize[nLen] = '\0';

		if (strcmp(szSize, szSentSize) != 0)
		{
			// Error. This can happen and does happen
			Disconnect();
			m_sInvalidData = szSentSize;
			ShootError(err_InvalidDataReceived);
			return S_OK;
		}

		// We have a byte stream now.
		return ReceiveFile();
	}
	
	return 666;
}

CComBSTR CTransfer::TranslateError(EnumErrorState err)
{
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
	case err_InvalidDataReceived:
		{
			USES_CONVERSION;
			string sErr = "Invalid data received. ";
			sErr += m_sInvalidData.c_str();

			bstr = A2W(sErr.c_str());
		}
		break;
	case err_ConnectionLost:
		bstr = "Connection Lost";
		break;
	case err_CouldNotOpenFile:
		bstr = "Local file could not be opened";
		break;
	case err_SocketBindFailed:
		bstr = "Socket could not be bound to port";
		break;
	case err_SocketListenFailed:
		bstr = "Could not listen on port";
		break;
	}

	return bstr;
}

DWORD CTransfer::ReceiveFile()
{
	ofstream file;

	if (OpenFileAuto(&file, m_sLocalFile) == 0)
	{
		// Could not open file. 
		Disconnect();
		ShootError(err_CouldNotOpenFile);
		return E_FAIL;
	}

	_ASSERT(file.is_open() != 0);

	ChangeTransferState(trans_TransferringByteStream);
	
	DWORD dwBaseTime  = GetTickCount();
	long  nBaseBytes = 0;
	char buffer[1024];
	while (m_nBytesTransferred != m_nFilesize)
	{
		int nSize = recv(m_socket, buffer, 1023, 0);
		if (nSize == SOCKET_ERROR || (nSize == 0 && m_nBytesTransferred != m_nFilesize))
		{
			Disconnect();
			ShootError(err_ConnectionLost);
			return E_FAIL;
		}
		
		if (nSize == 0) // Complete
			break;

		file.write(buffer, nSize);
		m_nBytesTransferred += nSize;
		
		_ASSERT(file.bad() != true);

		if (GetTickCount() - dwBaseTime > 2000)
		{
			// 2 seconds have elapsed.
			// We check how much data we received in the
			// 2 secs.
			
			m_nRate = (m_nBytesTransferred - nBaseBytes) / (GetTickCount() - dwBaseTime);

			nBaseBytes = m_nBytesTransferred;
			dwBaseTime = GetTickCount();
		}

		/*
		if (m_syncTransfer.IsLocked())
		{
			ChangeTransferState(trans_Aborted);
			break;
		}
		*/
	}
	
	// Close socket
	closesocket(m_socket);
	m_socket = 0;
	m_stateSck = socketDisconnected;

	// Close file
	file.close();
	
	// Return abort function
//	m_syncTransfer.Unlock();

	if (m_nBytesTransferred == m_nFilesize)
	{
		ChangeTransferState(trans_TransferComplete);
	}
	
	m_wndNotify.SendMessage(WM_TRANSCOMPLETE);

	return S_OK;
}

DWORD __stdcall CTransfer::UploadThreadEntry(LPVOID lpvThreadParm)
{
	CTransfer* pThis = (CTransfer*)lpvThreadParm;
	
	pThis->m_bReadyToUnload = false;
	DWORD dwResult = pThis->NegotiateUpload();
	pThis->m_bReadyToUnload = true;

	return dwResult;
}

BOOL CTransfer::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CTransfer* pThis = (CTransfer*)pClass;

	switch (uMsg)
	{
	case WM_NEGCOMPLETE:
		{
			USES_CONVERSION;

			string sFile;
			sFile = (pThis->m_trType == type_AltDownloadTransfer) ? pThis->m_sRemoteFile : pThis->m_sLocalFile;

			pThis->Fire_OnNegotiationComplete(A2W(sFile.c_str()), A2W(pThis->m_sHisNick.c_str()), pThis->m_nOffset);
		}
		break;
	case WM_TRANSCOMPLETE:
		{
			pThis->Fire_OnTransferComplete();
		}
		break;
	}

	return FALSE;
}


void CTransfer::ShootError(EnumErrorState err)
{
	m_stateErr = err;
	
	CComBSTR bstr = TranslateError(m_stateErr);

	ChangeTransferState(trans_Error);
//	Fire_OnError(err, bstr);
}

void CTransfer::Disconnect()
{
	if ( m_socket ) 
	{
		closesocket (m_socket);
		m_socket = 0;
		
		m_stateSck = socketDisconnected;
		Trace("Socket Closed");
	}
}

STDMETHODIMP CTransfer::get_LocalTargetFile(BSTR *pVal)
{
	CComBSTR bstr = m_sLocalFile.c_str();
	bstr.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CTransfer::put_LocalTargetFile(BSTR newVal)
{
	USES_CONVERSION;

	m_sLocalFile = W2A(newVal);

	return S_OK;
}

STDMETHODIMP CTransfer::get_RemoteFileSize(double *pVal)
{
	*pVal = m_nFilesize;

	return S_OK;
}

STDMETHODIMP CTransfer::put_RemoteFileSize(double newVal)
{
	m_nFilesize = newVal;

	return S_OK;
}

STDMETHODIMP CTransfer::UploadFileAlt(BSTR Address, long nPort, BSTR MyNick, BSTR LocalFilename)
{
	USES_CONVERSION;

	_ASSERT(m_trType == type_Unknown);
	
	try
	{
		if (m_wndNotify.IsWindow() == FALSE)
		{
			m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
				
			RECT rect;
			rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
			m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
		}

		m_bAbortRequested = false;
		m_sLocalFile  = W2A(LocalFilename);
		m_sAddress    = W2A(Address);
		m_sMyNick     = W2A(MyNick);
		m_nFilesize   = 0;
		m_nPort       = nPort;
		m_trType      = type_AltUploadTransfer;

		DWORD dwThreadID = 0;
		CreateThread(NULL,                  // Security attributes
					 0,                     // Initial stack size
					 DownloadThreadEntry,   // Thread start address
					 (LPVOID) this,         // Thread parameter
					 (DWORD) 0,             // Creation flags
					 &dwThreadID);          // Thread identifier
	}
	catch (...)
	{
		Fire_FatalError(L"Exception in CTransfer::UploadFile");
	}

	return S_OK;
}

STDMETHODIMP CTransfer::get_TransferState(EnumTransferState *pVal)
{
	*pVal = m_stateTrans;

	return S_OK;
}

int CTransfer::OpenFileAuto(ofstream *pStream, string sFilepath)
{
	// This function opens a file, and if the file is already
	// there, it creates a new filename and puts (1) around the
	// end.

	_ASSERT(pStream);
	ifstream inFile;

	bool bFoundCandidate = false;

	try
	{
		inFile.open(sFilepath.c_str(), ios::in | ios::binary );
		
		if (inFile.is_open() != 0)
		{
			// We could open the file for input. This means that the file
			// already exists
			inFile.close();
			
			for (int i=0;i<10;i++)
			{
				// Add (1) around the file. If there is already a (1),
				// add a (2)
				string::size_type pos = sFilepath.rfind(".");

				if (pos == string::npos)
				{
					// There is no extension on this file.
					// We set the pos to the end
					pos = sFilepath.size();
				}
				
				bool bBrackets = false;
				long nNumber = 1;
				if (sFilepath.at(pos - 1) == ')')
				{
					// There is a file in this form
					// c:\dude(1).mp3
					nNumber = atol(&sFilepath.at(pos - 2));
					if (nNumber != 0) // elsesomething is wrong
					{
						nNumber++;
						bBrackets = true;
					}
					else
						bBrackets = false;
				}

				string sExt;
				if (pos != sFilepath.size())
				{
					// We remove the extension
					sExt = sFilepath.substr(pos);
					sFilepath = sFilepath.substr(0, pos);
				}
				

				if (bBrackets == false)
					sFilepath = sFilepath + "(1)" + sExt;
				else
				{
					// We have to remove the brackets
					TCHAR szNo[20];
					sprintf(szNo, "%lu", nNumber);
					sFilepath = sFilepath.substr(0, pos - 3) + "(" + szNo + ")";
					sFilepath += sExt;
				}

				inFile.open(sFilepath.c_str(), ios::in | ios::binary );

				if (inFile.is_open() == 0)
				{
					bFoundCandidate = true;
					break;
				}
				else
					inFile.close();
			}
		}
		else
		{
			bFoundCandidate = true;
		}
	}
	catch (...)
	{
		_ASSERT(FALSE);
		bFoundCandidate = false;
		inFile.close();
	}

	m_sLocalFile = sFilepath;
	
	if (bFoundCandidate)
		pStream->open(sFilepath.c_str(), ios::out | ios::binary );

	return pStream->is_open();
}

STDMETHODIMP CTransfer::get_ReadyToUnload(VARIANT_BOOL *pVal)
{
	if (m_bReadyToUnload == true)
	{
		switch (m_stateTrans)
		{
		case trans_TransferComplete:
		case trans_RemotelyQueued:
		case trans_Error:
		case trans_Aborted:
			*pVal = VARIANT_TRUE;
			break;
		default:
			*pVal = VARIANT_FALSE;
		}
	}
	else
	{
		*pVal = VARIANT_FALSE;
	}

	return S_OK;
}
