#include <pspkernel.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

#include <../src/jsapi.h>
#include <../src/jsstr.h>
#include <../src/jsgc.h>

/* exported variables */

JSContext *cx;
JSObject *gobj;

JSContext* js_getContext(void){
	return cx;
}
JSObject* js_getGlobalObject(void){
	return gobj;
}
/* exported functions */
int js_test(int in){
#ifdef DEBUG_MODE
	printf("%08X\n",in);
#endif
	return in;
}
typedef struct JSPropertiesSpec{
    const char      *name;
    jsval           vp;
}JSPropertiesSpec;
/* bridge beetwen module_start and js_include */
JSFunctionSpec* mod_tmp_lfun;
JSFunctionSpec* mod_tmp_gfun;
JSPropertiesSpec* mod_tmp_lvar;
JSPropertiesSpec* mod_tmp_gvar;
void js_addModule(JSFunctionSpec* lfun,JSFunctionSpec* gfun,JSPropertiesSpec* lvar,JSPropertiesSpec* gvar){
	mod_tmp_lfun=lfun;
	mod_tmp_gfun=gfun;
	mod_tmp_lvar=lvar;
	mod_tmp_gvar=gvar;
}
JSObject* js_addClass(JSObject *obj,JSObject *parent_proto,JSNative constructor,uintN nargs,JSPropertySpec *ps,JSFunctionSpec *fs,JSPropertySpec *static_ps,JSFunctionSpec *static_fs,char *name,uint32 flags,JSPropertyOp addProperty,JSPropertyOp delProperty,JSPropertyOp getProperty,JSPropertyOp setProperty,JSEnumerateOp enumerate,JSResolveOp resolve,JSConvertOp convert,JSFinalizeOp finalize,JSGetObjectOps getObjectOps,JSCheckAccessOp checkAccess,JSNative call,JSNative construct,JSXDRObjectOp xdrObject,JSHasInstanceOp hasInstance,JSMarkOp mark,JSReserveSlotsOp reserveSlots,JSClass** outClass){
#ifdef DEBUG_MODE
	printf("adding class : %s\n",name);
#endif
	JSClass*tmpClass = JS_malloc(cx,sizeof(JSClass));
	if(outClass)*outClass=tmpClass;
	//else{printf("no class specified\n");}
	tmpClass->name=name;
  tmpClass->flags=flags;

	tmpClass->addProperty=(addProperty)?addProperty:JS_PropertyStub;
	tmpClass->delProperty=(delProperty)?delProperty:JS_PropertyStub;
	tmpClass->getProperty=(getProperty)?getProperty:JS_PropertyStub;
	tmpClass->setProperty=(setProperty)?setProperty:JS_PropertyStub;
	
	tmpClass->enumerate=(enumerate)?enumerate:JS_EnumerateStub;
	tmpClass->resolve=(resolve)?resolve:JS_ResolveStub;
	tmpClass->convert=(convert)?convert:JS_ConvertStub;
	tmpClass->finalize=(finalize)?finalize:JS_FinalizeStub;
	
	tmpClass->getObjectOps=getObjectOps;
	tmpClass->checkAccess=checkAccess;
	tmpClass->call=call;
	tmpClass->construct=construct;
	tmpClass->xdrObject=xdrObject;
	tmpClass->hasInstance=hasInstance;
	tmpClass->mark=mark;
	tmpClass->reserveSlots=reserveSlots;
	
	return JS_InitClass(cx, obj?obj:gobj, parent_proto, tmpClass, constructor, nargs, ps, fs, static_ps, static_fs);
}
JSBool js_convertArguments(uintN argc, jsval *argv, const char *format, ...){
	va_list ap;
	va_start(ap, format);
	JSBool ok = JS_ConvertArgumentsVA(cx, argc, argv, format, ap);
	va_end(ap);
	return ok;
}
JSObject* js_newObject(JSClass *clasp, JSObject *proto,JSObject *parent){
	return JS_NewObject(cx,clasp,proto,parent);
}
JSObject* js_addObj(const char* name,JSObject*obj){
	return JS_DefineObject(cx,obj?obj:gobj,name,0,NULL,JSPROP_ENUMERATE);
}
jsval js_getElement(JSObject *tobj,int index){
	jsval vp;
	JS_GetElement(cx,tobj,(jsint)index,&vp);
	return vp;
}
jsval js_getProperty(JSObject *tobj,const char* name){
	if(!tobj)tobj=gobj;
	jsval vp;
	JS_GetProperty(cx,tobj,name,&vp);
	return vp;
}
JSBool js_setProperty(JSObject *tobj,const char* name, jsval vp){
	if(!tobj)tobj=gobj;
	return JS_SetProperty(cx,tobj,name,&vp);
}
JSBool js_delProperty(JSObject *tobj,const char* name){
	if(!tobj)tobj=gobj;
	return JS_DeleteProperty(cx,tobj,name);
}
jsdouble js_valueToNumber(jsval v){
	jsdouble dp;
	JS_ValueToNumber(cx,v,&dp);
	return dp;
}
jsval js_numberToValue(jsdouble d){
	jsval val;
	JS_NewNumberValue(cx,d, &val);
	return val;
}
char* js_getStringBytes(JSString* str){
	return JS_GetStringBytes(str);
}
jsval js_convertValue(jsval v,JSType type){
	jsval dp;
	JS_ConvertValue(cx,v,type,&dp);
	return dp;
}
size_t js_getStringLength(JSString *str){
	return JS_GetStringLength(str);
}
JSString* js_newString(char* str,size_t size){
	if(size)
		return JS_NewString(cx,str,size);
	return JS_NewString(cx,str,strlen(str));
}
JSString* js_newBlob(jschar* chars,size_t length){
    
		//JSString *str = (JSString *) js_NewGCThing(cx, GCX_STRING, sizeof(JSString));
    //if(str)JSFLATSTR_INIT(str, chars, length);
		//return str;
	return JS_NewUCString(cx,chars,length);
}
JSString* js_valueToString(jsval str){
	return JS_ValueToString(cx,str);
}
u16 js_valueToUint16(jsval v){
	u16 u;
	JS_ValueToUint16(cx,v,&u);
	return u;
}
u32 js_valueToECMAUint32(jsval v){
	if (JSVAL_IS_INT(v)) {
		//printf("J2U (int:%08X)\n",JSVAL_TO_INT(v));
		return (uint32) JSVAL_TO_INT(v);
	}
	if (JSVAL_IS_DOUBLE(v)) {
		//jsdouble d = ;
		//unsigned t = d;
		//printf("J2U (dbl:%08X)\n",t);
		return *JSVAL_TO_DOUBLE(v);
	}
	return 0;
}
JSObject* js_valueToObject(jsval v){
//JSObject** js_valueToObject(jsval v,JSObject** tobj){
//js_ValueToObject(cx, v,tobj);
//return tobj
	
	return JSVAL_TO_OBJECT(v);
}
jsval js_evaluateScript(char* eval){
	jsval rval;
	uintN lineno = 0;
	JS_EvaluateScript(cx,gobj,eval,strlen(eval),"",lineno, &rval);
	return rval;
}
jsval js_callFunctionName(JSObject *obj,const char* name,uintN argc,jsval *argv){
	if(!obj)obj=gobj;
	JSBool haz;
	JS_HasProperty(cx,obj,"_unload",&haz);
	if(!haz)return JS_TRUE;
	jsval rval;
	JS_CallFunctionName(cx,obj,name,argc,argv,&rval);
	return rval;
}
JSType js_typeOfValue(jsval v){
	return JS_TypeOfValue(cx,v);
}
jsval js_computeThis(JSContext *cx, jsval *vp){
	return JS_ComputeThis(cx,vp);
}
JSBool js_defineFunctions(JSFunctionSpec *fs,JSObject *obj){
	return JS_DefineFunctions(cx,obj?obj:gobj,fs);
}
JSFunction * js_defineFunction(JSObject *obj,const char *name, JSNative call, uintN nargs, uintN flags){
	return JS_DefineFunction(cx,obj,name,call,nargs,flags);
}
/* C stuff (handled by SM) */
char* js_strdup(const char* str){
	return JS_strdup(cx,str);
}
void* js_malloc(size_t nbytes){
	void* p = JS_malloc(cx,nbytes);
#ifdef DEBUG_MODE
	printf("Jalloc 0x%08X (%i bytes)\n",(int)p,nbytes);
#endif
	return p;
}
void js_free(void *p){
#ifdef DEBUG_MODE
	printf("Jfree   0x%08X\n",(int)p);
#endif
	JS_free(cx,p);
}
void* js_realloc(void *p,size_t nbytes){
#ifdef DEBUG_MODE
	printf("Jrealloc 0x%08X (to %i bytes)\n",(int)p,nbytes);
#endif
	return JS_realloc(cx,p,nbytes);
}
/* real C stuff (if you don't want use libc in your prx) */
u32 c_addModule(const char *mod){
	int ret=0;
	u32 uid = sceKernelLoadModule(mod,0,NULL);
	int start = sceKernelStartModule(uid,0,NULL,&ret,NULL);
#ifdef DEBUG_MODE
	printf("Load/Start %s UID: 0x%08X (%08X)\n",mod,uid,start);
#endif
	return uid;
}
int c_delModule(u32 uid){
	int ret=0;
#ifdef DEBUG_MODE
	printf("Stop/Unload UID:%08X 0x%08X ",uid,sceKernelStopModule(uid,0,NULL,&ret,NULL));
	printf("0x%08X, %i\n",sceKernelUnloadModule(uid),ret);
#else
	sceKernelStopModule(uid,0,NULL,&ret,NULL);
	sceKernelUnloadModule(uid);
#endif
	return ret?uid:ret;
}
size_t c_strlen(char *str){
	return strlen(str);
}
void* c_malloc(size_t nbytes){
#ifdef USE_PARTITION
	if(!nbytes || nbytes>sceKernelMaxFreeMemSize())return NULL;
	SceUID part = sceKernelAllocPartitionMemory(2, "mem", PSP_SMEM_Low, nbytes+sizeof(SceUID), NULL);
	u32* ptr = (u32*)sceKernelGetBlockHeadAddr(part);
#ifdef DEBUG_MODE
	printf("MALLOC UID:%08X p:%p size:%08X\n",part,ptr,nbytes);
#endif
	ptr[0] = part;
	return &ptr[1];
#else
	void* p = malloc(nbytes);
#ifdef DEBUG_MODE
	printf("malloc 0x%08X (%i bytes)\n",(int)p,nbytes);
#endif
	return p;
#endif
}
void* c_memalign(size_t blocksize, size_t bytes){
#ifdef DEBUG_MODE
	printf("memalign size:%08X align:%i\n",bytes,blocksize);
#endif
#ifdef USE_PARTITION
	return c_malloc(bytes);
#else
	return memalign(blocksize,bytes);
#endif
}
void c_free(void *p){
#ifdef USE_PARTITION
	if((u32)p<0x08800000)return;//printf("free : invalid argument");
	sceKernelFreePartitionMemory(((u32*)p)[-1]);
#ifdef DEBUG_MODE
	printf("FREE UID:%08X p:%p\n",((u32*)p)[-1],p-4);
#endif
#else
#ifdef DEBUG_MODE
	printf("free   0x%08X\n",(int)p);
#endif
	free(p);
#endif
}
void* c_realloc(void *p,size_t nbytes){
#ifdef USE_PARTITION
#ifdef DEBUG_MODE
	printf("REALLOC p:%p size:%08X\n",p,nbytes);
#endif
	if((size_t)p<0x08800000)return malloc(nbytes);
	if(!nbytes){free(p);return NULL;}
	void* dst = malloc(nbytes);
	if(!dst)return NULL;
	memcpy(dst,p,nbytes);
	free(p);
	return dst;
#else
#ifdef DEBUG_MODE
	printf("realloc 0x%08X (to %i bytes)\n",(int)p,nbytes);
#endif
	return realloc(p,nbytes);
#endif
}

