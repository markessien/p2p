// NapsterServer.h : Declaration of the CNapsterServer

#ifndef __NAPSTERSERVER_H_
#define __NAPSTERSERVER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "P2PCP.h"

/////////////////////////////////////////////////////////////////////////////
// CNapsterServer
class ATL_NO_VTABLE CNapsterServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<INapsterServer, &IID_INapsterServer, &LIBID_P2PLib>,
	public CComControl<CNapsterServer>,
	public IPersistStreamInitImpl<CNapsterServer>,
	public IOleControlImpl<CNapsterServer>,
	public IOleObjectImpl<CNapsterServer>,
	public IOleInPlaceActiveObjectImpl<CNapsterServer>,
	public IViewObjectExImpl<CNapsterServer>,
	public IOleInPlaceObjectWindowlessImpl<CNapsterServer>,
	public IConnectionPointContainerImpl<CNapsterServer>,
	public IPersistStorageImpl<CNapsterServer>,
	public ISpecifyPropertyPagesImpl<CNapsterServer>,
	public IQuickActivateImpl<CNapsterServer>,
	public IDataObjectImpl<CNapsterServer>,
	public IProvideClassInfo2Impl<&CLSID_NapsterServer, &DIID__INapsterServerEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CNapsterServer>,
	public CComCoClass<CNapsterServer, &CLSID_NapsterServer>,
	public CProxy_INapsterServerEvents< CNapsterServer >
{
public:
	CNapsterServer()
	{
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_NAPSTER_SERVER);
		m_sckState = socketDisconnected;
		m_nCmd = 0;
		m_socket = NULL;
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

		m_bAutoSize = TRUE;

		return S_OK;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_NAPSTERSERVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNapsterServer)
	COM_INTERFACE_ENTRY(INapsterServer)
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

BEGIN_PROP_MAP(CNapsterServer)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CNapsterServer)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__INapsterServerEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CNapsterServer)
	CHAIN_MSG_MAP(CComControl<CNapsterServer>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	// INapster
public:
	
	STDMETHOD(get_ErrorState)(/*[out, retval]*/  EnumErrorState  *pVal);
	STDMETHOD(get_SocketState)(/*[out, retval]*/ EnumSocketState *pVal);
	STDMETHOD(get_CurrentCmd)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_CurrentData)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(AppUninitialize)();
	STDMETHOD(Disconnect)();
	STDMETHOD(SendData)(/*[in]*/ long nCmd, /*[in]*/ BSTR strData);
	STDMETHOD(ConnectToServer)(/*[in]*/ BSTR bstrAddress, /*[in]*/ long nPort, /*[out, retval]*/ VARIANT_BOOL *pResult);
	STDMETHOD(AppInitialize)(VARIANT_BOOL *pResult);
	
private:
	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);
	void   RetrieveData();
	void   DoEvents();
	void   ShootError(EnumErrorState err);
	void   ChangeSocketState(EnumSocketState newState);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}

private:
	short           m_nCmd;
	CComBSTR        m_bstrData;
	SOCKET			m_socket;
	CNotifyWindow   m_wndNotify;
	HICON			m_hIcon;
	EnumSocketState m_sckState;
	EnumErrorState  m_errState;
	CRITICAL_SECTION m_critObj;
};

#endif //__NAPSTERSERVER_H_
