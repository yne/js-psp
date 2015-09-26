#include <pspsdk.h>
#include "avcodec.h"

int sceAudiocodecCheckNeedMem (int arg1, int arg2){
	if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if ((((arg2 + 0xFFFFF000) >= 0x6)))return 0x80000004;
	_k1 = k1;
	k1 = k1 >> 16;
	if (((((arg1 + 0x68) | arg1) & -(k1&0x18)) < 0))return;
	arg1[0] = 0x5100601;
	ret = sceMeAudio_driver_BB9821AC (arg2, arg1);
	ret = ((0x4444)[ret<0?0:ret]);
	k1 = _k1;
	return 0;
}
int sceAudiocodecInit (int arg1, int arg2){
	if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return 0x80000004;
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x68) | arg1) & (0 - k1&0x18)) < 0)return 0x80000004;
	if (((0 - k1&0x18) & (((arg1[3] + arg1[4]) | arg1[3]) | arg1[4])) < 0)return 0x80000004;
	if (arg2 == 0x1002)
		arg1[14] = 0x270F;
	if (((0x220202 >> ((arg1[3] >> 27) & 0x1F)) & 1))
		sceKernelDcacheWritebackInvalidateRange (arg1[3], arg1[4]);
	arg1[0] = 0x5100601;
	ret = sceMeAudio_driver_F5F87C12 (arg2, arg1);
	if (ret)return ((int *) ((((((ret < 0xFFFFFFFC))) ? 0 : ret) << 2) + 0x4444))[4];
	k1 = _k1;
	return 0;
}
int sceAudiocodec_3DD7EE1A (int arg1, int arg2){
	if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return 0x80000004;
	var7 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x68) | arg1) & (0 - k1&0x18)) < 0)return 0x80000004;
	if (((0 - k1&0x18) & (((arg1[3] + arg1[4]) | arg1[3]) | arg1[4]))<0)return 0x80000004;
	if (arg2 == 0x1002)
		arg1[14] = 0x270F;
	if (((0x220202 >> ((arg1[3] >> 27) & 0x1F)) & 1))
		sceKernelDcacheWritebackInvalidateRange (arg1[3], arg1[4]);
	arg1[0] = 0x5100601;
	ret = sceMeAudio_driver_24AFB7E1 (arg2, arg1);
	if (ret)
		return ((int *) ((((((var15 < 0xFFFFFFFC))) ? 0 : var15) << 2) + 0x4444))[4];
	k1 = var7;
}
int sceAudiocodecDecode (int arg1, int arg2){
	if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return 0x80000004;
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x68) | arg1) & (0 - k1&0x18)) < 0)return 0x80000004;
	if (((0 - k1&0x18) & (((arg1[3] + arg1[4]) | arg1[3]) | arg1[4]))<0)return 0x80000004;
	if ((((arg1[6] + 0x10000) | arg1[6]) & (0 - k1 & 0x18)) < 0)return 0x80000004;
	if ((((arg1[8] + 0x10000) | arg1[8]) & (0 - k1 & 0x18)) >= 0)
	if (arg2 == 0x1002)len = arg1[10];
	else if (arg2 == 0x1004)len = arg1[10];
	else if(len=audiocodecGetInfo (arg1, arg2)<0)return len;
	sceKernelDcacheWritebackRange (arg1[6], len);
	if (len=getSizeofSample (arg1, arg2)<0)return len;
	sceKernelDcacheWritebackInvalidateRange (arg1[8], len);
	ret = sceMeAudio_driver_310C9CDA (arg2, arg1);
	if (ret)
		return = ((int *) ((((((var31 < 0xFFFFFFFC))) ? 0 : var31) << 2) + 0x4444))[4];
	k1 = _k1;
	return 0;
}
int sceAudiocodecGetInfo (int arg1, int arg2){
	var1 = arg1;
	var2 = 0x807F0002;
	sp[0] = s0;
	if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return;
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x68) | arg1) & (0 - k1&0x18)) < 0)return;
	if (((0 -  k1 & 0x18) & (((arg1[3] + arg1[4]) | arg1[3]) | arg1[4])) < 0)return;
	if (((((arg2 ^ 0x1002) < 1)) | (((arg2 ^ 0x1004) < 1)))==0)
		if ((((0 - k1&0x18) & (((arg1[6] + arg1[10]) | arg1[6]) | arg1[10])) < 0))return 0x80000023;
	arg1[0] = 0x5100601;
	ret = sceMeAudio_driver_7C8ADD5E (arg2,(arg2==0x1000)4:2);
	if (ret)
		return ((int *) ((((((ret < 0xFFFFFFFC))) ? 0 : ret) << 2) + 0x4444))[4];
	k1 = _k1;
	return 0;
}
int sceAudiocodec_59176A0F (int arg1, int arg2, int arg3){
  if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return 0x80000004;
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x68) | arg1) & (0 - k1&0x18)) < 0)return 0x80000004;
	if ((((arg3 + 4) | arg3) & (0 - k1 & 0x18)) < 0)return;
	len = getSizeofSample (arg1, arg2);
	if (len>=0)arg3[0] = len;
	return 0;
}
int sceAudiocodecGetEDRAM (int arg1, int arg2){
  if (!((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))return 0x807F0002;
	if (!(((arg2 + 0xFFFFF000) < 0x6)))return 0x80000004;
	var7 = k1;
	k1 = k1 >> 16;
	var8 = k1 & 0x18;
	if ((((arg1 + 0x6C) | arg1) & (0 - var8)) < 0)return;
	arg1[26] = sceMeMemory_driver_3D0D8BAF (((arg1[4] + 0x3F) | 0x3F));
	if (arg1[26]){
		if ((((0x3FFFFF < ((arg1[26] >> 0) & 0x1FFFFFFF))) ^ 1))return;
		arg1[3] = (((arg1[26] + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F));
	}
	sceMeMemory_driver_F9318AF4 (arg1[26]);
	arg1[26] = 0;
	arg1[3] = 0;
	return var3 = 0x807F0003;//??
}
int sceAudiocodecReleaseEDRAM (int arg1){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x6C) | arg1) & (0 - k1 & 0x18)) < 0)return 0x80000023; 
	if (((0 - k1 & 0x18) & (((arg1[3] + arg1[4]) | arg1[3]) | arg1[4]))<0)return;
	if (!arg1[26])return 0x807F0004;
	if (((((0x3FFFFF < ((arg1[26] >> 0) & 0x1FFFFFFF))) ^ 1)){
		sceMeMemory_driver_F9318AF4 (arg1[26]);
		arg1[26] = 0;
		arg1[3] = 0;
	}
	k1 = _k1;
	return 0;
}
int audiocodecGetInfo (int arg1, int arg2){
	if (arg2 >= 0x1006)return 0x80000004;
	switch (((int *)0x446C)[arg2-0x1000]) {
	case 0:
		var5 = arg1[12];
		var2 = 0x100A;
		if (!(var5 != 0))
		{
			var6 = arg1[16];
			var2 = var6 + 2;
		}
		goto label19;
	case 1:
		var8 = arg1[12];
		var2 = (var8 << 1) + 1;
		goto label19;
	case 2:
		if (arg1[14] == 0x270F)
			if((ret = sceAudiocodecGetInfo (arg1, 0x1002))<0)return ret;
		return getSampleLen (arg1[14], arg1[15], arg1[17], arg1[18], (arg1 + 0x28));
	case 3:
		return ((unsigned char *) arg1)[44] ? 0x609 : 0x600;
	case 4:
		return getSampleLen (arg1[12], arg1[13], arg1[15], arg1[16], (arg1 + 0x28));
	case 5:
		return = 0x420D;
	}
	return 0;
}
int getSizeofSample (int arg1, int arg2){
	if (arg2 >= 0x1006)return 0x1000;
	switch (((int *)0x4484)[arg2-0x1000]){
	case 0:
		if ((arg1[14] == 1)&&(arg1[18] != arg1[14]))return 0x2000;
		return arg1[18] << 0xC;
	case 1:
		return 0x1000;
	case 2:
		if (arg1[14] == 0x270F)
			if (ret=sceAudiocodecGetInfo (arg1, 0x1002)<0)return ret;
		return arg1[14]^1 ? 0x900 : 0x1200;
	case 3:
		return ((unsigned char *) arg1)[45] ? 0x2000 : 0x1000;
	case 4:
		return 0x1200;
	case 5:
		return 0x2F00;
	}
	return 0x1000;
}
int getSampleLen (int arg1, int arg2, int arg3, int arg4, int arg5){
	var3 = 0;
	if (((arg1<3) & ((!arg3) >> 0x1F))&&(arg3 < 0xF))
		var3 = ((unsigned char *) ((((arg1&1*16) - arg1&1) + 0x449C) + arg3))[0]<<3;
	var6 = 0;
	if (((arg1<3) & ((!arg4) >> 0x1F))&&(arg4 < 4))
		var6 = ((unsigned short *) ((((arg1*4)+arg4)*2) + 0x44BC))[0];
	var7 = 0x7C9;
	if ((((0 < var3)) & ((0 < var6)))){
		if (arg2 < 3){
			var8 = ((((var3 << 3) + var3) << 4) / var6) + 1;
			var7 = !(((var8 < 0x7CA))) ? 0x7C9 : var8;
		}
		var9 = var7 >> 1;
	}else	var9 = 0x7C9 >> 1;
	*arg5 = ((arg1 ^ 1)) ? var9 : var7;
	return *arg5;
}
int sceVideocodecGetEDRAM (int arg1){
	_k1=k1;k1=k1>>16;_k1=k1&0x18;
	if (arg1[23])return 0x806201FE;
	if (!(arg1[23]=sceMeMemory_driver_198F17FD (((arg1[6]+0x3F)|0x3F), 1)))return 0x806201FE;
	arg1[5] = (((arg1[23]+0x3F) & ~0x3F));
	k1=_k1;
	return 0;
}
int sceVideocodecReleaseEDRAM (int arg1){
	_k1 = k1;k1 = k1 >> 16;_k1 = k1 & 0x18;
	if (!arg1[23])return 0x806201FE;
	sceMeMemory_driver_F9318AF4 (arg1[23]);
	arg1[5] = 0;
	arg1[23] = 0;
	k1 = _k1;
}
int sceVideocodecOpen (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (ret=checkAlign (arg1, arg2))return ret;
	arg1[0] = 0x5100601;
	sceKernelDcacheWritebackInvalidateRange (arg1[4],arg2?0x100:0x28);
	if (ret=sceMeVideo_driver_F24820D4 (arg2, arg1))return ret;
	sceMePower_driver_52E7CD99(0);
	sceMePower_driver_2ECCB138(0);
	ret = ((0x4458)[ret<0?0:ret]);
	k1 = _k1;
}
int sceVideocodecInit (int arg1, int arg2){
	_k1 = k1;
	k1 = k1 >> 16;
	if(checkArgMem (arg1, arg2))return;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], ((arg2) ? 0x100 : 0x28));
	if (!(((0x3FFFFF < (arg1[5] & 0x1FFFFFFF))) ^ 1))
		sceKernelDcacheWritebackInvalidateRange (arg1[5], arg1[6]);
	sceKernelDcacheWritebackInvalidateRange (arg1[7], arg1[8]);
	ret = sceMeVideo_driver_93EED793 (arg2, arg1);
	if (((0x4458)[ret<0?0:ret])>=0)sceKernelSetEventFlag (SemaMpegBaseCSC, 1);
	k1 = _k1;
	return;
}
int sceVideocodecSetMemory (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (checkAlign (arg1, arg2))return;
	if (arg2)return;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x28);
	ret = sceMeVideo_driver_994BBA92 (0, 1, arg1);
	return ((0x4458)[ret<0?0:ret]);
	k1 = _k1;
	return;
}
int sceVideocodecScanHeader (int arg1, int arg2){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg1 + 0x60) | arg1) & (0 - k1&0x18)) < 0)return;
	if ((((arg1[4] + 0x100) | arg1[4]) & (0 - k1&0x18)) < 0)return;
	if (((0 - k1&0x18) & (((arg1[9] + arg1[10]) | arg1[9]) | arg1[10])) < 0)return;
	if (arg2>=3)return;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x100);
	if (!((0x3FFFFF < (arg1[9] & 0x1FFFFFFF)))^1)
		sceKernelDcacheWritebackInvalidateRange (arg1[9], arg1[10]);
	ret = sceMeVideo_driver_994BBA92 (arg2, 2, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecGetVersion (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (!((((arg1 + 0x60) | arg1) & -(k1&0x18)) < 0))return;
	if (((arg2 < 3)))return;
	ret = sceMeVideo_driver_994BBA92 (arg2, 3, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecGetSEI (int arg1, int arg2){
	_k1 = k1;
	k1 = k1 >> 16;
	if (arg2)return 0x806201FE;
	if (ret=checkAlign (arg1, arg2))return ret;
	if((((-(k1&0x18) & (((arg1[20] + 0xA4) | arg1[20]) | 0xA4))) >> 0x1F))return 0x80000023;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x28);
	sceKernelDcacheInvalidateRange (arg1[20], 0xC0);
	ret = sceMeVideo_driver_994BBA92 (0, 5, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecGetFrameCrop (int arg1, int arg2){
	_k1 = k1;
	k1 = k1 >> 16;
	if (arg2)return 0x806201FE;
	if (ret=checkAlign (arg1, arg2))return ret;
	if((((-(k1&0x18) & (((arg1[21] + 16) | arg1[21]) | 16))) >> 0x1F))return 0x80000023;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x28);
	sceKernelDcacheInvalidateRange (arg1[21], 0x40);
	ret = sceMeVideo_driver_994BBA92 (0, 0x6, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodec_893B32B1 (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (arg2)return 0x806201FE;
	if (ret=checkAlign (arg1, arg2))return var6;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x28);
	ret = sceMeVideo_driver_994BBA92 (0, 7, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecDecode (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (ret=checkStruct (arg1, arg2))return ret;
	invalidateDecStruct (arg1, arg2);
	invalidateDecStruct2(arg1, arg2);
	ret = sceMeVideo_driver_2C38DB84 (arg2, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecStop (int arg1, int arg2){
	_k1 = k1;k1 >>= 16;
	if ((((arg1 + 0x60) | arg1) & (0 - var2)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & arg1[3]) < 0)return 0x80000023;
	if (arg2 < 3)return 0x806201FE;
	if (((((arg1[4] + arg2?0x100:0x28) | arg1[4]) & (0 - k1 & 0x18)) < 0))return 0x80000023;
	if (!arg2)return 0;
	if (((0 - k1 & 0x18) & (((arg1[11] + (arg1[15] * 0x2C)) | arg1[11]) | (arg1[15] * 0x2C))) < 0)return 0x80000023;
	if ((((arg1[12] + 0x64) | arg1[12]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if (arg1[14]&&(((0 - k1 & 0x18) & (((arg1[14] + (arg1[15]*0x148)) | arg1[14]) | (arg1[15]*0x148))) < 0))return 0x80000023;

	if(!arg2)sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x28);
	if ((((0x3FFFFF >= (arg1[5] & 0x1FFFFFFF))) ^ 1))
		sceKernelDcacheWritebackInvalidateRange (arg1[5], arg1[6]);
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x100);

	invalidateDecStruct2 (arg1, arg2);
	ret = sceMeVideo_driver_6401013A (arg2, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int sceVideocodecDelete (int arg1, int arg2){
	_k1 = k1;k1 = k1 >> 16;
	if (checkAlign (arg1, arg2) < 0)return;
	sceKernelDcacheWritebackInvalidateRange (arg1[4], (arg2 ? 0x100 : 0x28));
	sceKernelPollEventFlag (SemaMpegBaseCSC, 1, 0x21, 0);
	ret = sceMeVideo_driver_2DAAC3A9 (arg2, arg1);
	k1 = _k1;
	return ((0x4458)[ret<0?0:ret]);
}
int checkAlign (int arg1, int arg2){
	if (((((arg1 + 0x60) | arg1) & -k1&0x18) < 0))return 0x80000023;
	var3 = arg2?0x100:0x28;
	if (arg2>=3)return 0x806201FE;
	return (((!((0 - k1&0x18) & (((arg1[4] + var3) | arg1[4]) | var3))) >> 0x1F)) ? 0 : 0x80000023;
}
int checkArgMem (int arg1, int arg2){
	_k1 = k1 & 0x18;
	if ((((arg1 + 0x60) | arg1) & (0 - arg2)) < 0)return 0x80000023;
	if (((0 - k1&0x18) & (((arg1[5] + arg1[6]) | arg1[5]) | arg1[6])) < 0)return 0x80000023;
	if (((0 - k1&0x18) & (((arg1[7] + arg1[8]) | arg1[7]) | arg1[8])) < 0)return 0x80000023;
	if((arg2 >= 3))return 0x806201FE;
	var10 = arg2?0x100:0x28;
	return (((((0 - k1&0x18) & (((arg1[4] + var10) | arg1[4]) | var10))) >> 0x1F)) ? 0x80000023 : 0;
}
int checkStruct (int arg1, int arg2){
//TBD
}
void invalidateDecStruct (int arg1, int arg2){
	sceKernelDcacheWritebackInvalidateRange (arg1[4], 0x100);
	if (arg2){
		sceKernelDcacheWritebackInvalidateRange (arg1[5], arg1[6]);
		sceKernelDcacheWritebackInvalidateRange (arg1[7], arg1[8]);
	}
	sceKernelDcacheWritebackInvalidateRange (arg1[9], arg1[10]);
}
void invalidateDecStruct2 (int arg1, int arg2){
	if (arg2)return;
	sceKernelDcacheInvalidateRange (arg1[11], ((((arg1[15] * 0x2C) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F)));
	sceKernelDcacheInvalidateRange (arg1[12], 0x40);
	if (arg1[14])
		sceKernelDcacheInvalidateRange (arg1[14], ((((arg1[15] * 0x148) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F)));
	if (arg1[13] < 0)
		if (arg1[20])sceKernelDcacheInvalidateRange (arg1[20], 0xC0);
	if (arg1[13] & 0x40000000 && arg1[21])
		sceKernelDcacheInvalidateRange (arg1[21], 0x40);
}
int sceMpegBaseYCrCbCopy (int arg1, int arg2, int arg3){
	_k1 = k1;k1 = k1 >> 16;
	if ((((arg2 + 0x30) | arg2) & (0 - k1&0x18)) < 0)return 0x80000023;
	if ((((arg1 + 0x30) | arg1) & (0 - k1&0x18)) < 0)return 0x80000023;
	var20 = (((arg2[1]+16)*64)*arg2[0]);
	var22 = (((arg2[1]+ 0)*64)*arg2[0]);
	if (0xBFF4 < var20)return 0x80000104;
	if (sceKernelWaitSema (SemaMpegBaseLLI, 1, 0) < 0)return
	var28 = 0x45C0;
	__asm__ ("cache			0x18, 0($s7);" : : "=r"(0x45C0));
	if(arg3&1){
		var61 = sub_02018 (0x45C0, arg1[4], arg2[4], var20);
		var66 = sub_02018 (var61, arg1[5], arg2[5], var22);
		var71 = sub_02018 (var66, arg1[8], arg2[8], var20*2);
		var28 = sub_02018 (var71, arg1[9], arg2[9], var22*2);
	}
	if(arg3&2){
		var40 = sub_02018 (var28, arg1[6 ], arg2[6 ], var20);
		var45 = sub_02018 (var40, arg1[7 ], arg2[7 ], var22);
		var50 = sub_02018 (var45, arg1[10], arg2[10], var20*2);
		var28 = sub_02018 (var50, arg1[11], arg2[11], var22*2);
	}
	if (var28 != 0x45C0)
		ret = copyVme (var28);
	sceKernelSignalSema (SemaMpegBaseLLI, 1);
	k1 = _k1;
	return ret;
}
int sceMpegBaseYCrCbCopyVme (int arg1, int arg2, int arg3){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((((arg2 + 0x28) | arg2) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg1 + 0x28) | arg1) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	var18 = (((((arg2[1] & 0x7F) ^ 0x50)) ? (arg2[1] + 0x20) : (arg2[1] + 0x30)) * arg2[0]);
	if (!(((0xBFF4 < var18 >> 5))))return 0x80000104;
	if((ret= sceKernelWaitSema (SemaMpegBaseLLI, 1, 0))<0)return ret;
	var26 = 0x45C0;
	__asm__ ("cache			0x18, 0($s7);" : : "=r"(0x45C0));
	if (arg3 & 1){
		var53 = sub_02018 (var26, arg1[4], arg2[4], var18 >> 5);
		var58 = sub_02018 (var53, arg1[6], arg2[6], var18 >> 7);
		var26 = sub_02018 (var58, arg1[7], arg2[7], var18 >> 7);
	}
	if (arg3 & 2){
		var38 = sub_02018 (var26, arg1[5], arg1[5], var18 >> 5);
		var43 = sub_02018 (var38, arg1[8], arg1[8], var18 >> 7);
		var26 = sub_02018 (var43, arg1[9], arg1[9], var18 >> 7);
	}
	if (var26 != 0x45C0)
		ret=copyVme (var26);
	sceKernelSignalSema (SemaMpegBaseLLI, 1);
	k1 = _k1;
	return;
}
int sub_02018 (int arg1, int arg2, int arg3, int arg4){
	while (arg4){
		i = MIN(arg4,0xFFF);
		arg4-= i;
		arg1[0] = ((((k1&0x18) ? 0x40000000 : 0) & 0xE0000000) | (arg3+=i*16 & 0x1FFFFFFF));
		arg1[1] = ((((k1&0x18) ? 0x40000000 : 0) & 0xE0000000) | (arg2+=i*16 & 0x1FFFFFFF));
		arg1[2] = (arg1+=16 & 0x1FFFFFFF);
		arg1[3] = (i | 0x1909000);
	}
	return arg1;
}
int copyVme (int arg1){
	arg1[0] = 0;
	arg1[-1]|= 0x80000000;
	sceKernelDcacheWritebackInvalidateRange (0x45C0, (arg1 - 0x45C0));
	while(1){
		if ((ret=sceDmacplus_driver_24B3E74C (0x45C0))&&(ret!=0x80000021))return ret;
		if(!sceDmacplus_driver_1D65E667 (0,0))break;
	}
	return ret;
}
int sceMpegbase_driver_BEA18F91 (int arg1){
	_k1 = k1;
	k1 = k1 >> 16;
	_k1 = k1 & 0x18;
	if (((0 - var3) & arg1) < 0)return;
	if ((ret=sceKernelWaitSema (SemaMpegBaseLLI, 1, 0)) < 0)return ret;
	var10 = 0x45C0;
	__asm__ ("cache			0x18, 0($s2);" : : "=r"(0x45C0));
	var1 = arg1;
	while (1) {
		var10[0] = ((((k1 & 0x18) ? 0x40000000 : 0) & 0xE0000000) | (var1[0] & 0x1FFFFFFF));
		var10[1] = ((((k1 & 0x18) ? 0x40000000 : 0) & 0xE0000000) | (var1[1] & 0x1FFFFFFF));
		if (!(var1[3] & 0xFFF))return 0;
		var1 += 16;
		if (var1[2]){
			var10[2] = ((var10+16) & 0x1FFFFFFF);
			var10[3] = (var17 | 0xA909000);
			var10 = (var10+16);
			if ((var10+16) == 0x4C00)return 0;
		}else{
			var10[3] = ((var1[3] & 0xFFF) | 0x8A909000);
			var10[2] = 0;
			sceKernelDcacheWritebackRange (0x45C0, (var10 + (16 - 0x45C0)));
			while (1) {
				if ((ret = sceDmacplus_driver_8AA7F020 (0x45C0))&&(ret == 0x80000021))return ret;
				if(!sceDmacplus_driver_915A917C (0, 0))break;
			}
			break;
		}
	}
	sceKernelSignalSema (SemaMpegBaseLLI, 1);
	k1 = _k1;
	return 0;
}
int sceJpegInitMJpeg (){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((ret=sceKernelWaitSema (SemaJpeg, 1, 0)) < 0){k1 = _k1;return ret;}
	CodecVersion = 0x5100601;
	if ((ret=sceMeVideo_driver_93EED793 (3, &CodecVersion)) < 0)
		ret = (((((var9 < 0xFFFFFFF7)) ^ 1) & (var9 >> 0x1F))) ? 0x80650042 : ret;
	else{
		JpegFlag = 1;
		sceKernelSetEventFlag (SemaMpegBaseCSC, 2);
	}
	sceKernelSignalSema (SemaJpeg, 1);
	k1 = _k1;
	return ret;
}
int sceJpegCreateMJpeg (int arg1, int arg2){
	if (arg1 >= 0x401)return 0x80650020;
	_k1 = k1;
	k1 = k1 >> 16;
	if ((ret = sceKernelWaitSema (SemaJpeg, 1, 0)) < 0){k1 = _k1;return ret;}
	if (JpegFlag != 1){sceKernelSignalSema (SemaJpeg, 1);k1 = _k1;return 0x80650039;}
	if ((ret=sceMpegbase_driver_AC9E717E (arg1, 0x44D4)) < 0){	sceKernelSignalSema (SemaJpeg, 1);k1 = _k1;return ret;}
	JpegFlag = 2;
	*((int *) 0x4544) = arg1;
	*((int *) 0x4548) = arg2;
	sceKernelSignalSema (SemaJpeg, 1);
	k1 = _k1;
	return ret;
}
int sceJpegDeleteMJpeg (){
	_k1 = k1;
	k1 = k1 >> 16;
	if (sceKernelWaitSema (SemaJpeg, 1, 0) < 0){k1 = _k1;return;}
	if (JpegFlag != 2){sceKernelSignalSema (SemaJpeg, 1);k1 = _k1;return;}
	JpegFlag = 1;
	sceKernelSignalSema (SemaJpeg, 1);
	k1 = _k1;
	return;
}
int sceJpegFinishMJpeg (){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((ret = sceKernelWaitSema (SemaJpeg, 1, 0)) < 0){k1 = _k1;return;}
	if (JpegFlag != 1){sceKernelSignalSema (SemaJpeg, 1);k1 = _k1;return;}
	var11 = sceKernelPollEventFlag (SemaMpegBaseCSC, 2, 0x21, 0);
	CodecVersion = 0x5100601;
	if ((ret = sceMeVideo_driver_2DAAC3A9 (3, &CodecVersion)) < 0)
		ret = (((((ret < 0xFFFFFFF7)) ^ 1) & (ret >> 0x1F))) ? 0x80650043 : ret;
	else
		JpegFlag = 0;
	sceKernelSignalSema (SemaJpeg, 1);
	k1 = _k1;
	return ret;
}
int sceJpegMJpegCsc (int arg1, int arg2, int height, int width){//max:1024x720
	if ((((((width < 0x401)) ^ 1) | (((((height>>16)&0xFFF) < 0x2D1)) ^ 1))))return 0x80650020;
	if (((((height&0xFFF) < 0x1E1))return 0x80650020;
	var8 = (((height>>16) & 0x70) ^ 0x70) ? (height>>16)&0xFFF : ((height>>16)&0xFFF)+ 16;
	var9 = (var8 * (height&0xFFF));
	var10 = var9 + (var9 >> 0x1F);
	_k1 = k1;
	k1 = k1 >> 16;
	var13 = k1 & 0x18;
	if (((0 - var13) & arg2) < 0)return
	if (((0 - k1 & 0x18) & arg1) < 0)return 0x80000023;
	var15 = (var10*2 + ((var10 >> 0x1F) >> 0x1E)) >> 2;
	sp[0] = ((height&0xFFF) >> 4);
	sp[1] = (var8 >> 4);
	sp[2] = 0;
	sp[3] = 1;
	sp[4] = arg2;
	sp[5] = arg2 + 2*var10;
	sp[6] = arg2 + 4*var10;
	sp[8] = arg2 + 4*var10 + 1*var15;
	sp[7] = arg2 + 4*var10 + 2*var15;
	sp[9] = arg2 + 4*var10 + 3*var15;
	sceKernelDcacheInvalidateRange (arg1, width*(height&0xFFF)*2);
	ret = sceMpegBaseCscVme (arg1, (arg1+(width*(height&0xFFF)*2), width, sp);
	k1 = _k1;
	return ret;
}
int sceJpegDecodeMJpeg (int arg1, int arg2, int arg3, int arg4){
	_k1 = k1;
	k1 >>= 16;
	if ((-(k1&0x18) & (((arg1 + arg2) | arg1) | arg2))<0){k1 = _k1;return 0x80000023;}
	sceKernelDcacheWritebackRange (arg1, arg2);
	if (((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))
		sceKernelDcacheInvalidateRange (0x40, 0x100000);
	dec = sceMeCore_driver_F702E73A (0x144, arg1, arg2, 0x40, 0x100000, ((arg4) ? 2 : 1));
	k1 = _k1;
	if (dec < 0)return dec;
	if (((*((int *) 0x4548) < (dec & 0xFFFF))))return 0x80000023;
	if ((((*((int *) 0x4544) < (dec >> 16)))))return 0x80000023;
	return sceJpegMJpegCsc (arg3, 0x40, dec, var17);
}
int sceJpegDecodeMJpegYCbCrSuccessively (int arg1, int arg2, int arg3, int arg4, int arg5){
	_k1 = k1;
	k1 = k1 >> 16;
	if ((ret=sceMeCore_driver_F702E73A (0x141, arg2, arg3, arg4, arg5, arg6, arg7))<0)return ret;
	if (!(p=sceMeMemory_driver_3D0D8BAF (ret)))return 0x80650041;
	p64 = ((p + 0x7F) & ~0x7F);
	if ((ret=sceMeCore_driver_F702E73A (0x140, p64, arg1, arg2, 1, ((arg5) ? 2 : 1)))<0)return ret;
	if (arg4 >= ret)return 0x80650041;
	if ((ret=sceMeCore_driver_F702E73A (0x143, p64, arg3, 0, 0, 0, 0))<0)return ret;
	while ((ret=sceMeCore_driver_278F2C25 (0x142, p64))>0);
	if (!ret)ret=sceMeCore_driver_F702E73A (0x147, p64);
	sceMeMemory_driver_F9318AF4 (p);
	k1 = _k1;
	return 0;
}
int sceJpegDecodeMJpegSuccessively (int arg1, int arg2, int arg3, int arg4){
	if (dec = sceJpegDecodeMJpegYCbCrSuccessively (arg1, arg2, 0x40, 0x100000, arg4)<0)return ret;
	if ((((*((int *) 0x4548) < (dec & 0xFFFF)))))return 0x80650020;
	if (((*((int *) 0x4544) < (dec >> 16))))return 0x80650020;
	if(res=sceJpegMJpegCsc (arg3, 0x40, dec, *((int *) 0x4544))<0)return res
	return dec;
}
int sceJpegGetOutputInfo (int arg1, int arg2, int arg3, int arg4){
	_k1 = k1;
	k1 = k1 >> 16;
	if (((0 - k1 & 0x18) & (((arg1 + arg2) | arg1) | arg2)) < 0)return;
	if ((arg3)&&(((0 - (k1 & 0x18)) & arg3) < 0))return;
	if ((len = sceMeCore_driver_F702E73A (0x141, 0 - k1 & 0x18, ((arg1 + arg2) | arg1) | arg2, k1 & 0x18, var10, var9, var8)) < 0)return;
	if (!(p = sceMeMemory_driver_3D0D8BAF (len)))return;
	sceKernelDcacheWritebackRange (arg1, arg2);
	var22 = sceMeCore_driver_F702E73A (0x140, var17, arg1, arg2, 1, (!(arg4) ? 0 : 2));
	if (var22>=0&&arg3)
	info = sceMeCore_driver_F702E73A (0x146, var17);
	*arg3 = (((((info >> 4) & 0xF) << 16) | ((1 << (((info >> 2) & 3)-1)) << 8)) | (1 << ((info & 3)-1)));
	if (info&3){
		if ((info & 0xC) == 0) *arg3 = 0;
		else if (!(info & 0xF0))*arg3 = 0;
	}else *arg3 = 0;
	return sceMeMemory_driver_F9318AF4 (var17);
	k1 = _k1;
}
int sceJpegDecompressAllImage (int arg1, int arg2, int arg3, int arg4){
	return decodeMjpeg (arg1, arg2, arg3, arg4, 0);
}
int sceJpegCsc (){
	return;
}
int sceJpegDecodeMJpegYCbCr (int arg1, int arg2, int arg3, int arg4, int arg5){
	return decodeMjpeg (arg1, arg2, arg3, arg4, ((arg5) ? 2 : 1));
}
int sceJpeg_9B36444C (){
	return;
}
int decodeMjpeg (int arg1, int arg2, int arg3, int arg4, int arg5){
	_k1 = k1;
	k1 >>= 16;
	if ((-(k1&0x18) & (((arg1 + arg2) | arg1) | arg2)) < 0)return;
	if (((-(k1&0x18) & (((arg3 + arg4) | arg3) | arg4)) < 0))return;
	sceKernelDcacheWritebackRange (arg1, arg2);
	if (((0x220202 >> ((arg1 >> 27) & 0x1F)) & 1))
		sceKernelDcacheInvalidateRange (arg3, arg4);
	ret = sceMeCore_driver_F702E73A (0x144, arg1, arg2, arg3, arg4, arg5);
	k1 = _k1;
	return ret;
}
int sceMpegBaseCscAvc (int arg1, int arg2, int arg3, int arg4){
	var5 = k1;
	k1 = k1 >> 16;
	res = (arg4[0] * arg4[1]) << 8;
	a = res>>3;
	b = res>>2;
	if (!arg3)arg3 = *((int *) 0x4C28);
	if ((((arg4 + 0x30) | arg4) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[ 4] + b) | arg4[ 4]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[ 5] + b) | arg4[ 5]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[ 6] + b) | arg4[ 6]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[ 7] + b) | arg4[ 7]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[ 8] + a) | arg4[ 8]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((var4[ 9] + a) | var4[ 9]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[10] + a) | arg4[10]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[11] + a) | arg4[11]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	var11 = (arg3 * arg4[1]) << 2;
	if (((0 - k1 & 0x18) & (((arg1 + var11) | arg1) | var11)) < 0)return 0x80000023;
	if (arg2&&(((0 - k1 & 0x18) & (((arg2 + var11) | arg2) | var11)) < 0))return 0x80000023;
	if (arg3&&(ret = checkCscWidth (*((int *) 0x4C2C), arg3, 0x4C10)))return ret;
	ret = sceKernelPollEventFlag (SemaMpegBaseCSC, 0x80000000, 0x21, sp);
	if (!(((((ret ^ 0x800201AF) < 1)) | ((!ret) >> 0x1F))))return ret;
	if (!((sp[0] & 3)))return 0x80000001;
	while (1) {
		if ((ret=sceDmacplus_driver_6BB9BD45 (arg1, arg2, arg4))&&(ret!=0x80000021))return ret;
		if (!sceDmacplus_driver_0A40EF79 (0, 0))break;
	}
	return 0;
}
int sceMpegBaseCscVme (int arg1, int arg2, int arg3, int arg4){
	var5 = k1;
	k1 = k1 >> 16;
	var6 = k1 & 0x18;
	if ((((arg4 + 0x28) | arg4) & (0 - var6)) < 0)return 0x80000023;
	var10 = (arg4[0] * arg4[1]) << 7;
	var11 = var10 >> 2;
	if (!arg3)arg3 = *((int *) 0x4C28);
	if (!(((arg3 < (arg4[1] << 4)))))return 0x800001FE;
	var13 = arg4[4];
	var14 = (arg3 * arg4[1]) << 2;
	if (((0 - k1 & 0x18) & (((var13 + var10) | var13) | var10)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((var16 + var10) | var16) | var10)) < 0)return 0x80000023;
	if ((((arg4[6] + var11) | arg4[6]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[7] + var11) | arg4[7]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[8] + var11) | arg4[8]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg4[9] + var11) | arg4[9]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((arg1 + var14) | arg1) | var14)) < 0)return 0x80000023;
	if ((!arg2)&&(((0 - k1 & 0x18) & (((arg2 + var14) | arg2) | var14)) < 0))return 0x80000023;
	if (arg3&&(ret=checkCscWidth (*((int *) 0x4C2C), arg3, 0x4C10)))return ret;
	ret = sceKernelPollEventFlag (SemaMpegBaseCSC, 0x80000000, 0x21, sp);
	if (!(((((ret ^ 0x800201AF) < 1)) | ((!ret) >> 0x1F))))return ret;
	if (!(sp[0] & 3))return 0x80000001;
	while (1) {
		if ((ret=sceDmacplus_driver_86EAC84A (arg1, arg2, arg4))&&ret!=0x80000021)return ret;
		if (!sceDmacplus_driver_0A40EF79 (0, 0))break
	}
	return 0;
}
int sceMpegBaseCscAvcRange (int arg1, int arg2, int arg3, int arg4, int arg5){
	var6 = k1;
	k1 = k1 >> 16;
	if ((((arg5 + 0x30) | arg5) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	res = (arg5[0] * arg5[1]) << 6;
	a = res >> 1;
	if (!arg4)
		arg4 = *((int *) 0x4C28);
	if ((arg4 < (arg3[2] << 4)))return 0x800001FE;
	if (((0 - k1 & 0x18) & (((arg5[4] + res) | arg5[4]) | res)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((arg5[6] + res) | arg5[6]) | res)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((arg5[5] + res) | arg5[5]) | res)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((arg5[7] + res) | arg5[7]) | res)) < 0)return 0x80000023;
	if ((((arg5[ 8] + a) | arg5[ 8]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg5[ 9] + a) | arg5[ 9]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg5[10] + a) | arg5[10]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if ((((arg5[11] + a) | arg5[11]) & (0 - k1 & 0x18)) < 0)return 0x80000023;
	if (((0 - k1 & 0x18) & (((arg1 + ((arg4 * arg5[1]) << 2)) | arg1) | ((arg4 * arg5[1]) << 2))) < 0)return 0x80000023;
	if (arg2&&(((0 - k1 & 0x18) & (((arg2 + var16) | arg2) | var16)) < 0))return;
	if (((arg5[1] < (arg3[0] + arg3[2]))))return 0x800001FE;
	if (((arg5[0] < (arg3[1] + arg3[3]))))return;
	if (arg4){
		if ((ret=checkCscWidth (*((int *) 0x4C2C), arg4, 0x4C10)))return ret;
		arg5[0] = arg5[0];
	}
	if (arg5[0]!=arg3[3])return sub_03C14 (arg1, arg2, arg3, arg5);
	if (arg5[1]!=arg3[2]){
		sp[16] = arg1;
		sp[17] = arg2;
		if ((ret=mpegBaseCscAvcRange (sp+0x40, sp+0x44, arg3, arg5, sp+0x30, sp+0x48)))return ret;
		sp[2] = arg5[2];
		sp[3] = arg5[3];
		sp[0] = arg3[3];
		sp[1] = (arg3[2] - sp[18]);
		sub_03900 (sp, arg5, sp+0x30, 0);
	}
	return mpegBaseCscAvc (arg1, arg2, arg5);
}
int checkCscWidth (int arg1, int arg2, int arg3){
	while (1) {
		if ((ret = sceDmacplus_driver_960D7B8A (arg1, arg2, arg3)) != 0x80000021)break;
		sceDmacplus_driver_0A40EF79 (0, 0);
	}
	return ret;
}
int sceMpegbase_driver_0530BE4E (int arg1){
	return checkCscWidth ((*((int *) 0x4C2C) = arg1), *((int *) 0x4C28), 0x4C10);
}
int sceMpegbase_driver_AC9E717E (int arg1, int arg2){
	_k1 = k1;
	k1 = k1 >> 16;
	var5 = ((arg2 + 0x16) | arg2) & (0 - k1 & 0x18);
	if (var5<0)return 0x80000023;
	var9 = 0x4C10;
	*((int *) 0x4C2C) = 0;
	var10 = arg2;
	var11 = arg2 + 16;
	*((int *) 0x4C28) = arg1;
	if ((arg2 | 0x4C10) & 3){
		var8 = 0;
		var6 = 0x80000000;
		var12 = var11;
		while (1) {
			var13 = LWL (var10, var8, 3);
			var8 = LWR (var10, var13, 0);
			var14 = LWL (var10, var5, 0x7);
			var5 = LWR (var10, var14, 4);
			var15 = LWL (var10, var6, 0xB);
			var6 = LWR (var10, var15, 0x8);
			var16 = LWL (var10, var11, 0xF);
			var11 = LWR (var10, var16, 0xC);
			SWL (var9, var8, 3);
			SWR (var9, var8, 0);
			SWL (var9, var5, 0x7);
			SWR (var9, var5, 4);
			SWL (var9, var6, 0xB);
			SWR (var9, var6, 0x8);
			SWL (var9, var11, 0xF);
			SWR (var9, var11, 0xC);
			var10 += 16;
			var9 += 16;
			if (var10 != var12)
				continue;
			break;
		}
		var17 = LWL (var10, var12, 3);
		var18 = LWR (var10, var17, 0);
		SWL (var9, var18, 3);
		SWR (var9, var18, 0);
		((char *) var9)[4] = ((char *) var10)[4];
		((char *) var9)[5] = ((char *) var10)[5];
	}else{
		do{
			var9[0] = var10[0];
			var9[1] = var10[1];//uncached
			var9[2] = var10[2];//uncached
			var9[3] = var10[3];//uncached
			var10+=16;
			var9 +=16;
		}while(var10 != var11);
		var9[0] = var10[0];
		((short *) var9)[2] = ((short *) var10)[2];
	}
	return checkCscWidth (0, arg1, arg2);
	k1 = _k1;
	ra = sp[1];
}
int sceMpegBaseCscInit (int arg1){
	_k1 = k1;
	k1 = k1 >> 16;
	ret = sceMpegbase_driver_AC9E717E (arg1, 0x44EC);
	k1 = _k1;
	return ret;
}
void sub_03900 (int arg1, int arg2, int arg3, int arg4){
	if ((arg4&2)){
		var10 = arg2[7] + arg3[1];
		var11 = arg2[5] + arg3[1];
		var12 = arg2[9] + arg3[3];
		var13 = arg2[11] + arg3[3];
	}else{
		var10 = arg2[6] + arg3[0];
		var11 = arg2[4] + arg3[0];
		var13 = arg2[10] + arg3[2];
		var12 = arg2[8] + arg3[2];
	}
	arg1[4] = var11;
	arg1[6] = var10;
	arg1[8] = var12;
	arg1[10] = var13;
	if (!arg4){
		var10 = arg2[7] + arg3[1];
		var13 = arg2[11] + arg3[3];
		var11 = arg2[5] + arg3[1];
		var12 = arg2[9] + arg3[3];
	}
	arg1[11] = var13;
	arg1[5] = var11;
	arg1[7] = var10;
	arg1[9] = var12;
}
int mpegBaseCscAvc (int arg1, int arg2, int arg3){
	ret = sceKernelPollEventFlag (SemaMpegBaseCSC, 0x80000000, 0x21, sp);
	if (!((((ret ^ 0x800201AF) < 1)) | ((!ret) >> 0x1F)))return ret;
	if (!(sp[0] & 3))return 0x80000001;
	while (1) {
		if ((ret=sceDmacplus_driver_6BB9BD45 (arg1, arg2, arg3))&&ret!=0x80000021)return ret;
		if (!sceDmacplus_driver_0A40EF79 (0, 0))break;
	}
	return 0;
}
int mpegBaseCscAvcRange (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	sp[1] = 0;
	if (*arg3 & 1){
		var18 = (arg4[0] << 4) >> 1;
		arg5[0] = (var18 * ((*arg3+1)>>1)) << 4;
		arg5[1] = (var18 * ((*arg3+0)>>1)) << 4;
		arg5[2] = (arg5[0] >> 1);
		arg5[3] = (arg5[1] >> 1);
		sp[0] = arg3[3];
		sp[1] = 1;
		sp[2] = arg4[2];
		sp[3] = arg4[3];
		sub_03900 (sp, arg4, arg5, 2);
		if ((ret=mpegBaseCscAvc (arg1[0], arg2[0], sp)))return ret;
		arg1[0] = (arg1[0] + 0x40);
		if (arg2[0])
			arg2[0] = (arg2[0] + 0x40);
		arg5[1] += var18 << 4;
		arg5[3] += ((var18 << 4) >> 1);
	}else{
		var10 = (((arg4[0] << 4) >> 1) * (*arg3 >> 1)) << 4;
		arg5[0] = var10;
		arg5[1] = var10;
		arg5[2] = var10 >> 1;
		arg5[3] = var10 >> 1;
	}
	*arg6 = sp[1];
	return 0;
}
int sub_03C14 (int arg1, int arg2, int arg3, int arg4){
	if ((ret=mpegBaseCscAvcRange (sp+0x40, sp+0x44, arg3, arg4, sp+0x30, sp+0x48)))return ret;
	var16 = arg3[2] - sp[18];
	sp[0] = arg3[3];
	sp[2] = arg4[2];
	sp[3] = arg4[3];
	sp[1] = 2;
	for (i=0,var20=arg4[0]<<7,var21=var20>>1;i < var16>>1;i++) {
		sub_03900 (sp, arg4, var1, 0);
		if ((ret=mpegBaseCscAvc (arg1,arg2, sp)))return ret;
		arg1+=0x80;
		if (arg2)arg2+=0x80;
		sp[12]+=var20;
		sp[14]+=var21;
		sp[13]+=var20;
		sp[15]+=var21;
	}
	if (var16 & 1){
		sp[1] = 1;
		sub_03900 (sp, arg4, var1, 0);
		return mpegBaseCscAvc (arg1,arg2, sp);
	}
	return 0;
}
int sceAvcodecStartEntry (){//module_start
	SemaMpegBaseLLI = sceKernelCreateSema ("SceMpegBaseLLI", 0, 1, 1, 0);
	*((int *) 0x4C28) = 0;
	*((int *) 0x4C2C) = 0;
	SemaMpegBaseCSC = sceKernelCreateEventFlag ("SceMpegBaseCSC", 0x200, 0, 0);
	sceMePower_driver_52E7CD99 (0);
	sceMePower_driver_2ECCB138 (0);
	JpegFlag = 0;
	SemaJpeg = sceKernelCreateSema ("SceJpeg", 0, 1, 1, 0);
	return;
}
int sceAvcodecEndEntry (){//module_stop
	sceKernelDeleteEventFlag (SemaMpegBaseCSC);
	sceKernelDeleteSema (SemaMpegBaseLLI);
	sceKernelDeleteSema (SemaJpeg);
}

