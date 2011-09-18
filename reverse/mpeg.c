int mpegFlushStream (int arg1, int*arg2){
	if ((ret = checkMpegArg (arg1)))return ret;
	waitSema(*arg1[411]);
	if ((au = checkAu (arg2[0],	arg1[0], 1)) == -1){
		signalSema (*arg1[411]);
		return 0x806101FE;
	}
	if (((int *) var17)[2] != -1){
		var22 = arg2[2];
		((int *) au)[3] = 0;
		((int *) au)[0] = -1;
		((int *) au)[1] = -1;
		if (var22 != -1){
			((int *) var22)[3] = 0;
			((int *) var22)[1] = -1;
			((int *) var22)[0] = -1;
		}
	}
	var27 = (sp[0] << 3) + 0x00007594;//?
	sub_06D68 (((int *) var27)[1];, sp + 4,arg2[0]);
	arg2[4] = 0x7FFF;
	arg2[5] = ((int *) var27)[1];
	arg2[6] = 1;
	arg2[8] = 0;
	arg2[10] = ((int *) var27)[0];
	arg2[11] = 0;
	arg2[13] = 0;
	arg2[14] = 0;
	arg2[12] &= 0xFFFFFFFB;
	arg2[16] = 0;
	ret = signalSema(*arg1[411]);
	return ret;
}
int flushAllStream (int mpeg){
	if (ret=checkMpegArg (mpeg))return ret;
	for(int i=0;i<0x70;i++) {
		str = ((int *) ((i << 4) + *mpeg[6]))[2];
		if (str!=-1 && (ret=mpegFlushStream (mpeg, str)))return ret;
	}
	return 0;
}
int mpegUnRegistStream (int arg1, int arg2){
	if (ret=checkMpegArg (arg1))return ret;
	waitSema(*arg1[411]);
	int*au = checkAu (arg2[0], *arg1, 1);
	if ((au = checkAu (arg2[0], *arg1, 1))==-1){
		signalSema(*arg1[411]);
		return 0x806101FE;
	}
	if (au[2]==-1))return 0;
	au[3] = 0;
	au[2] = -1;
	au[0] = -1;
	au[1] = -1;
	if (arg2[2]==-1)return 0;
	arg2[2][3] = 0;
	arg2[2][1] = -1;
	arg2[2][2] = -1;
	arg2[2][0] = -1;
	signalSema(*arg1[411]);
	return 0;
}
int mpegRegistStream (int arg1, int arg2, int arg3){
	mpeg = *arg1;
	if (!checkMpegArg (arg1))return 0;
	var9 = mpeg[411];
	waitSema();
	au = checkAu (getStr (arg2, arg3), mpeg, 2);
	if (au != -1){
		if(!regStream(arg1, arg2, arg3, arg2?-1:(mpeg[8] + (arg3 << 11), au))
			return au;
	}
	signalSema(mpeg[411]);
	return 0;
}
int mpegInit (){
	if(MpegIsInit)return 0x80618005;
	MpegIsInit = 1;
	if(createSema (1, 1, "SceMpegLibmpeg", semaLib))return 0x80618006;
	if(createSema (1, 1, "SceMpegAvc", semaAvc))return 0x80618006;
	if(createSema (1, 1, "SceMpegAtrac", semaAtrac))return 0x80618006;
	initVideoCodec ();
	initAudioCodec (0);
	initCodecStruct ();
	return 0;
}
int mpegFinish(){
	if (!MpegIsInit)return	0x80618005;
	MpegIsInit = 0;
	audiocodecReleaseEDRAM();
	sceVideocodecReleaseEDRAM (VEDRAM);
	if (deleteSema(semaLib))return 0x80618006;
	if (deleteSema(semaAvc))return 0x80618006;
	if (deleteSema(semaAtrac))return 0x80618006;
	return 0;
}
int mpegQueryMemSize (int arg1){
	if (arg1==1){
		if (sub_06B14 (0))return;
		return audiocodecReleaseEDRAM();
	}
	return 0x00010000;
}
int mpegCreate (int arg1, int arg2, int arg3, int*arg4, int arg5, int mode, int arg7){
	if (arg3<mpegQueryMemSize (mode))return 0x80610022;
	waitSema(semaLib);
	memset (arg2, 0, arg3);
	*arg1 = ((arg2 + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F);
	*arg1[0] = *((int *) 0x755C);
	*arg1[1] = *((int *) 0x7560);
	*arg1[2] = 0x313030;
	*arg1[3] = -1;
	*arg1[414] = mode;
	if (createSema (1, 1, "SceMpegMpegData", (arg1 + 0x66C))){
		signalSema(semaLib);
		return 0x80618006;
	}
	*arg1[6] = (((arg1 + 0x6D0) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F);
	*arg1[4] = arg4;
	*arg1[5] = arg4[8];
	arg4[10] = arg1;
	for(i=0x6F,p=*arg1[6];i>0;i--,p += 0x10) {
		p[0] = -1;
		p[1] = -1;
		p[2] = -1;
		p[3] = 0;
	}
	*arg1[7] = (((*arg1[6] + 0x704) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F);
	for (i = 0x6E;i>0;i--){}
	*arg1[8] = (((*arg1[7] + 0x1DC4) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F);
	memset (*arg1[8], 0, 0x8000);
	*arg1[9] = 0;
	for(i=0;i<=0;i++) {
		((int *) arg1)[10] = 0x63;
		var36 = arg1 + 0x2C;
		for(j=0;j<arg1[10];j++) {
			var36[0] = 0;
			var36[1] = 0;
			var36[2] = var36+0x10;
			var36[3] = 0;
			var36+=0x10;
		}
		((arg1+(j<<4))+28)[2] = 0;
		arg1 += 0x644;
	}
	var43 = ((((var29 + 0x8000) + 0x644) + 0x3F) & 0xFFFFFFC0) | (0 & 0x3F);
	*arg1[419] = var43;
	*arg1[420] = var43 + 0x80;
	*arg1[421] = var43 + 0x80 + 0x40;;
	*arg1[422] = var43 + 0x80 + 0x40 + 0xC0;
	*arg1[423] = 0;
	*arg1[425] = ((int *)VEDRAM)[5];
	if(!*arg1[425]){
		signalSema(semaLib);
		return 0x80610022;
	}
	if (mode == 1){
		*arg1[415] = 0;
		((char *) arg1)[1664] = mode;
		((char *) arg1)[1665] = mode;
		*arg1[417] = 0;
		*arg1[418] = 0;
		*arg1[429] = 3;
	}else{
		((char *) arg1)[1664] = 0;
		((char *) arg1)[1665] = 0;
		*arg1[415] = 0x2;
		*arg1[417] = 0x4A000;
		*arg1[418] = 0x62400;
		if (!arg7)arg7 = 0x9000000;
		*arg1[429] = 0x2;
	}
	*arg1[427] = 0x1E0;
	*arg1[428] = 0x110;
	*arg1[426] = arg7;
	*arg1[430] = 0;
	sp[0] = *arg1[428];
	sp[1] = *arg1[429];
	sp[2] = *arg1[430];
	if (ret=setupVideoCodec (*arg1[419], *arg1[420], *arg1[421], *arg1[422], *arg1[423], (arg1 + 0x6A4), *arg1[426], *arg1[427])){
	initError:
		signalSema(semaLib);
		return ret;
	}
	if (mode == 1)videocodec_893B32B1 (*arg1[419], 1);
	if (ret=sceMpegBaseCscInit (var67))goto initError;
	if (mode == 1){
		*arg1[434] = 0;
		*arg1[433] = 0;
	}else{
		*arg1[434] = var43 + 0x80 + 0x40 + 0xC0 + 0x80;
		waitSema(semaAtrac);
		ret = audiocodecCheckNeedMem (sp + 0x10, mode, 0);
		signalSema(semaAtrac);
		*arg1[434]+=0x80;
		if (ret)goto initError;
		*arg1[433] = sp[4];
	}
	if (mode==1)*arg1[432] = 0;
	else if (*arg1[432]=sub_06B14 (0))goto initError;
	return (((*arg1[434]<(arg2 + arg3)))) ? 0:0x80610022;
}
int delete (int arg1){
	if (ret=checkMpegArg (arg1))return ret
	videocodecDelete(*arg1[419]);
	waitSema(semaLib);
	var14 = *arg1[6];
	for (var15 = 0x6F;var15>0;var15--) {
		((int *) var14)[0] = -1;
		((int *) var14)[1] = -1;
		((int *) var14)[2] = -1;
		((int *) var14)[3] = 0;
		var14 += 0x10;
	}
	deleteSema(*arg1[411]);
	return signalSema(semaLib)?0x80618006:0;
}
int mpegInitAu (int arg1, int arg2, int arg3){
	if (ret=checkMpegArg (arg1))return ret;
	((int *) arg3)[4] = arg2;
	((int *) arg3)[5] = 0;
	return 0;
}
int regStream (int arg1, int arg2, int arg3, int arg4, int*arg5){
	if (ret=checkMpegArg (arg1))return ret,
	if (arg2>=7)return 0x806101FE;
	arg5[0] = getStr (arg2, arg3);
	arg5[4] = 0x7FFF;
	arg5[6] = 1;
	arg5[1] = sub_06FB4 (arg2);
	arg5[3] = (!(arg2) ? arg4 : 0);
	var15 = (arg2 << 3) + 0x00007594;
	arg5[10] = ((int *) var15)[0];
	arg5[5] = ((int *) var15)[1];
	arg5[11] = 0;
	arg5[8] = 0;
	arg5[13] = 0;
	arg5[14] = 0;
	arg5[12] = 0;
	arg5[16] = 0;
	if ((au=checkAu(arg5[0], *arg1, 1))==-1)return 0x806101FE;
	var23 = ((int *) au)[2];
	if (var23==-1)return 0x80618005;
	((int *) au)[1] = var23;
	((int *) au)[2] = arg5;
	((int *) au)[3] = 0;
	((int *) au)[0] = var23;
	if (arg2){
		arg5[2] = var23;
		return 0;
	}
	if (((var35=checkAu(getStr (6, arg3), *arg1, 1)) == var23))return 0x806101FE;
	if (((int *) var35)[2] != var23)return 0x80618005;
	arg5[2] = var35;
	((int *) var35)[0] = var23;
	((int *) var35)[1] = var23;
	((int *) var35)[2] = arg5;
	((int *) var35)[3] = 0;
	return 0;
}
int avcDecodeMode (int*arg1, int lcd){
	if (ret=checkMpegArg (arg1))return ret;
	if(lcd.conv<-1 || lcd.conv>2)return 0x806101FE;
	if(lcd.mode<-1 || lcd.mode>3)return 0x806101FE;
	sceMpegbase_0530BE4E (((int *) ((lcd.mode << 2) + 0x7608))[0]);
	((int *) (*arg1)[419])[13] = lcd.conv;
	return 0;
}
int getCodec (int arg1, int arg2){
	if (ret = checkMpegArg (arg1))return ret;
	*arg2=*arg1[419];
	return 0;
}
int avcDecode (SceMpeg*mpeg, SceMpegAu* au, int iFrameWidth, void* pBuffer, int* pics){
	if((ret=checkMpegArg(mpeg)))return ret;//0x08A57200
	int* var19 = mpeg[419];//0x8A5788C
	var19[9] = (getAuSample (mpeg,au.iEsBuffer) & 0x0FFFFFFF);
	var19[10]=au.iAuSize;
	ret = videocodecDecode(var19);
	au.iAuSize = 0;
	Mp4AvcInfoStruct*info = mpeg[420];//0x8A57890
	Mp4AvcYuvStruct*yuv = mpeg[421];//0x8A57894
	if (ret)return ret;
	*pics = info[8];
	if (mpeg[414]<7)return var28;//0?
	if (*pics<0)return var28;
	for(int i=0;;i++) {
		pBuffer += 4;
		if (!*pBuffer)return 0x806101FE;
		yuv += 0x2C;
		Mp4AvcCscStruct csc={info->height>>4,info->width>>4,0,0,yuv[0],yuv[1],yuv[2],yuv[3],yuv[4],yuv[5],yuv[6],yuv[7]};
		if((ret=sceMpegBaseCscAvc(*pBuffer, 0, iFrameWidth,&csc)))return ret;
		if(i >= *pics)return var28;
	}
	return ret;
}
int avcDecodeStop (int arg1, int arg2, int arg3, int arg4){
	var3 = *arg1[421];
	if (var7=avcDecodeFlush (arg1))return var7;
	*arg4 = *arg1[420][8];
	if (*arg1[414]<7)return var7;
	if (var7>=*arg4)return var7;
	for(i=0;i>=*arg4;i++) {
		if (!arg3[0])return 0x806101FE;
		sp[0] = *arg1[420][3]>>4;
		sp[1] = *arg1[420][2]>>4;
		sp[2] = 0;
		sp[3] = 0;
		sp[4] = var3[0];
		sp[5] = var3[1];
		sp[6] = var3[2];
		sp[7] = var3[3];
		sp[8] = var3[4];
		sp[9] = var3[5];
		sp[10] = var3[6];
		sp[11] = var3[7];
		if (sceMpegBaseCscAvc (*arg3, 0, arg2, sp))return;
		var3+=0x2C;
		arg3+=4;
	}
	return 0;
}
int avcDecodeFlush (int arg1){
	if (ret = checkMpegArg (arg1))return ret;
	return videoCodecStop_(*arg1[419]);
}
int avcDecodeDetail (int arg1, int*arg2){
	if (ret = checkMpegArg (arg1))return ret;
	if (getCodec (arg1, codec))return;
	if (!0<codec[0][4][8]))return 0x806101FE;
	arg2[0] = codec[0][2];
	arg2[1] = codec[0][11][8];
	arg2[2] = codec[0][4][2];
	arg2[3] = codec[0][4][3];
	arg2[4] = codec[0][4][4];
	arg2[5] = codec[0][4][5];
	arg2[6] = codec[0][4][6];
	arg2[7] = codec[0][4][7];
	arg2[8] = codec[0][4][8];
	return 0;	
}
int avcInitYCbCr (int arg1, int arg2, int arg3, int arg4, int arg5){
	if (ret = checkMpegArg (arg1))return ret;
	memset (arg5, 0, 0x00000080);
	if (arg2){
		arg5[11] = arg2;
		arg5[4] = arg2;
		arg5[6] = arg2;
		arg5[8] = arg2;
		arg5[10] = arg2;
		arg5[5] = arg2;
		arg5[7] = arg2;
		arg5[9] = arg2;
	}
	var17 = var2 + 0x00000080;
	if (arg2!=1)return 0x806101FE;
	if (ret=getYCbCrStruct (arg3, arg4, sp, sp+4))return ret;
	var21 = sp[0];
	var22 = sp[1];
	((int *) var2)[4] = var17;
	var23 = var17 + var21;
	var24 = var21 >> 1;
	var25 = var23 + var21;
	var26 = var25 + var24;
	var27 = var26 + var24;
	var28 = var27 + var22;
	var29 = var28 + var22;
	((int *) var2)[11] = (var29 + (var22 >> 1));
	((int *) var2)[6] = var23;
	((int *) var2)[8] = var25;
	((int *) var2)[10] = var26;
	((int *) var2)[5] = var27;
	((int *) var2)[7] = var28;
	((int *) var2)[9] = var29;
	return 0;
}
int avcQueryYCbCrSize (int arg1, int arg2, int arg3, int arg4, int arg5){
	*arg5 = 0;
	if (var6=checkMpegArg (arg1))return var6;
	if (arg2==2){
		*arg5 = 0x80;
		return var6;
	}
	if (arg2!=1)return 0x806101FE;
	if (var7=getYCbCrStruct (arg3, arg4, sp, sp+4))return var7;
	*arg5 = (((sp[0]+sp[1] << 1) + sp[0]+sp[1]) + 0x80);
	return 0;
}
int avcCsc (int arg1, int arg2, int arg3, int arg4, int arg5){
	if (ret=checkMpegArg (arg1))return ret;
	sp[0] = arg1[0];
	sp[1] = arg2[1];
	sp[2] = arg2[2];
	sp[3] = arg2[3];
	if (arg2[4] == 2){
		p = *arg1[421] + (arg2[12] * 0x2C);
		var26 = p[7] + *((int *) 0x00007790);
		sp[4] = p[0] + *((int *) 0x00007784));
	}else{
		p = arg2 + 0x10;
		var26 = ((int *) p)[7] + *((int *) 0x00007790);
		sp[4] = arg2[4] + *((int *) 0x00007784);
	}
	if (arg3[0] & 0xF)return 0x806101FE;
	if (arg3[1] & 0xF)return 0x806101FE;
	if (arg3[2] & 0xF)return 0x806101FE;
	if (arg3[3] & 0xF)return 0x806101FE;
	sp[5] = p[1] + *((int *) 0x00007788);
	sp[6] = p[2] + *((int *) 0x00007784);
	sp[7] = p[3] + *((int *) 0x00007788);
	sp[8] = p[4] + *((int *) 0x0000778C);
	sp[9] = p[5] + *((int *) 0x00007790);
	sp[10]= p[6] + *((int *) 0x0000778C);
	sp[11] = var26;
	sp[12] = (arg3[0] >> 4);
	sp[13] = (arg3[1] >> 4);
	sp[14] = (arg3[2] >> 4);
	sp[15] = (arg3[3] >> 4);
	return sceMpegBaseCscAvcRange (arg5, 0, sp + 0x30, arg4, sp);
}
int mpegYCrCbCopy (int arg1, int arg2, int arg3){
	if (ret=checkMpegArg (arg1))return ret;
	if (arg2<1 || arg3<1)return 0x806101FE;
	if (arg2[4]==2)return 0x806101FE;
	return YCrCbCopy (arg1, arg2, arg3, -1);
}
int avcDecodeYCbCr (int arg1, int arg2, int arg3, int arg4){
	if (ret = checkMpegArg (arg1))return ret;
	var11 = ((int *) arg1)[0];
	var12 = ((int *) arg2)[4];
	codec = ((int *) var11)[419];
	((int *) codec)[9] = ((getAuSample (arg1, var12) & 0x0FFFFFFF));
	((int *) codec)[10] =((int *) arg2)[5];
	var5 = videocodecDecode (codec);
	((int *) arg2)[5] = 0;
	if (var5)	return var5;
	return yCbCr (arg1, arg3, arg4);
}
int avcDecodeStopYCbCr (int arg1, int arg2, int arg3){
	if((err=avcDecodeFlush(arg1)))return err;
	return yCbCr (arg1, arg2, arg3);
}
int getYCbCrStruct (int arg1, int arg2, int arg3, int arg4){
	if ((((arg1 | arg2) & 0xF))return 0x806101FE;
	if (((((((arg1>>4)-1)<0x0000001E)) ^ 1) | (((arg2>>4)<1))))return 0x806101FE;
	if ((arg2>>4)>=12)return 0;
	if ((arg1>>4) & 1){
		arg3[0] = ((((arg1 & 0xFFFFFFE0) + 0x20) >> 1) * (arg2>>1));
		arg4[0] = ((((arg1 & 0xFFFFFFE0)       ) >> 1) * (arg2>>1));
	}else{
		arg3[0] = arg4[0] = ((((arg1 & 0xFFFFFFE0) | (0 & 0x0000001F)) >> 1) * (arg2>>1));
	}
	return 0;
}
//0x00001740
int YCrCbCopy (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFFF0;
	sp[0] = ra;
	var1 = ((int *) arg1)[0];
	var2 = arg2;
	var3 = arg2;
	var4 = ((int *) var1)[420];
	var5 = ((int *) var1)[421];
	if (arg4 == -1)
	{
		var17 = ((int *) arg3)[4];
		if (var17 == 0x00000002)
		{
			arg4 = ((int *) arg3)[12];

		label6:
		}
		else
		{
		}
	}
	else
	goto label6;
	var6 = arg4;
	if (arg4 == -1)
	{
		var16 = ((int *) var2)[4];
		var11 = arg3 + 0x00000010;
		var3 = var2;
		var6 = -1;
		var15 = 0x806101FE;
		if (!(var16 == 0x00000002))
		{
			var9 = ((int *) arg3)[0];
			var10 = ((int *) arg3)[1];

		label11:
			var14 = mpegBaseYCrCbCopy (var3, var6, var10, var9, var11);
			var15 = var14;
		}
	}
	else
	{
		var7 = ((int *) var4)[3];
		var8 = ((int *) var4)[2];
		var9 = var7 >> 0x00000004;
		var10 = var8 >> 0x00000004;
		var11 = var5 + (arg4 * 0x0000002C);
		goto label11;
	}
	ra = sp[0];
	sp = sp + 0x00000010;
	return var15;
}
int yCbCr (int*mpeg, int*p, int arg3){
	var6 = ((int *) mpeg[420])[8];
	((int *) arg3)[0] = var6;
	if (var6 <= 0)return var6;
	for(i=0;i<((int *) arg3)[0];i++) {
		if (!(p+=4))return 0x806101FE;
		if (ret=YCrCbCopy (arg1,*p,0,i))return ret;
	}
	return 0;
}
//0x00001898
int mpegBaseYCrCbCopy (int arg1, int arg2, int arg3, int arg4, int arg5){
	sp = sp + 0xFFFFFFC0;
	sp[13] = ra;
	sp[12] = s0;
	var1 = ((int *) arg1)[4];
	((int *) arg1)[0] = arg4;
	var2 = arg5;
	var3 = 0;
	((int *) arg1)[1] = arg3;
	var4 = sp;
	((int *) arg1)[2] = 0;
	((int *) arg1)[3] = 0;
	if (var1 == 0x00000002)
	{
		((int *) arg1)[12] = arg2;
	}
	else
	{
		var5 = *((int *) 0x00007784);
		var6 = *((int *) 0x00007790);
		var7 = *((int *) 0x0000778C);
		var8 = *((int *) 0x00007788);
		var9 = ((int *) var2)[7];
		var10 = ((int *) var2)[0];
		var11 = ((int *) var2)[2];
		var12 = ((int *) var2)[4];
		var13 = ((int *) var2)[6];
		var14 = ((int *) var2)[1];
		var15 = ((int *) var2)[3];
		var16 = ((int *) var2)[5];
		sp[11] = (var9 + var6);
		sp[1] = (arg3 << 0x00000004);
		sp[0] = (arg4 << 0x00000004);
		sp[4] = (var10 + var5);
		sp[6] = (var11 + var5);
		sp[8] = (var12 + var7);
		sp[10] = (var13 + var7);
		sp[5] = (var14 + var8);
		sp[7] = (var15 + var8);
		sp[9] = (var16 + var6);
		sp[2] = 0;
		sp[3] = 0;
		var19 = sceMpegBaseYCrCbCopy (arg1, var4, 3);
		var3 = var19;
	}
	ra = sp[13];
	var20 = sp[12];
	sp = sp + 0x00000040;
	return var3;
}
//0x0000198C
int atracDecode (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFFE0;
	sp[3] = s3;
	sp[2] = s2;
	var1 = arg2;
	sp[1] = s1;
	sp[0] = s0;
	sp[4] = ra;
	var4 = checkMpegArg (arg1);
	var5 = var4;
	if (!(var4 != 0))
	{
		var6 = ((int *) arg1)[0];
		var7 = ((int *) var6)[434];
		if (arg4 == 1)
		{
			var16 = ((int *) var1)[4];
			var17 = ((int *) var6)[433];
			var18 = ((int *) var6)[432];
			var21 = sub_06980 (var7, var18, var17, (var16 + 0x00000002), (var16 + 0x00000004));
			var5 = var21;
			if (!(var21 != 0))
			{
				var8 = ((int *) var1)[4];

			label11:
				((int *) var7)[8] = arg3;
				((int *) var7)[6] = var8;
				var11 = audiocodecDecode (var7);
				var5 = var11;
			}
		}
		else
		{
			var8 = ((int *) var1)[4];
			goto label11;
		}
	}
	ra = sp[4];
	var12 = sp[3];
	var13 = sp[2];
	var14 = sp[1];
	var15 = sp[0];
	sp = sp + 0x00000020;
	return var5;
}
int mpegQueryStreamOffset (int* arg1, int arg2, int* arg3){
	if (strcmp (arg1, "LIBMPEG"))arg3=0;return 0x806101FE;
	if (strncmp (arg2, "PSMF",4))arg3=0;return 0x806101FE;
	if ((arg1[3] = getPMFversion (arg2))<0){arg3=0;return 0x80610002;}
	if (((arg3 = read32 ((arg2 + 8))) & 0x07FF))arg3=0;return 0x806101FE;
	return 0;
}
int checkMpegArg (int arg1){
	return (strcmp (*var1, "LIBMPEG")?0x806101FE:0);
}
int mpegQueryStreamSize (int arg1, int arg2){
	*arg2 = read32(arg1+12);
	if(*arg2 & 0x7FF)){
		*arg2 = 0;
		return 0x806101FE;
	}
	return 0;
}
int getPMFversion (int arg1){
	if (!strncmp (arg1+4, "0012", 4))return 0;
	if (!strncmp (arg1+4, "0013", 4))return 1;
	if (!strncmp (arg1+4, "0014", 4))return 2;
	if (!strncmp (arg1+4, "0015", 4))return 3;
	return -1;
}
int checkAu (int arg1, int arg2, int arg3){
	if (((arg1 & 0xFFFFE000)) == 0xBF01E000){
		var18 = (arg1 >> 8) & 0x0000001F;
		if (arg3 == 1){
			var19 = ((int *) arg2)[6];
			var20 = var18 << 0x00000004;
		}else{
			var19 = ((int *) arg2)[7];
			var20 = ((var18 << 0x00000004) + var18) << 0x00000002;
		}
		var2 = var19 + var20;
	}
	else
	{
		if (((arg1 & 0xE0000000) | (0 & 0x1FFFFFFF)) == 0xE0000000)
		{
			var15 = (arg1 >> 24) & 0x0000001F;
			if (arg3 == 1)
			{
				var17 = ((int *) arg2)[6];
				var2 = (var17 + (var15 << 0x00000004)) + 0x00000100;
			}
			else
			{
				var16 = ((int *) arg2)[7];
				var2 = (var16 + (((var15 << 0x00000004) + var15) << 0x00000002)) + 0x00000440;
			}
		}
		else
		{
			var1 = (arg1 & 0xFFF00000) | (0 & 0x000FFFFF);
			if (var1 == 0xBD000000)
			{
				var12 = (arg1 >> 0x00000010) & 0x000042FF;
				if (arg3 == 1)
				{
					var14 = ((int *) arg2)[6];
					var2 = (var14 + (var12 << 0x00000004)) + 0x00000200;
				}
				else
				{
					var13 = ((int *) arg2)[7];
					var2 = (var13 + (((var12 << 0x00000004) + var12) << 0x00000002)) + 0x00000880;
				}
			}
			else
			{
				if (((arg1 & 0xFFE00000) | (0 & 0x001FFFFF)) == 0xBD800000)
				{
					var9 = (arg1 >> 0x00000010) & 0x0000427F;
					if (arg3 == 1)
					{
						var11 = ((int *) arg2)[6];
						var2 = (var11 + (var9 << 0x00000004)) + 0x00000400;
					}
					else
					{
						var10 = ((int *) arg2)[7];
						var2 = (var10 + (((var9 << 0x00000004) + var9) << 0x00000002)) + 0x00001100;
					}
				}
				else
				{
					if (var1 == 0xBD100000)
					{
						var6 = (arg1 >> 0x00000010) & 0x000042EF;
						if (arg3 == 1)
						{
							var8 = ((int *) arg2)[6];
							var2 = (var8 + (var6 << 0x00000004)) + 0x00000300;
						}
						else
						{
							var7 = ((int *) arg2)[7];
							var2 = (var7 + (((var6 << 0x00000004) + var6) << 0x00000002)) + 0x00000CC0;
						}
					}
					else
					{
						var2 = -1;
						if (var1 == 0xBD200000)
						{
							var3 = (arg1 >> 0x00000010) & 0x000042DF;
							if (arg3 == 1)
							{
								var5 = ((int *) arg2)[6];
								var2 = (var5 + (var3 << 0x00000004)) + 0x00000600;
							}
							else
							{
								var4 = ((int *) arg2)[7];
								var2 = (var4 + (((var3 << 0x00000004) + var3) << 0x00000002)) + 0x00001980;
							}
						}
					}
				}
			}
		}
	}
	return var2;
}
//0x00001DEC
void sub_01DEC (int arg1, int arg2, int arg3, int arg4, int arg5){
	var1 = ((int *) arg1)[1];
	((int *) arg5)[0] = 0;
	var2 = 0x806101FE;
	if (!(var1 == -1))
	{
		var3 = ((int *) arg1)[3];
		var2 = 0;
		if (!(((arg2<var3)) == 0))
		{
			var4 = var1;
			if (!(arg2 <= 0))
			{
				var5 = arg2;
				while (1) {
					var5 = var5 + -1;
					var4 = ((int *) var4)[0];
					if (var5 != 0)
						continue;
					break;
				}
			}
			var6 = MIN ((var3 - arg2), arg3);
			var7 = 0;
			if (!(var6 <= 0))
			{
				var8 = 0;
				while (1) {
					var9 = var8 + arg4;
					var10 = var4 + 0x00000008;
					while (1) {
						var11 = ((int *) var10)[0];
						var12 = ((int *) var10)[1];
						var13 = ((int *) var10)[2];
						var14 = ((int *) var10)[3];
						((int *) var9)[0] = var11;
						var10 = var10 + 0x00000010;
						var9 = var9 + 0x00000010;
						((int *) var9)[1073741821] = var12;
						((int *) var9)[1073741822] = var13;
						((int *) var9)[1073741823] = var14;
						if (var10 != (var4 + 0x00000028))
							continue;
						break;
					}
					var15 = ((int *) var10)[0];
					var16 = ((int *) var10)[1];
					var17 = ((int *) var10)[2];
					((int *) var9)[0] = var15;
					((int *) var9)[1] = var16;
					((int *) var9)[2] = var17;
					var7 = var7 + 1;
					var4 = ((int *) var4)[0];
					var8 = var8 + 0x0000002C;
					if (((var7<var6)) != 0)
						continue;
					break;
				}
			}
			((int *) arg5)[0] = var6;
			var2 = 0;
		}
	}
	return;
}
//0x00001EB4
void sub_01EB4 (int arg1, int arg2, int arg3){
	var1 = ((int *) arg1)[1];
	((int *) arg3)[0] = 0;
	var2 = 0x806101FE;
	if (!(var1 == -1))
	{
		var3 = ((int *) arg1)[3];
		var4 = var1;
		var5 = MIN (var3, arg2);
		var6 = var3;
		var7 = var5;
		if (!(var5 <= 0))
		{
			while (1) {
				var8 = ((int *) var4)[0];
				var9 = var6 + -1;
				var7 = var7 + -1;
				((int *) var4)[0] = -1;
				var6 = var9;
				((int *) var4)[1] = -1;
				var4 = var8;
				((int *) arg1)[3] = var9;
				if (var7 != 0)
					continue;
				break;
			}
		}
		((int *) arg3)[0] = var5;
		var10 = ((int *) arg1)[3];
		((int *) arg1)[1] = var4;
		if (!(var10 != 0))
		{
			((int *) arg1)[1] = -1;
			((int *) arg1)[0] = -1;
		}
		var2 = 0;
	}
	return;
}
//0x00001F34
int sub_01F34 (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFF60;
	sp[34] = s6;
	var1 = arg4;
	sp[29] = s1;
	var2 = arg2;
	sp[28] = s0;
	sp[37] = ra;
	sp[36] = fp;
	sp[35] = s7;
	sp[33] = s5;
	sp[32] = s4;
	sp[31] = s3;
	sp[30] = s2;
	var3 = ((int *) arg1)[0];
	var6 = checkMpegArg (arg1);
	var7 = var6;
	if (var6 != 0)
	{

	label64:
		ra = sp[37];
	}
	else
	{
		((int *) var1)[0] = 0;
		var8 = ((int *) var2)[4];
		var7 = 0x806101FE;
		if (var8 != 0x00000800)
			goto label64;
		var11 = sub_0301C (var2);
		var12 = ((int *) var2)[4];
		var13 = ((MIN (arg3, var11)) * var12);
		var7 = 0;
		if (!(var13 != 0))
			goto label64;
		var23 = ((int *) var3)[411];
		var24 = var13 << 3;
		var25 = sp;
		waitSema();
		var28 = ((int *) var2)[4];
		var29 = ((int *) var2)[1];
		var30 = ((int *) var2)[0];
		var31 = ((int *) var2)[5];
		var32 = sp;
		sp[0] = 0;
		var33 = var31 + (var29 * var28);
		sp[3] = var33;
		var34 = (var30 * var28);
		sp[6] = (var31 + var34);
		sp[7] = var34;
		sp[2] = var33;
		sp[4] = 0;
		sp[1] = 0;
		sp[5] = var31;
		sub_0229C (var32, 0);
		var37 = sp[0];
		var38 = var25;
		if (var37 == 0x000001BA)
		{

		label21:
			var88 = sp + 0x00000020;
			sub_023B0 (var38, var88);
			var37 = ((int *) var25)[0];
			goto label14;
		}

	label14:
		var39 = ((int *) var25)[1];
		var40 = 0;
		var41 = 0;
		while (1) {
			if ((var37 >> 0x00000008) != 1)
				break;
			if (var37 == 0x000001BA)
				break;
			if (var37 == 0x000001B9)
				break;
			var42 = sp + 0x00000020;
			if (((var39<var24)) == 0)
				break;
			var43 = var42 + 0x00000018;
			var46 = sub_02554 (var25, var43);
			if (var46<0)
				goto label49;
			var39 = ((int *) var25)[1];
			if (((var24<var39)) != 0)
			{
				var37 = ((int *) var25)[0];

			label63:
				var40 = var40 + 1;
				var41 = var41 + 0x00000034;
				continue;
			}
			else
			{
				var47 = sp[14];
				var50 = checkAu (var47, var3, 1);
				var51 = var50;
				if (var50 == -1)
				{

				label60:
					var74 = ((int *) var2)[4];
					if (var74 == 0)
					{
						__asm__ ("break			0x00007;");
					}
					((int *) var1)[0] = ((var39 >> 3) / var74);
					var37 = ((int *) var25)[0];
					goto label63;
				}
				else
				{
					var52 = ((int *) var50)[2];
					if (var52 == -1)
						goto label60;
					var53 = ((int *) var2)[4];
					var54 = ((int *) var1)[0];
					if (var53 == 0)
					{
						__asm__ ("break			0x00007;");
					}
					var55 = ((int *) var2)[1];
					var56 = ((int *) var2)[0];
					var57 = ((int *) var3)[5];
					var58 = var55 + ((var54 * var53) / var53);
					if (((var40<0x00000002)) == 0)
						goto label49;
					var59 = ((int *) var51)[0];
					var60 = (var57 + ((!(((var58<var56))) ? (var58 - var56) : var58) * 0x00000068)) + var41;
					((int *) var60)[0] = -1;
					((int *) var60)[1] = var59;
					var61 = ((int *) var51)[0];
					if (var61 != -1)
					{
						((int *) var61)[0] = var60;
					}
					((int *) var51)[0] = var60;
					var62 = var43;
					var63 = sp + 0x00000020;
					var64 = var60 + 0x00000008;
					while (1) {
						var65 = ((int *) var62)[0];
						var66 = ((int *) var62)[1];
						var67 = ((int *) var62)[2];
						var68 = ((int *) var62)[3];
						((int *) var64)[0] = var65;
						var62 = var62 + 0x00000010;
						var64 = var64 + 0x00000010;
						((int *) var64)[1073741821] = var66;
						((int *) var64)[1073741822] = var67;
						((int *) var64)[1073741823] = var68;
						if (var62 != (var63 + 0x00000038))
							continue;
						break;
					}
					var69 = ((int *) var62)[0];
					var70 = ((int *) var62)[1];
					var71 = ((int *) var62)[2];
					((int *) var64)[0] = var69;
					((int *) var64)[1] = var70;
					((int *) var64)[2] = var71;
					var72 = ((int *) var51)[1];
					if (var72 == -1)
					{
						var75 = ((int *) var51)[0];
						((int *) var51)[1] = var75;
					}
					var73 = ((int *) var51)[3];
					((int *) var51)[3] = (var73 + 1);
					var39 = ((int *) var25)[1];
					goto label60;
				}
			}
			goto label65;
		}
		if (((var39<var24)) != 0)
		{
			var38 = var25;
			if (var37 == 0x000001BA)
				goto label21;
			var83 = ((int *) var3)[411];
			signalSema();
			var86 = ((int *) var25)[1];
			var87 = ((int *) var2)[4];
			var7 = 0x80618007;
			if (var87 == 0)
			{
				__asm__ ("break			0x00007;");
			}
			if (((var86 >> 3) % var87) == 0)
			{
				var7 = 0;
				goto label64;
			}
			else
			{
				ra = sp[37];
			}
		}
		else
		{
			var79 = ((int *) var2)[4];
			if (var79 == 0)
			{
				__asm__ ("break			0x00007;");
			}
			if (((var39 >> 3) % var79) != 0)
			{

			label49:
				var76 = ((int *) var3)[411];
				signalSema();
				var7 = 0x80618007;
			}
			else
			{
				var80 = ((int *) var3)[411];
				signalSema();
				var7 = 0;
			}
			goto label64;
		}
	}

label65:
	var14 = sp[36];
	var15 = sp[35];
	var16 = sp[34];
	var17 = sp[33];
	var18 = sp[32];
	var19 = sp[31];
	var20 = sp[30];
	var21 = sp[29];
	var22 = sp[28];
	sp = sp + 0x000000A0;
	return var7;
}
//0x0000229C
void sub_0229C (int arg1, int arg2){
	var1 = arg1;
	var2 = arg2;
	while (1) {
		if (((var2<0x00000019)) != 0)
			break;
		var3 = ((int *) var1)[4];
		var4 = ((int *) var1)[0];
		var5 = var3 + 0xFFFFFFE8;
		((int *) var1)[0] = (var4 << 0x00000018);
		((int *) var1)[4] = var5;
		if (!(((var5<0x00000019)) == 0))
		{
			var6 = ((int *) var1)[6];
			while (1) {
				var7 = ((int *) var1)[3];
				var8 = ((int *) var1)[4];
				var9 = ((int *) var1)[0];
				var10 = ((unsigned char *) var7)[0];
				var11 = var7 + 1;
				var12 = var8 + 0x00000008;
				((int *) var1)[0] = (var9 | (var10 << (0x00000018 - var8)));
				((int *) var1)[3] = var11;
				if (!(((var11<var6)) != 0))
				{
					var13 = ((int *) var1)[5];
					((int *) var1)[3] = var13;
				}
				((int *) var1)[4] = var12;
				if (((var12<0x00000019)) != 0)
					continue;
				break;
			}
		}
		var14 = ((int *) var1)[1];
		var2 = var2 + 0xFFFFFFE8;
		((int *) var1)[1] = (var14 + 0x00000018);
		continue;
	}
	var15 = ((int *) var1)[4];
	var16 = ((int *) var1)[0];
	var17 = var15 - var2;
	((int *) var1)[0] = (var16 << var2);
	((int *) var1)[4] = var17;
	if (!(((var17<0x00000019)) == 0))
	{
		var18 = ((int *) var1)[6];
		while (1) {
			var19 = ((int *) var1)[3];
			var20 = ((int *) var1)[4];
			var21 = ((int *) var1)[0];
			var22 = ((unsigned char *) var19)[0];
			var23 = var19 + 1;
			var24 = var20 + 0x00000008;
			((int *) var1)[0] = (var21 | (var22 << (0x00000018 - var20)));
			((int *) var1)[3] = var23;
			if (!(((var23<var18)) != 0))
			{
				var25 = ((int *) var1)[5];
				((int *) var1)[3] = var25;
			}
			((int *) var1)[4] = var24;
			if (((var24<0x00000019)) != 0)
				continue;
			break;
		}
	}
	var26 = ((int *) var1)[1];
	((int *) var1)[1] = (var26 + var2);
	return;
}
//0x000023B0
void sub_023B0 (int arg1, int arg2){
	sp = sp + 0xFFFFFFE0;
	sp[6] = s6;
	var1 = arg2;
	sp[4] = s4;
	var2 = arg1;
	sp[7] = ra;
	sp[5] = s5;
	sp[3] = s3;
	sp[2] = s2;
	sp[1] = s1;
	sp[0] = s0;
	sub_0229C (arg1, 0x00000022);
	var5 = ((int *) var2)[0];
	sub_0229C (var2, 3);
	sub_0229C (var2, 1);
	var10 = ((int *) var2)[0];
	sub_0229C (var2, 0x0000000F);
	sub_0229C (var2, 1);
	var15 = ((int *) var2)[0];
	sub_0229C (var2, 0x0000000F);
	sub_0229C (var2, 1);
	var20 = ((int *) var2)[0];
	sub_0229C (var2, 0x00000009);
	((int *) var1)[0] = (var20 >> 0x00000017);
	sub_0229C (var2, 0x0000001E);
	var25 = ((int *) var2)[0];
	var26 = var25 >> 0x0000001D;
	sub_0229C (var2, 3);
	((int *) var1)[1] = ((((var5 >> 0x0000001D) << 0x0000001E) | ((var10 >> 0x00000011) << 0x0000000F)) | (var15 >> 0x00000011));
	var29 = 0;
	((int *) var1)[2] = (var5 >> 0x0000001F);
	if (var26 != 0)
	{
		var47 = var2;
		while (1) {
			var29 = var29 + 1;
			sub_0229C (var47, 0x00000008);
			var47 = var2;
			if (((var29<var26)) != 0)
				continue;
			break;
		}
		var30 = ((int *) var2)[0];
	}
	else
	{
		var30 = ((int *) var2)[0];
	}
	if (var30 == 0x000001BB)
	{
		((int *) var1)[3] = 1;
		sub_0229C (var2, 0x00000038);
		sub_0229C (var2, 0x00000028);
		var42 = ((int *) var2)[0];
		ra = sp[7];
		if (!((var42 >> 0x0000001F) != 1))
		{
			var43 = var2;
			while (1) {
				sub_0229C (var43, 0x00000018);
				var46 = ((int *) var2)[0];
				var43 = var2;
				if ((var46 >> 0x0000001F) == 1)
					continue;
				break;
			}
			ra = sp[7];
		}
	}
	else
	{
		((int *) var1)[3] = 0;
		ra = sp[7];
	}
	var31 = sp[6];
	var32 = sp[5];
	var33 = sp[4];
	var34 = sp[3];
	var35 = sp[2];
	var36 = sp[1];
	var37 = sp[0];
	sp = sp + 0x00000020;
	return;
}
//0x00002554
int sub_02554 (int arg1, int arg2){
	sp = sp + 0xFFFFFFC0;
	sp[9] = s5;
	var1 = arg2;
	sp[8] = s4;
	sp[13] = ra;
	sp[12] = fp;
	sp[11] = s7;
	sp[10] = s6;
	sp[7] = s3;
	sp[6] = s2;
	sp[5] = s1;
	sp[4] = s0;
	var2 = ((int *) arg1)[1];
	var3 = ((int *) arg1)[2];
	var4 = ((int *) arg1)[6];
	var5 = var3 + (var2 >> 3);
	var6 = arg1;
	if (!(((var5<var4)) != 0))
	{
		var7 = ((int *) arg1)[7];
		var5 = var5 - var7;
	}
	((int *) var1)[9] = var5;
	sub_0229C (arg1, 0x00000018);
	var10 = ((unsigned char *) var6)[3];
	sub_0229C (var6, 0x00000008);
	((int *) var1)[0] = (var10 << 0x00000018);
	var13 = ((unsigned short *) var6)[1];
	sub_0229C (var6, 0x00000010);
	var16 = ((int *) var1)[0];
	((int *) var1)[1] = var13;
	((int *) var1)[4] = -1;
	((int *) var1)[5] = -1;
	((int *) var1)[3] = -1;
	((int *) var1)[6] = -1;
	if ((((0<(var16 ^ 0xBC000000))) & ((0<(var16 ^ 0xBE000000)))) == 0)
	{

	label17:
		if (((((var16 ^ 0xBC000000)<1)) | (((var16 ^ 0xBF000000)<1))) != 0)
		{

		label23:
			var165 = ((int *) var1)[1];
			if (var16 == 0xBF000000)
			{
				var166 = ((int *) var6)[1];
				var167 = ((int *) var6)[2];
				var168 = ((int *) var6)[6];
				var169 = var167 + (var166 >> 3);
				if (((var169<var168)) != 0)
				{
					((int *) var1)[8] = var165;
				}
				else
				{
					var170 = ((int *) var6)[7];
					var169 = var169 - var170;
					((int *) var1)[8] = var165;
				}
				var171 = ((int *) var6)[0];
				((int *) var1)[7] = var169;
				var165 = var165 + 0xFFFFFFFD;
				sub_0229C (var6, 0x00000018);
				var174 = ((int *) var1)[0];
				((int *) var1)[0] = (var174 | (var171 >> 0x00000008));
			}
			if (var165 == 0)
			{
				var65 = 1;
			}
			else
			{
				var66 = ((int *) var6)[1];
				var67 = var165 << 3;

			label155:
				var68 = ((int *) var6)[2];
				var69 = var66 + var67;
				var70 = ((int *) var6)[6];
				var71 = var68 + (var69 >> 3);
				((int *) var6)[0] = 0;
				((int *) var6)[4] = 0;
				((int *) var6)[1] = var69;
				((int *) var6)[3] = var71;
				if (!(((var71<var70)) != 0))
				{
					var72 = ((int *) var6)[7];
					((int *) var6)[3] = (var71 - var72);
				}
				sub_0229C (var6, 0);
				var65 = 1;
			}
		}
		else
		{
			if (var16 == 0xF0000000)
				goto label23;
			if (var16 == 0xF1000000)
				goto label23;
			if (var16 == 0xFF000000)
				goto label23;
			if (var16 == 0xF2000000)
				goto label23;
			if (var16 == 0xF8000000)
				goto label23;
			var65 = 1;
			if (!(var16 != 0xBE000000))
			{
				var164 = ((int *) var1)[1];
				if (var164 == 0)
				{
					var65 = 1;
				}
				else
				{
					var66 = ((int *) var6)[1];
					var67 = var164 << 3;
					goto label155;
				}
			}
		}
	}
	else
	{
		if (var16 == 0xBF000000)
			goto label17;
		if (var16 == 0xF0000000)
			goto label17;
		if (var16 == 0xF1000000)
			goto label17;
		if (var16 == 0xFF000000)
			goto label17;
		if (var16 == 0xF2000000)
			goto label17;
		if (var16 == 0xF8000000)
			goto label17;
		sub_0229C (var6, 0x00000002);
		var19 = ((int *) var6)[0];
		sub_0229C (var6, 0x00000002);
		((int *) var1)[2] = (var19 >> 0x0000001E);
		sub_0229C (var6, 0x00000004);
		var24 = ((int *) var6)[0];
		var25 = var24 >> 0x0000001E;
		sub_0229C (var6, 0x00000002);
		var28 = ((int *) var6)[0];
		sp[1] = (var28 >> 0x0000001F);
		sub_0229C (var6, 1);
		var31 = ((int *) var6)[0];
		var32 = var31 >> 0x0000001C;
		sub_0229C (var6, 0x00000004);
		var35 = ((int *) var6)[0];
		var36 = var35 >> 0x0000001F;
		sub_0229C (var6, 1);
		var39 = ((unsigned char *) var6)[3];
		sp[2] = var39;
		sub_0229C (var6, 0x00000008);
		var42 = ((int *) var6)[1];
		sp[0] = var42;
		if ((var25 & 0x00000002) != 0)
		{
			sub_0229C (var6, 0x00000004);
			var149 = ((int *) var6)[0];
			sub_0229C (var6, 3);
			sub_0229C (var6, 1);
			var154 = ((int *) var6)[0];
			sub_0229C (var6, 0x0000000F);
			sub_0229C (var6, 1);
			var159 = ((int *) var6)[0];
			sub_0229C (var6, 0x0000000F);
			sub_0229C (var6, 1);
			((int *) var1)[4] = ((((var149 >> 0x0000001D) << 0x0000001E) | ((var154 >> 0x00000011) << 0x0000000F)) | (var159 >> 0x00000011));
			((int *) var1)[3] = (var149 >> 0x0000001F);
		}
		if (var25 == 3)
		{
			sub_0229C (var6, 0x00000004);
			var132 = ((int *) var6)[0];
			sub_0229C (var6, 3);
			sub_0229C (var6, 1);
			var137 = ((int *) var6)[0];
			sub_0229C (var6, 0x0000000F);
			sub_0229C (var6, 1);
			var142 = ((int *) var6)[0];
			sub_0229C (var6, 0x0000000F);
			sub_0229C (var6, 1);
			((int *) var1)[6] = ((((var132 >> 0x0000001D) << 0x0000001E) | ((var137 >> 0x00000011) << 0x0000000F)) | (var142 >> 0x00000011));
			((int *) var1)[5] = (var132 >> 0x0000001F);
		}
		else
		{
		}
		var43 = sp[1];
		if (var43 == 1)
		{
			sub_0229C (var6, 0x00000030);
		}
		if (var32 != 0)
		{
			var125 = ((unsigned char *) (var32 + 0x00007618))[0];
			sub_0229C (var6, var125);
		}
		if (var36 == 1)
		{
			var88 = ((int *) var6)[0];
			sub_0229C (var6, 1);
			var91 = ((int *) var6)[0];
			sub_0229C (var6, 1);
			var94 = ((int *) var6)[0];
			sub_0229C (var6, 1);
			var97 = ((int *) var6)[0];
			sub_0229C (var6, 1);
			sub_0229C (var6, 3);
			var102 = ((int *) var6)[0];
			sub_0229C (var6, 1);
			if ((var88 >> 0x0000001F) == var36)
			{
				sub_0229C (var6, 0x00000030);
				sub_0229C (var6, 0x00000030);
				sub_0229C (var6, 0x00000020);
			}
			else
			{
			}
			var65 = 0x80618007;
			if (!((var91 >> 0x0000001F) == 1))
			{
				if ((var94 >> 0x0000001F) == 1)
				{
					sub_0229C (var6, 0x00000010);
				}
				if ((var97 >> 0x0000001F) == 1)
				{
					sub_0229C (var6, 0x00000010);
				}
				if ((var102 >> 0x0000001F) != var36)
				{
					var44 = ((int *) var6)[1];
				}
				else
				{
					sub_0229C (var6, 1);
					var107 = ((int *) var6)[0];
					var108 = var107 >> 0x00000019;
					sub_0229C (var6, 0x00000007);
					var111 = 0;
					if (var108 == 0)
					{

					label139:
						var44 = ((int *) var6)[1];
					}
					else
					{
						var112 = var6;
						while (1) {
							var111 = var111 + 1;
							sub_0229C (var112, 0x00000008);
							if (!(((var111<var108)) != 0))
								break;
							var112 = var6;
							continue;
						}
						var44 = ((int *) var6)[1];
					}
				}
				var45 = sp[0];
				var46 = sp[2];
				var47 = var46 - ((var44 - var45) >> 3);
				if (var47 == 0)
				{
					var55 = ((int *) var1)[1];
				}
				else
				{
					var48 = ((int *) var6)[2];
					var49 = var44 + (var47 << 3);
					var50 = ((int *) var6)[6];
					var51 = var48 + (var49 >> 3);
					((int *) var6)[0] = 0;
					((int *) var6)[4] = 0;
					((int *) var6)[1] = var49;
					((int *) var6)[3] = var51;
					if (!(((var51<var50)) != 0))
					{
						var52 = ((int *) var6)[7];
						((int *) var6)[3] = (var51 - var52);
					}
					sub_0229C (var6, 0);
					var55 = ((int *) var1)[1];
				}
				var56 = sp[2];
				var57 = ((int *) var6)[2];
				var58 = ((int *) var6)[6];
				var59 = var55 - var56;
				var60 = var59 + 0xFFFFFFFD;
				((int *) var1)[8] = var60;
				var61 = ((int *) var6)[1];
				var62 = var57 + (var61 >> 3);
				var63 = ((int *) var1)[0];
				if (!(((var62<var58)) != 0))
				{
					var64 = ((int *) var6)[7];
					var62 = var62 - var64;
				}
				((int *) var1)[7] = var62;
				if (var63 == 0xBD000000)
				{
					var84 = ((int *) var6)[0];
					sub_0229C (var6, 0x00000018);
					var87 = ((int *) var1)[0];
					var60 = var59 + 0xFFFFFFFA;
					((int *) var1)[0] = (var87 | (var84 >> 0x00000008));
				}
				var65 = 1;
				if (!(var60 == 0))
				{
					var66 = ((int *) var6)[1];
					var67 = var60 << 3;
					goto label155;
				}
			}
		}
		else
		goto label139;
	}
	ra = sp[13];
	var75 = sp[12];
	var76 = sp[11];
	var77 = sp[10];
	var78 = sp[9];
	var79 = sp[8];
	var80 = sp[7];
	var81 = sp[6];
	var82 = sp[5];
	var83 = sp[4];
	sp = sp + 0x00000040;
	return var65;
}
int mpegRingbufferPut (int arg1, int arg2, int arg3){
	if ((buf=sub_02C40 (arg1, arg2, arg3))<0))return buf;
	if(ret = sub_01F34 (arg1[10], arg1, buf, sp))return ret;
	return sub_03084 (arg1, buf);
}
//0x00002C40
int sub_02C40 (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFFE0;
	sp[2] = s2;
	var1 = arg1;
	sp[1] = s1;
	sp[0] = s0;
	sp[7] = ra;
	sp[6] = s6;
	sp[5] = s5;
	sp[4] = s4;
	sp[3] = s3;
	var2 = ((int *) arg1)[10];
	var3 = ((int *) var2)[0];
	var6 = checkMpegArg (var2);
	var7 = var6;
	if (var6 == 0)
	{
		var15 = ((int *) var3)[411];
		var16 = MIN (arg2, arg3);
		var17 = ((int *) var1)[6];
		var18 = 0;
		waitSema();
		if (var16 <= 0)
		{

		label30:
			var45 = ((int *) var3)[411];
			signalSema();
			var7 = var18;
		}
		else
		{
			var21 = ((int *) var1)[0];
			var22 = ((int *) var1)[2];
			while (1) {
				if (var17 == 0)
				{
					var51 = ((int *) var3)[411];
					signalSema();
					var7 = 0x80610103;
				}
				else
				{
					var23 = ((int *) var3)[411];
					signalSema();
					var26 = ((int *) var1)[11];
					var27 = gp;
					gp = var26;
					var28 = ((int *) var1)[4];
					var29 = ((int *) var1)[2];
					var30 = ((int *) var1)[5];
					var31 = ((int *) var1)[7];
					var34 var35 = (*var17) ((var30 + (var29 * var28)), ((((var21<(var22 + var16)))) ? (var21 - var22) : var16), var31);
					var36 = var34;
					var37 = gp;
					gp = var27;
					var38 = ((int *) var3)[411];
					waitSema();
					if (var36<0)
					{
						if (var18 <= 0)
						{
							var48 = ((int *) var3)[411];
							signalSema();
							var7 = var36;
						}
						else
						{
							var36 = 0;

						label25:
							var41 = ((int *) var1)[2];
							var42 = ((int *) var1)[0];
							var18 = var18 + var36;
							var43 = var41 + var36;
							var16 = var16 - var36;
							var21 = var42;
							((int *) var1)[2] = var43;
							if (var43 == var42)
							{
								((int *) var1)[2] = 0;
							}
							var44 = ((int *) var1)[3];
							((int *) var1)[3] = (var44 + var36);
							if (var36 == 0)
								break;
							if (!(var16 > 0))
								break;
							var22 = ((int *) var1)[2];
							continue;
						}
					}
					else
					goto label25;
				}
				goto label33;
			}
			goto label30;
		}
	}

label33:
	ra = sp[7];
	var8 = sp[6];
	var9 = sp[5];
	var10 = sp[4];
	var11 = sp[3];
	var12 = sp[2];
	var13 = sp[1];
	var14 = sp[0];
	sp = sp + 0x00000020;
	return var7;
}
//0x00002DC8
int mpegRingbufferAvailableSize (int arg1){
	var1 = arg1;
	var2 = ((int *) arg1)[10];
	var3 = ((int *) var2)[0];
	if (ret=checkMpegArg (var2))return ret;
	var11 = ((int *) var3)[411];
	waitSema();
	var14 = ((int *) var1)[3];
	var15 = ((int *) var1)[0];
	var16 = 0;
	if (var14 == var15)
	{
		var36 = ((int *) var3)[411];
		signalSema();
		var6 = 0;
	}
	else
	{
		var17 = ((int *) var1)[1];
		sp[0] = var17;
		var18 = ((int *) var3)[6];
		while (1) {
			var19 = var18 + (var16 << 0x00000004);
			var20 = ((int *) var19)[2];
			var16 = var16 + 1;
			if (var20 == -1)
			{

			label18:
				var23 = (var16<0x00000070);

			label19:
				if (var23 != 0)
				{
					var18 = ((int *) var3)[6];
					continue;
				}
				else
				{
					var24 = sp[0];
				}
			}
			else
			{
				var21 = ((int *) var19)[1];
				var22 = sp;
				if (!(var21 != -1))
					goto label18;
				var33 = ((int *) var21)[9];
				sub_0313C (var1, var22, var33);
				var24 = sp[0];
				var23 = (var16<0x00000070);
				if (var24 != -1)
					goto label19;
				break;
			}
			goto label22;
		}

	label22:
		if (var24 == -1)
		{
			var28 = ((int *) var1)[3];
			var27 = ((int *) var1)[0];
			var29 = var27 - var28;
		}
		else
		{
			var25 = ((int *) var1)[2];
			var26 = ((int *) var1)[1];
			var27 = ((int *) var1)[0];
			if (((var25<var26)) != 0)
			{

			label28:
				var28 = ((int *) var1)[3];
				var29 = var26 - var24;
			}
			else
			{
				if (!(((var26<var24)) != 0))
					goto label28;
				var28 = ((int *) var1)[3];
				var29 = (var27 - var24) + var26;
			}
		}
		var30 = ((int *) var3)[411];
		signalSema();
		var6 = ((var27 - var28) - var29);
	}
	return 0;
}
int mpegRingbufferQueryMemSize (int arg1){
	return ((arg1<<11) + (arg1*104));
}
int mpegRingbufferQueryPackNum (int arg1){
	return ((hi (arg1 * 0xF3A0D52D)) >> 0x0000000B);
}
int mpegRingbufferConstruct (int*arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	sp[7] = ra;
	if (arg4>=((arg2<<12)+(arg2*0x68)))return 0x80610022;
	waitSema(semaLib);
	arg1[5] = arg3;
	arg1[4] = 0x00000800;
	arg1[8] = (arg3 + (arg2<<12));
	arg1[0] = arg2;
	arg1[6] = arg5;
	arg1[7] = arg6;
	arg1[3] = 0;
	arg1[2] = 0;
	arg1[1] = 0;
	arg1[10] = 0;
	arg1[11] = gp;
	signalSema(semaLib);
	return 0;
}
int mpegRingbufferDestruct(){
	return 0;
}
int sub_0301C (int arg1){
	if (ret=checkMpegArg (*arg1[10]))return ret;
	waitSema((*arg1[10][411]);
	ret = arg1[3];
	signalSema(*arg1[10][411]);
	return ret;
}
//0x00003084
int sub_03084 (int arg1, int arg2){
	sp = sp + 0xFFFFFFF0;
	sp[1] = s1;
	sp[0] = s0;
	var1 = arg1;
	sp[3] = ra;
	sp[2] = s2;
	var2 = ((int *) arg1)[10];
	var3 = ((int *) var2)[0];
	var6 = checkMpegArg (var2);
	var7 = var6;
	if (var6 == 0)
	{
		var11 = ((int *) var3)[411];
		waitSema();
		var14 = ((int *) var1)[3];
		var15 = MIN (arg2, var14);
		var16 = var15;
		if (!(var15 <= 0))
		{
			var17 = ((int *) var1)[0];
			var18 = ((int *) var1)[1];
			while (1) {
				var19 = !(((var17<(var18 + var16)))) ? var16 : (var17 - var18);
				var20 = var18 + var19;
				var16 = var16 - var19;
				((int *) var1)[1] = var20;
				if (var20 == var17)
				{
					((int *) var1)[1] = 0;
				}
				if (!(var16 > 0))
					break;
				var18 = ((int *) var1)[1];
				continue;
			}
		}
		((int *) var1)[3] = (var14 - var15);
		var21 = ((int *) var3)[411];
		signalSema();
		var7 = var15;
	}
	ra = sp[3];
	var8 = sp[2];
	var9 = sp[1];
	var10 = sp[0];
	sp = sp + 0x00000010;
	return var7;
}
//0x0000313C
void sub_0313C (int arg1, int arg2, int arg3){
	var1 = ((int *) arg1)[5];
	var2 = ((int *) arg1)[4];
	var3 = arg3 - var1;
	if (var2 == 0)
	{
		__asm__ ("break			0x00007;");
	}
	var4 = ((int *) arg1)[2];
	var5 = (var3 / var2);
	if (((((var5 ^ var4)<1)) & ((0<var3))) == 0)
	{
		var6 = ((int *) arg1)[1];
		if (((var4<var6)) == 0)
		{
			var9 = ((int *) arg2)[0];
			if (((var4<var5)) == 0)
			{
				if (!(((var6<var9)) != 0))
				{
					if (!(((var5<var6)) == 0))
					{
						if (((var5<var9)) != 0)
						{
							((int *) arg2)[0] = var5;
						}
						else
						{
						}
					}
				}

			label17:
			}
			else
			{
				var8 = (var5<var9);
				if (((var6<var9)) == 0)
				{

				label18:
					((int *) arg2)[0] = var5;
				}
				else
				{

				label16:
					if (var8 == 0)
						goto label17;
					goto label18;
				}
			}
		}
		else
		{
			var7 = ((int *) arg2)[0];
			var8 = (var5<var7);
			goto label16;
		}
	}
	else
	{
		((int *) arg2)[0] = -1;
	}
	return;
}
//0x000031EC
int sub_031EC (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFF70;
	sp[13] = arg1;
	sp[27] = s3;
	var1 = arg2;
	sp[33] = ra;
	sp[32] = fp;
	sp[31] = s7;
	sp[30] = s6;
	sp[29] = s5;
	sp[28] = s4;
	sp[26] = s2;
	sp[25] = s1;
	sp[24] = s0;
	var2 = sp[13];
	var3 = ((int *) arg2)[0];
	sp[14] = arg3;
	var4 = ((int *) var2)[0];
	sp[15] = arg4;
	var7 = checkAu (var3, var4, 1);
	sp[19] = var7;
	var8 = sp[19];
	sp[16] = 0x80618001;
	var9 = 0x806101FE;
	if (!(var8 == -1))
	{
		var10 = sp[14];
		sp[21] = ((var10 << 0x00000002) + 0x000076A8);
		while (1) {
			var11 = sp[13];
			var12 = 0;
			var15 = sub_04D80 (var11);
			var16 = sp[19];
			var17 = sp[15];
			var18 = ((int *) var1)[9];
			var19 = ((int *) var16)[3];
			var20 = sp[13];
			var21 = ((int *) var17)[4];
			var22 = MIN (var19, 0x00000063);
			sp[20] = (var15 + 0x00000004);
			var25 = getAuSample (var20, var21);
			var26 = (var18<1);
			sp[17] = var25;
			var27 = 0;
			sp[18] = 0;
			if ((((0<var22)) & (var26 ^ 1)) == 0)
			{
				var45 = (0<var22);

			label45:
				if (((var45 ^ 1) & (var26 ^ 1)) == 0)
				{
					((int *) var1)[8] = 0;
				}
				else
				{
					var46 = ((int *) var1)[11];
					var47 = ((int *) var1)[8];
					var48 = sp[18];
					((int *) var1)[9] = var18;
					((int *) var1)[11] = (var46 + var12);
					((int *) var1)[8] = (var47 + var48);
				}
				var49 = sp[20];
				var50 = sp[15];
				((int *) (var49 + (var27 << 0x00000004)))[1073741822] = 0;
				var51 = sp[14];
				var52 = ((int *) var50)[5];
				if (((var51<0x00000007)) == 0)
				{

				label65:
					sp[16] = 0x80618007;

				label66:
					var55 = sp[18];

				label67:
					var56 = sp[19];
				}
				else
				{
					var53 = sp[21];
					var54 = ((int *) var53)[0];
					if (((var54<(var52 + var12))) == 0)
					{
						var76 = ((int *) var1)[12];
						var55 = sp[18];
						if ((var76 & 0x00000005) != 0)
							goto label67;
						var77 = sp[20];
						if ((var76 & 0x00000002) == 0)
						{

						label55:
							sub_0477C (var77);
							var80 = sp[15];
							var81 = sp[17];
							var82 = ((int *) var80)[5];
							if ((((0x003FFFFF<((var81 >> 0) & 0x1FFFFFFF))) ^ 1) == 0)
							{
								var88 = sp[17];
								sceKernelDcacheWritebackInvalidateRange (var88, (var82 + var12));
							}
							var83 = sp[20];
							var86 = sceMpegbase_BEA18F91 (var83);
							var87 = sp[16];
							sp[16] = ((var86) ? var86 : var87);
							goto label66;
						}
						else
						{
							var56 = sp[19];
							if (!(var76 >= 0))
							{
								var77 = sp[20];
								goto label55;
							}
						}
					}
					else
					{
						goto label65;
					}
				}
			}
			else
			{
				while (1) {
					var28 = sp[19];
					var29 = sp + 0x00000030;
					var30 = sp;
					sub_01DEC (var28, var27, 1, var30, var29);
					var33 = sp[15];
					var34 = ((short *) var1)[14];
					var35 = ((int *) var1)[5];
					var36 = sp[8];
					var37 = ((int *) var33)[5];
					var38 = sp[7];
					var39 = sp[17];
					var40 = var36 - (var35 + var34);
					var18 = var18 - var40;
					var41 = (var39 + var37) + var12;
					var12 = var12 + var40;
					if (var18 <= 0)
					{
						var97 = sp[18];
						if (var18 != 0)
						{
							var104 = abs (var18);
							var40 = var40 - var104;
							var107 = abs (var18);
							((short *) var1)[14] = (var40 + var34);
							var12 = var12 - var107;
						}
						else
						{
							((short *) var1)[14] = 0;
							sp[18] = (var97 + 1);
						}
						var98 = sp[18];
						if (var98 <= 0)
						{
							var100 = ((int *) var1)[8];
							if (var100 > 0)
							{
								var99 = ((int *) var1)[6];

							label29:
								((int *) var1)[13] = 0;
								((int *) var1)[6] = (var99 | 1);

							label30:
								var42 = sp[20];
							}
							else
							{
								var101 = ((int *) var1)[13];
								var42 = sp[20];
								if (!(var101 != 1))
								{
									var99 = ((int *) var1)[6];
									goto label29;
								}
							}
						}
						else
						{
							var99 = ((int *) var1)[6];
							goto label29;
						}
					}
					else
					goto label30;
					var43 = var42 + (var27 << 0x00000004);
					((int *) var43)[0] = ((var38 + var35) + var34);
					((int *) var43)[2] = (var43 + 0x00000010);
					((int *) var43)[1] = var41;
					if (((var40<0x00001000)) == 0)
					{
						sp[16] = 0x80618007;
						((int *) var43)[3] = 0;
						goto label66;
					}
					else
					{
						((int *) var43)[3] = var40;
						if (var18 <= 0)
						{
							var91 = ((int *) var1)[10];
							var27 = var27 + 1;
							if (var91 == 0)
							{

							label42:
								var45 = (var27<var22);
							}
							else
							{
								if (var91 == 0)
								{
									__asm__ ("break			0x00007;");
								}
								var92 = (var12 % var91);
								if (var92 == 0)
								{
									var45 = (var27<var22);
								}
								else
								{
									var93 = sp[20];
									var94 = var91 - var92;
									if (var91 == 0)
									{
										__asm__ ("break			0x00007;");
									}
									var95 = var93 + (var27 << 0x00000004);
									((int *) var95)[3] = (!(((var94<0x00001000))) ? 0 : var94);
									var27 = var27 + 1;
									((int *) var95)[0] = 0x00007628;
									((int *) var95)[1] = (var41 + var40);
									((int *) var95)[2] = (var95 + 0x00000010);
									var96 = ((int *) var1)[10];
									var12 = var12 + (var96 - (var12 % var96));
									goto label42;
								}
							}
							var26 = (var18<1);
							sp[16] = 0;
							((int *) var1)[11] = 0;
							goto label45;
						}
						else
						{
							var44 = sp[18];
							var27 = var27 + 1;
							var26 = (var18<1);
							var45 = (var27<var22);
							((short *) var1)[14] = 0;
							sp[18] = (var44 + 1);
							if ((var45 & (var26 ^ 1)) != 0)
								continue;
							break;
						}
					}
					goto label68;
				}
				goto label45;
			}

		label68:
			var57 = sp + 0x00000030;
			sub_01EB4 (var56, var55, var57);
			var60 = sp[13];
			sub_04DA0();
			var63 = sp[15];
			var64 = sp[16];
			var65 = ((int *) var63)[5];
			var66 = sp[15];
			((int *) var66)[5] = (var65 + var12);
			if (((((var27<0x00000063)) ^ 1) & (((var64 ^ 0x80618001)<1))) != 0)
				continue;
			break;
		}
		var9 = var64;
	}
	ra = sp[33];
	var67 = sp[32];
	var68 = sp[31];
	var69 = sp[30];
	var70 = sp[29];
	var71 = sp[28];
	var72 = sp[27];
	var73 = sp[26];
	var74 = sp[25];
	var75 = sp[24];
	sp = sp + 0x00000090;
	return var9;
}
//0x00003624
int mpegGetPcmAu (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFF90;
	sp[22] = s6;
	var1 = arg4;
	sp[19] = s3;
	var2 = arg1;
	sp[18] = s2;
	var3 = arg3;
	sp[17] = s1;
	var4 = arg2;
	sp[25] = ra;
	sp[24] = fp;
	sp[23] = s7;
	sp[21] = s5;
	sp[20] = s4;
	sp[16] = s0;
	var5 = ((int *) arg1)[0];
	var8 = checkMpegArg (arg1);
	if (var8 == 0)
	{
		var18 = ((int *) var5)[411];
		waitSema();
		var21 = ((int *) var4)[0];
		var22 = ((int *) var2)[0];
		var25 = checkAu (var21, var22, 1);
		var26 = var25;
		if (var25 == -1)
		{
			var68 = ((int *) var5)[411];
			signalSema();
			var8 = 0x806101FE;
		}
		else
		{
			var27 = sp;
			var28 = sp + 0x00000030;
			sub_01DEC (var25, 0, 1, var27, var28);
			var31 = sp[12];
			if (var31 != 1)
			{

			label21:
				var65 = ((int *) var5)[411];
				signalSema();
				var8 = 0x80618001;
			}
			else
			{
				var32 = ((int *) var4)[11];
				if (var32 != 0)
				{

				label34:
					if (!(var1 == 0))
					{
						var51 = ((int *) var4)[16];
						((int *) var1)[0] = var51;
					}
					var54 = sub_031EC (var2, var4, 0x00000002, var3);
					var55 = ((int *) var5)[411];
					var56 = var54;
					signalSema();
					var59 = ((int *) var4)[12];
					if ((((var59 >> 2) & 1) & ((var56<1))) != 0)
					{
						((int *) var4)[12] = ((var59 & 0xFFFFFFFB) | (0 & 1));
						var62 = mpegGetPcmAu (var2, var4, var3, var1);
						var56 = var62;
					}
					var8 = var56;
				}
				else
				{
					((int *) var3)[5] = 0;
					var33 = sp + 0x00000030;
					while (1) {
						var34 = sp;
						sub_01DEC (var26, 0, 1, var34, var33);
						var37 = sp[12];
						var38 = sp[7];
						if (var37 != 1)
							break;
						var39 = ((int *) var4)[6];
						if ((var39 & 1) == 0)
						{
							((int *) var3)[1] = -1;
							((int *) var3)[2] = -1;
							((int *) var3)[0] = -1;
							((int *) var3)[3] = -1;

						label33:
							var48 = ((unsigned char *) var38)[1];
							((int *) var4)[16] = var48;
							var49 = ((unsigned char *) var38)[1];
							var50 = var49 & 0x0000000F;
							((int *) var4)[9] = (((var50 << 0x00000002) + var50) << 0x00000005);
							goto label34;
						}
						else
						{
							var42 = read16 ((var38 + 0x00000002));
							((short *) var4)[14] = var42;
							var43 = sp + 0x00000030;
							if (((char) var42) == -1)
							{
								sub_01EB4 (var26, 1, var43);
								var33 = sp + 0x00000030;
								continue;
							}
							else
							{
								var44 = sp[4];
								var45 = sp[5];
								var46 = sp[6];
								var47 = sp[3];
								((int *) var3)[1] = var44;
								((int *) var3)[0] = var47;
								((int *) var3)[2] = var45;
								((int *) var3)[3] = var46;
								((int *) var4)[6] = 0;
								goto label33;
							}
						}
						goto label46;
					}
					goto label21;
				}
			}
		}
	}

label46:
	ra = sp[25];
	var9 = sp[24];
	var10 = sp[23];
	var11 = sp[22];
	var12 = sp[21];
	var13 = sp[20];
	var14 = sp[19];
	var15 = sp[18];
	var16 = sp[17];
	var17 = sp[16];
	sp = sp + 0x00000070;
	return var8;
}
//0x00003850
int sub_03850 (int arg1, int arg2, int arg3, int arg4, int arg5){
	sp = sp + 0xFFFFFF80;
	sp[27] = s7;
	var1 = arg4;
	sp[26] = s6;
	var2 = arg1;
	sp[21] = s1;
	var3 = arg2;
	sp[29] = ra;
	sp[28] = fp;
	sp[25] = s5;
	sp[24] = s4;
	sp[23] = s3;
	sp[22] = s2;
	sp[20] = s0;
	sp[17] = arg3;
	sp[18] = arg5;
	var4 = ((int *) arg1)[0];
	var7 = checkMpegArg (arg1);
	if (var7 == 0)
	{
		var17 = ((int *) var4)[411];
		waitSema();
		var20 = ((int *) var3)[0];
		var21 = ((int *) var2)[0];
		var24 = checkAu (var20, var21, 1);
		var25 = var24;
		if (var24 == -1)
		{
			var128 = ((int *) var4)[411];
			signalSema();
			var7 = 0x806101FE;
		}
		else
		{
			var26 = sp;
			var27 = sp + 0x00000040;
			sub_01DEC (var24, 0, 1, var26, var27);
			var30 = sp[16];
			if (var30 != 1)
			{
				var127 = ((int *) var4)[411];

			label40:
				signalSema();
				var7 = 0x80618001;
			}
			else
			{
				var31 = ((int *) var3)[14];
				var32 = ((int *) var3)[11];
				if (var31 != 0)
				{

				label22:
					if (var32 != 0)
					{

					label35:
						var49 = var25;

					label36:
						var54 = sp;
						var55 = sp + 0x00000040;
						sub_01DEC (var49, 0, 1, var54, var55);
						var58 = sp[16];
						var59 = sp[8];
						if (var58 != 1)
						{

						label39:
							var124 = ((int *) var4)[411];
							goto label40;
						}
						else
						{
							var60 = ((short *) var3)[14];
							var61 = ((int *) var3)[14];
							var62 = var60 + 0x00000002;
							var63 = var59 - var62;
							if (!(var61 != 0))
							{
								((int *) var3)[14] = 0x00000008;
								var61 = 0x00000008;
							}
							var64 = 0x00000008 - var61;
							var65 = sp + 0x00000030;
							var66 = var65 + var64;
							while (1) {
								if (((var63<var61)) == 0)
									break;
								var67 = sp[7];
								var66 = var66 + var63;
								strncpy (var66, (var67 + var62), var63);
								var70 = ((int *) var3)[14];
								((int *) var3)[14] = (var70 - var63);
								var71 = sp;
								var72 = sp + 0x00000040;
								sub_01DEC (var25, 1, 1, var71, var72);
								var75 = sp[16];
								var76 = sp + 0x00000040;
								var62 = 0x00000002;
								if (var75 != 1)
								{
									((int *) var3)[13] = 1;
								}
								else
								{
									var77 = ((int *) var3)[11];
									var78 = sp[8];
									((int *) var3)[11] = (var77 + var63);
									var63 = var78 + 0xFFFFFFFE;
									sub_01EB4 (var25, 1, var76);
									var61 = ((int *) var3)[14];
									continue;
								}
								goto label56;
							}
							var117 = sp[7];
							strncpy (var66, (var117 + var62), var61);
							var120 = ((unsigned short *) var3)[14];
							var121 = ((unsigned short *) var3)[28];
							var122 = ((int *) var3)[11];
							var123 = ((int *) var3)[14];
							((short *) var3)[14] = (var120 + var121);
							((int *) var3)[11] = (var122 + var123);
							((int *) var3)[14] = 0;

						label56:
							var81 = ((int *) var3)[14];
							var82 = 0x00000008 - var81;
							var83 = (var82<0x00000005);
							if (!(((var64<0x00000004)) == 0))
							{
								var84 = var82 - var64;
								if (!(var83 != 0))
								{
									var84 = 0x00000004 - var64;
								}
								var85 = sp + 0x00000030;
								strncpy (((var3 + var64) + 0x0000003C), (var85 + var64), var84);
							}
							var88 = sp[18];
							if (((var83 ^ 1) & ((0<var88))) != 0)
							{
								var112 = MAX (var64, 0x00000004);
								var113 = sp[18];
								var114 = sp + 0x00000030;
								strncpy ((var113 + var112), (var114 + var112), (var82 - var112));
								var89 = ((int *) var3)[14];
							}
							else
							{
								var89 = ((int *) var3)[14];
							}
							if (var89 == 0)
							{
								var106 = read32 ((var3 + 0x0000003C));
								var107 = sp[18];
								((int *) var3)[9] = (var106 + 0xFFFFFFFC);
								if (var107 == 0)
								{

								label71:
									var33 = sp[17];
								}
								else
								{
									var108 = LWL (var3);
									var109 = LWR (var3, var108, 0x0000003C);
									SWL (var107, var109, 3);
									SWR (var107, var109, 0);
									var110 = LWL (sp, var109, 0x00000037);
									var111 = LWR (sp, var110, 0x00000034);
									SWL (var107, var111, 0x00000007);
									SWR (var107, var111, 0x00000004);
									var33 = sp[17];
								}
							}
							else
							goto label71;

						label72:
							var90 = var2;

						label73:
							var93 = sub_031EC (var90, var3, var33, var1);
							var94 = ((int *) var4)[411];
							var95 = var93;
							signalSema();
							var98 = ((int *) var3)[12];
							if ((((var98 >> 2) & 1) & ((var95<1))) != 0)
							{
								((int *) var3)[12] = ((var98 & 0xFFFFFFFB) | (0 & 1));
								var99 = sp[17];
								var100 = sp[18];
								var103 = sub_03850 (var2, var3, var99, var1, var100);
								var95 = var103;
							}
							var7 = var95;
						}
					}
					else
					{
						((int *) var1)[5] = 0;
						var35 = var25;
						while (1) {
							var36 = sp + 0x00000040;
							var37 = sp;
							sub_01DEC (var35, 0, 1, var37, var36);
							var40 = sp[16];
							var41 = sp + 0x00000040;
							if (var40 != 1)
								goto label39;
							var42 = sp[3];
							var43 = sp[4];
							if (var42 != -1)
								break;
							var44 = sp[5];
							if (var43 != var42)
								break;
							var45 = sp[6];
							if (var44 != var43)
								break;
							if (var45 != var44)
							{
								var48 = ((int *) var3)[6];
								goto label33;
							}
							else
							{
								sub_01EB4 (var25, 1, var41);
								var35 = var25;
								continue;
							}
							goto label89;
						}
						var48 = ((int *) var3)[6];

					label33:
						var49 = var25;
						if (!((var48 & 1) == 0))
						{
							var50 = sp[4];
							var51 = sp[5];
							var52 = sp[6];
							var53 = sp[3];
							((short *) var3)[14] = 0;
							((int *) var1)[0] = var53;
							((int *) var1)[1] = var50;
							((int *) var1)[2] = var51;
							((int *) var1)[3] = var52;
							((int *) var3)[6] = 0;
							goto label35;
						}
						goto label36;
					}
				}
				else
				{
					var33 = sp[17];
					if (var32 != 0)
						goto label72;
					var34 = ((int *) var3)[13];
					if (var34 == var30)
					{
						var90 = var2;
						goto label73;
					}
					else
					{
						goto label22;
					}
				}
			}
		}
	}

label89:
	ra = sp[29];
	var8 = sp[28];
	var9 = sp[27];
	var10 = sp[26];
	var11 = sp[25];
	var12 = sp[24];
	var13 = sp[23];
	var14 = sp[22];
	var15 = sp[21];
	var16 = sp[20];
	sp = sp + 0x00000080;
	return var7;
}
//0x00003C4C
int sub_03C4C (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFF90;
	sp[24] = fp;
	var1 = arg4;
	sp[22] = s6;
	var2 = arg1;
	sp[21] = s5;
	var3 = arg3;
	sp[18] = s2;
	var4 = arg2;
	sp[25] = ra;
	sp[23] = s7;
	sp[20] = s4;
	sp[19] = s3;
	sp[17] = s1;
	sp[16] = s0;
	var5 = ((int *) arg1)[0];
	var8 = checkMpegArg (arg1);
	if (var8 == 0)
	{
		var18 = ((int *) var5)[411];
		waitSema();
		var21 = ((int *) var4)[0];
		var22 = ((int *) var2)[0];
		var25 = checkAu (var21, var22, 1);
		var26 = var25;
		if (var25 == -1)
		{
			var91 = ((int *) var5)[411];
			signalSema();
			var8 = 0x806101FE;
		}
		else
		{
			var27 = sp;
			var28 = sp + 0x00000030;
			sub_01DEC (var25, 0, 1, var27, var28);
			var31 = sp[12];
			if (var31 != 1)
			{

			label23:
				var88 = ((int *) var5)[411];
				signalSema();
				var8 = 0x80618001;
			}
			else
			{
				var32 = ((int *) var4)[11];
				if (var32 == 0)
				{
					((int *) var3)[5] = 0;

				label19:
					var35 = sp;
					while (1) {
						var36 = sp + 0x00000030;
						sub_01DEC (var26, 0, 1, var35, var36);
						var39 = sp[12];
						var40 = sp[7];
						if (var39 != 1)
							break;
						var41 = ((int *) var4)[6];
						if ((var41 & 1) == 0)
						{
							((int *) var3)[1] = -1;
							((int *) var3)[2] = -1;
							((int *) var3)[0] = -1;
							((int *) var3)[3] = -1;

						label35:
							var50 = ((short *) var4)[14];
							var51 = sp[8];
							var52 = ((int *) var4)[14];
							var53 = var50 + 0x00000004;
							var54 = var51 - var53;
							if (!(var52 != 0))
							{
								((int *) var4)[14] = 0x00000004;
								var52 = 0x00000004;
							}
							var55 = (var4 - var52) + 0x00000040;
							var56 = 1;
							while (1) {
								var57 = var40 + var53;
								if (((var54<var52)) == 0)
									break;
								var55 = var55 + var54;
								strncpy (var55, var57, var54);
								var60 = ((int *) var4)[14];
								((int *) var4)[14] = (var60 - var54);
								var61 = sp;
								var62 = sp + 0x00000030;
								sub_01DEC (var26, var56, 1, var61, var62);
								var65 = sp[12];
								var53 = 0x00000004;
								var56 = var56 + 1;
								if (var65 != 1)
								{
									((int *) var4)[9] = 0x00000004;
									((int *) var4)[13] = 1;
								}
								else
								{
									var66 = sp[8];
									var52 = ((int *) var4)[14];
									var40 = sp[7];
									var54 = var66 + 0xFFFFFFFC;
									continue;
								}
								goto label50;
							}
							strncpy (var55, var57, var52);
							((int *) var4)[14] = 0;
							var84 = sub_04CD8 ((var4 + 0x0000003C));
							var85 = ((int *) var4)[11];
							((int *) var4)[9] = ((var84 - var85) + 0x00000008);

						label50:
							var34 = var2;

						label51:
							var69 = sub_031EC (var34, var4, 1, var3);
							var70 = ((int *) var5)[411];
							var71 = var69;
							signalSema();
							var74 = (var71<1);
							if ((var74 & ((0<var1))) == 0)
							{
								var76 = ((int *) var4)[12];
							}
							else
							{
								var75 = ((int *) var3)[4];
								((int *) var1)[0] = (var75 + 0x00000008);
								var76 = ((int *) var4)[12];
							}
							if ((((var76 >> 2) & 1) & var74) != 0)
							{
								((int *) var4)[12] = ((var76 & 0xFFFFFFFB) | (0 & 1));
								var79 = sub_03C4C (var2, var4, var3, var1);
								var71 = var79;
							}
							var8 = var71;
						}
						else
						{
							var44 = read16 ((var40 + 0x00000002));
							((short *) var4)[14] = var44;
							var45 = sp + 0x00000030;
							if (((char) var44) == -1)
							{
								sub_01EB4 (var26, 1, var45);
								var35 = sp;
								continue;
							}
							else
							{
								var46 = sp[4];
								var47 = sp[5];
								var48 = sp[6];
								var49 = sp[3];
								var40 = sp[7];
								((int *) var3)[1] = var46;
								((int *) var3)[0] = var49;
								((int *) var3)[2] = var47;
								((int *) var3)[3] = var48;
								((int *) var4)[6] = 0;
								goto label35;
							}
						}
						goto label65;
					}
					goto label23;
				}
				else
				{
					var33 = ((int *) var4)[14];
					var34 = var2;
					if (var33 == 0)
						goto label51;
					goto label19;
				}
			}
		}
	}

label65:
	ra = sp[25];
	var9 = sp[24];
	var10 = sp[23];
	var11 = sp[22];
	var12 = sp[21];
	var13 = sp[20];
	var14 = sp[19];
	var15 = sp[18];
	var16 = sp[17];
	var17 = sp[16];
	sp = sp + 0x00000070;
	return var8;
}
//0x00003F48
int sub_03F48 (int arg1, int arg2, int arg3){
	var1 = ((int *) arg1)[4];
	var2 = ((int *) arg1)[0];
	var3 = ((int *) arg1)[2];
	var4 = ((int *) arg1)[1];
	var5 = ((int *) arg1)[5];
	var6 = (arg2<var5);
	var7 = var5 + (var1 * var2);
	var8 = (var7<arg2);
	var9 = var5 + (var1 * var3);
	var10 = var5 + (var1 * var4);
	if ((var6 | var8) != 0)
	{

	label20:
		var13 = 0x80618007;
	}
	else
	{
		var11 = (arg3<var5);
		var12 = (var7<arg3);
		if (!((var11 | var12) == 0))
			goto label20;
		if (((var9<var10)) != 0)
		{
			var15 = (arg2<arg3);

		label18:
			var13 = 1;
			if (!(var15 != 0))
			{
				var13 = ((arg2 ^ arg3)) ? 3 : 0x00000002;
			}
		}
		else
		{
			if (((var6 ^ 1) & (((var10<arg2)) ^ 1)) == 0)
			{
				var14 = (arg2<var9);

			label12:
				if (((var14 ^ 1) & (var8 ^ 1)) == 0)
				{

				label16:
					var13 = !(((arg2<arg3))) ? 1 : 3;
				}
				else
				{
					if (((((arg3<var9)) ^ 1) & (var12 ^ 1)) == 0)
					{
						goto label16;
					}
					else
					{
						var15 = (arg2<arg3);
						goto label18;
					}
				}
			}
			else
			{
				if (((var11 ^ 1) & (((var10<arg3)) ^ 1)) != 0)
				{
					var15 = (arg2<arg3);
					goto label18;
				}
				else
				{
					var14 = (arg2<var9);
					goto label12;
				}
			}
		}
	}
	return var13;
}
//0x0000404C
int mpegGetAvcAu (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFF60;
	sp[36] = fp;
	var1 = arg4;
	sp[35] = s7;
	var2 = arg1;
	sp[32] = s4;
	var3 = arg3;
	sp[31] = s3;
	var4 = arg2;
	sp[37] = ra;
	sp[34] = s6;
	sp[33] = s5;
	sp[30] = s2;
	sp[29] = s1;
	sp[28] = s0;
	var5 = ((int *) arg1)[0];
	var8 = checkMpegArg (arg1);
	var9 = var8;
	if (!(var8 != 0))
	{
		var10 = ((int *) var4)[2];
		var9 = 0x806101FE;
		if (!(var10 == -1))
		{
			var11 = ((int *) var5)[411];
			waitSema();
			var14 = ((int *) var4)[0];
			var15 = ((int *) var2)[0];
			var18 = checkAu (var14, var15, 1);
			if (var18 == -1)
			{

			label22:
				var128 = ((int *) var5)[411];
				signalSema();
				var9 = 0x80618001;
			}
			else
			{
				var19 = sp;
				while (1) {
					var20 = sp + 0x00000060;
					sub_01DEC (var18, 0, 1, var19, var20);
					var23 = sp[24];
					var24 = sp + 0x00000030;
					var25 = sp + 0x00000060;
					if (var23 != 1)
						break;
					var26 = ((int *) var4)[11];
					if (var26 != 0)
					{
						var79 = ((int *) var4)[3];

					label45:
						var82 = sub_04D78 (var79);
						var83 = ((int *) var4)[4];
						var86 = sub_04D54 (var82, var83);
						var89 = sub_04D0C (var86);
						if (var89 == 0)
						{
							var124 = ((int *) var4)[12];

						label61:
							var92 = (var124 & 0x7FFFFFFF) | (0 & 1);
						}
						else
						{
							var90 = ((int *) var5)[3];
							if (var90 == 0)
							{
								var119 = sub_04D78 (var79);
								var122 = sub_04D4C (var119);
								var123 = ((int *) var4)[4];
								if (var123 != (var122 + -1))
								{
									var91 = ((int *) var4)[12];

								label63:
									var92 = var91 | 0x80000000;
								}
								else
								{
									var124 = ((int *) var4)[12];
									goto label61;
								}
							}
							else
							{
								var91 = ((int *) var4)[12];
								goto label63;
							}
						}
						((int *) var4)[12] = var92;
						if (!(var1 == 0))
						{
							var93 = ((int *) var4)[12];
							((int *) var1)[0] = (var93 >> 0x0000001F);
							var96 = sub_04D00 (var86);
							var97 = ((int *) var1)[0];
							((int *) var1)[0] = (var97 | (var96 << 1));
						}
						var100 = sub_031EC (var2, var4, 0, var3);
						var101 = var100;
						if (var100 == 0)
						{
							var111 = sub_04D78 (var79);
							var114 = sub_04D4C (var111);
							var115 = ((int *) var4)[4];
							var116 = var115 + 1;
							if (!(((var115<(var114 + -1))) != 0))
							{
								var116 = 0x00007FFF;
							}
							((int *) var4)[4] = var116;
						}
						var102 = ((int *) var5)[411];
						signalSema();
						var105 = ((int *) var4)[12];
						if ((((var105 >> 2) & 1) & ((var101<1))) != 0)
						{
							((int *) var4)[12] = ((var105 & 0xFFFFFFFB) | (0 & 1));
							var108 = mpegGetAvcAu (var2, var4, var3, var1);
							var101 = var108;
						}
						var9 = var101;
					}
					else
					{
						((int *) var3)[5] = 0;
						var27 = ((int *) var4)[4];
						var28 = sp[4];
						if (var27 != 0x00007FFF)
						{
							((int *) var3)[1] = -1;
							((int *) var3)[2] = -1;
							((int *) var3)[0] = -1;
							((int *) var3)[3] = -1;

						label38:
							var68 = ((int *) var4)[3];
							var71 = sub_04D78 (var68);
							var72 = ((int *) var4)[4];
							var75 = sub_04D54 (var71, var72);
							var78 = sub_04D2C (var75);
							var79 = ((int *) var4)[3];
							((int *) var4)[9] = var78;
							goto label45;
						}
						else
						{
							var29 = sp[5];
							var30 = sp[6];
							var31 = sp[3];
							var32 = ((int *) var4)[2];
							((int *) var3)[1] = var28;
							((int *) var3)[0] = var31;
							((int *) var3)[2] = var29;
							((int *) var3)[3] = var30;
							sub_01DEC (var32, 0, 1, var24, var25);
							var35 = sp[24];
							var36 = sp[19];
							if (var35 != var23)
								break;
							var37 = ((int *) var5)[4];
							var38 = sp[7];
							var41 = sub_03F48 (var37, var38, var36);
							var42 = sp + 0x00000060;
							if (var41 != var35)
							{
								sub_01EB4 (var32, 1, var42);
								var63 = sp[20];
								if (((var63<0x00000801)) == 0)
								{
									var125 = ((int *) var5)[411];
									signalSema();
									var9 = 0x80618007;
								}
								else
								{
									var64 = ((int *) var4)[3];
									var65 = sp[19];
									strncpy (var64, var65, var63);
									((int *) var4)[4] = 0;
									((short *) var4)[14] = 0;
									goto label38;
								}
							}
							else
							{
								var43 = ((int *) var5)[411];
								signalSema();
								var48 = mpegNextAvcRpAu (var2, var4);
								if (var48 != 0)
								{
									var9 = ((var48 ^ 0x80618004)) ? var48 : 0x80618001;
								}
								else
								{
									var49 = ((int *) var5)[411];
									waitSema();
									var19 = sp;
									continue;
								}
							}
						}
					}
					goto label92;
				}
				goto label22;
			}
		}
	}

label92:
	ra = sp[37];
	var52 = sp[36];
	var53 = sp[35];
	var54 = sp[34];
	var55 = sp[33];
	var56 = sp[32];
	var57 = sp[31];
	var58 = sp[30];
	var59 = sp[29];
	var60 = sp[28];
	sp = sp + 0x000000A0;
	return var9;
}
int mpegGetAvcEsAu (int arg1, int arg2, int arg3, int arg4){
	if (ret=checkMpegArg (arg1))return ret;
	arg4[5] = 0;
	var14 = sub_04D80 (arg1);
	sp[4] = 0;
	sp[5] = var14[0];
	sp[6] = var14;
	if (ret=sub_04888 (arg1, sp, arg2, arg3, 0, arg4))return ret;
	if (ret=getAvcAu (arg1, sp, arg4))return ret;
	sp[4] = 0;
	sp[5] = sp[6][0];
	sub_04DA0();
	return 0;
}
//0x0000447C
int mpegGetAvcNalAu (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFFB0;
	sp[15] = s7;
	var1 = arg1;
	sp[14] = s6;
	var2 = arg3;
	sp[12] = s4;
	var3 = arg2;
	sp[17] = ra;
	sp[16] = fp;
	sp[13] = s5;
	sp[11] = s3;
	sp[10] = s2;
	sp[9] = s1;
	sp[8] = s0;
	var6 = checkMpegArg (arg1);
	ra = sp[17];
	if (!(var6 != 0))
	{
		((int *) var2)[5] = 0;
		var7 = ((int *) var3)[4];
		var8 = 0;
		if (var7 == 0)
		{

		label55:
			var6 = 0x806101FE;
		}
		else
		{
			if (((var7<3)) != 0)
			{

			label8:
				var20 = sub_04D80 (var1);
				sp[4] = 0;
				var21 = ((int *) var3)[7];
				var22 = ((int *) var20)[0];
				sp[6] = var20;
				sp[5] = var22;
				if ((var21 & 1) == 0)
				{

				label19:
					if ((var21 & 0x00000002) == 0)
					{
						var25 = ((int *) var3)[6];

					label30:
						var26 = ((int *) var3)[5];
						if (var25 <= 0)
						{

						label47:
							var45 = sp;
							var48 = getAvcAu (var1, var45, var2);
							var49 = var48;
							if (!(var48 != 0))
							{
								sp[4] = 0;
								var49 = 0;
								var50 = sp[6];
								var51 = ((int *) var50)[0];
								sp[5] = var51;
							}
							var35 = var49;
						}
						else
						{
							var27 = ((int *) var3)[4];
							while (1) {
								var30 = readN (var26, var27);
								var31 = ((int *) var3)[4];
								var32 = var30;
								var25 = var25 - (var31 + var30);
								var33 = sp;
								var34 = var26 + var31;
								var35 = 0x80618007;
								if (((var25 >> 0x0000001F) | ((var30<1))) != 0)
									break;
								if (var8 == 0)
								{
									var37 = 0;
								}
								else
								{
									var36 = ((unsigned char *) var34)[0];
									var37 = 1;
									if (!(((((var36 & 0x0000001F) + 0xFFFFFFF9)<0x00000002)) == 0))
									{
										var37 = 0;
									}
								}
								var40 = sub_04888 (var1, var33, (var37 + 0x000076C4), (0x00000004 - var37), 0, var2);
								var8 = 1;
								var35 = var40;
								var41 = sp;
								var26 = var34 + var32;
								if (var40 != 0)
									break;
								var44 = sub_04888 (var1, var41, var34, var32, 0, var2);
								var35 = var44;
								if (var44 != 0)
									break;
								if (!(var25 > 0))
									goto label47;
								var27 = ((int *) var3)[4];
								continue;
							}
						}
					}
					else
					{
						var24 = ((int *) var3)[2];
						if (var24 != 0)
						{
							var54 = sp;
							var57 = sub_04888 (var1, var54, 0x000076C4, 0x00000004, 0, var2);
							var35 = var57;
							if (!(var57 != 0))
							{
								var58 = ((int *) var3)[2];
								var59 = ((int *) var3)[3];
								var60 = sp;
								var63 = sub_04888 (var1, var60, var58, var59, 0, var2);
								var35 = var63;
								if (!(var63 != 0))
								{
									var8 = 1;

								label29:
									var25 = ((int *) var3)[6];
									goto label30;
								}
							}
						}
						else
						goto label29;
					}
				}
				else
				{
					var23 = ((int *) var3)[0];
					if (!(var23 != 0))
						goto label19;
					var64 = sp;
					var67 = sub_04888 (var1, var64, 0x000076C4, 0x00000004, 0, var2);
					var35 = var67;
					if (!(var67 != 0))
					{
						var68 = ((int *) var3)[0];
						var69 = ((int *) var3)[1];
						var70 = sp;
						var73 = sub_04888 (var1, var70, var68, var69, 0, var2);
						var35 = var73;
						if (!(var73 != 0))
						{
							var21 = ((int *) var3)[7];
							var8 = 1;
							goto label19;
						}
					}
				}
				sub_04DA0();
				var6 = var35;
			}
			else
			{
				if (var7 == 0x00000004)
					goto label8;
				goto label55;
			}
		}
		ra = sp[17];
	}
	var9 = sp[16];
	var10 = sp[15];
	var11 = sp[14];
	var12 = sp[13];
	var13 = sp[12];
	var14 = sp[11];
	var15 = sp[10];
	var16 = sp[9];
	var17 = sp[8];
	sp = sp + 0x00000050;
	return var6;
}
void sub_04718 (int arg1, int arg2, int arg3, int arg4, int arg5){
	arg1[0] = arg2;
	arg1[1] = arg3;
	arg1[2] = arg4;
	arg1[3] = arg5<0x1000?arg5:0;
	return arg5<0x1000?0:0x806101FE;
}
void sub_0474C (int arg1, int arg2){
	arg1[2] = arg2;
}
int queryUserdataEsSize2 (int arg1, int arg2, int arg3, int arg4){
	return sub_03850 (arg1, arg2, 3, arg3, arg4);
}
void sub_0477C (int arg1){
	for (i=0;i<0x64;i++) {
		sceKernelDcacheWritebackInvalidateRange (arg1[0], (arg1[3] & 0x00000FFF));
		if (!(arg1=arg1[2]))break;
	}
}
int getAvcAu (int arg1, int arg2, int arg3){
	if (arg2[4])return 0;
	var9 = ((int *) arg3)[4];
	var12 = getAuSample (arg1, var9);
	((int *) (arg2[7] + (arg2[4] << 4)))[0x3FFFFFFE] = 0;
	sub_0477C (arg2[7]);
	if (!(0x003FFFFF<(var12 & 0x1FFFFFFF) ^ 1))
		sceKernelDcacheWritebackInvalidateRange (var12, arg3[5]);
	return sceMpegbase_BEA18F91 (arg2[7]);
}
int sub_04888 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	if (arg5>=7)return 0x80618007;
	if ((((*((arg5 << 2) + 0x000076A8)<(arg6[5] + arg4))))return 0x80618007;
	arg2[0] = arg3;
	arg2[1] = (getAuSample (arg1, arg6[4]) + arg6[5]);
	arg2[2] = arg4;
	arg2[3] = 0;
	while (1) {
		if (sub_049E0 (arg2))return 0x80618007;
		arg2[2] = (arg2[2] - arg2[3]);
		arg2[0] = (arg2[0] + arg2[3]);
		arg6[5] = (arg6[5] + arg2[3]);
		arg2)[1] = (arg2[1] + arg2[3]);
		if (((arg2[4]<arg2[5])))return 0x80618007;
		if (arg2[3]<arg2[2])return 0;
		if (!(au = getAvcAu (arg1, arg2, arg6)))continue
		au = 0;
		arg2[4] = 0;
		arg2[5] = arg2[6][0];
		return 0;
	}
	return 0;
}
//0x000049E0
int sub_049E0 (int arg1){
	var1 = ((int *) arg1)[4];
	var2 = ((int *) arg1)[5];
	var3 = ((int *) arg1)[6];
	var4 = arg1;
	((int *) arg1)[3] = 0;
	var5 = 0;
	var6 = ((int *) var4)[0];
	var7 = ((int *) var4)[1];
	if (!(((var1<var2)) == 0))
	{
		var8 = ((int *) var4)[2];
		if (!(var8 <= 0))
		{
			var9 = ((int *) var4)[3];
			while (1) {
				var10 = var8 - var9;
				var11 = (((var10<0x00000FF0))) ? var10 : 0x00000FF0;
				var12 = (var3 + 0x00000004) + (var1 << 0x00000004);
				((int *) var12)[2] = (var12 + 0x00000010);
				var5 = 0;
				((int *) var12)[0] = var6;
				var6 = var6 + 0x00000FF0;
				((int *) var12)[1] = var7;
				if (((var11<0x00001000)) == 0)
				{
					var5 = 0x806101FE;
					((int *) var12)[3] = 0;
				}
				else
				{
					((int *) var12)[3] = var11;
					var7 = var7 + 0x00000FF0;
					var13 = ((int *) var4)[4];
					var14 = ((int *) var4)[3];
					var15 = ((int *) var4)[5];
					var16 = var13 + 1;
					var17 = var14 + var11;
					var1 = var16;
					((int *) var4)[3] = var17;
					((int *) var4)[4] = var16;
					if (((var16<var15)) == 0)
						break;
					var8 = ((int *) var4)[2];
					if (!(((var17<var8)) != 0))
						break;
					var9 = ((int *) var4)[3];
					continue;
				}
			}
		}
	}
	return var5;
}
int mallocAvcEsBuf (int arg1){
	if (ret=checkMpegArg (arg1))return ret;
	waitSema(*arg1[411]);
	if (!(*arg1[415] <= 0)){
		for(i=0;!(unsigned char *) arg1)[1664];i++){
			if (i>=*arg1[415]){
				arg1+=i;
				break;
			}
		}
		((char *) arg1)[1664] = 1;
	}
label15:
	signalSema(*arg1[411]);
	return;
}
int mpegFreeAvcEsBuf (int arg1, int arg2){
	if (ret=checkMpegArg (arg1))return ret;
	waitSema(*arg1[411]);
	if (arg2 <= 0)return 0x806101FE;
	if (((*arg1[415]<arg2)) != 0)return 0x806101FE;
	((char *) (arg2 + arg1))[1663] = 0;
	signalSema(*arg1[411]);
	return 0;
}
int getAuSample (int arg1, int arg2){
	if (arg2 <= 0)return arg2;
	if (((*arg1[415]<arg2))return arg2;
	if (((unsigned char *) (arg2 + *arg1))[1663] != 1))return arg2;
	return ((int *) ((arg2 << 2) + *arg1))[416];
}
int mpegQueryAtracEsSize (int arg1, int arg2, int arg3){
	if (ret=checkMpegArg (arg1))return ret;
	arg2[0] = 0x0840;
	arg3[0] = 0x2000;
	return 0;
}
int mpegQueryPcmEsSize (int arg1, int arg2, int arg3){
	if (ret=checkMpegArg (arg1))return ret;
	arg2[0] = 0x0140;
	arg3[0] = 0x0140;
	return 0;
}
int queryUserdataEsSize (int arg1, int arg2, int arg3){
	if (ret=checkMpegArg (arg1))return ret;
	arg2[0] = 0x000A0000;
	arg3[0] = 0x000A0000;
	return 0;
}
int sub_04CD8 (int arg1){
	return (((read16 (arg1+2)&0x3FF)<<3)+8);
}
int sub_04D00 (unsigned char *arg1){
	return (arg1[0] & 0x0F);
}
int sub_04D0C (int arg1){
	return (read24 ((arg1 + 1)) >> 0x17);
}
int sub_04D2C (int arg1){
	return (read24 ((arg1 + 1)) & 0x001FFFFF);
}
int sub_04D4C (unsigned char *arg1){
	return arg1[3];
}
int sub_04D54 (unsigned char *arg1, int arg2){
	if (arg2<arg1[3])
		return (arg1+(arg2<<2))+4;
	return 0;
}
int sub_04D78 (int arg1){
	return (arg1 + 14);
}
int sub_04D80 (int *arg1){
	return ((arg1[0] + (arg1[0][9] * 0x0644)) + 0x28);
}
void sub_04DA0(){
	return;
}
int mpegNextAvcRpAu (int arg1, int*arg2){
	var1 = arg2;
	if (ret=checkMpegArg (arg1))return ret;
	var8 = arg2[2];
	if (arg2[2] == -1)return 0x806101FE;
	waitSema(*arg1[411]);
	au = checkAu (arg2[0], arg1[0], 1);
	if ((au = checkAu (arg2[0], arg1[0], 1)) == -1){
		signalSema(*arg1[411]);
		return 0x806101FE;
	}
	sub_01DEC (arg2[2], 0, 1, sp, sp + 0x30);
	if (sp[12] == 1)
		var24 = sp[7];
	else{
		ret = 0x80618004;
		var24 = 0xFFFF0000;
	}
	if (au[3]>0)
		while (i = 0;i<=au[3];i++) {
			sub_01DEC (au, 0, 1, sp, sp + 0x30);
			if (var24 == 0xFFFF0000)
				sub_01EB4 (au, 1, sp + 0x30);
			else{
				if (sub_03F48 (*arg1[4], var24, sp[7]) != 1))
					sub_01EB4 (au, 1, sp + 0x30);
				else
					var39 = arg2[12];
			}
			break;
		}
	arg2[4] = 0x7FFF;
	arg2[12] = arg2[12] & 0xFFFFFFFB;
	arg2[11] = 0;
	signalSema(*arg1[411]);
	return ret;
}
int mpegChangeGetAvcAuMode (int arg1, int arg2, int arg3){
	if(ret=checkMpegArg (arg1))return ret;
	waitSema(*arg1[411]);
	do{
	if (checkAu (*arg2, *arg1, 1) == -1){ret=0x806101FE;break}
	if (arg2[2] == -1){ret=0x806101FE;break}
	if (arg3==0)arg2[12] &= 0xFFFFFFFD;
	if (arg3==2)arg2[12] |= 2;
	else ret=0x806101FE
	}while(0);
	signalSema(*arg1[411]);
	return ret;
}
int mpegChangeGetAuMode (int *arg1, int*arg2, int arg3){
	if (ret=checkMpegArg (arg2))return ret;
	waitSema(arg1[0][411]);
	if (checkAu (arg2[0], arg1[0], 1) == -1 || (arg3>1)){
		signalSema(arg1[0][411]);
		return 0x806101FE;
	}
	if (arg3 == 0)arg2[12] = arg2[12] & 0xFFFFFFFE;
	if (arg3 == 1)arg2[12] = arg2[12] | 1;
	signalSema(arg1[0][411];);
	return 0;
}
void sceMpegQueryStreamOffset (int arg1, int arg2, int arg3){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryStreamOffset (arg1, arg2, arg3);
}
void sceMpegQueryStreamSize (int arg1, int arg2){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryStreamSize (arg1, arg2);
}
void sceMpegInit(){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegInit();
}
void sceMpegFinish(){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegFinish();
}
void sceMpegQueryMemSize(){
	if(sceKernelCheckThreadStack()<0x03F0)return 0x80618008;
	return mpegQueryMemSize (0);
}
void sceMpeg_42C679F6 (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryMemSize (arg1);
}
void sceMpegCreate (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int pool){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegCreate (arg1, arg2, arg3, arg4, arg5, 0x00, pool);
}
void sceMpeg_75E21135 (int arg1, int arg2, int arg3, int arg4, int arg5, int mode, int pool){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegCreate (arg1, arg2, arg3, arg4, arg5, mode, pool);
}
void sceMpegDelete (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return delete (arg1);
}
void sceMpegRegistStream (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRegistStream (arg1, arg2, arg3);
}
void sceMpegUnRegistStream (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegUnRegistStream (arg1, arg2);
}
void sceMpegMallocAvcEsBuf (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mallocAvcEsBuf (arg1);
}
void sceMpegFreeAvcEsBuf (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegFreeAvcEsBuf (arg1, arg2);
}
void sceMpegQueryAtracEsSize (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryAtracEsSize (arg1, arg2, arg3);
}
void sceMpegQueryPcmEsSize (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegQueryPcmEsSize (arg1, arg2, arg3);
}
void sceMpegInitAu (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegInitAu (arg1, arg2, arg3);
}
void sceMpegChangeGetAvcAuMode (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegChangeGetAvcAuMode (arg1, arg2, arg3);
}
void sceMpegChangeGetAuMode (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegChangeGetAuMode (arg1, arg2, arg3);
}
void sceMpegNextAvcRpAu (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegNextAvcRpAu (arg1, arg2);
}
void sceMpegGetAvcAu (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetAvcAu (arg1, arg2, arg3, arg4);
}
void sceMpegGetPcmAu (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetPcmAu (arg1, arg2, arg3, arg4);
}
void sceMpegGetAtracAu (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3R0)return 0x80618008;
	return sub_03C4C (arg1, arg2, arg3, arg4);
}
void sceMpegFlushStream (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegFlushStream (arg1, arg2);
}
void sceMpegFlushAllStream (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return flushAllStream (arg1);
}
void sceMpegAvcDecode (int arg1, int arg2, int arg3, int arg4, int arg5){
	if ((sceKernelCheckThreadStack()<0x3E0))return 0x80618008
	return avcDecode (arg1, arg2, arg3, arg4, arg5);
}
void sceMpegAvcDecodeDetail (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeDetail (arg1, arg2);
}
void sceMpegAvcDecodeMode (int arg1, int arg2){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008
	return avcDecodeMode (arg1, arg2);
}
void sceMpegAvcDecodeStop (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008
	return avcDecodeStop (arg1, arg2, arg3, arg4);
}
void sceMpegAvcDecodeFlush (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeFlush (arg1);
}
void sceMpegAvcQueryYCbCrSize (int arg1, int arg2, int arg3, int arg4, int arg5){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcQueryYCbCrSize (arg1, arg2, arg3, arg4, arg5);
}
void sceMpegAvcInitYCbCr (int arg1, int arg2, int arg3, int arg4, int arg5){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcInitYCbCr (arg1, arg2, arg3, arg4, arg5);
}
void sceMpegAvcDecodeYCbCr (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcDecodeYCbCr (arg1, arg2, arg3, arg4);
}
void sceMpegAvcDecodeStopYCbCr (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return avcDecodeStopYCbCr (arg1, arg2, arg3);
}
void sceMpegAvcCsc (int arg1, int arg2, int arg3, int arg4, int arg5){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return avcCsc (arg1, arg2, arg3, arg4, arg5);
}
void sceMpeg_0558B075 (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegYCrCbCopy (arg1, arg2, arg3);
}
void sceMpegAtracDecode (SceMpeg*Mpeg, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x000003E0)return 0x80618008;
	if (Mpeg[414] != 1)return 0x806101FE;
	return atracDecode (Mpeg, arg2, arg3, arg4);
}
void sceMpegQueryUserdataEsSize (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return queryUserdataEsSize (arg1, arg2, arg3);
}
void sceMpegQueryUserdataEsSize (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return queryUserdataEsSize2 (arg1, arg2, arg3, arg4);
}
void sceMpegGetAvcEsAu (int arg1, int arg2, int arg3, int arg4){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegGetAvcEsAu (arg1, arg2, arg3, arg4);
}
void sceMpegGetAvcNalAu (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegGetAvcNalAu (arg1, arg2, arg3);
}
void sceMpegRingbufferQueryMemSize (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferQueryMemSize (arg1);
}
void sceMpegRingbufferQueryPackNum (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferQueryPackNum (arg1);
}
void sceMpegRingbufferConstruct (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	if (sceKernelCheckThreadStack()<0x3E0)return 0x80618008;
	return mpegRingbufferConstruct (arg1, arg2, arg3, arg4, arg5, arg6);
}
void sceMpegRingbufferDestruct (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferDestruct();
}
void sceMpegRingbufferPut (int arg1, int arg2, int arg3){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferPut (arg1, arg2, arg3);
}
void sceMpegRingbufferAvailableSize (int arg1){
	if (sceKernelCheckThreadStack()<0x3F0)return 0x80618008;
	return mpegRingbufferAvailableSize (arg1);
}
int createSema(int arg1, int arg2, int arg3, int* arg4){
	return sceKernelCreateSema (arg3, 0, arg1, arg2, 0)<0?0x80000041:0);
}
int deleteSema(sema){
	return sceKernelDeleteSema() ? 0x80000041:0;
}
void waitSema(sema){
	return sceKernelWaitSema(sema, 1, 0);
}
void signalSema(){
	return sceKernelSignalSema (sema, 1);
}
int setupVideoCodec (int*arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8){
	waitSema(semaAvc);
	memset (arg2, 0, 40);
	memset (arg3, 0, 0xB0);
	memset (arg4, 0, 0x64);
	arg1[4] = arg2;
	arg1[11] = arg3;
	arg1[12] = arg4;
	arg1[15] = 4;
	arg1[14] = arg5;
	if (ret=sceVideocodecOpen (arg1,0))return;
	arg1[7] = arg7;
	arg1[5] = *arg6;
	if (sceVideocodecInit (arg1, 0))return;
	if (sceVideocodecGetVersion (arg1, 0))return;
	arg1[16] = arg8;
	arg1[17] = sp[12];
	arg1[18] = sp[13];
	arg1[19] = sp[14];
	if (sceVideocodecSetMemory (arg1, 0))return;
	signalSema(semaAvc);
	return 0;
}
int videocodecDecode (int arg1){
	waitSema(semaAvc);
	ret = sceVideocodecDecode (arg1, 0);
	signalSema(semaAvc);
	return ret;
}
int videoCodecStop_ (int arg1){
	waitSema(semaAvc);
	ret = sceVideocodecStop (arg1, 0);
	signalSema(semaAvc);
	return ret;
}
void videocodecDelete (int arg1){
	waitSema(semaAvc);
	ret=sceVideocodecDelete (arg1, 0);
	signalSema(semaAvc);
	return ret;
}
void videocodec_893B32B1 (int arg1, int arg2){
	waitSema(semaAvc);
	arg1[22] = arg2;
	ret = sceVideocodec_893B32B1 (arg1, 0);
	signalSema(semaAvc);
	return ret;
}
void initAudioCodec (int arg1){
	ADRAM = 0x000078C0;
	memset (0x000078C0, 0, 0x0000006C);
	if (ret=audiocodecCheckNeedMem (sp, arg1, 0x00007940))return ret;
	ret = sceAudiocodecGetEDRAM (ADRAM, 0x00001000);
	if (ret){
		ADRAM[3] = 0;
		return ret;
	}
	return 0;
}
int audiocodecCheckNeedMem (int arg1, int arg2, int arg3){
	var1 = ((arg2 ^ 3)<1);
	var3 = (var1 << 1) + "(" "\\" "\\" "\\";
	var4 = (var1 << 2) + 0x000076CC;
	if (arg3)*arg3=var1;
	ADRAM[12] = 1;
	((char *) ADRAM)[40] = ((char *) var3)[0];
	((char *) ADRAM)[41] = ((char *) var3)[1];
	var10 = LWR (var4, LWL (var4, v0, 3), 0);
	SWL (ADRAM, var10, 0x2F);
	SWR (ADRAM, var10, 0x2C);
	ADRAM[5] = 1;
	ret = sceAudiocodecCheckNeedMem (ADRAM, 0x00001000);
	*arg1 = ADRAM[4];
	return ret;
}
//0x00006980
int sub_06980 (int arg1, int arg2, int arg3, int arg4, int arg5){
	sp = sp + 0xFFFFFFE0;
	sp[4] = s4;
	sp[3] = s3;
	var1 = arg1;
	var2 = *((int *) semaAtrac);
	sp[6] = ra;
	sp[5] = s5;
	sp[2] = s2;
	var3 = arg5;
	sp[1] = s1;
	var4 = arg4;
	sp[0] = s0;
	waitSema();
	((int *) var1)[3] = arg2;
	((int *) var1)[12] = 1;
	var7 = ((char *) var4)[0];
	var8 = ((char *) var4)[1];
	((char *) var1)[40] = var7;
	((char *) var1)[41] = var8;
	var9 = LWL (var3, var7, 3);
	var10 = LWR (var3, var9, 0);
	SWL (var1, var10, 0x0000002F);
	SWR (var1, var10, 0x0000002C);
	((int *) var1)[5] = 1;
	var13 = sceAudiocodecCheckNeedMem (var1, 0x00001000);
	var14 = var13;
	if (var13 != 0)
	{

	label14:
		var29 = *((int *) semaAtrac);
		signalSema();
		var19 = var14;
	}
	else
	{
		var15 = ((int *) var1)[4];
		if (((arg3<var15)) == 0)
		{
			var28 = sceAudiocodecInit (var1, 0x00001000);
			var14 = var28;
			if (!(var28 == 0))
				goto label14;
			var32 = *((int *) semaAtrac);
			signalSema();
			var19 = 0;
		}
		else
		{
			var16 = *((int *) semaAtrac);
			signalSema();
			var19 = 0x807F00FF;
		}
	}
	ra = sp[6];
	var20 = sp[5];
	var21 = sp[4];
	var22 = sp[3];
	var23 = sp[2];
	var24 = sp[1];
	var25 = sp[0];
	sp = sp + 0x00000020;
	return var19;
}
void audiocodecReleaseEDRAM(){
	return ADRAM[3]?sceAudiocodecReleaseEDRAM():0;
}
int sub_06B14 (int arg1){
	if (arg1)*arg1 = *((int *) 0x00007940);
	return ADRAM[3];
}
int audiocodecDecode (int arg1){
	ret = sceAudiocodecDecode (arg1, 0x00001000);
	signalSema(semaAtrac);
	return ret;
}
int abs (int arg1){
	return (MAX (arg1,-arg1));
}
//0x00006CD4
int getStr (int arg1, int arg2){
	var1 = 0x806101FE;
	var2 = 0;
	if (!(((arg1<0x00000013)) == 0))
	{
		var3 = arg1 << 3;
		var4 = ((int *) (var3 + 0x000076D8))[1];
		if (var4 == 0xFFFF0000)
		{
			var2 = 0x00000010;

		label13:

		label14:
			var5 = ((int *) (var3 + 0x000076D8))[0];
			var1 = var5 | (arg2 << var2);
		}
		else
		{
			if (((0xFFFF0000<var4)) != 0)
			{
				if (var4 == 0xFFFFFF00)
				{
					var2 = 0x00000008;
					goto label13;
				}
				else
				{
					if (var4 != -1)
					{
						var1 = 0;
					}
					else
					{
						goto label14;
					}
				}
			}
			else
			{
				if (var4 == 0xFF000000)
				{
					var2 = 0x00000018;
					goto label13;
				}
				else
				{
					var1 = 0;
				}
			}
		}
	}
	return var1;
}
//0x00006D68
void sub_06D68 (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFFD0;
	var1 = 0;
	sp[8] = fp;
	var2 = 0x000076D8;
	var3 = 0;
	sp[7] = s7;
	var4 = 0;
	var5 = 0;
	sp[6] = s6;
	sp[5] = s5;
	sp[4] = s4;
	sp[3] = s3;
	sp[2] = s2;
	sp[1] = s1;
	sp[0] = s0;
	while (1) {
		var6 = ((int *) var2)[1];
		if (var6 == 0xFFFF0000)
		{
			var20 = ((int *) var2)[0];
			var21 = arg3;
			if (var20 == 0xBD400000)
			{

			label23:
				var3 = (var21 & 0xFFF00000) | (0 & 0x000FFFFF);

			label24:
				var4 = 0x0000000F;
			}
			else
			{
				if (((0xBD400000<var20)) != 0)
				{
					var23 = arg3;
					if (var20 == 0xBD880000)
					{

					label12:
						var3 = (var23 & 0xFFF80000) | (0 & 0x0007FFFF);
						var4 = 0x00000007;
					}
					else
					{
						var3 = (var23 & 0xFFE00000) | (0 & 0x001FFFFF);
						if (((0xBD880000<var20)) != 0)
						{
							var23 = arg3;
							if (var20 == 0xBD900000)
								goto label12;
							if (var20 != 0xBDA00000)
							{
								var22 = arg3;

							label26:
								var3 = (var22 & 0xFFFF0000) | (0 & 0x0000FFFF);
								var4 = 0;
							}
							else
							{
								var23 = arg3;
								goto label12;
							}
						}
						else
						{
							var4 = 0x0000001F;
							if (var20 != 0xBD800000)
							{

							label25:
								var22 = arg3;
								goto label26;
							}
							else
							{
							}
						}
					}
				}
				else
				{
					if (var20 == 0xBD100000)
					{
						var21 = arg3;
						goto label23;
					}
					else
					{
						if (((0xBD100000<var20)) != 0)
						{
							var21 = arg3;
							if (var20 == 0xBD200000)
								goto label23;
							if (var20 != 0xBD300000)
							{
								var22 = arg3;
								goto label26;
							}
							else
							{
								var3 = (arg3 & 0xFFF00000) | (0 & 0x000FFFFF);
								goto label24;
							}
						}
						else
						{
							var21 = arg3;
							if (var20 == 0xBD000000)
								goto label23;
							goto label25;
						}
					}
				}
			}
			if (var3 != var20)
			{
				var5 = var5 + 1;
			}
			else
			{
				var17 = (arg3 >> 0x00000010) & var4;

			label37:
				((int *) arg1)[0] = var5;

			label51:
				((int *) arg2)[0] = var17;

			label52:
				var5 = var5 + 1;
			}
		}
		else
		{
			if (((0xFFFF0000<var6)) != 0)
			{
				if (var6 == 0xFFFFFF00)
				{
					var19 = ((int *) var2)[0];
					if (var19 == 0xBF01E000)
					{
						var3 = (arg3 & 0xFFFFE000) | (0 & 0x00001FFF);
						var4 = 0x0000001F;
					}
					var17 = (arg3 >> 0x00000008) & var4;
					if (!(var3 != var19))
						goto label37;
					goto label52;
				}
				else
				{
					if (var6 != -1)
					{
						var5 = var5 + 1;
					}
					else
					{
						var18 = ((int *) var2)[0];
						var3 = (arg3 & 0xFFFFFF00) | (0 & 0x000000FF);
						if (var3 != var18)
						{
							var5 = var5 + 1;
						}
						else
						{
							var1 = 1;
							((int *) arg1)[0] = var5;
							((int *) arg2)[0] = (arg3 & 0x0000FFFF);
							goto label52;
						}
					}
				}
			}
			else
			{
				if (!(var6 == 0xFF000000))
					goto label52;
				var16 = ((int *) var2)[0];
				var3 = (arg3 & 0xF0000000) | (0 & 0x0FFFFFFF);
				var4 = 0x0000000F;
				if (!(var16 == 0xE0000000))
				{
					var3 = (arg3 & 0xE0000000) | (0 & 0x1FFFFFFF);
					var4 = 0x0000001F;
					if (!(var16 == 0xC0000000))
					{
						var3 = (arg3 & 0xFF000000) | (0 & 0x00FFFFFF);
						var4 = 0;
					}
				}
				if (var3 != var16)
				{
					var5 = var5 + 1;
				}
				else
				{
					((int *) arg1)[0] = var5;
					var17 = (arg3 >> 0x00000018) & var4;
					goto label51;
				}
			}
		}
		var2 = var2 + 0x00000008;
		if ((((var5<0x00000013)) & ((var1<1))) != 0)
			continue;
		break;
	}
	var7 = sp[8];
	var8 = sp[7];
	var9 = sp[6];
	var10 = sp[5];
	var11 = sp[4];
	var12 = sp[3];
	var13 = sp[2];
	var14 = sp[1];
	var15 = sp[0];
	sp = sp + 0x00000030;
	return;
}
int sub_06FB4 (int arg1){
	if (arg1>=0x13))return 0x806101FE;
	return ((int *) ((arg1 << 3) + 0x000076D8))[1];
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
}

