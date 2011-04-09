#include <pspkernel.h>
#include <pspsdk.h>
#include <psputility.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define PSP_FONT_8BIT 2
#define PSP_FONT_24BIT 3
#define PSP_FONT_32BIT 4

#define FILE 0
#define MEMORY 1

#define FONT(f) (f+1)
#define REGULAR 0
#define SERIF 1//on regular only
#define ITALIC 2
#define BOLD 4

typedef struct{//Font
    float unk0;
    float unk4;
    float unk8;
    float unk12;
    float unk16;
    unsigned short unk20;
    unsigned short unk22;
    unsigned short unk24;
    unsigned short unk26;
    unsigned short unk28;
    unsigned short unk30;
    unsigned char font[64];//unk32
    unsigned char file[64];//unk96
    unsigned int unk160;
    unsigned int unk164;
}Font;
typedef struct{//GlyphInfo
    unsigned width;//unk0
    unsigned height;//unk2
    int unk4;
    int unk8;
    int unk12;
    int unk16;
    int unk20;
    int unk24;
    int unk28;
    int unk32;
}GlyphInfo;
typedef struct{//CharInfo
    unsigned width;
    unsigned height;
    unsigned left;
    unsigned top;
    GlyphInfo glyph;
    char padding[2];
    unsigned short unk14;
} CharInfo;
typedef struct{//Rect
    unsigned short width;
    unsigned short height;
}Rect;
typedef struct{//Image
    unsigned int psm;
    int x;
    int y;
    Rect rect; /* buffer size */ 
    unsigned short tbw;
    unsigned short unk;
    unsigned char * buffer;
}Image; 
typedef struct{//InitParam
    void* userData;
    unsigned maxNumFonts;
    void * cache;
    void* (* malloc)(void*,unsigned); 
    void (* free)(void*,void*); 
    void * (* open)(void*,void*,int *);
    int (* close)(void*,void*); 
    unsigned (* read)(void*,void*,void*,unsigned,unsigned,int *);
    int (* seek)(void*,void*,unsigned);
    int (* errCB)(void*, int);
    int (* finalize)(void*,int);
} InitParam; 
extern void* sceFontNewLib(InitParam *,int * error);
extern unsigned sceFontDoneLib(void* lib);
extern void* sceFontOpen(void* lib,long,unsigned AccessMode,int * error);
extern unsigned sceFontClose(void* id );
extern unsigned sceFontGetCharInfo(void* id, short unsigned, CharInfo * );
extern unsigned sceFontGetCharGlyphImage(void* id, short unsigned, Image * );

#define MYIMAGE_WIDTH (512)
#define MYIMAGE_HEIGHT (20)
#define MYIMAGE_BPP (4)
#define MYIMAGE_SIZE (MYIMAGE_WIDTH*MYIMAGE_HEIGHT)*MYIMAGE_BPP

PSP_MODULE_INFO("libFont", 0, 1, 1);
PSP_HEAP_SIZE_KB(1024);

static void* myMalloc(void* pMyData,unsigned int size){
	void*p = malloc(size);
//	printf("malloc:%i %p\n",size,p);
	return p;
}
static void myFree(void* pMyData,void* p){
//	printf("free  : %p\n",p);
	free(p);
}
void RGBA2ARGB(void* p,u32 pixel){
	while(pixel--)
		((u32*)p)[pixel] = (((u32*)p)[pixel]>>8) | (((u32*)p)[pixel]<<24);
}
void RGBA2GREY(void* p,u32 pixel){
	while(pixel--){
		register u32 c = (((u32*)p)[pixel])&0xFF;
		((u32*)p)[pixel] = c<<24 | c<<16 | c<<8 | c<<0;
	}
}
int printchar(void* fontID,char*str){
	int i=0,x=0;
	while(str[i]){
		if(str[i]==' '){ x+=4*3; i++; continue; }
		unsigned short charCode = str[i];
		CharInfo charInfo;
		if(sceFontGetCharInfo(fontID, charCode, &charInfo)) return  -__LINE__;
		Image myImage={PSP_FONT_32BIT};
			myImage.psm = PSP_FONT_32BIT;
			myImage.rect.width = MYIMAGE_WIDTH;
			myImage.rect.height = MYIMAGE_HEIGHT;
			myImage.tbw = MYIMAGE_WIDTH * MYIMAGE_BPP;
			myImage.buffer = (void*)0x44000000+x*4+(MYIMAGE_HEIGHT-charInfo.top)*4*512;//malloc(MYIMAGE_SIZE);
			myImage.x = 0;
			myImage.y = 0;
//		RGBA2ARGB((void*)0x44000000,MYIMAGE_SIZE);
		//sceFontSetResolution(fontID,1,1);
		if(sceFontGetCharGlyphImage(fontID, charCode, &myImage)) return  -__LINE__;
		x+=charInfo.width+1;
		i++;
	}
	RGBA2GREY((void*)0x44000000,MYIMAGE_SIZE);
	return 0;
}
int load(SceSize args, void *argp){
	int stat,modid;
	if(sceKernelStartModule(modid=sceKernelLoadModule("flash0:/vsh/module/libfont_hv.prx",0,NULL),0,NULL,&stat,NULL)<0)return -__LINE__;
	int errorCode;
	InitParam initParams = {NULL,4,NULL,myMalloc,myFree,NULL,NULL,NULL,NULL,NULL,NULL};
	void* libID = sceFontNewLib(&initParams, &errorCode);if(errorCode)return  -__LINE__;
	void* fontID = sceFontOpen(libID, FONT(BOLD), FILE, &errorCode);if(errorCode)return -__LINE__;
	memset((void*)0x44000000,0,4*512*16);

	//print build date
	printchar(fontID, __DATE__" "__TIME__);//on vram
	sceIoWrite(2,__DATE__" "__TIME__,11+1+8);//on cout

	if(sceFontClose(fontID)) return  -__LINE__;
	if(sceFontDoneLib(libID)) return  -__LINE__;

	sceKernelStopModule(modid,0,NULL,&stat,NULL);
	sceKernelUnloadModule(modid);
	sceKernelSelfStopUnloadModule(1,0,NULL);
	return 0;
}
int module_start(int args, void* argp){
	return sceKernelStartThread(sceKernelCreateThread("load", load, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL), args, argp);
}

