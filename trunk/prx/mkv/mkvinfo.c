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
 
#include "mkvinfo_type.h"
#include "bufferedio.h"
#include "ebml.h"
#include "../../main/shared.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

mkvinfo_t* mkvinfo_open(const char* filename) {
	mkvinfo_t* info = (mkvinfo_t*)js_malloc(sizeof(mkvinfo_t));
	if (!info)
		return 0;
	memset(info, 0, sizeof(mkvinfo_t));
	
	buffered_io_t io;	
	int32_t result = io_open(filename, (void*)(&io));
	if ( result < 0 ) {
		js_free(info);
		return 0;
	}
	info->handle = &io;
	parse_ebml(info);
	io_close(&io);
	info->handle = 0;
	
	return info;
}

void mkvinfo_close(mkvinfo_t* info) {
	int32_t i;
	
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
	if (info->indexes) {
		js_free(info->indexes);
		info->indexes = 0;
		info->total_indexes = 0;
	}

	for (i = 0; i < info->total_tracks; i++) {
		if (info->tracks[i]) {
			
			if (info->tracks[i]->private_data)
				js_free(info->tracks[i]->private_data);
			js_free(info->tracks[i]);
			info->tracks[i] = 0;
		}
	}
	
	if (info) js_free(info);
}
