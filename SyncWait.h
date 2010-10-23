// SyncWait.h: interface for the CSyncWait class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
#define AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncWait  
{
public:
	BOOL IsLocked();
	void Unlock();
	void Lock();
	void WaitForUnlock(DWORD dwMilliseconds);

	CSyncWait();
	virtual ~CSyncWait();

private:
	HANDLE m_hEvent;
	BOOL   m_bIsLocked;
};

#endif // !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
