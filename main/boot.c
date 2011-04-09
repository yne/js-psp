#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <pspkernel.h>

typedef struct PBP_HEADER{
	char magic[4];
	char version[4];
	int param;
	int icon0;
	int icon1;
	int pic0;
	int pic1;
	int snd0;
	int data;//bin
	int psar;//psar
}PbpHeader;
typedef struct SFO_HEADER{
  u32 magic;
  u32 version;
  int keys;
  int table;
  int nbr;
} SFOHEADER;
typedef struct SFO_ITEM{
  short name;
  char  pad;
  char  type;
  int   length;
  int   size;
  int   offset;
} SFOITEM;

PbpHeader eboot;
char* toExecute=NULL;
int bootRemoveJs=0;
int kMode=0;
char bootTmpJsName[] = "_main.js";
int RunTimeSize=14*1024;
int ContextSize=8192;
int sfoPtr;

int getPbpInfo(SceUID in){
	if(sceIoRead(in,&eboot,sizeof(eboot))!=sizeof(eboot)){
		sceIoClose(in);
		return -1;
	}
	int size = sceIoLseek(in,0,SEEK_END);
	sfoPtr=eboot.param;
/*//print PBP info
	printf("param %i (%i)\n",eboot.param,eboot.icon0-eboot.param);
	printf("icon0 %i (%i)\n",eboot.icon0,eboot.icon1-eboot.icon0);
	printf("icon1 %i (%i)\n",eboot.icon1,eboot.pic0 -eboot.icon1);
	printf("pic0  %i (%i)\n",eboot.pic0, eboot.pic1 -eboot.pic0 );
	printf("pic1  %i (%i)\n",eboot.pic1, eboot.snd0 -eboot.pic1 );
	printf("snd0  %i (%i)\n",eboot.snd0, eboot.data -eboot.snd0 );
	printf("data  %i (%i)\n",eboot.data, eboot.psar -eboot.data );
	printf("psar  %i (%i)\n",eboot.psar, size       -eboot.psar );
//*/
	if(eboot.pic0-eboot.icon1){//we got the kernel prx in the icon1.pmf zone
		char tmp_name[] = "Kloader.prx";
		void*ptr=malloc(eboot.pic0-eboot.icon1);
		sceIoLseek(in,eboot.icon1,SEEK_SET);
		sceIoRead(in,ptr,eboot.pic0-eboot.icon1);
		SceUID out = sceIoOpen(tmp_name,PSP_O_RDWR|PSP_O_CREAT,0777);
		sceIoWrite(out,ptr,eboot.pic0-eboot.icon1);
		sceIoClose(out);
		int ret;
		if(sceKernelStartModule(sceKernelLoadModule(tmp_name, 0, NULL), 0, NULL, &ret, NULL)>0){
			kMode = 1;
			#ifdef DEBUG_MODE
			printf("Kernel is available\n");
			#endif
		}
		sceIoRemove(tmp_name);
		free(ptr);
	}
	if(size-eboot.psar && !toExecute){//we got the js in the psar zone and no argv
		void*ptr=malloc(size-eboot.psar);
		sceIoLseek(in,eboot.psar,SEEK_SET);
		sceIoRead(in,ptr,size-eboot.psar);
		SceUID out = sceIoOpen(bootTmpJsName,PSP_O_RDWR|PSP_O_CREAT,0777);
		sceIoWrite(out,ptr,size-eboot.psar);
		sceIoClose(out);
		free(ptr);
		toExecute=bootTmpJsName;
		bootRemoveJs=1;
		#ifdef DEBUG_MODE
		printf("boot:%s(psar)\n",toExecute);
		#endif
	}
	return 0;
}
int getSfoInfo(SceUID in,char* search,int* iout,char* sout){
	int i,length;
	char *key;
	void *value;
	SFOHEADER	header;
	sceIoLseek(in,sfoPtr,SEEK_SET);
	sceIoRead(in,&header,sizeof(header));  
	if(header.magic!=0x46535000)return -1;//bad header
	SFOITEM* sfo_item = malloc(header.nbr*16);
	sceIoRead(in,sfo_item,header.nbr*16);
	for(i=0;i<header.nbr;i++){
		if (i == header.nbr-1)
			length = header.table-(sfo_item[i].name+header.keys);
		else
			length = sfo_item[i+1].name-sfo_item[i].name;
		key=malloc(length);
		sceIoLseek(in,sfoPtr+header.keys+sfo_item[i].name,SEEK_SET);
		sceIoRead(in,key,length);
		//printf("%02d %s\n",i,key);
		if(!strcmp(key,search)){
			value=malloc(sfo_item[i].size);
			sceIoLseek(in,sfoPtr+header.table+sfo_item[i].offset,SEEK_SET);
			sceIoRead(in,value,sfo_item[i].size);
			if(sfo_item[i].type==2){//string
				strcpy(sout,value);
			}
			if(sfo_item[i].type==4){//int
				*iout=*(int*)value;
			}
			free(value);
		}
		free(key);
	}
	free(sfo_item);
	return 0;
}
void boot(){
	SceUID PBP = sceIoOpen("EBOOT.PBP",PSP_O_RDONLY|PSP_O_NBLOCK,0777);
	getPbpInfo(PBP);
	if(!toExecute){//nothing from psar
		getSfoInfo(PBP,"JS_FILE",NULL,toExecute);
		#ifdef DEBUG_MODE
		printf("boot:%s (SFO)\n",toExecute);
		#endif
	}
	if(!toExecute){//nothing from SFO
		toExecute="js/main.js";
		#ifdef DEBUG_MODE
		printf("boot:%s (default)\n",toExecute);
		#endif
	}
	getSfoInfo(PBP,"JS_RT_SIZE",&RunTimeSize,NULL);
	getSfoInfo(PBP,"JS_CX_SIZE",&ContextSize,NULL);
	sceIoClose(PBP);
}