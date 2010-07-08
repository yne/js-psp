#include <pspkernel.h>
#include <stdio.h>
#include <stdarg.h>
#include "src/jsapi.h"
#include "src/jsarray.h"

#include "functions.h"

PSP_MODULE_INFO("JSE", 0, 1, 1);
//PSP_HEAP_SIZE_KB(-1);//left 253kB free (not enought)
PSP_HEAP_SIZE_KB(-1024);//left 1.25MB free

JSContext *cx;
JSObject *gobj;

/* The class of the global object. */

int js_test(int in){
	return in*3;
}
static JSClass global_class = {
	"global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
	JSCLASS_NO_OPTIONAL_MEMBERS
};
JSFunctionSpec my_functions[] = {
	{"printf",js_print, 1},
	{"include",js_include, 1},
	{0}
};
int main(int argc, const char *argv[]){
	JSRuntime *rt = JS_NewRuntime(8 * 1024 * 1024);// runtime
	cx = JS_NewContext(rt, 8192); // Context
	gobj = JS_NewObject(cx, &global_class, NULL, NULL);// Create the global object.
	JS_InitStandardClasses(cx, gobj); //Populate the global object with the standard globals (String,Object,Array...)
	JS_DefineFunctions(cx, gobj, my_functions); // Populate the global object with my_function
	JSScript *script = JS_CompileFile(cx, gobj, "js/main.js");
	jsval result;
	while(1){
		if(!script){
			printf("Compilation error\n");
			break;
		}
		if (!JS_ExecuteScript(cx, gobj, script, &result)){
			printf("Execution error\n");
			break;
		}
		//printf("returned : %08X\n",JSVAL_TO_INT(result));
		break;
	}
	JS_MaybeGC(cx);
	JS_DestroyScript(cx, script);
	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
	sceKernelExitGame();
	return 0;
}