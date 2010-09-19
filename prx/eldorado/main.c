#include <pspkernel.h>

//http://pastebin.com/Q81WZVXL
 
#include "../../main/shared.h"

PSP_MODULE_INFO("eldorado",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

struct Vertex{
	unsigned short w,h,c,x,y,z;
};

JS_FUN(mapToArray){
	int x=J2I(argv[0]),y=J2I(argv[1]);
	unsigned short* map=NULL;
	if(JSVAL_IS_OBJECT(argv[2]))
		map=(void*)J2U(js_getProperty(J2O(argv[2]),"data"));
	else if(JSVAL_IS_STRING(argv[2]))
		map=(void*)J2S(argv[2]);
	u32 jv = js_evaluateScript("sceGuGetMemory(2*558*12)");
	struct Vertex* v = (void*)J2U(jv)-0x80000000;
	int i=(x/16)+256*(y/16);
	int dx=x%16;
	int dy=y%16;
	int n=0,m=0,ligne=0;
	while(ligne<18){
		int colonne = 0;
		while(colonne<31){
			v[n+0].w=16*((map[m+i]>>0)&0x0F);
			v[n+0].h=16*((map[m+i]>>4)&0x0F)+256*((map[m+i]>>8)&0x0F);
			v[n+1].w=16+v[n+0].w;
			v[n+1].h=16+v[n+0].h;
			v[n+0].x=colonne*16-dx;
			v[n+0].y= ligne *16-dy;
			v[n+1].x=16+v[n+0].x;
			v[n+1].y=16+v[n+0].y;
			n+=2;m+=1;
			colonne++;
		}
		m+=256-31;
		ligne++;
	}
	char eval[48];
	sprintf(eval,"sceGuDrawArray(6,0x80011A,2*558,0,0x%08X)",(J2I(v))*2);
	js_evaluateScript(eval);
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"mapToArray",mapToArray,2},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,0);
	return 0;
}
int module_stop(){
	return 0;
}