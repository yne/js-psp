#include <pspkernel.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#define INTR_MASK(P) ((P&PSP_CTRL_START)&&(P&PSP_CTRL_SELECT))

PSP_MODULE_INFO("JSlibLoader",0,0,0);

char* memcat(char* dst,char* src){
	int n = strlen(src)+1;
	memcpy(dst,src,n);
	return dst+n;
}
int boot(SceSize args,void* argp){
	char arg[128];char* _arg;
	int i;
	for(i=strlen((char*)argp);i&&((char*)argp)[i]!='/';i--);
	((char*)argp)[i+1]=0;
	_arg=memcat(memcat(memcat(arg,strcat((char*)argp,"libjs")),"main.js"),"8000");
	SceCtrlData pad;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
	SceUID mod = 0;
	do{
		if(!mod){
			mod=sceKernelLoadModule(arg, 0, NULL);
			sceKernelStartModule(mod, _arg-arg, arg, &i, NULL);
			sceKernelSelfStopUnloadModule(1, 0, NULL);//prx loading problem occur if BL still in RAM o_O
			sceKernelDelayThread(1000*1000);//give 1s to finish the start process
		}
		sceCtrlPeekBufferPositive(&pad,1);
		if(INTR_MASK(pad.Buttons)){//select+start pressed
			if(pad.Buttons&PSP_CTRL_LTRIGGER){//Leave (hard)
				sceKernelExitGame();
			}
			if(pad.Buttons&PSP_CTRL_RTRIGGER){//Reset
				int ret;
				sceKernelStopModule(mod,0,NULL,&ret,NULL);
				sceKernelUnloadModule(mod);
				mod=0;
			}
		}
	}while(1);
	sceKernelSelfStopUnloadModule(1, 0, NULL);
	puts("error unloading");
	return 0;
}
int module_start(SceSize args,void* argp){
	return sceKernelStartThread(sceKernelCreateThread("boot", boot, 0x18, 0x400, 0, NULL), args, argp);
}
int module_stop(SceSize args,void* argp){
	return 8;
}