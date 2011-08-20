	.set noreorder

#include "pspstub.s"

	STUB_START "OpenTube",0x00090000,0x00010005
	STUB_FUNC  0x3E3258CE,otGetCtx
	STUB_END
