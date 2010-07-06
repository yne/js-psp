#include <pspkernel.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "src/jsapi.h"
#include "src/jsarray.h"

PSP_MODULE_INFO("main", 0, 1, 1);
//PSP_HEAP_SIZE_KB(-1);//left 253kB free (not enought)
PSP_HEAP_SIZE_KB(-1024);//left 1.25MB free

JSContext *cx;
JSObject *gobj;

/* my custom functions */
JSBool js_print(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
	const char *msg;
	if (!JS_ConvertArguments(cx, argc, argv, "s", &msg))
		return JS_FALSE;
	printf(msg);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
/* js functions */
static JSFunctionSpec my_functions[] = {
	{"printf",js_print, 1},
	{0}
};
/* The class of the global object. */
static JSClass global_class = {
	"global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
	JSCLASS_NO_OPTIONAL_MEMBERS
};
int main(int argc, const char *argv[]){
	JSRuntime *rt = JS_NewRuntime(8L * 1024L * 1024L);// runtime
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
		printf("returned : %08X\n",JSVAL_TO_INT(result));
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