#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("user",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(Human){
	if(argc<3)
		return JS_TRUE;
	//JSObject*ret=js_addObj("");//create a annonym object
	js_setProperty(obj,"age",argv[0]);// no need to convert beacause argv are already in JS
	js_setProperty(obj,"sex",argv[1]);
	js_setProperty(obj,"loc",argv[2]);
	//*rval = O2J(ret);
	return JS_TRUE;
}
JS_FUN(Double){
	int i = J2I(argv[0]);//convert the first argument to int
	*rval = I2J(i*2);//return 2*i converted in JS_VALUE
	return JS_TRUE;
}
JS_FUN(Float){
	printf("%f\n",(double)J2L(argv[0]));
	return JS_TRUE;
}
// functions and variable defined in the target object
static JSFunctionSpec lfun[] = {
	{"Float",Float,1},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"Double",Double,1},
	{0}
};
static JSPropertiesSpec gvar[] = {
	{"Run", I2J(1)},
	{0}
};
static JSPropertiesSpec lvar[] = {
	{"TemplateIsLoaded", I2J(1)},
	{0}
};
static void myFinalizeStub(JSContext *cx, JSObject *obj){
	printf("Human Finalize\n");
	//sceKernelUnloadModule(sceKernelStopModule(J2I(js_getProperty(obj,"UID")),0,NULL,&rval,NULL));
}
static JSBool my_addProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	printf("Human + %s\n",J2S(id));
	return JS_TRUE;
}
static JSBool my_delProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	printf("Human - %s, value %s\n",J2S(id),J2S(*vp));
	return JS_TRUE;
}
static JSBool my_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp){
	//printf("Human convert\n");
	return JS_TRUE;
}
static JSBool my_resolve(JSContext *cx, JSObject *obj, jsval id, uintN flags,JSObject **objp){
	//printf("Human resolve\n");
	return JS_TRUE;
}
static JSBool my_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	printf("Human < %s : %s\n",J2S(id),J2S(*vp));
	return JS_TRUE;
}
static JSBool my_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	printf("Human > %s = %s\n",J2S(id),J2S(*vp));
	return JS_TRUE;
}
int module_start(SceSize args, void *argp){
	/* js_addModule
	1 > fonctions defined as local (must be called from the object) ex: Init will be called using module.Init()
	2 > fonctions defined as global ex: Init will be called using Init(), can make conflit with another module use the same function name
	3 > variables defined as local (must be called from the object) ex: running will be called using module.running
	4 > variables defined as global ex: modloaded will be called using modloaded, can make conflit with another module use the same variable name
	*/
	js_addModule(lfun,gfun,lvar,gvar);
	
	js_addClass(
		NULL, // object to define the class (leave NULL to use the global object)
		NULL, // parent prototype (usefull ?)
		Human, // prototype of the class
		3, // number of arg needed
		NULL, // property list automaticaly added
		NULL, // methodes list automaticaly added
		NULL, // property list automaticaly added as private
		NULL, // methodes list automaticaly added as private
		"Human", // name of the class (used by "new")
		JSCLASS_NEW_RESOLVE, // class options
		my_addProperty, // function called in every class's prop/fun addition
		my_delProperty, // function called in every class's prop/fun removing
		my_getProperty, // function called in every class's prop/fun getting
		my_setProperty, // function called in every class's prop/fun setting
		NULL,
		(JSResolveOp)my_resolve,
		my_convert,
		myFinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS
	);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
