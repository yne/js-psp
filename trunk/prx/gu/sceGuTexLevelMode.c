/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <math.h>

float truncf(float);

void sceGuTexLevelMode(unsigned int a0, float f12)
{
	int offset = (int)truncf(f12 * 16.0f);

	// mip map bias?
	if (offset >= 128)
		offset = 128;
	else if (offset < -128)
		offset = -128;

	sendCommandi(200,(((unsigned int)(offset)) << 16) | a0);
}
