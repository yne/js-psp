#include <pspkernel.h>
#include <pspsdk.h>
#include <stdio.h>

PSP_MODULE_INFO("modU",PSP_MODULE_USER,0,0);

extern int js_test(int);
int Ufun(void){
	printf("[Ufun] called\n");
	return 0;
}
int module_start(SceSize args, char* argp[]){
	printf("[modU] started !\n");
	printf("[modU] call js_test : %08X\n",js_test(5));
	return 0;//lib not started if != 0
}
int module_stop(SceSize args, void *argp){
	printf("[modU] stoped !\n");
	return 0;
}
