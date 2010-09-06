#include <pspkernel.h>
#include <psphprm.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceHprm",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(PeekCurrentKey){
	u32 key;
	sceHprmPeekCurrentKey(&key);
	*rval = I2J(key);
	return JS_TRUE;
}
JS_FUN(PeekLatch){
	u32 key;
	sceHprmPeekLatch(&key);
	*rval = I2J(key);
	return JS_TRUE;
}
JS_FUN(ReadLatch){
	u32 key;
	sceHprmReadLatch(&key);
	*rval = I2J(key);
	return JS_TRUE;
}
JS_FUN(IsHeadphoneExist){
	*rval = I2J(sceHprmIsHeadphoneExist());
	return JS_TRUE;
}
JS_FUN(IsRemoteExist){
	*rval = I2J(sceHprmIsRemoteExist());
	return JS_TRUE;
}
JS_FUN(IsMicrophoneExist){
	*rval = I2J(sceHprmIsMicrophoneExist());
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"PeekCurrentKey",PeekCurrentKey,0},
	{"PeekLatch",PeekLatch,0},
	{"ReadLatch",ReadLatch,0},
	{"IsHeadphoneExist",IsHeadphoneExist,0},
	{"IsRemoteExist",IsRemoteExist,0},
	{"IsMicrophoneExist",IsMicrophoneExist,0},
	{0}
};
static JSPropertiesSpec var[] = {
	{"PSP_HPRM_PLAYPAUSE", I2J(0x1)},
	{"PSP_HPRM_FORWARD", I2J(0x4)},
	{"PSP_HPRM_BACK", I2J(0x8)},
	{"PSP_HPRM_VOL_UP", I2J(0x10)},
	{"PSP_HPRM_VOL_DOWN", I2J(0x20)},
	{"PSP_HPRM_HOLD", I2J(0x80)},
	{0}
};

int module_start(SceSize args, void *argp){
	js_addModule(lfun,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
