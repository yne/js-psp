	.set noreorder

#include "pspstub.s"

	STUB_START "JSE",0x00090000,0x00010005
	STUB_FUNC  0x95935AFC,js_test
	STUB_END
