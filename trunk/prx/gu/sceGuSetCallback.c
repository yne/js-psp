/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void* sceGuSetCallback(int index, GuCallback callback)
{
	GuCallback old_callback = 0;

	if (index == 1)
	{
		old_callback = gu_settings.sig;
		gu_settings.sig = callback;
	}
	else if (index == 4)
	{
		old_callback = gu_settings.fin;
		gu_settings.fin = callback;
	}

	return old_callback;
}
