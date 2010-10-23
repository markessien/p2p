// SharedFolderManager.h : Declaration of the CSharedFolderManager

#ifndef __SHAREDFOLDERMANAGER_H_
#define __SHAREDFOLDERMANAGER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include <sstream>
#include "P2PCP.h"
#include "MP3Info.h"
#include "ProgressDialog.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSharedFolderManager
class ATL_NO_VTABLE CSharedFolderManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ISharedFolderManager, &IID_ISharedFolderManager, &LIBID_P2PLib>,
	public CComControl<CSharedFolderManager>,
	public IPersistStreamInitImpl<CSharedFolderManager>,
	public IOleControlImpl<CSharedFolderManager>,
	public IOleObjectImpl<CSharedFolderManager>,
	public IOleInPlaceActiveObjectImpl<CSharedFolderManager>,
	public IViewObjectExImpl<CSharedFolderManager>,
	public IOleInPlaceObjectWindowlessImpl<CSharedFolderManager>,
	public IConnectionPointContainerImpl<CSharedFolderManager>,
	public IPersistStorageImpl<CSharedFolderManager>,
	public ISpecifyPropertyPagesImpl<CSharedFolderManager>,
	public IQuickActivateImpl<CSharedFolderManager>,
	public IDataObjectImpl<CSharedFolderManager>,
	public IProvideClassInfo2Impl<&CLSID_SharedFolderManager, &DIID__ISharedFolderManagerEvents, &LIBID_P2PLib>,
	public IPropertyNotifySinkCP<CSharedFolderManager>,
	public CComCoClass<CSharedFolderManager, &CLSID_SharedFolderManager>,
	public CProxy_ISharedFolderManagerEvents< CSharedFolderManager >
{
        DECLARE_CLASSFACTORY2(CLicense)
public:
	CSharedFolderManager()
	{
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_SHAREDFOLDER_MANAGER);
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
DECLARE_REGISTRY_RESOURCEID(IDR_SHAREDFOLDERMANAGER)
DECLARE_NOT_AGGREGATABLE(CSharedFolderManager)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSharedFolderManager)
	COM_INTERFACE_ENTRY(ISharedFolderManager)
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

BEGIN_PROP_MAP(CSharedFolderManager)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CSharedFolderManager)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ISharedFolderManagerEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CSharedFolderManager)
	CHAIN_MSG_MAP(CComControl<CSharedFolderManager>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ISharedFolderManager
public:
	STDMETHOD(RemoveFolder)(/*[in]*/ BSTR Path);
	void ScanFolder(string sPath);
	STDMETHOD(get_FilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(Save)();
	STDMETHOD(Load)();
	STDMETHOD(GetSharedFileListPath)(/*[out]*/ BSTR * Path, /*[out, retval]*/ VARIANT_BOOL * pResult);
	STDMETHOD(AsyncWeedDeadFiles)();
	STDMETHOD(get_SharedFolder)(/*[in]*/ int Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SharedFolderCount)(/*[out, retval]*/ int *pVal);
	STDMETHOD(AddSharedFolder)(/*[in]*/ BSTR Path, VARIANT_BOOL * pResult);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}

private:
	struct tagFolder
	{
		bool bWeeded;
		bool bScanned;
		string sPath;
	};
	
	HICON m_hIcon;
	list<tagFolder> m_listFolders;
	string m_sPath;
	CMP3Info m_mp3Info;
	CProgressDialog m_dlgProgress;
};	

#endif //__SHAREDFOLDERMANAGER_H_
