/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

int sceGuSync(int mode, int a1)
{
	switch (mode)
	{
		case 0: return sceGeDrawSync(a1); break;
		case 3: return sceGeDrawSync(ge_list_executed[0]);
		case 4: return sceGeDrawSync(ge_list_executed[1]);
		default: case 1: case 2: return 0;
	}
}
