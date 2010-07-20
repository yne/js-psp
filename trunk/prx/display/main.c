#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceDisplay",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JSBool SetMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	int mode,width,height;
	if (!js_convertArguments(argc, argv, "iii", &mode,&width,&height))
		return JS_FALSE;
	*rval = INT_TO_JSVAL(sceDisplaySetMode(mode,width,height));
	return JS_TRUE;
}
JSBool GetMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	int mode,width,height;
	if (!js_convertArguments(argc, argv, "iii", &mode,&width,&height))
		return JS_FALSE;
	*rval = INT_TO_JSVAL(sceDisplayGetMode(&mode,&width,&height));
	return JS_TRUE;
}
JSBool SetFrameBuf(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
//int 	sceDisplaySetFrameBuf (void *topaddr, int bufferwidth, int pixelformat, int sync)
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool GetFrameBuf(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
//int 	sceDisplayGetFrameBuf (void **topaddr, int *bufferwidth, int *pixelformat, int sync)
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool GetVcount(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = INT_TO_JSVAL(sceDisplayGetVcount());
	return JS_TRUE;
}
JSBool WaitVblankStart(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankStart());
	return JS_TRUE;
}
JSBool WaitVblankStartCB(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankStartCB());
	return JS_TRUE;
}
JSBool WaitVblank(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblank());
	return JS_TRUE;
}
JSBool WaitVblankCB(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankCB());
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"SetMode",SetMode,3},
	{"GetMode",GetMode,3},
	{"SetFrameBuf",SetFrameBuf,4},
	{"GetFrameBuf",GetFrameBuf,4},
	{"GetVcount",GetVcount,0},
	{"WaitVblankStart",WaitVblankStart,0},
	{"WaitVblankStartCB",WaitVblankStartCB,0},
	{"WaitVblank",WaitVblank,0},
	{"WaitVblankCB",WaitVblankCB,0},
	{0}
};
static JSPropertiesSpec var[] = {
	{"BUF_WIDTH", I2J(512)},
	{"SCR_WIDTH", I2J(480)},
	{"SCR_HEIGHT", I2J(272)},
	{"PSP_DISPLAY_PIXEL_FORMAT_565", I2J(0)},
	{"PSP_DISPLAY_PIXEL_FORMAT_5551", I2J(1)},
	{"PSP_DISPLAY_PIXEL_FORMAT_4444", I2J(2)},
	{"PSP_DISPLAY_PIXEL_FORMAT_8888", I2J(3)},
	{"PSP_DISPLAY_SETBUF_IMMEDIATE", I2J(0)},
	{"PSP_DISPLAY_SETBUF_NEXTFRAME", I2J(1)},
	{0}
};

int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
