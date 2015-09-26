#include <pspsdk.h>
#include "usbacc.h"

void sceUsbAccGetAuthStat (){
	intr = sceKernelCpuSuspendIntr ();
	if (*((unsigned char *) 0x00000D63))ret = sceUsbBus_driver_8A3EB5D2 ()?0:0x80243701;
	else ret = 0x80243007;
	sceKernelCpuResumeIntr (intr);
}
void sceUsbAccGetInfo (int arg1){
	var1 = 0;
	if (!*((unsigned char *) 0x00000D63))return
	if (!(ret = sceUsbBus_driver_8A3EB5D2 ()))return;
	if (!arg1)return 0x80243002;
	if ((((arg1 + 0x00000008) | arg1) & (0 - k1&0x18)) < 0)return;
	_k1 = k1;
	k1 = k1 >> 0x00000010;
	intr = sceKernelCpuSuspendIntr ();
	var20 = LWL (0x00000D20, k1&0x18, 0x00000003);
	var21 = LWR (0x00000D20, var20, 0);
	var22 = LWL (0x00000D20, ret, 0x00000007);
	var23 = LWR (0x00000D20, var22, 0x00000004);
	SWL (arg1, var21, 0x00000003);
	SWR (arg1, var21, 0);
	SWL (arg1, var23, 0x00000007);
	SWR (arg1, var23, 0x00000004);
	k1 = _k1;
	sceKernelCpuResumeIntr (intr);
}
void sceUsbAcc_internal_2A100C1F (int*arg1){
	if (!*((unsigned char *) 0x00000D63))return 0x80243007;
	if (((unsigned char *) arg1[1])[3]>=0x3D)return 0x80243002;
	sceKernelDcacheWritebackRange (arg1[1], arg1[2]);
	arg1[0] = 0x00000CBC;
	arg1[2] = (((unsigned char *) arg1[1])[3] + 4);
	return sceUsbbdReqSend (arg1);
}
void sub_001E8 (int arg1, int arg2, int arg3){
//TODO
}
void sub_0034C (){
	var3 = sceKernelCreateFpl ("SceUsbAcc", 0x00000001, 0x00000100, 0x00000170, 0x00000001, 0);
//TODO
}

void sceUsbAccRegisterType (int arg1){
	if (*((unsigned short *) 0x00000D60) & arg1)
		*((short *) 0x00000D60) |= arg1;
}
void sceUsbAccUnregisterType (int arg1){
	if ((*((unsigned short *) 0x00000D60) & 0x0000FFFF) & arg1)
		*((short *) 0x00000D60) &= !arg1;
}
void module_start (){
	if (sceUsbbdRegister (0x00000CD4)>=0){
		*((short *) 0x00000D60) = 0;
		*((char *) 0x00000D62) = 0;
		return 0;
	}
	return 1;
}
void module_stop (){
	return sceUsbbdUnregister (0x00000CD4);
}
void sub_00588 (){
	sceUsbBus_driver_7B87815D ();
	sceKernelDeleteFpl (*((int *) 0x00000D5C));
	*((char *) 0x00000D62) = 0;
}
void sub_005C0 (int arg1){
	if (arg1[6])return;
	if (*((char *) 0x00000D28)<0)return;
	if (*((char *) 0x00000D29)!=1)return;
	var5 = LWL (arg1[1], 0x00000D20, 3);
	var6 = LWR (arg1[1], var5, 0);
	var7 = LWL (arg1[1], arg1, 7);
	var8 = LWR (arg1[1], var7, 4);
	SWL (0x00000D20, var6, 3);
	SWR (0x00000D20, var6, 0);
	SWL (0x00000D20, var8, 7);
	SWR (0x00000D20, var8, 4);
}

void sub_00618 (){
	if (!*((char *) 0x00000D63))
		*((char *) 0x00000D63) = 1;
}
void sub_00638 (){
	if (!*((unsigned char *) 0x00000D63))return;
	*((int *) 0x00000D24) = 0;
	*((char *) 0x00000D63) = 0;
	*((int *) 0x00000D20) = 0;
	var2 = 0x00000CB8;
	var3 = 1;
	while (var3>=0) {
		var3--;
		var2[0]=0;
		var2+=12;
	}
}
int sub_0067C (int arg1, char*arg2, int**arg3, int*arg4){
	var5 = arg4 + 0x00000018 + 0x0000000C + 0x00000030;
	arg3[1] = arg4 + 0x00000018;
	var8 = (arg2 | 0x00000B94) & 0x00000003;
	var9 = var5;
	arg3[2] = arg4 + 0x00000018 + 0x0000000C;
	arg3[0] = arg4;
	var10 = 0x00000BA4;
	arg3[3] = var5;
	var12 = arg3[2];
	var13 = arg2;
	if (var8 == 0){
		for (int *var6 = 0x00000B94;var6 != 0x00000BA4;var6 += 0x10) {
			int*var13 = 0x00000010;
			var13[ 0] = var6[0];
			var13[-1] = var6[3];
			var13[-2] = var6[2];
			var13[-3] = var6[1];
		}
		var52 = ((int *) var6)[0];
		((int *) var13)[0] = var52;
	}else{
		while (var6 != 0x00000BA4;var6 = var6 + 16,var13 = var13 + 16;) {
			var8 = LWR (var6, LWL (var6, var8, 3), 0);
			arg1 = LWR (var6, LWL (var6, arg1, 7), 4);
			var5 = LWR (var6, LWL (var6, var5, 11), 8);
			var10 = LWR (var6, LWL (var6, var10, 15), 12);
			SWL (var13, var8, 3);
			SWR (var13, var8, 0);
			SWL (var13, arg1, 7);
			SWR (var13, arg1, 4);
			SWL (var13, var5, 12);
			SWR (var13, var5, 8);
			SWL (var13, var10, 15);
			SWR (var13, var10, 12);
		}
		var18 = LWL (var6, 0x00000BA4, 0x00000003);
		var19 = LWR (var6, var18, 0);
		SWL (var13, var19, 0x00000003);
		SWR (var13, var19, 0);
	}
	arg4[0]		= *((int *) 0x0BA8);
	arg4[1]		= *((int *) 0x0BAC);
	arg4[2]		= *((int *) 0x0BB0);
	arg4[3]		= *((int *) 0x0BB4);
	arg4[4]		= *((int *) 0x0BB8);
	arg4[5]		= *((int *) 0x0BBC);
	arg3[1][0] = *((int *) 0x0BC0);
	arg3[1][1] = *((int *) 0x0BC4);
	arg3[1][2] = *((int *) 0x0BC8);
	
	int*var30 = arg3[2];
	while (int*var29 = 0x00000BCC;var29 != 0x00000BFC;var29 += 16,var30 += 16;) {
		var30[0] = var29[0];
		var30[1] = var29[5];
		var30[2] = var29[6];
		var30[3] = var29[7];
	}
	var9[0] = *((int *) 0x0BFC);
	var9[1] = *((int *) 0x0C00);
	var9[2] = *((int *) 0x0C04);
	var9[3] = *((int *) 0x0C08);
	var9[4] = *((int *) 0x0C0C);
	var9[5] = *((int *) 0x0C10);
	var9[6] = *((int *) 0x0C14);
	var9[7] = *((int *) 0x0C18);
	arg4[3][0] = arg3[2];
	arg3[2][3] = var9;
	arg2[7] = 0x40;
	((short *) var9)[2] = 0x00000040;
	((char *) var9)[6] = arg1==2?7:8;
	return (var5 + 0x00000020);
}

