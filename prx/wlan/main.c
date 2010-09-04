#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pspwlan.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceWlan",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(DevIsPowerOn){
	*rval = I2J(sceWlanDevIsPowerOn());
	return JS_TRUE;
}
JS_FUN(GetSwitchState){
	*rval = I2J(sceWlanGetSwitchState());
	return JS_TRUE;
}
JS_FUN(GetEtherAddr){
	u8 mac[6];
	sceWlanGetEtherAddr(mac);
	char*p=js_malloc(13);
	sprintf(p,"%02X%02X%02X%02X%02X%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	*rval = STRING_TO_JSVAL(js_newString(p,13));
	return JS_TRUE;
}
JS_FUN(DevAttach){
	*rval = I2J(sceWlanDevAttach());
	return JS_TRUE;
}
JS_FUN(DevDetach){
	*rval = I2J(sceWlanDevDetach());
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"devIsPowerOn",DevIsPowerOn,0},
	{"getSwitchState",GetSwitchState,0},
	{"getEtherAddr",GetEtherAddr,0},
	{"devAttach",DevAttach,0},
	{"devDetach",DevDetach,0},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,0);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
