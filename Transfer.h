// Transfer.h : Declaration of the CTransfer

#ifndef __TRANSFER_H_
#define __TRANSFER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "P2PCP.h"
#include "NotifyWindow.h"
#include "globals.h"
#include "SyncWait.h"

using namespace std;

#define WM_NEGCOMPLETE WM_USER + 105
#define WM_TRANSCOMPLETE WM_USER + 106

/////////////////////////////////////////////////////////////////////////////
// CTransfer
class ATL_NO_VTABLE CTransfer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ITransfer, &IID_ITransfer, &LIBID_P2PLib>,
	public CComControl<CTransfer>,
	public IPersistStreamInitImpl<CTransfer>,
	public IOleControlImpl<CTransfer>,
	public IOleObjectImpl<CTransfer>,
	public IOleInPlaceActiveObjectImpl<CTransfer>,
	public IViewObjectExImpl<CTransfer>,
	public IOleInPlaceObjectWindowlessImpl<CTransfer>,
	public IConnectionPointContainerImpl<CTransfer>,
	public IPersistStorageImpl<CTransfer>,
	public ISpecifyPropertyPagesImpl<CTransfer>,
	public IQuickActivateImpl<CTransfer>,
	public IDataObjectImpl<CTransfer>,
	public IProvideClassInfo2Impl<&CLSID_Transfer, &DIID__ITransferEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CTransfer>,
	public CComCoClass<CTransfer, &CLSID_Transfer>,
	public CProxy_ITransferEvents< CTransfer >
{
        DECLARE_CLASSFACTORY2(CLicense)
public:
	CTransfer()
	{
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_NAPSTER_TRANSFER);
		m_trType = type_Unknown;
		
		m_nPort = 0 ;
		m_socket = NULL;
		

		m_nFilesize = 0;
		m_nBytesTransferred = 0;
		m_nOffset = 0;
		m_nRate = 0;

		m_stateSck = socketDisconnected;
		m_stateTrans = trans_ContactingServer;
		m_stateErr = err_NoError;
		m_bReadyToUnload = true;
		m_bAbortRequested = false;
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



DECLARE_REGISTRY_RESOURCEID(IDR_TRANSFER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransfer)
	COM_INTERFACE_ENTRY(ITransfer)
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

BEGIN_PROP_MAP(CTransfer)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CTransfer)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ITransferEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CTransfer)
	CHAIN_MSG_MAP(CComControl<CTransfer>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ITransfer
public:
	STDMETHOD(get_ReadyToUnload)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	
	STDMETHOD(get_TransferState)(/*[out, retval]*/ EnumTransferState *pVal);
	STDMETHOD(UploadFileAlt)(/*[in]*/ BSTR Address, /*[in]*/ long nPort, /*[in]*/ BSTR MyNick, /*[in]*/ BSTR LocalFilename);
	STDMETHOD(get_RemoteFileSize)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_RemoteFileSize)(/*[in]*/ double newVal);
	STDMETHOD(get_LocalTargetFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LocalTargetFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_TransferType)(/*[out, retval]*/ EnumTransferType *pVal);
	STDMETHOD(UploadFile)(/*[in]*/ long hSocket);
	STDMETHOD(get_StatusString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(ResumeTransfer)();
	STDMETHOD(get_Speed)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_ProgressPercent)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_IsRemotelyQueued)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsRemotelyQueued)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_BytesTranferred)(/*[out, retval]*/ double *pVal);
	STDMETHOD(DownloadFile)(/*[in]*/ BSTR Address, /*[in]*/ long nPort, /*[in]*/ BSTR MyNick, /*[in]*/ BSTR RemoteFilename, /*[in]*/ BSTR LocalFilename, /*[in]*/ long FileSize);
	STDMETHOD(CancelTransfer)();

private:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}
	
	static DWORD __stdcall UploadThreadEntry(LPVOID lpvThreadParm);
	static DWORD __stdcall DownloadThreadEntry(LPVOID lpvThreadParm);
	static BOOL  __cdecl   NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);

	HRESULT NegotiateDownload();
	DWORD    ReceiveFile();
	void     ChangeSocketState(EnumSocketState newState);
	void     ChangeTransferState(EnumTransferState newVal);
	void     ShootError(EnumErrorState err);
	void     Disconnect();
	DWORD    NegotiateUpload();
	DWORD    SendFile();
	CComBSTR TranslateError(EnumErrorState err);
	int OpenFileAuto(ofstream * pStream, string sFilepath);

private:
	HICON  m_hIcon;
	string m_sLocalFile;
	string m_sRemoteFile;
	string m_sMyNick;
	string m_sHisNick;
	string m_sAddress;

	long   m_nPort;
	SOCKET m_socket;
	
	string m_sInvalidData;

	double m_nFilesize;
	double m_nBytesTransferred;
	double m_nOffset;
	long   m_nRate;

	EnumTransferType  m_trType;
	EnumSocketState	  m_stateSck;
	EnumTransferState m_stateTrans;
	EnumErrorState    m_stateErr;

//	CSyncWait         m_syncTransfer;
	CNotifyWindow     m_wndNotify;

	bool m_bReadyToUnload;
	bool m_bAbortRequested;
};

#endif //__TRANSFER_H_
