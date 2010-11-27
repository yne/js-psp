/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClear(int flags)
{
  GuContext* context = &gu_contexts[gu_curr_context];
  unsigned int filter;

  switch (gu_draw_buffer.pixel_size)
  {
    case 0: filter = context->clear_color & 0xffffff; break;
    case 1: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 31); break;
    case 2: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 28); break;
    case 3: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 24); break;
    default: filter = 0; break;
  }

  short* buffer;
  int count;

  if (!(flags & 0x10))
  {
    buffer = (short*)sceGuGetMemory(12*sizeof(short));
    count = 2;

	buffer[0] = 0;						// 0-1
	buffer[1] = 0;						// 2-3
	buffer[2] = 0;						// 4-5
    buffer[3] = 0;						// 6-6
    buffer[4] = context->clear_depth;	// 8-9
	// 10-11 - align
    ((unsigned int*)buffer)[3] = filter;// 12-15
    buffer[8] = gu_draw_buffer.width;	// 16-17
    buffer[9] = gu_draw_buffer.height;	// 18-19
    buffer[10] = context->clear_depth;	// 20-21
  }
  else
  {
    short* curr;
    unsigned int i;

    buffer = (short*)sceGuGetMemory(96*sizeof(short));
    curr = buffer;
    count = 16;

    for (i = 0; i < 16; ++i, curr += 6)
    {
      unsigned int j,k;

      j = ((int)((i >> 31) + i)) >> 1;
      k = (i - (j << 1));

      *((unsigned int*)curr) = filter;
      curr[2] = (j-k) << 6;
      curr[3] = k * gu_draw_buffer.height;
      curr[4] = context->clear_depth;
    }

  }

   sendCommandi(211,((flags & 0x07) << 8) | 0x01);
   sceGuDrawArray(6,GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D,count,0,buffer);
   sendCommandi(211,0);
}
