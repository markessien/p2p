
P2Pps.dll: dlldata.obj P2P_p.obj P2P_i.obj
	link /dll /out:P2Pps.dll /def:P2Pps.def /entry:DllMain dlldata.obj P2P_p.obj P2P_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del P2Pps.dll
	@del P2Pps.lib
	@del P2Pps.exp
	@del dlldata.obj
	@del P2P_p.obj
	@del P2P_i.obj
