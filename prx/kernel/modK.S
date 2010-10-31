	.set noreorder

#include "pspstub.s"

	STUB_START "modK",0x40090000,0x00040005
	STUB_FUNC  0x4F663338,loadModBuf
	STUB_FUNC  0x8B749527,my_addModule
	STUB_FUNC  0xBA953E2D,KCall
	STUB_FUNC  0x76846F7A,js_searchInfo
	STUB_END
