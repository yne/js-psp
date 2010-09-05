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
 
#ifndef __MKVINFO_TYPE_H__
#define __MKVINFO_TYPE_H__

#include <pspiofilemgr.h>

#define MATROSKA_MAX_TRACKS 32

/* matroska track types */
#define MATROSKA_TRACK_VIDEO    0x01
#define MATROSKA_TRACK_AUDIO    0x02
#define MATROSKA_TRACK_COMPLEX  0x03
#define MATROSKA_TRACK_LOGO     0x10
#define MATROSKA_TRACK_SUBTITLE 0x11
#define MATROSKA_TRACK_CONTROL  0x20

typedef struct {
	int32_t tracknum;
	uint32_t type;
	uint32_t video_type;
	uint32_t audio_type;
	
	uint64_t time_scale;
	uint64_t duration;
		
	uint32_t width;
	uint32_t height;
	uint32_t display_width;
	uint32_t display_height;
	
	uint32_t channels;
	uint32_t samplerate;
	uint32_t samplebits;
	
	uint8_t* private_data;
	uint32_t private_size;
	
} mkvinfo_track_t;

typedef struct {
	int32_t tracknum;
	uint64_t timecode;
	int32_t filepos;
} mkvinfo_index_t;

typedef struct {
	void* handle;
	
	int32_t* parsed_cues;
	int32_t parsed_cues_num;
	int32_t* parsed_seekhead;
	int32_t parsed_seekhead_num;
	
	int32_t segment_start;
	
	uint64_t timecode_scale;
	uint64_t first_timecode;
  	int32_t has_first_timecode;
	uint64_t duration;
	
	mkvinfo_index_t* indexes;
	int32_t total_indexes;
	
	mkvinfo_track_t* tracks[MATROSKA_MAX_TRACKS];
	int32_t total_tracks;
		
} mkvinfo_t;

#endif
