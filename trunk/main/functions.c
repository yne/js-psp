#include <pspkernel.h>
#include <string.h>
#include <stdio.h>
#include "src/jsapi.h"
#include "src/jsarray.h"

#include "shared.h"

/* my custom functions */

JS_FUN(js_print){
	printf(J2S(argv[0]));
	return JS_TRUE;
}
extern int Kfun();
extern JSFunctionSpec* modK_GetFun();
extern JSPropertiesSpec* modK_GetVar();

JS_FUN(js_run){
	JSScript *script=JS_CompileFile(cx, gobj, J2S(argv[0]));
	jsval result;
	*rval=I2J(0);//if no error occure, run return 0
	if(!script){
		*rval=I2J(-1);//return -1 on a compilation error (bad path etc...)
		return JS_TRUE;
	}
	if(!JS_ExecuteScript(cx, gobj, script, &result))
		*rval=I2J(-2);//return -2 on a execution error
	JS_MaybeGC(cx);
	JS_DestroyScript(cx, script);
  return JS_TRUE;
}
JS_FUN(js_include){
	char* path = J2S(argv[0]);
	u32 uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	u32 mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		printf("Error 0x%08X ", mod);
		if(mod == 0x8002012E)printf(": <%s> not found!",path);
		if(mod == 0x8002013B)printf(": <%s> already loaded/started",path);
		if(mod == 0x80020190)printf(": can't start prx : try to compile with PSPSDKlibC");
		if(mod == 0x8002013C)printf(": can't start prx : User compiled as kernel");
		printf("\n");
		return JS_FALSE;
	}
	if(obj!=gobj){
		// module_start *should* call addInfo (yep, kernel can't) //
		if(mod_tmp_lfun)
			JS_DefineFunctions(cx,obj,mod_tmp_lfun);
		if(mod_tmp_gfun)
			JS_DefineFunctions(cx,gobj,mod_tmp_gfun);
		if(mod_tmp_lvar){
			while(mod_tmp_lvar->name){
				JS_SetProperty(cx,obj,mod_tmp_lvar->name,&mod_tmp_lvar->vp);
				mod_tmp_lvar++;
			}
		}
		if(mod_tmp_gvar){
			while(mod_tmp_gvar->name){
				JS_SetProperty(cx,gobj,mod_tmp_gvar->name,&mod_tmp_gvar->vp);
				mod_tmp_gvar++;
			}
		}
	}
	js_setProperty(obj,"UID",I2J(mod));
	js_setProperty(obj,"path",argv[0]);
	mod_tmp_lfun=NULL;
	mod_tmp_gfun=NULL;
	mod_tmp_lvar=NULL;
	mod_tmp_gvar=NULL;
	printf("Load/Start host0:/%s UID: 0x%08X @OBJ: 0x%08X\n",J2S(argv[0]),mod,(u32)obj);	/**/
  return JS_TRUE;
}
JSBool JS_InitClasses(JSContext *cx, JSObject *obj){
	js_addClass(
		NULL,NULL,js_include,1,
		NULL,NULL,NULL,NULL,
		"Module",JSCLASS_NEW_RESOLVE,
		JSCLASS_NO_MANDATORY_MEMBERS,
		JSCLASS_NO_OPTIONAL_MEMBERS
	);
	return JS_TRUE;
}