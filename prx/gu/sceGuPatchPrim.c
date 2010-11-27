/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchPrim(unsigned int a0)
{
	switch(a0)
	{
		case 0: sendCommandi(55,2); break;
		case 2: sendCommandi(55,1); break;
		case 4: sendCommandi(55,0); break;
	}
}
