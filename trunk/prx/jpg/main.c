#include <stdio.h>
#include <pspkernel.h>
#include <jpeglib.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("libJpeg",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

u32 _impure_ptr;
int sscanf ( const char * str, const char * format, ...){
	return 0;
}
JS_FUN(Open){
	struct jpeg_decompress_struct dinfo;
	struct jpeg_error_mgr jerr;
	dinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&dinfo);
	FILE* inFile=NULL;
	if(JSVAL_IS_OBJECT(argv[0])){//filoe object
		jpeg_memory_src(&dinfo,(const JOCTET *)J2S(js_getProperty(J2O(argv[0]),"data")),J2SL(js_getProperty(J2O(argv[0]),"data")));
	}else{//String
		if(J2SL(argv[0])<256){//path
			inFile = fopen(J2S(argv[0]), "rb");
			if (!inFile){
				jpeg_destroy_decompress(&dinfo);
				return JS_TRUE;
			}
			jpeg_stdio_src(&dinfo, inFile);
		}else{//raw
			jpeg_memory_src (&dinfo, (const JOCTET *) J2S(argv[0]), J2SL(argv[0]));
		}
	}
	jpeg_read_header(&dinfo, TRUE);
	int width = dinfo.image_width,height = dinfo.image_height,texW = 1,texH = 1;
	jpeg_start_decompress(&dinfo);

	js_setProperty(obj,"imgW",I2J(width));
	js_setProperty(obj,"imgH",I2J(height));
	while(texW<width)texW<<= 1;
	while(texH<height)texH<<= 1;
	js_setProperty(obj,"texW",I2J(texW));
	js_setProperty(obj,"texH",I2J(texH));

	u32* data = (u32*) js_malloc(texW*texH*4);
	js_setProperty(obj,"data",STRING_TO_JSVAL(js_newString((void*)data,texW*texH*4)));
	
	u8* line = (u8*) js_malloc(width * 3);
	if (dinfo.jpeg_color_space == JCS_GRAYSCALE) {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			int x;
			for (x = 0; x < width; x++) {
				u32 c = line[x];
				data[x + texW * y] = c | (c << 8) | (c << 16) | 0xff000000;;
			}
		}
	} else {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			u8* linePointer = line;
			int x;
			for (x = 0; x < width; x++) {
				u32 c = *(linePointer++);
				c |= (*(linePointer++)) << 8;
				c |= (*(linePointer++)) << 16;
				data[x + texW * y] = c | 0xff000000;
			}
		}
	}
	jpeg_finish_decompress(&dinfo);
	jpeg_destroy_decompress(&dinfo);
	js_free(line);
	if(JSVAL_IS_STRING(argv[0])&&J2SL(argv[0])<256)
		fclose(inFile);
	*rval = O2J(obj);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
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