#include <pspkernel.h>
#include <string.h>
#include "src/jsapi.h"
#include "src/jsarray.h"

#include "shared.h"

/* my custom functions */

JSBool js_print(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
	printf(J2S(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
extern int Kfun();
extern int Ufun();
extern JSFunctionSpec* modU_GetFun();
extern JSPropertiesSpec* modU_GetVar();
extern JSFunctionSpec* modK_GetFun();
extern JSPropertiesSpec* modK_GetVar();

JSBool js_include(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
	char* path = JS_GetStringBytes(JS_ValueToString(cx,argv[0]));
	int uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	int mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		if(mod == 0x8002012E)printf("<%s> not found!\n",path);
		if(mod == 0x8002013B)printf("<%s> already loaded/started\n",path);
		if(mod == 0x80020190)printf("can't start prx : try to compile with PSPSDKlibC\n");
		if(mod == 0x8002013C)printf("can't start prx : User compiled as kernel\n");
		printf("Error 0x%08X when starting (ret:%X)\n", mod, ret);
	}
	JSObject* target = js_addObj(" ");//you cant find me :3
	if(strstr(path,"_driver")){
	/*function are correctly called but the reply can't be read ...*/
		printf("%08X %08X %08X\n",(int)modK_GetFun(),(int)modK_GetVar(),Kfun());
		//js_addFunc(modK_GetFun(),target);//functions are defined as local
		//js_addVar(modK_GetVar(),NULL);//variables are defined as global (local can be get by local function)
	}else{
		js_addFunc(modU_GetFun(),target);//functions are defined as local
		js_addVar(modU_GetVar(),NULL);//variables are defined as global (local can be get by local function)
	}
	*rval = O2J(target);
	return JS_TRUE;
}
