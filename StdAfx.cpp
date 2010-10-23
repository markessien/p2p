// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>

void Trace(LPCTSTR pStr, ...)
{
	_TCHAR szBuff[3024];

	va_list va;
	va_start(va, pStr);
	wvsprintf (szBuff, pStr, va);
	va_end(va);
	
	_tcscat(szBuff, "\n");

	OutputDebugString(szBuff);
}

string GetFirstWord(string sData)
{
	string::size_type posSta = 0;
	string::size_type posEnd = string::npos;

	if (sData == "")
		return "";

	if (sData.at(0) == '\"')
	{
		// We look for a closing "
		 posEnd = sData.find ("\"", 1);
		 posSta = 1;
	}
	else
	{
		// We look for the next space
		posEnd = sData.find (" ", 0);
	}

	if (posEnd == string::npos)
	{
		// No end was found
		posEnd = sData.size();
	}

	return sData.substr(posSta, posEnd - posSta);
}
