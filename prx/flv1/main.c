#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>

#include "flv1info.h"

#include "../../main/shared.h"

PSP_MODULE_INFO("FLV1",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(Flv1info_open){
	flv1info_t* info = flv1info_open(J2S(argv[0]),J2I(argv[1]));
	JSObject* mobj = js_addObj("");
	js_setProperty(mobj,"handle",I2J((u32)info->handle));
	js_setProperty(mobj,"duration",D2J(info->duration));
	js_setProperty(mobj,"video_type",I2J((u32)info->video_type));
	js_setProperty(mobj,"audio_type",I2J((u32)info->audio_type));
	js_setProperty(mobj,"video_scale",I2J((u32)info->video_scale));
	js_setProperty(mobj,"video_frame_duration",I2J((u32)info->video_frame_duration));
	js_setProperty(mobj,"width",I2J((u32)info->width));
	js_setProperty(mobj,"height",I2J((u32)info->height));
	js_setProperty(mobj,"channels",I2J((u32)info->channels));
	js_setProperty(mobj,"samplerate",I2J((u32)info->samplerate));
	js_setProperty(mobj,"samplebits",I2J((u32)info->samplebits));
	js_setProperty(mobj,"samples_per_frame",I2J((u32)info->samples_per_frame));

	js_setProperty(mobj,"avc_profile",I2J((u32)info->avc_profile));
	js_setProperty(mobj,"avc_sps_size",I2J((u32)info->avc_sps_size));
	js_setProperty(mobj,"avc_sps",I2J((u32)info->avc_sps));
	js_setProperty(mobj,"avc_pps_size",I2J((u32)info->avc_pps_size));
	js_setProperty(mobj,"avc_pps",I2J((u32)info->avc_pps));
	js_setProperty(mobj,"avc_nal_prefix_size",I2J((u32)info->avc_nal_prefix_size));

	js_setProperty(mobj,"data_start",I2J((u32)info->data_start));
	js_setProperty(mobj,"total_indexes",I2J((u32)info->total_indexes));
	js_setProperty(mobj,"indexes",I2J((u32)info->indexes));

	*rval = O2J(mobj);
	return JS_TRUE;
}
JS_FUN(Flv1info_close){
	if(JSVAL_IS_OBJECT(argv[0])){//receive a flv1info_t object
		js_free((void*)J2U(js_getProperty(J2O(argv[0]),"avc_sps")));
		js_free((void*)J2U(js_getProperty(J2O(argv[0]),"avc_pps")));
		js_free((void*)J2U(js_getProperty(J2O(argv[0]),"indexes")));
		//js_free(info);//the flv1info_t is managed by JSE
	}
	//flv1info_close(flv1info_t* info);
	return JS_TRUE;
}
JS_FUN(Flv1info_dump){
	//flv1info_dump(flv1info_t* info, const char* dumpfile);
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"open",Flv1info_open, 0},
	{"close",Flv1info_close, 0},
	{"dump",Flv1info_dump, 0},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,0,0,0);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
