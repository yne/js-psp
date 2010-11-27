/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLight(int light, int type, int components, const ScePspFVector3* position)
{
	GuLightSettings* settings = &light_settings[light];

	sendCommandf(settings->row0[2],position->x);
	sendCommandf(settings->row0[3],position->y);
	sendCommandf(settings->row1[0],position->z);

	int kind = 2;
	if (components != 8)
		kind = (components^6) < 1 ? 1 : 0;

	sendCommandi(settings->row0[1],((type & 0x03) << 8)|kind);
}
