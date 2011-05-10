#include <pspkernel.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "file.h"
PSP_MODULE_INFO("mp4",0,0,0);
PSP_HEAP_SIZE_KB(2048);
#define OR :case
#define sw(n) (((n>>24)&0xff)|((n<<8)&0xff0000)|((n>>8)&0xff00)|((n<<24)&0xff000000))
#define sw64(n) (((n<<56)&0xFF)|((n<<48)&0xFF00)|((n<<40)&0xFF0000)|((n<<32)&0xFF000000)|((n<<24)&0xFF00000000)|((n<<16)&0xFF0000000000)|((n<<8)&0xFF000000000000)|((n<<0)&0xFF00000000000000))
extern int __psp_free_heap(void);
u32 fd,size,type,tmp;//atom parsing
char curType;
MP4 f;
char* c=NULL;//atom content buffer
u32 read32(){
	u32 i;
	sceIoRead(fd,&i,4);
	return sw(i);
}
u64 read64(){//fixme
	u64 i;
	sceIoRead(fd,&i,8);
	return sw64(i);
}
void head(){
	size=read32()-8;
	type=read32();
	if(size==-7)size=read64();
}
int get(){
	c=realloc(c,size);
	return c?sceIoRead(fd,c,size):puts("malloc error");
}
void skip(){
	sceIoLseek(fd,size,SEEK_CUR);
}
void parse(){
	head();
//	printf("\n%c%c%c%c:",type>>24,type>>16,type>>8,type);
	switch(type){//parent atom must be in cased (otherwith they are skipped)
		case'moov'OR'trak'OR'mdia'OR'minf'OR'stbl':break;//parent:dont skip them
		case'mdhd':get();tmp=sw(((int*)c)[3]);break;
		case'hdlr':get();curType=c[8];break;
		case'stsd':{get();
			if(curType=='s'){
				f.Acodec=sw(((int*)c)[3]);
				if(c[12]=='m'&&c[13]=='p'&&c[14]=='4'&&c[15]=='a'){
					f.ch=c[15+18];
					f.bps=c[15+20];
					f.hz=((c[15+25]<<8)+(c[15+26]))&0xFFFF;
				}
			}else	if(curType=='v'){
				f.Vcodec=sw(((int*)c)[3]);
				f.fps=tmp;
				f.width=sw(((int*)c)[10])>>16;
				f.height=sw(((int*)c)[10])&0xFFFF;
				if((c[98]=='a')&&(c[99]=='v')&&(c[100]=='c')&&(c[101]=='C')){
					f.profile=*(c+103);
					f.nalSiz=1+((*(c+106))&0x03);
					f.spsLen=(*(c+108)<<8)+*(c+109);
					f.sps=malloc(f.spsLen);
					for(tmp=0;tmp<f.spsLen;tmp++)
						f.sps[tmp]=*(c+110+tmp);
					f.ppsLen=(*(c+111+tmp)<<8)+*(c+112+tmp);
					f.pps=malloc(f.ppsLen);
					for(int i=0;i<f.ppsLen;i++)
						f.pps[i]=*(c+113+tmp+i);
				}else{
					printf("codec not implemented");
				}
			}
		}break;
		case'stts':{get();
			if(curType=='s'){
				f.AsttsLen=sw(((int*)c)[2]);
				f.AsttsCnt=malloc(f.AsttsLen*sizeof(u32));
				for(int i=0;i<f.AsttsLen;i++)f.AsttsCnt[i] = sw(((int*)c)[2+i*2]);
				f.AsttsDur=malloc(f.AsttsLen*sizeof(u32));
				for(int i=0;i<f.AsttsLen;i++)f.AsttsDur[i] = sw(((int*)c)[3+i*2]);
			}else	if(curType=='v'){
				f.VsttsLen=sw(((int*)c)[2]);
				f.VsttsCnt=malloc(f.VsttsLen*sizeof(u32));
				for(int i=0;i<f.VsttsLen;i++)f.VsttsCnt[i] = sw(((int*)c)[2+2*i]);
				f.VsttsDur=malloc(f.VsttsLen*sizeof(u32));
				for(int i=0;i<f.AsttsLen;i++)f.AsttsDur[i] = sw(((int*)c)[3+2*i]);
			}
		}break;
		case'stss':{
			get();
			if(curType=='s'){
				f.AstssLen=sw(((int*)c)[1]);
				f.Vstss=malloc(f.AstssLen*sizeof(u32));
//				for(int i=0;i<f.AstssLen;i++)f.Astss[i] = sw(((int*)c)[2+i]);
			}else if(curType=='v'){
				f.VstssLen=sw(((int*)c)[1]);
				f.Vstss=malloc(f.VstssLen*sizeof(u32));
				//	for(int i=0;i<f.VstssLen;i++)
				//		f.Vstss[i] = sw(((int*)c)[2+i]);			
			}
		}break;
		case'stsc':{get();
			if(curType=='s'){
				f.AstscLen=sw(((int*)c)[1]);
				f.AstscFst=malloc(f.AstscLen*sizeof(u32));
				f.AstscSpc=malloc(f.AstscLen*sizeof(u32));
				f.AstscSid=malloc(f.AstscLen*sizeof(u32));
				for(int i=0;i<f.AstscLen;i++){
					//f.stscFst[i] = sw(((int*)c)[2+i]);
					//f.stscSpc[i] = sw(((int*)c)[3+i]);
					//f.stscSid[i] = sw(((int*)c)[4+i]);
				}
			}else if(curType=='v'){
				f.VstscLen=sw(((int*)c)[1]);
				f.VstscFst=malloc(f.VstscLen*sizeof(u32));
				f.VstscSpc=malloc(f.VstscLen*sizeof(u32));
				f.VstscSid=malloc(f.VstscLen*sizeof(u32));
				for(int i=0;i<f.VstscLen;i++){
					//f.stscFst[i] = sw(((int*)c)[2+i]);
					//f.stscSpc[i] = sw(((int*)c)[3+i]);
					//f.stscSid[i] = sw(((int*)c)[4+i]);
				}
			}
		}break;
		case'stsz':{get();
			if(curType=='s'){
				f.AstszCnt=sw(((int*)c)[1]);//0 if const size
				f.AstszLen=sw(((int*)c)[2]);
				f.AstszTbl=malloc(f.AstszLen*sizeof(u32));
				for(int i=0;i<f.AstszLen;i++){
					//f.stszTbl[i] = sw(((int*)c)[3+i]);
				}
			}else if(curType=='v'){
				f.VstszCnt=sw(((int*)c)[1]);//0 if const size
				f.VstszLen=sw(((int*)c)[2]);
				f.VstszTbl=malloc(f.VstszLen*sizeof(u32));
				for(int i=0;i<f.VstszLen;i++){
					//f.stszTbl[i] = sw(((int*)c)[3+i]);
				}
			}
		}break;
		case'stco':{get();
			if(curType=='s'){
				f.AstcoLen=sw(((int*)c)[1]);
				f.AstcoOff=malloc(f.AstcoLen*sizeof(u32));
				for(int i=0;i<f.AstcoLen;i++){
					//f.AstcoOff[i] = sw(((int*)c)[2+i]);
				}
			}else if(curType=='v'){
				f.VstcoLen=sw(((int*)c)[1]);
				f.VstcoOff=malloc(f.VstcoLen*sizeof(u32));
				for(int i=0;i<f.VstcoLen;i++){
					//f.VstcoOff[i] = sw(((int*)c)[2+i]);
				}
			};
		}break;
		case'mdat':return;//data >> gtfo !
		default:skip();break;
	}
	parse();
}//time//Astss//AstszCnt//AstcoLen//AstcoOff//VsttsLen
int main(int argc,char* argv[]){
	if(argc<2)return 0;
	if((fd=sceIoOpen(argv[1],PSP_O_RDONLY,0777))>0)
		parse();
	else puts("file open error: absolute path only atm.");
	for(int i=0;i<sizeof(MP4)/4;i++)printf("%02i:%08X\n",i,((u32*)&f)[i]);
	__psp_free_heap();
	sceIoClose(fd);
	return 0;
}
/*
int module_start(SceSize args,void* argp){
	char *argv[16+1];int argc=0,i=0;
	while((i+=strlen(argv[argc++]=&((char*)argp)[i])+1)<args);
	if(argc<=1)return -1;
	if((fd=sceIoOpen(argv[1],PSP_O_RDONLY,0777))>0)parse();
	//for(int i=0;i<sizeof(MP4)/4;i++)printf("%02i:%08X\n",i,((u32*)&f)[i]);
	__psp_free_heap();
	sceIoClose(fd);
	return 1;
}*/
/*
MSTRKRFT.mp4
-AUDIO-
stts:1 ko lol
-VIDEO-
stts:1 ko lol

>>http://wiki.multimedia.cx/index.php?title=QuickTime_container
moov
	mvhd => timeScale+Duration
	trak
		tkhd => width+height
		mdia
			mdhd => timeScale+Duration (again?)
			minf
				vmhd => isVideo
				smhd => isAudio
				stbl
					stts => stts[]
					ctts => ctts[]//unused
					stss => stss[]
					stsc => stsc[]
					stsz => stsz[]
					stco => stco[]
					stsd
						mp4a
							esds => samplerate
						mp4v => width+height
							esds => decinfo[]
						avc1 => width+height
							avcC >= profile nal sps[] pps[]
*/