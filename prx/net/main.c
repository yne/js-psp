#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocmatching.h>
#include <pspnet_adhocctl.h>

#include <arpa/inet.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceNet",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

u32 net_uid = 0; /* Net */
u32 ifhandle_uid = 0;//sceNetInterface_Service : avoid sceNetInit 0x8002013A error
u32 inet_uid = 0;
JS_FUN(NetInit){
	ifhandle_uid = c_addModule("flash0:/kd/ifhandle.prx");
	net_uid = c_addModule("flash0:/kd/pspnet.prx");
	*rval = I2J(sceNetInit(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),J2I(argv[4])));
	return JS_TRUE;
}
JS_FUN(NetTerm){
	*rval = I2J(sceNetTerm());
	c_delModule(inet_uid);
	c_delModule(net_uid);
	c_delModule(ifhandle_uid);
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
 /* apctl */
u32 apctl_uid = 0;
JS_FUN(ApctlInit){
	apctl_uid = c_addModule("flash0:/kd/pspnet_apctl.prx");
	*rval = I2J(sceNetApctlInit(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(ApctlTerm){
	*rval = I2J(sceNetApctlTerm());
	c_delModule(apctl_uid);
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
/* Inet */
JS_FUN(InetInit){
	inet_uid = c_addModule("flash0:/kd/pspnet_inet.prx");
	*rval = I2J(sceNetInetInit());
	return JS_TRUE;
}
JS_FUN(InetTerm){
	*rval = I2J(sceNetInetTerm());
	return JS_TRUE;
}
/* Resolver */
u32 resolver_uid = 0;
char resolv_buf[1024];
JS_FUN(ResolverInit){
	resolver_uid = c_addModule("flash0:/kd/pspnet_resolver.prx");
	*rval = I2J(sceNetResolverInit());
	return JS_TRUE;
}
JS_FUN(ResolverCreate){
	int rid = -1;
	sceNetResolverCreate(&rid, resolv_buf, 1024);
	*rval = I2J(rid);
	return JS_TRUE;
}
JS_FUN(ResolverStartNtoA){
	int rid = J2I(argv[0]);
	struct in_addr addr;
	void* ip = js_malloc(16);
	char* RESOLVE_NAME = J2S(argv[1]);
	if(sceNetResolverStartNtoA(rid, RESOLVE_NAME, &addr, 2, 3) < 0)
		return JS_TRUE;
	char* tmp = (char*)&(addr.s_addr);
	sprintf(ip,"%u.%u.%u.%u",(unsigned char)tmp[0],(unsigned char)tmp[1],(unsigned char)tmp[2],(unsigned char)tmp[3]);
	*rval = STRING_TO_JSVAL(js_newString(ip,0));
	return JS_TRUE;
}
JS_FUN(ResolverStartAtoN){//FIXME
	struct in_addr addr;
	addr.s_addr =	sceNetInetInetAddr(J2S(argv[1]));
	//char* tmp = (char*)&(addr.s_addr);
	//printf("%u.%u.%u.%u",(unsigned char)tmp[0],(unsigned char)tmp[1],(unsigned char)tmp[2],(unsigned char)tmp[3]);
	char name[1024];
	sceNetResolverStartAtoN(J2I(argv[0]),&addr,name,1024,30,5);
	void* temp = js_malloc(1024);
	strcpy(temp,name);
	*rval = STRING_TO_JSVAL(js_newString(temp,0));
	return JS_TRUE;
}
JS_FUN(ResolverStop){
	*rval = I2J(sceNetResolverStop(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(ResolverDelete){
	*rval = I2J(sceNetResolverDelete(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(ResolverTerm){
	*rval = I2J(sceNetResolverTerm());
	c_delModule(resolver_uid);
	return JS_TRUE;
}
u32 adhoc_uid = 0;
JS_FUN(AdhocInit){/* Adhoc */
	adhoc_uid = c_addModule("pspnet_adhoc.prx");
	*rval = I2J(sceNetAdhocInit());
	return JS_TRUE;
}
JS_FUN(AdhocPdpCreate){
	*rval = I2J(sceNetAdhocPdpCreate((void*)J2S(argv[0]),J2U(argv[1]),J2U(argv[2]),J2U(argv[3])));
	/* arg 3 = flag : 
	NONBLOCK		0x0001
	ALERTSEND		0x0010
	ALERTRECV		0x0020
	ALERTPOLL		0x0040
	ALERTCONNECT	0x0080
	ALERTACCEPT	0x0100
	ALERTFLUSH	0x0200
	*/
	return JS_TRUE;
}
JS_FUN(AdhocPdpDelete){
	*rval = I2J(sceNetAdhocPdpDelete(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(AdhocTerm){
	*rval = I2J(sceNetAdhocTerm());
	c_delModule(adhoc_uid);
	return JS_TRUE;
}
/*
int sceNetAdhocGameModeCreateMaster (void *data, int size)
int sceNetAdhocGameModeCreateReplica(unsigned char *mac, void *data, int size)
int sceNetAdhocGameModeUpdateMaster (void)
int sceNetAdhocGameModeUpdateReplica(int id, int unk1)
int sceNetAdhocGameModeDeleteMaster (void)
int sceNetAdhocGameModeDeleteReplica(int id)
int sceNetAdhocPdpSend              (int id, unsigned char *destMacAddr, unsigned short port, void *data, unsigned int len, unsigned int timeout, int nonblock)
int sceNetAdhocPdpRecv              (int id, unsigned char *srcMacAddr, unsigned short *port, void *data, void *dataLength, unsigned int timeout, int nonblock)
int sceNetAdhocGetPdpStat           (int *size, pdpStatStruct *stat)
int sceNetAdhocPtpOpen              (unsigned char *srcmac, unsigned short srcport, unsigned char *destmac, unsigned short destport, unsigned int bufsize, unsigned int delay, int count, int unk1)
int sceNetAdhocPtpConnect           (int id, unsigned int timeout, int nonblock)
int sceNetAdhocPtpListen            (unsigned char *srcmac, unsigned short srcport, unsigned int bufsize, unsigned int delay, int count, int queue, int unk1)
int sceNetAdhocPtpAccept            (int id, unsigned char *mac, unsigned short *port, unsigned int timeout, int nonblock)
int sceNetAdhocPtpSend              (int id, void *data, int *datasize, unsigned int timeout, int nonblock)
int sceNetAdhocPtpRecv              (int id, void *data, int *datasize, unsigned int timeout, int nonblock)
int sceNetAdhocPtpFlush             (int id, unsigned int timeout, int nonblock)
int sceNetAdhocPtpClose             (int id, int unk1)
int sceNetAdhocGetPtpStat           (int *size, ptpStatStruct *stat)
*/
u32 adhocctl_uid = 0;
JS_FUN(AdhocctlInit){ /* Adhocctl */
	adhocctl_uid = c_addModule("pspnet_adhocctl.prx");
	JSObject*Product = J2O(argv[2]);
	struct productStruct product;
	memcpy(product.product,J2S(js_getProperty(Product,"product")),9);
	product.unknown = J2I(js_getProperty(Product,"type"));
	*rval = I2J(sceNetAdhocctlInit(J2I(argv[0]),J2I(argv[1]),&product));
	return JS_TRUE;
}
JS_FUN(AdhocctlTerm){
	*rval = I2J(sceNetAdhocctlTerm());
	c_delModule(adhocctl_uid);
	return JS_TRUE;
}
JS_FUN(AdhocctlGetAdhocId){
	JSObject*Product = J2O(argv[0]);
	struct productStruct product;
	memcpy(product.product,J2S(js_getProperty(Product,"product")),9);
	product.unknown = J2I(js_getProperty(Product,"type"));
	*rval = I2J(sceNetAdhocctlGetAdhocId(&product));
	return JS_TRUE;
}
JS_FUN(AdhocctlDisconnect){
	*rval = I2J(sceNetAdhocctlDisconnect());
	return JS_TRUE;
}
JS_FUN(AdhocctlConnect){
	*rval = I2J(sceNetAdhocctlConnect(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocctlCreate){
	*rval = I2J(sceNetAdhocctlCreate(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocctlScan){
	*rval = I2J(sceNetAdhocctlScan());
	return JS_TRUE;
}
JS_FUN(AdhocctlDelHandler){
	*rval = I2J(sceNetAdhocctlDelHandler(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocctlGetState){
	int event;
	sceNetAdhocctlGetState(&event);
	*rval = I2J(event);
	return JS_TRUE;
}
JS_FUN(AdhocctlJoin){
	struct SceNetAdhocctlScanInfo scaninfo;
	sceNetAdhocctlJoin(&scaninfo);
	/*
	TODO: convert the scanlist to a array of objects
	*/
	return JS_TRUE;
}
JS_FUN(AdhocctlCreateEnterGameMode){
	*rval = I2J(sceNetAdhocctlCreateEnterGameMode(J2S(argv[0]),J2I(argv[1]),J2I(argv[2]),(unsigned char*)J2S(argv[3]),J2U(argv[4]),J2I(argv[5])));
	return JS_TRUE;
}
JS_FUN(AdhocctlJoinEnterGameMode){
	*rval = I2J(sceNetAdhocctlJoinEnterGameMode(J2S(argv[0]),(unsigned char*)J2S(argv[1]),J2U(argv[2]),J2I(argv[3])));
	return JS_TRUE;
}
JS_FUN(AdhocctlGetGameModeInfo){
	struct SceNetAdhocctlGameModeInfo gamemodeinfo;
	sceNetAdhocctlGetGameModeInfo(&gamemodeinfo);
	JSObject* info = js_addObj(" ");
	js_setProperty(info,"count",I2J(gamemodeinfo.count));
	//js_setProperty(info,"macs",STRING_TO_JSVAL(strncpy(js_malloc(6),(unsigned char)*gamemodeinfo.macs[0],6)));
	/*
	TODO:return mac list in array
	*/
	*rval = O2J(info);
	return JS_TRUE;
}
JS_FUN(AdhocctlExitGameMode){
	*rval = I2J(sceNetAdhocctlExitGameMode());
	return JS_TRUE;
}
JS_FUN(AdhocctlGetPeerList){
	struct SceNetAdhocctlPeerInfo peerinfo;
	sceNetAdhocctlGetPeerInfo((unsigned char*)J2S(argv[0]),J2I(argv[1]),&peerinfo);
	/*
	TODO: convert the peerlist to a array of objects
	*/
	*rval = I2J(0);
	return JS_TRUE;
}
JS_FUN(AdhocctlGetScanInfo){
	int length;
	void* p=NULL;
	*rval = I2J(sceNetAdhocctlGetScanInfo(&length,p));
	JSObject*info = js_addObj(" ");
	js_setProperty(info,"length",I2J(length));
	js_setProperty(info,"p",I2J((u32)p));
	*rval = O2J(info);
	return JS_TRUE;
}
JS_FUN(AdhocctlAddHandler){
	*rval = I2J(sceNetAdhocctlAddHandler((sceNetAdhocctlHandler)J2U(argv[0]),(void*)J2U(argv[1])));
	return JS_TRUE;
}
JS_FUN(AdhocctlGetNameByAddr){
	char nickname[128];
	sceNetAdhocctlGetNameByAddr((unsigned char *)J2S(argv[0]),nickname);
//	*rval = S2J(nickname,128);
	return JS_TRUE;
}
JS_FUN(AdhocctlGetAddrByName){
	//int length = 6;
	//sceNetAdhocctlGetAddrByName(J2S(argv[0]),&length, (void *)buf);
//	*rval = S2J();
	return JS_TRUE;
}
JS_FUN(AdhocctlGetParameter){
	struct SceNetAdhocctlParams params;
	sceNetAdhocctlGetParameter(&params);
	
	JSObject*Parameter = js_addObj(" ");
	js_setProperty(Parameter,"channel",I2J(params.channel));
//	js_setProperty(Parameter,"name",S2J(params.name,8));
//	js_setProperty(Parameter,"bssid",S2J(params.bssid,6));
//	js_setProperty(Parameter,"nickname",S2J(params.nickname,128));
	*rval = O2J(Parameter);
	return JS_TRUE;
}
u32 adhocMatching_uid = 0;/*AdhocMatching*/
JS_FUN(AdhocMatchingInit){
	adhocMatching_uid = c_addModule("pspnet_adhoc_matching.prx");
	*rval = I2J(sceNetAdhocMatchingInit(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingTerm){
	*rval = I2J(sceNetAdhocMatchingTerm());
	c_delModule(adhocMatching_uid);
	return JS_TRUE;
}
JS_FUN(AdhocMatchingCreate){
	*rval = I2J(sceNetAdhocMatchingCreate(J2I(argv[0]),J2I(argv[1]),J2u(argv[2]),J2I(argv[3]),J2U(argv[4]),J2U(argv[5]),J2I(argv[6]),J2U(argv[7]),(pspAdhocMatchingCallback)J2U(argv[8])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingDelete){
	*rval = I2J(sceNetAdhocMatchingDelete(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingStart){
	*rval = I2J(sceNetAdhocMatchingStart(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),J2I(argv[4]),J2I(argv[5]),(void*)J2U(argv[6])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingStop){
	*rval = I2J(sceNetAdhocMatchingStop(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingSelectTarget){
	*rval = I2J(sceNetAdhocMatchingSelectTarget(J2I(argv[0]),(unsigned char*)J2S(argv[1]),J2I(argv[2]),(void*)J2U(argv[3])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingCancelTarget){
	*rval = I2J(sceNetAdhocMatchingCancelTarget(J2I(argv[0]),(unsigned char*)J2S(argv[1])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingCancelTargetWithOpt){
	*rval = I2J(sceNetAdhocMatchingCancelTargetWithOpt(J2I(argv[0]),(unsigned char*)J2S(argv[1]),J2I(argv[2]),(void*)J2U(argv[3])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingSendData){
	*rval = I2J(sceNetAdhocMatchingSendData(J2I(argv[0]),(unsigned char*)J2S(argv[1]),J2I(argv[2]),(void*)J2U(argv[3])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingAbortSendData){
	*rval = I2J(sceNetAdhocMatchingAbortSendData(J2I(argv[0]),(unsigned char*)J2S(argv[1])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingSetHelloOpt){
	*rval = I2J(sceNetAdhocMatchingSetHelloOpt(J2I(argv[0]),J2I(argv[1]),(void*)J2U(argv[2])));
	return JS_TRUE;
}
JS_FUN(AdhocMatchingGetHelloOpt){
	int len = 0;
	void* p = NULL;
	sceNetAdhocMatchingGetHelloOpt(J2I(argv[0]),&len,p);
	JSObject*opt=js_addObj(" ");
	js_setProperty(opt,"data",I2J(p));
	js_setProperty(opt,"length",I2J(len));
	*rval = O2J(opt);
	return JS_TRUE;
}
JS_FUN(AdhocMatchingGetMembers){
	int len = 0;
	void* p = NULL;
	sceNetAdhocMatchingGetMembers(J2I(argv[0]),&len,p);
	JSObject*opt=js_addObj(" ");
	js_setProperty(opt,"data",I2J(p));
	js_setProperty(opt,"length",I2J(len));
	*rval = O2J(opt);
	return JS_TRUE;
}
JS_FUN(AdhocMatchingGetPoolMaxAlloc){
	*rval = I2J(sceNetAdhocMatchingGetPoolMaxAlloc());
	return JS_TRUE;
}
JS_FUN(AdhocMatchingGetPoolStat){
	struct pspAdhocPoolStat poolstat;
	sceNetAdhocMatchingGetPoolStat(&poolstat);
	JSObject*opt=js_addObj(" ");
	js_setProperty(opt,"data",I2J(poolstat.size));
	js_setProperty(opt,"maxsize",I2J(poolstat.maxsize));
	js_setProperty(opt,"freesize",I2J(poolstat.freesize));
	*rval = O2J(opt);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
/*general*/
	{"init",NetInit,4},
	{"term",NetTerm,0},
	{"freeThreadinfo",FreeThreadinfo,1},
	{"threadAbort",ThreadAbort,1},
	{"etherStrton",EtherStrton,0},
	{"etherNtostr",EtherNtostr,0},
	{"getLocalEtherAddr",GetLocalEtherAddr,0},
	{"getMallocStat",GetMallocStat,0},
/*Resolver*/
	{"resolverInit",ResolverInit,0},
	{"resolverDelete",ResolverDelete,1},
	{"resolverCreate",ResolverCreate,0},
	{"resolverTerm",ResolverTerm,0},
	{"resolverStop",ResolverStop,1},
	{"resolverStartNtoA",ResolverStartNtoA,0},
	{"resolverStartAtoN",ResolverStartAtoN,0},
/*Adhoc*/
	{"adhocInit",AdhocInit,0},
	{"adhocTerm",AdhocTerm,0},
	{"adhocPdpCreate",AdhocPdpCreate,1},
	{"adhocPdpDelete",AdhocPdpDelete,1},
/*Adhoc/ctl*/
	{"adhocctlInit",AdhocctlInit,1},
	{"adhocctlGetAdhocId",AdhocctlGetAdhocId,1},
	{"adhocctlTerm",AdhocctlTerm,1},
	{"adhocctlDisconnect",AdhocctlDisconnect,1},
	{"adhocctlConnect",AdhocctlConnect,1},
	{"adhocctlCreate",AdhocctlCreate,1},
	{"adhocctlScan",AdhocctlScan,1},
	{"adhocctlDelHandler",AdhocctlDelHandler,1},
	{"adhocctlGetState",AdhocctlGetState,1},
/*Adhoc/Matching*/
	{"adhocMatchingInit",AdhocMatchingInit,1},
	{"adhocMatchingTerm",AdhocMatchingTerm,1},
	{"adhocMatchingCreate",AdhocMatchingCreate,1},
	{"adhocMatchingDelete",AdhocMatchingDelete,1},
	{"adhocMatchingStart",AdhocMatchingStart,1},
	{"adhocMatchingStop",AdhocMatchingStop,1},
	{"adhocMatchingSelectTarget",AdhocMatchingSelectTarget,1},
	{"adhocMatchingCancelTarget",AdhocMatchingCancelTarget,1},
	{"adhocMatchingCancelTargetWithOpt",AdhocMatchingCancelTargetWithOpt,1},
	{"adhocMatchingSendData",AdhocMatchingSendData,1},
	{"adhocMatchingAbortSendData",AdhocMatchingAbortSendData,1},
	{"adhocMatchingSetHelloOpt",AdhocMatchingSetHelloOpt,1},
	{"adhocMatchingGetHelloOpt",AdhocMatchingGetHelloOpt,1},
	{"adhocMatchingGetMembers",AdhocMatchingGetMembers,1},
	{"adhocMatchingGetPoolMaxAlloc",AdhocMatchingGetPoolMaxAlloc,1},
	{"adhocMatchingGetPoolStat",AdhocMatchingGetPoolStat,1},
/*apctl*/
	{"apctlInit",ApctlInit,2},
	{"apctlTerm",ApctlTerm,0},
	{"apctlGetInfo",ApctlGetInfo,2},
	{"apctlAddHandler",ApctlAddHandler,2},
	{"apctlDelHandler",ApctlDelHandler,1},
	{"apctlConnect",ApctlConnect,1},
	{"apctlDisconnect",ApctlDisconnect,0},
	{"apctlGetState",ApctlGetState,0},
/*Inet*/
	{"inetInit",InetInit,0},
	{"inetTerm",InetTerm,0},
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
