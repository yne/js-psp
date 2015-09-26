
void module_start ()
{
  return;
}

void module_stop ()
{
  return;
}

int sceNpInstall_user_5847D8C7 (int arg1, int arg2, int arg3, int arg4){
	new_k1 = k1 << 12;
	old_k1 = k1;
	k1 = new_k1;
	ret = 0x80000023;
	if ( ((((arg2 + 0x20) | arg2) & new_k1) >= 0)
	  && ((((arg3 + 0x80) | arg3) & new_k1) >= 0)
	  && ((((arg4 + 0x40) | arg4) & new_k1) >= 0)
	){
		ret = _sceNpInstall_user_5847D8C7 (arg1, arg2, arg3, arg4);
	}
	k1 = old_k1;
	return ret;
}

int sceNpInstall_user_0B039B36 (int arg1, int arg2, int arg3){
	new_k1 = k1 << 12;
	old_k1 = k1;
	k1 = new_k1;
	ret = 0x80000023;
	if ( ((new_k1 & (((arg1 + arg2) | arg1) | arg2)) >= 0)
	  && ((((arg3 + 0x40) | arg3) & new_k1) >= 0)
	){
		ret = _sceNpInstall_user_0B039B36 (arg1, arg2, arg3);
	}
	k1 = old_k1;
	return ret;
}

void sceNpInstall_user_91F9D50D (int arg1){
	new_k1 = k1 << 12;
	old_k1 = k1;
	k1 = new_k1;
	//ret = ????;

	if (!((((arg1 + 0x08) | arg1) & new_k1) < 0))
		ret = _sceNpInstall_user_91F9D50D (arg1);
	k1 = old_k1;
	return ret;
}

//Desactivate
int sceNpInstall_user_7AE4C8BC (){
	old_k1 = k1;
	k1 = k1 << 12;
	ret = _sceNpInstall_user_7AE4C8BC ();
	k1 = old_k1;
	return ret;
}

//arg1: type
//2 = standard
//0 = type 1 + check( arg/rtc must be greater than @xxx )
//1 = access act.dat (no read/write)
u64 compare;//
int _sceNpInstall_user_5847D8C7 (int arg1, int arg2, int arg3, int arg4){
	fd = -1;
	if (((arg2 < 1) | (arg4 < 1)) || !arg3)
		return 0x80550980;

	int rtc_buf [0x10];//sp+40
	
	ret = sceRtc_driver_CEEF238F (&rtc_buf);
	if (ret < 0)return ret;
	
	if(arg1 > 2)
		return 0x80550980;
	
	if (arg1 == 1){
		fd = sceIoOpen ("flash2:/act.dat", 0x04000001, 0);
		if (fd < 0)return 0x80550983;
		sceIoClose (fd);
		return 0;
	}
	if (arg1 == 0){
		if ((rtc_buf.unk < compare)
			return 0x80550984;
	}
		
	int auth[7];

	memset (auth, 0, 0x30);
	u64 a = 0x10 + 0;//sp[16]
	memcpy (sp + 0x20, arg2, 0x20);
	u64 result = __udivdi3 ((sp[16] - 0xFF2BC000), ((sp[17] - 0xDCBFFE) - ((sp[16] < 0xFF2BC000))), 0x03E8, 0);
	ret = sceOpenPSIDGetPSID (result, 1);
	if(ret<0)return ret;
	int buf[12];
	ret = scePcactAuth1BB (arg1, buf, auth, sp + 0x48, arg3, arg4);
	int buffB [0x10];
	ret = sceRtc_driver_89FA4262 (0x09D0, buffB, 0x1E, 0);
	if (fd >= 0)
		sceIoClose (fd);

  return ret;
}

char buf_00374[0x10]//@0x09C0

// 0x00001038 : OK
// 0x80550980 : bad arg
// 0x80550981 : not enought data
int _sceNpInstall_user_0B039B36 (void* arg1, int arg2, int arg3){
	if (((arg1 < 1) | ((arg2 != 0x1090) > 0)) || !arg3)
		return 0x80550980;
	
	int ret,fd;
	if ( ((ret = scePcactAuth2BB (arg1, arg3, buf_00374)) < 0)
		|| ((ret = scePspNpDrm_driver_EBB198ED (arg1 + 0x50, buf_00374)) < 0)
		|| ((ret = sceNpDrmVerifyAct (arg1 + 0x50)) < 0) 
	){
		sceIoRemove ("flash2:/act.dat");
	}else{
		int fd = sceIoOpen ("flash2:/act.dat", 0x04000602, 0x01B6);
		if (fd >= 0){
			ret = sceIoWrite (fd, arg1 + 0x50, 0x1038);
			if (ret != 0x1038)
				ret = ret < 0 ? ret : 0x80550981;
			sceIoClose (fd);
		}
		if (ret < 0)
			sceIoRemove ("flash2:/act.dat");//TODO:use the same as above
	}
	memset (arg1 + 0x50, 0, 0x1040);
	memset (arg3, 0, 0x40);
	memset (buf_00374, 0, 0x10);
  return ret;
}

// 0x00000010 : OK
// 0x80550982 : null pointer
// 0x80550981 : not enought data
void _sceNpInstall_user_91F9D50D (int arg1){
	int ret = 0x80550982;
	if (!arg1)
		return ret;
	
	int fd = sceIoOpen ("flash2:/act.dat", 0x04000001, 0);
	if (fd >= 0){
		int file[4];
		ret = sceIoRead (fd, file, 0x10);
		if (ret != 0x10){
			if (ret >= 0)
				ret = 0x80550981;
		}else{
			arg1[0] = file[2];
			arg1[1] = file[3];
		}
		sceIoClose (fd);
	}
	return ret;
}

int Remove_res;//@ 0x09D8
//@00580
void remove_th (){
  Remove_res = sceIoRemove ("flash2:/act.dat");
}

void _sceNpInstall_user_7AE4C8BC (){
	int timeout = 0x4C4B40;
	int th_id = sceKernelCreateThread ("SceNpDeactivation", remove_th, 0x20, 0x4000, 0, 0);
	if (th_id >=0 ){
		Remove_res = 0;
		if ( (sceKernelStartThread (th_id, 0, 0) < 0)
		  || (sceKernelWaitThreadEnd (th_id, &timeout) < 0)
		){
			sceKernelTerminateThread (th_id);
			sceKernelDeleteThread (th_id);
		}else{
			int tmp = Remove_res;//whaaat ?
		}
	}
	return Remove_res;//I guess ...
}

