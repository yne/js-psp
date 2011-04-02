#include <jsapi.h>
#include <psprtc.h>

JSInt64 PRMJ_Now(void){
    u64 s;
		sceRtcGetCurrentTick (&s);
    return (JSInt64)s;
}