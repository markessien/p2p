// Login.h : Declaration of the CLogin

#ifndef __LOGIN_H_
#define __LOGIN_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "P2PCP.h"
#include "Rijndael.h"


/////////////////////////////////////////////////////////////////////////////
// CLogin
class ATL_NO_VTABLE CLogin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILogin, &IID_ILogin, &LIBID_P2PLib>,
	public CComControl<CLogin>,
	public IPersistStreamInitImpl<CLogin>,
	public IOleControlImpl<CLogin>,
	public IOleObjectImpl<CLogin>,
	public IOleInPlaceActiveObjectImpl<CLogin>,
	public IViewObjectExImpl<CLogin>,
	public IOleInPlaceObjectWindowlessImpl<CLogin>,
	public IConnectionPointContainerImpl<CLogin>,
	public IPersistStorageImpl<CLogin>,
	public ISpecifyPropertyPagesImpl<CLogin>,
	public IQuickActivateImpl<CLogin>,
	public IDataObjectImpl<CLogin>,
	public IProvideClassInfo2Impl<&CLSID_Login, &DIID__ILoginEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CLogin>,
	public CComCoClass<CLogin, &CLSID_Login>,
	public CProxy_ILoginEvents< CLogin >
{
        DECLARE_CLASSFACTORY2(CLicense)
public:
	CLogin()
	{
		m_bLoggingIn = false;
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_LOGIN);

		char* psz =      "dafioewkfnewn8238123i4nj21hsdjcnmcjxyb83q844nigbjfgmklaopjnji dfj"
			             "dsfd cmr89238r32iawddasuh9qwe7zdnasiv ckönöupkuzßpasas873igfdivcvm"
						 "fieifnc,yx,xy<my<mxy<ueu388060asdhasgztyxcxyögpüjzjö,lpdpodopeiowu"
						 ".nmljöpi9025asxxyx yxyhnfdjiogfiohi589t845r,v.v.-vccv,.x-c,övidjos"
						 "x,mxmnmcxmvbu27739ouzpukzlk.m,. m,.mlnmlkhaxdawqewewqw56e5ezhc xcm";
		
		int nLen = strlen(psz);
		memcpy(m_szDing, psz, nLen > 1023 ? 1023 : nLen);
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
DECLARE_REGISTRY_RESOURCEID(IDR_LOGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLogin)
	COM_INTERFACE_ENTRY(ILogin)
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

BEGIN_PROP_MAP(CLogin)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CLogin)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ILoginEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CLogin)
	CHAIN_MSG_MAP(CComControl<CLogin>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ILogin
public:
	STDMETHOD(get_Directory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Directory)(/*[in]*/ BSTR newVal);
	STDMETHOD(Init)();
	STDMETHOD(Destroy)();
	
	STDMETHOD(EncryptString)(/*[in]*/ BSTR sText, /*[out, retval]*/ BSTR * pResult);
	STDMETHOD(get_LoginNick)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(Login)(BSTR sServerName);
	STDMETHOD(OnMessage)(/*[in]*/ int iCmd, /*[in]*/ BSTR sData);
	STDMETHOD(SetLoginInfo)(/*[in]*/ BSTR MyNick, /*[in]*/ BSTR PasswordEncrypted, BSTR EMailAddr, /*[in]*/ long  nPort,  /*[in]*/ long nSpeed);

private:
	
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}
	
	void AddMap(string sServer, string sLogin);
	BOOL Load();
	BOOL Save();

	struct LoginMap
	{
		string sServerName;
		string sLoginName;
	};

	list<LoginMap> m_loginMapList;

	HICON	m_hIcon;
	string  m_sNick;
	string  m_sEMail;
	string  m_sPassword;
	string  m_sPort;
	string  m_sSpeed;
	string  m_sPath;
	string  m_sServer;
	static  char m_szDing[1024];
	bool    m_bLoggingIn;
};

#endif //__LOGIN_H_
