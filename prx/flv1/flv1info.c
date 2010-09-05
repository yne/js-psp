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

#include "flv1.h"
#include "bufferedio.h"
#include "flv1info_type.h"
#include "../../main/shared.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

flv1info_t* flv1info_open(const char* filename, int parse_index) {
	flv1info_t* info = (flv1info_t*)js_malloc(sizeof(flv1info_t));
	if (!info)
		return 0;
	memset(info, 0, sizeof(flv1info_t));
	
	buffered_io_t io;	
	int32_t result = io_open(filename, (void*)(&io));
	if ( result < 0 ) {
		js_free(info);
		return 0;
	}
	info->handle = &io;
	parse_flv1(info, parse_index);
	io_close(&io);
	info->handle = 0;
		
	return info;
}

void flv1info_close(flv1info_t* info) {
	
	if (info) {
		if (info->avc_sps)
			js_free(info->avc_sps);
		if (info->avc_pps)
			js_free(info->avc_pps);
		if (info->indexes)
			js_free(info->indexes);
		js_free(info);
	}
}

