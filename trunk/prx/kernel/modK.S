	.set noreorder

#include "pspstub.s"

	STUB_START "modK",0x40090000,0x00020005
	STUB_FUNC  0x203477E6,js_addKModule
	STUB_FUNC  0x76846F7A,js_searchInfo
	STUB_END
