	.set noreorder

#include "pspstub.s"

	STUB_START "modU",0x00090000,0x00030005
	STUB_FUNC  0x52095D97,Ufun
	STUB_FUNC  0xDCE46B75,modU_GetFun
	STUB_FUNC  0x6F33DBD7,modU_GetVar
	STUB_END
