#include <pspkernel.h>
#include <pspjpeg.h>
#define PIXEL_SIZE (4)
 
#include "../../main/shared.h"

PSP_MODULE_INFO("sceJpeg",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

u32 avMod = 0;//host avCodec UID
JS_FUN(Open){
	int width = 480, height = 272,texW=1,texH=1,size=0,i=0;
	void*p=NULL;SceUID fd=0;//if fopen+malloc needed
	if(!avMod)
		avMod = c_addModule("flash0:/kd/avcodec.prx");
	sceJpegInitMJpeg();
	jsval tmp;
	if(JSVAL_IS_OBJECT(argv[0]))
		tmp = js_getProperty(J2O(argv[0]),"data");
	else//if(JSVAL_IS_STRING(argv[0]))
		tmp = argv[0];
	if(J2SL(tmp)<256){//path
		fd=sceIoOpen(J2S(tmp),PSP_O_RDONLY,0777);
		size = sceIoLseek32(fd,0,SEEK_END);
		sceIoLseek32(fd,0,SEEK_SET);
		p = c_malloc(size);
		sceIoRead(fd,p,size);
	}
	u8* data=p?p:(void*)J2S(tmp);
	if(!size)size=js_getStringLength(JSVAL_TO_STRING(tmp));
	if(!(data[i++] == 0xFF && data[i++] == 0xD8 && data[i++] == 0xFF && data[i++] == 0xE0))goto err;//invalid SOI header
	int block_length = data[i] * 256 + data[i+1];
	if(!(data[i+2] == 'J' && data[i+3] == 'F' && data[i+4] == 'I' && data[i+5] == 'F' && data[i+6] == 0x00))goto err;//invalid JFIF
	while(1){//seek to 
		i+=block_length;//goto next block
		if(i>=size)goto err;//Check to protect against segmentation faults
		if(data[i] != 0xFF)goto err;//Check that we are truly at the start of another block
		if(data[i+1] == 0xC0){//0xFFC0 is the "Start of frame" marker which contains the file size
		//The structure of the 0xFFC0 block is quite simple [0xFFC0][ushort length][uchar precision][ushort x][ushort y]
			height = data[i+5]*256 + data[i+6];
			width = data[i+7]*256 + data[i+8];
			while(texW<width)texW<<= 1;
			while(texH<height)texH<<= 1;
			break;
		}else{
			i+=2;//Skip the block marker
			block_length = data[i]*256+data[i+1];//Go to the next block
		}
	}
	sceJpegCreateMJpeg(width, height);
	js_test(texH*texW*4);
	u32* imgBuf = (u32*)js_malloc(texH*texW*4);
	u32 res = sceJpegDecodeMJpeg(data,size,imgBuf,0);
	u32* vram = 0x44000000;
//remove transparency
	int x, y;
	for (x = height-1; x >= 0 ; x--)
		for (y = width-1; y >= 0; y--)
			//imgBuf[x*texW+y] = 0xFF000000|imgBuf[x*width+y];	
			vram[x*texW+y] = 0xFF000000|imgBuf[x*width+y];
	if((res>>16)!=width || (res&0xFFF)!=height)
		js_free(imgBuf);
	sceJpegDeleteMJpeg();

	js_setProperty(obj,"imgH",I2J(height));
	js_setProperty(obj,"imgW",I2J(width));
	js_setProperty(obj,"texH",I2J(texH));
	js_setProperty(obj,"texW",I2J(texW));
	js_setProperty(obj,"data",STRING_TO_JSVAL(js_newString((void*)imgBuf,texW*texH*4)));
	*rval = O2J(obj);
err:
	sceJpegFinishMJpeg();
	c_delModule(avMod);
	if(fd>0)
		sceIoClose(fd);
	if(p)
		c_free(p);
	return JS_TRUE;
}

JS_FUN(_Unload){
	if(avMod>0)
		c_delModule(avMod);
	return JS_TRUE;
}

static JSFunctionSpec gfunctions[] = {
	{"_unload",_Unload,1},
	{"sceJpegOpen",Open,1},
	{0}
};
static JSFunctionSpec functions[] = {
	{"_unload",_Unload,1},
	{"open",Open,1},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,0);
	return 0;
}
int module_stop(){
	return 0;
}