/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSignal(int a0, int a1)
{
	sendCommandi(14,((a0 & 0xff) << 16) | (a1 & 0xffff));
	sendCommandi(12,0);

	if (a0 == 3)
		sendCommandi(15,0);

	sendCommandiStall(0,0);
}
