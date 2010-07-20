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

unsigned* list;
PspGeContext __attribute__((aligned(16))) geContext;

JSBool DepthBuffer(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDepthBuffer((void*)J2U(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DispBuffer(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDispBuffer(J2I(argv[0]),J2I(argv[1]),(void*)J2U(argv[2]),J2I(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawBuffer(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDrawBuffer(J2I(argv[0]),(void*)J2U(argv[1]),J2I(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawBufferList(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDrawBufferList(J2I(argv[0]),(void*)J2U(argv[1]),J2I(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Display(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuDisplay(J2I(argv[0])));
	return JS_TRUE;
}
JSBool DepthFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDepthFunc(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DepthMask(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDepthMask(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DepthOffset(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDepthOffset(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DepthRange(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDepthRange(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Fog(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	float near,far;
	if (!js_convertArguments(argc, argv, "dd", &near,&far))
		return JS_FALSE;
	sceGuFog(near,far,J2U(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Init(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	list=js_malloc(0x40000);
	sceGuInit();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Term(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTerm();
	js_free(list);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Break(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuBreak(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Continue(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuContinue();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Signal(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSignal(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SendCommandf(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	int cmd;
	float argument;
	if (!js_convertArguments(argc, argv, "id", &cmd,&argument))
		return JS_FALSE;
	sceGuSendCommandf(cmd,argument);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SendCommandi(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSendCommandi(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool GetMemory(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuGetMemory(J2I(argv[0])));
	return JS_TRUE;
}
JSBool Start(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuStart(J2I(argv[0]),list);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Finish(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuFinish());
	return JS_TRUE;
}
JSBool FinishId(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuFinishId(J2U(argv[0])));
	return JS_TRUE;
}
JSBool CallList(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuCallList(list);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool CallMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuCallMode(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool CheckList(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuCheckList());
	return JS_TRUE;
}
JSBool SendList(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSendList(J2I(argv[0]),list,&geContext);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SwapBuffers(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuSwapBuffers());
	return JS_TRUE;
}
JSBool Sync(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuSync(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JSBool EndObject(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuEndObject();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SetStatus(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSetStatus(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool GetStatus(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuGetStatus(J2I(argv[0])));
	return JS_TRUE;
}
JSBool SetAllStatus(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSetAllStatus(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool GetAllStatus(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	*rval = I2J(sceGuGetAllStatus());
	return JS_TRUE;
}
JSBool Enable(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuEnable(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Disable(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDisable(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawArray(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
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
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawArrayN(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
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
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool BeginObject(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuBeginObject(J2I(argv[0]),J2I(argv[1]),(void*)J2U(argv[2]),(void*)J2U(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SetCallback(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSetCallback(J2I(argv[0]),(void*)J2U(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Light(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	JSObject *matrix=J2O(argv[3]);//array
	ScePspFVector3 * vertices=(ScePspFVector3 *)sceGuGetMemory(sizeof(ScePspFVector3 ));
	jsval vector=js_getElement(matrix,0);
	vertices[0].x = J2L(js_getProperty(J2O(vector), "x"));
	vertices[0].y = J2L(js_getProperty(J2O(vector), "y"));
	vertices[0].z = J2L(js_getProperty(J2O(vector), "z"));
	sceGuLight(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),vertices);
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool LightAtt(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuLightAtt(J2I(argv[0]),J2L(argv[1]),J2L(argv[2]),J2L(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool LightColor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuLightColor(J2I(argv[0]),J2I(argv[1]),J2U(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool LightMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuLightMode(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool LightSpot(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	JSObject *matrix=J2O(argv[3]);//array
	ScePspFVector3 * vertices=(ScePspFVector3 *)sceGuGetMemory(sizeof(ScePspFVector3 ));
	jsval vector=js_getElement(matrix,0);
	vertices[0].x = J2L(js_getProperty(J2O(vector), "x"));
	vertices[0].y = J2L(js_getProperty(J2O(vector), "y"));
	vertices[0].z = J2L(js_getProperty(J2O(vector), "z"));
	sceGuLightSpot(J2I(argv[0]),vertices,J2L(argv[4]),J2L(argv[5]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Clear(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClear(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ClearColor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClearColor(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ClearDepth(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClearDepth(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ClearStencil(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClearStencil(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool PixelMask(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuPixelMask(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Color(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuColor(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Ambient(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuAmbient(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool AmbientColor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuAmbientColor(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ColorFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuColorFunc(J2I(argv[0]),J2I(argv[1]),J2U(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ColorMaterial(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuColorMaterial(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool AlphaFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuAlphaFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool BlendFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuBlendFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2U(argv[3]),J2U(argv[4]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Material(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuMaterial(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ModelColor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuModelColor(J2U(argv[0]),J2U(argv[1]),J2U(argv[2]),J2U(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool StencilFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuStencilFunc(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool StencilOp(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuStencilOp(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Specular(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuSpecular(J2L(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool FrontFace(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuFrontFace(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool LogicalOp(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuLogicalOp(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ShadeModel(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuShadeModel(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexEnvColor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexEnvColor(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexFilter(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexFilter(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexFlush(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexFlush();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexFunc(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexFunc(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexMapMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexMapMode(J2I(argv[0]),J2U(argv[1]),J2U(argv[2]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SetDither(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
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
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexImage(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexImage(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),(void*)J2U(argv[4]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexLevelMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexLevelMode(J2U(argv[0]),J2L(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexMode(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexOffset(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexOffset(J2L(argv[0]),J2L(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexProjMapMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexProjMapMode(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexScale(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexScale(J2L(argv[0]),J2L(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexSlope(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexSlope(J2L(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexSync(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexSync();
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool TexWrap(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuTexWrap(J2I(argv[0]),J2I(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ClutLoad(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClutLoad(J2I(argv[0]),(void*)J2U(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool ClutMode(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuClutMode(J2U(argv[0]),J2U(argv[1]),J2U(argv[2]),J2U(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Offset(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuOffset(J2U(argv[0]),J2U(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Scissor(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuScissor(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool Viewport(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuViewport(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool PatchDivide(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuPatchDivide(J2U(argv[0]),J2U(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool PatchFrontFace(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuPatchFrontFace(J2U(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool PatchPrim(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuPatchPrim(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool MorphWeight(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuMorphWeight(J2I(argv[0]),J2L(argv[1]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawBezier(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDrawBezier(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),(void*)J2U(argv[3]),(void*)J2U(argv[4]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool DrawSpline(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	sceGuDrawSpline(J2I(argv[0]),J2I(argv[1]),J2I(argv[2]),J2I(argv[3]),J2I(argv[4]),(void*)J2U(argv[5]),(void*)J2U(argv[6]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SwapBuffersBehaviour(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	guSwapBuffersBehaviour(J2I(argv[0]));
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool BoneMatrix(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
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
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SetMatrix(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
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
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool CopyImage(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	//sceGuCopyImage (int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest)
	*rval = JSVAL_VOID;
	return JS_TRUE;
}
JSBool SwapBuffersCallback(JSContext *cx, JSObject *gobj, uintN argc, jsval *argv, jsval *rval){
	//guSwapBuffersCallback (GuSwapBuffersCallback callback)
	*rval = JSVAL_VOID;
	return JS_TRUE;
}


static JSFunctionSpec functions[]={
	{"DepthBuffer",DepthBuffer,2},
	{"DispBuffer",DispBuffer,4},
	{"DrawBuffer",DrawBuffer,3},
	{"DrawBufferList",DrawBufferList,3},
	{"Display",Display,1},
	{"DepthFunc",DepthFunc,1},
	{"DepthMask",DepthMask,1},
  {"DepthOffset",DepthOffset,1},
	{"DepthRange",DepthRange,2},
	{"Fog",Fog,3},
	{"Init",Init,0},
	{"Term",Term,0},
	{"Break",Break,1},
	{"Continue",Continue,0},
	{"SetCallback",SetCallback,2},//
	{"Signal",Signal,2},
	{"SendCommandf",SendCommandf,2},
	{"SendCommandi",SendCommandi,2},
	{"GetMemory",GetMemory,1},
	{"Start",Start,1},
	{"Finish",Finish,0},
	{"FinishId",FinishId,1},
	{"CallList",CallList,1},
	{"CallMode",CallMode,1},
	{"CheckList",CheckList,0},
	{"SendList",SendList,1},
	{"SwapBuffers",SwapBuffers,0},
	{"Sync",Sync,2},
	{"DrawArray",DrawArray,5},
	{"BeginObject",BeginObject,4},
	{"EndObject",EndObject,0},
	{"SetStatus",SetStatus,2},
	{"GetStatus",GetStatus,1},
	{"SetAllStatus",SetAllStatus,1},
	{"GetAllStatus",GetAllStatus,0},
	{"Enable",Enable,1},
	{"Disable",Disable,1},
	{"Light",Light,4},
	{"LightAtt",LightAtt,4},
	{"LightColor",LightColor,3},
	{"LightMode",LightMode,1},
	{"LightSpot",LightSpot,4},
	{"Clear",Clear,1},
	{"ClearColor",ClearColor,1},
	{"ClearDepth",ClearDepth,1},
	{"ClearStencil",ClearStencil,1},
	{"PixelMask",PixelMask,1},
	{"Color",Color,1},
	{"ColorFunc",ColorFunc,3},
	{"ColorMaterial",ColorMaterial,1},
	{"AlphaFunc",AlphaFunc,3},
	{"Ambient",Ambient,1},
	{"AmbientColor",AmbientColor,1},
	{"BlendFunc",BlendFunc,5},
	{"Material",Material,2},
	{"ModelColor",ModelColor,4},
	{"StencilFunc",StencilFunc,3},
	{"StencilOp",StencilOp,3},
	{"Specular",Specular,1},
	{"FrontFace",FrontFace,1},
	{"LogicalOp",LogicalOp,1},
	{"SetDither",SetDither,1},
	{"ShadeModel",ShadeModel,1},
	{"CopyImage",CopyImage,11},
	{"TexEnvColor",TexEnvColor,1},
	{"TexFilter",TexFilter,2},
	{"TexFlush",TexFlush,0},
	{"TexFunc",TexFunc,2},
	{"TexImage",TexImage,5},
	{"TexLevelMode",TexLevelMode,2},
	{"TexMapMode",TexMapMode,3},
	{"TexMode",TexMode,4},
	{"TexOffset",TexOffset,2},
	{"TexProjMapMode",TexProjMapMode,1},
	{"TexScale",TexScale,2},
	{"TexSlope",TexSlope,1},
	{"TexSync",TexSync,0},
	{"TexWrap",TexWrap,2},
	{"ClutLoad",ClutLoad,2},
	{"ClutMode",ClutMode,4},
	{"Offset",Offset,2},
	{"Scissor",Scissor,4},
	{"Viewport",Viewport,4},
	{"DrawBezier",DrawBezier,5},
	{"PatchDivide",PatchDivide,2},
	{"PatchFrontFace",PatchFrontFace,1},
	{"PatchPrim",PatchPrim,1},
	{"DrawSpline",DrawSpline,7},
	{"SetMatrix",SetMatrix,2},
	{"BoneMatrix",BoneMatrix,2},
	{"MorphWeight",MorphWeight,2},
	{"DrawArrayN",DrawArrayN,6},
	{"SwapBuffersBehaviour",SwapBuffersBehaviour,1},
	{"SwapBuffersCallback",SwapBuffersCallback,1},
	{0}
};

static JSPropertiesSpec var[] = {
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
	{"GU_PSM_5650",I2J(0)}, /* Display, Texture, Palette */
	{"GU_PSM_5551",I2J(1)}, /* Display, Texture, Palette */
	{"GU_PSM_4444",I2J(2)}, /* Display, Texture, Palette */
	{"GU_PSM_8888",I2J(3)}, /* Display, Texture, Palette */
	{"GU_PSM_T4",I2J(4)}, /* Texture */
	{"GU_PSM_T8",I2J(5)}, /* Texture */
	{"GU_PSM_T16",I2J(6)}, /* Texture */
	{"GU_PSM_T32",I2J(7)}, /* Texture */
	{"GU_PSM_DXT1",I2J(8)}, /* Texture */
	{"GU_PSM_DXT3",I2J(9)}, /* Texture */
	{"GU_PSM_DXT5",I2J(10)}, /* Texture */
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
	js_addModule(functions,0,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
