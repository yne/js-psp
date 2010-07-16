#include <pspkernel.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

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
	printf("test called !!\n\n");
	return in*3;
}
typedef struct JSPropertiesSpec{
    const char      *name;
    jsval           vp;
}JSPropertiesSpec;
int js_addVar(JSPropertiesSpec* ps, JSObject* obj){
	if(!obj)obj=gobj;
	while(ps->name){
		JS_SetProperty(cx,obj,ps->name,&ps->vp);
		ps++;
	}
	return JS_TRUE;
}
int js_addFunc(JSFunctionSpec* functions, JSObject * obj){
	printf("js_addFunc %08X %i\n",(int)functions,(int)obj);
	if(!obj)obj=gobj;
	return !JS_DefineFunctions(cx, obj, functions);
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
	jsval vp;
	JS_GetProperty(cx,tobj,name,&vp);
	return vp;
}
JSBool js_setProperty(JSObject *tobj,const char* name, jsval vp){
	return JS_SetProperty(cx,tobj,name,&vp);
}
jsdouble js_valueToNumber(jsval v){
	jsdouble dp;
	JS_ValueToNumber(cx,v,&dp);
	return dp;
}
char* js_getStringBytes(JSString* str){
	return JS_GetStringBytes(str);
}
jsval js_convertValue(jsval v,JSType type){
	jsval dp;
	JS_ConvertValue(cx,v,type,&dp);
	return dp;
}
JSString* js_newString(char* str){
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
char* js_strdup(const char* str){
	return JS_strdup(cx,str);
}
void* js_malloc(size_t nbytes){
	return JS_malloc(cx,nbytes);
}