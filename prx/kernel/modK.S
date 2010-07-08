	.set noreorder

#include "pspstub.s"

	STUB_START "modK",0x40090000,0x00010005
	STUB_FUNC  0xF1275C31,Kfun
	STUB_END
