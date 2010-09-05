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

#include <stdlib.h>
#include <string.h>
#include "bufferedio.h"

int32_t io_open(const char* filename, void* handle) {
	buffered_io_t* io = (buffered_io_t*)handle;
	io->handle = sceIoOpen(filename, PSP_O_RDONLY, 0777);
	if ( io->handle < 0) {
		return -1;
	}
	io->cache_first_position = 0;
	io->cache_last_position = 0;
	io->current_position = 0;
	io->length = sceIoLseek32(io->handle, 0, PSP_SEEK_END);
	io_set_position(handle, 0);
	return 0;
}

void io_close(void* handle) {
	buffered_io_t* io = (buffered_io_t*)handle;
	sceIoClose(io->handle);
}
 
int32_t io_get_length(void* handle) {
	buffered_io_t* io = (buffered_io_t*)handle;
	return io->length;
}
 
int32_t io_set_position(void* handle, const int32_t position) {
	buffered_io_t* io = (buffered_io_t*)handle;
	if ( position >= io->cache_first_position && position < io->cache_last_position ) {
		io->current_position = position;
		return position;
	}
	if ( position < 0 ) {
		io->cache_first_position = sceIoLseek32(io->handle, 0, PSP_SEEK_SET);
		io->current_position = io->cache_first_position;
	}
	else if ( position >= io->length ) {
		io->cache_first_position = sceIoLseek32(io->handle, 0, PSP_SEEK_END);
		io->current_position = io->cache_first_position;
	}
	else {
		io->cache_first_position = sceIoLseek32(io->handle, (position & 0xFFFFFFC0), PSP_SEEK_SET);
		io->current_position = position;//io->cache_first_position;
	}
	io->cache_last_position = io->cache_first_position + CACHE_BUFFER_SIZE ;
	if ( io->cache_last_position >= io->length )
		io->cache_last_position = io->length;
	if ( io->cache_last_position - io->cache_first_position > 0 )
		sceIoRead(io->handle, io->cache_buffer, io->cache_last_position - io->cache_first_position);
	return io->current_position;
}

int32_t io_get_position(void* handle) {
	buffered_io_t* io = (buffered_io_t*)handle;
	return io->current_position;
}

uint32_t io_read_data(void* handle, uint8_t* data, uint32_t size) {
	
	buffered_io_t* io = (buffered_io_t*)handle;
	
	if ( io->current_position == io->length )
		return 0; 
	
	if ( size <= io->cache_last_position - io->current_position ) {
		memcpy(data, 
			io->cache_buffer+(io->current_position-io->cache_first_position),
			size);
		io->current_position+=size;
		if ( io->current_position == io->cache_last_position )
			io_set_position(handle, io->cache_last_position);
		return size; 
	}
	else {
		uint32_t data_size;
		memcpy(data, 
			io->cache_buffer+(io->current_position-io->cache_first_position),
			io->cache_last_position - io->current_position);
		data_size = (io->cache_last_position - io->current_position);
		io_set_position(io, io->cache_last_position);
		data_size += io_read_data(handle, data+data_size, size - data_size);
		return data_size;
	}
}

uint64_t io_read_be64(void* handle) {
	uint8_t data[8];
	uint64_t result = 0;
	int i;
	
	io_read_data(handle, data, 8);
	for (i = 0; i < 8; i++) {
		result |= ((uint64_t)data[i]) << ((7 - i) * 8);
	}

	return result;
}

uint32_t io_read_be32(void* handle) {
	uint8_t data[4];
	uint32_t result = 0;
	uint32_t a, b, c, d;
	
	io_read_data(handle, data, 4);
	a = (uint8_t)data[0];
	b = (uint8_t)data[1];
	c = (uint8_t)data[2];
	d = (uint8_t)data[3];
	result = (a<<24) | (b<<16) | (c<<8) | d;

	return result;
}

uint32_t io_read_be24(void* handle) {
	uint8_t data[4];
	uint32_t result = 0;
	uint32_t a, b, c;
	
	io_read_data(handle, data, 3);
	a = (uint8_t)data[0];
	b = (uint8_t)data[1];
	c = (uint8_t)data[2];
	result = (a<<16) | (b<<8) | c;

	return result;
}

uint16_t io_read_be16(void* handle) {
	uint8_t data[2];
	uint16_t result = 0;
	uint16_t a, b;
	
	io_read_data(handle, data, 2);
	a = (uint8_t)data[0];
	b = (uint8_t)data[1];
	result = (a<<8) | b;

	return result;
}

uint8_t io_read_8(void* handle){
	uint8_t result;
    
	io_read_data(handle, &result, 1);
    
	return result;
}

