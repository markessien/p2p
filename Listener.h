// Listener.h : Declaration of the CListener

#ifndef __LISTENER_H_
#define __LISTENER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "NotifyWindow.h"
#include "P2PCP.h"
#include "SyncWait.h"

#define WM_NEWCONN WM_USER + 101


/////////////////////////////////////////////////////////////////////////////
// CListener
class ATL_NO_VTABLE CListener : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IListener, &IID_IListener, &LIBID_P2PLib>,
	public CComControl<CListener>,
	public IPersistStreamInitImpl<CListener>,
	public IOleControlImpl<CListener>,
	public IOleObjectImpl<CListener>,
	public IOleInPlaceActiveObjectImpl<CListener>,
	public IViewObjectExImpl<CListener>,
	public IOleInPlaceObjectWindowlessImpl<CListener>,
	public IConnectionPointContainerImpl<CListener>,
	public IPersistStorageImpl<CListener>,
	public ISpecifyPropertyPagesImpl<CListener>,
	public IQuickActivateImpl<CListener>,
	public IDataObjectImpl<CListener>,
	public IProvideClassInfo2Impl<&CLSID_Listener, &DIID__IListenerEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CListener>,
	public CComCoClass<CListener, &CLSID_Listener>,
	public CProxy_IListenerEvents< CListener >
{
        DECLARE_CLASSFACTORY2(CLicense)
public:
	CListener()
	{
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_LISTENER);
		m_listenSocket = 0;
		m_nListenPort = 0;
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

DECLARE_REGISTRY_RESOURCEID(IDR_LISTENER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CListener)
	COM_INTERFACE_ENTRY(IListener)
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

BEGIN_PROP_MAP(CListener)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CListener)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IListenerEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CListener)
	CHAIN_MSG_MAP(CComControl<CListener>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IListener
public:
	STDMETHOD(ConvertNumericIP)(/*[in]*/ double nAddr, /*[out, retval]*/ BSTR * pResult);
	STDMETHOD(OneRingToBindThemAll)(/*[in]*/ BSTR Ring);
	
	STDMETHOD(StopListenAndTerminate)();
	STDMETHOD(Listen)(/*[in]*/ long nPort);

private:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);

		return S_OK;
	}

private:
	static  DWORD __stdcall ListenThreadEntry(LPVOID lpvThreadParm);
	BOOL  IsRemoteConnectionAvailable(SOCKET s, int timeout);
	DWORD Listen();
	void  ShootError(EnumErrorState error);
	static BOOL  NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);

private:
	HICON  m_hIcon;
	SOCKET m_listenSocket;
	long   m_nListenPort;
	CNotifyWindow m_wndNotify;
	CSyncWait m_syncListen;
};

#endif //__LISTENER_H_
