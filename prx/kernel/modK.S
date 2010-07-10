	.set noreorder

#include "pspstub.s"

	STUB_START "modK",0x40090000,0x00030005
	STUB_FUNC  0xF1275C31,Kfun
	STUB_FUNC  0xC871B53E,modK_GetFun
	STUB_FUNC  0x98A53436,modK_GetVar
	STUB_END
