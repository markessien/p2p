/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 08 17:54:49 2002
 */
/* Compiler settings for X:\Mark$\Code\x86Win32\P2P\P2P.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_P2PLib = {0x38E1207E,0xA822,0x4AB2,{0x90,0x00,0x3D,0xB6,0x4E,0xD7,0x71,0xBB}};


const IID IID_INapsterServer = {0xCE753841,0x3480,0x4160,{0xAF,0x11,0xE3,0x87,0x17,0x8C,0x88,0x8D}};


const IID DIID__INapsterServerEvents = {0x4577E40B,0x69C1,0x457F,{0xA4,0xD8,0x3C,0x89,0x4B,0xA6,0xDE,0xFE}};


const IID IID_IServerManager = {0xC4FEA914,0x3519,0x4C5B,{0xB4,0x1E,0x68,0x96,0xF1,0x90,0x7C,0x30}};


const CLSID CLSID_NapsterServer = {0x0A85DEF3,0x41C5,0x467E,{0x9C,0xB1,0x80,0x49,0xFE,0xA8,0x85,0x71}};


const IID DIID__IServerManagerEvents = {0x02EE1A23,0xECBF,0x43B1,{0xBD,0xA1,0xE6,0x2E,0xE4,0x13,0xFA,0x24}};


const CLSID CLSID_ServerManager = {0x72076840,0x292C,0x40AD,{0xB1,0x94,0xEC,0x75,0xDB,0x11,0x98,0x1C}};


const IID IID_ISharedFolderManager = {0xE37FD987,0x8475,0x43D7,{0xA3,0x0F,0x48,0x52,0x0A,0xE5,0xC3,0x75}};


const IID DIID__ISharedFolderManagerEvents = {0x0CF5F273,0x7A25,0x4690,{0xAC,0x0F,0x1F,0x92,0xEA,0x66,0x08,0x39}};


const CLSID CLSID_SharedFolderManager = {0x0F532EFF,0x2D22,0x4C4C,{0x8C,0xB6,0xFF,0x9A,0xE2,0xD7,0xBC,0xE2}};


const IID IID_IListener = {0xF2E8509A,0x8804,0x4608,{0x87,0x21,0xD0,0xB9,0x87,0x97,0x17,0xD7}};


const IID DIID__IListenerEvents = {0xFD089BEA,0xF099,0x49C7,{0xA2,0xCB,0x66,0x9A,0x85,0xEE,0xC9,0x8B}};


const IID IID_ITransfer = {0xC4045426,0xDEA5,0x4187,{0xAF,0xCC,0x83,0xD4,0x15,0xAC,0x54,0xF3}};


const CLSID CLSID_Listener = {0xDEBCADA9,0x0AA6,0x44EE,{0x9D,0x6F,0x46,0xA9,0x63,0x88,0xDD,0xDE}};


const IID DIID__ITransferEvents = {0x60F360A1,0x7B1E,0x4CE7,{0xB5,0xD5,0x48,0x6D,0x9F,0xCA,0xED,0x03}};


const CLSID CLSID_Transfer = {0xF5D5BC22,0xE2EC,0x423B,{0xB7,0xEC,0xD9,0xF6,0xA6,0x4B,0xC8,0x4A}};


const IID IID_ILogin = {0x3BF90A90,0x52E1,0x4C97,{0xBC,0x85,0x3C,0x00,0xB0,0x8E,0xB1,0xFE}};


const IID DIID__ILoginEvents = {0xC1EB241F,0xEF0E,0x42DB,{0x9D,0xD5,0x1A,0x97,0x07,0x44,0xC1,0x4D}};


const CLSID CLSID_Login = {0x20142D08,0x4568,0x440C,{0x8B,0xE9,0x63,0xD2,0xF1,0x3B,0xF3,0x47}};


#ifdef __cplusplus
}
#endif

