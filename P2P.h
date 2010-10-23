/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 08 17:54:49 2002
 */
/* Compiler settings for X:\Mark$\Code\x86Win32\P2P\P2P.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __P2P_h__
#define __P2P_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INapsterServer_FWD_DEFINED__
#define __INapsterServer_FWD_DEFINED__
typedef interface INapsterServer INapsterServer;
#endif 	/* __INapsterServer_FWD_DEFINED__ */


#ifndef ___INapsterServerEvents_FWD_DEFINED__
#define ___INapsterServerEvents_FWD_DEFINED__
typedef interface _INapsterServerEvents _INapsterServerEvents;
#endif 	/* ___INapsterServerEvents_FWD_DEFINED__ */


#ifndef __IServerManager_FWD_DEFINED__
#define __IServerManager_FWD_DEFINED__
typedef interface IServerManager IServerManager;
#endif 	/* __IServerManager_FWD_DEFINED__ */


#ifndef __NapsterServer_FWD_DEFINED__
#define __NapsterServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class NapsterServer NapsterServer;
#else
typedef struct NapsterServer NapsterServer;
#endif /* __cplusplus */

#endif 	/* __NapsterServer_FWD_DEFINED__ */


#ifndef ___IServerManagerEvents_FWD_DEFINED__
#define ___IServerManagerEvents_FWD_DEFINED__
typedef interface _IServerManagerEvents _IServerManagerEvents;
#endif 	/* ___IServerManagerEvents_FWD_DEFINED__ */


#ifndef __ServerManager_FWD_DEFINED__
#define __ServerManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class ServerManager ServerManager;
#else
typedef struct ServerManager ServerManager;
#endif /* __cplusplus */

#endif 	/* __ServerManager_FWD_DEFINED__ */


#ifndef __ISharedFolderManager_FWD_DEFINED__
#define __ISharedFolderManager_FWD_DEFINED__
typedef interface ISharedFolderManager ISharedFolderManager;
#endif 	/* __ISharedFolderManager_FWD_DEFINED__ */


#ifndef ___ISharedFolderManagerEvents_FWD_DEFINED__
#define ___ISharedFolderManagerEvents_FWD_DEFINED__
typedef interface _ISharedFolderManagerEvents _ISharedFolderManagerEvents;
#endif 	/* ___ISharedFolderManagerEvents_FWD_DEFINED__ */


#ifndef __SharedFolderManager_FWD_DEFINED__
#define __SharedFolderManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class SharedFolderManager SharedFolderManager;
#else
typedef struct SharedFolderManager SharedFolderManager;
#endif /* __cplusplus */

#endif 	/* __SharedFolderManager_FWD_DEFINED__ */


#ifndef __IListener_FWD_DEFINED__
#define __IListener_FWD_DEFINED__
typedef interface IListener IListener;
#endif 	/* __IListener_FWD_DEFINED__ */


#ifndef ___IListenerEvents_FWD_DEFINED__
#define ___IListenerEvents_FWD_DEFINED__
typedef interface _IListenerEvents _IListenerEvents;
#endif 	/* ___IListenerEvents_FWD_DEFINED__ */


#ifndef __ITransfer_FWD_DEFINED__
#define __ITransfer_FWD_DEFINED__
typedef interface ITransfer ITransfer;
#endif 	/* __ITransfer_FWD_DEFINED__ */


#ifndef __Listener_FWD_DEFINED__
#define __Listener_FWD_DEFINED__

#ifdef __cplusplus
typedef class Listener Listener;
#else
typedef struct Listener Listener;
#endif /* __cplusplus */

#endif 	/* __Listener_FWD_DEFINED__ */


#ifndef ___ITransferEvents_FWD_DEFINED__
#define ___ITransferEvents_FWD_DEFINED__
typedef interface _ITransferEvents _ITransferEvents;
#endif 	/* ___ITransferEvents_FWD_DEFINED__ */


#ifndef __Transfer_FWD_DEFINED__
#define __Transfer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Transfer Transfer;
#else
typedef struct Transfer Transfer;
#endif /* __cplusplus */

#endif 	/* __Transfer_FWD_DEFINED__ */


#ifndef __ILogin_FWD_DEFINED__
#define __ILogin_FWD_DEFINED__
typedef interface ILogin ILogin;
#endif 	/* __ILogin_FWD_DEFINED__ */


#ifndef ___ILoginEvents_FWD_DEFINED__
#define ___ILoginEvents_FWD_DEFINED__
typedef interface _ILoginEvents _ILoginEvents;
#endif 	/* ___ILoginEvents_FWD_DEFINED__ */


#ifndef __Login_FWD_DEFINED__
#define __Login_FWD_DEFINED__

#ifdef __cplusplus
typedef class Login Login;
#else
typedef struct Login Login;
#endif /* __cplusplus */

#endif 	/* __Login_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __P2PLib_LIBRARY_DEFINED__
#define __P2PLib_LIBRARY_DEFINED__

/* library P2PLib */
/* [helpstring][version][uuid] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_P2P_0000_0001
    {	socketConnected	= 0,
	socketDisconnected	= socketConnected + 1
    }	EnumSocketState;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_P2P_0000_0002
    {	err_NoError	= 0,
	err_GenericError	= err_NoError + 1,
	err_WSAStartupFailed	= err_GenericError + 1,
	err_WSAStartupNotCalled	= err_WSAStartupFailed + 1,
	err_SocketCreationFailed	= err_WSAStartupNotCalled + 1,
	err_WSAAsyncSelectFailed	= err_SocketCreationFailed + 1,
	err_HostNameCouldNotBeResolved	= err_WSAAsyncSelectFailed + 1,
	err_CouldNotConnect	= err_HostNameCouldNotBeResolved + 1,
	err_ConnectionError	= err_CouldNotConnect + 1,
	err_InvalidDataReceived	= err_ConnectionError + 1,
	err_ConnectionLost	= err_InvalidDataReceived + 1,
	err_CouldNotOpenFile	= err_ConnectionLost + 1,
	err_SocketBindFailed	= err_CouldNotOpenFile + 1,
	err_SocketListenFailed	= err_SocketBindFailed + 1
    }	EnumErrorState;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_P2P_0000_0003
    {	sm_NothingDone	= 0,
	sm_LoadingLocalFiles	= sm_NothingDone + 1,
	sm_stateLoadingRemoteFiles	= sm_LoadingLocalFiles + 1,
	sm_Sorting	= sm_stateLoadingRemoteFiles + 1,
	sm_Ready	= sm_Sorting + 1
    }	ServerManagerState;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_P2P_0000_0004
    {	type_Unknown	= 0,
	type_UploadTransfer	= type_Unknown + 1,
	type_DownloadTransfer	= type_UploadTransfer + 1,
	type_AltUploadTransfer	= type_DownloadTransfer + 1,
	type_AltDownloadTransfer	= type_AltUploadTransfer + 1
    }	EnumTransferType;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_P2P_0000_0005
    {	trans_ContactingServer	= 0,
	trans_Connecting	= trans_ContactingServer + 1,
	trans_Negotiating	= trans_Connecting + 1,
	trans_TransferringByteStream	= trans_Negotiating + 1,
	trans_TransferComplete	= trans_TransferringByteStream + 1,
	trans_RemotelyQueued	= trans_TransferComplete + 1,
	trans_Error	= trans_RemotelyQueued + 1,
	trans_Aborted	= trans_Error + 1
    }	EnumTransferState;


EXTERN_C const IID LIBID_P2PLib;

#ifndef __INapsterServer_INTERFACE_DEFINED__
#define __INapsterServer_INTERFACE_DEFINED__

/* interface INapsterServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INapsterServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE753841-3480-4160-AF11-E387178C888D")
    INapsterServer : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppInitialize( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectToServer( 
            /* [in] */ BSTR bstrAddress,
            /* [in] */ long nPort,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendData( 
            /* [in] */ long nCmd,
            /* [in] */ BSTR strData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppUninitialize( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentData( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCmd( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SocketState( 
            /* [retval][out] */ EnumSocketState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorState( 
            /* [retval][out] */ EnumErrorState __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INapsterServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INapsterServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INapsterServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INapsterServer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppInitialize )( 
            INapsterServer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectToServer )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ BSTR bstrAddress,
            /* [in] */ long nPort,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendData )( 
            INapsterServer __RPC_FAR * This,
            /* [in] */ long nCmd,
            /* [in] */ BSTR strData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            INapsterServer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppUninitialize )( 
            INapsterServer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentData )( 
            INapsterServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCmd )( 
            INapsterServer __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SocketState )( 
            INapsterServer __RPC_FAR * This,
            /* [retval][out] */ EnumSocketState __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorState )( 
            INapsterServer __RPC_FAR * This,
            /* [retval][out] */ EnumErrorState __RPC_FAR *pVal);
        
        END_INTERFACE
    } INapsterServerVtbl;

    interface INapsterServer
    {
        CONST_VTBL struct INapsterServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INapsterServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INapsterServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INapsterServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INapsterServer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INapsterServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INapsterServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INapsterServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INapsterServer_AppInitialize(This,pResult)	\
    (This)->lpVtbl -> AppInitialize(This,pResult)

#define INapsterServer_ConnectToServer(This,bstrAddress,nPort,pResult)	\
    (This)->lpVtbl -> ConnectToServer(This,bstrAddress,nPort,pResult)

#define INapsterServer_SendData(This,nCmd,strData)	\
    (This)->lpVtbl -> SendData(This,nCmd,strData)

#define INapsterServer_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define INapsterServer_AppUninitialize(This)	\
    (This)->lpVtbl -> AppUninitialize(This)

#define INapsterServer_get_CurrentData(This,pVal)	\
    (This)->lpVtbl -> get_CurrentData(This,pVal)

#define INapsterServer_get_CurrentCmd(This,pVal)	\
    (This)->lpVtbl -> get_CurrentCmd(This,pVal)

#define INapsterServer_get_SocketState(This,pVal)	\
    (This)->lpVtbl -> get_SocketState(This,pVal)

#define INapsterServer_get_ErrorState(This,pVal)	\
    (This)->lpVtbl -> get_ErrorState(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INapsterServer_AppInitialize_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB INapsterServer_AppInitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INapsterServer_ConnectToServer_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [in] */ BSTR bstrAddress,
    /* [in] */ long nPort,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB INapsterServer_ConnectToServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INapsterServer_SendData_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [in] */ long nCmd,
    /* [in] */ BSTR strData);


void __RPC_STUB INapsterServer_SendData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INapsterServer_Disconnect_Proxy( 
    INapsterServer __RPC_FAR * This);


void __RPC_STUB INapsterServer_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INapsterServer_AppUninitialize_Proxy( 
    INapsterServer __RPC_FAR * This);


void __RPC_STUB INapsterServer_AppUninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INapsterServer_get_CurrentData_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INapsterServer_get_CurrentData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INapsterServer_get_CurrentCmd_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INapsterServer_get_CurrentCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INapsterServer_get_SocketState_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [retval][out] */ EnumSocketState __RPC_FAR *pVal);


void __RPC_STUB INapsterServer_get_SocketState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INapsterServer_get_ErrorState_Proxy( 
    INapsterServer __RPC_FAR * This,
    /* [retval][out] */ EnumErrorState __RPC_FAR *pVal);


void __RPC_STUB INapsterServer_get_ErrorState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INapsterServer_INTERFACE_DEFINED__ */


#ifndef ___INapsterServerEvents_DISPINTERFACE_DEFINED__
#define ___INapsterServerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INapsterServerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INapsterServerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4577E40B-69C1-457F-A4D8-3C894BA6DEFE")
    _INapsterServerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INapsterServerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INapsterServerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INapsterServerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INapsterServerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INapsterServerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INapsterServerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INapsterServerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INapsterServerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INapsterServerEventsVtbl;

    interface _INapsterServerEvents
    {
        CONST_VTBL struct _INapsterServerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INapsterServerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INapsterServerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INapsterServerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INapsterServerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INapsterServerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INapsterServerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INapsterServerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INapsterServerEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IServerManager_INTERFACE_DEFINED__
#define __IServerManager_INTERFACE_DEFINED__

/* interface IServerManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IServerManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4FEA914-3519-4C5B-B41E-6896F1907C30")
    IServerManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppInitialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppUninitialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadLocalServerList( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadRemoteServerList( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPermanentServer( 
            /* [in] */ BSTR Description,
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextServer( 
            /* [out] */ BSTR __RPC_FAR *Description,
            /* [out] */ BSTR __RPC_FAR *Address,
            /* [out] */ long __RPC_FAR *nPort,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFileSavePath( 
            /* [in] */ BSTR sPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServer( 
            /* [in] */ int Index,
            /* [out] */ BSTR __RPC_FAR *Description,
            /* [out] */ BSTR __RPC_FAR *Address,
            /* [out] */ long __RPC_FAR *nPort,
            /* [out] */ long __RPC_FAR *nUsers,
            /* [out] */ long __RPC_FAR *nGigas,
            /* [out] */ long __RPC_FAR *nFiles,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServerCount( 
            /* [retval][out] */ long __RPC_FAR *plResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadAllServerLists( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SortLists( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ ServerManagerState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveLocalFilesToDisk( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetStatusOfAllServers( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindServer( 
            /* [in] */ BSTR ServerName,
            /* [in] */ VARIANT_BOOL IsPermanent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServerManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IServerManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IServerManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IServerManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppInitialize )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppUninitialize )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadLocalServerList )( 
            IServerManager __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadRemoteServerList )( 
            IServerManager __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPermanentServer )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ BSTR Description,
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextServer )( 
            IServerManager __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *Description,
            /* [out] */ BSTR __RPC_FAR *Address,
            /* [out] */ long __RPC_FAR *nPort,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFileSavePath )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ BSTR sPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServer )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ int Index,
            /* [out] */ BSTR __RPC_FAR *Description,
            /* [out] */ BSTR __RPC_FAR *Address,
            /* [out] */ long __RPC_FAR *nPort,
            /* [out] */ long __RPC_FAR *nUsers,
            /* [out] */ long __RPC_FAR *nGigas,
            /* [out] */ long __RPC_FAR *nFiles,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServerCount )( 
            IServerManager __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadAllServerLists )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SortLists )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IServerManager __RPC_FAR * This,
            /* [retval][out] */ ServerManagerState __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveLocalFilesToDisk )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetStatusOfAllServers )( 
            IServerManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindServer )( 
            IServerManager __RPC_FAR * This,
            /* [in] */ BSTR ServerName,
            /* [in] */ VARIANT_BOOL IsPermanent);
        
        END_INTERFACE
    } IServerManagerVtbl;

    interface IServerManager
    {
        CONST_VTBL struct IServerManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServerManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IServerManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IServerManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IServerManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IServerManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IServerManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IServerManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IServerManager_AppInitialize(This)	\
    (This)->lpVtbl -> AppInitialize(This)

#define IServerManager_AppUninitialize(This)	\
    (This)->lpVtbl -> AppUninitialize(This)

#define IServerManager_LoadLocalServerList(This,pbResult)	\
    (This)->lpVtbl -> LoadLocalServerList(This,pbResult)

#define IServerManager_LoadRemoteServerList(This,pbResult)	\
    (This)->lpVtbl -> LoadRemoteServerList(This,pbResult)

#define IServerManager_AddPermanentServer(This,Description,Address,nPort,pbResult)	\
    (This)->lpVtbl -> AddPermanentServer(This,Description,Address,nPort,pbResult)

#define IServerManager_GetNextServer(This,Description,Address,nPort,bIsPermanent,pResult)	\
    (This)->lpVtbl -> GetNextServer(This,Description,Address,nPort,bIsPermanent,pResult)

#define IServerManager_SetFileSavePath(This,sPath)	\
    (This)->lpVtbl -> SetFileSavePath(This,sPath)

#define IServerManager_GetServer(This,Index,Description,Address,nPort,nUsers,nGigas,nFiles,bIsPermanent,pResult)	\
    (This)->lpVtbl -> GetServer(This,Index,Description,Address,nPort,nUsers,nGigas,nFiles,bIsPermanent,pResult)

#define IServerManager_GetServerCount(This,plResult)	\
    (This)->lpVtbl -> GetServerCount(This,plResult)

#define IServerManager_LoadAllServerLists(This)	\
    (This)->lpVtbl -> LoadAllServerLists(This)

#define IServerManager_SortLists(This)	\
    (This)->lpVtbl -> SortLists(This)

#define IServerManager_get_State(This,pVal)	\
    (This)->lpVtbl -> get_State(This,pVal)

#define IServerManager_SaveLocalFilesToDisk(This)	\
    (This)->lpVtbl -> SaveLocalFilesToDisk(This)

#define IServerManager_ResetStatusOfAllServers(This)	\
    (This)->lpVtbl -> ResetStatusOfAllServers(This)

#define IServerManager_FindServer(This,ServerName,IsPermanent)	\
    (This)->lpVtbl -> FindServer(This,ServerName,IsPermanent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_AppInitialize_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_AppInitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_AppUninitialize_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_AppUninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_LoadLocalServerList_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);


void __RPC_STUB IServerManager_LoadLocalServerList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_LoadRemoteServerList_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);


void __RPC_STUB IServerManager_LoadRemoteServerList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_AddPermanentServer_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [in] */ BSTR Description,
    /* [in] */ BSTR Address,
    /* [in] */ long nPort,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbResult);


void __RPC_STUB IServerManager_AddPermanentServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_GetNextServer_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *Description,
    /* [out] */ BSTR __RPC_FAR *Address,
    /* [out] */ long __RPC_FAR *nPort,
    /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB IServerManager_GetNextServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_SetFileSavePath_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [in] */ BSTR sPath);


void __RPC_STUB IServerManager_SetFileSavePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_GetServer_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [in] */ int Index,
    /* [out] */ BSTR __RPC_FAR *Description,
    /* [out] */ BSTR __RPC_FAR *Address,
    /* [out] */ long __RPC_FAR *nPort,
    /* [out] */ long __RPC_FAR *nUsers,
    /* [out] */ long __RPC_FAR *nGigas,
    /* [out] */ long __RPC_FAR *nFiles,
    /* [out] */ VARIANT_BOOL __RPC_FAR *bIsPermanent,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB IServerManager_GetServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_GetServerCount_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plResult);


void __RPC_STUB IServerManager_GetServerCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_LoadAllServerLists_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_LoadAllServerLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_SortLists_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_SortLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IServerManager_get_State_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [retval][out] */ ServerManagerState __RPC_FAR *pVal);


void __RPC_STUB IServerManager_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_SaveLocalFilesToDisk_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_SaveLocalFilesToDisk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_ResetStatusOfAllServers_Proxy( 
    IServerManager __RPC_FAR * This);


void __RPC_STUB IServerManager_ResetStatusOfAllServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IServerManager_FindServer_Proxy( 
    IServerManager __RPC_FAR * This,
    /* [in] */ BSTR ServerName,
    /* [in] */ VARIANT_BOOL IsPermanent);


void __RPC_STUB IServerManager_FindServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServerManager_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NapsterServer;

#ifdef __cplusplus

class DECLSPEC_UUID("0A85DEF3-41C5-467E-9CB1-8049FEA88571")
NapsterServer;
#endif

#ifndef ___IServerManagerEvents_DISPINTERFACE_DEFINED__
#define ___IServerManagerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IServerManagerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IServerManagerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("02EE1A23-ECBF-43B1-BDA1-E62EE413FA24")
    _IServerManagerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IServerManagerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IServerManagerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IServerManagerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IServerManagerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IServerManagerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IServerManagerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IServerManagerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IServerManagerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IServerManagerEventsVtbl;

    interface _IServerManagerEvents
    {
        CONST_VTBL struct _IServerManagerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IServerManagerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IServerManagerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IServerManagerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IServerManagerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IServerManagerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IServerManagerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IServerManagerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IServerManagerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ServerManager;

#ifdef __cplusplus

class DECLSPEC_UUID("72076840-292C-40AD-B194-EC75DB11981C")
ServerManager;
#endif

#ifndef __ISharedFolderManager_INTERFACE_DEFINED__
#define __ISharedFolderManager_INTERFACE_DEFINED__

/* interface ISharedFolderManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISharedFolderManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E37FD987-8475-43D7-A30F-48520AE5C375")
    ISharedFolderManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSharedFolder( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SharedFolderCount( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SharedFolder( 
            /* [in] */ int Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AsyncWeedDeadFiles( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSharedFileListPath( 
            /* [out] */ BSTR __RPC_FAR *Path,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveFolder( 
            /* [in] */ BSTR Path) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISharedFolderManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISharedFolderManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISharedFolderManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSharedFolder )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SharedFolderCount )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SharedFolder )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ int Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncWeedDeadFiles )( 
            ISharedFolderManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSharedFileListPath )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *Path,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            ISharedFolderManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            ISharedFolderManager __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilePath )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FilePath )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFolder )( 
            ISharedFolderManager __RPC_FAR * This,
            /* [in] */ BSTR Path);
        
        END_INTERFACE
    } ISharedFolderManagerVtbl;

    interface ISharedFolderManager
    {
        CONST_VTBL struct ISharedFolderManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISharedFolderManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISharedFolderManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISharedFolderManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISharedFolderManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISharedFolderManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISharedFolderManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISharedFolderManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISharedFolderManager_AddSharedFolder(This,Path,pVal)	\
    (This)->lpVtbl -> AddSharedFolder(This,Path,pVal)

#define ISharedFolderManager_get_SharedFolderCount(This,pVal)	\
    (This)->lpVtbl -> get_SharedFolderCount(This,pVal)

#define ISharedFolderManager_get_SharedFolder(This,Index,pVal)	\
    (This)->lpVtbl -> get_SharedFolder(This,Index,pVal)

#define ISharedFolderManager_AsyncWeedDeadFiles(This)	\
    (This)->lpVtbl -> AsyncWeedDeadFiles(This)

#define ISharedFolderManager_GetSharedFileListPath(This,Path,pResult)	\
    (This)->lpVtbl -> GetSharedFileListPath(This,Path,pResult)

#define ISharedFolderManager_Load(This)	\
    (This)->lpVtbl -> Load(This)

#define ISharedFolderManager_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define ISharedFolderManager_get_FilePath(This,pVal)	\
    (This)->lpVtbl -> get_FilePath(This,pVal)

#define ISharedFolderManager_put_FilePath(This,newVal)	\
    (This)->lpVtbl -> put_FilePath(This,newVal)

#define ISharedFolderManager_RemoveFolder(This,Path)	\
    (This)->lpVtbl -> RemoveFolder(This,Path)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_AddSharedFolder_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ISharedFolderManager_AddSharedFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_get_SharedFolderCount_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ISharedFolderManager_get_SharedFolderCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_get_SharedFolder_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [in] */ int Index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISharedFolderManager_get_SharedFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_AsyncWeedDeadFiles_Proxy( 
    ISharedFolderManager __RPC_FAR * This);


void __RPC_STUB ISharedFolderManager_AsyncWeedDeadFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_GetSharedFileListPath_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *Path,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB ISharedFolderManager_GetSharedFileListPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_Load_Proxy( 
    ISharedFolderManager __RPC_FAR * This);


void __RPC_STUB ISharedFolderManager_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_Save_Proxy( 
    ISharedFolderManager __RPC_FAR * This);


void __RPC_STUB ISharedFolderManager_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_get_FilePath_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISharedFolderManager_get_FilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_put_FilePath_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISharedFolderManager_put_FilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISharedFolderManager_RemoveFolder_Proxy( 
    ISharedFolderManager __RPC_FAR * This,
    /* [in] */ BSTR Path);


void __RPC_STUB ISharedFolderManager_RemoveFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISharedFolderManager_INTERFACE_DEFINED__ */


#ifndef ___ISharedFolderManagerEvents_DISPINTERFACE_DEFINED__
#define ___ISharedFolderManagerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISharedFolderManagerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISharedFolderManagerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0CF5F273-7A25-4690-AC0F-1F92EA660839")
    _ISharedFolderManagerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISharedFolderManagerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ISharedFolderManagerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ISharedFolderManagerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ISharedFolderManagerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ISharedFolderManagerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ISharedFolderManagerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ISharedFolderManagerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ISharedFolderManagerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ISharedFolderManagerEventsVtbl;

    interface _ISharedFolderManagerEvents
    {
        CONST_VTBL struct _ISharedFolderManagerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISharedFolderManagerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISharedFolderManagerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISharedFolderManagerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISharedFolderManagerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISharedFolderManagerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISharedFolderManagerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISharedFolderManagerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISharedFolderManagerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SharedFolderManager;

#ifdef __cplusplus

class DECLSPEC_UUID("0F532EFF-2D22-4C4C-8CB6-FF9AE2D7BCE2")
SharedFolderManager;
#endif

#ifndef __IListener_INTERFACE_DEFINED__
#define __IListener_INTERFACE_DEFINED__

/* interface IListener */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IListener;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F2E8509A-8804-4608-8721-D0B9879717D7")
    IListener : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Listen( 
            /* [in] */ long nPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopListenAndTerminate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OneRingToBindThemAll( 
            /* [in] */ BSTR Ring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertNumericIP( 
            /* [in] */ double nAddr,
            /* [retval][out] */ BSTR __RPC_FAR *pResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IListenerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IListener __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IListener __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IListener __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IListener __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IListener __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IListener __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IListener __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Listen )( 
            IListener __RPC_FAR * This,
            /* [in] */ long nPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopListenAndTerminate )( 
            IListener __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OneRingToBindThemAll )( 
            IListener __RPC_FAR * This,
            /* [in] */ BSTR Ring);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertNumericIP )( 
            IListener __RPC_FAR * This,
            /* [in] */ double nAddr,
            /* [retval][out] */ BSTR __RPC_FAR *pResult);
        
        END_INTERFACE
    } IListenerVtbl;

    interface IListener
    {
        CONST_VTBL struct IListenerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IListener_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IListener_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IListener_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IListener_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IListener_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IListener_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IListener_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IListener_Listen(This,nPort)	\
    (This)->lpVtbl -> Listen(This,nPort)

#define IListener_StopListenAndTerminate(This)	\
    (This)->lpVtbl -> StopListenAndTerminate(This)

#define IListener_OneRingToBindThemAll(This,Ring)	\
    (This)->lpVtbl -> OneRingToBindThemAll(This,Ring)

#define IListener_ConvertNumericIP(This,nAddr,pResult)	\
    (This)->lpVtbl -> ConvertNumericIP(This,nAddr,pResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IListener_Listen_Proxy( 
    IListener __RPC_FAR * This,
    /* [in] */ long nPort);


void __RPC_STUB IListener_Listen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IListener_StopListenAndTerminate_Proxy( 
    IListener __RPC_FAR * This);


void __RPC_STUB IListener_StopListenAndTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IListener_OneRingToBindThemAll_Proxy( 
    IListener __RPC_FAR * This,
    /* [in] */ BSTR Ring);


void __RPC_STUB IListener_OneRingToBindThemAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IListener_ConvertNumericIP_Proxy( 
    IListener __RPC_FAR * This,
    /* [in] */ double nAddr,
    /* [retval][out] */ BSTR __RPC_FAR *pResult);


void __RPC_STUB IListener_ConvertNumericIP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IListener_INTERFACE_DEFINED__ */


#ifndef ___IListenerEvents_DISPINTERFACE_DEFINED__
#define ___IListenerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IListenerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IListenerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("FD089BEA-F099-49C7-A2CB-669A85EEC98B")
    _IListenerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IListenerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IListenerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IListenerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IListenerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IListenerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IListenerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IListenerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IListenerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IListenerEventsVtbl;

    interface _IListenerEvents
    {
        CONST_VTBL struct _IListenerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IListenerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IListenerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IListenerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IListenerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IListenerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IListenerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IListenerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IListenerEvents_DISPINTERFACE_DEFINED__ */


#ifndef __ITransfer_INTERFACE_DEFINED__
#define __ITransfer_INTERFACE_DEFINED__

/* interface ITransfer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4045426-DEA5-4187-AFCC-83D415AC54F3")
    ITransfer : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelTransfer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DownloadFile( 
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR RemoteFilename,
            /* [in] */ BSTR LocalFilename,
            /* [in] */ long FileSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BytesTranferred( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsRemotelyQueued( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsRemotelyQueued( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressPercent( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Speed( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResumeTransfer( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UploadFile( 
            /* [in] */ long hSocket) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferType( 
            /* [retval][out] */ EnumTransferType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalTargetFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalTargetFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteFileSize( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteFileSize( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UploadFileAlt( 
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR LocalFilename) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferState( 
            /* [retval][out] */ EnumTransferState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadyToUnload( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransfer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransfer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITransfer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelTransfer )( 
            ITransfer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DownloadFile )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR RemoteFilename,
            /* [in] */ BSTR LocalFilename,
            /* [in] */ long FileSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BytesTranferred )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsRemotelyQueued )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsRemotelyQueued )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressPercent )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResumeTransfer )( 
            ITransfer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusString )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UploadFile )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ long hSocket);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransferType )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ EnumTransferType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalTargetFile )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalTargetFile )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteFileSize )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteFileSize )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UploadFileAlt )( 
            ITransfer __RPC_FAR * This,
            /* [in] */ BSTR Address,
            /* [in] */ long nPort,
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR LocalFilename);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransferState )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ EnumTransferState __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadyToUnload )( 
            ITransfer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITransferVtbl;

    interface ITransfer
    {
        CONST_VTBL struct ITransferVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransfer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransfer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransfer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransfer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITransfer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITransfer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITransfer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITransfer_CancelTransfer(This)	\
    (This)->lpVtbl -> CancelTransfer(This)

#define ITransfer_DownloadFile(This,Address,nPort,MyNick,RemoteFilename,LocalFilename,FileSize)	\
    (This)->lpVtbl -> DownloadFile(This,Address,nPort,MyNick,RemoteFilename,LocalFilename,FileSize)

#define ITransfer_get_BytesTranferred(This,pVal)	\
    (This)->lpVtbl -> get_BytesTranferred(This,pVal)

#define ITransfer_get_IsRemotelyQueued(This,pVal)	\
    (This)->lpVtbl -> get_IsRemotelyQueued(This,pVal)

#define ITransfer_put_IsRemotelyQueued(This,newVal)	\
    (This)->lpVtbl -> put_IsRemotelyQueued(This,newVal)

#define ITransfer_get_ProgressPercent(This,pVal)	\
    (This)->lpVtbl -> get_ProgressPercent(This,pVal)

#define ITransfer_get_Speed(This,pVal)	\
    (This)->lpVtbl -> get_Speed(This,pVal)

#define ITransfer_ResumeTransfer(This)	\
    (This)->lpVtbl -> ResumeTransfer(This)

#define ITransfer_get_StatusString(This,pVal)	\
    (This)->lpVtbl -> get_StatusString(This,pVal)

#define ITransfer_UploadFile(This,hSocket)	\
    (This)->lpVtbl -> UploadFile(This,hSocket)

#define ITransfer_get_TransferType(This,pVal)	\
    (This)->lpVtbl -> get_TransferType(This,pVal)

#define ITransfer_get_LocalTargetFile(This,pVal)	\
    (This)->lpVtbl -> get_LocalTargetFile(This,pVal)

#define ITransfer_put_LocalTargetFile(This,newVal)	\
    (This)->lpVtbl -> put_LocalTargetFile(This,newVal)

#define ITransfer_get_RemoteFileSize(This,pVal)	\
    (This)->lpVtbl -> get_RemoteFileSize(This,pVal)

#define ITransfer_put_RemoteFileSize(This,newVal)	\
    (This)->lpVtbl -> put_RemoteFileSize(This,newVal)

#define ITransfer_UploadFileAlt(This,Address,nPort,MyNick,LocalFilename)	\
    (This)->lpVtbl -> UploadFileAlt(This,Address,nPort,MyNick,LocalFilename)

#define ITransfer_get_TransferState(This,pVal)	\
    (This)->lpVtbl -> get_TransferState(This,pVal)

#define ITransfer_get_ReadyToUnload(This,pVal)	\
    (This)->lpVtbl -> get_ReadyToUnload(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransfer_CancelTransfer_Proxy( 
    ITransfer __RPC_FAR * This);


void __RPC_STUB ITransfer_CancelTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransfer_DownloadFile_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ BSTR Address,
    /* [in] */ long nPort,
    /* [in] */ BSTR MyNick,
    /* [in] */ BSTR RemoteFilename,
    /* [in] */ BSTR LocalFilename,
    /* [in] */ long FileSize);


void __RPC_STUB ITransfer_DownloadFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_BytesTranferred_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_BytesTranferred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_IsRemotelyQueued_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_IsRemotelyQueued_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITransfer_put_IsRemotelyQueued_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITransfer_put_IsRemotelyQueued_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_ProgressPercent_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_ProgressPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_Speed_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransfer_ResumeTransfer_Proxy( 
    ITransfer __RPC_FAR * This);


void __RPC_STUB ITransfer_ResumeTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_StatusString_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_StatusString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransfer_UploadFile_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ long hSocket);


void __RPC_STUB ITransfer_UploadFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_TransferType_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ EnumTransferType __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_TransferType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_LocalTargetFile_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_LocalTargetFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITransfer_put_LocalTargetFile_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITransfer_put_LocalTargetFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_RemoteFileSize_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_RemoteFileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITransfer_put_RemoteFileSize_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ITransfer_put_RemoteFileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransfer_UploadFileAlt_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [in] */ BSTR Address,
    /* [in] */ long nPort,
    /* [in] */ BSTR MyNick,
    /* [in] */ BSTR LocalFilename);


void __RPC_STUB ITransfer_UploadFileAlt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_TransferState_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ EnumTransferState __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_TransferState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransfer_get_ReadyToUnload_Proxy( 
    ITransfer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITransfer_get_ReadyToUnload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransfer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Listener;

#ifdef __cplusplus

class DECLSPEC_UUID("DEBCADA9-0AA6-44EE-9D6F-46A96388DDDE")
Listener;
#endif

#ifndef ___ITransferEvents_DISPINTERFACE_DEFINED__
#define ___ITransferEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITransferEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITransferEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("60F360A1-7B1E-4CE7-B5D5-486D9FCAED03")
    _ITransferEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITransferEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ITransferEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ITransferEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ITransferEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ITransferEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ITransferEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ITransferEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ITransferEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ITransferEventsVtbl;

    interface _ITransferEvents
    {
        CONST_VTBL struct _ITransferEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITransferEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITransferEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITransferEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITransferEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITransferEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITransferEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITransferEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITransferEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Transfer;

#ifdef __cplusplus

class DECLSPEC_UUID("F5D5BC22-E2EC-423B-B7EC-D9F6A64BC84A")
Transfer;
#endif

#ifndef __ILogin_INTERFACE_DEFINED__
#define __ILogin_INTERFACE_DEFINED__

/* interface ILogin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILogin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BF90A90-52E1-4C97-BC85-3C00B08EB1FE")
    ILogin : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLoginInfo( 
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR PasswordEncrypted,
            /* [in] */ BSTR EMailAddr,
            /* [in] */ long nPort,
            /* [in] */ long nSpeed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnMessage( 
            /* [in] */ int iCmd,
            /* [in] */ BSTR sData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Login( 
            /* [in] */ BSTR sServerName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginNick( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EncryptString( 
            /* [in] */ BSTR sText,
            /* [retval][out] */ BSTR __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Destroy( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Directory( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Directory( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILoginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILogin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILogin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILogin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILogin __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILogin __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILogin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILogin __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLoginInfo )( 
            ILogin __RPC_FAR * This,
            /* [in] */ BSTR MyNick,
            /* [in] */ BSTR PasswordEncrypted,
            /* [in] */ BSTR EMailAddr,
            /* [in] */ long nPort,
            /* [in] */ long nSpeed);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMessage )( 
            ILogin __RPC_FAR * This,
            /* [in] */ int iCmd,
            /* [in] */ BSTR sData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Login )( 
            ILogin __RPC_FAR * This,
            /* [in] */ BSTR sServerName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginNick )( 
            ILogin __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EncryptString )( 
            ILogin __RPC_FAR * This,
            /* [in] */ BSTR sText,
            /* [retval][out] */ BSTR __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Destroy )( 
            ILogin __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            ILogin __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Directory )( 
            ILogin __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Directory )( 
            ILogin __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILoginVtbl;

    interface ILogin
    {
        CONST_VTBL struct ILoginVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILogin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILogin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILogin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILogin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILogin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILogin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILogin_SetLoginInfo(This,MyNick,PasswordEncrypted,EMailAddr,nPort,nSpeed)	\
    (This)->lpVtbl -> SetLoginInfo(This,MyNick,PasswordEncrypted,EMailAddr,nPort,nSpeed)

#define ILogin_OnMessage(This,iCmd,sData)	\
    (This)->lpVtbl -> OnMessage(This,iCmd,sData)

#define ILogin_Login(This,sServerName)	\
    (This)->lpVtbl -> Login(This,sServerName)

#define ILogin_get_LoginNick(This,pVal)	\
    (This)->lpVtbl -> get_LoginNick(This,pVal)

#define ILogin_EncryptString(This,sText,pResult)	\
    (This)->lpVtbl -> EncryptString(This,sText,pResult)

#define ILogin_Destroy(This)	\
    (This)->lpVtbl -> Destroy(This)

#define ILogin_Init(This)	\
    (This)->lpVtbl -> Init(This)

#define ILogin_get_Directory(This,pVal)	\
    (This)->lpVtbl -> get_Directory(This,pVal)

#define ILogin_put_Directory(This,newVal)	\
    (This)->lpVtbl -> put_Directory(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_SetLoginInfo_Proxy( 
    ILogin __RPC_FAR * This,
    /* [in] */ BSTR MyNick,
    /* [in] */ BSTR PasswordEncrypted,
    /* [in] */ BSTR EMailAddr,
    /* [in] */ long nPort,
    /* [in] */ long nSpeed);


void __RPC_STUB ILogin_SetLoginInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_OnMessage_Proxy( 
    ILogin __RPC_FAR * This,
    /* [in] */ int iCmd,
    /* [in] */ BSTR sData);


void __RPC_STUB ILogin_OnMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_Login_Proxy( 
    ILogin __RPC_FAR * This,
    /* [in] */ BSTR sServerName);


void __RPC_STUB ILogin_Login_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILogin_get_LoginNick_Proxy( 
    ILogin __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILogin_get_LoginNick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_EncryptString_Proxy( 
    ILogin __RPC_FAR * This,
    /* [in] */ BSTR sText,
    /* [retval][out] */ BSTR __RPC_FAR *pResult);


void __RPC_STUB ILogin_EncryptString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_Destroy_Proxy( 
    ILogin __RPC_FAR * This);


void __RPC_STUB ILogin_Destroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILogin_Init_Proxy( 
    ILogin __RPC_FAR * This);


void __RPC_STUB ILogin_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILogin_get_Directory_Proxy( 
    ILogin __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILogin_get_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILogin_put_Directory_Proxy( 
    ILogin __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILogin_put_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILogin_INTERFACE_DEFINED__ */


#ifndef ___ILoginEvents_DISPINTERFACE_DEFINED__
#define ___ILoginEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILoginEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILoginEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C1EB241F-EF0E-42DB-9DD5-1A970744C14D")
    _ILoginEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILoginEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ILoginEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ILoginEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ILoginEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ILoginEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ILoginEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ILoginEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ILoginEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ILoginEventsVtbl;

    interface _ILoginEvents
    {
        CONST_VTBL struct _ILoginEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILoginEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ILoginEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ILoginEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ILoginEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ILoginEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ILoginEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ILoginEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILoginEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Login;

#ifdef __cplusplus

class DECLSPEC_UUID("20142D08-4568-440C-8BE9-63D2F13BF347")
Login;
#endif
#endif /* __P2PLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
