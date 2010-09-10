/* 
 *	Copyright (C) 2008 cooleyes
 *	eyes.cooleyes@gmail.com 
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psputility.h>
#include <pspgu.h>
#include <psppower.h>
#include <stdio.h>
#include <stdlib.h>
#include <psprtc.h>
#include <pspsdk.h>
#include <string.h>
#include <pspgu.h>
#include "cooleyesBridge.h"
#include "mem64.h"
#include "pspmpeg.h"
#include "mp4_read.h"

PSP_MODULE_INFO("AVCDecoder", 0, 1, 1);
PSP_NO_CREATE_MAIN_THREAD();


typedef struct {
	ScePVoid sps_buffer;
	SceInt32 sps_size;
	ScePVoid pps_buffer;
	SceInt32 pps_size;
	SceInt32 nal_prefix_size;
	ScePVoid nal_buffer;
	SceInt32 nal_size;
	SceInt32 mode;
} Mp4AvcNalStruct;
typedef struct {
	SceInt32 unknown0;
	SceInt32 unknown1;
	SceInt32 width;
	SceInt32 height;
	SceInt32 unknown4;
	SceInt32 unknown5;
	SceInt32 unknown6;
	SceInt32 unknown7;
	SceInt32 unknown8;
	SceInt32 unknown9;
} Mp4AvcInfoStruct;
typedef struct {
	ScePVoid buffer0;
	ScePVoid buffer1;
	ScePVoid buffer2;
	ScePVoid buffer3;
	ScePVoid buffer4;
	ScePVoid buffer5;
	ScePVoid buffer6;
	ScePVoid buffer7;
	SceInt32 unknown0;
	SceInt32 unknown1;
	SceInt32 unknown2;
} Mp4AvcYuvStruct;
typedef struct {
	SceInt32 unknown0;
	SceInt32 unknown1;
	SceInt32 unknown2;
	SceInt32 unknown3;
	Mp4AvcInfoStruct* info_buffer;
	SceInt32 unknown5;
	SceInt32 unknown6;
	SceInt32 unknown7;
	SceInt32 unknown8;
	SceInt32 unknown9;
	SceInt32 unknown10;
	Mp4AvcYuvStruct* yuv_buffer;
	SceInt32 unknown12;
	SceInt32 unknown13;
	SceInt32 unknown14;
	SceInt32 unknown15;
	SceInt32 unknown16;
	SceInt32 unknown17;
	SceInt32 unknown18;
	SceInt32 unknown19;
	SceInt32 unknown20;
	SceInt32 unknown21;
	SceInt32 unknown22;
	SceInt32 unknown23;
} Mp4AvcDetail2Struct;
typedef struct {
	SceInt32 height;
	SceInt32 width;
	SceInt32 mode0;
	SceInt32 mode1;
	ScePVoid buffer0;
	ScePVoid buffer1;
	ScePVoid buffer2;
	ScePVoid buffer3;
	ScePVoid buffer4;
	ScePVoid buffer5;
	ScePVoid buffer6;
	ScePVoid buffer7;
} Mp4AvcCscStruct;
typedef struct {
	int      mpeg_init;
	int      mpeg_create;
	ScePVoid mpeg_buffer;
	SceMpeg mpeg;
	SceMpegRingbuffer mpeg_ringbuffer;
	SceMpegAu* mpeg_au;
	SceInt32 mpeg_mode;
	SceInt32 mpeg_buffer_size;
	ScePVoid mpeg_ddrtop;
	ScePVoid mpeg_au_buffer;
	ScePVoid mpeg_sps_pps_buffer;
	SceInt32 mpeg_sps_size;
	SceInt32 mpeg_pps_size;
	SceInt32 mpeg_nal_prefix_size;
	Mp4AvcDetail2Struct* mpeg_detail2;
	SceInt32 mpeg_pic_num;
} Mp4AvcDecoderStruct;

extern void sceMpegGetAvcNalAu(SceMpeg*,Mp4AvcNalStruct*,SceMpegAu*);
extern void sceMpegAvcDecodeDetail2(SceMpeg*,Mp4AvcDetail2Struct**);
extern int sceMpegBaseCscAvc(void*,unsigned,unsigned,Mp4AvcCscStruct*);
Mp4AvcDecoderStruct avc_struct;
Mp4AvcDecoderStruct* avc = &avc_struct;
Mp4AvcCscStruct csc_struct;
Mp4AvcCscStruct* csc = &csc_struct;
struct mp4_read_struct reader;
Mp4AvcNalStruct nal;
struct mp4_video_read_output_struct v_packet;
int ready=0;

#define EXIT {js_test(__LINE__);goto wait;}
int modload(char* path){
	int status;
	SceUID modid = sceKernelLoadModule(path, 0, NULL);
	if(modid >= 0)
		modid = sceKernelStartModule(modid, 0, 0, &status, NULL);
	else return 1;
	return 0;
}
int last_frame_count=0;
JS_FUN(Play){
	if(!ready)return JS_TRUE;
	int frame_count;
	if(!argc) frame_count = last_frame_count;
	else frame_count = J2I(argv[0]);
	if(frame_count>reader.file.number_of_video_frames)return JS_TRUE;
	
	nal.sps_buffer      = avc->mpeg_sps_pps_buffer;
	nal.sps_size        = avc->mpeg_sps_size;
	nal.pps_buffer      = avc->mpeg_sps_pps_buffer+avc->mpeg_sps_size;
	nal.pps_size        = avc->mpeg_pps_size;
	nal.nal_prefix_size = avc->mpeg_nal_prefix_size;
	
	if (mp4_read_get_video(&reader, frame_count, &v_packet))return JS_TRUE;
	
	nal.nal_buffer = v_packet.video_buffer;
	nal.nal_size = v_packet.video_length ;
	frame_count?(nal.mode=0):(nal.mode=3);
	sceMpegGetAvcNalAu(&avc->mpeg, &nal, avc->mpeg_au);
	sceMpegAvcDecode(&avc->mpeg, avc->mpeg_au, 512, 0, &avc->mpeg_pic_num);
	sceMpegAvcDecodeDetail2(&avc->mpeg, &avc->mpeg_detail2);
	if(avc->mpeg_pic_num>0){
		int i;
		for( i = 0; i < avc->mpeg_pic_num; i++ ) {
			Mp4AvcCscStruct csc;
			csc.height = (avc->mpeg_detail2->info_buffer->height+15) >> 4;
			csc.width = (avc->mpeg_detail2->info_buffer->width+15) >> 4;
			csc.mode0 = 0;
			csc.mode1 = 0;
			csc.buffer0 = avc->mpeg_detail2->yuv_buffer->buffer0;
			csc.buffer1 = avc->mpeg_detail2->yuv_buffer->buffer1;
			csc.buffer2 = avc->mpeg_detail2->yuv_buffer->buffer2;
			csc.buffer3 = avc->mpeg_detail2->yuv_buffer->buffer3;
			csc.buffer4 = avc->mpeg_detail2->yuv_buffer->buffer4;
			csc.buffer5 = avc->mpeg_detail2->yuv_buffer->buffer5;
			csc.buffer6 = avc->mpeg_detail2->yuv_buffer->buffer6;
			csc.buffer7 = avc->mpeg_detail2->yuv_buffer->buffer7;
			if(!sceMpegBaseCscAvc((void*)(0x4000000+J2U(js_getProperty(NULL,"GU_DRAW_BUFFER"))), 0,(avc->mpeg_mode == 4) ? 512 : 768, &csc)){
				//return JS_TRUE;
			}
		}		
	}
	*rval = I2J(++frame_count);
	last_frame_count=frame_count;
	return JS_TRUE;
}
JS_FUN(Load){
	int devkitVersion = sceKernelDevkitVersion();
	mp4_read_safe_constructor(&reader);
	memset(avc, 0, sizeof(Mp4AvcDecoderStruct));

	if(sceUtilityLoadAvModule(0))EXIT;
	if(modload("mpeg_vsh370.prx"))EXIT;
	if(modload("cooleyesBridge.prx"))EXIT;
	if(mp4_read_open(&reader, J2S(argv[0])))EXIT;
	printf("video width %d, height %d\n",reader.file.video_width,reader.file.video_height);
		
	if(reader.file.info->tracks[reader.file.video_track_id]->avc_profile==0x4D&&(reader.file.video_width>480||reader.file.video_height>272)){//480P mode
		cooleyesMeBootStart(devkitVersion, 1);
		avc->mpeg_mode = 5;
	}else if(reader.file.info->tracks[reader.file.video_track_id]->avc_profile==0x4D){//main profile ( <=480*272 )
		cooleyesMeBootStart(devkitVersion, 3);
		avc->mpeg_mode = 4;
	}else if(reader.file.info->tracks[reader.file.video_track_id]->avc_profile==0x42){//baseline profile ( <=480*272 )
		cooleyesMeBootStart(devkitVersion, 4);
		avc->mpeg_mode = 4;
	}
	if(sceMpegInit())EXIT;
	avc->mpeg_ddrtop =  c_memalign(0x400000, 0x400000);
	avc->mpeg_au_buffer = avc->mpeg_ddrtop + 0x10000;
	int result = sceMpegQueryMemSize(avc->mpeg_mode);
	if(result<0)EXIT;
	avc->mpeg_buffer_size = result;
	if (!(result & 0xF))
		result = (result & 0xFFFFFFF0) + 16;
	
	avc->mpeg_buffer = malloc_64(result);
	if(!avc->mpeg_buffer)EXIT;
	if(sceMpegCreate(&avc->mpeg, avc->mpeg_buffer, avc->mpeg_buffer_size, &avc->mpeg_ringbuffer, 512, avc->mpeg_mode, avc->mpeg_ddrtop))EXIT;
	avc->mpeg_au = (SceMpegAu*)malloc_64(64);
	if(!avc->mpeg_au)EXIT;
	memset(avc->mpeg_au, 0xFF, 64);
	if(sceMpegInitAu(&avc->mpeg, avc->mpeg_au_buffer, avc->mpeg_au))EXIT;

	avc->mpeg_sps_size = reader.file.info->tracks[reader.file.video_track_id]->avc_sps_size;
	avc->mpeg_pps_size = reader.file.info->tracks[reader.file.video_track_id]->avc_pps_size;
	avc->mpeg_nal_prefix_size = reader.file.info->tracks[reader.file.video_track_id]->avc_nal_prefix_size;
	avc->mpeg_sps_pps_buffer = malloc_64(avc->mpeg_sps_size + avc->mpeg_pps_size);
	if(!avc->mpeg_sps_pps_buffer)EXIT;
	memcpy(avc->mpeg_sps_pps_buffer, reader.file.info->tracks[reader.file.video_track_id]->avc_sps, avc->mpeg_sps_size);
	memcpy(avc->mpeg_sps_pps_buffer+avc->mpeg_sps_size, reader.file.info->tracks[reader.file.video_track_id]->avc_pps, avc->mpeg_pps_size);
	ready=1;
	return JS_TRUE;
wait:
	mp4_read_close(&reader);
	ready=0;
	return JS_TRUE;
}
static JSFunctionSpec lfun[] = {
	{"load",Load,1},
	{"play",Play,1},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,0,0,0);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}