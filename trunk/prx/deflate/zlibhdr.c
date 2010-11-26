#include <string.h>
#include <libdeflt.h>
#include <pspkernel.h>

int sceZlibDecompress(u_char *pDst, u_int uiBufSize, const void *pSrcZlib, u_int *puiAdler32){
	const void *pDeflate;
	const void *pNext;
	u_char cmf, flg;
	u_int uiAdler32;
	int res = sceZlibGetInfo(pSrcZlib, &cmf, &flg, NULL, &pDeflate);
	if((res<0)|((cmf & 0x0F)!=0x08)|((flg & 0x20)!=0))return -1;
	res = sceDeflateDecompress(pDst, uiBufSize, pDeflate, &pNext);
	if (res<0)return (res);
	memcpy(&uiAdler32, pNext, 4);
	if (puiAdler32)*puiAdler32 = uiAdler32;
	return (res);
}
int sceZlibIsValid(const void *pSrc){
	const u_char *p = (const u_char *)pSrc;
	u_char cmf = p[0];
	u_char flg = p[1];
	u_short us = (cmf<<8) | flg;
	if ((us % 31)!=0)return 0;
	return 1;
}
int sceZlibGetInfo(const void *pSrcZlib, u_char *pbCmf, u_char *pbFlg, u_int *puiDictId, const void **ppvData){
	const u_char *p = (const u_char *)pSrcZlib;
	u_char cmf = p[0];
	u_char flg = p[1];
	u_short us = (cmf<<8) | flg;
	if ((us % 31)!=0)return -1;
	if (pbCmf)*pbCmf = cmf;			// CMF (Compression Method and flags)
	if (pbFlg)*pbFlg = flg;			// FLG (FLaGs)
	p += 2;
	if ((flg & 0x20)!=0) {
		if (puiDictId)*puiDictId = (p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3];
		p += 4;
	}
	if (ppvData)*ppvData = p;
	return (0);
}
const void *sceZlibGetCompressedData(const void *pSrcZlib){
	const void *pvCompData;
	if (sceZlibGetInfo(pSrcZlib, NULL, NULL, NULL, &pvCompData))
		return NULL;
	return (pvCompData);
}

