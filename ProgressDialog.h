// ProgressDialog.h : Declaration of the CProgressDialog

#ifndef __PROGRESSDIALOG_H_
#define __PROGRESSDIALOG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog
class CProgressDialog : 
	public CAxDialogImpl<CProgressDialog>
{
public:
	
	CProgressDialog()
	{
	}

	~CProgressDialog()
	{
	}

	enum { IDD = IDD_PROGRESSDIALOG };

BEGIN_MSG_MAP(CProgressDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
	void UpdateProgress(LPCTSTR psz);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__PROGRESSDIALOG_H_
