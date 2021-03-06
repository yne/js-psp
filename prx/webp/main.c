#include <pspkernel.h>
#include <pspjpeg.h>
#define PIXEL_SIZE (4)
 
#include "../../main/shared.h"
#include "decode.h"
#include <stdlib.h>
#include "vp8i.h"
#include "yuv.h"

PSP_MODULE_INFO("webp",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

static inline uint32_t get_le32(const uint8_t* const data) {
  return data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
}
static uint32_t CheckRIFFHeader(const uint8_t** data_ptr,uint32_t *data_size_ptr) {
  uint32_t chunk_size = 0xffffffffu;
  if (*data_size_ptr >= 10 + 20 && !memcmp(*data_ptr, "RIFF", 4)) {
    if (memcmp(*data_ptr + 8, "WEBP", 4))return 0;  // wrong image file signature
    const uint32_t riff_size = get_le32(*data_ptr + 4);
    if (riff_size < 12)return 0;   // we should have at least one chunk
    if (memcmp(*data_ptr + 12, "VP8 ", 4))return 0;   // invalid compression format
    chunk_size = get_le32(*data_ptr + 16);
    if (chunk_size > riff_size - 12)return 0;  // inconsistent size information.
    *data_ptr += 20;// We have a RIFF container. Skip it.
    *data_size_ptr -= 20;
    return chunk_size;// Note: we don't report error for odd-sized chunks.
  }
  return *data_size_ptr;
}
typedef struct {
  uint8_t* output;      // rgb(a) or luma
  uint8_t *u, *v;
  uint8_t *top_y, *top_u, *top_v;
  int stride;           // rgb(a) stride or luma stride
  int u_stride;
  int v_stride;
  int mode;
} Params;
static int CustomPut(const VP8Io* io) {
  Params *p = (Params*)io->opaque;
  const int w = io->width;
  const int mb_h = io->mb_h;
  assert(!(io->mb_y & 1));

  if (w <= 0 || mb_h <= 0)return 0;
  uint8_t* dst = p->output + io->mb_y * p->stride;
  // Point-sampling U/V upscaler.
  int j;
  for (j = 0; j < mb_h; ++j) {
    const uint8_t* y_src = io->y + j * io->y_stride;
    int i;
    for (i = 0; i < w; ++i) {
      const int y = y_src[i];
      const int u = io->u[(j / 2) * io->uv_stride + (i / 2)];
      const int v = io->v[(j / 2) * io->uv_stride + (i / 2)];
      VP8YuvToRgba(y, u, v, dst + i * 4);
    }
    dst += p->stride;
  }
  return 1;
}
static int CustomPutAlpha(const VP8Io* io) {
  Params *p = (Params*)io->opaque;
  const int w = io->width;
  const int mb_h = io->mb_h;
  assert(!(io->mb_y & 1));

  if (w <= 0 || mb_h <= 0)return 0;
  uint8_t* dst = p->output + io->mb_y * p->stride;
  // Point-sampling U/V upscaler.
  int j;
  for (j = 0; j < mb_h; ++j) {
    const uint8_t* y_src = io->y + j * io->y_stride;
    int i;
    for (i = 0; i < w; ++i) {
      const int y = y_src[i];
      const int u = io->u[(j / 2) * io->uv_stride + (i / 2)];
      const int v = io->v[(j / 2) * io->uv_stride + (i / 2)];
      VP8YuvToAlpha(y, u, v, dst + i * 4);
    }
    dst += p->stride;
  }
  return 1;
}
static uint8_t* DecodeInto(const uint8_t* data, uint32_t length,uint8_t* buf,int bufWidth,int isAlpha) {
	int ok = 0;
	Params params;
  params.mode = 3;//MODE_RGBA;
	params.output = buf;
  params.stride = bufWidth;

  VP8Decoder* dec = VP8New();
  if (!dec)return NULL;
  VP8Io io;
  VP8InitIo(&io);
  io.data = data;
  io.data_size = length;
  io.opaque = &params;
	if(isAlpha)io.put = CustomPutAlpha;
	else io.put = CustomPut;
//  io.setup = CustomSetup;
//  io.teardown = CustomTeardown;
  if (VP8GetHeaders(dec, &io)) {
		VP8YUVInit();
		ok = VP8Decode(dec, &io);	
  }//else puts("bad header");
  VP8Delete(dec);
  return ok ? params.output : NULL;
}
int WebPGetInfo(const uint8_t* data, uint32_t data_size,int *width,int *height) {
  const uint32_t chunk_size = CheckRIFFHeader(&data, &data_size);
  if (!chunk_size)return 0;// unsupported RIFF header
  if (data_size < 10)return 0;// not enough data
  if (data[3] != 0x9d || data[4] != 0x01 || data[5] != 0x2a)return 0;// Wrong signature.
  const uint32_t bits = data[0] | (data[1] << 8) | (data[2] << 16);
  if ((bits & 1)// Not a keyframe.
  || (((bits >> 1) & 7) > 3)// unknown profile
  || (!((bits >> 4) & 1))// first frame is invisible!
  || (((bits >> 5)) >= chunk_size))// inconsistent size information.
		return 0;
  if(width)*width = ((data[7] << 8) | data[6]) & 0x3fff;
  if(height)*height = ((data[9] << 8) | data[8]) & 0x3fff;
  return 1;
}
void addAlpha(char* path,void* buf,int width){//path to the alpha channel image, buffer filled with 24bit color
	void*p;SceUID fd;
	if((fd=sceIoOpen(path,PSP_O_RDONLY,0777))<0)return;
	int size = sceIoLseek32(fd,0,SEEK_END);
	sceIoLseek32(fd,0,SEEK_SET);
	if(!(p=c_malloc(size)))return;
	sceIoRead(fd,p,size);
	fd=sceIoClose(fd);
	DecodeInto(p,size,(uint8_t*)buf,width,1);
	c_free(p);
}
JS_FUN(Open){//path
//	if(!(cx->fp->flags & JSFRAME_CONSTRUCTING))return JS_TRUE;// called as class
	int width=0,height=0,texW=1,size=0;
	void*p=NULL,*q=NULL;
	u8 header[32];
	SceUID fd;
//get header info
	if((fd=sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777))<0)goto end;
	size = sceIoLseek32(fd,0,SEEK_END);
	if(size<sizeof(header))goto end;
	sceIoLseek32(fd,0,SEEK_SET);
	sceIoRead(fd,header,sizeof(header));
	fd=sceIoClose(fd);
	if(!WebPGetInfo((void*)header,sizeof(header),&width,&height))goto end;
	while(texW<height)texW<<= 1;
//js_malloc can interupt us so we must be prepared (no pending fd ...)
	uint8_t* imgBuf = (uint8_t*)js_malloc(height*texW*4);
//cp file ram
	if((fd=sceIoOpen(J2S(argv[0]),PSP_O_RDONLY,0777))<0)goto end;
	size = sceIoLseek32(fd,0,SEEK_END);
	sceIoLseek32(fd,0,SEEK_SET);
	if(!(p=c_malloc(size)))goto end;
	sceIoRead(fd,p,size);
	fd=sceIoClose(fd);
//decode ram>ram
	DecodeInto(p,size,imgBuf,texW*4,0);
//add alpha
	if(argc>=2){
		if((fd=sceIoOpen(J2S(argv[1]),PSP_O_RDONLY,0777))<0)goto end;
		size = sceIoLseek32(fd,0,SEEK_END);
		sceIoLseek32(fd,0,SEEK_SET);
		if(!(q=c_malloc(size)))goto end;
		sceIoRead(fd,q,size);
		fd=sceIoClose(fd);
		DecodeInto(q,size,imgBuf,texW*4,1);
	}
	c_free(p);p=NULL;
	c_free(q);q=NULL;
//finalize
	js_setProperty(obj,"imgH",I2J(height));
	js_setProperty(obj,"imgW",I2J(width));
	js_setProperty(obj,"texH",I2J(height));
	js_setProperty(obj,"texW",I2J(texW));
	js_setProperty(obj,"data",V2J(imgBuf,height*texW*4));
end:
	if(fd)sceIoClose(fd);
	if(p)c_free(p);
	return JS_TRUE;
}
JS_FUN(_Unload){
	return JS_TRUE;
}
static JSFunctionSpec gfunctions[] = {
//	{"Webp",Open,1},
	{0}
};
static JSFunctionSpec functions[] = {
	{"_unload",_Unload,1},
//	{"open",Open,1},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addClass(NULL,NULL,Open,0,NULL,/*date_methods*/0,NULL,NULL,"Webp",
		JSCLASS_NEW_RESOLVE,0,0,0,0,0,0,0,0,JSCLASS_NO_OPTIONAL_MEMBERS,NULL);
	js_addModule(functions,gfunctions,0,0);
	return 0;
}
int module_stop(){
	return 0;
}