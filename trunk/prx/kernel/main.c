#include <pspsdk.h>
#include <pspkernel.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("modK",PSP_MODULE_KERNEL,0,0);

int Kfun(void){
	printf("[modK::Kfun] started !\n\n");
	return 0;
}
int module_start(SceSize args, char* argp[]){
	printf("[modK] started !\n\n");
	return 0;//lib not started if != 0
}
int module_stop(SceSize args, void *argp){
	printf("[modK] stoped !\n\n");
	return 0;
}
