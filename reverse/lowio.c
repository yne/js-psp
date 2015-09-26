#include <pspsdk.h>

void sceSysreg_driver_26D97F66 (){
	setReset (0x01, 1);
}
void sceSysreg_driver_36DA035E (){
	setReset (0x02, 1);
}
void sceSysreg_driver_20C9E2C4 (){
	setReset (0x04, 1);
}
void sceSysreg_driver_5F190A4E (){
	setReset (0x04, 0);
}
void sceSysreg_driver_2CFF6043 (){
	setReset (0x08, 1);
}
void sceSysreg_driver_DBD8D3D2 (){
	setReset (0x08, 0);
}
void sceSysreg_driver_4FFB12A2 (){
	setReset (0x10, 1);
}
void sceSysreg_driver_CEE8BAF6 (){
	setReset (0x10, 0);
}
void sceSysreg_driver_663D5471 (){
	setReset (0x20, 1);
}
void sceSysreg_driver_35BC4DD2 (){
	setReset (0x20, 0);
}
void sceSysreg_driver_E70F8FD3 (){
	setReset (0x40, 1);
}
void sceSysreg_driver_09220B6F (){
	setReset (0x40, 0);
}
void sceSysreg_driver_77F3701E (){
	setReset (0x80, 1);
}
void sceSysreg_driver_B3F134C7 (){
	setReset (0x80, 0);
}
void sceSysreg_driver_AE663FC3 (int arg1){
	if((arg1>0)&&(arg1<2))setReset ((0x0100 << arg1), 1);
}
void sceSysreg_driver_63FBF749 (int arg1){
	if((arg1>0)&&(arg1<2))setReset ((0x0100 << arg1), 0);
}
void sceSysreg_driver_1389C30D (){
	setReset (0x0400, 1);
	return;
}
void sceSysreg_driver_DA41BE07 (){
	setReset (0x0400, 0);
}
void sceSysreg_driver_1DC62106 (){
	setReset (0x1000, 1);
}
void sceSysreg_driver_C778A8A3 (){
	setReset (0x1000, 0);
}
void sceSysreg_driver_89C72A7B (){
	setReset (0x2000, 1);
}
void sceSysreg_driver_8721EA15 (){
	setReset (0x2000, 0);
}
void setReset (int arg1, int arg2){
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2)*((int *) 0xBC10004C) |= arg1
	else		*((int *) 0xBC10004C) ^= arg1 & *((int *) 0xBC10004C);
	sceKernelCpuResumeIntr (intr, arg2);
}
void sceSysreg_driver_08E0EE7E (){
	setBusClock (1, 1);
}
void sceSysreg_driver_CD36673C (){
	setBusClock (1, 0);
}
void sceSysreg_driver_3C5806AF (){
	setBusClock (2, 1);
}
void sceSysreg_driver_126F5946 (){
	setBusClock (2, 0);
}
void sceSysreg_driver_819ACEB6 (){
	setBusClock (0x04, 1);
}
void sceSysreg_driver_FE32C7C1 (){
	setBusClock (0x04, 0);
}
void sceSysreg_driver_05A0D371 (){
	setBusClock (0x08, 1);
}
void sceSysreg_driver_BE63A2B9 (){
	setBusClock (0x08, 0);
}
void sceSysregDmacplusBusClockEnable (){
	setBusClock (0x10, 1);
}
void sceSysregDmacplusBusClockDisable (){
	setBusClock (0x10, 0);
}
void sceSysreg_driver_E74CB850 (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x20 << arg1), 1);
}
void sceSysreg_driver_5ECA49E4 (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x20 << arg1), 0);
}
void sceSysreg_driver_3C7163B5 (){
	setBusClock (0x80, 1);
}
void sceSysreg_driver_8A56E7F1 (){
	setBusClock (0x80, 0);
}
void sceSysregAtaBusClockEnable (){
	setBusClock (0x0100, 1);
}
void sceSysregAtaBusClockDisable (){
	setBusClock (0x0100, 0);
}
void sceSysreg_driver_00CEA69D (){
	setBusClock (0x0200, 1);
}
void sceSysreg_driver_04FA5F9F (){
	setBusClock (0x0200, 0);
}
void sceSysreg_driver_CAC37836 (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x0400 << arg1), 1);
}
void sceSysreg_driver_4638FA5B (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x0400 << arg1), 0);
}
void sceSysreg_driver_A012D356 (){
	setBusClock (0x1000, 1);
}
void sceSysreg_driver_31BE6914 (){
	setBusClock (0x1000, 0);
}
void sceSysregEmcsmBusClockEnable (){
	setBusClock (0x2000, 1);
}
void sceSysregEmcsmBusClockDisable (){
	setBusClock (0x2000, 0);
}
void sceSysreg_driver_70DB03B3 (){
	setBusClock (0x4000, 1);
}
void sceSysreg_driver_73F75CF8 (){
	setBusClock (0x4000, 0);
}
void sceSysreg_driver_C7FC7669 (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x8000 << arg1), 1);
}
void sceSysreg_driver_F9A652BC (int arg1){
	if((arg1>0)&&(arg1<2))setBusClock ((0x8000 << arg1), 0);
}
void sceSysreg_driver_97B76F89 (){
	setBusClock (0x00020000, 1);
}
void sceSysreg_driver_58B2671B (){
	setBusClock (0x00020000, 0);
}
void sceSysreg_driver_C367C076 (){
	setBusClock (0x00040000, 1);
}
void sceSysreg_driver_C03903EE (){
	setBusClock (0x00040000, 0);
}
void setBusClock (int arg1, int arg2){
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2)*((int *) 0xBC100050) |= arg1;
	else *((int *) 0xBC100050) ^= *((int *) 0xBC100050) & arg1;
	sceKernelCpuResumeIntr (intr, arg2);
}
void sceSysreg_driver_AFD7C10B (){
	setClk (1, 1);
}
void sceSysreg_driver_BD89766B (){
	setClk (1, 0);
}
void sceSysreg_driver_3616B538 (){
	setClk (2, 1);
}
void sceSysreg_driver_FC42CD72 (){
	setClk (2, 0);
}
void sceSysreg_driver_7E046110 (){
	setClk (0x00010000, 1);
}
void sceSysreg_driver_4F9452D7 (){
	setClk (0x00010000, 0);
}
void sceSysreg_driver_6CD41073 (int arg1){
	if((arg1>0)&&(arg1<2))setClk ((0x0100 << arg1), 1);
}
void sceSysreg_driver_3AAE2AE9 (int arg1){
	if((arg1>0)&&(arg1<2))setClk ((0x0100 << arg1), 0);
}
void sceSysregSpiClkEnable (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x0100 << arg1), 1);
}
void sceSysregSpiClkDisable (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x0100 << arg1), 0);
}
void sceSysregUartClkEnable (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x40 << arg1), 1);
}
void sceSysregUartClkDisable (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x40 << arg1), 0);
}
void sceSysreg_driver_9C89F935 (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x1000 << arg1), 1);
}
void sceSysreg_driver_036D4A59 (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x1000 << arg1), 0);
}
void sceSysreg_driver_823FFD7A (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x00010000 << arg1), 1);
}
void sceSysreg_driver_E2412D26 (int arg1){
	if((arg1>0)&&(arg1<2))setClkout ((0x00010000 << arg1), 0);
}
void sceSysreg_driver_F092AED8 (){
	setClkout (0x00040000, 1);
}
void sceSysreg_driver_280F9241 (){
	setClkout (0x00040000, 0);
}
void sceSysreg_driver_8684E7A1 (){
	setClkout (0x00080000, 1);
}
void sceSysreg_driver_03BD35E5 (){
	setClkout (0x00080000, 0);
}
void sceSysreg_driver_C0BC0E36 (){
	setClkout (0x00100000, 1);
}
void sceSysreg_driver_4ACB2BB3 (){
	setClkout (0x00100000, 0);
}
void sceSysreg_driver_04839CA2 (){
	setClkout (0x00200000, 1);
}
void sceSysreg_driver_917F9660 (){
	setClkout (0x00200000, 0);
}
void sceSysregSircsClkEnable (){
	setClkout (0x00400000, 1);
}
void sceSysregSircsClkDisable (){
	setClkout (0x00400000, 0);
}
void sceSysreg_driver_2E9CF295 (){
	setClkout (0x00800000, 1);
}
void sceSysreg_driver_E987E988 (){
	setClkout (0x00800000, 0);
}
void sceSysreg_driver_7A154A45 (){
	setClkout (0x01000000, 1);
}
void sceSysreg_driver_CA84A2D9 (){
	setClkout (0x01000000, 0);
}
void setClk (int arg1, int arg2){
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2)*((int *) 0xBC100054) |= arg1;
	else		*((int *) 0xBC100054) ^= arg1 & *((int *) 0xBC100054);
	sceKernelCpuResumeIntr (intr, arg2);
}
void setClkout (int arg1, int arg2){
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2)*((int *) 0xBC100058) |= arg1;
	else		*((int *) 0xBC100058) ^= arg1 & *((int *) 0xBC100054);
	sceKernelCpuResumeIntr (intr, arg2);
}
void sceSysreg_driver_D5F04B96 (int arg1){
	setClkEx (arg1, 1);
}
void sceSysreg_driver_C60904D4 (int arg1){
	setClkEx (arg1, 0);
}
void setClkEx (int arg1, int arg2){
	int intr = sceKernelCpuSuspendIntr ();
	if(!arg2) *((int *) 0xBC100054) = (*((int *) 0xBC100054)&~0xF0)|((((*((int *) 0xBC100054)>>4)&0xF)|arg1));
	else      *((int *) 0xBC100054) = (*((int *) 0xBC100054)&~0xF0)|((((*((int *) 0xBC100054)>>4)&0xF)|arg1)&0x0F);
	sceKernelCpuResumeIntr (intr, arg2);
}
void sceSysregEmcsmIoEnable (){
	setIo (2, 1);
}
void sceSysregEmcsmIoDisable (){
	setIo (2, 0);
}
void sceSysreg_driver_03E84901 (){
	setIo (0x04, 1);
}
void sceSysreg_driver_B5CD678F (){
	setIo (0x04, 0);
}
void sceSysreg_driver_463B488C (){
	setIo (0x08, 1);
}
void sceSysreg_driver_421E5DCF (){
	setIo (0x08, 0);
}
void sceSysreg_driver_86D9213D (int arg1){
	if((arg1>0)&&(arg1<2))setIo ((0x10 << arg1), 1);
}
void sceSysreg_driver_9FBCA4D0 (int arg1){
	if((arg1>0)&&(arg1<2))setIo ((0x10 << arg1), 0);
}
void sceSysreg_driver_BEF287D5 (){
	setIo (0x40, 1);
}
void sceSysreg_driver_FF6D37E7 (){
	setIo (0x40, 0);
}
void sceSysreg_driver_410C74F7 (int arg1){
	if ((arg1<0)||(arg1>=2))return;
	setIo ((0x80 << arg1), 1);
}
void sceSysreg_driver_3841D7C8 (int arg1){
	if ((arg1<0)||(arg1>=2))return;
	setIo ((0x80 << arg1), 0);
}
void sceSysreg_driver_23944179 (){
	setIo (0x0200, 1);
}
void sceSysreg_driver_6D204F2A (){
	setIo (0x0200, 0);
}
void sceSysregSircsIoEnable (){
	setIo (0x0400, 1);
}
void sceSysregSircsIoDisable (){
	setIo (0x0400, 0);
}
void sceSysreg_driver_E46A0890 (){
	setIo (0x0800, 1);
}
void sceSysreg_driver_77B582E9 (){
	setIo (0x0800, 0);
}
void sceSysreg_driver_9B2871A8 (){
}
void sceSysreg_driver_3160E8A2 (){
}
void sceSysreg_driver_6B5C5FD0 (){
	setIo (0x2000, 1);
}
void sceSysreg_driver_80995BB5 (){
	setIo (0x2000, 0);
}
void sceSysreg_driver_FB40B1AA (){
	setIo (0x4000, 1);
}
void sceSysreg_driver_3F0DF46D (){
	setIo (0x4000, 0);
}
void sceSysregUartIoEnable (int arg1){
	if ((arg1<0)||(arg1>=6))return;
	setIo ((0x00010000 << arg1), 1);
}
void sceSysregUartIoDisable (int arg1){
	if ((arg1<0)||(arg1>=6))return;
	setIo ((0x00010000 << arg1), 0);
}
void sceSysregSpiIoEnable (int arg1){
	if ((arg1<0)||(arg1>=6))return;
	setIo ((0x01000000 << arg1), 1);
}
void sceSysregSpiIoDisable (int arg1){
	if ((arg1<0)||(arg1>=6))return;
	setIo ((0x01000000 << arg1), 0);
}
void setIo (int arg1, int arg2){
	intr = sceKernelCpuSuspendIntr ();
	prev = *((int *) 0xBC100078);
	*((int *) 0xBC100078) = arg2 ? (prev | arg1) : (prev ^ prev & arg1));
	sceKernelCpuResumeIntr (intr, arg2);
}
void sceSysreg_driver_217316F7 (int arg1){
	if ((arg1<0)||(arg1>=0x20))return;
	sub_00B04 ((1 << arg1), 1);
}
void sceSysreg_driver_C0D33340 (int arg1){
	if ((arg1<0)||(arg1>=0x20))return;
	sub_00B04 ((1 << arg1), 0);
}
void sub_00B04 (int arg1, int arg2){
	var3 = sceKernelCpuSuspendIntr ();
	prev = *((int *) 0xBC10007C);
	*((int *) 0xBC10007C) = (!(arg2) ? (prev ^ (prev & arg1)) : (prev | arg1));
	sceKernelCpuResumeIntr (var3, arg2);
}
void sub_00BCC (int arg1, int arg2){
	intr = sceKernelCpuSuspendIntr ();
	if(arg2)*((int *) 0xBC100074)|=arg1;
	else    *((int *) 0xBC100074)^=arg1&*((int *) 0xBC100074);
	sceKernelCpuResumeIntr (intr, arg2);
	return = 0 < *((int *) 0xBC100074) & arg1;
}
void sub_00BA4 (int arg1, int arg2, int arg3){
	if ((arg1<0)||(arg1>=2))return;
	sub_00BCC ((arg3 << (arg1 << 2)), arg2);
}
void sceSysreg_driver_64C2D131 (int arg1){
	sub_00BA4 (arg1, 0, 1);
}
void sceSysreg_driver_ACA3F3A3 (int arg1){
	sub_00BA4 (arg1, 1, 1);
}
void sceSysreg_driver_19DF2827 (int arg1){
	sub_00BA4 (arg1, 0, 2);
}
void sceSysreg_driver_02A1F862 (int arg1){
	sub_00BA4 (arg1, 1, 2);
}
void sceSysreg_driver_2FCFA7CD (){
	sub_00BCC (0x0100, 1);
}
void sceSysreg_driver_E440DC4A (){
	sub_00BCC (0x0100, 0);
}
void sceSysreg_driver_12EF2C08 (){
	return *((int *) 0xBC100080);
}
void sceSysreg_driver_0C3CFD86 (){
	var1 = *((int *) 0xBC100080);
}
void sceSysreg_driver_7911A536 (int arg1){
	intr = sceKernelCpuSuspendIntr ();
	*((int *) 0xBC100080) = (((arg1 & ((*((int *) 0xBC100080) >> 1) & 0xF)) & 0xF) << 1);
	sceKernelCpuResumeIntrWithSync (intr);
}
void sceSysreg_driver_F464A3D9 (){
	return *((int *) 0xBC1000B0);
}
void sceSysreg_driver_8D4FE210 (int arg1){
	intr = sceKernelCpuSuspendIntr ();
	*((int *) 0xBC1000B0) = ((arg1 & (*((int *) 0xBC1000B0) & 7)) & 7);
	sceKernelCpuResumeIntrWithSync (intr);
}
void sceSysreg_driver_49B453CB (int arg1){
	if ((arg1<0)||(arg1>=2))return;
	return *((int *) 0xBC100080);
}
void sceSysreg_driver_36BBA207 (int arg1){
	if ((arg1<0)||(arg1>=2))return;
	return *((int *) 0xBC100080);
}
void sceSysreg_driver_BA43633B (int arg1, int arg2){
	if ((arg1<0)||(arg1>=2))return;
	intr = sceKernelCpuSuspendIntr ();
	*((int *) 0xBC100080) = (((arg2 & (((*((int *) 0xBC100080) >> (arg1 << 3)) >> 9) & 7)) << 9) << (arg1 << 3));
	sceKernelCpuResumeIntrWithSync (intr);
}
void sceSysreg_driver_EEE7B082 (){
	__asm__ ("sync;");
	*((int *) 0xBC100044) = 1;
	__asm__ ("sync;");
}
int sceSysreg_driver_461B8077 (){
	__asm__ ("mfc0			 $v1, COP0_22;" : "=r"(var1));
	__asm__ ("sync;");
	*((int *) 0xBC100048) = var1 + 1;
	return (!(((*((int *) 0xBC100048) & 3) ^ *((int *) 0xBC100048))) ? 0 : -1);
}
void sceSysreg_driver_0E6301D0 (){
	__asm__ ("sync;");
	*((int *) 0xBC100048) = 0;
	__asm__ ("sync;");
}
int sceSysreg_driver_F03852E0 (int arg1){
	intr = sceKernelCpuSuspendIntr ();
	while (sceSysreg_driver_461B8077 ());
	sceSysreg_driver_0E6301D0 ();
	sceKernelCpuResumeIntr (intr);
	return *arg1;
}
int sceSysreg_driver_9CE69EC1 (int arg1, int arg2, int arg3){
	intr = sceKernelCpuSuspendIntr ();
	while (sceSysreg_driver_461B8077 ()<0);
	*arg1 = ((*arg1 & arg2) | arg3);
	sceSysreg_driver_0E6301D0 ();
	sceKernelCpuResumeIntr (intr);
	return *arg1;
}
void sceDdrInit (){
	return;
}
void sceDdrEnd (){
	return;
}
void sceDdrSuspend (){
	return;
}
void sceDdrResume (){
	return;
}
void sceDdrFlush (int arg1){
	__asm__ ("sync;");
	*((int *) 0xBD000004) = arg1 & 0xF;
	while (*((int *) 0xBD000004) & (arg1 & 0xF));
}
void sceDdr_driver_647FEC11 (int arg1){
	*((int *) 0xBD00002C) = ((((arg1 < 1))) ? 0 : (0x80000000 | arg1));
	__asm__ ("sync;");
	return;
}
void sceDdr_driver_DC921C35 (){
	return *((int *) 0xBD00002C);
}
int sceDdr_driver_C6B7CCDE (){
	int i = 1,j;
	for (j = 0x40;j>0;j--) {
		*((int *) 0xBD000040) = 0x2B;
		if ((*((int *) 0xBD000040) & 0x0100))break;
		i++;
	}
	while (i + 1) {
		*((int *) 0xBD000040) = 0x2A;
	}
	*((int *) 0xBD000040) = 0x20;
	__asm__ ("sync;");
	return i;
}
void sceDdr_driver_CFC352DF (int arg1, int arg2, int arg3){
	while (((*((int *) 0xBD000020) >> 16) & 1));
	*((int *) 0xBD000024) = ((((arg1 & 1) << 0x0A) | (arg2 << 0x10)) | (arg3 & 0x7BFF));
	__asm__ ("sync;");
	*((int *) 0xBD000020) = (arg1 | 0x8000);
	__asm__ ("sync;");
	while ((*((int *) 0xBD000020) >> 16) & 1);
}
void sceDdr_driver_75B600EF (int arg1, int arg2, int arg3, int arg4){
	sceDdr_driver_19423D2C (arg3);
	sceDdr_driver_D341BACD ();
	var6 = t8;
	if (var6<0)var6 = 1;
	sceDdr_driver_740F2933 (t7, var6);
}
void sceDdr_driver_19423D2C (int arg1){
	int *var1 = 0xB970 + (arg1 << 3);
	*((int *) 0xBD000030) = (((*((int *) 0xBD000030) | 0x31) ^ 0x31) | var1[0]);
	*((int *) 0xBD000038) = var1[1];
	__asm__ ("sync;");
}
void sceDdr_driver_ABFCB233 (){
	return *((int *) 0xBD000030);
}
void sceDdr_driver_740F2933 (int arg1, int arg2){
	sceDdr_driver_CFC352DF (0x25, 0, 0);
	sceDdr_driver_CFC352DF (0x22, 0, 0);
	sceDdr_driver_CFC352DF (0x22, 0, 0);
	sceDdr_driver_CFC352DF (0x20, 0, (arg1 << 0x04) | 1);
	sceDdr_driver_CFC352DF (0x20, 2, (arg2 << 0x05));
}
void sceDdr_driver_B4D05E62 (int arg1, int arg2){
	sceDdr_driver_CFC352DF (0x20, 2, (arg2 << 0x05));
}

//TO BE DONE ...

