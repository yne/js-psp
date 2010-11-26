#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <libdeflt.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceDeflt",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

JS_FUN(DeflateDecompress){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(GzipDecompress){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(GzipGetComment){
	if(!argc)return JS_TRUE;
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	char buf[10];
	sceIoRead(fd,buf,10);
	sceIoClose(fd);
	const char* com = sceGzipGetComment(buf);
	if(!com)return JS_TRUE;
	return JS_TRUE;
}
JS_FUN(GzipGetCompressedData){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(GzipGetInfo){
	if(!argc)return JS_TRUE;
	char buf[sizeof(SceGzipHeader)+128];
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	sceIoRead(fd,buf,sizeof(SceGzipHeader)+128);
	sceIoClose(fd);
	const char* Name;//,Comment;
	if(sceGzipGetInfo(buf,NULL,&Name,NULL,NULL,NULL)){
		return JS_TRUE;
	}
	//printf("%s\n",Name);
	*rval = S2J(Name);
	return JS_TRUE;
}
JS_FUN(GzipGetName){
		if(!argc)return JS_TRUE;
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	char buf[sizeof(SceGzipHeader)];
	sceIoRead(fd,buf,sizeof(SceGzipHeader));
	sceIoClose(fd);
	const char* name = sceGzipGetName(buf);
	if(!name)return JS_TRUE;
	return JS_TRUE;
}
JS_FUN(GzipIsValid){
	if(!argc)return JS_TRUE;
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	char buf[2];
	sceIoRead(fd,buf,2);
	sceIoClose(fd);
	*rval = I2J(sceGzipIsValid(buf));
	return JS_TRUE;
}
JS_FUN(ZlibAdler32){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(ZlibDecompress){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(ZlibGetCompressedData){
	*rval = I2J(1);
	return JS_TRUE;
}
JS_FUN(ZlibGetInfo){
	if(!argc)return JS_TRUE;
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	char buf[8];
	sceIoRead(fd,buf,8);
	sceIoClose(fd);
	unsigned char pbCmf,pbFlg;
	unsigned puiDictId;
	//const void **ppvData)
	if(!sceZlibGetInfo(buf,&pbCmf,&pbFlg,&puiDictId,NULL))
		return JS_TRUE;

	js_setProperty(obj,"flag",I2J(pbFlg));
	js_setProperty(obj,"comment",I2J(pbCmf));
	js_setProperty(obj,"dictId",I2J(puiDictId));
	*rval = O2J(obj);
	
	return JS_TRUE;
}
JS_FUN(ZlibIsValid){
	if(!argc)return JS_TRUE;
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777);
	char buf[2];
	sceIoRead(fd,buf,2);
	sceIoClose(fd);
	*rval = I2J(sceZlibIsValid(buf));
	return JS_TRUE;
}
static JSFunctionSpec gfun[] = {
	{"sceDeflateDecompress",DeflateDecompress,3},
	{"sceGzipDecompress",GzipDecompress,3},
	{"sceGzipGetComment",GzipGetComment,3},
	{"sceGzipGetCompressedData",GzipGetCompressedData,3},
	{"sceGzipGetInfo",GzipGetInfo,3},
	{"sceGzipGetName",GzipGetName,3},
	{"sceGzipIsValid",GzipIsValid,3},
	{"sceZlibAdler32",ZlibAdler32,3},
	{"sceZlibDecompress",ZlibDecompress,3},
	{"sceZlibGetCompressedData",ZlibGetCompressedData,3},
	{"sceZlibGetInfo",ZlibGetInfo,3},
	{"sceZlibIsValid",ZlibIsValid,3},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(0,gfun,0,0);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
