#include <pspkernel.h>
#include <pspkdebug.h>
#include <stdio.h>
#include <string.h>
#include <systemctrl.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("JSEK",0x1007,0,0);

KmodInfo js_addKModule(void){
	KmodInfo info;
	info.lfun = NULL;
	info.gfun = NULL;
	info.lvar = NULL;
	info.gvar = NULL;
	return info;
}

int js_searchInfo(KfindProc chaine){
	return sctrlHENFindFunction(chaine.mod, chaine.lib, chaine.nid);
//	printf("%s\n\n",chaine.value);
}

int module_start(SceSize args, char* argp[]){
	printf("Kloader ready\n\n");
	//printf("[modK] call js_test : %08X\n",js_test(5));//forbidden by the os
	return 0;//lib not started if != 0
}