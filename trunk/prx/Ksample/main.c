#include <pspkernel.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("Ksample",PSP_MODULE_KERNEL,1,1);
PSP_NO_CREATE_MAIN_THREAD();

int Ksample_addModule(){
	return 200;
}
int module_start(SceSize args, void *argp){
	printf("addresse : %p\n",Ksample_addModule);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
