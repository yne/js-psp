#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "intraFont.h"

#include "../../main/shared.h"

PSP_MODULE_INFO("intraFont",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JSObject* font2js(intraFont *font){
	return NULL;
}

JS_FUN(Init){
	*rval = intraFontInit();
	return JS_TRUE;
}
JS_FUN(Shutdown){
	intraFontShutdown();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Load){
	js_setProperty(obj,"path",argv[0]);
	js_setProperty(obj,"param",argv[1]);
	js_setProperty(obj,"data",I2J((u32)intraFontLoad(J2S(argv[0]),J2I(argv[1]))));
	return JS_TRUE;
}
JS_FUN(Unload){
	intraFontUnload((void*)J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Print){
	float width = 0.0f;
	if(argc==5)width = J2L(argv[4]);
	if(js_typeOfValue(argv[0])==JSTYPE_OBJECT)
		*rval = I2J(intraFontPrint((void*)J2U(js_getProperty(J2O(argv[0]),"data")), J2I(argv[1]), J2I(argv[2]), J2S(argv[3]),width));
	else
		*rval = I2J(intraFontPrint((void*)J2U(argv[0]), J2I(argv[1]), J2I(argv[2]), J2S(argv[3]),width));
	return JS_TRUE;
}
JS_FUN(SetStyle){
	if(js_typeOfValue(argv[0])==JSTYPE_OBJECT)
		intraFontSetStyle((void*)J2U(js_getProperty(J2O(argv[0]),"data")), J2L(argv[1]), J2U(argv[2]), J2U(argv[3]), J2U(argv[4]));
	else
		intraFontSetStyle((void*)J2U(argv[0]), J2L(argv[1]), J2U(argv[2]), J2U(argv[3]), J2U(argv[4]));
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"Init",Init,0},
	{"Shutdown",Shutdown,0},
	{"Load",Load,2},
	{"SetStyle",SetStyle,5},
	{"Unload",Unload,1},
	{"Print",Print,4},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"intraFontInit",Init,0},
	{"intraFontShutdown",Shutdown,0},
	{"intraFontLoad",Load,2},
	{"intraFontSetStyle",SetStyle,5},
	{"intraFontUnload",Unload,1},
	{"intraFontPrint",Print,4},
	{0}
};
static JSPropertiesSpec gvar[] = {
	{"INTRAFONT_ADVANCE_H", I2J(INTRAFONT_ADVANCE_H)},
	{"INTRAFONT_ADVANCE_V", I2J(INTRAFONT_ADVANCE_V)},
	{"INTRAFONT_ALIGN_LEFT", I2J(INTRAFONT_ALIGN_LEFT)},
	{"INTRAFONT_ALIGN_CENTER", I2J(INTRAFONT_ALIGN_CENTER)},
	{"INTRAFONT_ALIGN_RIGHT", I2J(INTRAFONT_ALIGN_RIGHT)},
	{"INTRAFONT_ALIGN_FULL", I2J(INTRAFONT_ALIGN_FULL)},
	{"INTRAFONT_SCROLL_LEFT", I2J(INTRAFONT_SCROLL_LEFT)},

	{"INTRAFONT_SCROLL_SEESAW", I2J(INTRAFONT_SCROLL_SEESAW)},
	{"INTRAFONT_SCROLL_RIGHT", I2J(INTRAFONT_SCROLL_RIGHT)},
	{"INTRAFONT_SCROLL_THROUGH", I2J(INTRAFONT_SCROLL_THROUGH)},
	{"INTRAFONT_WIDTH_VAR", I2J(INTRAFONT_WIDTH_VAR)},
	{"INTRAFONT_WIDTH_FIX", I2J(INTRAFONT_WIDTH_FIX)},

	{"INTRAFONT_ACTIVE", I2J(INTRAFONT_ACTIVE)},
	{"INTRAFONT_CACHE_MED", I2J(INTRAFONT_CACHE_MED)},
	{"INTRAFONT_CACHE_LARGE", I2J(INTRAFONT_CACHE_LARGE)},
	{"INTRAFONT_CACHE_ASCII", I2J(INTRAFONT_CACHE_ASCII)},

	{"INTRAFONT_CACHE_ALL", I2J(INTRAFONT_CACHE_ALL)},

	{"INTRAFONT_STRING_ASCII", I2J(INTRAFONT_STRING_ASCII)},
	{"INTRAFONT_STRING_CP437", I2J(INTRAFONT_STRING_CP437)},
	{"INTRAFONT_STRING_CP850", I2J(INTRAFONT_STRING_CP850)},
	{"INTRAFONT_STRING_CP866", I2J(INTRAFONT_STRING_CP866)},
	{"INTRAFONT_STRING_SJIS", I2J(INTRAFONT_STRING_SJIS)},
	{"INTRAFONT_STRING_GBK", I2J(INTRAFONT_STRING_GBK)},
	{"INTRAFONT_STRING_KOR", I2J(INTRAFONT_STRING_KOR)},
	{"INTRAFONT_STRING_BIG5", I2J(INTRAFONT_STRING_BIG5)},
	{"INTRAFONT_STRING_CP1251", I2J(INTRAFONT_STRING_CP1251)},
	{"INTRAFONT_STRING_CP1252", I2J(INTRAFONT_STRING_CP1252)},
	{"INTRAFONT_STRING_UTF8", I2J(INTRAFONT_STRING_UTF8)},

	{"RED", I2J(0xFF0000FF)},
	{"GREEN", I2J(0xFF00FF00)},
	{"BLUE", I2J(0xFFFF0000)},
	{"WHITE", I2J(0xFFFFFFFF)},
	{"LITEGRAY", I2J(0xFFBFBFBF)},
	{"GRAY", I2J(0xFF7F7F7F)},
	{"DARKGRAY", I2J(0xFF3F3F3F)},		
	{"BLACK", I2J(0xFF000000)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,gfun,0,gvar);
	js_addClass(NULL,NULL,Load,2,NULL,NULL,NULL,NULL,"Font",
		JSCLASS_NEW_RESOLVE,JSCLASS_NO_MANDATORY_MEMBERS,JSCLASS_NO_OPTIONAL_MEMBERS);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}