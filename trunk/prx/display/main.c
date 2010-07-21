#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceDisplay",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(SetMode){
	*rval = I2J(sceDisplaySetMode(J2I(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(GetMode){
	JSObject*rslt;
	if(argv[0])
		rslt=J2O(argv[0]);
	else
		rslt=js_addObj(" ");
	int mode,width,height;
	sceDisplayGetMode(&mode,&width,&height);
	js_setProperty(rslt,"mode",I2J(mode));
	js_setProperty(rslt,"width",I2J(width));
	js_setProperty(rslt,"height",I2J(height));
	*rval = O2J(rslt);
	return JS_TRUE;
}
JS_FUN(SetFrameBuf){
	*rval = I2J(sceDisplaySetFrameBuf((void*)J2U(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3])));
	return JS_TRUE;
}
JS_FUN(GetFrameBuf){
	int sync=0;
	if(argc>0)
		sync=J2U(argv[0]);
	static int bufferwidth, pixelformat;
	static u32* topaddr;
	sceDisplayGetFrameBuf((void*)&topaddr, &bufferwidth, &pixelformat, sync);
	JSObject*rslt=js_addObj(" ");
	js_setProperty(rslt,"topaddr",I2J(topaddr));
	js_setProperty(rslt,"bufferwidth",I2J(bufferwidth));
	js_setProperty(rslt,"pixelformat",I2J(pixelformat));
	*rval = O2J(rslt);
	return JS_TRUE;
}
JS_FUN(GetVcount){
	*rval = INT_TO_JSVAL(sceDisplayGetVcount());
	return JS_TRUE;
}
JS_FUN(WaitVblankStart){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankStart());
	return JS_TRUE;
}
JS_FUN(WaitVblankStartCB){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankStartCB());
	return JS_TRUE;
}
JS_FUN(WaitVblank){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblank());
	return JS_TRUE;
}
JS_FUN(WaitVblankCB){
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
