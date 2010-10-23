// SharedFolderManager.cpp : Implementation of CSharedFolderManager

#include "stdafx.h"
#include "P2P.h"
#include "SharedFolderManager.h"
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CSharedFolderManager



STDMETHODIMP CSharedFolderManager::AddSharedFolder(BSTR Path, VARIANT_BOOL * pResult)
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: This will add a shared folder to the folder list.
	// It will then start an asynchronous scan of the folder. Whenever
	// a new file is encountered, an event will be fired to the client.
	// When the directory scan is complete, the results are written to
	// the file.
	
	USES_CONVERSION;
	char* psz = W2A(Path);

	std::list<tagFolder>::iterator iter;
	for (iter=m_listFolders.begin(); iter != m_listFolders.end(); ++iter)
	{
		if (psz == (*iter).sPath)
		{
			*pResult = VARIANT_FALSE;
			return S_OK;
		}
	}
	
	tagFolder folder;
	folder.bScanned = false;
	folder.bWeeded = true; // we will scan it, which is same as weeding
	folder.sPath = psz;
	m_listFolders.push_back(folder);
	
	ScanFolder(psz);
	*pResult = VARIANT_TRUE;

	return S_OK;
}


STDMETHODIMP CSharedFolderManager::get_SharedFolderCount(int *pVal)
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: Returns the number of folders that are currently
	// being shared. Subfolders are not included, but are shared.
	
	*pVal = m_listFolders.size();
	return S_OK;
}

STDMETHODIMP CSharedFolderManager::get_SharedFolder(int Index, BSTR *pVal)
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: Returns the path of a folder. Used mostly for the 
	// listboxes/treeview. Filescanning is done here, so no point
	// using this path for anything,
	
	int iListIndex = 0;
	std::list<tagFolder>::iterator iter;
	for (iter=m_listFolders.begin(); iter != m_listFolders.end(); ++iter)
	{
		if (iListIndex == Index)
		{
			CComBSTR bstr = (*iter).sPath.c_str();
			bstr.CopyTo(pVal);
			return S_OK;
		}
		iListIndex++;
	}

	return S_OK;
}

STDMETHODIMP CSharedFolderManager::AsyncWeedDeadFiles()
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: This should be called after the app is
	// launched. A thread is started in low priority which
	// compares the results of the filelist with the contents
	// of the folders. FileAdded and FileRemoved events are 
	// fired. SharedFolderMissing events may also be fired.

	return S_OK;
}

STDMETHODIMP CSharedFolderManager::GetSharedFileListPath(BSTR *Path, VARIANT_BOOL *pResult)
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: Returns the path to the shared folder list.
	// The com client should then read the file and send it to
	// the server. The advised way to do this is to call this once on
	// connection, and the resulting file is sent to the server,
	// After the send, AsyncWeedDeadFiles is called, which will
	// fire events. In response to these events, the client should
	// share on unshare the files from the server.
	// When a new folder is added, the com client should do the same
	// thing. It should respond to events.
	// The next time the client is started, though, the folder will be
	// part of the list

	 *pResult = VARIANT_TRUE;
	
	USES_CONVERSION;
	CComBSTR bstr = string(m_sPath + "filelist.txt").c_str();
	bstr.CopyTo(Path);
	return S_OK;
}


STDMETHODIMP CSharedFolderManager::Load()
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: Loads folder list. Sharedfile list is not
	// loaded (too large)

	std::ifstream file;

	file.open(string(m_sPath + "folders.txt").c_str());

	if (file.is_open())
	{
		while (file.good())
		{
			TCHAR szLine[1024];
			file.getline(szLine, 1024);
	
			// We have exactly one line in our szLine. 
			// This line is a folder path
			tagFolder folder;
			folder.sPath = szLine;
			folder.bScanned = true; // if it is in folders file, it is scanned
			folder.bWeeded = false;
			if (folder.sPath > "")
			{
				m_listFolders.push_back(folder);
			}
		}

		file.close();
	}

	return S_OK;
}

STDMETHODIMP CSharedFolderManager::Save()
{
	// Author: Mark A. Essien
	// Date: 05.03.2002
	// Description: Saves the shared folder list to the disk.
	// Does not write the shared files list. This is done after
	// each directory is scanned. The result is appended to the
	// file.
	
	std::fstream file;
	file.open(string(m_sPath + "folders.txt").c_str(), ios::out);
	
	if (file.is_open())
	{
		std::list<tagFolder>::iterator iter;
		for (iter=m_listFolders.begin(); iter != m_listFolders.end(); ++iter)
		{
			string sData = (*iter).sPath + "\n";

			file.write(sData.c_str(),sData.size());
		}

		file.close();
	}
	else
		_ASSERT(FALSE);

	return S_OK;
}

STDMETHODIMP CSharedFolderManager::get_FilePath(BSTR *pVal)
{
	CComBSTR bstr = m_sPath.c_str();
	bstr.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CSharedFolderManager::put_FilePath(BSTR newVal)
{
	USES_CONVERSION;
	m_sPath = W2A(newVal);

	return S_OK;
}

void CSharedFolderManager::ScanFolder(string sPath)
{
	USES_CONVERSION;
	WIN32_FIND_DATA fd;
	HANDLE hSearch;

	hSearch = FindFirstFile(string(sPath + "\\*.*").c_str(), &fd);
	if(hSearch == INVALID_HANDLE_VALUE)
	{
		Fire_OnFolderRemoved(A2W(sPath.c_str()));
		return;
	}
	
	std::fstream file;
	file.open(string(m_sPath + "filelist.txt").c_str(), ios::out | ios::app);
	if (file.is_open() == 0)
		return;
	
	m_dlgProgress.Create(0, 0);
	m_dlgProgress.ShowWindow(SW_SHOW);

	do
	{
		if (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) 
		{
			
			TCHAR szBytes[20];
			sprintf(szBytes, "%d", fd.nFileSizeLow);
			
			// Filename
			string sData = "\"" + sPath + "\\" + fd.cFileName + "\"";
			
			// md5
			sData += " 00000000000000000000000000000000 ";

			// size in bytes
			sData += szBytes;
			
			// <bitrate> <frequency> <time>
			string sFile = fd.cFileName;
			if(sFile.substr(sFile.rfind(".")) == ".mp3")
			{
			
				TCHAR szMP3Path[256];
				strcpy(szMP3Path, string(sPath + "\\" + sFile.c_str()).c_str());
				if (m_mp3Info.loadInfo(szMP3Path) == 0)
				{
					TCHAR buffer[100];
					sprintf(buffer, " %lu %lu %lu\n", m_mp3Info.getBitrate(), 
							m_mp3Info.getFrequency(), m_mp3Info.getLengthInSeconds());

					sData += buffer;
				}
				else
					sData += " 0 0 0\n";
			}
			else
				sData += " 0 0 0\n";

			file.write(sData.c_str(), sData.size());
			m_dlgProgress.UpdateProgress(sFile.c_str());
		}

	}
	while(FindNextFile(hSearch, &fd));

	FindClose(hSearch);
	m_dlgProgress.DestroyWindow();
}

STDMETHODIMP CSharedFolderManager::RemoveFolder(BSTR Path)
{
	USES_CONVERSION;
	char* psz = W2A(Path);

	std::list<tagFolder>::iterator iter;
	for (iter=m_listFolders.begin(); iter != m_listFolders.end(); ++iter)
	{
		if (psz == (*iter).sPath)
		{
			m_listFolders.erase(iter);
			Fire_OnFolderRemoved(Path);
			break;;
		}
	}
	
	// Remove shared files from this directory from the
	// filelist
	int nPathLen = strlen(psz);
	string sFolderFileData;
	std::ifstream file;
	file.open(string(m_sPath + "filelist.txt").c_str());
	
	if (file.is_open())
	{
		while (file.good())
		{
			TCHAR szLine[1024];
			file.getline(szLine, 1024);

			if (strncmp(psz, szLine + 1, nPathLen) != 0)
			{
				sFolderFileData += szLine;
				sFolderFileData += "\n";
			}
		}

		file.close();
	}
	
	std::fstream ffile;
	ffile.open(string(m_sPath + "filelist.txt").c_str(), ios::out);
	if (ffile.is_open() == 0)
		return S_OK;

	ffile.write(sFolderFileData.c_str(), sFolderFileData.size());
	
	ffile.close();

	return S_OK;
}
