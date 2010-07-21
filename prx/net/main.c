#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceNet",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(NetInit){
	*rval = I2J(sceNetInit(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),J2I(argv[4])));
	return JS_TRUE;
}
JS_FUN(NetTerm){
	*rval = I2J(sceNetTerm());
	return JS_TRUE;
}
JS_FUN(FreeThreadinfo){
	*rval = I2J(sceNetFreeThreadinfo(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(ThreadAbort){
	*rval = I2J(sceNetThreadAbort(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(EtherStrton){
	return JS_TRUE;
}
JS_FUN(EtherNtostr){
	return JS_TRUE;
}
JS_FUN(GetLocalEtherAddr){
	//unsigned char mac[10];
	//char name[100];
	//sceNetGetLocalEtherAddr(mac);
	//sceNetEtherNtostr(mac,name);
	return JS_TRUE;
}
JS_FUN(GetMallocStat){
	return JS_TRUE;
}
JS_FUN(ApctlInit){
	*rval = I2J(sceNetApctlInit(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(ApctlTerm){
	*rval = I2J(sceNetApctlTerm());
	return JS_TRUE;
}
JS_FUN(ApctlGetInfo){
	return JS_TRUE;
}
JS_FUN(ApctlAddHandler){
	return JS_TRUE;
}
JS_FUN(ApctlDelHandler){
	return JS_TRUE;
}
JS_FUN(ApctlConnect){
	*rval = I2J(sceNetApctlConnect(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(ApctlDisconnect){
	*rval = I2J(sceNetApctlDisconnect());
	return JS_TRUE;
}
JS_FUN(ApctlGetState){
	int pState;
	sceNetApctlGetState(&pState);
	*rval = I2J(pState);
	return JS_TRUE;
}
JS_FUN(InetInit){
	*rval = I2J(sceNetInetInit());
	return JS_TRUE;
}
JS_FUN(InetTerm){
	*rval = I2J(sceNetInetTerm());
	return JS_TRUE;
}
JS_FUN(ResolverInit){
	*rval = I2J(sceNetResolverInit());
	return JS_TRUE;
}
JS_FUN(ResolverDelete){
	*rval = I2J(sceNetResolverDelete(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(ResolverCreate){
	int rid = 0;
	char buf[1024];
  sceNetResolverCreate(&rid, buf, 1024);
	*rval = I2J(rid);
	return JS_TRUE;
}
JS_FUN(ResolverTerm){
	*rval = I2J(sceNetResolverTerm());
	return JS_TRUE;
}
JS_FUN(ResolverStop){
	*rval = I2J(sceNetResolverStop(J2I(argv[0])));
	return JS_TRUE;
}
/*
int 	sceNetResolverStartNtoA (int rid, const char *hostname, struct in_addr *addr, unsigned int timeout, int retry)
int 	sceNetResolverStartAtoN (int rid, const struct in_addr *addr, char *hostname, SceSize hostname_len, unsigned int timeout, int retry)
*/
static JSFunctionSpec functions[] = {
	{"Init",NetInit,4},
	{"Term",NetTerm,0},
	{"FreeThreadinfo",FreeThreadinfo,1},
	{"ThreadAbort",ThreadAbort,1},
	{"EtherStrton",EtherStrton,0},
	{"EtherNtostr",EtherNtostr,0},
	{"GetLocalEtherAddr",GetLocalEtherAddr,0},
	{"GetMallocStat",GetMallocStat,0},
	{"ApctlInit",ApctlInit,2},
	{"ApctlTerm",ApctlTerm,0},
	{"ApctlGetInfo",ApctlGetInfo,2},
	{"ApctlAddHandler",ApctlAddHandler,2},
	{"ApctlDelHandler",ApctlDelHandler,1},
	{"ApctlConnect",ApctlConnect,1},
	{"ApctlDisconnect",ApctlDisconnect,0},
	{"ApctlGetState",ApctlGetState,0},
	{"InetInit",InetInit,0},
	{"InetTerm",InetTerm,0},	
	{0}
};
static JSPropertiesSpec var[] = {
	{"PSPNET_H", I2J(1)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
