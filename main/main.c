#include <pspkernel.h>
#include <pspsyscon.h>
#include <stdio.h>
#include <stdarg.h>

#define MAIN 1

#include "shared.h"

#include "functions.h"

PSP_MODULE_INFO("JSE", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
#ifdef KERNEL
PSP_HEAP_SIZE_KB(-128);
#else
PSP_HEAP_SIZE_KB(-1024);//left 1.25MB free
#endif
static JSClass global_class = {
	"global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
	JSCLASS_NO_OPTIONAL_MEMBERS
};
JSFunctionSpec my_functions[] = {
	{"printf",js_print, 1},
	{"run",js_run, 1},
	{"exit",js_exit, 0},
	{"meminfo",js_meminfo, 0},
	{0}
};
void reportError(JSContext *cx, const char *message, JSErrorReport *report){
	if(report->filename)// error in file
		printf("\x1B[1;37;41m%s:%u:%s\x1B[0;39;109m\n",report->filename,(unsigned int) report->lineno,message);
	else// internal error
		printf("\x1B[1;37;41m%s\x1B[0;39;109m\n",message);
	sceKernelExitGame();//exit b4 bus error 8)
}
int main(int argc, const char *argv[]){
#ifdef DEBUG_MODE
	printf("\x1B[39;49mSpiderMonkey 1.8 ["__DATE__" "__TIME__"]\n");
#endif
#ifdef USE_KERNEL
	int ret;
	if(sceKernelStartModule(sceKernelLoadModule("prx/Kloader.prx", 0, NULL), 0, NULL, &ret, NULL)>0)
		printf("\x1B[31;40mKernel is available\n");
#endif
	while(1){
		JSRuntime *rt = JS_NewRuntime(14 * 1024 * 1024);// runtime
		cx = JS_NewContext(rt, 8192); // Context
		JS_SetErrorReporter(cx, reportError);//the error callback
		gobj = JS_NewObject(cx, &global_class, NULL, NULL);// Create the global object.
		JS_InitStandardClasses(cx, gobj); //Populate the global object with the standard globals (String,Object,Array...)
		JS_DefineFunctions(cx, gobj, my_functions); // Populate the global object with my_function
		JS_InitClasses(cx, gobj);//Populate the global object with the non-standard classes (Module)
		JSScript *script=JS_CompileFile(cx, gobj, argc>1?argv[1]:"js/main.js");
		jsval result;
		if(!script){
			printf("\x1B[1;37;41mCompilation error\n");
			break;
		}
		if (!JS_ExecuteScript(cx, gobj, script, &result)){
			printf("\x1B[1;37;41mExecution error\n");
			break;
		}
		//printf("returned : %08X\n",JSVAL_TO_INT(result));
		JS_MaybeGC(cx);
		JS_DestroyScript(cx, script);
		JS_DestroyContext(cx);
		JS_DestroyRuntime(rt);
	}
	JS_ShutDown();
	sceKernelExitGame();
	return 0;
}