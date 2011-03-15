#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspctrl.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceCtrl",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(SetSamplingCycle){
	*rval = I2J(sceCtrlSetSamplingCycle(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(GetSamplingCycle){
	int mode;
	sceCtrlGetSamplingCycle(&mode);
	*rval = I2J(mode);
	return JS_TRUE;
}
JS_FUN(SetSamplingMode){
	*rval = I2J(sceCtrlSetSamplingMode(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(GetSamplingMode){
	int mode;
	sceCtrlGetSamplingMode(&mode);
	*rval = I2J(mode);
	return JS_TRUE;
}
JS_FUN(ReadBufferPositive){
	JSObject*opad=argc?J2O(argv[0]):obj;
	SceCtrlData pad;
	sceCtrlReadBufferPositive(&pad,1);
	js_setProperty(opad,"Buttons",I2J(pad.Buttons));
	js_setProperty(opad,"Lx",I2J(pad.Lx));
	js_setProperty(opad,"Ly",I2J(pad.Ly));
	*rval = O2J(opad);
	return JS_TRUE;
}
JS_FUN(ReadBufferNegative){
	JSObject*opad=argc?J2O(argv[0]):obj;
	SceCtrlData pad;
	sceCtrlReadBufferNegative(&pad,1);
	js_setProperty(opad,"Buttons",I2J(pad.Buttons));
	js_setProperty(opad,"Lx",I2J(pad.Lx));
	js_setProperty(opad,"Ly",I2J(pad.Ly));
	*rval = O2J(opad);
	return JS_TRUE;
}
JS_FUN(PeekBufferPositive){
	JSObject*opad=argc?J2O(argv[0]):obj;
	SceCtrlData pad;
	sceCtrlPeekBufferPositive(&pad,1);
	js_setProperty(opad,"Buttons",I2J(pad.Buttons));
	js_setProperty(opad,"Lx",I2J(pad.Lx));
	js_setProperty(opad,"Ly",I2J(pad.Ly));
	*rval = O2J(opad);
	return JS_TRUE;
}
JS_FUN(PeekBufferNegative){
	JSObject*opad=argc?J2O(argv[0]):obj;
	SceCtrlData pad;
	sceCtrlPeekBufferNegative(&pad,1);
	js_setProperty(opad,"Buttons",I2J(pad.Buttons));
	js_setProperty(opad,"Lx",I2J(pad.Lx));
	js_setProperty(opad,"Ly",I2J(pad.Ly));
	*rval = O2J(opad);
	return JS_TRUE;
}
JS_FUN(PeekLatch){
	JSObject*olatch=argc?J2O(argv[0]):obj;
	SceCtrlLatch latch_data;
	sceCtrlPeekLatch(&latch_data);
	js_setProperty(olatch,"uiMake",I2J(latch_data.uiMake));
	js_setProperty(olatch,"uiBreak",I2J(latch_data.uiBreak));
	js_setProperty(olatch,"uiPress",I2J(latch_data.uiPress));
	js_setProperty(olatch,"uiRelease",I2J(latch_data.uiRelease));
	*rval = O2J(olatch);
	return JS_TRUE;
}
JS_FUN(ReadLatch){
	JSObject*olatch=argc?J2O(argv[0]):obj;
	SceCtrlLatch latch_data;
	sceCtrlPeekLatch(&latch_data);
	js_setProperty(olatch,"uiMake",I2J(latch_data.uiMake));
	js_setProperty(olatch,"uiBreak",I2J(latch_data.uiBreak));
	js_setProperty(olatch,"uiPress",I2J(latch_data.uiPress));
	js_setProperty(olatch,"uiRelease",I2J(latch_data.uiRelease));
	*rval = O2J(olatch);
	return JS_TRUE;
}
JS_FUN(SetIdleCancelThreshold){
	*rval = I2J(sceCtrlSetIdleCancelThreshold(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(GetIdleCancelThreshold){
	JSObject*othreshold=argc?J2O(argv[0]):obj;
	int idlerest, idleback;
	sceCtrlGetIdleCancelThreshold(&idlerest,&idleback);
	js_setProperty(othreshold,"idlerest",I2J(idlerest));
	js_setProperty(othreshold,"idleback",I2J(idleback));
	*rval = JSVAL_VOID;//O2J(othreshold);
	return JS_TRUE;
}
static JSPropertiesSpec var[] = {
	{"PSP_CTRL_MODE_DIGITAL",I2J(PSP_CTRL_MODE_DIGITAL)},
	{"PSP_CTRL_MODE_ANALOG",I2J(PSP_CTRL_MODE_ANALOG)},
	{"PSP_CTRL_SELECT",I2J(PSP_CTRL_SELECT)},
	{"PSP_CTRL_START",I2J(PSP_CTRL_START)},
	{"PSP_CTRL_UP",I2J(PSP_CTRL_UP)},
	{"PSP_CTRL_RIGHT",I2J(PSP_CTRL_RIGHT)},
	{"PSP_CTRL_DOWN",I2J(PSP_CTRL_DOWN)},
	{"PSP_CTRL_LEFT",I2J(PSP_CTRL_LEFT)},
	{"PSP_CTRL_LTRIGGER",I2J(PSP_CTRL_LTRIGGER)},
	{"PSP_CTRL_RTRIGGER",I2J(PSP_CTRL_RTRIGGER)},
	{"PSP_CTRL_TRIANGLE",I2J(PSP_CTRL_TRIANGLE)},
	{"PSP_CTRL_CIRCLE",I2J(PSP_CTRL_CIRCLE)},
	{"PSP_CTRL_CROSS",I2J(PSP_CTRL_CROSS)},
	{"PSP_CTRL_SQUARE",I2J(PSP_CTRL_SQUARE)},
	{"PSP_CTRL_HOME",I2J(PSP_CTRL_HOME)},
	{"PSP_CTRL_HOLD",I2J(PSP_CTRL_HOLD)},
	{"PSP_CTRL_NOTE",I2J(PSP_CTRL_NOTE)},
	{"PSP_CTRL_SCREEN",I2J(PSP_CTRL_SCREEN)},
	{"PSP_CTRL_VOLUP",I2J(PSP_CTRL_VOLUP)},
	{"PSP_CTRL_VOLDOWN",I2J(PSP_CTRL_VOLDOWN)},
	{"PSP_CTRL_WLAN_UP",I2J(PSP_CTRL_WLAN_UP)},
	{"PSP_CTRL_REMOTE",I2J(PSP_CTRL_REMOTE)},
	{"PSP_CTRL_DISC",I2J(PSP_CTRL_DISC)},
	{"PSP_CTRL_MS",I2J(PSP_CTRL_MS)}
};
static JSFunctionSpec lfun[] = {
	{"peekLatch",PeekLatch, 0},
	{"readLatch",ReadLatch, 0},
	{"setSamplingMode",SetSamplingMode, 1},
	{"getSamplingMode",GetSamplingMode, 0},
	{"setSamplingCycle",SetSamplingCycle, 1},
	{"getSamplingCycle",GetSamplingCycle, 0},
	{"peekBufferPositive",PeekBufferPositive, 0},
	{"peekBufferNegative",PeekBufferNegative, 0},
	{"readBufferPositive",ReadBufferPositive, 0},
	{"readBufferNegative",ReadBufferNegative, 0},
	{"setIdleCancelThreshold",SetIdleCancelThreshold, 2},
	{"getIdleCancelThreshold",GetIdleCancelThreshold, 0},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"sceCtrlPeekLatch",PeekLatch, 0},
	{"sceCtrlReadLatch",ReadLatch, 0},
	{"sceCtrlSetSamplingMode",SetSamplingMode, 1},
	{"sceCtrlGetSamplingMode",GetSamplingMode, 0},
	{"sceCtrlSetSamplingCycle",SetSamplingCycle, 1},
	{"sceCtrlGetSamplingCycle",GetSamplingCycle, 0},
	{"sceCtrlPeekBufferPositive",PeekBufferPositive, 0},
	{"sceCtrlPeekBufferNegative",PeekBufferNegative, 0},
	{"sceCtrlReadBufferPositive",ReadBufferPositive, 0},
	{"sceCtrlReadBufferNegative",ReadBufferNegative, 0},
	{"sceCtrlSetIdleCancelThreshold",SetIdleCancelThreshold, 2},
	{"sceCtrlGetIdleCancelThreshold",GetIdleCancelThreshold, 0},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,gfun,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
