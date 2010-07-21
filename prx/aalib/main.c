#include <pspkernel.h>
#include <stdio.h>
#include "pspaalib.h"
#include "../../main/shared.h"

PSP_MODULE_INFO("aalib",PSP_MODULE_USER,0,0);

/*you cant printf in user module (did i missed something ?)*/
int Ufun(void){
	return 0;
}
JS_FUN(js_AalibSetAmplification){
	*rval = I2J(AalibSetAmplification(J2I(argv[0]),0.01f*J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(js_AalibSetVolume){
	AalibVolume vol;
	vol.left=0.01f*J2I(argv[1]);
	vol.right=0.01f*J2I(argv[2]);
	*rval = I2J(AalibSetVolume(J2I(argv[0]),vol));
	return JS_TRUE;
}
JS_FUN(js_AalibSetPlaySpeed){
	*rval = I2J(AalibSetAmplification(J2I(argv[0]),0.01f*J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(js_AalibInit){
	*rval = I2J(AalibInit());
	return JS_TRUE;
}
JS_FUN(js_AalibLoad){
	*rval = I2J(AalibLoad(J2S(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(js_AalibUnload){
	*rval = I2J(AalibUnload(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibPlay){
	*rval = I2J(AalibPlay(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibStop){
	*rval = I2J(AalibStop(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibPause){
	*rval = I2J(AalibPause(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibRewind){
	*rval = I2J(AalibRewind(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibSetAutoloop){
	*rval = I2J(AalibSetAutoloop(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(js_AalibGetStopReason){
	*rval = I2J(AalibGetStopReason(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibGetStatus){
	*rval = I2J(AalibGetStatus(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(js_AalibTest){
	*rval = I2J(69);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"SetAmplification",js_AalibSetAmplification, 1},
	{"SetVolume",js_AalibSetVolume, 1},
	{"SetPlaySpeed",js_AalibSetPlaySpeed, 1},
	{"Init",js_AalibInit, 1},
	{"Load",js_AalibLoad, 1},
	{"Unload",js_AalibUnload, 1},
	{"Play",js_AalibPlay, 1},
	{"Stop",js_AalibStop, 1},
	{"Pause",js_AalibPause, 1},
	{"Rewind",js_AalibRewind, 1},
	{"SetAutoloop",js_AalibSetAutoloop, 1},
	{"GetStopReason",js_AalibGetStopReason, 1},
	{"GetStatus",js_AalibGetStatus, 1},
	{"Test",js_AalibTest, 1},
	{0}
};
static JSPropertiesSpec var[] = {
	{"AALIB_IS_LOADED",I2J(1)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
