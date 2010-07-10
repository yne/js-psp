#include <pspkernel.h>
#include <stdio.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("modK",PSP_MODULE_KERNEL,0,0);

int Kfun(void){
	printf("[modK] Kfun called\n");
	return 0;
}
JSBool template(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	printf("test receive : \"%i\"",J2I(argv[0]));
	*rval = I2J(J2I(argv[0])*3);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"template",template, 1},
	{0}
};
JSFunctionSpec* modK_GetFun(void){
	return functions;
}
static JSPropertiesSpec var[] = {
	{"KTEMPLATE_IS_LOADED",I2J(1)},
	{0}
};
JSPropertiesSpec* modK_GetVar(void){
	return var;
}
int module_start(SceSize args, char* argp[]){
	printf("[modK] started !\n");
	//printf("[modK] call js_test : %08X\n",js_test(5));//forbidden by the os
	return 0;//lib not started if != 0
}
int module_stop(SceSize args, void *argp){
	printf("[modK] stoped !\n");
	return 0;
}