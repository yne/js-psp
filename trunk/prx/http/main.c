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

#include <psphttp.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceHttp",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

u32 puri=0,phttp=0,lhttp=0;
JS_FUN(Init){//[poolSize]
	puri=c_addModule("flash0:/kd/libparse_uri.prx");
	phttp=c_addModule("flash0:/kd/libparse_http.prx");
	lhttp=c_addModule("flash0:/kd/libhttp.prx");
	*rval = I2J(sceHttpInit(argc?J2I(argv[0]):20000));
	return JS_TRUE;
}
JS_FUN(End){
	c_delModule(lhttp);
	c_delModule(phttp);
	c_delModule(puri);
	*rval = I2J(sceHttpEnd());
	return JS_TRUE;
}
JS_FUN(CreateTemplate){//user_agent[,http_ver[,netcnf]]
	*rval = I2J(sceHttpCreateTemplate(argc?J2S(argv[0]):"Mozilla/5.0 (Windows; Windows NT 5.1; rv:2.0b2) Gecko/20100720 Firefox/4.1",(argc<1)?J2I(argv[1]):1,(argc<2)?J2I(argv[2]):0));
	return JS_TRUE;
}
JS_FUN(DeleteTemplate){
	*rval = I2J(sceHttpDeleteTemplate(J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(EnableCookie){
	if(argc)
		*rval = I2J(sceHttpEnableCookie(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(DisableCookie){
	if(argc)
		*rval = I2J(sceHttpDisableCookie(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(CreateConnection){//tmpl,server_name,[scheme,[port,[keepalive]]]
	if(argc<2)return JS_TRUE;
	int cnx = sceHttpCreateConnection(J2I(argv[0]),J2S(argv[1]),(argc>2)?J2S(argv[2]):"http",(argc>3)?J2I(argv[3]):80,(argc>4)?J2U(argv[4]):1);
	if(cnx>0)*rval = I2J(cnx);
	else{js_test(__LINE__);js_test(cnx);}
	return JS_TRUE;
}
JS_FUN(CreateConnectionWithURL){//tmpl,server_name[,keepalive]
	if(argc<2)return JS_TRUE;
	int cnx = sceHttpCreateConnectionWithURL(J2I(argv[0]),J2S(argv[1]),(argc>2)?J2I(argv[2]):1);
	if(cnx>0)*rval = I2J(cnx);
	else{js_test(__LINE__);js_test(cnx);}
	return JS_TRUE;
}
JS_FUN(DeleteConnection){
	if(argc)
		*rval = I2J(sceHttpDeleteConnection(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(AddExtraHeader){
	if(argc>2)
		*rval = I2J(sceHttpAddExtraHeader(J2I(argv[0]),J2S(argv[1]),J2S(argv[2]),0));
	return JS_TRUE;
}
JS_FUN(DeleteHeader){
	if(argc==2)
		*rval = I2J(sceHttpDeleteHeader(J2I(argv[0]),J2S(argv[1])));
	return JS_TRUE;
}
JS_FUN(CreateRequest){//cnx,methode,path[,length]
	if(argc<3)return JS_TRUE;
	if(J2I(argv[1])==PSP_HTTP_METHOD_GET)//only 3 arg neeeded
		*rval = I2J(sceHttpCreateRequest(J2I(argv[0]),J2I(argv[1]),J2S(argv[2]),0));
	else
		*rval = I2J(sceHttpCreateRequest(J2I(argv[0]),J2I(argv[1]),J2S(argv[2]),J2L(argv[3])));
	return JS_TRUE;
}
JS_FUN(CreateRequestWithURL){//cnx,methode,uri[,length]
	if(argc<3)return JS_TRUE;
	if(J2I(argv[1])==PSP_HTTP_METHOD_GET)//only 3 arg neeeded
		*rval = I2J(sceHttpCreateRequestWithURL(J2I(argv[0]),J2I(argv[1]),J2S(argv[2]),0));
	else
		*rval = I2J(sceHttpCreateRequestWithURL(J2I(argv[0]),J2I(argv[1]),J2S(argv[2]),J2L(argv[3])));
	return JS_TRUE;
}
JS_FUN(AbortRequest){
	if(argc)
		*rval = I2J(sceHttpAbortRequest(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(DeleteRequest){
	if(argc)
		*rval = I2J(sceHttpDeleteRequest(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(EnableKeepAlive){
	if(argc)
		*rval = I2J(sceHttpEnableKeepAlive(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(DisableKeepAlive){
	if(argc)
		*rval = I2J(sceHttpDisableKeepAlive(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(EnableRedirect){
	if(argc)
		*rval = I2J(sceHttpEnableRedirect(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(SendRequest){
	if(!argc)return JS_TRUE;
	*rval = I2J(sceHttpSendRequest(J2I(argv[0]),(argc>1)?J2S(argv[1]):NULL,(argc>1)?js_getStringLength(JSVAL_TO_STRING(argv[1])):0));
	return JS_TRUE;
}
JS_FUN(ReadData){//80431100=bad id
	unsigned length=J2U(argv[1]);
	char* data=js_malloc((int)length);
	int res = sceHttpReadData(J2I(argv[0]),data,length);
	if(res>0)
		*rval = STRING_TO_JSVAL(js_newString(data,res));
	return JS_TRUE;
}
JS_FUN(GetContentLength){
	if(!argc)return JS_TRUE;
	unsigned long long contentlength;
	u32 result = sceHttpGetContentLength(J2I(argv[0]),&contentlength);
	if(result>0)
		*rval = I2J(contentlength);
	return JS_TRUE;
}
JS_FUN(GetStatusCode){
	if(!argc)return JS_TRUE;
	int statuscode;
	sceHttpGetStatusCode(J2I(argv[0]),&statuscode);
	*rval = I2J(statuscode);
	return JS_TRUE;
}
JS_FUN(SaveSystemCookie){
	*rval = I2J(sceHttpSaveSystemCookie());
	return JS_TRUE;
}
JS_FUN(LoadSystemCookie){
	*rval = I2J(sceHttpLoadSystemCookie());
	return JS_TRUE;
}
JS_FUN(SetConnectTimeOut){
	if(argc<2)return JS_TRUE;
	*rval = I2J(sceHttpSetConnectTimeOut(J2I(argv[0]),J2U(argv[1])));
	return JS_TRUE;
}
JS_FUN(SetRecvTimeOut){
	if(argc<2)return JS_TRUE;
	*rval = I2J(sceHttpSetRecvTimeOut(J2I(argv[0]),J2U(argv[1])));
	return JS_TRUE;
}
JS_FUN(SetResolveRetry){
	if(argc<2)return JS_TRUE;
	*rval = I2J(sceHttpSetResolveRetry(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(SetResolveTimeOut){
	if(argc<2)return JS_TRUE;
	*rval = I2J(sceHttpSetResolveTimeOut(J2I(argv[0]),J2U(argv[1])));
	return JS_TRUE;
}
JS_FUN(SetSendTimeOut){
	if(argc<2)return JS_TRUE;
	*rval = I2J(sceHttpSetSendTimeOut(J2I(argv[0]),J2U(argv[1])));
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"init",Init,1},
	{"end",End,0},
	{"createTemplate",CreateTemplate,3},
	{"deleteTemplate",DeleteTemplate,3},
	{"createConnection",CreateConnection,5},
	{"createConnectionWithURL",CreateConnectionWithURL,3},
	{"deleteConnection",DeleteConnection,1},
	{"addExtraHeader",AddExtraHeader,3},
	{"deleteHeader",DeleteHeader,2},
	{"createRequest",CreateRequest,4},
	{"createRequestWithURL",CreateRequestWithURL,4},
	{"deleteRequest",DeleteRequest,1},
	{"enableRedirect",EnableRedirect,1},
	{"saveSystemCookie",SaveSystemCookie,0},
	{"loadSystemCookie",LoadSystemCookie,0},
	{"enableCookie",EnableCookie,1},
	{"disableCookie",DisableCookie,1},
	{"enableKeepAlive",EnableKeepAlive,1},
	{"disableKeepAlive",DisableKeepAlive,1},
	{"readData",ReadData,2},
	{"sendRequest",SendRequest,2},
	{"setConnectTimeOut",SetConnectTimeOut,2},
	{"setRecvTimeOut",SetRecvTimeOut,2},
	{"getStatusCode",GetStatusCode,1},
	{"getContentLength",GetContentLength,1},
	{"setSendTimeOut",SetSendTimeOut,2},
	{"setResolveTimeOut",SetResolveTimeOut,2},
	{"setResolveRetry",SetResolveRetry,2},
	{0}
};
static JSPropertiesSpec var[] = {
	{"PSP_HTTP_METHOD_GET", I2J(0)},
	{"PSP_HTTP_METHOD_POST", I2J(1)},
	{"PSP_HTTP_METHOD_HEAD", I2J(2)},
	{"PSP_HTTP_METHOD_OPTIONS", I2J(3)},
	{"PSP_HTTP_METHOD_PUT", I2J(4)},
	{"PSP_HTTP_METHOD_DELETE", I2J(5)},
	{"PSP_HTTP_METHOD_TRACE", I2J(6)},
	{"PSP_HTTP_METHOD_CONNECT", I2J(7)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}