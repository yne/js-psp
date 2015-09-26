int sceKernelLoadModule (const char *path, int flags, SceKernelLMOption *option){
	//K1>>16
	if(sceKernelIsIntrContext())return 0x80020064;
	if (!(k1 & 0x00000018))return 0x80020149
	if (!path)return 0x800200D3
	if (((-k1 & 0x18) & path)<0)return 0x800200D3;
	if (strchr (path, 0x00000025))return 0x8002012F;

	if (option){
		if (((0x0207FFFF < ((SysMemForKernel_2CFF6F90 (0) & 0xFFFF0000) | (0 & 0x0000FFFF)))) == 0){
			if (((((option + 0x14) | option) & (- k1 & 0x18)) < 0))
				return 0x800200D3
		}else{
			if (((int *) option)[0] == 0x14)
				if (((((option + 0x14) | option) & (- k1 & 0x18)) < 0))
					return 0x800201BC
		}
	}
	if((fd = sceIoOpen (path, 0x04000001, 0x1FF))<0)return fd;
	if(sceIoIoctl (fd, 0x00208001, 0, 0, 0, 0)<0)return 0x80020146;
	struct mod={
		char char0,char1,char2,char3;
		int int1,*int2,*int4,int5,int6,int13,int15,int16,int19,int20,int22=event,int24;int25,int31;
	}//size = A0
	
	mod.char0 = 0;
	mod.char1 = 1;
	mod.int1 = 16;
	mod.int16 = fd;
	mod.int13 = 0;
	mod.int25 = (sceIoIoctl (fd, 0x00208081, 0, 0, 0, 0) < 0) ? (mod.unk100 : 0x10;
	mod.int31 = 0;
	
	int ret = sub_06FE0 (mod, option);
	sceIoClose (fd);
	return ret;
}

int sub_06FE0 (struct mod, SceKernelLMOption *option){
	if (!option){
		mod.char2 = 0;
		mod.char3 = 1;
		mod.int5 = 0;
		mod.int6 = 0;
	}else{
		mod.char2 = ((unsigned char *) option)[16];//position
		mod.char3 = ((unsigned char *) option)[17];//access
		mod.int5 = ((int *) option)[1];//mpid text
		mod.int6 = ((int *) option)[2];//mpid data
	}
	mod.int15 = 0;
	mod.int19 = 0;
	mod.int20 = 0;
	mod.int24 = 0;
	return sub_06F10 (mod);
}

int sub_06F10 (struct mod){
	if((id = sceKernelGetThreadId ())<0)return id;
	if (id == *((int *) 0x0000901C)){
		Kprintf ("module manager busy.\n", 1);
		return 0x80020143;
	}
	mod.int2 = sp;
	mod.int22 = *((int *) 0x00009018);
	
	if(mutex = sceKernelLockMutex (*((int *) 0x00009014), 1, 0) < 0)return mutex;
	if(ret = sceKernelStartThread (*((int *) 0x00009010), sizeof(mod), mod) < 0)return tmp;
	sceKernelWaitEventFlag (*((int *) 0x00009018), 1, 0x00000011, 0, 0);
	sceKernelUnlockMutex (*((int *) 0x00009014), 1);
	return 0;
}

void module_reboot_phase (){
  return;
}
void module_reboot_before (){
  return sceKernelSuspendThread (*((int *) 0x00009010));
}

void module_bootstart (){
  *((int *) 0x00009010) = sceKernelCreateThread ("SceKernelModmgrWorker", 0x00000170, 0x00000020, 0x00001000, 0, 0);
  *((int *) 0x00009014) = sceKernelCreateMutex (0x00008838, 0, 0, 0);
  *((int *) 0x00009018) = sceKernelCreateEventFlag (0x00008838, 0, 0, 0);
  *((int *) 0x00009020) = 0xFFFFFFFF;
  *((int *) 0x00009030) = 0;
  *((int *) 0x00009024) = 0x00009024;
  *((int *) 0x0000901C) = 0xFFFFFFFF;
  *((int *) 0x00009028) = 0x00009024;
  return;
}
int sub_000B0 (int arg1)
{
  sp = sp + 0xFFFFFFF0;
  var2 = arg1;
  var3 = ((unsigned short *) arg1)[18];
  var4 = var3 & 0x0000000F;
  if (var4 < 2)return 0x80020138;
	if (var4 >= 4){
		if (var4 == 0x00000007)
		{
			var6 = ((int *) var2)[27];
			goto label7;
		}
	}
	{
		var27 = ((int *) var2)[27];

	label7:
		var7 = ((int *) var2)[28];
		SysMemForKernel_8D34BBDA (var6, 0x0000004D, var7);
		var10 = ((int *) var2)[27];
		var11 = ((int *) var2)[28];
		var12 = ((int *) var2)[29];
		var13 = ((int *) var2)[30];
		SysMemForKernel_10652B45 ((var10 + var11), 0xFFFFFFFF, (var12 + var13));
		sceKernelIcacheInvalidateAll ();
		LoadCoreForKernel_10FD7D37 (var2);
		var20 = ((unsigned short *) var2)[18];
		if ((var20 & 0x00001000) == 0x00000000)
		{
			var23 = ((int *) var2)[13];
			var26 = SysMemForKernel_AFBE8876 (var23);
		}
		LoadCoreForKernel_AE96A41B (var2);
		return 0;
	}
  return var1;
}
int sub_06A14 (int arg1, unsigned short * arg2, int arg3, int arg4, int*arg5){
	if (((arg2[18] & 0x0000000F) != 0x00000003))return 0x80020001;
	arg2[18] = (((arg2[18] & 0xFFFFFFF0) | (0x00000000 & 0x0000000F)) | 0x00000004);
	if ((ret = sub_07A48 (arg1, arg2)) < 0){
		((short *) arg2)[18] = (((arg2[18] & 0xFFFFFFF0) | (0x00000000 & 0x0000000F)) | 0x00000003);
		return ret;
	}
	var9 = 0x00000000;
	if (arg2[12] != -1){
		*((int *) 0x0000901C) = arg2[12];
		if (!sceKernelStartThread (((int *) arg2)[12], arg3, arg4))
			var9 = sceKernelWaitThreadEnd (((int *) arg2)[12], 0x00000000);
		*((int *) 0x0000901C) = 0xFFFFFFFF;
		sceKernelDeleteThread (((int *) arg2)[12]);
		((int *) arg2)[12] = 0xFFFFFFFF;
	}
	if (arg5)
		*arg5 = var9;
	if (var9){
		var26 = sub_00000 (arg2);
		arg2[18] = (((arg2[18] & 0xFFFFFFF0) | (0x00000000 & 0x0000000F)) | 0x00000007);
		var30 = sub_000B0 (arg2);
		return var9;
	}
	arg2[18] = (((arg2[18] & 0xFFFFFFF0) | (0x00000000 & 0x0000000F)) | 0x00000005);
	return var9;
}
// sub_0566C sub_06220 <sub_06A14> sub_06B5C <sub_000B0>

void sub_00170 (int arg1, int mod){
	var3 = 0;
	tmp = mod.int4;
	SysMemForKernel_10652B45 (sp, 0, 0x000000C0);
	switch (((int *) (((mod.char0 << 2) + 0x00008AA4))[0]){
	case 0:
		if (!mod.int4){
			if (mod.int4 = LoadCoreForKernel_A48D2D08 ())
				break;
		}
		mod.int15 = sp;
		tmp = sub_0566C (mod);
		sceKernelChangeThreadPriority (0, 0x20);
		if (tmp < 0){
			mod.int2[0] = tmp;
			if (tmp)
				LoadCoreForKernel_AE96A41B (tmp);
			break;
		}
		mod.int2[0] = tmp[11];
		if (mod.char1 == 0)
			break;
	case 1:
		if (!tmp){
			if (!(tmp = LoadCoreForKernel_A48D2D08 ()))
				break;
			else mod.int4=tmp;
			((short *) tmp)[18] = (((((unsigned short *) tmp)[18] & 0xFFFFFFF0) | (0 & 0x0000000F)) | 0x00000002);
			LoadCoreForKernel_B3391485 (tmp);
		}
		if (!mod.int15){
			SysMemForKernel_10652B45 (mod.int15, 0, 0x000000C0);
		}
		if ((var3 = sub_06220 (mod)) < 0){
			mod.int2[0] = var3;
			if (!tmp)break;
			LoadCoreForKernel_10FD7D37 (tmp);
			LoadCoreForKernel_AE96A41B (tmp);
			break;
		}
		mod.int2[0] = ((int *) tmp)[11];
		if (mod.char1 == 1)
			break;
	case 2:
		tmp = addr;
		if (!addr = LoadCoreForKernel_587F4973 (mod.int11)){
			if (!(tmp = LoadCoreForKernel_00E94E85 (mod.int11))){
				mod.int2[0] = 0x8002012E;break;}
		}
		ret = sub_06A14 (mod, tmp, mod.int17, mod.int18, mod.int21);
		if (ret == 0)
			mod.int2[0] = tmp[11];
		else{
			if (ret == 1)
				mod.int2[0] = 0;
			else
				mod.int2[0] = ret;
		}
		if (ret < 0)break;
		if (mod.char1 == 2)break;
	case 3:
		if (addr)break;
		if (!(addr = LoadCoreForKernel_587F4973 (mod.int11))){
			mod.int2[0] = 0x8002012E;break;}
		ret = sub_06B5C (mod, addr, mod.char0,  mod.int12, mod.int17, mod.int18, mod.int21);
		if (ret < 0)break;
		if (ret == 0)
			mod.int2[0] = 0;
		if (ret == 1)
			mod.int2[0] = addr[11];
		else
			mod.int2[0] = ret;
		if (mod.char1 == 3)
			break;
	case 4:
		void*addr = LoadCoreForKernel_587F4973 (mod.int11);
		if (!addr){
			mod.int2[0] = 0x8002012E;break;}
		if ((ret = sub_000B0 (addr)) < 0){
			mod.int2[0] = ret;break}
		else{
			mod.int2[0] = addr[11];break;}
		}
	default:break;
	}
	if (mod.int22){
		sceKernelChangeThreadPriority (0, 1);
		sceKernelSetEventFlag (mod.int22, 1);
	}
}