#include "src/jsapi.h"
#include "src/jscntxt.h"

/*from JSVAL*/
#define J2I(j) JSVAL_TO_INT(j)
#define J2S(j) js_getStringBytes(js_valueToString(j))
#define J2U(j) js_valueToECMAUint32(j)
#define J2u(j) js_valueToUint16(j)
#define J2O(j) JSVAL_TO_OBJECT(j)//(j,op) js_valueToObject(j,op)
#define J2L(j) js_valueToNumber(j)
#define J2D(j) js_valueToNumber(j)
/*to JSVAL*/
#define I2J(i) INT_TO_JSVAL(i)
#define D2J(i) js_numberToValue(i)
#define O2J(i) OBJECT_TO_JSVAL(i)
#define S2J(i) STRING_TO_JSVAL(js_newString((i),0))

/* for methode prupose */
#define THIS   js_computeThis(cx, vp)
#define ARGV   ((vp)+2)

#define UNDEFINED 0xC0000000
#define JS_FUN(fun_name) JSBool fun_name (JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
#define JS_METH(meth_name) static JSBool meth_name (JSContext *cx, uintN argc, jsval *vp)

#define JSCLASS_NO_MANDATORY_MEMBERS 0,0,0,0,0,0,0,0

#ifndef __JS_SHARED_H__
#define __JS_SHARED_H__

typedef struct JSPropertiesSpec {
    const char      *name;
    jsval           vp;
}JSPropertiesSpec;

typedef struct KmodInfo{
	JSFunctionSpec* lfun;
	JSFunctionSpec* gfun;
	JSPropertiesSpec* lvar;
	JSPropertiesSpec* gvar;
}KmodInfo;

typedef struct kfindproc {
	char mod[80];
	char lib[80];
	unsigned nid;
}KfindProc;

#ifdef MAIN
#define EXT  
#else
#define EXT extern
#endif

/* variables hosted by the interpreter */
JSContext *cx;
JSObject *gobj;

JSFunctionSpec* mod_tmp_lfun;
JSFunctionSpec* mod_tmp_gfun;
JSPropertiesSpec* mod_tmp_lvar;
JSPropertiesSpec* mod_tmp_gvar;

/* functions hosted by the interpreter */

EXT int js_test(int);
EXT JSObject* js_addClass(JSObject *obj,JSObject *parent_proto,JSNative constructor,uintN nargs,JSPropertySpec *ps,JSFunctionSpec *fs,JSPropertySpec *static_ps,JSFunctionSpec *static_fs,char *name,uint32 flags,JSPropertyOp addProperty,JSPropertyOp delProperty,JSPropertyOp getProperty,JSPropertyOp setProperty,JSEnumerateOp enumerate,JSResolveOp resolve,JSConvertOp convert,JSFinalizeOp finalize,JSGetObjectOps getObjectOps,JSCheckAccessOp checkAccess,JSNative call,JSNative construct,JSXDRObjectOp xdrObject,JSHasInstanceOp hasInstance,JSMarkOp mark,JSReserveSlotsOp reserveSlots);
EXT void js_addModule(JSFunctionSpec* lfun,JSFunctionSpec* gfun,JSPropertiesSpec* lvar,JSPropertiesSpec* gvar);
EXT JSObject* js_addObj(const char*);
EXT JSContext* js_getContext(void);
EXT JSObject* js_getGlobalObject(void);
EXT JSBool js_convertArguments(uintN, jsval*, const char *, ...);
EXT jsval js_getElement(JSObject *tobj,int index);
EXT jsval js_getProperty(JSObject *tobj,const char* name);
EXT JSBool js_setProperty(JSObject *tobj,const char* name, jsval);
EXT JSBool js_delProperty(JSObject *tobj,const char* name);
EXT jsval js_convertValue(jsval v,JSType type);
EXT char* js_getStringBytes(JSString* str);
EXT size_t js_getStringLength(JSString *str);
EXT JSString* js_newString(char* str,size_t size);
EXT JSObject** js_valueToObject(jsval v,JSObject** tobj);
EXT JSString* js_valueToString(jsval v);
EXT u32 js_valueToECMAUint32(jsval v);
EXT u16 js_valueToUint16(jsval v);
EXT jsdouble js_valueToNumber(jsval v);
EXT jsval js_numberToValue(jsdouble d);
EXT jsval js_evaluateScript(char* eval);
EXT jsval js_callFunctionName(JSObject *obj,const char* name,uintN argc,jsval *argv);
EXT JSType js_typeOfValue(jsval v);
EXT jsval js_computeThis(JSContext *cx, jsval *vp);

EXT char* js_strdup(const char* str);
EXT void* js_malloc(size_t nbytes);
EXT void* js_realloc(void *p,size_t nbytes);
EXT void js_free(void *p);

EXT u32 c_addModule(const char *mod);
EXT int c_delModule(u32 uid);
EXT size_t c_strlen(const char *str);
EXT void* c_memalign(size_t blocksize, size_t bytes);

#endif
