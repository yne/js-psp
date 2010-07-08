#include <pspkernel.h>
#include <string.h>
#include "src/jsapi.h"
#include "src/jsarray.h"

/* my custom functions */

JSBool js_print(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
	const char *msg;
	if (!JS_ConvertArguments(cx, argc, argv, "s", &msg))
		return JS_FALSE;
	printf(msg);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
extern int Kfun();
extern int Ufun();
JSBool js_include(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
	char* path = JS_GetStringBytes(JS_ValueToString(cx,argv[0]));
	int uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	int mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		if(mod == 0x8002012E)printf("<%s> not found!\n",path);
		if(mod == 0x80020190)printf("can't start prx : try to compile with PSPSDKlibC\n");
		if(mod == 0x8002013C)printf("can't start prx : User compiled as kernel\n");
		printf("Error 0x%08X when starting (ret:%X)\n", mod, ret);
	}
	if(strstr(path,"_driver")){
		printf("calling Kfun ...\n");
		Kfun();
	}else{
		printf("calling Ufun ...\n");
		Ufun();
	}
	return JS_TRUE;
}
