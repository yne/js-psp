/* 
 *	Copyright (C) 2009 cooleyes
 *	eyes.cooleyes@gmail.com 
 *
 *  This Program is js_free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the js_free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the js_free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bufferedio.h"
#include "flv1info_type.h"
#include "../../main/shared.h"

#define FOURCC(a,b,c,d) \
	( ((uint32_t)d) | (((uint32_t)c) << 8) | (((uint32_t)b) << 16) | (((uint32_t)a) << 24) )
	
#define FLV1_AUDIO_SAMPLESSIZE_OFFSET 1
#define FLV1_AUDIO_SAMPLERATE_OFFSET  2
#define FLV1_AUDIO_CODECID_OFFSET     4

#define FLV1_VIDEO_FRAMETYPE_OFFSET   4

/* bitmasks to isolate specific values */
#define FLV1_AUDIO_CHANNEL_MASK    0x01
#define FLV1_AUDIO_SAMPLESIZE_MASK 0x02
#define FLV1_AUDIO_SAMPLERATE_MASK 0x0c
#define FLV1_AUDIO_CODECID_MASK    0xf0

#define FLV1_VIDEO_CODECID_MASK    0x0f
#define FLV1_VIDEO_FRAMETYPE_MASK  0xf0

#define FLV1_AMF_END_OF_OBJECT         0x09

enum {
    FLV1_MONO   = 0,
    FLV1_STEREO = 1,
};

enum {
    FLV1_TAG_TYPE_AUDIO = 0x08,
    FLV1_TAG_TYPE_VIDEO = 0x09,
    FLV1_TAG_TYPE_SCRIPT_DATA  = 0x12,
};

enum {
    FLV1_CODECID_PCM                  = 0,
    FLV1_CODECID_ADPCM                = 1 << FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_MP3                  = 2 << FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_PCM_LE               = 3 << FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_NELLYMOSER_8KHZ_MONO = 5 << FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_NELLYMOSER           = 6 << FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_AAC                  = 10<< FLV1_AUDIO_CODECID_OFFSET,
    FLV1_CODECID_SPEEX                = 11<< FLV1_AUDIO_CODECID_OFFSET,
};

enum {
    FLV1_CODECID_H263    = 2,
    FLV1_CODECID_SCREEN  = 3,
    FLV1_CODECID_VP6     = 4,
    FLV1_CODECID_VP6A    = 5,
    FLV1_CODECID_SCREEN2 = 6,
    FLV1_CODECID_H264    = 7,
};

enum {
    AMF_DATA_TYPE_NUMBER      = 0x00,
    AMF_DATA_TYPE_BOOL        = 0x01,
    AMF_DATA_TYPE_STRING      = 0x02,
    AMF_DATA_TYPE_OBJECT      = 0x03,
    AMF_DATA_TYPE_NULL        = 0x05,
    AMF_DATA_TYPE_UNDEFINED   = 0x06,
    AMF_DATA_TYPE_REFERENCE   = 0x07,
    AMF_DATA_TYPE_MIXEDARRAY  = 0x08,
    AMF_DATA_TYPE_ARRAY       = 0x0a,
    AMF_DATA_TYPE_DATE        = 0x0b,
    AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
};

static uint32_t flv1_mp3_samples_per_frames[9] = {384, 1152, 1152, 384, 1152, 576, 384, 1152, 576};
static uint32_t flv1_aac_samplerates[] = {96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000};

void parse_audio_tag(flv1info_t* info) {
	uint8_t audio_flag = io_read_8(info->handle);
	uint8_t audio_id = audio_flag & FLV1_AUDIO_CODECID_MASK;
	info->channels = (audio_flag & FLV1_AUDIO_CHANNEL_MASK) == FLV1_STEREO ? 2 : 1; 
	info->samplebits = (audio_flag & FLV1_AUDIO_SAMPLESIZE_MASK) ? 16 : 8;
	info->samplerate = (44100 << ((audio_flag & FLV1_AUDIO_SAMPLERATE_MASK) >> FLV1_AUDIO_SAMPLERATE_OFFSET) >> 3);
	
	if ( FLV1_CODECID_PCM == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_ADPCM == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_MP3 == audio_id ) {
		info->audio_type = FOURCC('m', 'p', '3' ,' ');
		io_read_8(info->handle);
		uint8_t mp3_flag = io_read_8(info->handle);
		uint32_t mp3_version;
		uint32_t mp3_level;
		switch((mp3_flag >> 3) & 0x03) {
			case 0:
				mp3_version = 2; // MPEG 2.5
				break;
			case 2:
				mp3_version = 1; // MPEG 2
				break;
			case 3:
				mp3_version = 0; // MPEG 1
				break;
			default:
				mp3_version = 0;
				break;
		}
		mp3_level = 3 - ((mp3_flag >> 1) & 0x03);
		if ( mp3_level == 3 ) 
			mp3_level--;
		
		info->samples_per_frame = flv1_mp3_samples_per_frames[mp3_version*3+mp3_level];		
	}
	else if( FLV1_CODECID_PCM_LE == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_NELLYMOSER_8KHZ_MONO == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_NELLYMOSER == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_AAC == audio_id ) {
		uint8_t aac_flag = io_read_8(info->handle);
		if ( aac_flag != 0x00 )
			return;
		uint8_t aac_header[7];
		io_read_data(info->handle, aac_header, 7);
		
		info->audio_type = FOURCC('m', 'p', '4' ,'a');
		info->samplerate = ((aac_header[0] & 0x07) << 1) | (aac_header[1]>>7);
		info->samplerate = flv1_aac_samplerates[info->samplerate];
		info->samples_per_frame = 1024;
	}
	else if( FLV1_CODECID_SPEEX == audio_id )
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
	else
		info->audio_type = FOURCC('u', 'n', 's' ,'p');
}

void parse_video_tag(flv1info_t* info) {
	
	uint8_t video_flag = io_read_8(info->handle);
	uint8_t video_id = video_flag & FLV1_VIDEO_CODECID_MASK;
	if ( FLV1_CODECID_H263 == video_id )
		info->video_type = FOURCC('f', 'l', 'v' ,'1');
	else if( FLV1_CODECID_SCREEN == video_id )
		info->video_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_VP6 == video_id )
		info->video_type = FOURCC('v', 'p', '6' ,'f');
	else if( FLV1_CODECID_VP6A == video_id )
		info->video_type = FOURCC('v', 'p', '6' ,'a');
	else if( FLV1_CODECID_SCREEN2 == video_id )
		info->video_type = FOURCC('u', 'n', 's' ,'p');
	else if( FLV1_CODECID_H264 == video_id ) {
		uint8_t avc_flag = io_read_8(info->handle);
		if ( avc_flag != 0x00 )
			return;
		io_read_be24(info->handle); //time offset
		io_read_8(info->handle); //configurationVersion
		info->avc_profile = io_read_8(info->handle); //AVCProfileIndication
		io_read_8(info->handle); //profile_compatibility
		io_read_8(info->handle); //AVCLevelIndication
		uint8_t value = io_read_8(info->handle); //reserved <6bits> & lengthSizeMinusOne <2bits>
		info->avc_nal_prefix_size = (value & 0x03) + 1;
		io_read_8(info->handle); //reserved1 <3bits> & numOfSequenceParameterSets <5bits>
    
		info->avc_sps_size = io_read_be16(info->handle);
		info->avc_sps = (uint8_t*)js_malloc(info->avc_sps_size);
		if ( info->avc_sps ) {
			io_read_data(info->handle, info->avc_sps, info->avc_sps_size);
		
			io_read_8(info->handle); /* numOfPictureParameterSets */
			info->avc_pps_size = io_read_be16(info->handle);
			info->avc_pps = (uint8_t*)js_malloc(info->avc_pps_size);
			if ( info->avc_pps ) {
				io_read_data(info->handle, info->avc_pps, info->avc_pps_size);
			} else {
				info->avc_pps_size = 0;
			}
		} else {
			info->avc_sps_size = 0;
		}
		info->video_type = FOURCC('a', 'v', 'c' ,'1');
	}
	else
		info->video_type = FOURCC('u', 'n', 's' ,'p');
}

static char* get_amf_string(flv1info_t* info, uint16_t size) {
	char* buf = (char*)js_malloc(size+1);
	if ( buf ) {
		memset(buf, 0, size+1);
		io_read_data(info->handle, (void*)buf, size);
	}
	return buf;
}

static void release_amf_string(char* str) {
	if ( str )
		js_free(str);
}

int parse_mixedarray_or_object(flv1info_t* info, int32_t max_pos, int parse_index, int is_mixedarray);
int parse_array(flv1info_t* info, int32_t max_pos, int parse_index, const char* key_name);
int parse_array_item(flv1info_t* info, int32_t max_pos, int parse_index, uint64_t* u64value, int32_t* s32value);


int parse_array_item(flv1info_t* info, int32_t max_pos, int parse_index, uint64_t* u64value, int32_t* s32value) {
	int32_t cur_pos = io_get_position(info->handle);
	if ( cur_pos < max_pos ) {
		double value_double = 0.0f;
		uint8_t value_boolean = 0;
		char* value_string = 0;
			
		uint8_t value_type = io_read_8(info->handle);
		if ( value_type == AMF_DATA_TYPE_NUMBER ) {
			uint64_t temp = io_read_be64(info->handle);
			value_double = *((double*)&temp);
		}
		else if ( value_type == AMF_DATA_TYPE_BOOL ) { 
			value_boolean = io_read_8(info->handle);
		}
		else if ( value_type == AMF_DATA_TYPE_STRING ) {
			uint16_t value_size = io_read_be16(info->handle);
			if ( value_size != 0 ) {
				//value_string = get_amf_string(info, value_size);
				//just skip string
				io_set_position(info->handle, io_get_position(info->handle)+value_size);
			}
		}
		else if ( value_type == AMF_DATA_TYPE_DATE ) {
			io_read_be64(info->handle);
			io_read_be16(info->handle);
		}
		else if ( value_type == AMF_DATA_TYPE_OBJECT ) {
			if ( parse_mixedarray_or_object(info, max_pos, parse_index, 0) < 0 ) {
				return -1;
			}
		}
		else if ( value_type == AMF_DATA_TYPE_ARRAY ) {
			if ( parse_array(info, max_pos, parse_index, 0) < 0 ) {
				return -1;
			}
		}
		else if ( value_type == AMF_DATA_TYPE_MIXEDARRAY) {
			if ( parse_mixedarray_or_object(info, max_pos, parse_index, 1) < 0 ) {
				return -1;
			}
		}
		else if ( value_type == AMF_DATA_TYPE_NULL || 
			value_type == AMF_DATA_TYPE_UNDEFINED ||
			value_type == AMF_DATA_TYPE_UNSUPPORTED ) {
		}
		else {
			return -1;
		}
		if ( u64value ) 
			*u64value = (uint64_t)(value_double*1000.0f);
		if ( s32value )
			*s32value = ((int32_t)value_double) - 4;
		release_amf_string(value_string);
		return 0;
	}
	return -1;
}

int parse_array(flv1info_t* info, int32_t max_pos, int parse_index, const char* key_name) {
	int32_t cur_pos = io_get_position(info->handle);
	if ( cur_pos < max_pos ) {
		
		int32_t array_size = (int32_t)io_read_be32(info->handle);
		
		if ( array_size > 0 ) {
			int timecode_flag, offset_flag;
			timecode_flag = offset_flag = 0;
			if ( key_name && parse_index ) {
				if ( strcmp(key_name, "filepositions") == 0 ) {
					if ( info->indexes ) {
						if ( info->total_indexes > array_size )
							info->total_indexes = array_size;
					}
					else {
						info->indexes = (flv1info_index_t*)js_malloc(array_size*sizeof(flv1info_index_t));
						if(!info->indexes)
							return -1;
						info->total_indexes = array_size;
					}
					timecode_flag = 0;
					offset_flag = 1;
				}
				else if ( strcmp(key_name, "times") == 0 ) {
					if ( info->indexes ) {
						if ( info->total_indexes > array_size )
							info->total_indexes = array_size;
					}
					else {
						info->indexes = (flv1info_index_t*)js_malloc(array_size*sizeof(flv1info_index_t));
						if(!info->indexes)
							return -1;
						info->total_indexes = array_size;
					}
					timecode_flag = 1;
					offset_flag = 0;
				}
			}
			int32_t i;
			for( i = 0; i < array_size; i++ ) {
				if ( parse_array_item(info, max_pos, parse_index, 
					((timecode_flag && i < info->total_indexes)?(&(info->indexes[i].timecode)):0),
					((offset_flag && i < info->total_indexes)?(&(info->indexes[i].filepos)):0)) < 0 )
					return -1;
			}
		}
		
		return 0;
	}
	return -1;
}

int parse_mixedarray_or_object(flv1info_t* info, int32_t max_pos, int parse_index, int is_mixedarray) {
	int32_t cur_pos = io_get_position(info->handle);
	if ( cur_pos < max_pos ) {
		
		if ( is_mixedarray )
			io_read_be32(info->handle); //32-bit max array index
		while(1) {
			double value_double = 0.0f;
			uint8_t value_boolean = 0;
			char* value_string = 0;
			uint16_t key_size = io_read_be16(info->handle);
			if ( key_size == 0 ) {
				uint8_t end_flag = io_read_8(info->handle);
				if (end_flag == FLV1_AMF_END_OF_OBJECT)
					return 0;
				else
					return -1;
			}
			char* key_name = get_amf_string(info, key_size);
			if ( !key_name )
				return -1;
			
			uint8_t value_type = io_read_8(info->handle);
			if ( value_type == AMF_DATA_TYPE_NUMBER ) {
				uint64_t temp = io_read_be64(info->handle);
				value_double = *((double*)&temp);
			}
			else if ( value_type == AMF_DATA_TYPE_BOOL ) { 
				value_boolean = io_read_8(info->handle);
			}
			else if ( value_type == AMF_DATA_TYPE_STRING ) {
				uint16_t value_size = io_read_be16(info->handle);
				if ( value_size != 0 ) {
					//value_string = get_amf_string(info, value_size);
					//just skip string
					io_set_position(info->handle, io_get_position(info->handle)+value_size);
				}
			}
			else if ( value_type == AMF_DATA_TYPE_DATE ) {
				io_read_be64(info->handle);
				io_read_be16(info->handle);
			}
			else if ( value_type == AMF_DATA_TYPE_OBJECT ) {
				if ( parse_mixedarray_or_object(info, max_pos, parse_index, 0) < 0 ) {
					release_amf_string(key_name);
					return -1;
				}
			}
			else if ( value_type == AMF_DATA_TYPE_ARRAY ) {
				if ( parse_array(info, max_pos, parse_index, key_name) < 0 ) {
					release_amf_string(key_name);
					return -1;
				}
			}
			else if ( value_type == AMF_DATA_TYPE_MIXEDARRAY) {
				if ( parse_mixedarray_or_object(info, max_pos, parse_index, 1) < 0 ) {
					release_amf_string(key_name);
					return -1;
				}
			}
			else if ( value_type == AMF_DATA_TYPE_NULL || 
				value_type == AMF_DATA_TYPE_UNDEFINED ||
				value_type == AMF_DATA_TYPE_UNSUPPORTED ) {
			}
			else {
				release_amf_string(key_name);
				return -1;
			}
			
			if ( is_mixedarray ) {
				if( strcmp(key_name, "duration") == 0 ) 
					info->duration = value_double;
				else if ( strcmp(key_name, "width") == 0 )
					info->width = (uint32_t)value_double;
				else if ( strcmp(key_name, "height") == 0 )
					info->height = (uint32_t)value_double;
			}
			
			release_amf_string(key_name);
			release_amf_string(value_string);
			
		}
	
		return 0;
		
	}
	return -1;
}

void parse_meta_tag(flv1info_t* info, int32_t max_pos, int parse_index) {
	int32_t cur_pos = io_get_position(info->handle);
	if ( cur_pos < max_pos ) {
		
		 //first object needs to be "onMetaData" string
		uint8_t type = io_read_8(info->handle);
		if ( type != AMF_DATA_TYPE_STRING )
			return;
		
		uint16_t size = io_read_be16(info->handle);
		if (size != 0x000A)
			return;
		char* str = get_amf_string(info, size);
		if ( ! (str && strcmp(str, "onMetaData")==0) ) {
			release_amf_string(str);
			return;
		}
		release_amf_string(str);
		
		type = io_read_8(info->handle);
		if ( type != AMF_DATA_TYPE_MIXEDARRAY )
			return;
		
		parse_mixedarray_or_object(info, max_pos, parse_index, 1);
		
	}
}

void parse_flv1_body(flv1info_t* info, int parse_index) {
	int audio_ok, video_ok, meta_ok;
	audio_ok = video_ok = meta_ok = 0;
	
	uint32_t first_video_time_stamp = 0;
	int is_first_video_frame = 1;
	
	while(io_get_position(info->handle) < io_get_length(info->handle)) {
		
		if ( audio_ok && video_ok && meta_ok )
			break;
		
		/*int32_t pos = */io_get_position(info->handle);
		int32_t next;
		
		uint8_t tag_type;
		uint32_t data_size;
		uint32_t time_stamp, time_stamp_ext;
		
		io_read_be32(info->handle);//prev tag size
		tag_type = io_read_8(info->handle);
		data_size = io_read_be24(info->handle);
		time_stamp = io_read_be24(info->handle);
		time_stamp_ext = io_read_8(info->handle);
		time_stamp |= (time_stamp_ext << 24);
		io_read_be24(info->handle); // stream Id
		
		if ( data_size == 0 )
			continue;
		
		next = data_size + io_get_position(info->handle);
		
		if ( tag_type == FLV1_TAG_TYPE_AUDIO ) {
			if ( !audio_ok ) {
				parse_audio_tag(info);
				if( info->audio_type != 0x00000000 )
					audio_ok = 1;
			}
		}
		else if ( tag_type == FLV1_TAG_TYPE_VIDEO) {
			if ( !video_ok ) {
				if ( info->video_frame_duration == 0 ) {
					if ( is_first_video_frame ) { 
						first_video_time_stamp = time_stamp;
						is_first_video_frame = 0;
					}
					else {
						info->video_frame_duration = time_stamp - first_video_time_stamp;
						info->video_scale = 1000;
					} 
				}
				if ( info->video_type == 0x00000000 ) {
					parse_video_tag(info);
				}
				if ( info->video_frame_duration != 0 && info->video_type != 0x00000000 )
					video_ok = 1;
			}
		}
		else if ( tag_type == FLV1_TAG_TYPE_SCRIPT_DATA) {
			if ( !meta_ok ) {
				parse_meta_tag(info, next, parse_index);
				meta_ok = 1;
			}
		}
		io_set_position(info->handle, next);
	}
}

void build_index(flv1info_t* info){
	while(io_get_position(info->handle) < io_get_length(info->handle)) {
		int32_t pos = io_get_position(info->handle);
		int32_t next;
		
		uint8_t tag_type;
		uint32_t data_size;
		uint32_t time_stamp, time_stamp_ext;
		
		io_read_be32(info->handle);//prev tag size
		tag_type = io_read_8(info->handle);
		data_size = io_read_be24(info->handle);
		time_stamp = io_read_be24(info->handle);
		time_stamp_ext = io_read_8(info->handle);
		time_stamp |= (time_stamp_ext << 24);
		io_read_be24(info->handle); // stream Id
		
		if ( data_size == 0 )
			continue;
		
		next = data_size + io_get_position(info->handle);
		
		if ( tag_type == FLV1_TAG_TYPE_VIDEO) {
			
			uint8_t video_flag = io_read_8(info->handle);
			
			if ( (video_flag & FLV1_VIDEO_FRAMETYPE_MASK) == 0x10 ) {
			
				if(info->total_indexes % 64 == 0){
					if(info->total_indexes == 0)
						info->indexes = (flv1info_index_t*)js_malloc(sizeof(flv1info_index_t) * 64);
					else
						info->indexes = (flv1info_index_t*)js_realloc(info->indexes, sizeof(flv1info_index_t) * (info->total_indexes + 64));
					if(!info->indexes){
						return;
					}
				}
				
				info->indexes[info->total_indexes].timecode = time_stamp;
				info->indexes[info->total_indexes].filepos = pos;
				info->total_indexes++;
			}
		}
		io_set_position(info->handle, next);
	}
}

void check_index(flv1info_t* info) {
	if ( !( info->indexes && info->total_indexes > 0 ) ) {
		if ( info->indexes ) {
			js_free(info->indexes);
			info->indexes = 0;
		}
		build_index(info);
	}
}

void parse_flv1(flv1info_t* info, int parse_index) {
	uint8_t flv1_header[9];
	memset(flv1_header, 0, 9);
	
	if ( io_read_data(info->handle, flv1_header, 9) == 9 ) {
	
		if ( flv1_header[0] == 'F' && flv1_header[1] == 'L' && flv1_header[2] == 'V' && flv1_header[3] == 1 ) {
			uint32_t a, b, c, d;
			a = flv1_header[5];
			b = flv1_header[6];
			c = flv1_header[7];
			d = flv1_header[8];
		
			info->data_start = (a<<24) | (b<<16) | (c<<8) | d;
		
			if (info->data_start >= 0 && info->data_start < io_get_length(info->handle)) {
				io_set_position(info->handle, info->data_start);
				parse_flv1_body(info, parse_index);
				
				if ( parse_index ) {
					io_set_position(info->handle, info->data_start);
					check_index(info);
				}
			}
		}
	}
}
