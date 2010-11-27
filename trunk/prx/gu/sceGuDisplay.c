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

int sceGuDisplay(int state)
{
	if (state)
		sceDisplaySetFrameBuf((void*)((unsigned int)ge_edram_address+(unsigned int)gu_draw_buffer.disp_buffer),gu_draw_buffer.frame_width,gu_draw_buffer.pixel_size,1);
	else
		sceDisplaySetFrameBuf(0,0,0,1);

	gu_display_on = state;
	return state;
}
