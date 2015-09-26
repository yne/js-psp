#include <pspkernel.h>
#include <pspvideocodec.h>
#include <pspaudiocodec.h>
#include "libmpeg.h"
#include <string.h>

PSP_MODULE_INFO("libmpeg", 0x1007, 1, 1);

int MpegIsInit=0;
int semaLib,semaAvc,semaAtrac,mpegAvcSema,mpegAtracSema;
unsigned long audioCodecStruct[0x1B];//0x000078C0
unsigned long*pAudioCodecStruct;//0x00007880
unsigned long videoCodecStruct[0x18];//0x000077C0
unsigned long*pVideoCodecStruct;

int createSema (int initVal, int maxVal,const char *name, int*ret){
	return (*ret=sceKernelCreateSema(name,0,initVal,maxVal,0))<0?0x80000041:*ret;
}
int waitSema(int sema){
	return sceKernelWaitSema(sema, 1, 0);
}
int signalSema(int sema){
	return sceKernelSignalSema(sema, 1);
}
int deleteSema(sema){
	return sceKernelDeleteSema(sema) ? 0x80000041:0;
}
int checkMpegLib(SceMpeg *mp){
	return(strcmp((char*)mp->sys, "LIBMPEG")?0x806101FE:0);
}
SceMpegAu*checkAu (SceMpegStream *id, int*arg2, int arg3){//redo it
	/*
	int _id;
	if (((id & 0xFFFFE000)) == 0xBF01E000){
		_id = (id >> 8) & 0x1F;
		if (arg3 == 1) return (SceMpegAu*)arg2[6] + (_id << 4);
		else return (SceMpegAu*)arg2[7] + (((_id << 4) + _id) << 2);
	}
	if (((id & 0xE0000000)) == 0xE0000000){
		_id = (id >> 24) & 0x1F;
		if (arg3 == 1) return (SceMpegAu*)(arg2[6] + (_id << 4)) + 0x100;
		else return (SceMpegAu*)(arg2[7] + (((_id << 4) + _id) << 2)) + 0x440;
	}
	int msb = id & 0xFFF00000;
	if (msb == 0xBD000000){
		_id = (id >> 0x00000010) & 0x000042FF;
		if (arg3 == 1) return (SceMpegAu*)(arg2[6] + (_id << 4)) + 0x00000200;
		else return (SceMpegAu*)(arg2[7] + (((_id << 4) + _id) << 2)) + 0x00000880;
	}
	if (((id & 0xFFE00000)) == 0xBD800000){
		_id = (id >> 0x00000010) & 0x0000427F;
		if (arg3 == 1)return (SceMpegAu*)(arg2[6] + (_id << 4)) + 0x00000400;
		else return (SceMpegAu*)(arg2[7] + (((_id << 4) + _id) << 2)) + 0x00001100;
	}
	if (msb == 0xBD100000){
		_id = (id >> 0x00000010) & 0x000042EF;
		if (arg3 == 1)return (SceMpegAu*)(arg2[6] + (_id << 4)) + 0x00000300;
		else return (SceMpegAu*)(arg2[7] + (((_id << 4) + _id) << 2)) + 0x00000CC0;
	}
	if (msb == 0xBD200000){
		_id = (id >> 0x00000010) & 0x000042DF;
		if (arg3 == 1) return (SceMpegAu*)(arg2[6] + (_id << 4)) + 0x00000600;
		else return (SceMpegAu*)(arg2[7] + (((_id << 4) + _id) << 2)) + 0x00001980;
	}
*/	return (SceMpegAu*)-1;
}
int getPMFversion (const char* arg1){
	if (!strncmp (arg1+4, "0012", 4))return 0;
	if (!strncmp (arg1+4, "0013", 4))return 1;
	if (!strncmp (arg1+4, "0014", 4))return 2;
	if (!strncmp (arg1+4, "0015", 4))return 3;
	return -1;
}
int read16 (unsigned char * arg1){
	return (((arg1[0]<<8)+arg1[1])&0xFFFF);
}
int read24 (unsigned char * arg1){
	return (((arg1[0] << 16) + (arg1[1] << 8)) + arg1[2]);
}
int read32 (unsigned char *arg1){
	return ((((arg1[0] << 24) + (arg1[1] << 16)) + (arg1[2] << 8)) + arg1[3]);
}
int readN (unsigned char *arg1, int arg2){
	if(arg2==1)return arg1[0];
	if(arg2==2)return read16(arg1);
	if(arg2==3)return read24(arg1);
	if(arg2==4)return read32(arg1);
	return 0;
}
int mpegQueryStreamOffset (SceMpeg *mp, const char* addr, unsigned* offset){
	if (strcmp ((char*)mp, "LIBMPEG"))offset=0;return 0x806101FE;
	if (strncmp (addr, "PSMF",4))offset=0;return 0x806101FE;
	if ((mp->sys[3] = getPMFversion (addr))<0){offset=0;return 0x80610002;}
	if (((*offset = (unsigned)read32 ((unsigned char*) (addr + 8))) & 0x07FF)){offset=0;return 0x806101FE;}
	return 0;
}
int mpegQueryStreamSize (const void* addr, unsigned* stream_size){
	*stream_size = read32((unsigned char *)addr+12);
	if(*stream_size & 0x7FF){
		*stream_size = 0;
		return 0x806101FE;
	}
	return 0;
}
int videocodecOpen (int*arg1){
	int ret = sceVideocodecOpen (pVideoCodecStruct, 0);
	*arg1 = pVideoCodecStruct[6];
	return ret;
}
int initVideoCodec (){
	int ret,tmp;
	pVideoCodecStruct = videoCodecStruct;
	memset (pVideoCodecStruct, 0, 0x60);
/*
	*(0x7840) = 0;//0xA340 VSH offset
	*(0x7844) = 0;//0xA344
	*(0x7848) = 0;//0xA348
	*(0x784C) = 0;//0xA34C
	*(0x7850) = 0;//0xA350
	*(0x7854) = 0;//0xA354
	*(0x7858) = 0;//0xA358
	*(0x785C) = 0;//0xA35C
	*(0x7860) = 0;//0xA360
	*(0x7864) = 0;//0xA364
	pVideoCodecStruct[4] = 0x7840;//0xA340
	*(0x7798) = pVideoCodecStruct[4];//0xA284
*/
	if((ret=videocodecOpen(&tmp)))return ret;
	if((ret=sceVideocodecGetEDRAM(pVideoCodecStruct, 0))){
		pVideoCodecStruct[5] = 0;
		return ret;
	}
	return ret;
}
int AudioNeededMem;
int audiocodecCheckNeedMem (int*arg1, int arg2, int*arg3){//!
	int ret = sceAudiocodecCheckNeedMem (pAudioCodecStruct, 0x00001000);
	*arg1 = pAudioCodecStruct[4];
	return ret;
}
int initAudioCodec (int arg1){
	pAudioCodecStruct = audioCodecStruct;
	memset (audioCodecStruct, 0, 0x6C);
	int ret,tmp;
	if((ret=audiocodecCheckNeedMem (&tmp, arg1, &AudioNeededMem)))return ret;
	if((ret=sceAudiocodecGetEDRAM (pAudioCodecStruct, 0x00001000)))return ret;
	pAudioCodecStruct[3] = 0;
	return 0;
}
int mpegInit (){
	if(MpegIsInit)return 0x80618005;
	MpegIsInit = 1;
	if(createSema (1, 1, "SceMpegLibmpeg", &semaLib))return 0x80618006;
	if(createSema (1, 1, "SceMpegAvc", &semaAvc))return 0x80618006;
	if(createSema (1, 1, "SceMpegAtrac", &semaAtrac))return 0x80618006;
	initAudioCodec (0);
	initVideoCodec ();
	return 0;
}
int audiocodecReleaseEDRAM(){
	return pAudioCodecStruct[3]?sceAudiocodecReleaseEDRAM(pAudioCodecStruct):0;
}
int mpegFinish(){
	if (!MpegIsInit)return	0x80618005;
	MpegIsInit = 0;
	audiocodecReleaseEDRAM();
	sceVideocodecReleaseEDRAM (pVideoCodecStruct);
	if (deleteSema(semaLib))return 0x80618006;
	if (deleteSema(semaAvc))return 0x80618006;
	if (deleteSema(semaAtrac))return 0x80618006;
	return 0;
}
int getAudioNeededMem (int*arg1){
	if (arg1)*arg1 = AudioNeededMem;
	return pAudioCodecStruct[3];
}
int mpegQueryMemSize (int arg1){
	if (arg1==1){
		int ret;
		if ((ret=getAudioNeededMem (0)))return ret;
		return audiocodecReleaseEDRAM();
	}
	return 0x00010000;
}
extern int sceVideocodecDelete(void*,int);
int mpegDelete (SceMpeg *mp){
	waitSema (mpegAvcSema);
	return sceVideocodecDelete (mp, 0);
}
int regStream (SceMpeg *mp, int iStreamType, int ch, int arg4, SceMpegStream*arg5){
	int ret;
	if ((ret=checkMpegLib (mp)))return ret;
	return 0;
}
SceMpegStream*mpegRegistStream (SceMpeg *mp, SceMpegStrType iStreamType, int ch){
	if (!checkMpegLib (mp))return 0;
	waitSema(mp->sys[411]);
	SceMpegStream*au = NULL;//checkAu (getStr (iStreamType, ch), mp->sys, 2);
	if (au-1){
		if(!regStream(mp, iStreamType, ch, iStreamType?-1:(mp->sys[8] + (ch << 11)), au))
			return au;
	}
	signalSema(mp->sys[411]);
	return 0;
}
int sceMpegQueryStreamOffset (SceMpeg *mp, const void* addr, unsigned* offset){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryStreamOffset(mp, addr, offset);
}
int sceMpegQueryStreamSize (const void* addr, unsigned* stream_size){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryStreamSize(addr, stream_size);
}
int sceMpegInit(void){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegInit();
}
int sceMpegFinish(void){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegFinish();
}
int sceMpegQueryMemSize(int iMpegMode){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryMemSize(0);
}
int sceMpegQueryMemSizeEx(int iMpegMode){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryMemSize(iMpegMode);
}
/*
int sceMpegCreate(SceMpeg * mp,unsigned char * work_area,int size,SceMpegRingbuffer *pPSRB,int iFrameWidth,int iMpegMode,void *pDDRTop){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegCreate(mp, work_area, size, pPSRB, iFrameWidth, 0, pDDRTop);
}
int sceMpegCreateEx(SceMpeg * mp,unsigned char * work_area,int size,SceMpegRingbuffer *pPSRB,int iFrameWidth,int iMpegMode,void *pDDRTop){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegCreate(mp, work_area, size, pPSRB, iFrameWidth, iMpegMode, pDDRTop);
}*/
int sceMpegDelete(SceMpeg *mp){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegDelete(mp);
}
SceMpegStream*sceMpegRegistStream(SceMpeg *mp, SceMpegStrType iStreamType, int ch){
	if(sceKernelCheckThreadStack()<0x3F0)return (SceMpegStream*)0x80618008;
	return mpegRegistStream(mp, iStreamType, ch);
}
/*
int sceMpegUnRegistStream(SceMpeg *mp, SceMpegStream *pStream){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegUnRegistStream(mp, pStream);
}
*/
SceMpegHandle mpegMallocAvcEsBuf (SceMpeg *mp){
	int i,ret;
	if ((ret=checkMpegLib (mp)))return (SceMpegHandle)ret;
	waitSema(mp->sys[411]);
	if (!(mp->sys[415] <= 0)){
		for(i=0;!((char*)mp->sys)[1664];i++){
			if (i>=mp->sys[415]){
				mp+=i;
				break;
			}
		}
		((char *) mp->sys)[1664] = 1;
	}
	signalSema(mp->sys[411]);
	return 0;
}
SceMpegHandle sceMpegMallocAvcEsBuf(SceMpeg *mp){
	if(sceKernelCheckThreadStack()<0x3F0)return (SceMpegHandle)0x80618008;
	return mpegMallocAvcEsBuf(mp);
}
int mpegFreeAvcEsBuf (SceMpeg *mp, SceMpegHandle tHandle){
	int ret;
	if ((ret=checkMpegLib (mp)))return ret;
	waitSema(mp->sys[411]);
	if (tHandle <= 0)return 0x806101FE;
	if (mp->sys[415]<(int)tHandle)return 0x806101FE;
	//(char *)(mp->sys+tHandle)[1663] = 0;
	signalSema(mp->sys[411]);
	return 0;
}
int sceMpegFreeAvcEsBuf(SceMpeg *mp, SceMpegHandle tHandle){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegFreeAvcEsBuf(mp, tHandle);
}
int mpegQueryAtracEsSize (SceMpeg *mp, int *iEsSize, int *iOutSize){
	int ret;
	if((ret=checkMpegLib (mp)))return ret;
#ifdef VSH
	if(mp->sys[414] == 3){
		*iEsSize = 0x00001040;
		*iOutSize = 0x00008000;
	}else
#endif	
	{
		*iEsSize = 0x00000840;
		*iOutSize = 0x00002000;
	}
	return 0;
}
int sceMpegQueryAtracEsSize(SceMpeg *mp, int *iEsSize, int *iOutSize){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryAtracEsSize(mp, iEsSize, iOutSize);
}
int mpegQueryPcmEsSize (SceMpeg *mp, int *iEsSize, int *iOutSize){
	int ret;
	if((ret=checkMpegLib(mp)))return ret;
	*iEsSize = 0x00000140;
	*iOutSize = 0x00000140;
	return 0;
}
int sceMpegQueryPcmEsSize(SceMpeg *mp, int *iEsSize, int *iOutSize){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryPcmEsSize(mp, iEsSize, iOutSize);
}
int mpegInitAu (SceMpeg *mp,SceMpegHandle hEsBuf,SceMpegAu *pAu){
	int ret;
	if((ret=checkMpegLib(mp)))return ret;
	pAu->pEsBuf = hEsBuf;
	pAu->iEsSize = 0;
	return 0;
}
int sceMpegInitAu(SceMpeg *mp,SceMpegHandle hEsBuf,SceMpegAu *pAu){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegInitAu(mp, hEsBuf, pAu);
}
int mpegChangeGetAuMode(SceMpeg *mp,SceMpegStream *pStream,SceMpegAuMode iAuMode){
	int ret;
	if ((ret=checkMpegLib (mp)))return ret;
	waitSema(mp->sys[411]);
	if (checkAu (pStream, mp->sys, 1) == (void*)-1 || (iAuMode>1)){
		signalSema(mp->sys[411]);
		return 0x806101FE;
	}
	if (iAuMode==0)pStream->m_iGetAuMode &= -2;
	if (iAuMode==1)pStream->m_iGetAuMode |= 1;
	signalSema(mp->sys[411]);
	return 0;
}
int sceMpegChangeGetAuMode(SceMpeg *mp,SceMpegStream *pStream,SceMpegAuMode iAuMode){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegChangeGetAuMode(mp, pStream, iAuMode);
}
int mpegChangeGetAvcAuMode (SceMpeg *mp,SceMpegStream *pStream,SceMpegAuMode iAuMode){
	int ret;
	if((ret=checkMpegLib (mp)))return ret;
	waitSema(mp->sys[411]);
	do{
		if (checkAu (pStream, mp->sys, 1) == (void*)-1){ret=0x806101FE;break;}
		if (pStream->m_pRAPICtrlStream == (void*)-1){ret=0x806101FE;break;}
		if (iAuMode==0)pStream->m_iGetAuMode &= -3;
		if (iAuMode==2)pStream->m_iGetAuMode |= 2;
		else ret=0x806101FE;
	}while(0);
	signalSema(mp->sys[411]);
	return ret;
}
int sceMpegChangeGetAvcAuMode(SceMpeg *mp,SceMpegStream *pStream,SceMpegAuMode iAuMode){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegChangeGetAvcAuMode(mp, pStream, iAuMode);
}
/*
int sceMpegNextAvcRpAu(int arg1, int arg2){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegNextAvcRpAu(arg1, arg2);
}
int sceMpegGetAvcAu(int arg1, int arg2, int arg3, int arg4){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetAvcAu(arg1, arg2, arg3, arg4);
}
int sceMpegGetPcmAu(SceMpeg *mp,SceMpegStream *pStream,SceMpegAu *pAu,int *iAttr){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetPcmAu(mp, pStream, pAu, iAttr);
}
int sceMpegGetAtracAu(SceMpeg *mp,SceMpegStream *pStream,SceMpegAu *pAu,void **pAtracBody){
	if(sceKernelCheckThreadStack()<0x3R0)return 0x80618008;
	return mpegGetAtracAu(arg1, arg2, arg3, arg4);
}
*/
void flushStream (int arg1, int*arg2, int arg3){//!
}
int mpegFlushStream (SceMpeg *mp,SceMpegStream *pStream){
	int ret,*au,*str;
	if ((ret = checkMpegLib (mp)))return ret;
	waitSema(mp->sys[411]);
	if ((au = checkAu ((void*)pStream->qStreamId,	mp->sys, 1)) == (void*)-1){
		signalSema (mp->sys[411]);
		return 0x806101FE;
	}
	if (au[2] != -1){
		au[3] = 0;
		au[0] = -1;
		au[1] = -1;
		if ((str=pStream->m_pRAPICtrlStream) != (void*)-1){
			str[3] = 0;
			str[1] = -1;
			str[0] = -1;
		}
	}
	int tmp[2];
	int* id = (int*)(tmp[0] << 3) + 0x00007594;//0x00009FCC
	flushStream (id[1], &tmp[1] ,pStream->qStreamId);
	pStream->m_iAuNum = 0x7FFF;
	pStream->m_iPesPacketForwardSize = id[1];
	pStream->m_iPesPacketForwardFlag = 1;
	pStream->m_iPesPacketNum = 0;
	pStream->m_iBoundarySize = id[0];
	pStream->m_iAuSizeOfProceed = 0;
	pStream->m_iGetAuMode &= -5;
	pStream->m_iPayloadHeaderRemainderFlag = 0;
	pStream->m_iPayloadHeaderRemainderSize = 0;
	pStream->unk64 = 0;
	return signalSema(mp->sys[411]);
}
int sceMpegFlushStream(SceMpeg *mp,SceMpegStream *pStream){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegFlushStream(mp, pStream);
}
int flushStr(SceMpeg*mp,int arg2){//!
	return 0;
}
int mpegFlushAllStream(SceMpeg *mp){
  int ret,i;
  if((ret=checkMpegLib(mp)))return 0;
	for(i = 0;i<0x70;i++) {
		int str =((int*)mp->sys[i])[2];
		if(str!=-1 && (ret=flushStr(mp,str)))return ret;
	}
  return i;
}
int sceMpegFlushAllStream(SceMpeg *mp){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegFlushAllStream(mp);
}
/*
int avcDecode (SceMpeg*mp, SceMpegAu* au, int iFrameWidth, void* pBuffer, int* pics){
	int ret;
	if((ret=checkMpegLib(mp)))return ret;//0x08A57200
	int* codec = mp->sys[419];//0x8A5788C
	codec[9] = (getAuSample (mp->sys,au.iEsBuffer) & 0x0FFFFFFF);
	codec[10]=au.iAuSize;
	ret = videocodecDecode(codec);
	au.iAuSize = 0;
	Mp4AvcInfoStruct*info = mp->sys[420];//0x8A57890
	Mp4AvcYuvStruct*yuv = mp->sys[421];//0x8A57894
	if (ret)return ret;
	*pics = info[8];
	if (mp->sys[414]<7)return ret;//0?
	if (*pics<0)return ret;
	for(int i=0;;i++) {
		pBuffer += 4;
		if (!*pBuffer)return 0x806101FE;
		yuv += 0x2C;
		Mp4AvcCscStruct csc={info->height>>4,info->width>>4,0,0,yuv[0],yuv[1],yuv[2],yuv[3],yuv[4],yuv[5],yuv[6],yuv[7]};
		if((ret=sceMpegBaseCscAvc(*pBuffer, 0, iFrameWidth,&csc)))return ret;
		if(i >= *pics)return ret;
	}
	return ret;
}
int sceMpegAvcDecode(SceMpeg *mp,SceMpegAu *pAu,int iFrameWidth,unsigned char *pRGBA[],int *iNum){
	if((sceKernelCheckThreadStack()<0x3E0))return 0x80618008;
	return avcDecode(mp, pAu, iFrameWidth, pRGBA, iNum);
}
*/
int getCodec (SceMpeg *mp, unsigned long** codec){
	int ret;
	if ((ret = checkMpegLib (mp)))return ret;
	*codec=mp->sys[419];
	return 0;
}
int avcDecodeDetail (SceMpeg *mp,SceMpegAvcDecodeDetailInfo *pDetail){
	int ret;
	if ((ret=checkMpegLib (mp)))return ret;
/*
	VCodec*codec;
	if (ret=getCodec (mp,&codec))return ret;
	if (!0<codec[4][8]))return 0x806101FE;
	pDetail->iDecodeResult = codec[2];
	pDetail->uiRecoveryPoint = codec->yuv[8];
	pDetail->uiHorizontalSize = codec->info[2];
	pDetail->uiVerticalSize = codec->info[3];
	pDetail->uiFrameCropLeftOffset = codec->info[4];
	pDetail->uiFrameCropRightOffset = codec->info[5];
	pDetail->uiFrameCropTopOffset = codec->info[6];
	pDetail->uiFrameCropBottomOffset = codec->info[7];
	pDetail->uiDisplayFrameNum = codec->info[8];*/
	return 0;	
}
int sceMpegAvcDecodeDetail(SceMpeg *mp,SceMpegAvcDecodeDetailInfo *pDetail){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeDetail(mp, pDetail);
}
/*
int sceMpegAvcDecodeMode(SceMpeg *mp, int mode){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008
	return avcDecodeMode(mp, mode);
}
int sceMpegAvcDecodeStop(SceMpeg *mp,int iFrameWidth,unsigned char *pRGBA[],int *iNum){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008
	return avcDecodeStop(mp, iFrameWidth, pRGBA, iNum);
}
int sceMpegAvcDecodeFlush(SceMpeg *mp){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeFlush(mp);
}
int sceMpegAvcQueryYCbCrSize(SceMpeg *mp,int iYCbCrMode,int iYCbCrWidth,int iYCbCrHeight,int *iAvcYCbCrSize){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcQueryYCbCrSize(mp, iYCbCrMode, iYCbCrWidth, iYCbCrHeight, iAvcYCbCrSize);
}
int sceMpegAvcInitYCbCr(SceMpeg *mp,int iYCbCrMode,int iYCbCrWidth,int iYCbCrHeight,unsigned char *pAvcYCbCr){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcInitYCbCr(mp, iYCbCrMode, iYCbCrWidth, iYCbCrHeight, pAvcYCbCr);
}
int sceMpegAvcDecodeYCbCr(SceMpeg *mp,SceMpegAu *pAu,unsigned char *pAvcYCbCr[],int *iNum){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcDecodeYCbCr(mp, pAu, pAvcYCbCr, iNum);
}
int sceMpegAvcDecodeStopYCbCr(SceMpeg *mp,unsigned char *pAvcYCbCr[],int *iNum){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeStopYCbCr(mp, pAvcYCbCr, iNum);
}
int sceMpegAvcCsc(int arg1, int arg2, int arg3, int arg4, int arg5){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcCsc(arg1, arg2, arg3, arg4, arg5);
}
int sceMpeg_0558B075(int arg1, int arg2, int arg3){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegYCbCrCopy(arg1, arg2, arg3);
}
*/
int audiocodecSetup (unsigned long*codec, int arg2, int arg3, void*arg4, void* arg5){
	return 0;
}
int audiocodecDecode (unsigned long*arg1){
	waitSema (mpegAtracSema);
	int ret=sceAudiocodecDecode (arg1, 0x00001000);
	signalSema (mpegAtracSema);
	return ret;
}
int mpegAtracDecode(SceMpeg *mp,SceMpegAu *pAu,unsigned char *pPcmData,int iInitFlag){
	int ret;
	if((ret=checkMpegLib (mp)))return ret;
#ifdef VSH
	unsigned long*codec = (unsigned long*)mp->sys[440];
#else
	unsigned long*codec = (unsigned long*)mp->sys[434];
#endif
	if(iInitFlag == 1){
#ifdef VSH
		int mem = mp->sys[439];
		int len = mp->sys[438];
#else
		int mem = mp->sys[433];
		int len = mp->sys[432];
#endif
		if((ret = audiocodecSetup (codec, len, mem,&pAu[4]+2,&pAu[4]+4)))return ret;
		codec[6] = ((int*)pAu)[4];
		codec[8] = (int)pPcmData;
		return audiocodecDecode (codec);
	}
	return 0;
}
int sceMpegAtracDecode(SceMpeg *mp,SceMpegAu *pAu,unsigned char *pPcmData,int iInitFlag){
	if(sceKernelCheckThreadStack()<0x000003E0)return 0x80618008;
	if(mp->sys[414] != 1)return 0x806101FE;
	return mpegAtracDecode(mp, pAu, pPcmData, iInitFlag);
}
int queryUserdataEsSize (SceMpeg *mp, int*arg2, int*arg3){
	int ret;
	if ((ret=checkMpegLib (mp)))return ret;
	*arg2 = 0x000A0000;
	*arg3 = 0x000A0000;
	return 0;
}
int sceMpegQueryUserdataEsSize(SceMpeg *mp, int*arg2, int*arg3){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return queryUserdataEsSize(mp, arg2, arg3);
}
int queryUserdataEsSize2 (SceMpeg *mp, int arg2, int arg3, int arg4, int arg5){//!
	return 0;
}
int mpegQueryUserdataEsSize2 (SceMpeg *mp, int arg2, int arg3, int arg4){
	return queryUserdataEsSize2 (mp, arg2, 3, arg3, arg4);
}
int sceMpegQueryUserdataEsSize2(SceMpeg *mp, int arg2, int arg3, int arg4){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegQueryUserdataEsSize2(mp, arg2, arg3, arg4);
}
/*
int sceMpegGetAvcEsAu(int arg1, int arg2, int arg3, int arg4){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetAvcEsAu(arg1, arg2, arg3, arg4);
}
int sceMpegGetAvcNalAu(int arg1, int arg2, int arg3){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegGetAvcNalAu(arg1, arg2, arg3);
}
*/
int mpegRingbufferQueryMemSize (int arg1){
	return ((arg1<<11) + (arg1*104));
}
int sceMpegRingbufferQueryMemSize(int iPackNum){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferQueryMemSize(iPackNum);
}
int hi(int a){
	return a;
}
int mpegRingbufferQueryPackNum (SceMpegRingbuffer *pRingbuffer){
	return 0;//(hi (pRingbuffer * 0xF3A0D52D)) >> 11;
}
int sceMpegRingbufferQueryPackNum(SceMpegRingbuffer *pRingbuffer){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferQueryPackNum(pRingbuffer);
}
int mpegRingbufferConstruct(SceMpegRingbuffer *pRingbuffer,int iPackNum,void *pBuf,int iSize,SceMpegRBCallback callback,void *pCallbackData){
	if (iSize>=((iPackNum<<12)+(iPackNum*0x68)))return 0x80610022;
	waitSema(semaLib);
	pRingbuffer->m_iBufsize = iPackNum;
	pRingbuffer->m_iRpos = 0;
	pRingbuffer->m_iWpos = 0;
	pRingbuffer->m_iInlen = 0;
	pRingbuffer->m_iTypeSize = 0;
	pRingbuffer->m_pBuf = pBuf;
	pRingbuffer->callback = callback;
	pRingbuffer->m_CallbackData = pCallbackData;
	pRingbuffer->pPack = (pBuf + (iPackNum<<12));
	pRingbuffer->iSemaRB = 0;
	pRingbuffer->mp = 0;//gp;
	signalSema(semaLib);
	return 0;
}
int sceMpegRingbufferConstruct(SceMpegRingbuffer *pRingbuffer,int iPackNum,void *pBuf,int iSize,SceMpegRBCallback callback,void *pCallbackData){
	if(sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegRingbufferConstruct(pRingbuffer, iPackNum, pBuf, iSize, callback, pCallbackData);
}
int mpegRingbufferDestruct(){
	return 0;
}
int sceMpegRingbufferDestruct(SceMpegRingbuffer *pRingbuffer){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferDestruct();
}
/*
int sceMpegRingbufferPut(SceMpegRingbuffer *pRB, int iPackNum, int iAvailable){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferPut(pRB, iPackNum, iAvailable);
}
int sceMpegRingbufferAvailableSize(SceMpegRingbuffer* pRB){
	if(sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferAvailableSize(pRB);
}
*/
int module_start(int args,char*argp){
	return 0;
}
int module_stop(){
	return 0;
}