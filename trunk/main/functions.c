#include <pspkernel.h>
#include <string.h>
#include <stdio.h>
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
extern JSFunctionSpec* modK_GetFun();
extern JSPropertiesSpec* modK_GetVar();

const JS_FUN(js_include){
	char* path = JS_GetStringBytes(JS_ValueToString(cx,argv[0]));
	int uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	int mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		printf("Error 0x%08X ", mod);
		if(mod == 0x8002012E)printf(": <%s> not found!",path);
		if(mod == 0x8002013B)printf(": <%s> already loaded/started",path);
		if(mod == 0x80020190)printf(": can't start prx : try to compile with PSPSDKlibC");
		if(mod == 0x8002013C)printf(": can't start prx : User compiled as kernel");
		printf("\n");
		return JS_FALSE;
	}
	/* module_start *should* call addInfo (yep, kernel can't) */
	JSObject* target = js_addObj(" ");//you cant find me :3
	if(mod_tmp_lfun)
		JS_DefineFunctions(cx,target,mod_tmp_lfun);
	if(mod_tmp_gfun)
		JS_DefineFunctions(cx,gobj,mod_tmp_gfun);
	if(mod_tmp_lvar){
		while(mod_tmp_lvar->name){
			JS_SetProperty(cx,target,mod_tmp_lvar->name,&mod_tmp_lvar->vp);
			mod_tmp_lvar++;
		}
	}
	if(mod_tmp_gvar){
		while(mod_tmp_gvar->name){
			JS_SetProperty(cx,gobj,mod_tmp_gvar->name,&mod_tmp_gvar->vp);
			mod_tmp_gvar++;
		}
	}
	mod_tmp_lfun=NULL;
	mod_tmp_gfun=NULL;
	mod_tmp_lvar=NULL;
	mod_tmp_gvar=NULL;
	*rval = O2J(target);
	return JS_TRUE;
}
JSClass js_ModuleClass = {
    "Module",
    JSCLASS_HAS_PRIVATE | JSCLASS_NEW_ENUMERATE,
    JS_PropertyStub,    JS_PropertyStub,   JS_PropertyStub,   JS_PropertyStub,
    JS_EnumerateStub,   JS_ResolveStub,    JS_ConvertStub,    JS_FinalizeStub,
    NULL,               NULL,              NULL,              NULL,
    NULL,               NULL,              NULL,              NULL
};
static JS_FUN(Module){
	char* path = JS_GetStringBytes(JS_ValueToString(cx,argv[0]));
	int uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	int mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		printf("Error 0x%08X ", mod);
		if(mod == 0x8002012E)printf(": <%s> not found!",path);
		if(mod == 0x8002013B)printf(": <%s> already loaded/started",path);
		if(mod == 0x80020190)printf(": can't start prx : try to compile with PSPSDKlibC");
		if(mod == 0x8002013C)printf(": can't start prx : User compiled as kernel");
		printf("\n");
		return JS_FALSE;
	}
	/* module_start *should* call addInfo (yep, kernel can't) */
	JSObject* target = js_addObj(" ");//you cant find me :3
	if(mod_tmp_lfun)
		JS_DefineFunctions(cx,target,mod_tmp_lfun);
	if(mod_tmp_gfun)
		JS_DefineFunctions(cx,gobj,mod_tmp_gfun);
	if(mod_tmp_lvar){
		while(mod_tmp_lvar->name){
			JS_SetProperty(cx,target,mod_tmp_lvar->name,&mod_tmp_lvar->vp);
			mod_tmp_lvar++;
		}
	}
	if(mod_tmp_gvar){
		while(mod_tmp_gvar->name){
			JS_SetProperty(cx,gobj,mod_tmp_gvar->name,&mod_tmp_gvar->vp);
			mod_tmp_gvar++;
		}
	}
	mod_tmp_lfun=NULL;
	mod_tmp_gfun=NULL;
	mod_tmp_lvar=NULL;
	mod_tmp_gvar=NULL;
	*rval = O2J(target);
	return JS_TRUE;
}
JSBool JS_InitClasses(JSContext *cx, JSObject *obj){
	JS_InitClass(cx, obj, NULL, &js_ModuleClass, Module, 1, NULL, NULL, NULL, NULL);
	return JS_TRUE;
}