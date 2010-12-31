#include <pspsdk.h>
#include <pspkernel.h>
#include "intraFont.h"
#include "../gu/pspgu.h"
#include "../../main/shared.h"

PSP_MODULE_INFO("intraFont", 0x0006, 1, 0);
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
	*rval = I2J(intraFontLoad(J2S(argv[0]), J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(Unload){
	intraFontUnload((void*)J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(Print){
	intraFontPrint((void*)J2U(argv[0]), J2I(argv[1]), J2I(argv[2]), J2S(argv[3]));
	return JS_TRUE;
}
JS_FUN(SetStyle){
	intraFontSetStyle((void*)J2U(argv[0]), J2I(argv[1]), J2U(argv[2]), J2U(argv[3]), J2U(argv[4]));
	return JS_TRUE;
}
//constructor
JS_FUN(Font){
	if(!argc)return JS_TRUE;
	intraFont* fnt;
	if(J2I(argv[1])==UNDEFINED)
		fnt = intraFontLoad(J2S(argv[0]),0);
	else
		fnt = intraFontLoad(J2S(argv[0]), J2I(argv[1]));
	if(fnt)
		js_setProperty(obj,"p",I2J(fnt));
	return JS_TRUE;
}
//methodes
JS_METH(font_print){
	intraFontPrint((void*)J2U(js_getProperty(J2O(ARGV[-1]),"p")), J2I(ARGV[1]), J2I(ARGV[2]), J2S(ARGV[0]));
	return JS_TRUE;
}
JS_METH(font_style){
	intraFontSetStyle((void*)J2U(js_getProperty(J2O(ARGV[-1]),"p")), J2D(ARGV[0]), J2U(ARGV[1]), J2U(ARGV[2]), J2U(ARGV[3]));
	return JS_TRUE;
}
JS_METH(font_unload){
	intraFontUnload((void*)J2U(js_getProperty(J2O(ARGV[-1]),"p")));
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"init",Init,0},
	{"load",Load,2},
	{"setStyle",SetStyle,5},
	{"unload",Unload,1},
	{"print",Print,4},
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

	{0}
};
static JSFunctionSpec fontMethodes[] = {
	JS_FN("print", font_print,1,0,0),
	JS_FN("style", font_style,1,0,0),
	JS_FN("unload", font_unload,1,0,0),
	JS_FS_END
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,gfun,0,gvar);
	js_addClass(NULL,NULL,Font,2,NULL,fontMethodes,NULL,NULL,"Font",
		JSCLASS_NEW_RESOLVE,JSCLASS_NO_MANDATORY_MEMBERS,JSCLASS_NO_OPTIONAL_MEMBERS,NULL);
	intraFontInit();//clut generation
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}