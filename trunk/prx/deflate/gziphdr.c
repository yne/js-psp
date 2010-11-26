#include <string.h>
#include <libdeflt.h>

int  sceGzipDecompress(u_char *pDst, u_int uiBufSize, const void *pSrcGzip, u_int *puiCrc32){
	const SceGzipHeader *pHeader = pSrcGzip;
	const void *pNext;
	struct {
		u_int uiCrc32;		// CRC-32
		u_int uiIsize;		// Input SIZE
	} footer;

	const void *pDeflate = sceGzipGetCompressedData(pSrcGzip);
	if(!pDeflate | ((pHeader->cm)!=0x08))return -1;
	int res = sceDeflateDecompress(pDst, uiBufSize, pDeflate, &pNext);
	if(res<0)return (res);
	memcpy(&footer, pNext, 8);
	if ((u_int)res!=footer.uiIsize)return -1;
	if (puiCrc32!=NULL)*puiCrc32 = footer.uiCrc32;
	return (res);
}
int sceGzipIsValid(const void *pSrc){
	const u_char *p = pSrc;
	if (p[0]!=0x1F || p[1]!=0x8B)return (0);
	return (1);
}
int sceGzipGetInfo(const void *pSrc, const void **ppvExtra, const char **ppszName, const char **ppszComment, u_short *pusCrc, const void **ppvData){
	SceGzipHeader hdr;
	const u_char *p = ((const u_char *)pSrc) + 10;

	if (ppvExtra)		*ppvExtra    = NULL;
	if (ppszName)		*ppszName    = NULL;
	if (ppszComment)	*ppszComment = NULL;
	if (pusCrc)			*pusCrc      = 0;
	if (ppvData)		*ppvData     = NULL;
	if (!pSrc)
		return -1;
	memcpy(&hdr, pSrc, sizeof(SceGzipHeader));
	if (hdr.id1!=0x1F || hdr.id2!=0x8B)
		return -1;
	if (hdr.flg&0x04){
		int xlen = p[0] | (p[1]<<8);
		if (ppvExtra) *ppvExtra = (const void *)p;
		p += xlen;
	}
	if (hdr.flg&0x08){
		if (ppszName)*ppszName = (const char *)p;
		while(*p) p++;
		p++;
	}
	if (hdr.flg&0x10){
		if (ppszComment) *ppszComment = (const char *)p;
		while(*p)p++;
		p++;
	}
	if (hdr.flg&0x02) {
		if (pusCrc) *pusCrc = p[0] | (p[1]<<8);
		p += 2;
	}
	if (ppvData) *ppvData = (const void *)p;
	return (0);
}
const char *sceGzipGetName(const void *pSrc){
	const char *pszName;
	int res;
	res = sceGzipGetInfo(pSrc, NULL, &pszName, NULL, NULL, NULL);
	if (res<0)
		return (NULL);
	return (pszName);
}
const char *sceGzipGetComment(const void *pSrc){
	const char *pszComment;
	int res = sceGzipGetInfo(pSrc, NULL, NULL, &pszComment, NULL, NULL);
	if (res<0)
		return (NULL);
	return (pszComment);
}
const void *sceGzipGetCompressedData(const void *pSrc){
	const void *pvCompData;
	int res = sceGzipGetInfo(pSrc, NULL, NULL, NULL, NULL, &pvCompData);
	if (res<0)
		return (NULL);
	return (pvCompData);
}

