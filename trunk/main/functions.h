#include "src/jsapi.h"
#include "src/jsarray.h"

JS_FUN(js_print);
JS_FUN(js_meminfo);
JS_FUN(js_include);
JS_FUN(js_run);
JS_FUN(js_exit);
JSBool JS_InitClasses(JSContext *cx, JSObject *obj);