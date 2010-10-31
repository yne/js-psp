#include <pspkernel.h>
#include <pspkdebug.h>
#include <stdio.h>
#include <string.h>
#include <systemctrl.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("JSEK",0x1007,0,0);
PSP_MAIN_THREAD_ATTR(0);

u32 loadModBuf(void*buffer,u32 size){
	return 50;//sceKernelLoadModuleBuffer(size,(void*)buffer,0,NULL);
	//u32 modid = sceKernelLoadModuleBuffer(sizeof(buffer),(void*)buffer,0,NULL);
	//return sceKernelStartModule(modid, 0, NULL, NULL, NULL);
}
int my_addModule(){//will be hoocked to the loaded *Kmodule*_addModule
	return 0;
}
u32 KCall(u32 uid,u32 nid,u32 arg){
	SceModule2* mod = sceKernelFindModuleByUID(uid);
	u32 (*function)(int);
	function = (void*)sctrlHENFindFunction(mod->modname,mod->modname,nid);
	if(function)
		return function(arg);
	return 0;
}
u32 js_searchInfo(KfindProc chaine){
	u32 newFun = sctrlHENFindFunction(chaine.mod, chaine.lib, chaine.nid);
	sctrlHENPatchSyscall((u32)my_addModule,(void*)newFun);
	return newFun;
}
int module_start(SceSize args, char* argp[]){
	return 0;
}