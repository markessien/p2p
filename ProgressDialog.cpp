// ProgressDialog.cpp : Implementation of CProgressDialog
#include "stdafx.h"
#include "ProgressDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog

void CProgressDialog::UpdateProgress(LPCTSTR psz)
{
	::SetWindowText(GetDlgItem(IDC_CAPTION), psz);
}
