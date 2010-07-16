#include <pspkernel.h>
#include <stdio.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("modU",PSP_MODULE_USER,0,0);

int Ufun(void){
	printf("[modU] Ufun called\n");
	return 0;
}
JSBool template(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	printf("test receive : \"%s\"",J2S(argv[0]));
	*rval = I2J(32);//O2J(Threshold);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"template",template, 1},
	{0}
};
JSFunctionSpec* modU_GetFun(void){
	return functions;
}
static JSPropertiesSpec var[] = {
	{"TEMPLATE_IS_LOADED",I2J(1)},
	{0}
};
JSPropertiesSpec* modU_GetVar(void){
	printf("modU_GetVar called\n");
	return var;
}
int module_start(SceSize args, char* argp[]){
while(1){
	printf("[modU] started !\n");
	printf("[modU] call js_test : %08X\n",js_test(5));//(5*3=15=F)
	}
	return 0;//lib not started if != 0
}
int module_stop(SceSize args, void *argp){
	printf("[modU] stoped !\n");
	return 0;
}
