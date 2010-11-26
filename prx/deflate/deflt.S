	.set noreorder

#include "pspstub.s"

	STUB_START "deflt",0x00090000,0x000C0005
	STUB_FUNC  0x44054E03,sceDeflateDecompress
	STUB_FUNC  0x6DBCF897,sceGzipDecompress
	STUB_FUNC  0xB767F9A0,sceGzipGetComment
	STUB_FUNC  0x0BA3B9CC,sceGzipGetCompressedData
	STUB_FUNC  0x8AA82C92,sceGzipGetInfo
	STUB_FUNC  0x106A3552,sceGzipGetName
	STUB_FUNC  0x1B5B82BC,sceGzipIsValid
	STUB_FUNC  0x2EE39A64,sceZlibAdler32
	STUB_FUNC  0xA9E4FB28,sceZlibDecompress
	STUB_FUNC  0x6A548477,sceZlibGetCompressedData
	STUB_FUNC  0xAFE01FD3,sceZlibGetInfo
	STUB_FUNC  0xE46EB986,sceZlibIsValid
	STUB_END
