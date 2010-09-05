#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>

#include "mkvinfo.h"
#include "bufferedio.h"
#include "ebml.h"

#include "../../main/shared.h"

PSP_MODULE_INFO("FLV1",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(Mkvinfo_open){
	mkvinfo_t* info = (mkvinfo_t*)js_malloc(sizeof(mkvinfo_t));
	if (!info)
		return JS_TRUE;

	buffered_io_t io;
	if (io_open(J2S(argv[0]), (void*)(&io)) < 0 ) {
		js_free(info);
		return JS_TRUE;
	}
	info->handle = &io;
	parse_ebml(info);
	io_close(&io);
	info->handle = 0;
	

	info = mkvinfo_open(J2S(argv[0]));
	JSObject* mobj = js_addObj("");
	js_setProperty(mobj,"handle",I2J((u32)info->handle));
	js_setProperty(mobj,"parsed_cues",I2J((u32)info->parsed_cues));
	js_setProperty(mobj,"parsed_cues_num",I2J((u32)info->parsed_cues_num));
	js_setProperty(mobj,"parsed_seekhead",I2J((u32)info->parsed_seekhead));
	js_setProperty(mobj,"parsed_seekhead_num",I2J((u32)info->parsed_seekhead_num));
	js_setProperty(mobj,"segment_start",I2J((u32)info->segment_start));
	js_setProperty(mobj,"timecode_scale",D2J(info->timecode_scale));
	js_setProperty(mobj,"first_timecode",D2J(info->first_timecode));
	js_setProperty(mobj,"has_first_timecode",I2J((u32)info->has_first_timecode));
	js_setProperty(mobj,"duration",D2J((u32)info->duration));
	js_setProperty(mobj,"indexes",I2J((u32)info->indexes));
	js_setProperty(mobj,"total_indexes",I2J((u32)info->total_indexes));
	js_setProperty(mobj,"tracks",I2J((u32)info->tracks));
	js_setProperty(mobj,"total_tracks",I2J((u32)info->total_tracks));
	*rval = O2J(mobj);
	return JS_TRUE;
}
JS_FUN(Mkvinfo_close){
	if(!argc)return JS_TRUE;
	
	js_free((void*)J2U(js_getProperty(J2O(argv[0]),"parsed_cues")));
	js_free((void*)J2U(js_getProperty(J2O(argv[0]),"parsed_seekhead")));
	js_free((void*)J2U(js_getProperty(J2O(argv[0]),"indexes")));
	mkvinfo_track_t* tracks=(mkvinfo_track_t*)J2U(js_getProperty(J2O(argv[0]),"tracks"));
	int32_t i;
	int32_t total_tracks = J2U(js_getProperty(J2O(argv[0]),"indexes"));
	for (i = 0; i < total_tracks; i++) {
		/*if (tracks[i]) {
			if (tracks[i].private_data)
				js_free(tracks[i].private_data);
			js_free(&(tracks[i]));
			tracks[i] = 0;
		}*/
	}
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"open",Mkvinfo_open, 0},
	{"close",Mkvinfo_close, 0},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,0,0,0);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
