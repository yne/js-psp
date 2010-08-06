#include "src/jsapi.h"

/*from JSVAL*/
#define J2I(j) JSVAL_TO_INT(j)
#define J2S(j) js_getStringBytes(js_valueToString(j))
#define J2U(j) js_valueToECMAUint32(j)
#define J2u(j) js_valueToUint16(j)
#define J2O(j) JSVAL_TO_OBJECT(j)//(j,op) js_valueToObject(j,op)
#define J2L(j) js_valueToNumber(j)
/*to JSVAL*/
#define I2J(i) INT_TO_JSVAL(i)
#define O2J(i) OBJECT_TO_JSVAL(i)

#define JS_FUN(fun_name) JSBool fun_name (JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval)


typedef struct JSPropertiesSpec {
    const char      *name;
    jsval           vp;
}JSPropertiesSpec;

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
EXT void js_addModule(JSFunctionSpec* lfun,JSFunctionSpec* gfun,JSPropertiesSpec* lvar,JSPropertiesSpec* gvar);
EXT JSObject* js_addObj(const char*);
EXT JSContext* js_getContext(void);
EXT JSObject* js_getGlobalObject(void);
EXT JSBool js_convertArguments(uintN, jsval*, const char *, ...);
EXT jsval js_getElement(JSObject *tobj,int index);
EXT jsval js_getProperty(JSObject *tobj,const char*);
EXT jsval js_setProperty(JSObject *tobj,const char*, jsval);
EXT jsval js_convertValue(jsval v,JSType type);
EXT char* js_getStringBytes(JSString* str);
EXT JSString* js_newString(char* str);
EXT JSString* js_newExternalString(char* str);
EXT JSObject** js_valueToObject(jsval v,JSObject** tobj);
EXT JSString* js_valueToString(jsval v);
EXT u32 js_valueToECMAUint32(jsval v);
EXT u16 js_valueToUint16(jsval v);
EXT jsdouble js_valueToNumber(jsval v);
EXT jsdouble js_valueToNumber(jsval v);
EXT jsval js_evaluateScript(char* eval);
EXT JSType js_typeOfValue(jsval v);

EXT char* js_strdup(const char* str);
EXT void* js_malloc(size_t nbytes);
EXT void* js_realloc(void *p,size_t nbytes);
EXT void js_free(void *p);
EXT size_t c_strlen(const char *str);
