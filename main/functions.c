#include <pspkernel.h>
#include <string.h>
#include <stdio.h>
#include "src/jsapi.h"
#include "src/jsarray.h"

#include "shared.h"
#include "boot.h"

/* my custom functions */

JS_FUN(js_print){
	printf("\x1B[1;37;40m%s\x1B[0;39;49m",J2S(argv[0]));
	return JS_TRUE;
}
JS_FUN(js_exit){
#ifdef DEBUG_MODE
	printf("\x1B[0;39;49mexiting ...\n");
#endif
	sceKernelExitGame();
	return JS_TRUE;
}
extern KmodInfo js_addKModule();
JS_FUN(js_meminfo){
	js_setProperty(obj,"data",I2J(cx->runtime->gcBytes));//used to execute
	js_setProperty(obj,"dataMax",I2J(cx->runtime->gcMaxBytes));
	js_setProperty(obj,"text",I2J(cx->runtime->gcMallocBytes));//used to store ressource
	js_setProperty(obj,"textMax",I2J(cx->runtime->gcMaxMallocBytes));
	*rval=O2J(obj);
  return JS_TRUE;
}
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
u32 fun2nid(char* fun){
	u32 nid = 0xFFFFFFFF;
	u8 digest[20];
	if(sceKernelUtilsSha1Digest((u8*)fun, strlen(fun), digest) >= 0)
		nid = digest[0] | (digest[1] << 8) | (digest[2] << 16) | (digest[3] << 24);
	return nid;
}
extern u32 js_searchInfo(KfindProc);
u32 getKinfo(char* name){
	name[strrchr(name,'.')-name]=0;//module&librairie name
	printf("hook %s :",name);
	char fun[80];
	KfindProc chaine;
	strncpy(chaine.mod,name,80);
	strncpy(chaine.lib,name,80);
	sprintf(fun,"%s_addModule",name);
	chaine.nid=fun2nid(fun);
	u32 addr = js_searchInfo(chaine);
	if(addr){
		//u32 (*fun)() = (void*)addr;
		printf(" 0x%08X !\n",addr);
		return addr;
	}
	printf(" not found !\n");
	return 0;
}
JS_FUN(js_include){
	char* path = J2S(argv[0]);
	u32 uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	u32 mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	
	if(mod != uid){
		if(mod == 0x8002013B)return JS_TRUE;//printf(": <%s> already loaded/started",path);
		printf("\x1B[1;37;41mModule error 0x%08X \n", mod);
		//if(mod == 0x8002012E)printf(": <%s> not found!",path);
		//if(mod == 0x80020190)printf(": can't start prx : try to compile with PSPSDKlibC");
		//if(mod == 0x8002013C)printf(": can't start prx : User compiled as kernel");
		return JS_FALSE;
	}
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
	js_setProperty(obj,"UID",I2J(mod));
	js_setProperty(obj,"path",argv[0]);
	mod_tmp_lfun=NULL;
	mod_tmp_gfun=NULL;
	mod_tmp_lvar=NULL;
	mod_tmp_gvar=NULL;
#ifdef DEBUG_MODE
	printf("\x1B[33;40mLoad/Start host0:/%s UID: 0x%08X @OBJ: 0x%08X\n",J2S(argv[0]),mod,(u32)obj);
#endif
  return JS_TRUE;
}
JS_FUN(js_kinclude){
	char* path = J2S(argv[0]);
	u32 uid = sceKernelLoadModule(path, 0, NULL);
	int ret = 0;
	u32 mod = sceKernelStartModule(uid, 0, NULL, &ret, NULL);
	if(mod != uid){
		printf("\x1B[1;37;41mModule error 0x%08X \n", mod);
		return JS_FALSE;
	}
//	extern int my_addModule();
//	if(getKinfo(strrchr(path,'/')+1))
//		printf("my_addModule (ret:%i)\n",my_addModule());
	js_setProperty(obj,"UID",I2J(mod));
	js_setProperty(obj,"path",argv[0]);
#ifdef DEBUG_MODE
	printf("\x1B[33;40mLoad/Start (kernel) host0:/%s UID: 0x%08X @OBJ: 0x%08X\n",J2S(argv[0]),mod,(u32)obj);
#endif
  return JS_TRUE;
}
extern int KCall(u32 uid,u32 nid,u32 arg);
JS_METH(js_kcall){
	if(JSVAL_IS_STRING(ARGV[0]))
		*(vp) = I2J(KCall(J2U(js_getProperty((JSObject*)THIS,"UID")),fun2nid(J2S(ARGV[0])),J2U(ARGV[1])));
	if(JSVAL_IS_NUMBER(ARGV[0]))
		*(vp) = I2J(KCall(J2U(js_getProperty((JSObject*)THIS,"UID")),J2U(ARGV[0]),J2U(ARGV[1])));
  return JS_TRUE;
}
JS_METH(js_exclude){
	int ret=0;
	js_callFunctionName(J2O(ARGV[-1]),"_unload",0,NULL);
#ifdef DEBUG_MODE
	printf("\x1B[33;40mStop/Unload %s : %i %08X\n",J2S(js_getProperty(J2O(ARGV[-1]),"path")),ret,sceKernelStopModule(J2I(js_getProperty(J2O(ARGV[-1]),"UID")),0,NULL,&ret,NULL));
#else
	sceKernelStopModule(J2I(js_getProperty(J2O(ARGV[-1]),"UID")), 0, NULL, &ret, NULL)
#endif
	sceKernelUnloadModule(J2I(js_getProperty(J2O(ARGV[-1]),"UID")));
	*(vp) = I2J(ret);
	return JS_TRUE;
}
static JSFunctionSpec ModuleMethodes[] = {
	JS_FN("unload",js_exclude,0,0,0),
	JS_FS_END
};
static JSFunctionSpec KModuleMethodes[] = {
	JS_FN("call",js_kcall,0,0,0),
	JS_FS_END
};
JSBool JS_InitClasses(JSContext *cx, JSObject *obj){
	js_addClass(
		NULL,NULL,js_include,1,
		NULL,ModuleMethodes,NULL,NULL,
		"Module",JSCLASS_NEW_RESOLVE,
		JSCLASS_NO_MANDATORY_MEMBERS,
		JSCLASS_NO_OPTIONAL_MEMBERS
	);
	if(kMode)
	js_addClass(
		NULL,NULL,js_kinclude,1,
		NULL,KModuleMethodes,NULL,NULL,
		"KModule",JSCLASS_NEW_RESOLVE,
		JSCLASS_NO_MANDATORY_MEMBERS,
		JSCLASS_NO_OPTIONAL_MEMBERS
	);
	return JS_TRUE;
}

JSBool JS_InitObjs(JSContext *cx, JSObject *obj){
#ifdef _PSP_FW_VERSION
	JSObject* psp = JS_DefineObject(cx,obj,"PSP",0,NULL,JSPROP_ENUMERATE);
	JS_DefineFunction(cx,psp,"meminfo",js_meminfo,0,0);
	js_setProperty(psp,"ok",I2J(2000));
#endif
	return JS_TRUE;
}