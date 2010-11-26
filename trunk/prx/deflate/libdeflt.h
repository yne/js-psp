#ifndef LIBDEFLT_H
#define LIBDEFLT_H

#include <sys/types.h>

typedef struct {
	u_char id1;
	u_char id2;
	u_char cm;//Compression Method 0-7:resv,8:deflate,9:?
	u_char flg;//Flag 0:FTEXT,FHCRC,FEXTRA,FNAME,FCOMMENT,5-7:reserved
	u_int  uiMtime;// Mod date
	u_char xlf;// extra flags 2:slowest algorithm	,4=fastest algorithm
	u_char os;//0:FAT,Amiga,VMS,Unix,VM/CMS,Atari,HPFS,Mac,Z-System,CP/M,TOPS-20,NTFS,QDOS,Acorn RISCOS
} SceGzipHeader;

int sceGzipIsValid(const void *pSrc);
int sceGzipGetInfo(const void *pSrc, const void **ppvExtra, const char **ppszName, const char **ppszComment, u_short *pusCrc, const void **ppvData);
const char *sceGzipGetName(const void *pSrc);
const char *sceGzipGetComment(const void *pSrc);
const void *sceGzipGetCompressedData(const void *pSrc);
int  sceGzipDecompress(u_char *pDst, u_int uiBufSize, const void *pSrcGzip, u_int *puiCrc32);
int sceZlibIsValid(const void *pSrc);
int sceZlibGetInfo(const void *pSrc, u_char *pbCmf, u_char *pbFlg, u_int *puiDictId, const void **ppvData);
const void *sceZlibGetCompressedData(const void *pSrcZlib);
int  sceZlibDecompress(u_char *pDst, u_int uiBufSize, const void *pSrcZlib, u_int *puiAdler32);
u_int sceGzipCrc32(u_int uiCrc, const u_char *pSrc, u_int uiSize);
u_int sceZlibAdler32(u_int uiAdler, const u_char *pSrc, u_int uiSize);
int  sceDeflateDecompress(u_char *pDst, u_int uiBufSize, const void *pSrcDeflate, void *ppNext);
void *sceDeflateGetErxEntries(void);
#endif
