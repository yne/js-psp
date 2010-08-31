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
	*rval = I2J(sceIoOpen(J2S(argv[0]),J2I(argv[1])?J2I(argv[1]):PSP_O_RDWR|PSP_O_CREAT,J2I(argv[2])?J2I(argv[2]):0777));
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
	int fd = sceIoOpen(J2S(argv[0]),PSP_O_CREAT|PSP_O_RDONLY|PSP_O_WRONLY,0777);
	js_setProperty(obj,"path",argv[0]);
	js_setProperty(obj,"fd",I2J(fd));
	js_setProperty(obj,"size",I2J(sceIoLseek32(fd,0,SEEK_END)));
	js_setProperty(obj,"pos" ,I2J(0));//updated by callback
	js_setProperty(obj,"date",I2J(0));//updated by callback
	sceIoLseek32(fd,0,SEEK_SET);
	return JS_TRUE;
}
JS_METH(file_write){
	u32 length;
	if(argc==1)
		length = js_getStringLength(JSVAL_TO_STRING(ARGV[0]));
	else
		length = J2I(ARGV[1]);
	*(vp) = I2J(sceIoWrite(J2I(js_getProperty(J2O(ARGV[-1]),"fd")),J2S(ARGV[0]),length));
	return JS_TRUE;
}
JS_METH(file_close){
	*(vp) = I2J(sceIoClose(J2I(js_getProperty(J2O(ARGV[-1]),"fd"))));
	return JS_TRUE;
}
JS_METH(file_rename){
	*(vp) = I2J(sceIoRename(J2S(js_getProperty(J2O(ARGV[-1]),"path")),J2S(ARGV[0])));
	js_setProperty(J2O(ARGV[-1]),"path",ARGV[0]);
	return JS_TRUE;
}
JS_METH(file_remove){
	*(vp) = I2J(sceIoRemove(J2S(js_getProperty(J2O(ARGV[-1]),"path"))));
	return JS_TRUE;
}
JS_METH(file_read){
	int fd = J2I(js_getProperty(J2O(ARGV[-1]),"fd"));
	u32 cur = sceIoLseek32(fd,0,SEEK_CUR);//save the current position
	u32 size = 0;
	switch(argc){
		case 0 :
			size = sceIoLseek32(fd,0,SEEK_END);
			sceIoLseek32(fd,0,SEEK_SET);
		break;
		case 1 :
			size = J2I(ARGV[1]);
		case 2 :
			size = J2I(ARGV[2]);
			sceIoLseek32(fd,J2I(ARGV[1]),PSP_SEEK_SET);
		break;
	}
	void* p = js_malloc(size);
	sceIoRead(fd,p,size);
	*(vp) = STRING_TO_JSVAL(js_newString(p,size));
	sceIoLseek32(fd,cur,SEEK_SET);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"open",Open,3},
	{"openAsync",OpenAsync,3},
	{"dopen",Dopen,1},
	{"lseek",Lseek,3},
	{"close",Close,1},
	{"closeAsync",CloseAsync,1},
	{"read",Read,3},
	{"readAsync",ReadAsync,3},
	{"write",Write,3},
	{"writeAsync",WriteAsync,3},
	{"lseekAsync",LseekAsync,3},
	{"lseek32",Lseek32,3},
	{"lseek32Async",Lseek32Async,3},
	{"remove",Remove,1},
	{"mkdir",Mkdir,2},
	{"rmdir",Rmdir,1},
	{"chdir",Chdir,1},
	{"rename",Rename,2},
	{"dread",Dread,2},
	{"dclose",Dclose,1},
	{"devctl",Devctl,6},
	{"assign",Assign,6},
	{"unassign",Unassign,1},
	{"getstat",Getstat,2},
	{"chstat",Chstat,3},
	{"ioctl",Ioctl,6},
	{"ioctlAsync",IoctlAsync,6},
	{"sync",Sync,2},
	{"waitAsync",WaitAsync,2},
	{"waitAsyncCB",WaitAsyncCB,2},
	{"pollAsync",PollAsync,2},
	{"getAsyncStat",GetAsyncStat,3},
	{"cancel",Cancel,1},
	{"getDevType",GetDevType,1},
	{"changeAsyncPriority",ChangeAsyncPriority,2},
	{"setAsyncCallback",SetAsyncCallback,3},
	{0}
};
static JSFunctionSpec gfunctions[] = {
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
static JSFunctionSpec fileMethodes[] = {
	JS_FN("remove",file_remove,0,0,0),
	JS_FN("rename",file_rename,2,0,0),
	JS_FN("read",  file_read,2,0,0),
	JS_FN("close", file_close,0,0,0),
	JS_FN("write", file_write,2,0,0),
	JS_FS_END
};
static JSBool class_get(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	char eval[64];
	SceIoStat stat;
	//printf("FILE < %s : %s\n",J2S(id),J2S(*vp));
	if(!strcmp(J2S(id),"pos")){
		*(vp) = I2J(sceIoLseek32(J2I(js_getProperty(obj,"fd")),0,SEEK_CUR));
	}else	if(!strcmp(J2S(id),"size")){
		sceIoGetstat(J2S(js_getProperty(obj,"path")),&stat);
		*(vp) = I2J(stat.st_size);
	}else if(!strcmp(J2S(id),"created")){
		sceIoGetstat(J2S(js_getProperty(obj,"path")),&stat);
		sprintf(eval,"new Date(%i,%i,%i,%i,%i,%i,%i)",stat.st_ctime.year,stat.st_ctime.month-1,stat.st_ctime.day,stat.st_ctime.hour,stat.st_ctime.minute,stat.st_ctime.second,stat.st_ctime.microsecond);
		*(vp) = js_evaluateScript(eval);
	}else if(!strcmp(J2S(id),"modified")){
		sceIoGetstat(J2S(js_getProperty(obj,"path")),&stat);
		sprintf(eval,"new Date(%i,%i,%i,%i,%i,%i,%i)",stat.st_mtime.year,stat.st_mtime.month-1,stat.st_mtime.day,stat.st_mtime.hour,stat.st_mtime.minute,stat.st_mtime.second,stat.st_mtime.microsecond);
		*(vp) = js_evaluateScript(eval);
	}else if(!strcmp(J2S(id),"accessed")){
		sceIoGetstat(J2S(js_getProperty(obj,"path")),&stat);
		sprintf(eval,"new Date(%i,%i,%i,%i,%i,%i,%i)",stat.st_atime.year,stat.st_atime.month-1,stat.st_atime.day,stat.st_atime.hour,stat.st_atime.minute,stat.st_atime.second,stat.st_atime.microsecond);
		*(vp) = js_evaluateScript(eval);
	}
	return JS_TRUE;
}
static JSBool class_set(JSContext *cx, JSObject *obj, jsval id, jsval *vp){
	if(!strcmp(J2S(id),"pos")){
		int fd = J2I(js_getProperty(obj,"fd"));
		u32 end = sceIoLseek32(fd,0,SEEK_END);
		if(J2I(*vp)>end)//try to go outside the file , return the end position
			*(vp) = I2J(sceIoLseek32(fd,end,SEEK_SET));
		else
			*(vp) = I2J(sceIoLseek32(fd,J2I(*vp),SEEK_SET));
	}else if(!strcmp(J2S(id),"size")){
		int fd = J2I(js_getProperty(obj,"fd"));
		u32 cur = sceIoLseek32(fd,0,SEEK_CUR);//get the current place
		*(vp) = sceIoLseek32(fd,0,SEEK_END);//return the last place
		sceIoLseek32(fd,cur,SEEK_SET);//update-back to original place
	}
	return JS_TRUE;
}
int module_start(SceSize args, void *argp){
	js_addClass(NULL,NULL,File,2,NULL,fileMethodes,NULL,NULL,"File",
		JSCLASS_NEW_RESOLVE,NULL,NULL,class_get,class_set,NULL,NULL,NULL,NULL,JSCLASS_NO_OPTIONAL_MEMBERS);
	js_addModule(functions,gfunctions,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
