#include <pspkernel.h>
#include <pspsdk.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("Ksample",PSP_MODULE_KERNEL,1,1);
PSP_NO_CREATE_MAIN_THREAD();

/*
JS_FUN(WaitVblankCB){
	*rval = INT_TO_JSVAL(sceDisplayWaitVblankCB());
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
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

*/
static JSPropertiesSpec var[] = {
	{"Ksample", I2J(1)},
	{0}
};
KmodInfo Ksample_addModule (){
	KmodInfo info;
	info.lfun = NULL;
	info.gfun = NULL;
	info.lvar = NULL;
	info.gvar = var;
	return info; 
}
int module_start(SceSize args, void *argp){
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
