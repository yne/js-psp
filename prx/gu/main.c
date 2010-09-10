#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <pspgu.h>
#include <pspdisplay.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("sceGu",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

typedef struct ScePspCVector3 {
	signed char x, y, z;
} ScePspCVector3;

void* list=NULL;
PspGeContext __attribute__((aligned(16))) geContext;

JS_FUN(DepthBuffer){
	sceGuDepthBuffer((void*)J2U(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(DispBuffer){
	sceGuDispBuffer(J2I(argv[0]),J2I(argv[1]),(void*)J2U(argv[2]),J2I(argv[3]));
	return JS_TRUE;
}
JS_FUN(DrawBuffer){
	sceGuDrawBuffer(J2I(argv[0]),(void*)J2U(argv[1]),J2I(argv[2]));
	return JS_TRUE;
}
JS_FUN(DrawBufferList){
	sceGuDrawBufferList(J2I(argv[0]),(void*)J2U(argv[1]),J2I(argv[2]));
	return JS_TRUE;
}
JS_FUN(Display){
	*rval = I2J(sceGuDisplay(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(DepthFunc){
	sceGuDepthFunc(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(DepthMask){
	sceGuDepthMask(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(DepthOffset){
	sceGuDepthOffset(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(DepthRange){
	sceGuDepthRange(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(Fog){
	float near,far;
	if (!js_convertArguments(argc, argv, "dd", &near,&far))
		return JS_FALSE;
	sceGuFog(near,far,J2U(argv[2]));
	return JS_TRUE;
}
JS_FUN(Init){
	if(!list)list=js_malloc(argc?J2I(argv[0]):0x40000);
	sceGuInit();
	return JS_TRUE;
}
JS_FUN(Term){
	sceGuTerm();
	js_free(list);
	list=NULL;
	return JS_TRUE;
}
JS_FUN(Break){
	sceGuBreak(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(Continue){
	sceGuContinue();
	return JS_TRUE;
}
JS_FUN(Signal){
	sceGuSignal(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(SendCommandf){
	int cmd;
	float argument;
	if (!js_convertArguments(argc, argv, "id", &cmd,&argument))
		return JS_FALSE;
	sceGuSendCommandf(cmd,argument);
	return JS_TRUE;
}
JS_FUN(SendCommandi){
	sceGuSendCommandi(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(GetMemory){
	*rval = I2J(sceGuGetMemory(J2U(argv[0])));
	return JS_TRUE;
}
JS_FUN(Start){
	sceGuStart(J2I(argv[0]),list);
	return JS_TRUE;
}
JS_FUN(Finish){
	*rval = I2J(sceGuFinish());
	return JS_TRUE;
}
JS_FUN(FinishId){
	*rval = I2J(sceGuFinishId(J2U(argv[0])));
	return JS_TRUE;
}
JS_FUN(CallList){
	sceGuCallList(list);
	return JS_TRUE;
}
JS_FUN(CallMode){
	sceGuCallMode(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(CheckList){
	*rval = I2J(sceGuCheckList());
	return JS_TRUE;
}
JS_FUN(SendList){
	sceGuSendList(J2I(argv[0]),list,&geContext);
	return JS_TRUE;
}
JS_FUN(SwapBuffers){
	void* currentBuffer=sceGuSwapBuffers();
	js_setProperty(NULL,"GU_DRAW_BUFFER", I2J(currentBuffer));
	*rval = I2J(currentBuffer);
	return JS_TRUE;
}
JS_FUN(Sync){
	*rval = I2J(sceGuSync(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(EndObject){
	sceGuEndObject();
	return JS_TRUE;
}
JS_FUN(SetStatus){
	sceGuSetStatus(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(GetStatus){
	*rval = I2J(sceGuGetStatus(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(SetAllStatus){
	sceGuSetAllStatus(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(GetAllStatus){
	*rval = I2J(sceGuGetAllStatus());
	return JS_TRUE;
}
JS_FUN(Enable){
	sceGuEnable(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(Disable){
	sceGuDisable(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(DrawArray){
	if(js_typeOfValue(argv[4])==JSTYPE_OBJECT){
		JSObject *matrix=J2O(argv[4]);
		int n;
		void* vert=NULL;
		switch((J2I(argv[1])&GU_VERTEX_32BITF)){
			case GU_VERTEX_32BITF : {
				ScePspFVector3* vertices = (ScePspFVector3*)sceGuGetMemory(J2I(argv[2])*sizeof(ScePspFVector3));
				for(n=0;n<J2I(argv[2]);n++){
					jsval vector=js_getElement(matrix,n);
					vertices[n].x = J2L(js_getProperty(J2O(vector), "x"));
					vertices[n].y = J2L(js_getProperty(J2O(vector), "y"));
					vertices[n].z = J2L(js_getProperty(J2O(vector), "z"));
				}
			vert = vertices;
			}
			break;
			case GU_VERTEX_16BIT:{
				ScePspSVector3* vertices = (ScePspSVector3*)sceGuGetMemory(J2I(argv[2])*sizeof(ScePspSVector3));
				for(n=0;n<J2I(argv[2]);n++){
					jsval vector=js_getElement(matrix,n);
					vertices[n].x = J2I(js_getProperty(J2O(vector), "x"));
					vertices[n].y = J2I(js_getProperty(J2O(vector), "y"));
					vertices[n].z = J2I(js_getProperty(J2O(vector), "z"));
				}
			vert = vertices;
			}
			break;
			case GU_VERTEX_8BIT:{
				ScePspCVector3* __attribute__((aligned(16))) vertices = (ScePspCVector3*)sceGuGetMemory(J2I(argv[2])*sizeof(ScePspCVector3));
				for(n=0;n<J2I(argv[2]);n++){
					jsval vector=js_getElement(matrix,n);
					vertices[n].x = J2I(js_getProperty(J2O(vector), "x"));
					vertices[n].y = J2I(js_getProperty(J2O(vector), "y"));
					vertices[n].z = J2I(js_getProperty(J2O(vector), "z"));
				}
			vert = vertices;
			}
			break;
		}
		sceGuDrawArray(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),(void*)J2U(argv[3]),vert);
	}else{
		sceGuDrawArray(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),(void*)J2U(argv[3]),(void*)J2I(argv[4]));
	}
	return JS_TRUE;
}
JS_FUN(DrawArrayN){
	JSObject *matrix=J2O(argv[5]);
	ScePspFVector3* vertices=(ScePspFVector3*)sceGuGetMemory(J2I(argv[2])*sizeof(ScePspFVector3));
	int n;
	for(n=0;n<J2I(argv[2]);n++){
		jsval vector=js_getElement(matrix,n);
		vertices[n].x = J2L(js_getProperty(J2O(vector), "x"));
		vertices[n].y = J2L(js_getProperty(J2O(vector), "y"));
		vertices[n].z = J2L(js_getProperty(J2O(vector), "z"));
	}
	sceGuDrawArrayN(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),(void*)J2U(argv[4]),vertices);
	return JS_TRUE;
}
JS_FUN(BeginObject){
	sceGuBeginObject(J2I(argv[0]),J2I(argv[1]),(void*)J2U(argv[2]),(void*)J2U(argv[3]));
	return JS_TRUE;
}
JS_FUN(SetCallback){
	sceGuSetCallback(J2I(argv[0]),(void*)J2U(argv[1]));
	return JS_TRUE;
}
JS_FUN(Light){
	JSObject *matrix=J2O(argv[3]);//array
	ScePspFVector3 * vertices=(ScePspFVector3 *)sceGuGetMemory(sizeof(ScePspFVector3 ));
	jsval vector=js_getElement(matrix,0);
	vertices[0].x = J2L(js_getProperty(J2O(vector), "x"));
	vertices[0].y = J2L(js_getProperty(J2O(vector), "y"));
	vertices[0].z = J2L(js_getProperty(J2O(vector), "z"));
	sceGuLight(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),vertices);
	return JS_TRUE;
}
JS_FUN(LightAtt){
	sceGuLightAtt(J2I(argv[0]),J2L(argv[1]),J2L(argv[2]),J2L(argv[3]));
	return JS_TRUE;
}
JS_FUN(LightColor){
	sceGuLightColor(J2I(argv[0]),J2I(argv[1]),J2U(argv[2]));
	return JS_TRUE;
}
JS_FUN(LightMode){
	sceGuLightMode(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(LightSpot){
	JSObject *matrix=J2O(argv[3]);//array
	ScePspFVector3 * vertices=(ScePspFVector3 *)sceGuGetMemory(sizeof(ScePspFVector3 ));
	jsval vector=js_getElement(matrix,0);
	vertices[0].x = J2L(js_getProperty(J2O(vector), "x"));
	vertices[0].y = J2L(js_getProperty(J2O(vector), "y"));
	vertices[0].z = J2L(js_getProperty(J2O(vector), "z"));
	sceGuLightSpot(J2I(argv[0]),vertices,J2L(argv[4]),J2L(argv[5]));
	return JS_TRUE;
}
JS_FUN(Clear){
	argc?sceGuClear(J2I(argv[0])):sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	return JS_TRUE;
}
JS_FUN(ClearColor){
	sceGuClearColor(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(ClearDepth){
	sceGuClearDepth(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(ClearStencil){
	sceGuClearStencil(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(PixelMask){
	sceGuPixelMask(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(Color){
	sceGuColor(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(Ambient){
	sceGuAmbient(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(AmbientColor){
	sceGuAmbientColor(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(ColorFunc){
	sceGuColorFunc(J2I(argv[0]),J2I(argv[1]),J2U(argv[2]));
	return JS_TRUE;
}
JS_FUN(ColorMaterial){
	sceGuColorMaterial(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(AlphaFunc){
	sceGuAlphaFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	return JS_TRUE;
}
JS_FUN(BlendFunc){
	sceGuBlendFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2U(argv[3]),J2U(argv[4]));
	return JS_TRUE;
}
JS_FUN(Material){
	sceGuMaterial(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(ModelColor){
	sceGuModelColor(J2U(argv[0]),J2U(argv[1]),J2U(argv[2]),J2U(argv[3]));
	return JS_TRUE;
}
JS_FUN(StencilFunc){
	sceGuStencilFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	return JS_TRUE;
}
JS_FUN(StencilOp){
	sceGuStencilOp(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	return JS_TRUE;
}
JS_FUN(Specular){
	sceGuSpecular(J2L(argv[0]));
	return JS_TRUE;
}
JS_FUN(FrontFace){
	sceGuFrontFace(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(LogicalOp){
	sceGuLogicalOp(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(ShadeModel){
	sceGuShadeModel(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(TexEnvColor){
	sceGuTexEnvColor(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(TexFilter){
	sceGuTexFilter(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(TexFlush){
	sceGuTexFlush();
	return JS_TRUE;
}
JS_FUN(TexFunc){
	sceGuTexFunc(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(TexMapMode){
	sceGuTexMapMode(J2I(argv[0]),J2U(argv[1]),J2U(argv[2]));
	return JS_TRUE;
}
JS_FUN(SetDither){
	int xx,xy,xz,xw,
			yx,yy,yz,yw,
			zx,zy,zz,zw,
			wx,wy,wz,ww;
	if (!js_convertArguments(argc, argv, "iiiiiiiiiiiiiiii",&xx,&xy,&xz,&xw,&yx,&yy,&yz,&yw,&zx,&zy,&zz,&zw,&wx,&wy,&wz,&ww))
		return JS_FALSE;
	ScePspIMatrix4 matrix = {
  {xx,xy,xz,xw},
  {yx,yy,yz,yw},
  {zx,zy,zz,zw},
  {wx,wy,wz,ww}
	};
	sceGuSetDither(&matrix);
	return JS_TRUE;
}
JS_FUN(TexImage){
	sceGuTexImage(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),(void*)J2U(argv[4]));
	return JS_TRUE;
}
JS_FUN(TexLevelMode){
	sceGuTexLevelMode(J2U(argv[0]),J2L(argv[1]));
	return JS_TRUE;
}
JS_FUN(TexMode){
	sceGuTexMode(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	return JS_TRUE;
}
JS_FUN(TexOffset){
	sceGuTexOffset(J2L(argv[0]),J2L(argv[1]));
	return JS_TRUE;
}
JS_FUN(TexProjMapMode){
	sceGuTexProjMapMode(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(TexScale){
	sceGuTexScale(J2L(argv[0]),J2L(argv[1]));
	return JS_TRUE;
}
JS_FUN(TexSlope){
	sceGuTexSlope(J2L(argv[0]));
	return JS_TRUE;
}
JS_FUN(TexSync){
	sceGuTexSync();
	return JS_TRUE;
}
JS_FUN(TexWrap){
	sceGuTexWrap(J2I(argv[0]),J2I(argv[1]));
	return JS_TRUE;
}
JS_FUN(ClutLoad){
	sceGuClutLoad(J2I(argv[0]),(void*)J2U(argv[1]));
	return JS_TRUE;
}
JS_FUN(ClutMode){
	sceGuClutMode(J2U(argv[0]),J2U(argv[1]),J2U(argv[2]),J2U(argv[3]));
	return JS_TRUE;
}
JS_FUN(Offset){
	sceGuOffset(J2U(argv[0]),J2U(argv[1]));
	return JS_TRUE;
}
JS_FUN(Scissor){
	sceGuScissor(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	return JS_TRUE;
}
JS_FUN(Viewport){
	sceGuViewport(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	return JS_TRUE;
}
JS_FUN(PatchDivide){
	sceGuPatchDivide(J2U(argv[0]),J2U(argv[1]));
	return JS_TRUE;
}
JS_FUN(PatchFrontFace){
	sceGuPatchFrontFace(J2U(argv[0]));
	return JS_TRUE;
}
JS_FUN(PatchPrim){
	sceGuPatchPrim(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(MorphWeight){
	sceGuMorphWeight(J2I(argv[0]),J2L(argv[1]));
	return JS_TRUE;
}
JS_FUN(DrawBezier){
	sceGuDrawBezier(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),(void*)J2U(argv[3]),(void*)J2U(argv[4]));
	return JS_TRUE;
}
JS_FUN(DrawSpline){
	sceGuDrawSpline(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),J2I(argv[4]),(void*)J2U(argv[5]),(void*)J2U(argv[6]));
	return JS_TRUE;
}
JS_FUN(SwapBuffersBehaviour){
	guSwapBuffersBehaviour(J2I(argv[0]));
	return JS_TRUE;
}
JS_FUN(BoneMatrix){
	u32 index;
	float xx,xy,xz,xw,
				yx,yy,yz,yw,
				zx,zy,zz,zw,
				wx,wy,wz,ww;
	if (!js_convertArguments(argc, argv, "uiiiiiiiiiiiiiiii",&index,&xx,&xy,&xz,&xw,&yx,&yy,&yz,&yw,&zx,&zy,&zz,&zw,&wx,&wy,&wz,&ww))
		return JS_FALSE;
	ScePspFMatrix4 matrix = {
  {xx,xy,xz,xw},
  {yx,yy,yz,yw},
  {zx,zy,zz,zw},
  {wx,wy,wz,ww}
	};
	sceGuBoneMatrix(index,&matrix);
	return JS_TRUE;
}
JS_FUN(SetMatrix){
	int type;
	float xx,xy,xz,xw,
				yx,yy,yz,yw,
				zx,zy,zz,zw,
				wx,wy,wz,ww;
	if (!js_convertArguments(argc, argv, "iiiiiiiiiiiiiiiii",&type,&xx,&xy,&xz,&xw,&yx,&yy,&yz,&yw,&zx,&zy,&zz,&zw,&wx,&wy,&wz,&ww))
		return JS_FALSE;
	ScePspFMatrix4 matrix = {
  {xx,xy,xz,xw},
  {yx,yy,yz,yw},
  {zx,zy,zz,zw},
  {wx,wy,wz,ww}
	};
	sceGuSetMatrix(type,&matrix);
	return JS_TRUE;
}
JS_FUN(CopyImage){
	//sceGuCopyImage (int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest)
	return JS_TRUE;
}
JS_FUN(SwapBuffersCallback){
	//guSwapBuffersCallback (GuSwapBuffersCallback callback)
	return JS_TRUE;
}
JS_FUN(Setup){
	#define BUF_WIDTH (512)
	#define SCR_WIDTH (480)
	#define SCR_HEIGHT (272)
	#define PIXEL_SIZE (4)
	#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCR_H*PIXEL_SIZE)

  sceGuInit();
	if(!list)list=js_malloc(0x40000);
  sceGuStart(GU_DIRECT, list);
	sceGuDrawBuffer(GU_PSM_8888, (void*)0, BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, (void*)0x88000, BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000, BUF_WIDTH);
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
  sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
  sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
  sceGuDepthRange(0xc350, 0x2710);
  sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
  sceGuEnable(GU_SCISSOR_TEST);
  sceGuAlphaFunc(GU_GREATER, 0, 0xff);
  sceGuEnable(GU_ALPHA_TEST);
  sceGuDepthFunc(GU_GEQUAL);
  sceGuDisable(GU_DEPTH_TEST);
  sceGuFrontFace(GU_CW);
  sceGuShadeModel(GU_SMOOTH);
  sceGuEnable(GU_CULL_FACE);
  sceGuEnable(GU_TEXTURE_2D);
  sceGuEnable(GU_CLIP_PLANES);
  sceGuTexMode(GU_PSM_8888, 0, 0, 0);
  sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
  sceGuTexFilter(GU_NEAREST, GU_NEAREST);
  sceGuAmbientColor(0xffffffff);
  sceGuEnable(GU_BLEND);
  sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
  sceGuFinish();
  sceGuSync(0, 0);
  sceGuDisplay(GU_TRUE);
 
	return JS_TRUE;
}
typedef struct{
	unsigned short u, v;
	short x, y, z;
} Vertex;
JS_FUN(BlitImage){
//(int sx, int sy, int width, int height, Image* source, int dx, int dy)
//	sceKernelDcacheWritebackInvalidateAll();
	int dx=0,dy=0,sx=0,sy=0,imgW,imgH,texW,texH;
	if(!argc)return JS_TRUE;
	if(argc>2){//at least 3 param (image+screenX+screenY)
		dx=J2I(argv[1]);
		dy=J2I(argv[2]);
	}
	imgW=J2I(js_getProperty(J2O(argv[0]),"imgW"));
	imgH=J2I(js_getProperty(J2O(argv[0]),"imgH"));
	texW=J2I(js_getProperty(J2O(argv[0]),"texW"));
	texH=J2I(js_getProperty(J2O(argv[0]),"texH"));

	sceGuTexImage(0, texW, texH, texW, (void*) J2S(js_getProperty(J2O(argv[0]),"data")));
	//float u = 1.0f / ((float)texW);
	//float v = 1.0f / ((float)texH);
	//sceGuTexScale(u, v);
	int j = 0;
	while (j < imgW) {
		Vertex* v = (Vertex*) sceGuGetMemory(2 * sizeof(Vertex));
		int sliceWidth = 64;
		if (j + sliceWidth > imgW) sliceWidth = imgW - j;
		v[0].u = sx + j;
		v[0].v = sy;
		v[0].x = dx + j;
		v[0].y = dy;
		v[0].z = 0;
		//------  v[0]  +
		v[1].u = v[0].u + sliceWidth;
		v[1].v = v[0].v + imgH;
		v[1].x = v[0].x + sliceWidth;
		v[1].y = v[0].y + imgH;
		v[1].z = v[0].z;
		sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, v);
		j += sliceWidth;
	}

	return JS_TRUE;
}
JS_FUN(BlitImage_ori){
	int x=0,y=0,imgW,imgH,texW,texH;
	if(!argc)return JS_TRUE;
	if(argc>2){//at least 3 param (image+screenX+screenY)
		x=J2I(argv[1]);
		y=J2I(argv[2]);
	}
	imgW=J2I(js_getProperty(J2O(argv[0]),"imgW"));
	imgH=J2I(js_getProperty(J2O(argv[0]),"imgH"));
	texW=J2I(js_getProperty(J2O(argv[0]),"texW"));
	texH=J2I(js_getProperty(J2O(argv[0]),"texH"));

  sceGuTexMode(GU_PSM_8888,0,0,0);
  sceGuTexImage(0,texW,texH,texW,J2S(js_getProperty(J2O(argv[0]),"data")));
	typedef struct{
		unsigned short u, v;
		short x, y, z;
	}tVertex;

  tVertex* v = sceGuGetMemory(2 * sizeof(tVertex));
  v[0].u = 0;v[1].u = 0+imgW;
  v[0].v = 0;v[1].v = 0+imgH;
  v[0].x = x;v[1].x = x+imgW;
  v[0].y = y;v[1].y = y+imgH;
  v[0].z = 0;v[1].z = 0;
	
  sceGuEnable(GU_TEXTURE_2D);
  sceGuDisable(GU_DEPTH_TEST);
  sceGuEnable(GU_BLEND);
	if(argc>3)
		sceGuColor(GU_RGBA(255,255,255,255));
  sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, v);

	return JS_TRUE;
}
static JSFunctionSpec functions[]={
	//custom macro from graphics.c
	{"setup",Setup,0},
	{"blitImage",BlitImage,3},
	//standard sce* functions
	{"depthBuffer",DepthBuffer,2},
	{"dispBuffer",DispBuffer,4},
	{"drawBuffer",DrawBuffer,3},
	{"drawBufferList",DrawBufferList,3},
	{"display",Display,1},
	{"depthFunc",DepthFunc,1},
	{"depthMask",DepthMask,1},
  {"depthOffset",DepthOffset,1},
	{"depthRange",DepthRange,2},
	{"fog",Fog,3},
	{"init",Init,0},
	{"term",Term,0},
	{"break",Break,1},
	{"continue",Continue,0},
	{"setCallback",SetCallback,2},//
	{"signal",Signal,2},
	{"sendCommandf",SendCommandf,2},
	{"sendCommandi",SendCommandi,2},
	{"getMemory",GetMemory,1},
	{"start",Start,1},
	{"finish",Finish,0},
	{"finishId",FinishId,1},
	{"callList",CallList,1},
	{"callMode",CallMode,1},
	{"checkList",CheckList,0},
	{"sendList",SendList,1},
	{"swapBuffers",SwapBuffers,0},
	{"sync",Sync,2},
	{"drawArray",DrawArray,5},
	{"beginObject",BeginObject,4},
	{"endObject",EndObject,0},
	{"setStatus",SetStatus,2},
	{"getStatus",GetStatus,1},
	{"setAllStatus",SetAllStatus,1},
	{"getAllStatus",GetAllStatus,0},
	{"enable",Enable,1},
	{"disable",Disable,1},
	{"light",Light,4},
	{"lightAtt",LightAtt,4},
	{"lightColor",LightColor,3},
	{"lightMode",LightMode,1},
	{"lightSpot",LightSpot,4},
	{"clear",Clear,1},
	{"clearColor",ClearColor,1},
	{"clearDepth",ClearDepth,1},
	{"clearStencil",ClearStencil,1},
	{"pixelMask",PixelMask,1},
	{"color",Color,1},
	{"colorFunc",ColorFunc,3},
	{"colorMaterial",ColorMaterial,1},
	{"alphaFunc",AlphaFunc,3},
	{"ambient",Ambient,1},
	{"ambientColor",AmbientColor,1},
	{"blendFunc",BlendFunc,5},
	{"material",Material,2},
	{"modelColor",ModelColor,4},
	{"stencilFunc",StencilFunc,3},
	{"stencilOp",StencilOp,3},
	{"specular",Specular,1},
	{"frontFace",FrontFace,1},
	{"logicalOp",LogicalOp,1},
	{"setDither",SetDither,1},
	{"shadeModel",ShadeModel,1},
	{"copyImage",CopyImage,11},
	{"texEnvColor",TexEnvColor,1},
	{"texFilter",TexFilter,2},
	{"texFlush",TexFlush,0},
	{"texFunc",TexFunc,2},
	{"texImage",TexImage,5},
	{"texLevelMode",TexLevelMode,2},
	{"texMapMode",TexMapMode,3},
	{"texMode",TexMode,4},
	{"texOffset",TexOffset,2},
	{"texProjMapMode",TexProjMapMode,1},
	{"texScale",TexScale,2},
	{"texSlope",TexSlope,1},
	{"texSync",TexSync,0},
	{"texWrap",TexWrap,2},
	{"clutLoad",ClutLoad,2},
	{"clutMode",ClutMode,4},
	{"offset",Offset,2},
	{"scissor",Scissor,4},
	{"viewport",Viewport,4},
	{"drawBezier",DrawBezier,5},
	{"patchDivide",PatchDivide,2},
	{"patchFrontFace",PatchFrontFace,1},
	{"patchPrim",PatchPrim,1},
	{"drawSpline",DrawSpline,7},
	{"setMatrix",SetMatrix,2},
	{"boneMatrix",BoneMatrix,2},
	{"morphWeight",MorphWeight,2},
	{"drawArrayN",DrawArrayN,6},
	{"swapBuffersBehaviour",SwapBuffersBehaviour,1},
	{"swapBuffersCallback",SwapBuffersCallback,1},
	{0}
};
static JSFunctionSpec gfunctions[]={
//custom functions
//standard sce* functions
	{"sceGuDepthBuffer",DepthBuffer,2},
	{"sceGuDispBuffer",DispBuffer,4},
	{"sceGuDrawBuffer",DrawBuffer,3},
	{"sceGuDrawBufferList",DrawBufferList,3},
	{"sceGuDisplay",Display,1},
	{"sceGuDepthFunc",DepthFunc,1},
	{"sceGuDepthMask",DepthMask,1},
  {"sceGuDepthOffset",DepthOffset,1},
	{"sceGuDepthRange",DepthRange,2},
	{"sceGuFog",Fog,3},
	{"sceGuInit",Init,0},
	{"sceGuTerm",Term,0},
	{"sceGuBreak",Break,1},
	{"sceGuContinue",Continue,0},
	{"sceGuSetCallback",SetCallback,2},//
	{"sceGuSignal",Signal,2},
	{"sceGuSendCommandf",SendCommandf,2},
	{"sceGuSendCommandi",SendCommandi,2},
	{"sceGuGetMemory",GetMemory,1},
	{"sceGuStart",Start,1},
	{"sceGuFinish",Finish,0},
	{"sceGuFinishId",FinishId,1},
	{"sceGuCallList",CallList,1},
	{"sceGuCallMode",CallMode,1},
	{"sceGuCheckList",CheckList,0},
	{"sceGuSendList",SendList,1},
	{"sceGuSwapBuffers",SwapBuffers,0},
	{"sceGuSync",Sync,2},
	{"sceGuDrawArray",DrawArray,5},
	{"sceGuBeginObject",BeginObject,4},
	{"sceGuEndObject",EndObject,0},
	{"sceGuSetStatus",SetStatus,2},
	{"sceGuGetStatus",GetStatus,1},
	{"sceGuSetAllStatus",SetAllStatus,1},
	{"sceGuGetAllStatus",GetAllStatus,0},
	{"sceGuEnable",Enable,1},
	{"sceGuDisable",Disable,1},
	{"sceGuLight",Light,4},
	{"sceGuLightAtt",LightAtt,4},
	{"sceGuLightColor",LightColor,3},
	{"sceGuLightMode",LightMode,1},
	{"sceGuLightSpot",LightSpot,4},
	{"sceGuClear",Clear,1},
	{"sceGuClearColor",ClearColor,1},
	{"sceGuClearDepth",ClearDepth,1},
	{"sceGuClearStencil",ClearStencil,1},
	{"sceGuPixelMask",PixelMask,1},
	{"sceGuColor",Color,1},
	{"sceGuColorFunc",ColorFunc,3},
	{"sceGuColorMaterial",ColorMaterial,1},
	{"sceGuAlphaFunc",AlphaFunc,3},
	{"sceGuAmbient",Ambient,1},
	{"sceGuAmbientColor",AmbientColor,1},
	{"sceGuBlendFunc",BlendFunc,5},
	{"sceGuMaterial",Material,2},
	{"sceGuModelColor",ModelColor,4},
	{"sceGuStencilFunc",StencilFunc,3},
	{"sceGuStencilOp",StencilOp,3},
	{"sceGuSpecular",Specular,1},
	{"sceGuFrontFace",FrontFace,1},
	{"sceGuLogicalOp",LogicalOp,1},
	{"sceGuSetDither",SetDither,1},
	{"sceGuShadeModel",ShadeModel,1},
	{"sceGuCopyImage",CopyImage,11},
	{"sceGuTexEnvColor",TexEnvColor,1},
	{"sceGuTexFilter",TexFilter,2},
	{"sceGuTexFlush",TexFlush,0},
	{"sceGuTexFunc",TexFunc,2},
	{"sceGuTexImage",TexImage,5},
	{"sceGuTexLevelMode",TexLevelMode,2},
	{"sceGuTexMapMode",TexMapMode,3},
	{"sceGuTexMode",TexMode,4},
	{"sceGuTexOffset",TexOffset,2},
	{"sceGuTexProjMapMode",TexProjMapMode,1},
	{"sceGuTexScale",TexScale,2},
	{"sceGuTexSlope",TexSlope,1},
	{"sceGuTexSync",TexSync,0},
	{"sceGuTexWrap",TexWrap,2},
	{"sceGuClutLoad",ClutLoad,2},
	{"sceGuClutMode",ClutMode,4},
	{"sceGuOffset",Offset,2},
	{"sceGuScissor",Scissor,4},
	{"sceGuViewport",Viewport,4},
	{"sceGuDrawBezier",DrawBezier,5},
	{"sceGuPatchDivide",PatchDivide,2},
	{"sceGuPatchFrontFace",PatchFrontFace,1},
	{"sceGuPatchPrim",PatchPrim,1},
	{"sceGuDrawSpline",DrawSpline,7},
	{"sceGuSetMatrix",SetMatrix,2},
	{"sceGuBoneMatrix",BoneMatrix,2},
	{"sceGuMorphWeight",MorphWeight,2},
	{"sceGuDrawArrayN",DrawArrayN,6},
	{"sceGuSwapBuffersBehaviour",SwapBuffersBehaviour,1},
	{"sceGuSwapBuffersCallback",SwapBuffersCallback,1},
	{0}
};
static JSPropertiesSpec var[] = {
//custom define
	{"GU_DRAW_BUFFER",I2J(0)},
	{"BUF_WIDTH",I2J(512)},
	{"SCR_WIDTH",I2J(480)},
	{"SCR_HEIGHT",I2J(272)},
//gu* define
	{"GU_TRUE",I2J(1)},
	{"GU_FALSE",I2J(0)},
	{"GU_TRUE",I2J(1)},
	{"GU_POINTS",I2J(0)},
	{"GU_LINES",I2J(1)},
	{"GU_LINE_STRIP",I2J(2)},
	{"GU_TRIANGLES",I2J(3)},
	{"GU_TRIANGLE_STRIP",I2J(4)},
	{"GU_TRIANGLE_FAN",I2J(5)},
	{"GU_SPRITES",I2J(6)},
	{"GU_ALPHA_TEST",I2J(0)},
	{"GU_DEPTH_TEST",I2J(1)},
	{"GU_SCISSOR_TEST",I2J(2)},
	{"GU_STENCIL_TEST",I2J(3)},
	{"GU_BLEND",I2J(4)},
	{"GU_CULL_FACE",I2J(5)},
	{"GU_DITHER",I2J(6)},
	{"GU_FOG",I2J(7)},
	{"GU_CLIP_PLANES",I2J(8)},
	{"GU_TEXTURE_2D",I2J(9)},
	{"GU_LIGHTING",I2J(10)},
	{"GU_LIGHT0",I2J(11)},
	{"GU_LIGHT1",I2J(12)},
	{"GU_LIGHT2",I2J(13)},
	{"GU_LIGHT3",I2J(14)},
	{"GU_LINE_SMOOTH",I2J(15)},
	{"GU_PATCH_CULL_FACE",I2J(16)},
	{"GU_COLOR_TEST",I2J(17)},
	{"GU_COLOR_LOGIC_OP",I2J(18)},
	{"GU_FACE_NORMAL_REVERSE",I2J(19)},
	{"GU_PATCH_FACE",I2J(20)},
	{"GU_FRAGMENT_2X",I2J(21)},
	{"GU_PROJECTION",I2J(0)},
	{"GU_VIEW",I2J(1)},
	{"GU_MODEL",I2J(2)},
	{"GU_TEXTURE",I2J(3)},
	{"GU_LIGHT2",I2J(13)},
	{"GU_TEXTURE_8BIT",I2J(GU_TEXTURE_SHIFT(1))},
	{"GU_TEXTURE_16BIT",I2J(GU_TEXTURE_SHIFT(2))},
	{"GU_TEXTURE_32BITF",I2J(GU_TEXTURE_SHIFT(3))},
	{"GU_TEXTURE_BITS",I2J(GU_TEXTURE_SHIFT(3))},
	{"GU_COLOR_5650",I2J(GU_COLOR_SHIFT(4))},
	{"GU_COLOR_5551",I2J(GU_COLOR_SHIFT(5))},
	{"GU_COLOR_4444",I2J(GU_COLOR_SHIFT(6))},
	{"GU_COLOR_8888",I2J(GU_COLOR_SHIFT(7))},
	{"GU_COLOR_BITS",I2J(GU_COLOR_SHIFT(7))},
	{"GU_NORMAL_8BIT",I2J(GU_NORMAL_SHIFT(1))},
	{"GU_NORMAL_16BIT",I2J(GU_NORMAL_SHIFT(2))},
	{"GU_NORMAL_32BITF",I2J(GU_NORMAL_SHIFT(3))},
	{"GU_NORMAL_BITS",I2J(GU_NORMAL_SHIFT(3))},
	{"GU_VERTEX_8BIT",I2J(GU_VERTEX_SHIFT(1))},
	{"GU_VERTEX_16BIT",I2J(GU_VERTEX_SHIFT(2))},
	{"GU_VERTEX_32BITF",I2J(GU_VERTEX_SHIFT(3))},
	{"GU_VERTEX_BITS",I2J(GU_VERTEX_SHIFT(3))},
	{"GU_WEIGHT_8BIT",I2J(GU_WEIGHT_SHIFT(1))},
	{"GU_WEIGHT_16BIT",I2J(GU_WEIGHT_SHIFT(2))},
	{"GU_WEIGHT_32BITF",I2J(GU_WEIGHT_SHIFT(3))},
	{"GU_WEIGHT_BITS",I2J(GU_WEIGHT_SHIFT(3))},
	{"GU_INDEX_8BIT",I2J(GU_INDEX_SHIFT(1))},
	{"GU_INDEX_16BIT",I2J(GU_INDEX_SHIFT(2))},
	{"GU_INDEX_BITS",I2J(GU_INDEX_SHIFT(3))},
	{"GU_WEIGHTS_BITS",I2J(GU_WEIGHTS(8))},
	{"GU_VERTICES_BITS",I2J(GU_VERTICES(8))},
	{"GU_TRANSFORM_3D",I2J(GU_TRANSFORM_SHIFT(0))},
	{"GU_TRANSFORM_2D",I2J(GU_TRANSFORM_SHIFT(1))},
	{"GU_TRANSFORM_BITS",I2J(GU_TRANSFORM_SHIFT(1))},
	{"GU_PSM_5650",I2J(0)}, // Display, Texture, Palette
	{"GU_PSM_5551",I2J(1)}, // Display, Texture, Palette
	{"GU_PSM_4444",I2J(2)}, // Display, Texture, Palette
	{"GU_PSM_8888",I2J(3)}, // Display, Texture, Palette
	{"GU_PSM_T4",I2J(4)}, // Texture
	{"GU_PSM_T8",I2J(5)}, // Texture
	{"GU_PSM_T16",I2J(6)}, // Texture
	{"GU_PSM_T32",I2J(7)}, // Texture
	{"GU_PSM_DXT1",I2J(8)}, // Texture
	{"GU_PSM_DXT3",I2J(9)}, // Texture
	{"GU_PSM_DXT5",I2J(10)}, // Texture
	{"GU_FILL_FILL",I2J(0)},
	{"GU_OPEN_FILL",I2J(1)},
	{"GU_FILL_OPEN",I2J(2)},
	{"GU_OPEN_OPEN",I2J(3)},
	{"GU_FLAT",I2J(0)},
	{"GU_SMOOTH",I2J(1)},
	{"GU_CLEAR",I2J(0)},
	{"GU_AND",I2J(1)},
	{"GU_AND_REVERSE",I2J(2)},
	{"GU_COPY",I2J(3)},
	{"GU_AND_INVERTED",I2J(4)},
	{"GU_NOOP",I2J(5)},
	{"GU_XOR",I2J(6)},
	{"GU_OR",I2J(7)},
	{"GU_NOR",I2J(8)},
	{"GU_EQUIV",I2J(9)},
	{"GU_INVERTED",I2J(10)},
	{"GU_OR_REVERSE",I2J(11)},
	{"GU_COPY_INVERTED",I2J(12)},
	{"GU_OR_INVERTED",I2J(13)},
	{"GU_NAND",I2J(14)},
	{"GU_SET",I2J(15)},
	{"GU_NEAREST",I2J(0)},
	{"GU_LINEAR",I2J(1)},
	{"GU_NEAREST_MIPMAP_NEAREST",I2J(4)},
	{"GU_LINEAR_MIPMAP_NEAREST",I2J(5)},
	{"GU_NEAREST_MIPMAP_LINEAR",I2J(6)},
	{"GU_LINEAR_MIPMAP_LINEAR",I2J(7)},
	{"GU_TEXTURE_COORDS",I2J(0)},
	{"GU_TEXTURE_MATRIX",I2J(1)},
	{"GU_ENVIRONMENT_MAP",I2J(2)},
	{"GU_TEXTURE_AUTO",I2J(0)},
	{"GU_TEXTURE_CONST",I2J(1)},
	{"GU_TEXTURE_SLOPE",I2J(2)},
	{"GU_POSITION",I2J(0)},
	{"GU_UV",I2J(1)},
	{"GU_NORMALIZED_NORMAL",I2J(2)},
	{"GU_NORMAL",I2J(3)},
	{"GU_REPEAT",I2J(0)},
	{"GU_CLAMP",I2J(1)},
	{"GU_CW",I2J(0)},
	{"GU_CCW",I2J(1)},
	{"GU_NEVER",I2J(0)},
	{"GU_ALWAYS",I2J(1)},
	{"GU_EQUAL",I2J(2)},
	{"GU_NOTEQUAL",I2J(3)},
	{"GU_LESS",I2J(4)},
	{"GU_LEQUAL",I2J(5)},
	{"GU_GREATER",I2J(6)},
	{"GU_GEQUAL",I2J(7)},
	{"GU_COLOR_BUFFER_BIT",I2J(1)},
	{"GU_STENCIL_BUFFER_BIT",I2J(2)},
	{"GU_DEPTH_BUFFER_BIT",I2J(4)},
	{"GU_FAST_CLEAR_BIT",I2J(16)},
	{"GU_TFX_MODULATE",I2J(0)},
	{"GU_TFX_DECAL",I2J(1)},
	{"GU_TFX_BLEND",I2J(2)},
	{"GU_TFX_REPLACE",I2J(3)},
	{"GU_TFX_ADD",I2J(4)},
	{"GU_TCC_RGB",I2J(0)},
	{"GU_TCC_RGBA",I2J(1)},
	{"GU_ADD",I2J(0)},
	{"GU_SUBTRACT",I2J(1)},
	{"GU_REVERSE_SUBTRACT",I2J(2)},
	{"GU_MIN",I2J(3)},
	{"GU_MAX",I2J(4)},
	{"GU_ABS",I2J(5)},
	{"GU_SRC_COLOR",I2J(0)},
	{"GU_ONE_MINUS_SRC_COLOR",I2J(1)},
	{"GU_SRC_ALPHA",I2J(2)},
	{"GU_ONE_MINUS_SRC_ALPHA",I2J(3)},
	{"GU_DST_COLOR",I2J(0)},
	{"GU_ONE_MINUS_DST_COLOR",I2J(1)},
	{"GU_DST_ALPHA",I2J(4)},
	{"GU_ONE_MINUS_DST_ALPHA",I2J(5)},
	{"GU_FIX",I2J(10)},
	{"GU_KEEP",I2J(0)},
	{"GU_ZERO",I2J(1)},
	{"GU_REPLACE",I2J(2)},
	{"GU_INVERT",I2J(3)},
	{"GU_INCR",I2J(4)},
	{"GU_DECR",I2J(5)},
	{"GU_AMBIENT",I2J(1)},
	{"GU_DIFFUSE",I2J(2)},
	{"GU_SPECULAR",I2J(4)},
	{"GU_AMBIENT_AND_DIFFUSE",I2J(GU_AMBIENT|GU_DIFFUSE)},
	{"GU_DIFFUSE_AND_SPECULAR",I2J(GU_DIFFUSE|GU_SPECULAR)},
	{"GU_UNKNOWN_LIGHT_COMPONENT",I2J(8)},
	{"GU_SINGLE_COLOR",I2J(0)},
	{"GU_SEPARATE_SPECULAR_COLOR",I2J(1)},
	{"GU_DIRECTIONAL",I2J(0)},
	{"GU_POINTLIGHT",I2J(1)},
	{"GU_SPOTLIGHT",I2J(2)},
	{"GU_DIRECT",I2J(0)},
	{"GU_CALL",I2J(1)},
	{"GU_SEND",I2J(2)},
	{"GU_TAIL",I2J(0)},
	{"GU_HEAD",I2J(1)},
	{"GU_SYNC_FINISH",I2J(0)},
	{"GU_SYNC_SIGNAL",I2J(1)},
	{"GU_SYNC_DONE",I2J(2)},
	{"GU_SYNC_LIST",I2J(3)},
	{"GU_SYNC_SEND",I2J(4)},
	{"GU_SYNC_WAIT",I2J(0)},
	{"GU_SYNC_NOWAIT",I2J(1)},
	{"GU_SYNC_WHAT_DONE",I2J(0)},
	{"GU_SYNC_WHAT_QUEUED",I2J(1)},
	{"GU_SYNC_WHAT_DRAW",I2J(2)},
	{"GU_SYNC_WHAT_STALL",I2J(3)},
	{"GU_SYNC_WHAT_CANCEL",I2J(4)},
	{"GU_CALLBACK_SIGNAL",I2J(1)},
	{"GU_CALLBACK_FINISH",I2J(4)},
	{"GU_BEHAVIOR_SUSPEND",I2J(1)},
	{"GU_BEHAVIOR_CONTINUE",I2J(2)},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(functions,gfunctions,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	if(list)
		js_free(list);
	return 0;
}
