#include <pspsdk.h>
#include "500\dmacman.h"

#define UNQUEUED_MASK 0x0001
#define TRANSFER_MASK 0x0002
#define SUCCED_MASK 0x0010
#define PENDING_MASK 0x0020
#define FINISHED_MASK 0x0040
#define USED_MASK 0x0070
#define ASSIGNED_MASK 0x0100
#define FREE_MASK 0x1000

typedef struct {
	void* ctx,
	void* unk1,
	int unk2,
	int unk3,
	void* onSuspend,
	void* onResume,
	int unk6,//event
	short state,//unk14
	short unk15s,
	int unk8,//reqA
	int unk9,//reqA
	int unk10,//reqB
	int unk11,//reqB
	int unk12,//0xC001 (action?)
	short unk26,
	short unk27,
	int unk14,
	int unk15,
}DmaOp;
int ctx_header;//0x2000
int ctx[0x20*16];//0x2040 32 op
int* currentCtx;//0x4000 [26]
void* currentCB;//0x4058
int currentDMAop;//0x4050
int nextDMAop;//0x4050
void module_start (){
	suspend = sceKernelCpuSuspendIntr ();
	memset (ctx, 0, 0x2000);
	p1 = ctx;
	currentCtx = ctx;
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
	currentCtx[14] = 0x1000;
	nextDMAop = 0;
	currentCtx[0] = 0;
	currentDMAop = 0;
	sceKernelRegisterSuspendHandler (0x14, suspendHandler, 0);//0x1AF0
	sceKernelRegisterResumeHandler (0x14, resumeHandler, 0);//0x1B80

	ret = 0;
	ret |= sceKernelRegisterIntrHandler (0x16, 2, intrHandler, 0, 0);
	ret	|= sceKernelEnableIntr (0x16);
	ret |= sceKernelRegisterIntrHandler (0x17, 2, intrHandler, 1, 0);
	ret	|= sceKernelEnableIntr (0x16);

	i = 0;
	if (ret < 0){
		while (i < 2) {
			sceKernelReleaseIntrHandler (0x16);
			i++;
		}
		ret = 0x800202BC;
	}
	_sceKernelDmaSetCallback (callback);
	sceKernelCpuResumeIntr (suspend);
	return ret;
}
void sceKernelDmaExit (){
	suspend = sceKernelCpuSuspendIntr ();
	int i = 0;
	while (i < 2) {
		int j = 0;
		while (j < 8) {
			interupt = (i) ? ((j<<5) + 0xBCA00100) : ((j<<5) + 0xBC900100);
			interupt[4] |= 0x00040000;
			while (interupt[4] & 0x00020000){};
			interupt[4] &= 0xFFFF3FFE;
			j++;
		}
		i++;
	}
	sceKernelDmaOpAllCancel ();
	i = 0;
	while (i < 2) {
		interupt = (i) ? 0xBCA00000 : 0xBC900000;
		interupt[2] = 0xFF;
		interupt[4] = 0xFF;
		interupt[12] &= 0xFFFFFFFE;
		sceKernelReleaseIntrHandler (i + 0x16);
		i++;
		tmpIntr = sceKernelCpuSuspendIntr ();
		*((int *) 0xBC100050) &= !(0x0020 << i);
		sceKernelCpuResumeIntr (tmpIntr);
	}
	sceKernelCpuResumeIntr (suspend);
	return;
}
#define _sceKernelDmaSetSyncCallback DmacManForKernel_32757C57
void _sceKernelDmaSetSyncCallback (void* cb){
	currentCB=(cb?cb:callback);
}
void sceKernelDmaSoftRequest (int type, int value, int a, int b){
	int *var1 = (type) ? 0xBCA00000 : 0xBC900000;
	var1[8+2*(!!b)+(!a)] = (1 << value);
	__asm__ ("sync;");
}
void sceKernelDmaOpFree (DmaOp* arg1){
	var5 = sceKernelCpuSuspendIntr ();
	if(!arg1)return 0x800202CF;
	in = ((unsigned short *) arg1)[14];
	if (in & FREE_MASK)return 0x800202C3;
	if (in & UNQUEUED_MASK)return 0x800202BE;
	if (in & TRANSFER_MASK)return 0x800202C0;
	arg1[0] = currentCtx;
	arg1[1] = 0;
	arg1[4] = 0;
	arg1[8] = 0;
	arg1[9] = 0;
	arg1[10] = 0;
	arg1[11] = 0;
	arg1[12] = 0;
	arg1[14] = 0;
	arg1[15] = -1;
	if (currentCtx)currentCtx[1] = arg1;
	((short *) arg1)[14] = FREE_MASK;
	currentCtx = arg1;
	sceKernelDeleteEventFlag (arg1[6]);
	sceKernelCpuResumeIntr (var5);
	return 0;
}
void sceKernelDmaOpEnQueue (DmaOp* arg1){
	if (!arg1)return 0x800202CF;
	if (!arg1[2])return 0x800202CD;
	var9 = sceKernelCpuSuspendIntr ();
	while (arg1[3]) {
		in = ((unsigned short *) arg1)[14];
		if (in&1)return = 0x800202BE;
		if (in & FREE_MASK)return 0x800202C3;
		if (!in & ASSIGNED_MASK)return 0x800202C1;
		if (in & TRANSFER_MASK)return 0x800202C0;
		if (in & USED_MASK)return 0x800202C4;
		if (!currentDMAop)currentDMAop = arg1;
		arg1[0] = 0;
		arg1[1] = nextDMAop
		if (arg1[1])arg1[1][0] = arg1;
		nextDMAop = arg1;
		((short *) arg1)[14] |= UNQUEUED_MASK;
		buildDMAop ();
		sceKernelCpuResumeIntr (var9);
		return 0;
	}
}
void sceKernelDmaOpDeQueue (DmaOp* arg1){
	var1 = arg1;
	if (!arg1)return 0x800202CF;
	var6 = sceKernelCpuSuspendIntr ();
	in = ((unsigned short *) arg1)[14];
	if ((in & FREE_MASK))return 0x800202C3;
	if (!(var8 & ASSIGNED_MASK))return 0x800202C1;
	if ((var9 & TRANSFER_MASK))return 0x800202C0;
	if (!(var10 & UNQUEUED_MASK))return 0x800202BF;
	if (arg1[1])arg1[1][0] = arg1[0];
	if (arg1[0])arg1[0][1] = arg1[1];
	if (nextDMAop == arg1)nextDMAop = ((int *) arg1)[1];
	if (currentDMAop == arg1)currentDMAop = ((int *) arg1)[0];
	((int *) arg1)[1] = 0;
	((short *) arg1)[14] &= 0xFFFFFFFE;
	((int *) arg1)[0] = 0;
	sceKernelCpuResumeIntr (var6);
}
void sceKernelDmaOpAllCancel (){
	if (currentDMAop)return 0x800202BF;
	intr = sceKernelCpuSuspendIntr ();
	p = ctx_header;
	i = 0;
	res = *((int *) 0x2000);
	while (!res) {
		i++;
		p += 4;
		if (i < 16){
			res = p[0];
			continue;
		}
		if (currentDMAop){
			currentDMAop[1] = 0;
			currentDMAop[0] = 0;
		}
		nextDMAop = 0;
		currentDMAop = 0;
		sceKernelCpuResumeIntr (intr);
		return 0x800202C0;
	}
	sceKernelCpuResumeIntr (intr);
}
void sceKernelDmaOpSetCallback (DmaOp* arg1, void* suspend, void* resume){
	if (!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	if ((!arg1[14] & ASSIGNED_MASK))return 0x800202C1;
	if (arg1[14] & TRANSFER_MASK)return 0x800202C0;
	if (arg1[14] & USED_MASK)return 0x800202C4;
	arg1[4] = suspend;
	arg1[5] = resume;
	return 0;
}
void sceKernelDmaOpSetupMemcpy (DmaOp* arg1, int arg2, int arg3, int arg4){
	if (!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	if ((!arg1[14] & ASSIGNED_MASK))return 0x800202C1;
	if (arg1[14] & TRANSFER_MASK)return 0x800202C0;
	if (arg1[14] & USED_MASK)return 0x800202C4;
	if (arg4 >= FREE_MASK)return 0x800202CE;
	arg1[8] = arg3;
	arg1[9] = arg2;
	arg1[10] = 0;
	arg1[11] = (arg4 | 0x8C4BF000);
	arg1[12] |= 0xC001);
	return 0;
}
void sceKernelDmaOpSetupNormal (DmaOp* arg1, int arg2, int arg3, int arg4, int arg5){
	if (!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	if ((!arg1[14] & ASSIGNED_MASK))return 0x800202C1;
	if (arg1[14] & TRANSFER_MASK)return 0x800202C0;
	if (arg1[14] & USED_MASK)return 0x800202C4;
	arg1[8] = arg4;
	arg1[9] = arg3;
	arg1[10] = 0;
	arg1[11] = (arg5 | 0x80000000);
	arg1[12] |= (arg2 | 0xC001);
	return 0;
}
void sceKernelDmaOpSetupLink (DmaOp* arg1, int cmd, DmaOp* arg3){
	if (!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	if ((!arg1[14] & ASSIGNED_MASK))return 0x800202C1;
	if (arg1[14] & 0x0002)return 0x800202C0;
	if (arg1[14] & 0x0070)return 0x800202C4;

	arg3 = (0xA0000000 & 0xE0000000) | (((arg3 & 0xFFFFFFFC)) & 0x1FFFFFFF);
	arg1[14] = arg3;
	arg1[8] =  arg3[0];
	arg1[9] =  arg3[1];
	arg1[10] = arg3[2];
	arg1[11] = arg3[3];
	arg1[12] |= (cmd | 0xC001);
	if (arg3[2]){
		while (var17) {
			arg3 = (0xA0000000 & 0xE0000000) | (arg3[2] & 0x1FFFFFFF);
			var17 = arg3[2];
			var16 = arg3[2];
		}
	}
	arg3[3] |= 0x80000000;
	(*currentCB) (0x0004, ((arg1[12] | cmd) | 0x0000C001), arg1[12] | cmd, arg3[2], 0xA0000000, var17, var16, 0x0000);
	arg1[15] = arg3;
	return 0;
}
void sceKernelDmaOpSync (DmaOp* arg1, int arg2, int evParam){
	if (!(arg1[14] == 0x0000))return 0x800202CF;
	if (!((arg1[14] & FREE_MASK) != 0x0000))return 0x800202C3;
	if (!((arg1[14] & ASSIGNED_MASK) == 0x0000))return 0x800202C1;
	if (!((arg1[14] & PENDING_MASK) != 0x0000))return 0x800202C6;
	if (arg2 == 1)return (sceKernelWaitEventFlag (arg1[6], 0x0006, 0x0011, 0x0000, 0x0000)) ? 0x80020001 : 0;
	if (arg2 < 2){//error
		if (arg2)return 0x80020001;//impossible ?
		if (arg1[14] & FINISHED_MASK)return 0x80020001;
		if (!(arg1[14] & SUCCED_MASK))return 0x800202C7;
		if (!(arg1[14] & UNQUEUED_MASK))return 0x800202BE;
		if (arg1[14] & TRANSFER_MASK)return 0x800202C0;
		return 0x800202BF;
	}else{
		if (arg2 != 0x0002)return 0x80020001;
		res = sceKernelWaitEventFlag (arg1[6], 0x0006, 0x0010, 0x0000, &arg3);
		if (!res)return 0;
		if (res != 0x800201A8)
			return 0x80020001;
		OpSync (arg1);
		return 0x800202C2;
	}
	return 0;
}
void OpSync (int arg1){
	addr = (arg1[15] >> 3) ? 0xBCA00000 : 0xBC900000;
	op = ((arg1[15] & 7) << 5) + addr);
	op[4] &= 0xFFFFFFFE;
	while (op[4] & UNQUEUED_MASK) {}
	var12 = 1 << (arg1[15] & 7);
	arg1[14] = PENDING_MASK;
	*((int *) 0x4048) &= (!(1 << arg1[15]));
	arg1[15] = -1;
	((arg1[15] << 2) + 0x2000)[0] = 0;
	addr[2] = var12;
	addr[4] = var12;
}
void sceKernelDmaOpQuit (int arg1){
	intr = sceKernelCpuSuspendIntr ();
	if (!arg1)return 0x800202CF;
	if (!(arg1[14] & FREE_MASK))return 0x800202C3;
	if (arg1[14] & ASSIGNED_MASK)return 0x800202C1;
	if (!(arg1[14] & FINISHED_MASK))return 0x800202BF;
	if (!(arg1[14] & UNQUEUED_MASK))return 0x800202BE;
	if (!(arg1[14] & SUCCED_MASK))return 0x800202C7;
	if (!(arg1[14] & PENDING_MASK))return 0x800202C6;
	if (arg1[14] & 0x0002)return 0x80020001;
	OpSync (arg1);
	sceKernelCpuResumeIntrWithSync (intr);
	return 0;
}
void DmacManForKernel_E18A93A5 (int arg1, int arg2){
  var1 = arg2;
  var2 = arg1;
  if (arg1){
    var3 = (0xA0000000 & 0xE0000000) | (arg2 & 0x1FFFFFFF);
    var4 = ((int *) var3)[2];
    if (var4 == 0x00000000)
    {
      var7 = ((int *) var3)[3];
    }
    else
    {
      var5 = ((int *) var3)[2];
      while (1) {
        var3 = (0xA0000000 & 0xE0000000) | (var5 & 0x1FFFFFFF);
        var6 = ((int *) var3)[2];
        if (!(var6 != 0x00000000))
          break;
        var5 = ((int *) var3)[2];
        continue;
      }
      var7 = ((int *) var3)[3];
    }
    ((int *) var3)[3] = (var7 | 0x80000000);
    var10 = sceKernelCpuSuspendIntr ();
    var11 = ((unsigned short *) var2)[14];
    var12 = var11 & 0x0000FFFF;
    if ((var12 & 0x00001170) != 0x00000100)
    {
      sceKernelCpuResumeIntr (var10);
    }
    else
    {
      var13 = 0x00000000;
      if ((var12 & 0x00000002) == 0x00000000)
      {
        if ((var12 & 0x00000001) != 0x00000000)
        {
          var42 = ((int *) var2)[15];
          ((int *) var2)[15] = var3;
          ((int *) var42)[2] = var1;
        }
        else
        {
          var13 = 0x80020001;
        }
      }
      else
      {
        var14 = ((unsigned short *) var2)[15];
        var15 = ((unsigned short *) var2)[15];
        var16 = (var14 & 0x00000007) << 0x00000005;
        var17 = var16 + 0xBC900100;
        if (!((((char) var15) >> 0x00000003) == 0x00000000))
        {
          var17 = var16 + 0xBCA00100;
        }
        var18 = ((int *) var17)[4];
        var19 = var18 | 0x00040000;
        ((int *) var17)[4] = var19;
        var20 = ((int *) var17)[2];
        if (var20 == 0x00000000)
        {
          var36 = var19 & 0x01003800;
          if (((((var36 ^ 0x01000000) < 0x00000001)) | (((var36 ^ 0x01001000) < 0x00000001))) != 0x00000000)
          {

          label26:
            var13 = 0x800202BC;
          }
          else
          {
            if (var36 == 0x01003000)
            {
              goto label26;
            }
            else
            {
              while (1) {
                var37 = ((int *) var17)[4];
                if ((var37 & 0x00020000) != 0x00000000)
                  continue;
                break;
              }
              var38 = ((int *) var17)[3];
              if ((var38 & 0x00000FFF) == 0x00000000)
              {
                var13 = 0x800202C4;
              }
              else
              {
                var39 = ((int *) var17)[4];
                ((int *) var17)[4] = ((var39 & 0xFFFFFFFE) | (0x00000000 & 0x00000001));
                while (1) {
                  var40 = ((int *) var17)[4];
                  if ((var40 & 0x00000001) != 0x00000000)
                    continue;
                  break;
                }
                ((int *) var17)[2] = var1;
                var41 = ((int *) var17)[4];
                ((int *) var2)[15] = var3;
                ((int *) var17)[4] = (var41 | 0x00000001);
              }
            }
          }
        }
        else
        {
          var21 = ((int *) var2)[15];
          ((int *) var2)[15] = var3;
          ((int *) var21)[2] = var1;
        }
        var22 = ((int *) var17)[4];
        var23 = (var22 & 0xFFFBFFFF) | (0x00000000 & 0x00000001);
        ((int *) var17)[4] = var23;
      }
      var24 = *((int *) 0x00004058);
      var27 var28 = (*var24) (0x00000004, var19, var21, var23, var14, 0x00000000, var20, 0x00040000);
      sceKernelCpuResumeIntrWithSync (var10);
    }
  }
  return;
}
void sceKernelDmaOpAssignMultiple (int arg1, int arg2){
	if ((((arg2 -2) >= 16)))return 0x800202BD;
	var3 = ((int *) arg1)[0];
	i = 0;
	var5 = ((unsigned short *) var3)[26];
	while (i+1 < 0x0010) {
		i++;
		arg2 -= ((var5 >> i) & 1);
	}
	if (arg2 < 0)return 0x800202BD;
	var6 = arg2-1;
	var11 = 0;
	if (!var6){
	label16:
		var21 = sceKernelCpuSuspendIntr ();
		i = 0;
		if (!var6)
			var30 = arg1[0];
		else{
			var23 = arg1;
			while (i < var6) {
				i++;
				var23[0][3] = var23[1];
				var23[1][2] = var23[0];
				var23[0][0] = 0;
				var23[0][1] = 0;
				var23[1][26] = arg1[0][26];
				var23+=4;
			}
		}
		arg1[0][27] = arg2;
		sceKernelCpuResumeIntr (var21);
	}else{
		i=0;
		while (1) {
			i++;
			arg1+=4;
			if (!arg1[0])return 0x800202CF;
			if ((arg1[0][14] & FREE_MASK) != 0x0000)return 0x800202C3;
			if ((arg1[0][14] & ASSIGNED_MASK) == 0x0000)return 0x800202C1;
			if ((arg1[0][14] & UNQUEUED_MASK) != 0x0000)return 0x800202BE;
			if ((arg1[0][14] & 0x0002) != 0x0000)return 0x800202C0;
			if ((arg1[0][14] & 0x0070) != 0x0000)return 0x800202C4;
			if (i >= var6))
				goto label16;
		}
	}
}
void intrHandler (int, int arg2){
	i = 0;
	var5 = sceKernelCpuSuspendop ();
	addr = (arg2) ? 0xBCA00000 : 0xBC900000;
	value = (addr[3] | addr[1]) & 0xFF;
	while (value >= (1 << i)) {
		if (value & (1 << i)){
			op = ((((arg2 << 3) + i) << 2) + 0x2000)[0];
			if (!op){
				if (!(*((int *) 0x4040) & (1 << ((arg2 << 3) + i))))
					Kprintf ("Fatal error: Stray interrupt occurred\n");
				goto end_intrH;
			}
			var46 = i << 5 + addr;
			op[8] = ((int *) var46)[0];
			op[9] = ((int *) var46)[1];
			op[10] = ((int *) var46)[2];
			op[11] = ((int *) var46)[3];
			op[12] = ((int *) var46)[4];
			if (!(((int *) sp)[1] & (1 << i))){
				if (var46[2]){
					if (var46[4] & 1)
						OpSync (op);
				}
				op[14] = (op[14] | 0x0010);
				*((int *) 0x4048) &= !(1 << ((arg2 << 3) + i));
				((int *) ((((arg2 << 3) + i) << 2) + 0x2000))[0] = 0;
				op[14] &= 0xFFFFFFFD;
				op[15] = -1;
				if (op[6] > 0)sceKernelSetEventFlag (op[6], 4);
				((int *) ((arg2) ? 0xBCA00000 : 0xBC900000))[4] = (1 << i);
				var61 = -1;
			}else{
				if (!var46[2]){
					if (!(var46[4] & 1)){
						*((int *) 0x4048) &= !(1 << ((arg2 << 3) + i));
						((int *) ((((arg2 << 3) + i) << 2) + 0x2000))[0] = 0;
						op[14] = ((op[14] | 0x0040) & 0xFFFFFFFD);
						op[15] = -1;
						if (op[6]>0)sceKernelSetEventFlag (op[6], 2);
					}
				}
				var60 = (arg2) ? 0xBCA00000 : 0xBC900000;
				((int *) var60)[2] = (1 << i);
				var61 = 0;
			}
			if (!op[4]||((*var62) (op, var61, ((arg2 << 3) + i), op[5]) != 1))goto end_intrH;
			if (op[14]){
				op[8] = op[14][0];
				op[9] = op[14][1];
				op[10] = op[14][2];
				op[11] = op[14][3];
			}
			if (!currentDMAop)
				currentDMAop = op;
			op[0] = 0;
			op[1] = nextDMAop;
			if (nextDMAop)
				nextDMAop[0] = op;
			nextDMAop = op;
			op[14] |= 1;
		}
		end_intrH:
		i++;
	}
	if (!currentDMAop)
		buildDMAop ();
	var14 = *((int *) 0x4040) | *((int *) 0x4048);
	if (!(var14 & 0xFF))
		*((int *) 0xBC100050) &= 0xFFFFFFDF;
	if (!(var14 & 0xFF00))
		*((int *) 0xBC100050) &= 0xFFFFFFBF;
	sceKernelCpuResumeop (var5);
	return;
}
void buildDMAop (){
	var1 = *((int *) 0x4040);
	var2 = *((int *) 0x4048);
	var3 = currentDMAop;
	var4 = var1 | var2;
	var5 = var4 ^ 0xFFFF;
	if ((((0x0000 < var3)) & ((0x0000 < var5))) == 0x0000)
	{

	label53:
	}
	else
	{
		var6 = ((int *) var3)[3];
		while (1) {
			if (var6 == 0x0000)
			{

			label16:
				var26 = var3;
				while (1) {
					var27 = ((unsigned short *) var26)[15];
					var28 = (char) var27;
					if (var28 < 0)
					{
						var55 = ((unsigned short *) var26)[26];
						var28 = CLZ ((BITREV ((var55 & (!var4)))));
						if (((var28 < 0x0010)) == 0x0000)
							break;
						((int *) ((var28 << 0x0002) + 0x2000))[0] = var26;
						var4 = var4 | (0x0001 << var28);
						((short *) var26)[15] = var28;

					label21:
						var29 = *((int *) 0xBC100050);
						var30 = var28 >> 0x0003;
						var31 = 0x0020 << var30;
						if ((var29 & var31) != 0x0000)
						{
							var36 = var28 & 0x0007;
						}
						else
						{
							*((int *) 0xBC100050) = (var29 | var31);
							var32 = (var30) ? 0xBCA00000 : 0xBC900000;
							var33 = ((int *) var32)[12];
							var34 = var32;
							var35 = 0x0007;
							((int *) var32)[12] = (var33 | 0x0001);
							((int *) var32)[13] = 0x0000;
							while (1) {
								var35 = var35 + 0xFFFFFFFF;
								((int *) var34)[64] = 0x0000;
								((int *) var34)[65] = 0x0000;
								((int *) var34)[66] = 0x0000;
								((int *) var34)[67] = 0x0000;
								((int *) var34)[68] = 0x0000;
								var34 = var34 + 0x0020;
								if (var35 >= 0)
									continue;
								break;
							}
							((int *) var32)[2] = 0x00FF;
							((int *) var32)[4] = 0x00FF;
							var36 = var28 & 0x0007;
						}
						var37 = var36 << 0x0005;
						var38 = ((int *) var26)[8];
						var39 = (var30) ? (var37 + 0xBCA00100) : (var37 + 0xBC900100);
						((int *) var39)[0] = var38;
						var40 = ((int *) var26)[9];
						var41 = ((int *) var26)[2];
						((int *) var39)[1] = var40;
						var42 = ((int *) var26)[10];
						((int *) var39)[2] = var42;
						var43 = ((int *) var26)[11];
						((int *) var39)[3] = var43;
						var44 = ((unsigned short *) var26)[14];
						((short *) var26)[14] = (var44 | 0x0002);
						var45 = ((int *) var26)[12];
						((int *) var39)[4] = var45;
						if (var41 != 0x0000)
						{
							var26 = ((int *) var26)[3];
						}
						else
						{
							var46 = ((unsigned short *) var26)[14];
							var47 = nextDMAop;
							((short *) var26)[14] = ((var46 & 0xFFFFFFFE) | (0x0000 & UNQUEUED_MASK));
							if (var47 == var26)
							{
								var54 = ((int *) var26)[1];
								nextDMAop = var54;
							}
							var48 = currentDMAop;
							if (var48 == var26)
							{
								var53 = ((int *) var26)[0];
								currentDMAop = var53;
							}
							var49 = ((int *) var26)[1];
							if (var49 == 0x0000)
							{
								var51 = ((int *) var26)[0];
							}
							else
							{
								var50 = ((int *) var26)[0];
								((int *) var26)[1] = 0x0000;
								((int *) var49)[0] = var50;
								var51 = ((int *) var26)[0];
							}
							if (var51 == 0x0000)
							{
								var26 = ((int *) var26)[3];
							}
							else
							{
								var52 = ((int *) var26)[1];
								((int *) var26)[0] = 0x0000;
								((int *) var51)[1] = var52;
								var26 = ((int *) var26)[3];
							}
						}
						if (var26 != 0x0000)
							continue;
						break;
					}
					else
					goto label21;
				}
				var3 = ((int *) var3)[0];
				var5 = var4 ^ 0xFFFF;

			label51:
				if (!((((0x0000 < var3)) & ((0x0000 < var5))) != 0x0000))
					break;
				var6 = ((int *) var3)[3];
				continue;
			}
			else
			{
				var7 = ((int *) var3)[2];
				if (var7 != 0x0000)
				{
					goto label16;
				}
				else
				{
					var8 = ((unsigned short *) var3)[26];
					var9 = ((unsigned short *) var3)[27];
					var10 = var8 & (!var4);
					var11 = 0x0000;
					while (1) {
						var11 = var11 + 0x0001;
						var9 = var9 - ((var10 >> var11) & UNQUEUED_MASK);
						if (((var11 < 0x0010)) != 0x0000)
							continue;
						break;
					}
					var12 = var3;
					if (var9 >= 0)
					{
						var23 = 0x1FFC;
						var24 = 0x0000;
						while (1) {
							var25 = 0x0001 << var24;
							var23 = var23 + 0x0004;
							if ((var10 & var25) != 0x0000)
							{
								((int *) var23)[0] = var12;
								var4 = var4 | var25;
								((short *) var12)[15] = var24;
								var12 = ((int *) var12)[3];
							}
							var24 = var24 + 0x0001;
							if (var12 != 0x0000)
								continue;
							break;
						}
						goto label16;
					}
					else
					{
						var13 = ((int *) var3)[0];
						if (var13 == 0x0000)
						{
						}
						else
						{
							var14 = ((int *) var3)[1];
							var15 = ((int *) var13)[0];
							((int *) var13)[1] = var14;
							((int *) var3)[1] = var13;
							var16 = ((int *) var13)[1];
							((int *) var3)[0] = var15;
							if (var16 == 0x0000)
							{
								currentDMAop = var13;
							}
							else
							{
								((int *) var16)[0] = var13;
							}
							var17 = ((int *) var13)[0];
							if (var17 == 0x0000)
							{
								nextDMAop = var3;
							}
							else
							{
								var18 = ((int *) var3)[0];
								((int *) var18)[1] = var3;
							}
							((int *) var13)[0] = var3;
							var3 = var13;
							goto label51;
						}
					}
				}
			}
			goto label54;
		}
		goto label53;
	}

label54:
	var19 = *((int *) 0x4040);
	*((int *) 0x4048) = (var4 & (!var19));
}
void sceKernelDmaChExclude (int ch, int arg2){
	if (ch >= 0x0010)return;
	if (*((int *) 0x4044) & (1 << ch))return;
	var6 = sceKernelCpuSuspendIntr ();
	if (arg2){
		*((int *) 0x4040) |= (1 << ch));
		sub_01C20 (ch >> 3);
	}else{
		*((int *) 0x4040) &= (!(1 << ch));
	}
	sceKernelCpuResumeIntr (var6);
	return;
}
void sceKernelDmaChReserve (int arg1, int arg2){
	var3 = sceKernelCpuSuspendIntr ();
	if (*((int *) 0x4040) & (1 << arg1))
		sceKernelCpuResumeIntr (var3);
	else{
		if (arg2 < 0)
			var7 = *((int *) 0x4044) & (!(1 << arg1));
		else
			var7 = *((int *) 0x4044) | (1 << arg1);
		*((int *) 0x4044) = var7;
		sceKernelCpuResumeIntr (var3);
	}
}
void sceKernelDmaOpAlloc (){
	var4 = *((int *) currentCtx);
	if (!var4)return;
	var5 =sceKernelCpuSuspendIntr ();
	var6 = currentCtx[14];
	if (!(var6 & FREE_MASK))
		goto label7;
	currentCtx = ((int *) var4)[0];
	var4[2] = 0;
	var4[3] = 0;
	var4[4] = 0;
	var4[6] = sceKernelCreateEventFlag ("SceDmacmanEvflag");
	var4[14] = 0;
	var4[15] = -1;
	var4[26] = -1;
label7:
	sceKernelCpuResumeIntr (var5);
	return;
}
void sceKernelDmaOpAssign (int arg1, char lo, char hi, int arg4){
	if(!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	if (arg1[14] & UNQUEUED_MASK)return 0x800202BE;
	if (arg1[14] & TRANSFER_MASK)return 0x800202C0;
	arg1[12] = arg4;
	arg1[26] = (((hi & 0x00FF) << 8) | (lo & 0x00FF));
	arg1[14] = ASSIGNED_MASK;
	return 0;
}
void DmacManForKernel_1FC036B7 (int arg1, int arg2){
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = s1;
	var1 = arg1;
	((int *) sp)[0] = s0;
	((int *) sp)[2] = ra;
	var2 = ((int *) arg1)[15];
	var3 = *((int *) currentCB);
	((int *) var2)[2] = arg2;
	var6 var7 = (*var3) (0x0004, arg2, 0x0000, arg4, arg5, arg6, arg7, arg8);
	var8 = (0xA0000000 & 0xE0000000) | (arg2 & 0x1FFFFFFF);
	var9 = ((int *) var8)[2];
	if (var9 == 0x0000)
	{
		((int *) var1)[15] = var8;
	}
	else
	{
		var10 = ((int *) var8)[2];
		while (1) {
			var11 = (0xA0000000 & 0xE0000000) | (var10 & 0x1FFFFFFF);
			var12 = ((int *) var11)[2];
			if (!(var12 != 0x0000))
				break;
			var10 = ((int *) var11)[2];
			continue;
		}
		((int *) var1)[15] = var11;
	}
	ra = ((int *) sp)[2];
	var13 = ((int *) sp)[1];
	var14 = ((int *) sp)[0];
	sp = sp + 0x0010;
	return;
}
void sceKernelDmaOnDebugMode (){
	return;
}
void sceKernelDmaOpFreeLink (int arg1){
	if(!arg1)return 0x800202CF;
	if (arg1[14] & FREE_MASK)return 0x800202C3;
	return (arg1[14] & ASSIGNED_MASK) ? 0 : 0x800202C1;
}
void suspendHandler (){
	(int *) i = 0x2000;
	n = 15;
	while (n >= 0) {
		n--;
		i+=4;
		if (i)OpSync (*i);
	}
	*((int *) 0x4048) = 0x0000;
	sceKernelDmaOpAllCancel ();
	for (n=0;n < 2;n++)
		sceKernelDisableIntr (0x16);
}
void resumeHandler (){
	if ((*((int *) 0x4040) & 0xFF00))
		sub_01C20 (1);
	if ((*((int *) 0x4040) & 0x00FF))
		sub_01C20 (0);
	i=0
	while (i < 2) {
		i++;
		sceKernelEnableIntr (0x0016);
	}
}
void callback (){
	__asm__ ("sync;");
	return ((((ra >> 0x1F) + 2) << 0x1D) | ra)[0];
}
void sub_01C20 (int arg1){
	value = *((int *) 0xBC100050);
	if (!(value & (0x20 << arg1))){
		*((int *) 0xBC100050) = (value | (0x20 << arg1));
		addr = (arg1) ? 0xBCA00000 : 0xBC900000;
		addr[12] |= 1;
		addr[13] = 0;
		i = 8;
		while (i >= 0) {
			i--;
			addr[64] = 0;
			addr[65] = 0;
			addr[66] = 0;
			addr[67] = 0;
			addr[68] = 0;
			addr += 0x20;
		}
		addr[2] = 0x00FF;
		addr[4] = 0x00FF;
	}
	return;
}

