/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSpriteMode(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
	GuContext* context = &gu_contexts[gu_curr_context];

	context->sprite_mode[0] = a0;
	context->sprite_mode[1] = a1;
	context->sprite_mode[2] = a2;
	context->sprite_mode[3] = a3;
}
