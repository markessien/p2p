// ServerManager.h : Declaration of the CServerManager

#ifndef __SERVERMANAGER_H_
#define __SERVERMANAGER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "P2PCP.h"
#include "SyncWait.h"

using namespace std;

#define WM_SERVER_ADDED WM_USER+3
#define WM_SERVER_UPDATED WM_USER+4
#define WM_PERMSERVERS_LOADED WM_USER+5
#define WM_REMOTEFILES_LOADED WM_USER+6
#define WM_REMOTEFILESCACHE_LOADED WM_USER+7

/////////////////////////////////////////////////////////////////////////////
// CServerManager
class ATL_NO_VTABLE CServerManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IServerManager, &IID_IServerManager, &LIBID_P2PLib>,
	public CComControl<CServerManager>,
	public IPersistStreamInitImpl<CServerManager>,
	public IOleControlImpl<CServerManager>,
	public IOleObjectImpl<CServerManager>,
	public IOleInPlaceActiveObjectImpl<CServerManager>,
	public IViewObjectExImpl<CServerManager>,
	public IOleInPlaceObjectWindowlessImpl<CServerManager>,
	public IConnectionPointContainerImpl<CServerManager>,
	public IPersistStorageImpl<CServerManager>,
	public ISpecifyPropertyPagesImpl<CServerManager>,
	public IQuickActivateImpl<CServerManager>,
	public IDataObjectImpl<CServerManager>,
	public IProvideClassInfo2Impl<&CLSID_ServerManager, &DIID__IServerManagerEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CServerManager>,
	public CComCoClass<CServerManager, &CLSID_ServerManager>,
	public CProxy_IServerManagerEvents< CServerManager >
{
    DECLARE_CLASSFACTORY2(CLicense)
public:
	struct ServerInfo
	{
		std::string sAddr;
		std::string sDesc;
		std::string sNetw;
		long   nUsers;
		long   nFiles;
		long   nGigs;
		long   nPort;
		bool   bTried;

		operator < (ServerInfo& srv2) { if (srv2.nFiles > srv2.nFiles) 
											return TRUE;
										else
											return FALSE; }
	};
	
	CServerManager()
	{
		m_sPath = "c:\\";
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_SERVER_MANAGER);
		m_bCancelThreads = FALSE;
	}

	HRESULT FinalConstruct( )
	{
		SIZEL size = {32, 32};
		AtlPixelToHiMetric( &size, &m_sizeExtent );
		m_sizeNatural = m_sizeExtent;

		SIZEL szlPixels, szlMetric;
		szlPixels.cx = 32;
		szlPixels.cy = 32;

		AtlPixelToHiMetric(&szlPixels, &szlMetric);

		// IOleObjectImpl
		SetExtent(DVASPECT_CONTENT, &szlMetric);

		// update control sizing...
		m_rcPos.right= m_rcPos.left + 32;
		m_rcPos.bottom= m_rcPos.top + 32;
		
		if (m_spInPlaceSite != NULL) 
		{
		  // needed for IE to accept the resizing
		  m_spInPlaceSite->OnPosRectChange(&m_rcPos);
		}
		//SetFocus();

		m_bAutoSize = TRUE;

		return S_OK;
	}

public:
DECLARE_REGISTRY_RESOURCEID(IDR_SERVERMANAGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServerManager)
	COM_INTERFACE_ENTRY(IServerManager)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CServerManager)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CServerManager)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IServerManagerEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CServerManager)
	CHAIN_MSG_MAP(CComControl<CServerManager>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IServerManager
public:
	STDMETHOD(FindServer)(/*[jn]*/ BSTR ServerName, /*[in]*/ VARIANT_BOOL IsPermanent);
	STDMETHOD(ResetStatusOfAllServers)();
	STDMETHOD(SaveLocalFilesToDisk)();
	STDMETHOD(get_State)(/*[out, retval]*/ ServerManagerState *pVal);
	STDMETHOD(SortLists)();
	STDMETHOD(LoadAllServerLists)();
	STDMETHOD(GetServerCount)(/*[out, retval]*/ long * plResult);
	STDMETHOD(GetServer)(/*[in]*/ int Index, /*[out]*/ BSTR * Description, /*[out]*/ BSTR * Address, /*[out]*/ long * nPort, long * nUsers, long * nGigas, long * nFiles,/*[out]*/ VARIANT_BOOL * bIsPermanent, /*[out, retval]*/ VARIANT_BOOL * pResult);
	STDMETHOD(SetFileSavePath)(/*[in]*/ BSTR sPath);
	STDMETHOD(GetNextServer)(BSTR * Description, BSTR * Address,  long * nPort, VARIANT_BOOL * bIsPermanent, VARIANT_BOOL * pResult);
	STDMETHOD(AddPermanentServer)(/*[in]*/ BSTR Description, /*[in]*/ BSTR Address, /*[in]*/ long nPort, /*[out, retval]*/ VARIANT_BOOL * pbResult);
	STDMETHOD(LoadRemoteServerList)(/*[out, retval]*/ VARIANT_BOOL * pbResult);
	STDMETHOD(LoadLocalServerList)(/*[out, retval]*/ VARIANT_BOOL * pbResult);
	STDMETHOD(AppUninitialize)();
	STDMETHOD(AppInitialize)();

private:

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}
		
	void SerializeServerList();
	BOOL UpdateServerInList(ServerInfo srv, BOOL bPermanent);
	BOOL LoadServerList(const TCHAR* pszFile, BOOL bPermanent, BOOL bCheckIfInList = FALSE);
	void ParseAndAddServerLine(TCHAR* pszLine, BOOL bPermanent, BOOL bCheckIfInList);
	static DWORD __stdcall LoadLocalServerListThread(LPVOID lpvThreadParm);
	static DWORD __stdcall LoadRemoteServerListThread(LPVOID lpvThreadParm);
	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);

private:
	HICON m_hIcon;
	list<ServerInfo> m_permanentList;
	list<ServerInfo> m_recycledList;
	std::string      m_sPath;
	CNotifyWindow    m_wndNotify;
	CRITICAL_SECTION m_critObj;
	CSyncWait        m_syncRemoteServer;
	CSyncWait        m_syncLocalServer;
	BOOL             m_bCancelThreads;
};

#endif //__SERVERMANAGER_H_
