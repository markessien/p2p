# Microsoft Developer Studio Project File - Name="P2P" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=P2P - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "P2P.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "P2P.mak" CFG="P2P - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "P2P - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "P2P - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "P2P - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wininet.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\P2P.dll
InputPath=.\Debug\P2P.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "P2P - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 wininet.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\P2P.dll
InputPath=.\ReleaseMinDependency\P2P.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "P2P - Win32 Debug"
# Name "P2P - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\Listener.cpp
# End Source File
# Begin Source File

SOURCE=.\Login.cpp
# End Source File
# Begin Source File

SOURCE=.\MP3Info.cpp
# End Source File
# Begin Source File

SOURCE=.\NapsterServer.cpp
# End Source File
# Begin Source File

SOURCE=.\P2P.cpp
# End Source File
# Begin Source File

SOURCE=.\P2P.def
# End Source File
# Begin Source File

SOURCE=.\P2P.idl
# ADD MTL /tlb ".\P2P.tlb" /h "P2P.h" /iid "P2P_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\P2P.rc
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Rijndael.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SharedFolderManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SyncWait.cpp
# End Source File
# Begin Source File

SOURCE=.\Transfer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\License.h
# End Source File
# Begin Source File

SOURCE=.\Listener.h
# End Source File
# Begin Source File

SOURCE=.\Login.h
# End Source File
# Begin Source File

SOURCE=.\MP3Info.h
# End Source File
# Begin Source File

SOURCE=.\NapsterServer.h
# End Source File
# Begin Source File

SOURCE=.\NotifyWindow.h
# End Source File
# Begin Source File

SOURCE=.\P2PCP.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Rijndael.h
# End Source File
# Begin Source File

SOURCE=.\ServerManager.h
# End Source File
# Begin Source File

SOURCE=.\SharedFolderManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SyncWait.h
# End Source File
# Begin Source File

SOURCE=.\ThreadSwitch.h
# End Source File
# Begin Source File

SOURCE=.\Transfer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\app_icon.ico
# End Source File
# Begin Source File

SOURCE=.\res\download.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\links.ico
# End Source File
# Begin Source File

SOURCE=.\Listener.rgs
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.ico
# End Source File
# Begin Source File

SOURCE=.\Login.rgs
# End Source File
# Begin Source File

SOURCE=.\NapsterDownload.rgs
# End Source File
# Begin Source File

SOURCE=.\NapsterServer.rgs
# End Source File
# Begin Source File

SOURCE=.\NapsterUpload.rgs
# End Source File
# Begin Source File

SOURCE=.\res\register.bmp
# End Source File
# Begin Source File

SOURCE=.\RegisterUser.rgs
# End Source File
# Begin Source File

SOURCE=.\res\search.ico
# End Source File
# Begin Source File

SOURCE=.\res\server.ico
# End Source File
# Begin Source File

SOURCE=.\res\server_manager.ico
# End Source File
# Begin Source File

SOURCE=.\ServerManager.rgs
# End Source File
# Begin Source File

SOURCE=.\SharedFolderManager.rgs
# End Source File
# Begin Source File

SOURCE=.\res\socket_icon.ico
# End Source File
# Begin Source File

SOURCE=.\res\SvrWorld.ico
# End Source File
# Begin Source File

SOURCE=.\res\thing.ico
# End Source File
# Begin Source File

SOURCE=.\res\transfer.bmp
# End Source File
# Begin Source File

SOURCE=.\Transfer.rgs
# End Source File
# End Group
# End Target
# End Project
# Section P2P : {00000000-0000-0000-0000-800000800000}
# 	1:18:IDD_PROGRESSDIALOG:109
# End Section
