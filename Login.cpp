// Login.cpp : Implementation of CLogin

#include "stdafx.h"
#include "P2P.h"
#include "Login.h"
#include "globals.h"

/////////////////////////////////////////////////////////////////////////////
// CLogin


char CLogin::m_szDing[1024];

STDMETHODIMP CLogin::SetLoginInfo(BSTR MyNick, BSTR PasswordEncrypted, BSTR EMailAddr, long nPort, long nSpeed)
{
	USES_CONVERSION;

	CRijndael encrypt;
	
	char szKey[17];
	int k = 14;
	for (int i=0;i<16;i++)
	{
		strncpy(&szKey[i], &m_szDing[k], 1);
		k += 3;

		if (k > 25)
			k += 2;

		if (k > 33)
			k -=1;

		if (k > 39)
			k += 7;
	}
	szKey[16] = '\0';

	encrypt.MakeKey(szKey, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16, 16);

	// We need our password
	// m_encrypt.
	char szPassword[25] = {'\0'};
	encrypt.Decrypt(W2A(PasswordEncrypted), szPassword, wcslen(PasswordEncrypted));
	m_sPassword = szPassword;
	
	int nLen = m_sPassword.size() - 1;
	while (m_sPassword.at(nLen) == '#')
	{
		nLen--;
	}

	// Get the info we need
	m_sPassword = m_sPassword.substr(0, nLen + 1);
	m_sNick = W2A(MyNick);
	m_sEMail = W2A(EMailAddr);

	TCHAR szInt[20];
	sprintf(szInt, "%lu", nPort);
	m_sPort = szInt;

	sprintf(szInt, "%lu", nSpeed);
	m_sSpeed = szInt;

	return S_OK;
}

STDMETHODIMP CLogin::OnMessage(int iCmd, BSTR sData)
{
	// 3  login ack [SERVER]; Format: <email>
	// 8  nickname not registered [SERVER]; Format:(empty)
	// 9  nickname already registered [SERVER]; Format: (empty)
	// 10 (0x0a) invalid nickname [SERVER]; Format: (empty)
	
	switch (iCmd)
	{
	case 0:
	case 404:
		if (m_bLoggingIn == true)
		{
			// This is a login error
			Fire_LoginError(sData);
			m_bLoggingIn = false;
		}
		break;
	case 3:
		// We logged in succesfully, so we save the server and
		// login name.
		AddMap(m_sServer, m_sNick);
		Fire_LoginComplete(VARIANT_TRUE);
		m_bLoggingIn = false;
		break;
	case 8:
		m_bLoggingIn = false;
		Login(NULL);
		break;
	case 9:
		break;
	case 10:
		break;
	}
	return S_OK;
}

STDMETHODIMP CLogin::Login(BSTR sServerName)
{
	// 2	login [CLIENT]
	// Format: <nick> <password> <port> "<client-info>" <link-type> [ <num> ]

	// 6	new user login [CLIENT]
	// Format: <nick> <pass> <port> "<client-info>" <speed> <email-address>

	// 7	nick check [CLIENT]
	// Format: <nick>

	// 14	login options [CLIENT]
	// NAME:%s ADDRESS:%s CITY:%s STATE:%s PHONE:%s AGE:%s INCOME:%s EDUCATION:%s
	
	// The servername will have to be stored somewhere
	
	USES_CONVERSION;
	
	m_bLoggingIn = true;

	BOOL bFound = FALSE;
	string sServer = W2A(sServerName);
	std::list<LoginMap>::iterator iter;
	for (iter=m_loginMapList.begin(); iter != m_loginMapList.end(); ++iter)
	{
		if ( (*iter).sServerName == sServer)
		{
			m_sNick = (*iter).sLoginName;
			bFound = TRUE; // we assume we danna have to register new user
			break;
		}
	}

	m_sServer = W2A(sServerName);
	
	if (bFound)
	{
		string sData;
		sData = m_sNick + " " + m_sPassword + " " + m_sPort + " \"" + "SoulShare v1" + "\" " + m_sSpeed;

		Fire_SendToServer(2, A2W(sData.c_str()));
	}
	else
	{
		string sData;
		sData = m_sNick + " " + m_sPassword + " " + m_sPort + " \"" + "SoulShare v1" + "\" " + m_sSpeed + " " + m_sEMail;

		Fire_SendToServer(6, A2W(sData.c_str()));
	}
	
	return S_OK;
}


STDMETHODIMP CLogin::get_LoginNick(BSTR *pVal)
{
	CComBSTR bstr = m_sNick.c_str();
	bstr.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CLogin::EncryptString(BSTR sText, BSTR *pResult)
{
	CRijndael encrypt;

	char szKey[17];
	int k = 14;
	for (int i=0;i<16;i++)
	{
		strncpy(&szKey[i], &m_szDing[k], 1);
		k += 3;

		if (k > 25)
			k += 2;

		if (k > 33)
			k -=1;

		if (k > 39)
			k += 7;
	}
	szKey[16] = '\0';

	encrypt.MakeKey(szKey, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16, 16);
	
	USES_CONVERSION;
	int nLen = 0;
	string str = W2A(sText);

	nLen = str.size();
	
	while (nLen < 16)
	{
		str += "#";
		nLen++;
	}

	char szResult[1024] = {'\0'};
	encrypt.Encrypt(str.c_str(), szResult, nLen);

	CComBSTR bstr = szResult;
	bstr.CopyTo(pResult);

	return S_OK;
}

BOOL CLogin::Load()
{
	std::ifstream file;
	file.open(string(m_sPath + "login.txt").c_str());

	if (file.is_open() == 0)
		return FALSE;

	while (file.good())
	{
		string sLine;
		TCHAR szLine[1024];
		file.getline(szLine, 1024);
		sLine = szLine;
		
		if (sLine != "")
		{
			string sServerName = GetFirstWord(sLine);
			sLine = sLine.substr(sServerName.size() + 1);
			string sLoginName = GetFirstWord(sLine);
			
			AddMap(sServerName, sLoginName);
		}
	}

	file.close();

	return TRUE;
}

BOOL CLogin::Save()
{
	std::fstream file;
	file.open(string(m_sPath + "login.txt").c_str(), ios::out);
	
	if (file.is_open() == 0)
		return FALSE;

	std::list<LoginMap>::iterator iter;
	for (iter=m_loginMapList.begin(); iter != m_loginMapList.end(); ++iter)
	{
		string sLine = (*iter).sServerName + " " + (*iter).sLoginName + "\n";

		file.write(sLine.c_str(), sLine.size());
	}

	file.close();

	return TRUE;
}

void CLogin::AddMap(string sServer, string sLogin)
{
	
	// First we cehck if the server is already in the list
	std::list<LoginMap>::iterator iter;
	for (iter=m_loginMapList.begin(); iter != m_loginMapList.end(); ++iter)
	{
		if ( (*iter).sServerName == sServer)
		{
			(*iter).sLoginName = sLogin;
			return;
		}
	}

	// Server not found. add new one
	LoginMap map;
	map.sServerName = sServer;
	map.sLoginName = sLogin;
	if (m_loginMapList.size() < 32)
	{
		m_loginMapList.push_back(map);
	}
	else
	{
		m_loginMapList.push_front(map);
		m_loginMapList.pop_back();
	}
}

STDMETHODIMP CLogin::Destroy()
{
	Save();

	return S_OK;
}

STDMETHODIMP CLogin::Init()
{
	Load();

	return S_OK;
}

STDMETHODIMP CLogin::get_Directory(BSTR *pVal)
{
	CComBSTR bstr = m_sPath.c_str();
	bstr.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CLogin::put_Directory(BSTR newVal)
{
	USES_CONVERSION;
	
	m_sPath = W2A(newVal);

	return S_OK;
}
