// P2P.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f P2Pps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "P2P.h"

#include "P2P_i.c"
#include "NotifyWindow.h"
#include "NapsterServer.h"
#include "ServerManager.h"
#include "SharedFolderManager.h"
#include "Listener.h"
#include "Transfer.h"
#include "Login.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_NapsterServer, CNapsterServer)
OBJECT_ENTRY(CLSID_ServerManager, CServerManager)
OBJECT_ENTRY(CLSID_SharedFolderManager, CSharedFolderManager)
OBJECT_ENTRY(CLSID_Listener, CListener)
OBJECT_ENTRY(CLSID_Transfer, CTransfer)
OBJECT_ENTRY(CLSID_Login, CLogin)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_P2PLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


