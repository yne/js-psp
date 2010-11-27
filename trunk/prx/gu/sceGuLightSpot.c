/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightSpot(int index, const ScePspFVector3* direction, float f12, float f13) // inner & outer cone?
{
	GuLightSettings* settings = &light_settings[index];

	sendCommandf(settings->row3[2],f12);
	sendCommandf(settings->row3[3],f13);

	sendCommandf(settings->row1[1],direction->x);
	sendCommandf(settings->row1[2],direction->y);
	sendCommandf(settings->row1[3],direction->z);
}
