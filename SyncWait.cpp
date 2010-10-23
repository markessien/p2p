// SyncWait.cpp: implementation of the CSyncWait class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SyncWait.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSyncWait::CSyncWait()
{
	m_bIsLocked = FALSE;
	m_hEvent = CreateEvent(0, true, true, 0);
}

CSyncWait::~CSyncWait()
{

}

void CSyncWait::WaitForUnlock(DWORD dwMilliseconds)
{
	WaitForSingleObject(m_hEvent, dwMilliseconds); // Elapses after 10 seconds
}

void CSyncWait::Lock()
{
	// Set the event so that other threads will know when
	// we are in this function.
	m_bIsLocked = TRUE;
	ResetEvent(m_hEvent);
}

void CSyncWait::Unlock()
{
	m_bIsLocked = FALSE;
	SetEvent(m_hEvent);
}

BOOL CSyncWait::IsLocked()
{
	return m_bIsLocked;
}
