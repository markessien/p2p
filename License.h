// License.h: interface for the CLicense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENSE_H__79B4BD9C_6DCE_4602_83F8_A6C981CC5267__INCLUDED_)
#define AFX_LICENSE_H__79B4BD9C_6DCE_4602_83F8_A6C981CC5267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream>
using namespace std;

// http://faqchest.dynhost.com/msdn/ATL/atl-98/atl-9808/atl98081019_09097.html

class CLicense  
{
protected:
   static BOOL VerifyLicenseKey(BSTR bstr)
   {
      USES_CONVERSION;
      return !lstrcmp(OLE2T(bstr), _T("1100x5h4232110003890342hy36"));
   }

   static BOOL GetLicenseKey(DWORD dwReserved, BSTR* pBstr) 
   {
      USES_CONVERSION;
      *pBstr = SysAllocString( T2OLE(_T("1100x5h4232110003890342hy36"))); 
      return TRUE;
   }

   static BOOL IsLicenseValid() 
   {
       char szPath[MAX_PATH];
       GetWindowsDirectory(szPath, MAX_PATH); 
       strcat(szPath, "\\p2pcomp.lic");
        
       	std::ifstream file;
	    file.open(szPath);

	    if (!file.is_open())
        {
            MessageBox(NULL, "P2P Component is not licensed to be used in a development enviroment", NULL, NULL);
            return FALSE;
        }
        
        TCHAR szLine[1024];
		file.getline(szLine, 1024);
	    
        if (strcmp(szLine, "guid:7BD07F49-5B92-4be7-82D4-2813A8C8CD5C:{EA287BEE-98F9-4284-9326-B226CA364407};p2p;rdcorp") == 0)
        {
		    return TRUE;
        }
        else
            MessageBox(NULL, "P2P Component is not licensed to be used in a development enviroment", NULL, NULL);

        file.close();

        return FALSE;
   }
};
#endif // !defined(AFX_LICENSE_H__79B4BD9C_6DCE_4602_83F8_A6C981CC5267__INCLUDED_)
