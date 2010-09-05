#include <pspkernel.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

#include <../src/jsapi.h>

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
	printf("test:%08X\n",in);
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
JSObject* js_addClass(JSObject *obj,JSObject *parent_proto,JSNative constructor,uintN nargs,JSPropertySpec *ps,JSFunctionSpec *fs,JSPropertySpec *static_ps,JSFunctionSpec *static_fs,char *name,uint32 flags,JSPropertyOp addProperty,JSPropertyOp delProperty,JSPropertyOp getProperty,JSPropertyOp setProperty,JSEnumerateOp enumerate,JSResolveOp resolve,JSConvertOp convert,JSFinalizeOp finalize,JSGetObjectOps getObjectOps,JSCheckAccessOp checkAccess,JSNative call,JSNative construct,JSXDRObjectOp xdrObject,JSHasInstanceOp hasInstance,JSMarkOp mark,JSReserveSlotsOp reserveSlots){
	printf("adding class : %s\n",name);
	JSClass* tmpClass = JS_malloc(cx,sizeof(JSClass));
	tmpClass->name=name;
  tmpClass->flags=flags;

	if(addProperty) tmpClass->addProperty=addProperty; else tmpClass->addProperty=JS_PropertyStub;
	if(delProperty) tmpClass->delProperty=delProperty; else tmpClass->delProperty=JS_PropertyStub;
	if(getProperty) tmpClass->getProperty=getProperty; else tmpClass->getProperty=JS_PropertyStub;
	if(setProperty) tmpClass->setProperty=setProperty; else tmpClass->setProperty=JS_PropertyStub;
	
	if(enumerate  ) tmpClass->enumerate=enumerate;     else tmpClass->enumerate=JS_EnumerateStub;
	if(resolve    ) tmpClass->resolve=resolve;         else tmpClass->resolve=JS_ResolveStub;
	if(convert    ) tmpClass->convert=convert;         else tmpClass->convert=JS_ConvertStub;
	if(finalize   ) tmpClass->finalize=finalize;       else tmpClass->finalize=JS_FinalizeStub;
	
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
JSObject* js_addObj(const char* name){
	return JS_DefineObject(cx,gobj,name,0,NULL,JSPROP_ENUMERATE);
	//printf("js_addObj:%i\n",JS_DefineProperty(cx, obj, "param", INT_TO_JSVAL((int)111), NULL, NULL, JSPROP_ENUMERATE));
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
JSString* js_valueToString(jsval str){
	return JS_ValueToString(cx,str);
}
u16 js_valueToUint16(jsval v){
	u16 u;
	JS_ValueToUint16(cx,v,&u);
	return u;
}
u32 js_valueToECMAUint32(jsval v){
	u32 u;
	JS_ValueToECMAUint32(cx,v,&u);
	return u;
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
JSType js_typeOfValue(jsval v){
	return JS_TypeOfValue(cx,v);
}
jsval js_computeThis(JSContext *cx, jsval *vp){
	return JS_ComputeThis(cx,vp);
}
/* C stuff (handled by SM) */
char* js_strdup(const char* str){
	return JS_strdup(cx,str);
}
void* js_malloc(size_t nbytes){
	void* p = JS_malloc(cx,nbytes);
	//printf("malloc %i bytes at [%08X|%08X]\n",nbytes,(int)p,(int)p+nbytes);
	return p;
}
void* js_realloc(void *p,size_t nbytes){
	return JS_realloc(cx,p,nbytes);
}
void js_free(void *p){
	//printf("free at %08X\n",(int)p);
	JS_free(cx,p);
}
/* real C stuff (if you don't want use libc in your prx) */
u32 c_addModule(const char *mod){
	int ret=0;
	u32 uid = sceKernelLoadModule(mod,0,NULL);
	sceKernelStartModule(uid,0,NULL,&ret,NULL);
	return uid;
}
int c_delModule(u32 uid){
	int ret=0;
	sceKernelStopModule(uid,0,NULL,&ret,NULL);
	sceKernelUnloadModule(uid);
	return ret?uid:ret;
}
size_t c_strlen(char *str){
	return strlen(str);
}
void* c_memalign(size_t blocksize, size_t bytes){
	return memalign(blocksize,bytes);
}
