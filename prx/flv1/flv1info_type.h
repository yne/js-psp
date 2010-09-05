/* 
 *	Copyright (C) 2009 cooleyes
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
 
#ifndef __FLV1INFO_TYPE_H__
#define __FLV1INFO_TYPE_H__

#include <pspiofilemgr.h>

typedef struct {
	uint64_t timecode;
	int32_t filepos;
} flv1info_index_t;

typedef struct {
	void* handle;
	
	double duration;
	
	uint32_t video_type;
	uint32_t audio_type;
	
	uint32_t video_scale;
	uint32_t video_frame_duration;
	
	uint32_t width;
	uint32_t height;
	
	uint32_t channels;
	uint32_t samplerate;
	uint32_t samplebits;
	uint32_t samples_per_frame;
	
	uint32_t avc_profile;
	uint32_t avc_sps_size;
	uint8_t* avc_sps;
	uint32_t avc_pps_size;
	uint8_t* avc_pps;
	uint32_t avc_nal_prefix_size;
	
	int32_t data_start;
	int32_t total_indexes;
	flv1info_index_t* indexes;
	
} flv1info_t;

#endif
