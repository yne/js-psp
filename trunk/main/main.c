#include <pspkernel.h>
#include <pspsyscon.h>
#include <stdio.h>
#include <stdarg.h>

#define MAIN 1

#include "shared.h"

#include "functions.h"

PSP_MODULE_INFO("JSE", 0, 1, 1);
//PSP_HEAP_SIZE_KB(-1);//left 253kB free (not enought)
PSP_HEAP_SIZE_KB(-1024);//left 1.25MB free

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
		printf("%s:%u:%s\n",report->filename,(unsigned int) report->lineno,message);
	else// internal error
		printf("%s\n",message);
	sceKernelExitGame();//exit b4 bus error 8)
}
int main(int argc, const char *argv[]){
	int ret;
	sceKernelStartModule(sceKernelLoadModule("prx/Kloader.prx", 0, NULL), 0, NULL, &ret, NULL);
	while(1){
		JSRuntime *rt = JS_NewRuntime(16 * 1024 * 1024);// runtime
		cx = JS_NewContext(rt, 8192); // Context
		JS_SetErrorReporter(cx, reportError);//the error callback
		gobj = JS_NewObject(cx, &global_class, NULL, NULL);// Create the global object.
		JS_InitStandardClasses(cx, gobj); //Populate the global object with the standard globals (String,Object,Array...)
		JS_DefineFunctions(cx, gobj, my_functions); // Populate the global object with my_function
		JS_InitClasses(cx, gobj);//Populate the global object with the non-standard classes (Module)
		JSScript *script=JS_CompileFile(cx, gobj, argc>1?argv[1]:"js/main.js");
		jsval result;
		if(!script){
			printf("Compilation error\n");
			break;
		}
		if (!JS_ExecuteScript(cx, gobj, script, &result)){
			printf("Execution error\n");
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