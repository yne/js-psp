/* 
 *	Copyright (C) 2009 cooleyes
 *	eyes.cooleyes@gmail.com 
 *
 *  This Program is js_free software; you can redistribute it and/or modify
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "../../main/shared.h"
#include "bufferedio.h"
#include "mkvinfo_type.h"
#include "ebml_id.h"

#define FOURCC(a,b,c,d) \
	( ((uint32_t)d) | (((uint32_t)c) << 8) | (((uint32_t)b) << 16) | (((uint32_t)a) << 24) )

static double int2double(int64_t v){
    if(v+v > 0xFFEULL<<52)
        return 0.0/0.0;
    return ldexp(((v&((1LL<<52)-1)) + (1LL<<52)) * (v>>63|1), (v>>52&0x7FF)-1075);
}

static float int2float(int32_t v){
    if(v+v > 0xFF000000U)
        return 0.0/0.0;
    return ldexp(((v&0x7FFFFF) + (1<<23)) * (v>>31|1), (v>>23&0xFF)-150);
}

static uint32_t ebml_read_id(void* handle, int32_t* length) {
	int32_t i, len_mask = 0x80;
	uint32_t id;

	for (i=0, id=io_read_8(handle); i<4 && !(id & len_mask); i++)
		len_mask >>= 1;
	if (i >= 4)
		return EBML_ID_INVALID;
	if (length)
		*length = i + 1;
	while (i--)
		id = (id << 8) | io_read_8(handle);
	return id;
}


uint64_t ebml_read_length(void* handle, int32_t* length) {
	int32_t i, j, num_ffs = 0, len_mask = 0x80;
	uint64_t len;

	for (i=0, len=io_read_8(handle); i<8 && !(len & len_mask); i++)
		len_mask >>= 1;
	if (i >= 8)
		return EBML_UINT_INVALID;
	j = i+1;
	if (length)
		*length = j;
	if ((int)(len &= (len_mask - 1)) == len_mask - 1)
		num_ffs++;
	while (i--) {
		len = (len << 8) | io_read_8(handle);
		if ((len & 0xFF) == 0xFF)
			num_ffs++;
	}
	if (j == num_ffs)
		return EBML_UINT_INVALID;
	return len;
}

uint64_t ebml_read_uint(void* handle, uint64_t* length) {
	uint64_t len, value = 0;
	int32_t l;

	len = ebml_read_length (handle, &l);
	if (len == EBML_UINT_INVALID || len < 1 || len > 8)
		return EBML_UINT_INVALID;
	if (length)
		*length = len + l;

	while (len--)
		value = (value << 8) | io_read_8(handle);

	return value;
}


int64_t ebml_read_int(void* handle, uint64_t* length) {
	int64_t value = 0;
	uint64_t len;
	int32_t l;

	len = ebml_read_length (handle, &l);
	if (len == EBML_UINT_INVALID || len < 1 || len > 8)
		return EBML_INT_INVALID;
	if (length)
		*length = len + l;

	len--;
	l = io_read_8(handle);
	if (l & 0x80)
		value = -1;
	value = (value << 8) | l;
	while (len--)
		value = (value << 8) | io_read_8(handle);

	return value;
}

long double ebml_read_float(void* handle, uint64_t* length) {
	long double value;
	uint64_t len;
	int32_t l;

	len = ebml_read_length (handle, &l);
	switch (len) {
		case 4: {
			value = int2float(io_read_be32(handle));
			break;
		}
		case 8: {
			value = int2double(io_read_be64(handle));
			break;
		}
		default:
			return EBML_FLOAT_INVALID;
	}

	if (length)
		*length = len + l;

	return value;
}

char* ebml_read_ascii(void* handle, uint64_t* length) {
	uint64_t len;
	char* str = NULL;
	int32_t l;

	len = ebml_read_length (handle, &l);
	if (len == EBML_UINT_INVALID)
		return NULL;
	if (len > SIZE_MAX - 1)
		return NULL;
	if (length)
		*length = len + l;

	str = (char*)js_malloc(len+1);
	if (!str)
		return str;
	if (io_read_data(handle, str, len) != len) {
		js_free(str);
		return NULL;
    	}
	str[len] = '\0';

	return str;
}

char* ebml_read_utf8(void* handle, uint64_t* length) {
	return ebml_read_ascii(handle, length);
}

int32_t ebml_read_skip(void* handle, uint64_t* length) {
	uint64_t len;
	int32_t l;

	len = ebml_read_length (handle, &l);
	if (len == EBML_UINT_INVALID)
		return 1;
	if (length)
		*length = len + l;

	io_set_position(handle, io_get_position(handle)+len);

	return 0;
}

uint32_t ebml_read_master(void* handle, uint64_t* length) {
	uint64_t len;
	uint32_t id;

	id = ebml_read_id(handle, NULL);
	if (id == EBML_ID_INVALID)
		return id;

	len = ebml_read_length (handle, NULL);
	if (len == EBML_UINT_INVALID)
		return EBML_ID_INVALID;
	if (length)
		*length = len;

	return id;
}


char* ebml_read_header(void* handle, int32_t* version) {
	uint64_t length, l, num;
	uint32_t id;
	char* str = NULL;

	if (ebml_read_master(handle, &length) != EBML_ID_HEADER)
		return 0;

	if (version)
		*version = 1;

	while (length > 0) {
		id = ebml_read_id (handle, NULL);
		if (id == EBML_ID_INVALID)
			return NULL;
		length -= 2;

		switch (id) {
			case EBML_ID_EBMLREADVERSION: {
				num = ebml_read_uint (handle, &l);
				if (num != EBML_VERSION)
					return NULL;
				break;
			}
          
			case EBML_ID_EBMLMAXSIZELENGTH: {
				num = ebml_read_uint (handle, &l);
				if (num != sizeof (uint64_t))
					return NULL;
				break;
			}
        		
        		case EBML_ID_EBMLMAXIDLENGTH: {
				num = ebml_read_uint (handle, &l);
				if (num != sizeof (uint32_t))
					return NULL;
				break;
			}
			
			case EBML_ID_DOCTYPE: {
				str = ebml_read_ascii (handle, &l);
				if (str == NULL)
					return NULL;
				break;
			}
			
			case EBML_ID_DOCTYPEREADVERSION: {
				num = ebml_read_uint (handle, &l);
				if (num == EBML_UINT_INVALID)
					return NULL;
				if (version)
					*version = num;
				break;
			}
        		
        		case EBML_ID_VOID:
        		case EBML_ID_EBMLVERSION:
        		case EBML_ID_DOCTYPEVERSION:
        		default:
				if (ebml_read_skip (handle, &l))
					return NULL;
				break;
		}
		length -= l;
	}

	return str;
}

static int32_t parse_ebml_info(mkvinfo_t* info) {
	uint64_t length, l;
	int32_t il;
	uint64_t tc_scale = 1000000;
	long double duration = 0.;

	length = ebml_read_length(info->handle, NULL);
	while (length > 0) {
		switch (ebml_read_id(info->handle, &il)) {
			case MATROSKA_ID_TIMECODESCALE: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 1;
				tc_scale = num;
				break;
			}

			case MATROSKA_ID_DURATION: {
				long double num = ebml_read_float(info->handle, &l);
				if (num == EBML_FLOAT_INVALID)
					return 1;
				duration = num;
				break;
			}

			default:
				ebml_read_skip(info->handle, &l); 
				break;
		}
		length -= l + il;
	}
	info->timecode_scale = tc_scale;
	info->duration = (uint64_t)(duration * tc_scale / 1000000.0);
	return 0;
}

static void mkv_js_free_trackentry(mkvinfo_track_t* track) {
	if ( track ) {
		if (track->private_data) 
			js_free(track->private_data);
		js_free(track);
	}
}

static int32_t parse_ebml_trackaudio(mkvinfo_t* info, mkvinfo_track_t* track) {
	uint64_t len, length, l;
	int32_t il;

	len = length = ebml_read_length(info->handle, &il);
	len += il;
	while (length > 0) {
		switch(ebml_read_id(info->handle, &il)) {
			case MATROSKA_ID_AUDIOSAMPLINGFREQ: {
				long double num = ebml_read_float(info->handle, &l);
				if (num == EBML_FLOAT_INVALID)
					return 0;
				track->samplerate = (uint32_t)num;
				break;
			}

			case MATROSKA_ID_AUDIOBITDEPTH: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->samplebits = num;
				break;
			}

			case MATROSKA_ID_AUDIOCHANNELS: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->channels = num;
				break;
			}

			default:
				ebml_read_skip(info->handle, &l);
				break;
		}
		length -= l + il;
	}
	return len;
}

static int32_t parse_ebml_trackvideo(mkvinfo_t* info, mkvinfo_track_t* track) {
	uint64_t len, length, l;
	int32_t il;

	len = length = ebml_read_length(info->handle, &il);
	len += il;
	while (length > 0) {
		switch (ebml_read_id(info->handle, &il)) {

			case MATROSKA_ID_VIDEODISPLAYWIDTH: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->display_width = num;
				break;
			}

			case MATROSKA_ID_VIDEODISPLAYHEIGHT: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->display_height = num;
				break;
			}

			case MATROSKA_ID_VIDEOPIXELWIDTH: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->width = num;
				break;
			}

			case MATROSKA_ID_VIDEOPIXELHEIGHT: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->height = num;
				break;
			}

			default:
				ebml_read_skip(info->handle, &l);
				break;
		}
		length -= l + il;
	}
	return len;
}

static int32_t parse_ebml_trackencodings(mkvinfo_t* info, mkvinfo_track_t* track) {
	uint64_t len, length, l;
	int32_t il;

	len = length = ebml_read_length(info->handle, &il);
	len += il;
	while (length > 0) {
		switch (ebml_read_id(info->handle, &il)) {
			
			default:
				ebml_read_skip(info->handle, &l);
				break;
		}
		length -= l + il;
	}
	return len;
}

static int32_t parse_ebml_trackentry(mkvinfo_t* info) {
	mkvinfo_track_t* track;
	uint64_t len, length, l;
	int32_t il;

	track = js_malloc(sizeof(mkvinfo_track_t));
	memset(track, 0, sizeof(mkvinfo_track_t));
  
	len = length = ebml_read_length(info->handle, &il);
	len += il;
	while (length > 0) {
		switch (ebml_read_id(info->handle, &il)) {
			case MATROSKA_ID_TRACKNUMBER: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					goto err_out;
				track->tracknum = num;
				break;
			}
	          
			case MATROSKA_ID_TRACKTYPE: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					return 0;
				track->type = num;
				break;
			}
	
			case MATROSKA_ID_TRACKAUDIO : {
				l = parse_ebml_trackaudio(info, track);
				if (l == 0)
					goto err_out;
				break;
			}
	
			case MATROSKA_ID_TRACKVIDEO: {
				l = parse_ebml_trackvideo(info, track);
				if (l == 0)
					goto err_out;
				break;
			}
	
			case MATROSKA_ID_CODECID: {
				char* codec_id = ebml_read_ascii(info->handle, &l);
				if (codec_id == NULL)
					goto err_out;
				if (!strncmp(codec_id, MKV_A_AAC, strlen(MKV_A_AAC)))
					track->audio_type = FOURCC('m','p','4','a');
				else if (!strcmp (codec_id, MKV_V_MPEG4_AVC))
					track->video_type = FOURCC('a','v','c','1');
				else if (!strcmp(codec_id, MKV_V_MPEG4_AP) ||
					!strcmp(codec_id, MKV_V_MPEG4_SP) ||
					!strcmp(codec_id, MKV_V_MPEG4_ASP) )
						track->video_type = FOURCC('m','p','4','v');
				else if (!strcmp(codec_id, MKV_S_TEXTUTF8))
						track->video_type = FOURCC('t','x','t','u');
				else if (!strcmp(codec_id, MKV_S_TEXTASCII))
						track->video_type = FOURCC('t','x','t','l');
				else if (!strcmp(codec_id, MKV_S_TEXTSSA))
						track->video_type = FOURCC('s','s','a','u');
				else if (!strcmp(codec_id, MKV_S_TEXTASS))
						track->video_type = FOURCC('a','s','s','u');
				
				js_free(codec_id);
				break;
			}
	
			case MATROSKA_ID_CODECPRIVATE: {
				int32_t x;
				uint64_t num = ebml_read_length(info->handle, &x);
				if (num > SIZE_MAX - 1000) 
					goto err_out;
				l = x + num;
				track->private_data = js_malloc(num + MKV_INPUT_PADDING);
				if ( !track->private_data )
					goto err_out;
				if (io_read_data(info->handle, track->private_data, num) != num)
					goto err_out;
				track->private_size = num;
				break;
			}
	
			case MATROSKA_ID_TRACKDEFAULTDURATION: {
				uint64_t num = ebml_read_uint(info->handle, &l);
				if (num == EBML_UINT_INVALID)
					goto err_out;
				if (num == 0)
				;
				else {
					track->duration = num;
					track->time_scale = 1000000000;
				}
				break;
			}
	
			case MATROSKA_ID_TRACKENCODINGS: {
				l = parse_ebml_trackencodings(info, track);
				if (l == 0)
					goto err_out;
				break;
			}
			default:
				ebml_read_skip(info->handle, &l);
				break;
		}
		length -= l + il;
	}

	info->tracks[info->total_tracks++] = track;
	return len;

err_out:
	mkv_js_free_trackentry(track);
	return 0;
}

static int32_t parse_ebml_tracks(mkvinfo_t* info) {
	
	uint64_t length, l;
	int32_t i;

	info->total_tracks = 0;

	length = ebml_read_length(info->handle, NULL);
	while (length > 0) {
		switch (ebml_read_id(info->handle, &i)) {
			case MATROSKA_ID_TRACKENTRY:
          			l = parse_ebml_trackentry(info);
				if (l == 0)
					return 1;
				break;

			default:
				ebml_read_skip(info->handle, &l);
				break;
		}
		length -= l + i;
	}
  	return 0;
}

static int32_t parse_ebml_cues(mkvinfo_t* info) {
	uint64_t time, track, pos, block;
	int32_t off;
	uint64_t length0, length1, length2;
	int32_t i, i0, i1, i2;
	uint64_t l0, l1, l2;
	int32_t il0, il1;
	

	off = io_get_position(info->handle);
	for (i=0; i<info->parsed_cues_num; i++) {
		if (info->parsed_cues[i] == off) {
			ebml_read_skip(info->handle, NULL);
			return 0;
		}
	}
	
	info->parsed_cues = js_realloc(info->parsed_cues, (info->parsed_cues_num+1)*sizeof(int32_t));
	info->parsed_cues[info->parsed_cues_num++] = off;

	length0 = ebml_read_length(info->handle, NULL);

	while (length0 > 0) { //while level 0
		time = track = pos = EBML_UINT_INVALID;

		switch (ebml_read_id(info->handle, &i0)) {
			case MATROSKA_ID_POINTENTRY: {
				
				length1 = ebml_read_length(info->handle, &il0);
				l0 = length1 + il0;

				while (length1 > 0) { //while level 1
					
					switch(ebml_read_id(info->handle, &i1)) {
						case MATROSKA_ID_CUETIME:
							time = ebml_read_uint(info->handle, &l1);
							break;

						case MATROSKA_ID_CUETRACKPOSITION: {
							length2 = ebml_read_length(info->handle, &il1);
							l1 = length2 + il1;
							while (length2 > 0) { //while level 2
								
								switch (ebml_read_id(info->handle, &i2)) {
									case MATROSKA_ID_CUETRACK:
										track = ebml_read_uint(info->handle, &l2);
										break;

									case MATROSKA_ID_CUECLUSTERPOSITION:
										pos = ebml_read_uint(info->handle, &l2);
										break;
										
									case MATROSKA_ID_CUEBLOCKNUMBER:
										block = ebml_read_uint(info->handle, &l2);
										break;

									default:
										ebml_read_skip(info->handle, &l2);
										break;
								}
								length2 -= i2 + l2;
							}
							break;
						}

						default:
							ebml_read_skip(info->handle, &l1);
							break;
					}
					length1 -= i1 + l1;
				}
				break;
			}

			default:
				ebml_read_skip(info->handle, &l0);
				break;
		}

		length0 -= i0 + l0;

		if (time != EBML_UINT_INVALID && track != EBML_UINT_INVALID
			&& pos != EBML_UINT_INVALID) {
				
				if (!(info->total_indexes & 31))
					info->indexes = js_realloc(info->indexes, (info->total_indexes + 32) * sizeof(mkvinfo_index_t));
				
				info->indexes[info->total_indexes].tracknum = track;
				info->indexes[info->total_indexes].timecode = time;
				info->indexes[info->total_indexes].filepos = info->segment_start+pos;
				info->total_indexes++;
		}
	}

	return 0;
}

static int32_t parse_ebml_tags(mkvinfo_t* info) {
	ebml_read_skip (info->handle, NULL);
	return 0;
}

static int32_t parse_ebml_chapters(mkvinfo_t* info) {
	ebml_read_skip (info->handle, NULL);
	return 0;
}

static int32_t parse_ebml_attachments(mkvinfo_t* info) {
	ebml_read_skip (info->handle, NULL);
	return 0;
}

static int32_t parse_ebml_seekhead(mkvinfo_t* info) {
	uint64_t seek_pos, saved_pos, num;
	uint32_t seek_id;
	int32_t res = 0;
	int32_t off;
	
	uint64_t length0, length1;
	int32_t i,i0,i1;
	uint64_t l0,l1;
	int32_t il0;

	off = io_get_position(info->handle);
	for (i=0; i<info->parsed_seekhead_num; i++) {
		if (info->parsed_seekhead[i] == off) {
			ebml_read_skip(info->handle, NULL);
			return 0;
		}
	}
	
	info->parsed_seekhead = js_realloc(info->parsed_seekhead,  (info->parsed_seekhead_num+1)*sizeof(int32_t));
	info->parsed_seekhead[info->parsed_seekhead_num++] = off;

	length0 = ebml_read_length(info->handle, NULL);
	off = io_get_position(info->handle) + length0;
	while (length0 > 0 && !res) { // while level 0

		seek_id = 0;
		seek_pos = EBML_UINT_INVALID;

		switch (ebml_read_id(info->handle, &i0)) {
			case MATROSKA_ID_SEEKENTRY: {
				
				length1 = ebml_read_length(info->handle, &il0);
				l0 = length1 + il0;

				while (length1 > 0) { //while level 1
					
					switch (ebml_read_id(info->handle, &i1)) {
						case MATROSKA_ID_SEEKID:
							num = ebml_read_uint(info->handle, &l1);
							if (num != EBML_UINT_INVALID)
								seek_id = num;
							break;

						case MATROSKA_ID_SEEKPOSITION:
							seek_pos = ebml_read_uint(info->handle, &l1);
							break;

						default:
							ebml_read_skip(info->handle, &l1);
							break;
					}
					length1 -= i1 + l1;
				}

				break;
			}

			default:
				ebml_read_skip(info->handle, &l0);
				break;
		}
		length0 -= i0 + l0;

		if (seek_id == 0 || seek_id == MATROSKA_ID_CLUSTER
			|| seek_pos == EBML_UINT_INVALID ||
				((info->segment_start + seek_pos) >= io_get_length(info->handle)))
					continue;

		saved_pos = io_get_position(info->handle);
		if ( io_set_position(info->handle, info->segment_start + seek_pos) != (info->segment_start + seek_pos))
			res = 1;
		else {
			if (ebml_read_id(info->handle, &i0) != seek_id)
				res = 1;
			else {
				switch (seek_id) {
					case MATROSKA_ID_CUES:
						if (parse_ebml_cues (info))
							res = 1;
						break;

					case MATROSKA_ID_TAGS:
						if (parse_ebml_tags (info))
							res = 1;
						break;

					case MATROSKA_ID_SEEKHEAD:
						if (parse_ebml_seekhead (info))
							res = 1;
						break;

					case MATROSKA_ID_CHAPTERS:
						if (parse_ebml_chapters (info))
							res = 1;
						break;
				}
			}
		}

		io_set_position(info->handle, saved_pos);
	}
	if (res) {
		if (io_set_position(info->handle, off) == off)
			res = 0;
	}
	else
		if (length0 > 0)
			io_set_position(info->handle, io_get_position(info->handle) + length0);
	
	return res;
}

void parse_ebml(mkvinfo_t* info) {
	int32_t version;
	char* str;

	str = ebml_read_header(info->handle, &version);
	if (str == NULL || strcmp (str, "matroska") || version > 2) {
		return;
	}
	js_free (str);
	
	if (ebml_read_id (info->handle, NULL) != MATROSKA_ID_SEGMENT) {
		return;
	}
	ebml_read_length (info->handle, NULL); 
	
	info->timecode_scale = 1000000;
	info->segment_start = io_get_position(info->handle);
	
	info->parsed_cues = js_malloc(sizeof(int32_t));
	info->parsed_seekhead = js_malloc(sizeof(int32_t));
	
	int32_t res = 0;
	
	while (!res){
		switch (ebml_read_id (info->handle, NULL)) {
			case MATROSKA_ID_INFO: {
				res = parse_ebml_info(info);
				break;
			}

			case MATROSKA_ID_TRACKS: {
				res = parse_ebml_tracks(info);
				break;
			}
			
			case MATROSKA_ID_CUES: {
				res = parse_ebml_cues(info);
				break;
			}
			
			case MATROSKA_ID_TAGS: {
				res = parse_ebml_tags(info);
				break;
			}

			case MATROSKA_ID_SEEKHEAD: {
				res = parse_ebml_seekhead(info);
				break;
			}

			case MATROSKA_ID_CHAPTERS: {
				res = parse_ebml_chapters(info);
				break;
			}
			
			case MATROSKA_ID_ATTACHMENTS: {
				res = parse_ebml_attachments(info);
				break;
			}
			
			case MATROSKA_ID_CLUSTER: {
				int32_t p, l;
				p = io_get_position(info->handle);
				l = ebml_read_length(info->handle, NULL);
				while (ebml_read_id(info->handle, NULL) != MATROSKA_ID_CLUSTERTIMECODE) {
					ebml_read_skip(info->handle, NULL);
					if (io_get_position(info->handle) >= p + l)
						break;
				}
				if (io_get_position(info->handle) < p + l) {
					uint64_t num = ebml_read_uint(info->handle, NULL);
					if (num == EBML_UINT_INVALID)
						return;
					info->first_timecode = num;
					info->has_first_timecode = 1;
				}
				io_set_position(info->handle, p - 4);
				res = 1;
				break;
			}

			default:
				res = 1;
			case EBML_ID_VOID:
				ebml_read_skip(info->handle, NULL);
				break;
		}
	}
	
	if (info->parsed_cues) {
		js_free(info->parsed_cues);
		info->parsed_cues = 0;
		info->parsed_cues_num = 0;
	}
	if (info->parsed_seekhead) {
		js_free(info->parsed_seekhead);
		info->parsed_seekhead = 0;
		info->parsed_seekhead_num = 0;
	}
}

