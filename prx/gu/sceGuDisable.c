/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDisable(int state)
{
  switch(state)
  {
    case 0: sendCommandi(34,0); break;
    case 1: sendCommandi(35,0); break;
    case 2:
    {
    	GuContext* context = &gu_contexts[gu_curr_context];
	context->scissor_enable = 0;
	sendCommandi(212,0);
	sendCommandi(213,((gu_draw_buffer.height-1) << 10)|(gu_draw_buffer.width-1));
    }
    break;
    case 3: sendCommandi(36,0); break;
    case 4: sendCommandi(33,0); break;
    case 5: sendCommandi(29,0); break;
    case 6: sendCommandi(32,0); break;
    case 7: sendCommandi(31,0); break;
    case 8: sendCommandi(28,0); break;
    case 9: sendCommandi(30,0); break;
    case 10: sendCommandi(23,0); break;
    case 11: sendCommandi(24,0); break;
    case 12: sendCommandi(25,0); break;
    case 13: sendCommandi(26,0); break;
    case 14: sendCommandi(27,0); break;
    case 15: sendCommandi(37,0); break;
    case 16: sendCommandi(38,0); break;
    case 17: sendCommandi(39,0); break;
    case 18: sendCommandi(40,0); break;
    case 19: sendCommandi(81,0); break;
    case 20: sendCommandi(56,0); break;
    case 21:
    {
	GuContext* context = &gu_contexts[gu_curr_context];
	context->unknown_state = 0;
	sendCommandi(201,context->texture_function);
    }
    break;
  }

  if (state < 22)
    gu_states &= ~(1 << state);
}
