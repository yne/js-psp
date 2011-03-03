#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("cmd",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();
int harakiri(SceSize args, void *argp){
	sceKernelDelayThread(1000*500);
	sceKernelSelfStopUnloadModule(1,0,NULL);
	return 0;
}
int module_start(SceSize args, u8 *argp){
	char*eval=NULL;
	int i=0;
	while(i<args){
		if(!argp[i]&&!eval)eval=(char*)argp+(++i);
		if(!argp[i]&&argp[i+1]!=0xFF)argp[i]=' ';
		i++;
	}
	if(js_test(J2I(js_evaluateScript(eval)))==0x8002013A)
		printf("JSE not loaded\n");
	sceKernelStartThread(sceKernelCreateThread("harakiri",harakiri,0x11,0xFA0,0,0),0,NULL);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
