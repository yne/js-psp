/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuEnable(int state)
{
  switch(state)
  {
    case 0: sendCommandi(34,1); break;
    case 1: sendCommandi(35,1); break;
    case 2:
    {
    	GuContext* context = &gu_contexts[gu_curr_context];
	context->scissor_enable = 1;
	sendCommandi(212,(context->scissor_start[1]<<10)|context->scissor_start[0]);
	sendCommandi(213,(context->scissor_end[1]<<10)|context->scissor_end[0]);
    }
    break;
    case 3: sendCommandi(36,1); break;
    case 4: sendCommandi(33,1); break;
    case 5: sendCommandi(29,1); break;
    case 6: sendCommandi(32,1); break;
    case 7: sendCommandi(31,1); break;
    case 8: sendCommandi(28,1); break;
    case 9: sendCommandi(30,1); break;
    case 10: sendCommandi(23,1); break;
    case 11: sendCommandi(24,1); break;
    case 12: sendCommandi(25,1); break;
    case 13: sendCommandi(26,1); break;
    case 14: sendCommandi(27,1); break;
    case 15: sendCommandi(37,1); break;
    case 16: sendCommandi(38,1); break;
    case 17: sendCommandi(39,1); break;
    case 18: sendCommandi(40,1); break;
    case 19: sendCommandi(81,1); break;
    case 20: sendCommandi(56,1); break;
    case 21:
    {
	GuContext* context = &gu_contexts[gu_curr_context];
	context->unknown_state = 0x10000;
	sendCommandi(201,0x10000|context->texture_function);
    }
    break;
  }

  if (state < 22)
    gu_states |= (1 << state);
}
