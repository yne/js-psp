#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceIo",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

/*
int sceIoDevctl           (const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
int sceIoAssign           (const char *dev1, const char *dev2, const char *dev3, int mode, void* unk1, long unk2);
int sceIoUnassign         (const char *dev);
int sceIoGetstat          (const char *file, SceIoStat *stat);
int sceIoChstat           (const char *file, SceIoStat *stat, int bits);
int sceIoIoctl            (SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
int sceIoIoctlAsync       (SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

int sceIoWaitAsync        (SceUID fd, SceInt64 *res);
int sceIoWaitAsyncCB      (SceUID fd, SceInt64 *res);
int sceIoPollAsync        (SceUID fd, SceInt64 *res);
int sceIoGetAsyncStat     (SceUID fd, int poll, SceInt64 *res);
int sceIoCancel           (SceUID fd);
int sceIoGetDevType       (SceUID fd);
int sceIoChangeAsyncPriority(SceUID fd, int pri);
int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void *argp);
*/
JS_FUN(Open){
	*rval = I2J(sceIoOpen(J2S(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(OpenAsync){
	*rval = I2J(sceIoOpenAsync(J2S(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(Dopen){
	*rval = I2J(sceIoDopen(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(Lseek){
	*rval = I2J(sceIoLseek(J2I(argv[0]),J2L(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(Close){
	*rval = I2J(sceIoClose(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(CloseAsync){
	*rval = I2J(sceIoCloseAsync(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(Read){
	*rval = I2J(sceIoRead(J2I(argv[0]),(void*)J2U(argv[1]),J2U(argv[2])));
	return JS_TRUE;
}
JS_FUN(ReadAsync){
	*rval = I2J(sceIoReadAsync(J2I(argv[0]),(void*)J2U(argv[1]),J2U(argv[2])));
	return JS_TRUE;
}
JS_FUN(Write){
	*rval = I2J(sceIoWrite(J2I(argv[0]),(void*)J2U(argv[1]),J2U(argv[2])));
	return JS_TRUE;
}
JS_FUN(WriteAsync){
	*rval = I2J(sceIoWriteAsync(J2I(argv[0]),(void*)J2U(argv[1]),J2U(argv[2])));
	return JS_TRUE;
}
JS_FUN(LseekAsync){
	*rval = I2J(sceIoLseekAsync(J2I(argv[0]),J2L(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(Lseek32){
	*rval = I2J(sceIoLseek32(J2I(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(Lseek32Async){
	*rval = I2J(sceIoLseek32Async(J2I(argv[0]),J2I(argv[1]),J2I(argv[2])));
	return JS_TRUE;
}
JS_FUN(Remove){
	if(js_typeOfValue(argv[0])==JSTYPE_OBJECT)
		*rval = I2J(sceIoRemove(J2S(js_getProperty(J2O(argv[0]),"path"))));
	else
		*rval = I2J(sceIoRemove(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(Mkdir){
	*rval = I2J(sceIoMkdir(J2S(argv[0]),J2I(argv[1])?J2I(argv[1]):0777));
	return JS_TRUE;
}
JS_FUN(Rmdir){
	*rval = I2J(sceIoRmdir(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(Chdir){
	*rval = I2J(sceIoChdir(J2S(argv[0])));
	return JS_TRUE;
}
JS_FUN(Rename){
	*rval = I2J(sceIoRename(J2S(argv[0]),J2S(argv[1])));
	return JS_TRUE;
}
JS_FUN(Dread){
	SceIoDirent ent;
	memset(&ent, 0, sizeof(SceIoDirent));
	*rval = I2J(sceIoDread(J2I(argv[0]),&ent));
	return JS_TRUE;
}
JS_FUN(Dclose){
	*rval = I2J(sceIoDclose(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(Devctl){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Assign){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Unassign){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Getstat){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Chstat){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Ioctl){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(IoctlAsync){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Sync){
	*rval = I2J(sceIoSync(J2S(argv[0]),J2U(argv[1])));
	return JS_TRUE;
}
JS_FUN(WaitAsync){
	*rval = I2J(sceIoWaitAsync(J2I(argv[0]),0));//J2L(argv[1])
	return JS_TRUE;
}
JS_FUN(WaitAsyncCB){
	*rval = I2J(sceIoWaitAsyncCB(J2I(argv[0]),0));//J2L(argv[1])
	return JS_TRUE;
}
JS_FUN(PollAsync){
	*rval = I2J(sceIoPollAsync(J2I(argv[0]),0));//J2L(argv[1])
	return JS_TRUE;
}
JS_FUN(GetAsyncStat){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(Cancel){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(GetDevType){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(ChangeAsyncPriority){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(SetAsyncCallback){
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JS_FUN(File){
	JSObject* file = js_addObj(" ");
	int fd = sceIoOpen(J2S(argv[0]),argv[1]?argv[1]:(PSP_O_CREAT|PSP_O_RDONLY|PSP_O_WRONLY),0777);
	int size = sceIoLseek(fd,0,SEEK_END);
	void* p = js_malloc(size);
	sceIoRead(fd,p,size);
	js_setProperty(file,"_type",argv[0]);
	js_setProperty(file,"path",argv[0]);
	js_setProperty(file,"data",I2J((u32)p));
	js_setProperty(file,"fd",I2J(fd));
	js_setProperty(file,"length",I2J(size));
	*rval = O2J(file);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"Open",Open,3},
	{"OpenAsync",OpenAsync,3},
	{"Dopen",Dopen,1},
	{"Lseek",Lseek,3},
	{"Close",Close,1},
	{"CloseAsync",CloseAsync,1},
	{"Read",Read,3},
	{"ReadAsync",ReadAsync,3},
	{"Write",Write,3},
	{"WriteAsync",WriteAsync,3},
	{"LseekAsync",LseekAsync,3},
	{"Lseek32",Lseek32,3},
	{"Lseek32Async",Lseek32Async,3},
	{"Remove",Remove,1},
	{"Mkdir",Mkdir,2},
	{"Rmdir",Rmdir,1},
	{"Chdir",Chdir,1},
	{"Rename",Rename,2},
	{"Dread",Dread,2},
	{"Dclose",Dclose,1},
	{"Devctl",Devctl,6},
	{"Assign",Assign,6},
	{"Unassign",Unassign,1},
	{"Getstat",Getstat,2},
	{"Chstat",Chstat,3},
	{"Ioctl",Ioctl,6},
	{"IoctlAsync",IoctlAsync,6},
	{"Sync",Sync,2},
	{"WaitAsync",WaitAsync,2},
	{"WaitAsyncCB",WaitAsyncCB,2},
	{"PollAsync",PollAsync,2},
	{"GetAsyncStat",GetAsyncStat,3},
	{"Cancel",Cancel,1},
	{"GetDevType",GetDevType,1},
	{"ChangeAsyncPriority",ChangeAsyncPriority,2},
	{"SetAsyncCallback",SetAsyncCallback,3},
	{0}
};
static JSFunctionSpec gfunctions[] = {
/* new */
	{"File",File,1},
/* global */
	{"sceIoOpen",Open,3},
	{"sceIoOpenAsync",OpenAsync,3},
	{"sceIoDopen",Dopen,1},
	{"sceIoLseek",Lseek,3},
	{"sceIoClose",Close,1},
	{"sceIoCloseAsync",CloseAsync,1},
	{"sceIoRead",Read,3},
	{"sceIoReadAsync",ReadAsync,3},
	{"sceIoWrite",Write,3},
	{"sceIoWriteAsync",WriteAsync,3},
	{"sceIoLseekAsync",LseekAsync,3},
	{"sceIoLseek32",Lseek32,3},
	{"sceIoLseek32Async",Lseek32Async,3},
	{"sceIoRemove",Remove,1},
	{"sceIoMkdir",Mkdir,2},
	{"sceIoRmdir",Rmdir,1},
	{"sceIoChdir",Chdir,1},
	{"sceIoRename",Rename,2},
	{"sceIoDread",Dread,2},
	{"sceIoDclose",Dclose,1},
	{"sceIoDevctl",Devctl,6},
	{"sceIoAssign",Assign,6},
	{"sceIoUnassign",Unassign,1},
	{"sceIoGetstat",Getstat,2},
	{"sceIoChstat",Chstat,3},
	{"sceIoIoctl",Ioctl,6},
	{"sceIoIoctlAsync",IoctlAsync,6},
	{"sceIoSync",Sync,2},
	{"sceIoWaitAsync",WaitAsync,2},
	{"sceIoWaitAsyncCB",WaitAsyncCB,2},
	{"sceIoPollAsync",PollAsync,2},
	{"sceIoGetAsyncStat",GetAsyncStat,3},
	{"sceIoCancel",Cancel,1},
	{"sceIoGetDevType",GetDevType,1},
	{"sceIoChangeAsyncPriority",ChangeAsyncPriority,2},
	{"sceIoSetAsyncCallback",SetAsyncCallback,3},
	{0}
};
static JSPropertiesSpec var[] = {
	{"IOASSIGN_RDWR", I2J(0)},
	{"IOASSIGN_RDONLY", I2J(1)},
	{"PSP_O_RDONLY", I2J(0x0001)},
	{"PSP_O_WRONLY", I2J(0x0002)},
	{"PSP_O_RDWR", I2J(PSP_O_RDONLY|PSP_O_WRONLY)},
	{"PSP_O_NBLOCK", I2J(0x0004)},
	{"PSP_O_DIROPEN", I2J(0x0008)},
	{"PSP_O_APPEND", I2J(0x0100)},
	{"PSP_O_CREAT", I2J(0x0200)},
	{"PSP_O_TRUNC", I2J(0x0400)},
	{"PSP_O_EXCL", I2J(0x0800)},
	{"PSP_O_NOWAIT", I2J(0x8000)},
	{"PSP_SEEK_SET", I2J(0)},
	{"PSP_SEEK_CUR", I2J(1)},
	{"PSP_SEEK_END", I2J(2)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,gfunctions,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
