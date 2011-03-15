TARGET = ../sceGu
OBJS = main.o ../../main/JSE.o\
	callbackFin.o callbackSig.o \
	guInternal.o resetValues.o \
	sceGuAlphaFunc.o sceGuAmbient.o \
	sceGuAmbientColor.o sceGuBeginObject.o \
	sceGuBlendFunc.o sceGuBoneMatrix.o \
	sceGuBreak.o sceGuCallList.o \
	sceGuCallMode.o sceGuCheckList.o \
	sceGuClear.o sceGuClearColor.o \
	sceGuClearDepth.o sceGuClearStencil.o \
	sceGuClutLoad.o sceGuClutMode.o \
	sceGuColor.o sceGuColorFunc.o \
	sceGuColorMaterial.o sceGuContinue.o \
	sceGuCopyImage.o sceGuDepthBuffer.o \
	sceGuDepthFunc.o sceGuDepthMask.o \
	sceGuDepthOffset.o sceGuDepthRange.o \
	sceGuDisable.o sceGuDispBuffer.o \
	sceGuDisplay.o sceGuDrawArray.o \
	sceGuDrawArrayN.o sceGuDrawBezier.o \
	sceGuDrawBuffer.o sceGuDrawBufferList.o \
	sceGuDrawSpline.o sceGuEnable.o \
	sceGuEndObject.o sceGuFinish.o \
	sceGuFog.o sceGuFrontFace.o \
	sceGuGetAllStatus.o sceGuGetMemory.o \
	sceGuGetStatus.o sceGuInit.o \
	sceGuLight.o sceGuLightAtt.o \
	sceGuLightColor.o sceGuLightMode.o \
	sceGuLightSpot.o sceGuLogicalOp.o \
	sceGuMaterial.o sceGuModelColor.o \
	sceGuMorphWeight.o sceGuOffset.o \
	sceGuPatchDivide.o sceGuPatchFrontFace.o \
	sceGuPatchPrim.o sceGuPixelMask.o \
	sceGuScissor.o sceGuSendCommandf.o \
	sceGuSendCommandi.o sceGuSendList.o \
	sceGuSetAllStatus.o sceGuSetCallback.o \
	sceGuSetDither.o sceGuSetMatrix.o \
	sceGuSetStatus.o sceGuShadeModel.o \
	sceGuSignal.o sceGuSpecular.o \
	sceGuSpriteMode.o sceGuStart.o \
	sceGuStencilFunc.o sceGuStencilOp.o \
	sceGuSwapBuffers.o sceGuSync.o \
	sceGuTerm.o sceGuTexEnvColor.o \
	sceGuTexFilter.o sceGuTexFlush.o \
	sceGuTexFunc.o sceGuTexImage.o \
	sceGuTexLevelMode.o sceGuTexMapMode.o \
	sceGuTexMode.o sceGuTexOffset.o \
	sceGuTexProjMapMode.o sceGuTexScale.o \
	sceGuTexSlope.o sceGuTexSync.o \
	sceGuTexWrap.o sceGuViewport.o \
	sendCommand.o

CFLAGS   = -G0 -Wall -O4 -DUSE_FPS_METER
ASFLAGS  = $(CFLAGS)
LDFLAGS  = -mno-crt0 -nostartfiles

PRX_EXPORTS = pluginGu.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS = -lpsprtc

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
	psp-packer.exe $(TARGET).prx
	rm $(TARGET).elf
#	rm *.o