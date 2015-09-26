#include <pspkernel.h>
#include <pspsdk.h>
#include <string.h>

#define UNQUEUED_MASK 0x0001
#define TRANSFER_MASK 0x0002
#define SUCCED_MASK 0x0010
#define PENDING_MASK 0x0020
#define FINISHED_MASK 0x0040
#define USED_MASK 0x0070
#define ASSIGNED_MASK 0x0100
#define MALLOCED_MASK 0x1000
typedef struct _DmaOp{
	struct _DmaOp* curr;//current op
	struct _DmaOp* next;//next op
	int unk2;
	int unk3;
	void* onSuspend;
	void* onResume;
	int ev;
	short state,unk15s;
	int unk8;//reqA
	int unk9;//reqA
	int unk10;//reqB
	int unk11;//reqB
	int unk12;//0xC001 (action?)
	short mask,unk27;
	int unk14;
	int unk15;
}DmaOp;

PSP_MODULE_INFO("dmac_driver", 0x1007, 1, 1);

int*ctx_header;//0x2000
DmaOp ctx[64];//[0x20*16];//0x2040 32 op
DmaOp*lastDMAop;//0x4000 [26]
DmaOp*currDMAop;//0x4050
DmaOp*nextDMAop;//0x4050
void *SyncCallback;//0x4058
int reservedChan;//0x4040
int reservedChan2;//0x4044
int suspended;//0x4048
/*sub*/
void clearDma (int type){
	if(*((int*)0xBC100050) & (0x20 << type))return;
	*((int*)0xBC100050)|=(0x20 << type);
	int*addr = (type) ? (int*)0xBCA00000 : (int*)0xBC900000;
	addr[12]|= 1;
	addr[13] = 0;
	for(int i=8;i>=0;i--,addr+=0x20) {
		addr[64] = 0;
		addr[65] = 0;
		addr[66] = 0;
		addr[67] = 0;
		addr[68] = 0;
	}
	addr[2] = 0xFF;
	addr[4] = 0xFF;
}
void OpSync (DmaOp*op){
	int*addr = (op->unk15 >> 3) ? (int*)0xBCA00000 : (int*)0xBC900000;
	while ((addr[8*(op->unk15&7)+4] &= ~2) & UNQUEUED_MASK);
	int tmp = 1 << (op->unk15 & 7);
	op->mask = PENDING_MASK;
	suspended &= !(1 << op->unk15);
	op->unk15 = -1;
	ctx_header[op->unk15] = 0;
	addr[2] = tmp;
	addr[4] = tmp;
}
int callback (){
	__asm__ ("sync;");
	return /*((((ra >> 0x1F) + 2) << 0x1D) | ra)[0]*/0;
}
void buildDMAop (){
}
int sceKernelDmaOpAllCancel ();
void suspendHandler (){
	for (int i=15;i>=i;i--)
		/*if(0x2000[i])OpSync (*0x2000[i])*/;
	suspended = 0;
	sceKernelDmaOpAllCancel ();
	sceKernelDisableIntr (0x16);
	sceKernelDisableIntr (0x17);
}
void resumeHandler (){
	if(reservedChan & 0xFF00)clearDma (1);
	if(reservedChan & 0x00FF)clearDma (0);
	sceKernelEnableIntr (0x16);
	sceKernelEnableIntr (0x17);
}
/*exports*/
int module_start(int args,char*argp){
	int intr = sceKernelCpuSuspendIntr ();
	memset (ctx,0,0x2000);
	DmaOp*p1 = ctx;
	lastDMAop = ctx;
//	ctx += 0x40;
	DmaOp*p2 = p1+3*0x40;
	int i;
	for(i=2;i<2*0x40;i++) {//try to understand this
//		p1[16] = p2;
//		p1[17] = p1;
		p2 += 0x40;
//		p1 += 0x40;
//		p1[6+4] = 0x1000;
	}
	lastDMAop->mask = 0x1000;
	nextDMAop = 0;
	lastDMAop->curr = 0;
	currDMAop = 0;
//	_sceKernelDmaSetCallback (callback);
	sceKernelCpuResumeIntr(intr);
	return 0;
}
void sceKernelDmaExit (){
	int*interupt;
	for (int i=0;i<2;i++) {
		for(int j=0;j<8;j++) {
			interupt = (i) ? &((int*)0xBCA00100)[2*j]:&((int*)0xBC900100)[2*j];
			interupt[4] |= 0x00040000;
			while(interupt[4] & 0x00020000){};
			interupt[4] &= 0xFFFF3FFE;
		}
	}
	sceKernelDmaOpAllCancel ();
	for(int i=0;i<2;i++) {
		interupt = (i) ? (int*)0xBCA00000 : (int*)0xBC900000;
		interupt[2] = 0xFF;
		interupt[4] = 0xFF;
		interupt[12] &= ~2;
		sceKernelReleaseIntrHandler (i + 0x16);
		int intr = sceKernelCpuSuspendIntr ();
		*((int *) 0xBC100050) &= !(0x0020 << (i+1));
		sceKernelCpuResumeIntr (intr);
	}
}
#define _sceKernelDmaSetSyncCallback DmacManForKernel_32757C57
void _sceKernelDmaSetSyncCallback (void* cb){
	SyncCallback=(cb?cb:callback);
}
void sceKernelDmaSoftRequest (int type,int value,int a,int b){
	int *p = (type) ? (int*)0xBCA00000 : (int*)0xBC900000;
	p[8+2*(!!b)+(!a)] = (1 << value);
	__asm__ ("sync;");
}
int sceKernelDmaOpFree (DmaOp* op){
	int intr = sceKernelCpuSuspendIntr ();
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if(op->mask & UNQUEUED_MASK)return 0x800202BE;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	op->curr = lastDMAop;
	op->next = 0;
	op->onSuspend = 0;
	op->unk8 = 0;
	op->unk9 = 0;
	op->unk10 = 0;
	op->unk11 = 0;
	op->unk12 = 0;
	op->mask = 0;
	op->unk15 = -1;
	if(lastDMAop)lastDMAop->next = op;
	op->mask = MALLOCED_MASK;
	lastDMAop = op;
	sceKernelDeleteEventFlag (op->ev);
	sceKernelCpuResumeIntr (intr);
	return 0;
}
int sceKernelDmaOpEnQueue (DmaOp* op){
	if(!op)return 0x800202CF;
	if(!op->unk2)return 0x800202CD;
	int intr = sceKernelCpuSuspendIntr ();
	while (op->unk3) {
		if( op->mask & UNQUEUED_MASK)return 0x800202BE;
		if( op->mask & MALLOCED_MASK)return 0x800202C3;
		if(!op->mask & ASSIGNED_MASK)return 0x800202C1;
		if( op->mask & TRANSFER_MASK)return 0x800202C0;
		if( op->mask & USED_MASK)return 0x800202C4;
		if(!currDMAop)currDMAop=op;
		op->curr = NULL;
		op->next = nextDMAop;
		if(nextDMAop)nextDMAop=op;
		nextDMAop = op;
		op->mask |= UNQUEUED_MASK;
		buildDMAop ();
	}
	sceKernelCpuResumeIntr (intr);
	return 0;
}
int sceKernelDmaOpDeQueue (DmaOp* op){
	if(!op)return 0x800202CF;
	if((op->mask & MALLOCED_MASK))return 0x800202C3;
	if(!(op->mask & ASSIGNED_MASK))return 0x800202C1;
	if((op->mask & TRANSFER_MASK))return 0x800202C0;
	if(!(op->mask & UNQUEUED_MASK))return 0x800202BF;
	int intr = sceKernelCpuSuspendIntr ();
	if(op->next)op->next->curr = op->curr;
	if(op->curr)op->curr->next = op->next;
	if(nextDMAop == op)nextDMAop = nextDMAop->next;
	if(currDMAop == op)currDMAop = currDMAop->curr;
	op->next = NULL;
	op->curr = NULL;
	op->mask &= ~2;
	sceKernelCpuResumeIntr (intr);
	return 0;
}
int sceKernelDmaOpAllCancel (){
	if(currDMAop)return 0x800202BF;
	int intr = sceKernelCpuSuspendIntr ();
	for (int i=0;!ctx_header;i++) {
		if(i < 16){
//			ctx_header = ctx_header[i];
			continue;
		}
		//nothing found in ctx header :
		if(currDMAop){
			currDMAop->next = NULL;
			currDMAop->curr = NULL;
		}
		nextDMAop = NULL;
		currDMAop = NULL;
		sceKernelCpuResumeIntr (intr);
		return 0x800202C0;
	}
	sceKernelCpuResumeIntr (intr);
	return 0;
}
int sceKernelDmaOpSetCallback (DmaOp* op,void* suspend,void* resume){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if((!op->mask & ASSIGNED_MASK))return 0x800202C1;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	if(op->mask & USED_MASK)return 0x800202C4;
	op->onSuspend = suspend;
	op->onResume = resume;
	return 0;
}
int sceKernelDmaOpSetupMemcpy (DmaOp* op,int src,int dst,int len){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if((!op->mask & ASSIGNED_MASK))return 0x800202C1;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	if(op->mask & USED_MASK)return 0x800202C4;
	if(len >= 0x1000)return 0x800202CE;
	op->unk8 = dst;
	op->unk9 = src;
	op->unk10 = 0;
	op->unk11 = (len | 0x8C4BF000);
	op->unk12 |= 0xC001;
	return 0;
}
int sceKernelDmaOpSetupNormal (DmaOp* op,int arg2,int arg3,int arg4,int arg5){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if((!op->mask & ASSIGNED_MASK))return 0x800202C1;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	if(op->mask & USED_MASK)return 0x800202C4;
	op->unk8 = arg4;
	op->unk9 = arg3;
	op->unk10 = 0;
	op->unk11 = (arg5 | 0x80000000);
	op->unk12 |= (arg2 | 0xC001);
	return 0;
}
int  sceKernelDmaOpSetupLink (DmaOp* op,int cmd,DmaOp* arg3){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if((!op->mask & ASSIGNED_MASK))return 0x800202C1;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	if(op->mask & USED_MASK)return 0x800202C4;

	arg3 = (DmaOp*) (0xA0000000 | (((((int)arg3) & -4)) & 0x1FFFFFFF));
//	op->mask = arg3;
	op->unk8  = (int)arg3->curr;
	op->unk9  = (int)arg3->next;
	op->unk10 = (int)arg3->unk2;
	op->unk11 = (int)arg3->unk3;
	op->unk12 |= (cmd | 0xC001);
	while (arg3->unk2) {
		arg3 = (DmaOp*)(0xA0000000 | (arg3->unk2 & 0x1FFFFFFF));
	}
	arg3->unk3 |= 0x80000000;
//	(*SyncCallback) (4,((op[12] | cmd) | 0xC001),op[12] | cmd,arg3[2],0xA0000000,arg3[2],arg3[2],0);
	op->unk15 = (int)arg3;
	return 0;
}
int sceKernelDmaOpSync (DmaOp* op,int arg2,unsigned evParam){
	if(op->mask)return 0x800202CF;
	if(!(op->mask & MALLOCED_MASK))return 0x800202C3;
	if(op->mask & ASSIGNED_MASK)return 0x800202C1;
	if(!(op->mask & PENDING_MASK))return 0x800202C6;
	if(arg2 == 1)return (sceKernelWaitEventFlag (op->ev,6,0x11,0,0)) ? 0x80020001 : 0;
	if(arg2 < 2){//error
		if(arg2)return 0x80020001;//impossible ?
		if(op->mask & FINISHED_MASK)return 0x80020001;
		if(!(op->mask & SUCCED_MASK))return 0x800202C7;
		if(!(op->mask & UNQUEUED_MASK))return 0x800202BE;
		if(op->mask & TRANSFER_MASK)return 0x800202C0;
		return 0x800202BF;
	}else{
		if(arg2 != 0x0002)return 0x80020001;
		int res = sceKernelWaitEventFlag (op->ev,0x0006,0x0010,0x0000,&evParam);
		if(!res)return 0;
		if(res != 0x800201A8)
			return 0x80020001;
		OpSync (op);
		return 0x800202C2;
	}
	return 0;
}
void sceKernelDmaChExclude (int ch,int arg2){
	if(ch>15)return;
	if(reservedChan2 & (1 << ch))return;
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2){
		reservedChan |= (1 << ch);
		clearDma (ch >> 3);
	}else{
		reservedChan &= !(1 << ch);
	}
	sceKernelCpuResumeIntr (intr);
	return;
}
void sceKernelDmaChReserve (int arg1,int arg2){
	if(reservedChan & (1 << arg1))return;
	int intr = sceKernelCpuSuspendIntr ();
	if(arg2 < 0)reservedChan2 &= !(1 << arg1);
	else reservedChan2 |=  (1 << arg1);
	sceKernelCpuResumeIntr (intr);
}
void sceKernelDmaOpAlloc (){
	if(!lastDMAop)return;
	if(lastDMAop->mask & MALLOCED_MASK)return;
	int intr=sceKernelCpuSuspendIntr ();
	DmaOp*op=lastDMAop;
	op->unk2 = 0;
	op->unk3 = 0;
	op->onSuspend = 0;
	op->ev = sceKernelCreateEventFlag ("SceDmacmanEvflag",0,0,0);
	op->mask = 0;
	op->unk15 = -1;
	op->mask = -1;
	sceKernelCpuResumeIntr (intr);
	return;
}
int sceKernelDmaOpAssign (DmaOp* op,char lo,char hi,int arg4){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	if(op->mask & UNQUEUED_MASK)return 0x800202BE;
	if(op->mask & TRANSFER_MASK)return 0x800202C0;
	op->unk12=arg4;
	op->mask=(hi<<8)|lo;
	op->mask=ASSIGNED_MASK;
	return 0;
}
void sceKernelDmaOnDebugMode (){
	return;
}
int sceKernelDmaOpFreeLink (DmaOp* op){
	if(!op)return 0x800202CF;
	if(op->mask & MALLOCED_MASK)return 0x800202C3;
	return (op->mask & ASSIGNED_MASK) ? 0 : 0x800202C1;
}
int module_stop(){
	return 0;
}