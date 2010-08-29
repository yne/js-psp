	.set noreorder

#include "pspstub.s"

	STUB_START "Ksample",0x40090000,0x00010005
	STUB_FUNC  0xE9FAA67D,Ksample_addModule
	STUB_END
