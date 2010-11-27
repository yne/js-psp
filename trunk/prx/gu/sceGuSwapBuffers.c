/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspdisplay.h>

void* sceGuSwapBuffers(void)
{
	// flush_font();

	// switch pointers

	void* temp = gu_draw_buffer.disp_buffer;
	gu_draw_buffer.disp_buffer = gu_draw_buffer.frame_buffer;
	gu_draw_buffer.frame_buffer = temp;

	if (gu_display_on)
		sceDisplaySetFrameBuf((void*)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, 0);

	gu_current_frame ^= 1;

	return gu_draw_buffer.frame_buffer;
}
