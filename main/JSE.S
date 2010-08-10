	.set noreorder

#include "pspstub.s"

	STUB_START "JSE",0x00090000,0x001A0005
	STUB_FUNC  0x95935AFC,js_test
	STUB_FUNC  0x8D642FB1,js_addModule
	STUB_FUNC  0x1776BE04,js_addObj
	STUB_FUNC  0xBBB84232,js_addClass
	STUB_FUNC  0x7AC58FDC,js_getContext
	STUB_FUNC  0x5E233C36,js_getGlobalObject
	STUB_FUNC  0x6EB05312,js_convertArguments
	STUB_FUNC  0xC501F7FB,js_getElement
	STUB_FUNC  0xA2574AA9,js_getProperty
	STUB_FUNC  0xAD977CC9,js_setProperty
	STUB_FUNC  0xADF72D92,js_getStringBytes
	STUB_FUNC  0xE76E2E93,js_newString
	STUB_FUNC  0xE4AB1197,js_convertValue
	STUB_FUNC  0x5C614B34,js_valueToNumber
	STUB_FUNC  0x8BF7443C,js_valueToObject
	STUB_FUNC  0x03A8718F,js_valueToString
	STUB_FUNC  0x12E80E83,js_valueToECMAUint32
	STUB_FUNC  0xDEF43686,js_valueToUint16
	STUB_FUNC  0x265E0E3A,js_evaluateScript
	STUB_FUNC  0x7803EBA9,js_typeOfValue
	STUB_FUNC  0x6C56460A,js_computeThis
	STUB_FUNC  0x3465956E,js_strdup
	STUB_FUNC  0xDFF11919,js_realloc
	STUB_FUNC  0xFC4105A3,js_malloc
	STUB_FUNC  0xDD8A2A2F,js_free
	STUB_FUNC  0x56589224,c_strlen
	STUB_END
