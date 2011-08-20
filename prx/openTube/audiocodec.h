/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudiocodec.h - Prototypes for the sceAudiocodec library.
 *
 * Copyright (c) 2006 hitchhikr
 *
 * $Id: pspaudiocodec.h 2430 2008-08-28 12:04:04Z Raphael $
 */

#ifndef AUDIOCODEC_H

#define PSP_CODEC_AT3PLUS	(0x00001000)
#define PSP_CODEC_AT3		(0x00001001)
#define PSP_CODEC_MP3		(0x00001002)
#define PSP_CODEC_AAC		(0x00001003)
typedef struct{
	int checkSize;
	int unk1;
	u32*Dcache;
	u32 DcacheLen;
	u32 needMem;
	int unk4;
	u32*src;
	u32 srcLen;
	u32*dst;
	u32 dstLen;//filled by sceAudiocodecDecode : ch*bps*SampleLen
	u32 freq;
	int unkA[15];//3rd entry moded if mp3
	u32 EDRAM;
	int unkB[38];
}AuCodec;

int sceAudiocodecCheckNeedMem(AuCodec *Buffer, int Type);
int sceAudiocodecInit(AuCodec *Buffer, int Type);
int sceAudiocodecDecode(AuCodec *Buffer, int Type);
int sceAudiocodecGetEDRAM(AuCodec *Buffer, int Type);
int sceAudiocodecReleaseEDRAM(AuCodec *Buffer);
#define AUDIOCODEC_H
#endif
