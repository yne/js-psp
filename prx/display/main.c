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
	if(argc)obj=J2O(argv[0]);
	int mode,width,height;
	sceDisplayGetMode(&mode,&width,&height);
	js_setProperty(obj,"mode",I2J(mode));
	js_setProperty(obj,"width",I2J(width));
	js_setProperty(obj,"height",I2J(height));
	*rval = O2J(obj);
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
	js_setProperty(obj,"topaddr",I2J(topaddr));
	js_setProperty(obj,"bufferwidth",I2J(bufferwidth));
	js_setProperty(obj,"pixelformat",I2J(pixelformat));
	*rval = O2J(obj);
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
static JSFunctionSpec lfun[] = {
	{"setMode",SetMode,3},
	{"getMode",GetMode,3},
	{"setFrameBuf",SetFrameBuf,4},
	{"getFrameBuf",GetFrameBuf,4},
	{"getVcount",GetVcount,0},
	{"waitVblankStart",WaitVblankStart,0},
	{"waitVblankStartCB",WaitVblankStartCB,0},
	{"waitVblank",WaitVblank,0},
	{"waitVblankCB",WaitVblankCB,0},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"sceDisplaySetMode",SetMode,3},
	{"sceDisplayGetMode",GetMode,3},
	{"sceDisplaySetFrameBuf",SetFrameBuf,4},
	{"sceDisplayGetFrameBuf",GetFrameBuf,4},
	{"sceDisplayGetVcount",GetVcount,0},
	{"sceDisplayWaitVblankStart",WaitVblankStart,0},
	{"sceDisplayWaitVblankStartCB",WaitVblankStartCB,0},
	{"sceDisplayWaitVblank",WaitVblank,0},
	{"sceDisplayWaitVblankCB",WaitVblankCB,0},
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
	js_addModule(lfun,gfun,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
