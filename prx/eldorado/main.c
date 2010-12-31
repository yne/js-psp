#include <pspkernel.h>
#include <pspgu.h>
#include <pspctrl.h>
#include <psprtc.h>

//http://pastebin.com/Q81WZVXL
 
#include "../../main/shared.h"

PSP_MODULE_INFO("eldorado",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

typedef struct{
	short w,h;
	short c;
	short x,y,z;
}Vertex;
void* pal=NULL;
void* titles=NULL;
void* player=NULL;
#ifdef MAP16
unsigned short* map=NULL;
#else
unsigned char* map=NULL;
#endif
int x=2048,y=2048,dir=0;
int isPossible(int x,int y){
	if(map && (
		map[(x+240)/16 + ((y+135)/16)*256]<78||
		map[(x+240)/16 + ((y+150)/16)*256]<78||
		map[(x+255)/16 + ((y+150)/16)*256]<78||
		map[(x+255)/16 + ((y+135)/16)*256]<78
	))
		return 0;
	return 1;
}
JS_FUN(setMove){
	int btn=J2I(argv[0]);
	int oldX=x,oldY=y;
	if(btn&PSP_CTRL_UP){
		y--;
		if(y<0)y=0;
		dir=2;
	}
	else if(btn&PSP_CTRL_DOWN){
		y++;
		if(y>4096-272)y=4096-272;
		dir=0;
	}
	if(btn&PSP_CTRL_LEFT){
		x--;
		if(x<0)x=0;
		dir=1;
	}
	else if(btn&PSP_CTRL_RIGHT){
		x++;
		if(x>4096-480)x=4096-480;
		dir=3;
	}
	if(!isPossible(x,oldY))
		x=oldX;
	if(!isPossible(oldX,y))
		y=oldY;
	*rval=I2J(dir);
	return JS_TRUE;
}
JS_FUN(setPal){
	if(JSVAL_IS_OBJECT(argv[0]))
		pal=(void*)J2U(js_getProperty(J2O(argv[0]),"data"));
	else if(JSVAL_IS_STRING(argv[0]))
		pal=(void*)J2S(argv[0]);
	return JS_TRUE;
}
JS_FUN(setPlayer){
	if(JSVAL_IS_OBJECT(argv[0]))
		player=(void*)J2U(js_getProperty(J2O(argv[0]),"data"));
	else if(JSVAL_IS_STRING(argv[0]))
		player=(void*)J2S(argv[0]);
	return JS_TRUE;
}
JS_FUN(setTitle){
	if(JSVAL_IS_OBJECT(argv[0]))
		titles=(void*)J2U(js_getProperty(J2O(argv[0]),"data"));
	else if(JSVAL_IS_STRING(argv[0]))
		titles=(void*)J2S(argv[0]);
	return JS_TRUE;
}
JS_FUN(drawPlayer){//dir step
	//set image+palette
	sceGuEnable(GU_ALPHA_TEST);
	sceGuEnable(GU_BLEND);
	sceGuTexMode(GU_PSM_4444,0,0,1);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
	sceGuTexImage(0,16*4,32*4,16*4,player);
	Vertex* v = sceGuGetMemory(2*sizeof(Vertex));
	v[0].w=J2I(argv[0])*16; v[1].w=v[0].w+16;
	v[0].h=(J2I(argv[1])>>2)*32; v[1].h=v[0].h+32;
	//printf("%i %i\n",v[0].w,v[0].h);
	v[0].x=240; v[1].x=v[0].x+16;
	v[0].y=130; v[1].y=v[0].y+32;
	v[0].c=0xFFFF; v[1].c=0xFFFF;
	sceGuDrawArray(GU_SPRITES,GU_COLOR_4444|GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,v);
	sceGuDisable(GU_BLEND);
	sceGuDisable(GU_ALPHA_TEST);
	return JS_TRUE;
}
u64 last_tick=0;
int getFPS(){
	u64 curr_tick;
	sceRtcGetCurrentTick(&curr_tick);
	int ret=1000000/(curr_tick-last_tick);
	sceRtcGetCurrentTick(&last_tick);
	return ret;
}
JS_FUN(mapToArray){
	//set image+palette
	sceGuClutMode(GU_PSM_4444,0,255,0);
	sceGuClutLoad(256/8,pal);
	sceGuTexMode(GU_PSM_T8,0,0,1);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGB);
	sceGuTexImage(0,256,512,256,titles);
//	int x=J2I(argv[0]),y=J2I(argv[1]);
	if(JSVAL_IS_OBJECT(argv[0]))
		map=(void*)J2U(js_getProperty(J2O(argv[0]),"data"));
	else if(JSVAL_IS_STRING(argv[0]))
		map=(void*)J2S(argv[0]);
	else return JS_TRUE;
	Vertex* v = sceGuGetMemory(2*558*sizeof(Vertex));
	int i=(x/16)+256*(y/16);
	int dx=x%16,dy=y%16,n=0,m=0,ligne=0;
	while(ligne<18){
		int colonne = 0;
		while(colonne<31){
#ifdef MAP16
			v[n+0].w=((map[m+i]>>0)&0x0F)<<4;
			v[n+0].h=(((map[m+i]>>4)&0x0F)<<4)+(((map[m+i]>>8)&0x0F)<<8);
#else
			v[n+0].w=((map[m+i])&0x0F)<<4;
			v[n+0].h=((map[m+i])&0xF0);
#endif
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
	sceGuDrawArray(GU_SPRITES,GU_COLOR_4444|GU_TRANSFORM_2D|GU_TEXTURE_16BIT|GU_VERTEX_16BIT,2*558,0,v);
	//printf("%i\n",getFPS());
	return JS_TRUE;
}
static JSFunctionSpec functions[] = {
	{"drawPlayer",drawPlayer,2},
	{"drawLayer",mapToArray,2},
	{"setPal",setPal,2},
	{"setTitle",setTitle,2},
	{"setPlayer",setPlayer,2},
	{"setMove",setMove,2},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,0,0,0);
	return 0;
}
int module_stop(){
	return 0;
}