#include <pspkernel.h>
#include <pspkdebug.h>
#include <stdio.h>
#include <string.h>
#include <systemctrl.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("JSEK",0x1007,0,0);

static JSPropertiesSpec var[] = {
	{"Ksample", I2J(1)},
	{0}
};
KmodInfo js_addKModule(void){
	KmodInfo info;
	info.lfun = NULL;
	info.gfun = NULL;
	info.lvar = NULL;
	info.gvar = var;
	return info;
}
int tmpFunction(){//will be hoocked to the loaded *Kmodule*_addModule
	return 0;
}
int js_searchInfo(KfindProc chaine){
	u32 newFun = sctrlHENFindFunction(chaine.mod, chaine.lib, chaine.nid);
	sctrlHENPatchSyscall((u32)tmpFunction,(void*)newFun);
	return newFun;
}
int module_start(SceSize args, char* argp[]){
	return 0;
}