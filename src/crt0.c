#include <pspkernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "shared.h"
#include "functions.h"

PSP_MODULE_INFO("libJS" ,PSP_MODULE_USER,1,1);
SceUID mainTh;//used on unload to avoid exeption
int sce_newlib_heap_kb_size;//defined later

int module_stop(SceSize args,void* argp){
	if(argp)puts(argp);else puts("external request");
	JS_ShutDown();
	extern int __psp_free_heap(void);
	__psp_free_heap();
	sceKernelTerminateDeleteThread(mainTh);
	if(argp){//external kill should not privide argp
		sceKernelSelfStopUnloadModule(1, 0, NULL);
		puts("error unloading");
	}
	return 0;
}
void reportError(JSContext *cx, const char *message, JSErrorReport *report){
	if(report->filename)// error in file
		printf("\x1B[1;37;41m%s:%i:%s\x1B[0;39;109m\n",report->filename,report->lineno,message);
	else// internal error
		printf("\x1B[1;37;41m%s\x1B[0;39;109m\n",message);
	module_stop(0,"script error");//exit b4 bus error 8)
}
int _start(SceSize args,void* argp){
//set argv
	char *argv[16+1];
	int argc=0,i=0;
	while((i+=strlen(argv[argc++]=&((char*)argp)[i])+1)<args);
	if(argc<2)module_stop(0,"libjs script.js 1024");
//	for(i=0;argv[i]+1;i++)
//		printf("argv[%i] : %s\n",i,argv[i]);
//set path
	char cwd[64];
	memcpy(cwd,argv[0]+1?argv[0]:"ms0:/",64);
	for(i=strlen(cwd);i>0;i--)
		if(cwd[i]=='/'){cwd[i+1]=0;break;}
	if(sceIoChdir(cwd))puts("error in cwd");
//init env{1:script,2:HEAP_SIZE_KB}
	sce_newlib_heap_kb_size=argv[2]+1?atoi(argv[2]):1024;//arg2 = HEAP
	//printf("cwd :%s\n",cwd);
	//printf("heap:%i\n",sce_newlib_heap_kb_size);
	//printf("file:%s\n",argv[1]+1?argv[1]:"main.js");
//main
	do{
		JSRuntime *rt = JS_NewRuntime(sce_newlib_heap_kb_size*1024);// runtime
		cx = JS_NewContext(rt, 8192); // Context
		JS_SetErrorReporter(cx, reportError);//the error callback
		static JSClass global_class={"global",JSCLASS_GLOBAL_FLAGS,JSCLASS_DEFAULT_MANDATORY_MEMBERS, JSCLASS_NO_OPTIONAL_MEMBERS};
		gobj = JS_NewObject(cx, &global_class, NULL, NULL);// Create the global object.
		
		JS_InitStandardClasses(cx, gobj); //Populate the global object with the standard globals (String,Object,Array...)
		JS_InitClasses(cx, gobj);//Populate the global object with the non-standard classes (Module)
		JS_InitObjs(cx,gobj);
		JSFunctionSpec my_functions[] = {
			{"print",js_print, 1},
			{"printf",js_print, 1},
			{"run",js_run, 1},
			{"delay",js_delay, 1},
			{"exit",js_exit, 0},
			{0}
		};
		JS_DefineFunctions(cx, gobj, my_functions); // Populate the global object with my_function
		JSScript *script=JS_CompileFile(cx, gobj,argv[1]+1?argv[1]:"main.js");
		if(!script){
			printf("\x1B[1;37;41mCompilation error\n");
			break;
		}
		jsval result;
		if (!JS_ExecuteScript(cx, gobj, script, &result)){
			printf("\x1B[1;37;41mExecution error\n");
			break;
		}
		//printf("returned : %08X\n",JSVAL_TO_INT(result));
		JS_MaybeGC(cx);
		JS_DestroyScript(cx, script);
		JS_DestroyContext(cx);
		JS_DestroyRuntime(rt);
	}while(0);
	module_stop(0,"end of main");//exit
	return 0;
}
int module_start(SceSize args,void* argp){
	mainTh = sceKernelCreateThread("JSE", _start, 0x18, 0x10000, PSP_THREAD_ATTR_VFPU, NULL);
	return sceKernelStartThread(mainTh, args, argp);
}
