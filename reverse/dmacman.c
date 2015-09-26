#include <pspsdk.h>
#include "500\dmacman.h"

#define UNQUEUED_MASK 0x0001
#define TRANSFER_MASK 0x0002
#define SUCCED_MASK 0x0010
#define PENDING_MASK 0x0020
#define FINISHED_MASK 0x0040
#define USED_MASK 0x0070
#define ASSIGNED_MASK 0x0100
#define MALLOCED_MASK 0x1000

typedef struct {
	void* curr,//current op
	void* next,//next op
	int unk2,
	int unk3,
	void* onSuspend,
	void* onResume,
	int ev,
	short state,
	short unk15s,
	int unk8,//reqA
	int unk9,//reqA
	int unk10,//reqB
	int unk11,//reqB
	int unk12,//0xC001 (action?)
	short mask,
	short unk27,
	int unk14,
	int unk15,
}DmaOp;
int ctx_header;//0x2000
int ctx[0x20*16];//0x2040 32 op
DmaOp*lastDMAop;//0x4000 [26]
DmaOp*currDMAop;//0x4050
DmaOp*nextDMAop;//0x4050
void *SyncCallback;//0x4058
void module_start (){
	intr = sceKernelCpuSuspendIntr ();
	memset (ctx,0,0x2000);
	p1 = ctx;
	lastDMAop = ctx;
	ctx += 0x40;
	p2 = p1+3*0x40;
	int i = 2;
	while (i < 2*0x40) {//try to understand this
		p1[16] = p2;
		p1[17] = p1;
		p2 += 0x40;
		p1 += 0x40;
		(p1 + 0x10)[6] = 0x1000;
		i++;
	}
	lastDMAop.mask = 0x1000;
	nextDMAop = 0;
	lastDMAop[0] = 0;
	currDMAop = 0;
	sceKernelRegisterSuspendHandler (0x14,suspendHandler,0);//0x1AF0
	sceKernelRegisterResumeHandler (0x14,resumeHandler,0);//0x1B80
	ret |= sceKernelRegisterIntrHandler (0x16,2,intrHandler,0,0);
	ret |= sceKernelEnableIntr (0x16);
	ret |= sceKernelRegisterIntrHandler (0x17,2,intrHandler,1,0);
	ret |= sceKernelEnableIntr (0x17);
	if(ret < 0){
		ret = 0x800202BC;
		for(int i=0;i<2;i++)
			sceKernelReleaseIntrHandler (0x16+i);
	}
	_sceKernelDmaSetCallback (callback);
	sceKernelCpuResumeIntr (intr);
	return ret;
}
void sceKernelDmaExit (){
	for (i=0;i < 2;i++) {
		for(int j=0;j<8;j++) {
			interupt = (i) ? ((j<<5) + 0xBCA00100) : ((j<<5) + 0xBC900100);
			interupt[4] |= 0x00040000;
			while (interupt[4] & 0x00020000){};
			interupt[4] &= 0xFFFF3FFE;
		}
	}
	sceKernelDmaOpAllCancel ();
	for(i=0;i<2;i++) {
		interupt = (i) ? 0xBCA00000 : 0xBC900000;
		interupt[2] = 0xFF;
		interupt[4] = 0xFF;
		interupt[12] &= ~2;
		sceKernelReleaseIntrHandler (i + 0x16);
		intr2 = sceKernelCpuSuspendIntr ();
		*((int *) 0xBC100050) &= !(0x0020 << (i+1));
		sceKernelCpuResumeIntr (intr2);
	}
	return;
}
#define _sceKernelDmaSetSyncCallback DmacManForKernel_32757C57
void _sceKernelDmaSetSyncCallback (void* cb){
	SyncCallback=(cb?cb:callback);
}
void sceKernelDmaSoftRequest (int type,int value,int a,int b){
	int *var1 = (type) ? 0xBCA00000 : 0xBC900000;
	var1[8+2*(!!b)+(!a)] = (1 << value);
	__asm__ ("sync;");
}
void sceKernelDmaOpFree (DmaOp* op){
	intr = sceKernelCpuSuspendIntr ();
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if(op.mask & UNQUEUED_MASK)return 0x800202BE;
	if(op.mask & TRANSFER_MASK)return 0x800202C0;
	op[0] = lastDMAop;
	op[1] = 0;
	op[4] = 0;
	op[8] = 0;
	op[9] = 0;
	op[10] = 0;
	op[11] = 0;
	op[12] = 0;
	op.mask = 0;
	op[15] = -1;
	if(lastDMAop)lastDMAop.next = op;
	op.mask = MALLOCED_MASK;
	lastDMAop = op;
	sceKernelDeleteEventFlag (op[6]);
	sceKernelCpuResumeIntr (intr);
	return 0;
}
void sceKernelDmaOpEnQueue (DmaOp* op){
	if(!op)return 0x800202CF;
	if(!op[2])return 0x800202CD;
	intr = sceKernelCpuSuspendIntr ();
	while (op[3]) {
		if( op.mask & UNQUEUED_MASK)return = 0x800202BE;
		if( op.mask & MALLOCED_MASK)return 0x800202C3;
		if(!op.mask & ASSIGNED_MASK)return 0x800202C1;
		if( op.mask & TRANSFER_MASK)return 0x800202C0;
		if( op.mask & USED_MASK)return 0x800202C4;
		if(!currDMAop)currDMAop=op;
		op.curr = NULL;
		op.next = nextDMAop
		if(nextDMAop)*nextDMAop=op;
		nextDMAop = op;
		op.mask |= UNQUEUED_MASK;
		buildDMAop ();
	}
	sceKernelCpuResumeIntr (intr);
	return 0;
}
void sceKernelDmaOpDeQueue (DmaOp* op){
	if(!op)return 0x800202CF;
	if((op.mask & MALLOCED_MASK))return 0x800202C3;
	if(!(op.mask & ASSIGNED_MASK))return 0x800202C1;
	if((op.mask & TRANSFER_MASK))return 0x800202C0;
	if(!(op.mask & UNQUEUED_MASK))return 0x800202BF;
	intr = sceKernelCpuSuspendIntr ();
	if(op.next)op.next.curr = op.curr;
	if(op.curr)op.curr.next = op.next;
	if(nextDMAop == op)nextDMAop = nextDMAop.next;
	if(currDMAop == op)currDMAop = currDMAop.curr;
	op.next = NULL;
	op.curr = NULL;
	op.mask &= ~2;
	sceKernelCpuResumeIntr (intr);
}
void sceKernelDmaOpAllCancel (){
	if(currDMAop)return 0x800202BF;
	intr = sceKernelCpuSuspendIntr ();
	for (int i=0;!*(0x2000);i++) {
		if(i < 16){
			*(0x2000) = ctx_header[i];
			continue;
		}
		//nothing found in ctx header :
		if(currDMAop){
			currDMAop.next = NULL;
			currDMAop.curr = NULL;
		}
		nextDMAop = NULL;
		currDMAop = NULL;
		sceKernelCpuResumeIntr (intr);
		return 0x800202C0;
	}
	sceKernelCpuResumeIntr (intr);
}
void sceKernelDmaOpSetCallback (DmaOp* op,void* suspend,void* resume){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if((!op.mask & ASSIGNED_MASK))return 0x800202C1;
	if(op.mask & TRANSFER_MASK)return 0x800202C0;
	if(op.mask & USED_MASK)return 0x800202C4;
	op[4] = suspend;
	op[5] = resume;
	return 0;
}
void sceKernelDmaOpSetupMemcpy (DmaOp* op,int src,int dst,int len){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if((!op.mask & ASSIGNED_MASK))return 0x800202C1;
	if(op.mask & TRANSFER_MASK)return 0x800202C0;
	if(op.mask & USED_MASK)return 0x800202C4;
	if(len >= 0x1000)return 0x800202CE;
	op[8] = dst;
	op[9] = src;
	op[10] = 0;
	op[11] = (len | 0x8C4BF000);
	op[12] |= 0xC001;
	return 0;
}
void sceKernelDmaOpSetupNormal (DmaOp* op,int arg2,int arg3,int arg4,int arg5){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if((!op.mask & ASSIGNED_MASK))return 0x800202C1;
	if(op.mask & TRANSFER_MASK)return 0x800202C0;
	if(op.mask & USED_MASK)return 0x800202C4;
	op[8] = arg4;
	op[9] = arg3;
	op[10] = 0;
	op[11] = (arg5 | 0x80000000);
	op[12] |= (arg2 | 0xC001);
	return 0;
}
void sceKernelDmaOpSetupLink (DmaOp* op,int cmd,DmaOp* arg3){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if((!op.mask & ASSIGNED_MASK))return 0x800202C1;
	if(op.mask & 0x0002)return 0x800202C0;
	if(op.mask & 0x0070)return 0x800202C4;

	arg3 = 0xA0000000 | (((arg3 & 0xFFFFFFFC)) & 0x1FFFFFFF);
	op.mask = arg3;
	op[8]  = arg3[0];
	op[9]  = arg3[1];
	op[10] = arg3[2];
	op[11] = arg3[3];
	op[12] |= (cmd | 0xC001);
	while (arg3[2]) {
		arg3 = 0xA0000000 | (arg3[2] & 0x1FFFFFFF);
		var17 = arg3[2];
		var16 = arg3[2];
	}
	arg3[3] |= 0x80000000;
	(*SyncCallback) (4,((op[12] | cmd) | 0xC001),op[12] | cmd,arg3[2],0xA0000000,var17,var16,0);
	op[15] = arg3;
	return 0;
}
void sceKernelDmaOpSync (DmaOp* op,int arg2,int evParam){
	if(!(op.mask == 0x0000))return 0x800202CF;
	if(!((op.mask & MALLOCED_MASK) != 0x0000))return 0x800202C3;
	if(!((op.mask & ASSIGNED_MASK) == 0x0000))return 0x800202C1;
	if(!((op.mask & PENDING_MASK) != 0x0000))return 0x800202C6;
	if(arg2 == 1)return (sceKernelWaitEventFlag (op[6],0x0006,0x0011,0x0000,0x0000)) ? 0x80020001 : 0;
	if(arg2 < 2){//error
		if(arg2)return 0x80020001;//impossible ?
		if(op.mask & FINISHED_MASK)return 0x80020001;
		if(!(op.mask & SUCCED_MASK))return 0x800202C7;
		if(!(op.mask & UNQUEUED_MASK))return 0x800202BE;
		if(op.mask & TRANSFER_MASK)return 0x800202C0;
		return 0x800202BF;
	}else{
		if(arg2 != 0x0002)return 0x80020001;
		res = sceKernelWaitEventFlag (op[6],0x0006,0x0010,0x0000,&arg3);
		if(!res)return 0;
		if(res != 0x800201A8)
			return 0x80020001;
		OpSync (op);
		return 0x800202C2;
	}
	return 0;
}
void OpSync (int arg1){
	addr = (op[15] >> 3) ? 0xBCA00000 : 0xBC900000;
	while ((((op[15]&7)<<5)+addr)[4] &= ~2) & UNQUEUED_MASK) {}
	var12 = 1 << (op[15] & 7);
	op.mask = PENDING_MASK;
	*((int *) 0x4048) &= !(1 << op[15]);
	op[15] = -1;
	((op[15] << 2) + 0x2000)[0] = 0;
	addr[2] = var12;
	addr[4] = var12;
}
void sceKernelDmaOpQuit (DmaOp* op){
	intr = sceKernelCpuSuspendIntr ();
	if(!op)return 0x800202CF;
	if(!(op.mask & MALLOCED_MASK))return 0x800202C3;
	if(op.mask & ASSIGNED_MASK)return 0x800202C1;
	if(!(op.mask & FINISHED_MASK))return 0x800202BF;
	if(!(op.mask & UNQUEUED_MASK))return 0x800202BE;
	if(!(op.mask & SUCCED_MASK))return 0x800202C7;
	if(!(op.mask & PENDING_MASK))return 0x800202C6;
	if(op.mask & 0x0002)return 0x80020001;
	OpSync (op);
	sceKernelCpuResumeIntrWithSync (intr);
	return 0;
}
void DmacManForKernel_E18A93A5 (DmaOp*op,int arg2){
  if(!op)return;
	var3 = 0xA0000000 | (arg2 & 0x1FFFFFFF);
	while (var3[2])
		var3 = 0xA0000000 | (var3[2] & 0x1FFFFFFF);
	var3[3] |= 0x80000000;
	var12 = (op.mask) & 0xFFFF;
	if((var12 & 0x00001170) != 0x00000100)return 0;
	intr = sceKernelCpuSuspendIntr ();
	if(!(var12&2){
		if(!var12&1)return 0x80020001;
		op[15][2] = arg2;
		op[15] = var3;
	}else{
		var17 = ((var14&7)<<5) + (((char) op[15])>>3)?0xBCA00100:0xBC900100;
		var17[4] |= 0x00040000;
		if(!var17[2]){
			var36 = (var17[4]|0x00040000) & 0x01003800;
			if(((((var36 ^ 0x01000000) < 1)) | (((var36 ^ 0x01001000) < 1))))return 0x800202BC;
			if(var36 == 0x01003000)return 0x800202BC;
			while (var17[4] & 0x00020000) {}
			if(!(var17[3] & 0x0FFF))return 0x800202C4;
			var17[4] &= ~2;
			while (var17[4]&1) {}
			var17[2] = arg2;
			var17[4]|=1;
		}else op[15][2] = arg2;
		op[15] = var3;
		var17[4] |= var17[4] & 0xFFFBFFFF;
	}
	(*0x00004058) (4,var17[4],op[15],var17[4],op[15],0,var20,0x00040000);
	sceKernelCpuResumeIntrWithSync (intr);
}
void sceKernelDmaOpAssignMultiple (DmaOp**op,int n){
	if((((n -2) >= 16)))return 0x800202BD;
	for (int i=0;i<16;i++)
		n -= 1&(((unsigned short *) op[0])[26] >> i);
	if(n<0)return 0x800202BD;
	for(i=0;i<n;i++) {
		if(!op[i])return 0x800202CF;
		if((op[i][14] & MALLOCED_MASK))return 0x800202C3;
		if(!(op[i][14] & ASSIGNED_MASK))return 0x800202C1;
		if((op[i][14] & UNQUEUED_MASK))return 0x800202BE;
		if((op[i][14] & 0x0002))return 0x800202C0;
		if((op[i][14] & 0x0070))return 0x800202C4;
	}
	intr = sceKernelCpuSuspendIntr ();
	while (i=0;i < n-1;i++) {//re-reverse
		op.curr[3] = op.next;
		op.next[2] = op.curr;
		op.curr.curr = NULL;
		op.curr.next = NULL;
		op.next.mask = op.curr.mask;
	}
	arg1.curr[27] = n;
	sceKernelCpuResumeIntr (intr);
}
void intrHandler (int unused,int type){
	intr = sceKernelCpuSuspendIntr ();
	addr = (type) ? 0xBCA00000 : 0xBC900000;
	value = (addr[3] | addr[1]) & 0xFF;
	for (i = 0;value >= (1 << i);i++) {
		if(value & (1 << i))continue;
		op = (0x2000)[(type*2)+i];
		if(!op){
			if(!(*((int *) 0x4040) & (1 << ((type << 3) + i))))
				Kprintf ("Fatal error: Stray interrupt occurred\n");
			continue;
		}
		var46 = i << 5 + addr;
		op[8] = var46[0];
		op[9] = var46[1];
		op[10] =var46[2];
		op[11] =var46[3];
		op[12] =var46[4];
		if(!((addr[1][1] & (1 << i))){
			if(var46[2]&&(var46[4]&1))OpSync (op);
			op.mask |= 0x10;
			*((int *) 0x4048) &= !(1 << ((type << 3) + i));
			((int *) ((((type << 3) + i) << 2) + 0x2000))[0] = 0;
			op.mask &= ~2;
			op[15] = -1;
			if(op[6] > 0)sceKernelSetEventFlag (op[6],4);
			((type) ? 0xBCA00000 : 0xBC900000)[4] = (1 << i);
			var61 = -1;
		}else{
			if(!var46[2] && !(var46[4]&1)){
				*((int *) 0x4048) &= !(1 << ((type << 3) + i));
				((int *) ((((type << 3) + i) << 2) + 0x2000))[0] = 0;
				op.mask = ((op.mask | 0x0040) & ~2);
				op[15] = -1;
				if(op[6]>0)sceKernelSetEventFlag (op[6],2);
			}
			((type) ? 0xBCA00000 : 0xBC900000)[2] = (1 << i);
			var61 = 0;
		}
		if(!op[4]||((*var62) (op,var61,((type << 3) + i),op[5]) != 1))continue;
		if(op.mask){
			op[8]  = op.mask[0];
			op[9]  = op.mask[1];
			op[10] = op.mask[2];
			op[11] = op.mask[3];
		}
		if(!currDMAop)currDMAop = op;
		op[0] = 0;
		op[1] = nextDMAop;
		if(nextDMAop)nextDMAop[0] = op;
		nextDMAop = op;
		op.mask |= 1;
	}
	if(!currDMAop)buildDMAop ();
	var14 = *((int *) 0x4040) | *((int *) 0x4048);
	if(!(var14 & 0xFF))
		*((int *) 0xBC100050) &= ~0x20;
	if(!(var14 & 0xFF00))
		*((int *) 0xBC100050) &= ~0x40;
	sceKernelCpuResumeIntr (intr);
}
void buildDMAop (){
	var4 = *((int *) 0x4040) | *((int *) 0x4048);
	var5 = var4 ^ 0xFFFF;
	if((((0x0000 < currDMAop)) & ((0x0000 < var5)))){
		var6 = currDMAop[3];
		while (1) {
			if(!var6||!currDMAop[2]){
				var26 = currDMAop;
				while (1) {
					var27 = ((unsigned short *) var26)[15];
					var28 = (char) var27;
					if(var28 < 0){
						var55 = ((unsigned short *) var26)[26];
						var28 = CLZ ((BITREV ((var55 & (!var4)))));
						if(((var28 < 0x0010)) == 0x0000)
							break;
						((int *) ((var28 << 0x0002) + 0x2000))[0] = var26;
						var4 = var4 | (0x0001 << var28);
						((short *) var26)[15] = var28;
					}
					var29 = *((int *) 0xBC100050);
					var31 = 0x20 << (var28>>3);
					if(!(var29&var31)){
						*((int *) 0xBC100050) = (var29 | var31);
						var32 = (var28>>3) ? 0xBCA00000 : 0xBC900000;
						((int *) var32)[12]|= 1;
						((int *) var32)[13] = 0;
						for(i=7;i>=0;i--,var32+=0x20) {
							var32[64] = 0;
							var32[65] = 0;
							var32[66] = 0;
							var32[67] = 0;
							var32[68] = 0;
						}
						((int *) var32)[2] = 0x00FF;
						((int *) var32)[4] = 0x00FF;
					}
					var39 = ((var28 & 7)<<5) + (var28>>3) ?0xBCA00100:0xBC900100;
					((int *) var39)[0] = ((int *) var26)[8];
					((int *) var39)[1] = ((int *) var26)[9];
					((int *) var39)[2] = ((int *) var26)[10];
					((int *) var39)[3] = ((int *) var26)[11];
					((int *) var39)[4] = ((int *) var26)[12];
					((short *) var26)[14] |= 2;
					if(((int *) var26)[2]){
						var26 = ((int *) var26)[3];
					}else{
						var46 = ((unsigned short *) var26)[14];
						((short *) var26)[14] = ((var46 & 0xFFFFFFFE) | (0x0000 & UNQUEUED_MASK));
						if(nextDMAop == var26)nextDMAop = nextDMAop[1];
						if(currDMAop == var26) currDMAop = *currDMAop;
						var49 = ((int *) var26)[1];
						if(var49){
							((int *) var26)[1] = 0x0000;
							((int *) var49)[0] = ((int *) var26)[0];
						}
						var51 = ((int *) var26)[0];
						if(var51){
							var52 = ((int *) var26)[1];
							((int *) var26)[0] = 0x0000;
							((int *) var51)[1] = var52;
						}
						var26 = ((int *) var26)[3];
					}
					if(var26)continue;
					break;
				}
				currDMAop = currDMAop[0];
				var5 = var4 ^ 0xFFFF;
			label51:
				if(!((((0x0000 < currDMAop)) & ((0x0000 < var5)))))
					break;
				var6 = currDMAop[3];
				continue;
			}else{
				var9 = ((unsigned short *) currDMAop)[27];
				var10 = ((unsigned short *) currDMAop)[26] & (!var4);
				for (int i=1;i < 16;i++)
					var9 -= ((var10 >> i) & UNQUEUED_MASK);
				var12 = currDMAop;
				if(var9 >= 0){
					var23 = 0x1FFC;
					for (int i=0;var12;i++) {
						var25 = 1 << i;
						if(var10 & var25){
							var23[i] = var12;
							var4 |= var25;
							((short *) var12)[15] = i;
							var12 = var12[3];
						}
					}
					goto label16;
				}else{
					if((var13=currDMAop[0])){
						var13[1] = currDMAop[1];
						currDMAop[1] = var13;
						currDMAop[0] = var13[0];
						if(var13[1])var13[1][0] = var13;
						else currDMAop = var13;
						if(var13[0])	currDMAop[0][1] = currDMAop;
						else nextDMAop = currDMAop;
						var13[0] = currDMAop;
						currDMAop = var13;
						goto label51;
					}
				}
			}
			goto label54;
		}
	}
label54:
	*((int *) 0x4048) = (var4 & (!*((int *) 0x4040)));
}
void sceKernelDmaChExclude (int ch,int arg2){
	if(ch>15)return;
	if(*((int *) 0x4044) & (1 << ch))return;
	intr = sceKernelCpuSuspendIntr ();
	if(arg2){
		*((int *) 0x4040) |= (1 << ch));
		clearDma (ch >> 3);
	}else{
		*((int *) 0x4040) &= (!(1 << ch));
	}
	sceKernelCpuResumeIntr (intr);
	return;
}
void sceKernelDmaChReserve (int arg1,int arg2){
	if(*((int *) 0x4040) & (1 << arg1))return;
	intr = sceKernelCpuSuspendIntr ();
	if(arg2 < 0)	*((int *) 0x4044) &= !(1 << arg1);
	else *((int *) 0x4044) |=  (1 << arg1);
	sceKernelCpuResumeIntr (intr);
}
void sceKernelDmaOpAlloc (){
	if(!lastDMAop)return;
	if(lastDMAop.mask & MALLOCED_MASK)return;
	intr=sceKernelCpuSuspendIntr ();
	op=*lastDMAop;
	op[2] = 0;
	op[3] = 0;
	op[4] = 0;
	op[6] = sceKernelCreateEventFlag ("SceDmacmanEvflag");
	op.mask = 0;
	op[15] = -1;
	op[26] = -1;
	sceKernelCpuResumeIntr (intr);
	return;
}
void sceKernelDmaOpAssign (DmaOp* op,char lo,char hi,int arg4){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	if(op.mask & UNQUEUED_MASK)return 0x800202BE;
	if(op.mask & TRANSFER_MASK)return 0x800202C0;
	op[12]=arg4;
	op[26]=(hi<<8)|lo;
	op.mask=ASSIGNED_MASK;
	return 0;
}
void DmacManForKernel_1FC036B7 (int op,int arg2){
	op[15][2] = arg2;
	(*SyncCallback) (0x0004,arg2,0x0000,arg4,arg5,arg6,arg7,arg8);
	arg2 = 0xA0000000 | (arg2 & 0x1FFFFFFF);
	while (arg2[2])
		arg2 = (0xA0000000 | (arg2[2] & 0x1FFFFFFF))[2];
	op[15] = arg2;
}
void sceKernelDmaOnDebugMode (){
	return;
}
void sceKernelDmaOpFreeLink (DmaOp* op){
	if(!op)return 0x800202CF;
	if(op.mask & MALLOCED_MASK)return 0x800202C3;
	return (op.mask & ASSIGNED_MASK) ? 0 : 0x800202C1;
}
void suspendHandler (){
	for (n=15;n >= 0;n--)
		if(0x2000[i])OpSync (*0x2000[i]);
	*((int *) 0x4048) = 0;
	sceKernelDmaOpAllCancel ();
	sceKernelDisableIntr (0x16);
	sceKernelDisableIntr (0x17);
}
void resumeHandler (){
	if((*((int *) 0x4040) & 0xFF00))clearDma (1);
	if((*((int *) 0x4040) & 0x00FF))clearDma (0);
	sceKernelEnableIntr (0x16);
	sceKernelEnableIntr (0x17);
}
void callback (){
	__asm__ ("sync;");
	return ((((ra >> 0x1F) + 2) << 0x1D) | ra)[0];
}
void clearDma (int type){
	if(*(0xBC100050) & (0x20 << type))return;
	*(0xBC100050)|=(0x20 << type);
	addr = (type) ? 0xBCA00000 : 0xBC900000;
	addr[12]|= 1;
	addr[13] = 0;
	for(i=8;i>=0;i--,addr+=0x20) {
		addr[64] = 0;
		addr[65] = 0;
		addr[66] = 0;
		addr[67] = 0;
		addr[68] = 0;
	}
	addr[2] = 0xFF;
	addr[4] = 0xFF;
}
/*
void sample (int src, int dst, int len){
	if (!((0x00220202 >> ((src >> 27) & 0x1F))&1))return;
	void*op=sceKernelDmaOpAlloc ();
	sceKernelDmaOpAssign (op, 0xFF, 0xFF, 0, 0);
	bloc = len >> 2;
	sceKernelDmaOpSetupMemcpy (op,
		(((((src >> 0x1F)^1) << 0x1E) & 0xE0000000)|(src&~0xE0000000)),
		(((((dst >> 0x1F)^1) << 0x1E) & 0xE0000000)|(dst&~0xE0000000)), bloc);
	_len = bloc << 2;
	sceKernelDcacheInvalidateRange (src, _len);
	sceKernelDcacheWritebackInvalidateRange (p, _len);
	sceKernelDmaOpEnQueue (op);
	sceKernelDmaOpSync (op, 1, 0);
	sceDdrFlush (1);	
	sceKernelDmaOpFree (op);
}
*/