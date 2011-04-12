#include <pspsdk.h>
#include "utility.h"

void sceUtilityInit (){
	EventFlag2 = sceKernelCreateEventFlag ("SceUtilityWorktime", 0x200, 0, 0);
	if (var3 < 0)return 0x80000042;
	BusyEvent = sceKernelCreateEventFlag ("SceUtilitySuspend", 0x200, 3, 0);
	if (BusyEvent < 0)return 0x80000042;
	StructID = 0;
	CurrentType = 0;
	UnkFlag = 0;
	Status = 0;
	IsBusy = 0;
	CurStruct = 0;
	sceKernelRegisterSysEventHandler (0x9960);
	sub_02154 ();
	sub_02808 ();
	sub_02B88 ();
	sub_031C0 ();
	sub_0329C ();
	sub_03530 ();
	sub_03620 ();
	sub_0293C ();
	sub_036D4 ();
	var4 = 0;
}
void initStart (int type, struct* arg2){//type(<17&!0&!2)
/*
16:store
15:RSSrdr
14:RSSscrb
13:PS3
12:NPsign
11:ScreenShot
10:1FD567D4
9:Install
8:Auth
7:DNAS
6:Osk
5:dlg
4:Netconf
3:GameShar
1:Save
*/
	var1 = type;
	structInput = arg2;
	var3 = 0;
	structID = 0;
	if (Status)	return 0x80110001
	if (((arg2 + 0x30 | structInput) & (- k1&0x18)) < 0)return 0x80110002;
	if (type >= 0x11)return 0x80110003;
	switch (type) {
	case 1:
		if (((int *) structInput)[0] == 0x600){
			structID = 0xC8;
			if ((((structInput + 0x600 | structInput) & (-k1&0x18)) < 0))return 0x80110002;
			var15 = ((int *) structInput)[12];
			var3 = 1;
			if ((((var15 < 2)) | (((var15 ^ 8) < 1))) != 0){
			label85:
			}else{
				if (var15 != 9){
					if(var15 == 11){
					label84:
						var3 = 1;
					}else{
						if (var15 > 11 && var15 < 0x16)
							goto label84;
						var3 = 0;
						if ((var15 == 0x16))
							goto label84;
					}
					goto label85;
				}
			}
		}else if(var12 == 0x5DC){//sizeof struct != 0x600
			structID = 0x96;
			var13 = k1 & 0x18;
			var14 = structInput + 0x5DC;
			return 0x80110002;
		}else if(var12 == 0x5C8){
			structID = 0x67;
			var13 = k1 & 0x18;
			var14 = structInput + 0x5C8;
		}
		return 0x80110004;
	case 3:
		if(((int *) structInput)[0] == 0x64){
			structID = 0xFA;
			if ((((structInput + 0x64) | structInput) & (-k1&0x18)) < 0)return 0x80110002;
			var38 = ((int *) structInput)[23];
			var39 = ((int *) structInput)[24];
			var40 = k1 & 0x18;
			ret = 0x80110002;
			if (((0 - var40) & (((var38 + var39) | var38) | var39)) >= 0)
				goto label85;
			ra = ((int *) sp)[2];
		}else{
			if (((int *) structInput)[0] == 0x54)
			{
				structID = 0x96;
				var33 = k1 & 0x18;
				endOfStruct = structInput + 0x54;

			label61:
				ret = 0x80110002;
				if (!(((endOfStruct | structInput) & (0 - var33)) < 0))
				{
					var35 = ((int *) structInput)[18];
					var36 = k1 & 0x18;
					ret = 0x80110002;
					if (!((((var35 + 4) | var35) & (0 - var36)) < 0))
						goto label85;
				}
			}
			else
			{
				ret = 0x80110004;
				if (!(((int *) structInput)[0] != 0x50))
				{
					structID = 0x67;
					var33 = k1 & 0x18;
					endOfStruct = structInput + 0x50;
					goto label61;
				}
			}
			goto lBadStructSize;
		}
	case 4:
		structSize = ((int *) structInput)[0];
		if (structSize == 0x44){
			structID = 0x12C;
		label46:
			endOfStruct = structInput + 0x44;
		label51:
			if (((endOfStruct | structInput) & (- k1 & 0x18)) < 0)return 0x80110002;
			goto label85;
		}
		else
		{
			structID = 0xC8;
			if (structSize == 0x40){
			label48:
				endOfStruct = structInput + 0x40;
				goto label51;
			}else{
				ret = 0x80110004;
				structID = 0x96;
				if (structSize != 0x38)
					goto lBadStructSize;
			label50:
				endOfStruct = structInput + 0x38;
				goto label51;
			}
		}
	case 5:
		var44 = ((int *) structInput)[0];
		structID = 0x172;
		if (var44 == 0x2C4)
		{
			endOfStruct = structInput + 0x2C4;
			goto label51;
		}
		else
		{
			if (var44 == 0x244){
				structID = 0x96;
				endOfStruct = structInput + 0x244;
				goto label51;
			}
			else
			{
				ret = 0x80110004;
				if (var44 != 0x23C)
					goto lBadStructSize;
				structID = 0x67;
				endOfStruct = structInput + 0x23C;
				goto label51;
			}
		}
	case 6:
		if (((int *) structInput)[0] == 0x40){
			structID = 0x67;
			goto label48;
		}else if (((int *) structInput)[0] == 0x44){
			structID = 0x3E9;
			goto label46;
		}
		return 0x80110004;
	case 7:
		if (((int *) structInput)[0] != 0x38)return 0x80110004
		structID = 0xC8;
		goto label50;
	case 8:
		structSize = ((int *) structInput)[0];
		ret = 0x80110004;
		if (structSize != 0x34)
			goto lBadStructSize;
		structID = 0xC8;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0x34;
		goto label51;
	case 9://install
		if (((int *) structInput)[0] != 0x64)
			goto LoadThread;
		structID = 0xC8;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0x64;
		goto label51;
	case 10://unk
		structSize = ((int *) structInput)[0];
		ret = 0x80110004;
		if (structSize != 0x30)
			goto lBadStructSize;
		structID = 0x118;//total size ?
		ret = 0x80110002;
		if (((arg2 + 0x30 | structInput) & (-k1 & 0x18)) >= 0)//var8=pspUtility????
			goto label85;
		ra = ((int *) sp)[2];
		return;
	case 11://sceenshot
		structSize = ((int *) structInput)[0];
		structID = 0x17C;
		if (structSize == 0x3A0){
		label20:
			if ((((structInput + 0x3A0) | structInput) & (-k1&0x18)) < 0)return 0x80110002;
			else{
				screenMode = ((int *) structInput)[16];
				screenWidth = ((int *) structInput)[17];
				screenHeight = ((int *) structInput)[22];
				resolution = (screenWidth * screenHeight);
				if ((-(k1&0x18) & (((screenMode + resolution) | screenMode) | resolution)) >= 0)
					goto LoadThread;
				return 0x80110002;
			}
		}else if (structSize == 0x1B4){
			structID = 0x172;
			goto label20;
		}else return 0x80110004;
		goto lBadStructSize;
	case 12:
		structSize = ((int *) structInput)[0];
		ret = 0x80110004;
		if (structSize != 0x40)
			goto lBadStructSize;
		structID = 0x172;
		ret = 0x80110002;
		if ((structInput & 7) == 0)
			goto label48;
		ra = ((int *) sp)[2];
		return;
	case 13:
		structSize = ((int *) structInput)[0];
		ret = 0x80110004;
		if (structSize != 0xE0)
			goto lBadStructSize;
		structID = 0x17C;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0xE0;
		goto label51;
	case 14:
		ret0 = ((int *) structInput)[0];
		ret = 0x80110004;
		if (ret0 != 0x54)
			goto lBadStructSize;
		structID = 0x17C;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0x54;
		goto label51;
	case 15:
		ret1 = ((int *) structInput)[0];
		ret = 0x80110004;
		if (ret1 != 0x70)
			goto lBadStructSize;
		structID = 0x187;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0x70;
		goto label51;
	case 16:
		ret2 = ((int *) structInput)[0];
		ret = 0x80110004;
		if (ret2 != 0x4C)
			goto lBadStructSize;
		structID = 0x1F4;
		var42 = k1 & 0x18;
		endOfStruct = structInput + 0x4C;
		goto label51;
	}
LoadThread:
	StructID = structID;
	Status = 1;
	UnkFlag = var3;
	CurStruct = structInput;
	CurrentType = type;
	sub_07424 (type, var3);//9
	Devctl = sceIoDevctl ("mscmhc0:", 0x202580A, 0, 0, 0xA124, 0x10);
	sceKernelStartThread(sceKernelCreateThread ("SceUtilityInit", 0x1330,((int *) CurStruct)[4], 0x800, 0, 0), 0, 0)
	return;
}
void shutdownStart (int arg1){//type
	if (CurrentType != arg1)return 0x80110005;
	if (Status != 3)return 0x80110001;
	var4 = CurStruct;
	Status = 4;
	structID = ((int *) var4)[4];
	th = sceKernelCreateThread ("SceUtilityShutdown", 0x1838, structID, 0x800, 0, 0);
	if (th <= 0){th = 0;return;}
	ret = sceKernelStartThread (var8, 0, 0);
	if (ret != 0){
		sceKernelDeleteThread (th);
		th = 0;
	}
}
void contStart (int arg1, int arg2){//CONT start
	var1 = arg1;
	var3 = arg2;
	var4 = 0;
	if (Status != 5)return 0x80110001;
	if ((((arg2 + 0x30) | arg2) & (-k1&0x18)) < 0)return 0x80110002;
	if (CurrentType != var1)return 0x80110005;
	if (var1 == 11){
		if (((int *) var3)[0] != 0x3A0)return 0x80110004;
		if ((((var3 + 0x3A0) | var3) & (-k1 & 0x18)) < 0)return 0x80110002;
		var4 = 0x17C;
		var19 = ((int *) var3)[17];
		structInput0 = ((int *) var3)[22];
		structInput1 = ((int *) var3)[16];
		graphicThreadPrio = (var19 * structInput0);
		structInput3 = k1 & 0x18;
		if (((0 - structInput3) & (((structInput1 + graphicThreadPrio) | structInput1) | graphicThreadPrio)) >= 0){
		label18:
			CurrentType = var1;
			CurStruct = var3;
			StructID = var4;
			Status = 2;
			UnkFlag = 0;
			sceKernelSetEventFlag (EventFlag2, 0x10);
			sceKernelWaitEventFlag (EventFlag2, 0x20, 0x20, 0, 0);
			return 0;
		}else goto label11;
		goto label23;
	}else if (var1 == 15){
		if (((int *) var3)[0] != 0x70)return 0x80110004;
		var4 = 0x187;
		if ((((var3 + 0x70) | var3) & (k1 & 0x18))<0)return 0x80110002;
	}
	goto label18;
	return;
}
void sceUtility_private_9E8CD6BC (int arg1){
	if (((((arg1 + 0x10) | arg1) & ( - k1 & 0x18)) < 0))return 0x80110002;
	if (!Devctl){
		((int *) arg1)[0] = *((int *) 0xA124);
		((int *) arg1)[1] = *((int *) 0xA128);
		((int *) arg1)[2] = *((int *) 0xA12C);
		((int *) arg1)[3] = *((int *) 0xA130);
	}
	return 0;
}
void sceUtility_private_107CA63E (char* arg1, int arg2, int arg3){//load prx from str
	if (((-k1 & 0x18) & arg1) < 0)return;
	structID = k1 & 0x18;
	if (!((((arg3 + 0x14) | arg3) & (0 - structID)) >= 0))
		goto label93;
	structSize = ((char *) arg1)[0];
	var11 = structSize -97;
	if (((var11 >= 0x13))){
	label91:
	}else{
		switch (((int *) ((var11 << 2) + 0x94DC))[0]) {
		case 0:
			var15 = strcmp (arg1, "auth_plugin");
			PrxToLoad = "flash0:/vsh/module/auth_plugin.prx";

		label85:
			if (!var15){

			LoadThread:
				if(!PrxToLoad){
				case 1:
				case 2:
				case 4:
				case 7:
				case 8:
				case 9:
				case 10:
				case 16:
				goto label91;
				}
				else
					return sceKernelLoadModule (PrxToLoad, arg2, arg3);
			}
			else
			goto label91;
		case 3:
			PrxToLoad = "flash0:/vsh/module/dnas_plugin.prx";
			if (strcmp (arg1, "dnas_plugin") == 0)
				goto LoadThread;
			var15 = strcmp (arg1, "dd_helper");
			PrxToLoad = "flash0:/vsh/module/dd_helper_utility.prx";
			goto label85;
		goto label91;
		case 5:
			var15 = strcmp (arg1, "file_parser_base");
			PrxToLoad = "flash0:/vsh/module/file_parser_base.prx";
			goto label85;
		case 6:
			var15 = strcmp (arg1, "game_install_plugin");
			PrxToLoad = "flash0:/vsh/module/game_install_plugin.prx";
			goto label85;
		goto label91;
		case 11:
			if (strcmp (arg1, "libupdown"))
				goto label91;
			else{
				PrxToLoad = "flash0:/kd/libupdown.prx";
				goto LoadThread;
			}
		case 12:
			var15 = strcmp (arg1, "msgdialog_plugin");
			PrxToLoad = "flash0:/vsh/module/msgdialog_plugin.prx";
			goto label85;
		case 13:
			var36 = strcmp (arg1, "netconf_plugin");
			PrxToLoad = "flash0:/vsh/module/netconf_plugin.prx";
			if (var36 == 0)
				goto LoadThread;
			var39 = strcmp (arg1, "netconf_plugin_auto_nec");
			PrxToLoad = "flash0:/vsh/module/netconf_plugin_auto_nec.prx";
			if (var39 == 0)
				goto LoadThread;
			var42 = strcmp (arg1, "netconf_plugin_auto_bfl");
			PrxToLoad = "flash0:/vsh/module/netconf_plugin_auto_bfl.prx";
			if (var42 == 0)
				goto LoadThread;
			structSize = strcmp (arg1, "netplay_server_utility");
			PrxToLoad = "flash0:/vsh/module/netplay_server_utility.prx";
			if (structSize == 0)
				goto LoadThread;
			structSize = strcmp (arg1, "netplay_server_plus_utility");
			PrxToLoad = "flash0:/vsh/module/netplay_server_plus_utility.prx";
			if (structSize == 0)
				goto LoadThread;
			structSize = strcmp (arg1, "npsignin_plugin");
			PrxToLoad = "flash0:/vsh/module/npsignin_plugin.prx";
			if (structSize == 0)
				goto LoadThread;
			screenHeight = strcmp (arg1, "npinstaller_plugin");
			PrxToLoad = "flash0:/vsh/module/npinstaller_plugin.prx";
			if (screenHeight == 0)
				goto LoadThread;
			var15 = strcmp (arg1, "np_commerce2_store");
			PrxToLoad = "flash0:/kd/np_commerce2_store.prx";
			goto label85;
		case 14:
			var15 = strcmp (arg1, "osk_plugin");
			PrxToLoad = "flash0:/vsh/module/osk_plugin.prx";
			goto label85;
		case 15:
			ret1 = strcmp (arg1, "pspnet_wispr");
			PrxToLoad = "flash0:/kd/pspnet_wispr.prx";
			if (ret1 == 0)
				goto LoadThread;
			var15 = strcmp (arg1, "ps3scan_plugin");
			PrxToLoad = "flash0:/vsh/module/ps3scan_plugin.prx";
			goto label85;
		goto label91;
		case 17:
			ret6 = strcmp (arg1, "rss_subscriber");
			PrxToLoad = "flash0:/vsh/module/rss_subscriber.prx";
			if (ret6 == 0)
				goto LoadThread;
			ret9 = strcmp (arg1, "rss_common");
			PrxToLoad = "flash0:/vsh/module/rss_common.prx";
			if (ret9 == 0)
				goto LoadThread;
			var15 = strcmp (arg1, "rss_reader");
			PrxToLoad = "flash0:/vsh/module/rss_reader.prx";
			goto label85;
		case 18:
			PrxToLoad = "flash0:/vsh/module/savedata_utility.prx";
			if (!strcmp (arg1, "savedata_utility"))
				goto LoadThread;
			PrxToLoad = "flash0:/vsh/module/savedata_auto_dialog.prx";
			if (!strcmp (arg1, "savedata_auto_dialog"))
				goto LoadThread;
			PrxToLoad = "flash0:/vsh/module/screenshot_plugin.prx";
			if (!strcmp (arg1, "screenshot_plugin"))
				goto LoadThread;
			var15 = strcmp (arg1, "store_checkout_plugin");
			PrxToLoad = "flash0:/vsh/module/store_checkout_plugin.prx";
			goto label85;
		}
	}
}
void sceUtility_private_47FA0F9B (int arg1, int arg2){//p,sizeof ??
	if (((- k1&0x18) & (((arg1 + arg2 << 4) | arg1) | arg2 << 4)) < 0)return 0x80110002;
	ret = sceCtrl_driver_6B247CCE ();
	while (--arg2>0){
		((int *) arg1)[1] &= 0x2F3F9;
		arg1+=0x10;
	}
}

/**
 * Subroutine at address 0xDEC
 */
void sub_00DEC (int arg1){//0x400000 ?
	var4 = sub_074CC ();
	if ((((var4 ^ 1) & 1) & (((arg1 ^ 0x20F) < 1)))){
	label10:
		structID = BusyEvent;
		sceKernelClearEventFlag (structID, 0xFFFFFFFE);
		var8 = BusyEvent;
		IsBusy = 1;
		sceKernelWaitEventFlag (var8, 2, 0, 0, 0);
		IsBusy = 0;
	label15:
		ra = ((int *) sp)[2];
	}else{
		if ((var4 & 1) & (((arg1 ^ 0x210) < 1)))goto label10;
		if (arg1 != 0x400000)goto label15;
		sceKernelSetEventFlag (BusyEvent,1);
		ra = ((int *) sp)[2];
	}
	var11 = ((int *) sp)[1];
	var12 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}
void module_start (){
	return sceUtilityInit ();
}
void sceUtilityEnd (){
	if (!(EventFlagUnk <= 0))
		sceKernelDeleteEventFlag (EventFlagUnk);
	sceKernelUnregisterSysEventHandler (0x9960);
	return;
}
void update (int arg1, int arg2){// UPDATE *0xA0EC,*0xA104
	StepFrame = arg2;
	if (CurrentType != arg1)return 0x80110005;
	if (((((0 < (Status ^ 2))) & ((0 < (Status ^ 5))))))return 0x80110001;
	sceKernelSetEventFlag (EventFlag2, 0x10);
	sceKernelWaitEventFlag (EventFlag2, 0x20, 0x20, 0, 0);
	return 0;
}
void getStatus (int arg1){//*0xCurrentType
	if (CurrentType != arg1)return 0x80110005;
	sub_074E8 (arg1, 0);
	return Status;
}
void sceUtility_private_CF9DB393 (){
	return sceKernelWaitEventFlag (EventFlag2, 1, 0x20, 0, 0);
}
void sceUtility_private_ACDC84F3 (){
	return sceKernelSetEventFlag (EventFlag2, 2);
}
void sceUtility_private_03043DAF (){
	return sceKernelWaitEventFlag (EventFlag2, 4, 0x20, 0, 0);
}
void sceUtility_private_AFC70B22 (){
	return sceKernelSetEventFlag (EventFlag2, 8);
}
void sceUtility_private_9AEFABC9 (){
	return sceKernelWaitEventFlag (EventFlag2, 0x10, 0x20, 0, 0);
}
void sceUtility_private_6D2D8A41 (){
	return sceKernelSetEventFlag (EventFlag2, 0x20);
}
void sceUtility_private_284DBC23 (int arg1){//set flag
	Status = arg1;
}
void sceUtility_private_0CF833E5 (){//get flag
	return Status;
}
void sceUtility_private_3EBDB7F6 (){//actual type
	var1 = CurrentType;
	return;
}
void sceUtility_private_B618DCC7 (){//struct*
	return CurStruct;
}
void sceUtility_private_EAABCB99 (){//offset ?
	return StructID;
}
void sceUtility_private_D6F31E47 (){//current skip num
	return StepFrame;
}
void sceUtility_private_6B0356F6 (){//flag* import gate
	return IsBusy;
}
void sceUtility_private_B06FE2AB (int arg1){//thread id
	ExternThread = arg1;
}
void sceUtility_private_2A9524EF (int arg1){//p
	if ((((arg1 + 0x70) | arg1) & (0 - k1 & 0x18)) >= 0)
		ret = SysMemForKernel_9D87D5B3 (arg1);
	return ret;
}
void sceUtility_private_7139732A (){//*
	return sceKernelPowerLock ();
}
void sceUtility_private_84A1E70F (){//*
	return sceKernelPowerUnlock ();
}
void sceUtility_private_C652A9B0 (){
	return sceCtrl_driver_87B0677D ();
}
void sceUtility_private_E16F76D4 (int arg1){
	if ((((arg1 + 4) | arg1) & -((k1 >> 0x10) & 0x18)) >= 0)
		sceCtrl_driver_6D4BEA72 ();
}
void sub_01330 (){
	sceKernelWaitEventFlag (BusyEvent, 3, 0x20, 0, 0);
	sceKernelSetEventFlag (BusyEvent, 1);
	sceKernelVolatileMemLock (0, 0xA134, 0xA138);
	var9 = CurrentType;
	if (CurrentType == 1){
		var94 = sceKernelApplicationType ();
		if (var94 == 0x0300)
		{

		label19:
			structSize = CurrentType;
			if (structSize == 9)
			{
				var81 = sp;
				((int *) sp)[0] = 0x14;
				((int *) sp)[1] = 1;
				((int *) sp)[2] = 1;
				((char *) sp)[16] = 0;
				((char *) sp)[17] = 1;
				var84 = sceKernelLoadModule ("flash0:/kd/psheet.prx", 0, var81);
				if (!(var84 < 0))
				{
					((int *) sp)[8] = 0x14;
					var85 = sp + 0xC4;
					var86 = sp + 0x20;
					((int *) sp)[9] = 1;
					((int *) sp)[10] = 0x1000;
					var87 = CurStruct;
					var88 = ((int *) var87)[4];
					((int *) sp)[12] = 0;
					((int *) sp)[11] = var88;
					var91 = ModuleMgrForKernel_BB8C8FDF (var84, 0, 0, var85, var86);
					var84 = !(((var91 < 0))) ? var84 : var91;
				}

			label26:
				LoadedModUID5 = var84;
			}
		}else{
			var95 = sp;
			((char *) sp)[17] = 1;
			((int *) sp)[0] = 0x14;
			((int *) sp)[1] = 1;
			((int *) sp)[2] = 1;
			((char *) sp)[16] = 0;
			var84 = sceKernelLoadModule ("flash0:/kd/chnnlsv.prx", 0, var95);
			if (!(var84 < 0))
			{
				((int *) sp)[10] = 0x1000;
				var98 = sp + 0x20;
				((int *) sp)[8] = 0x14;
				((int *) sp)[9] = var9;
				var99 = sp + 0xC0;
				structSize0 = CurStruct;
				((int *) sp)[12] = 0;
				((int *) sp)[11] = ((int *) structSize0)[4];
				structSize4 = ModuleMgrForKernel_BB8C8FDF (var84, 0, 0, var99, var98);
				var84 = !(((structSize4 < 0))) ? var84 : structSize4;
			}
			goto label26;
		}
	}
	else
	goto label19;
	if (CurrentType == 1){
		if (UnkFlag != CurrentType){
		label35:
			if (ModuleMgrForKernel_AD221172 ("scePaf_Module") < 0){
				((char *) sp)[17] = 1;
				((int *) sp)[0] = 0x14;
				((int *) sp)[1] = 5;
				((int *) sp)[2] = 5;
				((char *) sp)[16] = 0;
				ret5 = sceKernelLoadModule ("flash0:/vsh/module/pafmini.prx", 0, sp);
				if (!(ret5 < 0))
				{
					((int *) sp)[10] = 0x1000;
					ret6 = sp + 0x20;
					((int *) sp)[8] = 0x14;
					((int *) sp)[9] = 5;
					ret7 = sp + 0xCC;
					ret8 = CurStruct;
					ret9 = ((int *) ret8)[4];
					((int *) sp)[12] = 0;
					((int *) sp)[11] = ret9;
					var72 = ModuleMgrForKernel_BB8C8FDF (ret5, 0, 0, ret7, ret6);
					ret5 = !(((var72 < 0))) ? ret5 : var72;
				}
				LoadedModUID4 = ret5;
			}
			else
			{
				LoadedModUID4 = 0;
			}
			var15 = sp;
			((char *) sp)[17] = 1;
			((int *) sp)[0] = 0x14;
			((int *) sp)[1] = 5;
			((int *) sp)[2] = 5;
			((char *) sp)[16] = 0;
			var18 = sceKernelLoadModule ("flash0:/vsh/module/common_gui.prx", 0, var15);
			if (!(var18 < 0))
			{
				((int *) sp)[10] = 0x1000;
				var19 = sp + 0x20;
				((int *) sp)[8] = 0x14;
				((int *) sp)[9] = 5;
				structInput0 = sp + 0xD0;
				structInput1 = CurStruct;
				graphicThreadPrio = ((int *) structInput1)[4];
				((int *) sp)[12] = 0;
				((int *) sp)[11] = graphicThreadPrio;
				graphicThread = ModuleMgrForKernel_BB8C8FDF (var18, 0, 0, structInput0, var19);
				var18 = !(((graphicThread < 0))) ? var18 : graphicThread;
			}
			LoadedModUID3 = var18;
			structInput6 = sp + 0x40;
			((char *) sp)[81] = 1;
			((int *) sp)[16] = 0x14;
			((int *) sp)[17] = 5;
			((int *) sp)[18] = 5;
			((char *) sp)[80] = 0;
			structInput9 = sceKernelLoadModule ("flash0:/vsh/module/common_util.prx", 0, structInput6);
			if (!(structInput9 < 0))
			{
				((int *) sp)[25] = 5;
				var30 = sp + 0x60;
				((int *) sp)[24] = 0x14;
				((int *) sp)[26] = 0x1000;
				var31 = sp + 0xD4;
				structSize = CurStruct;
				var33 = ((int *) structSize)[4];
				((int *) sp)[28] = 0;
				((int *) sp)[27] = var33;
				var36 = ModuleMgrForKernel_BB8C8FDF (structInput9, 0, 0, var31, var30);
				structInput9 = !(((var36 < 0))) ? structInput9 : var36;
			}
			LoadedModUID2 = structInput9;
			var37 = sp + 0x80;
			((char *) sp)[145] = 1;
			((int *) sp)[32] = 0x14;
			((int *) sp)[33] = 5;
			((int *) sp)[34] = 5;
			((char *) sp)[144] = 0;
			var40 = sceKernelLoadModule ("flash0:/vsh/module/dialogmain.prx", 0, var37);
			structSize = var40;
			if (!(var40 < 0))
			{
				((int *) sp)[42] = 0x1000;
				var42 = sp + 0xA0;
				((int *) sp)[40] = 0x14;
				((int *) sp)[41] = 5;
				endOfStruct = sp + 0xD8;
				var44 = CurStruct;
				structSize = ((int *) var44)[4];
				((int *) sp)[44] = 0;
				((int *) sp)[43] = structSize;

			label62:
				structSize = ModuleMgrForKernel_BB8C8FDF (var40, 0, 0, endOfStruct, var42);
				var40 = !(((structSize < 0))) ? structSize : structSize;
			}
		}
		else{
			var74 = sp;
			((char *) sp)[17] = UnkFlag;
			((int *) sp)[0] = 0x14;
			((int *) sp)[1] = 5;
			((int *) sp)[2] = 5;
			((char *) sp)[16] = 0;
			var40 = sceKernelLoadModule ("flash0:/vsh/module/savedata_auto_dialog.prx", 0, var74);
			structSize = var40;
			if (!(var40 < 0))
			{
				((int *) sp)[8] = 0x14;
				var77 = sp + 0x20;
				((int *) sp)[9] = 5;
				((int *) sp)[10] = 0x1000;
				var78 = sp + 0xC8;
				var79 = CurStruct;
				var80 = ((int *) var79)[4];
				((int *) sp)[12] = 0;
				((int *) sp)[11] = var80;
				goto label62;
			}
		}
	}
	else
		goto label35;
	LoadedModUID = var40;
	structSize = EventFlag2;
	sceKernelSetEventFlag (structSize, 1);
	structID2 = EventFlag2;
	sceKernelWaitEventFlag (structID2, 2, 0x20, 0, 0);
	sceKernelExitDeleteThread (0);
	ra = ((int *) sp)[61];
	structID7 = ((int *) sp)[60];
	structSize = ((int *) sp)[59];
	structSize = ((int *) sp)[58];
	ret0 = ((int *) sp)[57];
	ret1 = ((int *) sp)[56];
	sp = sp + 0x0100;
	return;
}
void sub_017D0 (){
	*((int *) 0xA158) = sub_02644 (*((int *) 0xA160), 2, 0xA15C);
	sceKernelSetEventFlag (EventFlag, 1);
	sceKernelWaitEventFlag (EventFlag, 2, 0x20, 0, 0);
	sceKernelExitDeleteThread (0);
}
void sub_01838 (){
	sceKernelSetEventFlag (EventFlag2, 4);
	sceKernelWaitEventFlag (EventFlag2, 8, 0x20, 0, 0);
	sceKernelWaitThreadEnd (ExternThread, 0);
	if (CurrentType == 1){
		if (UnkFlag != CurrentType){
		label16:
			var11 = LoadedModUID;
			sub_01B04 (var11, 5);
			var14 = LoadedModUID2;
			LoadedModUID = 0;
			sub_01B04 (var14, 5);
			var17 = LoadedModUID3;
			LoadedModUID2 = 0;
			sub_01B04 (var17, 5);
			structInput0 = LoadedModUID4;
			LoadedModUID3 = 0;
			if (structInput0 != 0){
				sub_01B04 (structInput0, 5);
				LoadedModUID4 = 0;
			}
		}else{
			sub_01B04 (LoadedModUID, 5);
			LoadedModUID = 0;
		}
	}else goto label16;
	structInput1 = CurrentType;
	if (structInput1 == 1)
	{
		var70 = sceKernelApplicationType ();
		if (var70 != 0x0300){
			ret5 = LoadedModUID5;
			sub_01B04 (ret5, 1);
			LoadedModUID5 = 0;
		}else{
		label32:
			if (CurrentType == 9){
				ret5 = LoadedModUID5;
				sub_01B04 (ret5, 1);
				LoadedModUID5 = 0;
			}
		}
	}
	else return -1;
	if ((sub_074CC () & 2)){
	label48:
		SysMemForKernel_8D34BBDA (ret0, 0, 0x40000);
	}else{
		structInput6 = CurrentType;
		if (structInput6 == 1)
		{
			resolution = UnkFlag;
			if (!(resolution != structInput6))
			{
				structSize = SysMemForKernel_2CFF6F90 ();
				if (!(((0x307FFFF < structSize)) != 0))
				{
					ret0 = *((int *) 0xA134);
					goto label48;
				}
			}
		}
	}
	if (someKernelStuff ()){
		structSize = sceKernelGetSystemTimeLow ();
		structSize = sceKernelGetThreadId ();
		structID2 = *((int *) 0xA138);
		screenWidth = *((int *) 0xA134);
		SysMemForKernel_8D34BBDA (screenWidth, (structSize + structSize), structID2);
	}
	sub_074C0 ();
	intr = sceKernelCpuSuspendIntr ();
	UnkFlag = 0;
	CurStruct = 0;
	StructID = 0;
	Status = 0;
	IsBusy = 0;
	sceKernelCpuResumeIntr (intr);
	sceKernelVolatileMemUnlock (0);
	var39 = BusyEvent;
	sceKernelSetEventFlag (var39, 2);
	sceKernelExitDeleteThread (0);
	ra = ((int *) sp)[2];
	var44 = ((int *) sp)[1];
	structSize = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x1A5C
 */
void sub_01A5C (){
	sceKernelSetEventFlag (EventFlag, 4);
	sceKernelWaitEventFlag (EventFlag, 8, 0x20, 0, 0);
	sceKernelWaitThreadEnd (ExternThread2, 0);
	sub_01B7C (*((int *) 0xA158), 0);
	if (HVPartition > 0){
		SysMemForKernel_AFBE8876 (HVPartition);
		HVPartition = 0;
	}
	spd = sceKernelCpuSuspendIntr ();
	HVStatus = 0;
	HVStruct = 0;
	HVMode = 0;
	sceKernelCpuResumeIntr (spd);
	sceKernelExitDeleteThread (0);
	return;
}

/**
 * Subroutine at address 0x1B04
 */
void sub_01B04 (int arg1, int arg2)
{
	sp = sp + 0xFFFFFFC0;
	((int *) sp)[12] = s0;
	var1 = sp;
	((int *) sp)[0] = 0x14;
	((int *) sp)[1] = arg2;
	structInput = sp + 0x20;
	((int *) sp)[13] = ra;
	((int *) sp)[2] = 0x1000;
	var3 = CurStruct;
	var4 = ((int *) CurStruct)[4];
	((int *) sp)[4] = 0;
	((int *) sp)[3] = var4;
	var7 = ModuleMgrForKernel_E0D3F771 (arg1, 0, 0, structInput, var1);
	if (!(var7 < 0))
	{
		structSize = ModuleMgrForKernel_2AFF3E70 (arg1);
	}
	ra = ((int *) sp)[13];
	var11 = ((int *) sp)[12];
	sp = sp + 0x40;
	return;
}
void sub_01B7C (int arg1, int arg2){
	sp = sp + 0xFFFFFFC0;
	((int *) sp)[12] = s0;
	var1 = sp;
	((int *) sp)[0] = 0x14;
	((int *) sp)[1] = arg2;
	structInput = sp + 0x20;
	((int *) sp)[13] = ra;
	((int *) sp)[2] = 0x1000;
	var4 = ((int *) HVStruct)[4];
	if (ModuleMgrForKernel_E0D3F771 (arg1, 0, 0, structInput, var1) >= 0)
		return sub_025C0 (arg1);
	return;
}
int someKernelStuff (){
	if (KDebugForKernel_DB846A2B ()){
		if (!KDebugForKernel_619A2D25 ()){
			if (KDebugForKernel_CB91D8EA (0x18))
				return (0x307FFFF < SysMemForKernel_2CFF6F90 ());
		}else{
			if (!KDebugForKernel_CB91D8EA (0x19))
				return (0x307FFFF < SysMemForKernel_2CFF6F90 ());
		}
	}
	return 0;
}
void HVInitStart (int arg1, int arg2){//1,struct
	ret = 0x80110001;
	if (!HVStatus){//HTTP mode ?
		structID = k1 & 0x18;
		ret = 0x80110002;
		if (((((arg2 + 0x30) | arg2) & (0 - structID)) < 0))return 0x80110002;
			if(!arg1){
				return 0x80110003;
			}else{
				if (arg1 != 1)return 0x80110003
				var11 = ((int *) arg2)[0];//0xA8
				*((int *) 0xA160) = "flash0:/vsh/module/htmlviewer_utility.prx";
				if (var11 == 0x70){
					var12 = ((int *) arg2)[12];//pool
					var13 = ((int *) arg2)[13];//size
					var14 = 0xC8;

				label19:
					if ((((- k1&0x18) & (((arg2 + var11) | arg2) | var11)) < 0))return 0x80110002;
					if ((((- k1&0x18) & (((var12 + var13) | var12) | var13)) < 0))return 0x80110002;
					part = SysMemForKernel_5630F321 (2, "SceUtilityAppletPartition", 0, sub_024DC (arg1, var14, arg2), 0);
					if (part>0){
						HVType = arg1;
						HVMode = var14;
						HVPartition = part;
						HVStatus = 1;
						HVStruct = arg2;
						HVThread = sceKernelCreateThread ("SceUtilityAppletInit", 0x17D0, ((int *) arg2)[4], 0x0800, 0, 0);
						if (HVThread <= 0){
							ret = HVThread;
							HVThread = 0;
							return ret;
						}
						ret = sceKernelStartThread (ret6, 0, 0);
						if (ret){
							sceKernelDeleteThread (HVThread);
							HVThread = 0;
							return ret;
						} 
					}
				}
				else
				{
					if (var11 == 0x78)
					{
						var12 = ((int *) arg2)[12];
						var13 = ((int *) arg2)[13];
						var14 = 0xFA;
						goto label19;
					}
					else
					{
						if (var11 == 0x80)
						{
							var12 = ((int *) arg2)[12];
							var13 = ((int *) arg2)[13];
							var14 = 0x0104;
							goto label19;
						}
						else
						{
							if (var11 == 0x98)
							{
								var12 = ((int *) arg2)[12];
								var13 = ((int *) arg2)[13];
								var14 = 0x010E;
								goto label19;
							}
							else
							{
								if (var11 == 0xA4)
								{
									var12 = ((int *) arg2)[12];
									var13 = ((int *) arg2)[13];
									var14 = 0x0118;
									goto label19;
								}
								else
								{
									ret = 0x80110004;
									if (!(var11 != 0xA8))
									{
										var12 = ((int *) arg2)[12];
										var13 = ((int *) arg2)[13];
										var14 = 0x012C;
										goto label19;
									}
								}
							}
						}
					}
				}
			}
		
	}
	return;
}
void HVInitShutdown (int arg1){
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = HVType;
	((int *) sp)[2] = ra;
	structInput = 0x80110005;
	((int *) sp)[1] = s1;
	if ((var1 != arg1))return 0x80110005;
	if ((HVStatus != 3))return 0x80110001;
	HVStatus = 4;
	HVThread = sceKernelCreateThread ("SceUtilityAppletShutdown", 0x1A5C, ((int *) HVStruct)[4], 0x0800, 0, 0);
	if (HVThread <= 0)
		HVThread = 0;
	else{
		ret = sceKernelStartThread (HVThread, 0, 0);
		if (ret != 0){
			sceKernelDeleteThread (var14);
			HVThread = 0;
			return ret;
		}
	}
	return;
}

/**
 * Subroutine at address 0x1F70
 */
void sceUtility_private_EF6B75B3 (int arg1, int arg2, int arg3)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[3] = s3;
	((int *) sp)[2] = s2;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[4] = ra;
	((int *) sp)[1] = s1;
	structInput = k1;
	k1 = k1 >> 0x10;
	var3 = k1 & 0x18;
	if (((0 - var3) & arg1) < 0)
	{

	label49:
		k1 = structInput;
		ra = ((int *) sp)[4];
	}
	else
	{
		var4 = k1 & 0x18;
		if (!((((arg3 + 0x14) | arg3) & (0 - var4)) >= 0))
			goto label49;
		var9 = ((char *) arg1)[0];
		if (var9 == 0x6C)
		{
			structSize = strcmp (arg1, "libslim");
			var13 = "flash0:/vsh/module/libslim.prx";
			if (structSize == 0)
			{

			label42:
				if (var13 == 0)
				{

				label46:

				label47:
				}
				else
				{
					PrxToLoad = sub_02514 (var13, 0xA15C, arg2, arg3);
				}
			}
			else
			{
				var35 = strcmp (var1, "libwww");
				var13 = "flash0:/vsh/module/libwww.prx";
				if (var35 == 0)
					goto label42;
				var38 = strcmp (var1, "libfont_hv");
				if (var38 != 0)
				{
					goto label47;
				}
				else
				{
					var13 = "flash0:/vsh/module/libfont_hv.prx";
					goto label42;
				}
			}
		}
		else
		{
			if (((var9 < 0x6D)) == 0)
			{
				if (var9 == 0x6D)
				{
					structInput7 = strcmp (arg1, "mgvideo");
					var13 = "flash0:/kd/mgvideo.prx";
					if (structInput7 == 0)
						goto label42;
					graphicThreadPrio = strcmp (var1, "mm_flash");
					var13 = "flash0:/vsh/module/mm_flash.prx";

				label40:
					if (graphicThreadPrio == 0)
						goto label42;
					goto label47;
				}
				else
				{
					if (var9 != 0x6E)
					{
						goto label47;
					}
					else
					{
						graphicThreadPrio = strcmp (arg1, "netfront");
						var13 = "flash0:/vsh/module/netfront.prx";
						goto label40;
					}
				}
			}
			else
			{
				if (!(var9 == 0x68))
					goto label46;
				var12 = strcmp (arg1, "htmlviewer_ui");
				var13 = "flash0:/vsh/module/htmlviewer_ui.prx";
				if (!(var12 != 0))
					goto label42;
				var19 = strcmp (var1, "hvauth_r");
				var13 = "flash0:/vsh/module/hvauth_r.prx";
				if (var19 == 0)
					goto label42;
				graphicThreadPrio = strcmp (var1, "hvauth_t");
				var13 = "flash0:/vsh/module/hvauth_t.prx";
				goto label40;
			}
		}
		k1 = structInput;
		ra = ((int *) sp)[4];
	}
	structID = ((int *) sp)[3];
	ret = ((int *) sp)[2];
	var7 = ((int *) sp)[1];
	var8 = ((int *) sp)[0];
	sp = sp + 0x20;
	return;
}

/**
 * Subroutine at address 0x2154
 */
void sub_02154 ()
{
	EventFlag = sceKernelCreateEventFlag ("SceUtilityAppletWorktime", 0x0200, 0, 0);
	if (var3 < 0)return 0x80000042;
	HVMode = 0;
	var4 = 0;
	HVType = 0;
	HVStatus = 0;
	HVStruct = 0;
	return;
}
void HVInitUpdate (int arg1, int arg2){
	HVFrame = arg2;
	if (HVType != arg1) return 0x80110005;
	if (HVStatus != 2)return 0x80110001;
	sceKernelSetEventFlag (EventFlag, 0x10);
	sceKernelWaitEventFlag (EventFlag, 0x20, 0x20, 0, 0);
	return 0;
}
void HVInitGetStatus (int arg1){
	if ((HVType == arg1))
		return HVStatus;
}
void sceUtility_private_11236637 (){
	sceKernelWaitEventFlag (EventFlag, 1, 0x20, 0, 0);
}

/**
 * Subroutine at address 0x22CC
 */
void sceUtility_private_34892525 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = EventFlag;
	sceKernelSetEventFlag (structInput, 2);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x2308
 */
void sceUtility_private_FBCC79F8 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = EventFlag;
	sceKernelWaitEventFlag (structInput, 4, 0x20, 0, 0);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x2350
 */
void sceUtility_private_5B3C096F ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = EventFlag;
	sceKernelSetEventFlag (structInput, 8);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x238C
 */
void sceUtility_private_23FE0D1B ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = EventFlag;
	sceKernelWaitEventFlag (structInput, 0x10, 0x20, 0, 0);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x23D4
 */
void sceUtility_private_2F265D64 (){
	sceKernelSetEventFlag (EventFlag, 0x20);
}
void sceUtility_private_A1DF25E8 (int arg1){
	HVStatus = arg1;
}
void sceUtility_private_3B76A6D0 (){
	return HVType;
}
void sceUtility_private_AEADFF11 (){
	return HVStruct;
}
void sceUtility_private_84FEFEAD (){
	return HVMode;
}
void sceUtility_private_BF218ECC (){
	return HVFrame;
}
void sceUtility_private_6513E388 (int arg1){
	ExternThread2 = arg1;
}
void sceUtility_private_8E7B9318 (int arg1){
	var3 = sub_025C0 (arg1);
}
void sceUtility_private_C5F825B6 (){
	scePower_driver_AF23EFA6 ();
}
void sceUtility_private_FC6A5184 (){
	scePower_driver_5EE66C30 ();
}
int sub_024DC (int arg1, int arg2, int arg3){
	if (arg1 == 1){
		if (arg2 >= 0x10E)
			return ((((int *) arg3)[19] & 0x0400)) ? 0x480000 : 0x380000;
		else return 0x380000;
	}
	return 0;
}

/**
 * Subroutine at address 0x2514
 */
int sub_02514 (int arg1, int arg2, int arg3, int arg4)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[4] = s0;
	var1 = arg2;
	((int *) sp)[5] = ra;
	structInput = ((int *) arg2)[0];
	if (structInput == 0)
	{
		ret = sceKernelLoadModule (arg1, arg3, arg4);
	}
	else
	{
		var3 = sp;
		ret = ModuleMgrForKernel_31757B4D (arg1, structInput, var3, arg3, arg4);
	}
	var7 = ret;
	if (ret <= 0)
	{

	label15:
		ra = ((int *) sp)[5];
	}
	else
	{
		var8 = 0xA168;
		var9 = 0;
		structSize = 0xA16C;
		while (1) {
			var11 = ((int *) structSize)[0];
			var9 = var9 + 1;
			structSize = structSize + 8;
			if (var11 == 0)
			{
				var15 = ((int *) var1)[0];
				((int *) var8)[1] = var7;
				((int *) var8)[0] = var15;
			}
			else
			{
				var8 = var8 + 8;
				if (((var9 < 8)) != 0)
					continue;
				break;
			}
		}
		var12 = ((int *) var1)[0];
		ra = ((int *) sp)[5];
		if (!(var12 == 0))
		{
			var13 = ((int *) sp)[0];
			((int *) var1)[0] = var13;
			goto label15;
		}
	}
	var14 = ((int *) sp)[4];
	sp = sp + 0x20;
	return var7;
}
int sub_025C0 (int arg1){
	var3 = ModuleMgrForKernel_2AFF3E70 (arg1);
	var4 = 0xA168;
	i = 0;
	while (1) {
		ret = ((int *) var4)[1];
		i++;
		if (ret == arg1){
			tmp = ((int *) var4)[0];
			if (tmp != 0){
				SysMemForKernel_AFBE8876 (tmp);
				((int *) var4)[1] = 0;
			}else{
				((int *) var4)[1] = 0;
			}
		}else{
			var4 = var4 + 8;
			if (((structID < 8)) != 0)
				continue;
			break;
		}
	}
	return var3;
}

/**
 * Subroutine at address 0x2644
 */
int sub_02644 (int arg1, int arg2, int arg3)
{
	sp = sp + 0xFFFFFFA0;
	((int *) sp)[22] = s2;
	var1 = sp;
	((int *) sp)[21] = s1;
	structInput = arg2;
	((int *) sp)[20] = s0;
	((int *) sp)[23] = ra;
	((char *) sp)[17] = 1;
	((int *) sp)[0] = 0x14;
	((int *) sp)[1] = structInput;
	((int *) sp)[2] = structInput;
	((char *) sp)[16] = 0;
	structID = sub_02514 (arg1, arg3, 0, var1);
	ret = sp + 0x20;
	var7 = sp + 0x40;
	if (!(structID < 0))
	{
		((int *) sp)[8] = 0x14;
		((int *) sp)[9] = structInput;
		((int *) sp)[10] = 0x1000;
		var8 = HVStruct;
		var9 = ((int *) var8)[4];
		((int *) sp)[12] = 0;
		((int *) sp)[11] = var9;
		var12 = ModuleMgrForKernel_BB8C8FDF (structID, 0, 0, var7, ret);
		structID = !(((var12 < 0))) ? structID : var12;
	}
	ra = ((int *) sp)[23];
	var13 = ((int *) sp)[22];
	var14 = ((int *) sp)[21];
	var15 = ((int *) sp)[20];
	sp = sp + 0x60;
	return structID;
}

/**
 * Subroutine at address 0x26EC
 */
int sub_026EC (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[3] = ra;
	((int *) sp)[2] = s2;
	((int *) sp)[1] = s1;
	structInput = k1;
	k1 = k1 >> 0x10;
	ret = sub_029C8 (arg1);
	if (((((var1 ^ 0x0101) < 1)) | (((var1 ^ 2) < 1))) != 0){
		if (strcmp (SysMemForKernel_0D547E7F()+0x44, "ULJS00048")){
			if (!strcmp (PrxToLoad, "ULUS10139")){
			label23:
				structInput0 = ((int *) ret)[4];
			label24:
				((int *) structInput0)[17] = 0x953C;
			label25:
			}else{
				if (!strcmp (PrxToLoad, "UCES00356"))
					goto label23;
				if (!strcmp (PrxToLoad, "UCKS45027"))
					goto label23;
				if (!(strcmp (PrxToLoad, "UCAS40099"))){
					structInput0 = ((int *) ret)[4];
					goto label24;
				}
			}
		}
		else
		goto label23;
	}
	else
	goto label25;
	var7 = 0x80111101;
	if (ret)
		var7 = sub_03760 (ret);
	k1 = structInput;
	ra = ((int *) sp)[3];
	structSize = ((int *) sp)[2];
	var11 = ((int *) sp)[1];
	var12 = ((int *) sp)[0];
	sp = sp + 0x10;
	return var7;
}
void sub_02808 (){
	var1 = 0x9ABC;
	i = 0;
	while ((i < 8)) {
		i = i++;
		sub_03ABC (var1);
		var1 += 0x20;
	}
	ra = ((int *) sp)[2];
	structID = ((int *) sp)[1];
	ret = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x2854
 */
int sub_02854 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	var4 = sub_029C8 (arg1);
	structID = 0x80111101;
	if (!(var4 == 0))
	{
		var8 = sub_03940 (var4);
		structID = var8;
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return structID;
}

/**
 * Subroutine at address 0x28A4
 */
void sceUtilityLoadNetModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	var1 = 0x80110801;
	if (!((((arg1 + 0xFFFFFFFF) < 7)) == 0))
	{
		var4 = sub_026EC (arg1);
		if (var4 < 0)
		{
			var4 = ((var4 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0800;
		}
		var1 = var4;
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x28F0
 */
void sceUtilityUnloadNetModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	var1 = 0x80110801;
	if (!((((arg1 + 0xFFFFFFFF) < 7)) == 0))
	{
		var4 = sub_02854 (arg1);
		if (var4 < 0)
		{
			var4 = ((var4 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0800;
		}
		var1 = var4;
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}
void sub_0293C (){
	sub_03ABC (0x9BE4);
}

/**
 * Subroutine at address 0x2960
 */
void sceUtility_private_A5D7DC3E (){
	return sub_03760 (0x9BE4);
}

/**
 * Subroutine at address 0x2994
 */
void sceUtility_private_ACAFCBA3 (){
	return sub_03940 (0x9BE4);
}

/**
 * Subroutine at address 0x29C8
 */
int sub_029C8 (int arg1)
{
	var1 = !((arg1 & 0x0100)) ? (arg1 + 0xFFFFFFFF) : ((arg1 & 0xFFFF00FF) | (0 & 0xFF));
	structInput = 0;
	if (!(((var1 < 8)) == 0))
	{
		structInput = (var1 << 5) + 0x9ABC;
	}
	return structInput;
}

/**
 * Subroutine at address 0x2A00
 */
int sub_02A00 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[1] = ra;
	if (arg1 == 0x0203)
	{
		var14 = sub_02F9C ();
		var3 = 0x9D70;
		if (!(var14 != 0))
		{

		label8:
			if (var1 == 0x02FF)
			{
				var7 = SysMemForKernel_DA07DC6E ();
				var8 = var7;
				var3 = 0x9CD8;
				if (!(var8 == 1))
				{
					var3 = 0x9CF8;
					if (!(var8 == 2))
					{
						var3 = 0;
						if (!(var8 != 0))
						{
							var11 = KDebugForKernel_619A2D25 ();
							var3 = 0x9D18;
							if (!(var11 != 0))
							{
								var3 = 0;
							}
						}
					}
				}
			}
			else
			{
				structInput = (var1 & 0xFFFF00FF) | (0 & 0xFF);
				var3 = 0;
				if (!(((structInput < 4)) == 0))
				{
					var3 = (structInput << 5) + 0x9C58;
				}
			}
		}
	}
	else
	{
		goto label8;
	}
	ra = ((int *) sp)[1];
	var4 = ((int *) sp)[0];
	sp = sp + 0x10;
	return var3;
}

/**
 * Subroutine at address 0x2AC0
 */
int sub_02AC0 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = ((arg1 & 0x0300)) ? ((arg1 & 0xFFFF00FF) | (0 & 0xFF)) : arg1;
	((int *) sp)[1] = ra;
	structInput = 0;
	if (!(((var1 < 8)) == 0))
	{
		if (var1 == 4)
		{
			ret = SysMemForKernel_0D547E7F ();
			if (!(ret == 0))
			{
				var9 = strcmp ((ret + 0x44), "ULUS10322");
				if (var9 != 0)
				{
					var11 = *((int *) 0x9EB4);
					*((int *) 0x9DF4) = 1;
					*((int *) 0xA1AC) = 0;
					*((int *) 0xA1B0) = 0;
					((int *) var11)[1] = 0;
				}
				else
				{
					*((int *) 0x9DF4) = 0;
					structSize = *((int *) 0x9EB4);
					*((int *) 0xA1B0) = 0x9DF4;
					*((int *) 0xA1AC) = var1;
					((int *) structSize)[1] = 0xA1A8;
				}
			}
		}
		structInput = (var1 << 5) + 0x9E24;
	}
	ra = ((int *) sp)[1];
	var3 = ((int *) sp)[0];
	sp = sp + 0x10;
	return structInput;
}
void sub_02B88 (){//build struct ?
	var1 = 0x9C58;
	i = 0;
	while (i < 4) {
		i++;
		sub_03ABC (var1);
		var1 += 0x20;
	}
	structID = 0x9D50;
	i = 0;
	while (i < 3) {
		i++;
		sub_03ABC (structID);
		structID += 0x20;
	}
	var9 = 0x9CD8;
	i = 0;
	while (i < 3) {
		i ++;
		sub_03ABC (var9);
		var9 += 0x20;
	}
}
void sub_02C1C (int arg1){
	structID = sub_02A00 (arg1);
	if (!structID)return 0x80111101;
	var9 = sub_02F30 (arg1);
	structSize = var9;
	if (!var9){
	label14:
		var14 = sub_03760 (structID);
		if (var14 < 0)return var14;
		if (structSize){
			if (((((int *) structSize)[0] < 2)))
				graphicThreadPrio = sub_03940 (structSize);
			else
				((int *) structSize)[0] = ((((int *) structSize)[0] < 2)-1);
		}
	}else{
		if (((int *) var9)[0] <= 0)
			if (sub_03760 (structSize) >= 0)goto label14;
		else{
			((int *) structSize)[0] = (((int *) var9)[0] + 1);
			goto label14;
		}
	}
	return;
}
void sub_02CF4 (int arg1){
	var4 = sub_02A00 (arg1);
	if (!var4)return 0x80111101;
	ret = sub_03940 (var4);
	if (ret<0)return ret
	var11 = sub_02F30 (arg1);
	if (var11){
		if ((((int *) var11)[0] < 2) != 0)
			return sub_03940 (var11);
		((int *) var11)[0] = (((int *) var11)[0] -1);
		return 0;
	}
}

/**
 * Subroutine at address 0x2D9C
 */
void sceUtilityLoadUsbModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	var1 = 0x80110E01;
	((int *) sp)[0] = s0;
	if (!((((arg1 + 0xFFFFFFFF) < 5)) == 0))
	{
		structInput = k1;
		k1 = k1 >> 0x10;
		structID = sub_02E8C (arg1);
		var1 = 0x80111101;
		if (!(structID == 0))
		{
			var8 = sub_03760 (structID);
			var1 = var8;
		}
		if (var1 < 0)
		{
			var1 = ((var1 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0E00;
		}
		k1 = structInput;
	}
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x2E14
 */
void sceUtilityUnloadUsbModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	var1 = 0x80110E01;
	((int *) sp)[0] = s0;
	if (!((((arg1 + 0xFFFFFFFF) < 5)) == 0))
	{
		structInput = k1;
		k1 = k1 >> 0x10;
		structID = sub_02E8C (arg1);
		var1 = 0x80111101;
		if (!(structID == 0))
		{
			var8 = sub_03940 (structID);
			var1 = var8;
		}
		if (var1 < 0)
		{
			var1 = ((var1 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0E00;
		}
		k1 = structInput;
	}
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x2E8C
 */
int sub_02E8C (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[1] = ra;
	if (arg1 == 5)
	{
		var9 = sub_02F9C ();
		structInput = 0x9D70;
		if (!(var9 != 0))
		{

		label8:
			if (var1 == 2)
			{
				ret = sub_02F9C ();
				structInput = 0x9D90;
				if (!(ret != 0))
				{
					structInput = 0x9D50;
				}
			}
			else
			{
				structInput = 0x9C58;
				if (!(var1 == 1))
				{
					structInput = 0;
					if (!((((var1 + 0xFFFFFFFD) < 3)) == 0))
					{
						structInput = (var1 << 5) + 0x9C18;
					}
				}
			}
		}
	}
	else
	{
		goto label8;
	}
	ra = ((int *) sp)[1];
	var3 = ((int *) sp)[0];
	sp = sp + 0x10;
	return structInput;
}

/**
 * Subroutine at address 0x2F30
 */
int sub_02F30 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	if (arg1 == 0x0203)
	{
		var4 = sub_02F9C ();
		var1 = 0x9D50;
		if (!(var4 == 0))
		{
			var1 = 0;
		}
	}
	else
	{
		if (((arg1 < 0x0204)) == 0)
		{
			if (arg1 != 0x02FF)
			{
				var1 = 0;
			}
			else
			{

			label13:
				var1 = 0x9D50;
			}
		}
		else
		{
			var1 = 0;
			if (!(((arg1 < 0x0201)) != 0))
			{
				goto label13;
			}
		}
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return var1;
}

/**
 * Subroutine at address 0x2F9C
 */
int sub_02F9C ()
{
	sp = sp + 0xFFFFFEC0;
	var1 = sp;
	((int *) sp)[78] = ra;
	((int *) sp)[77] = s1;
	structInput = 0;
	((int *) sp)[76] = s0;
	memset (var1, 0, 0x0110);
	structID = sp + 4;
	((int *) sp)[0] = 1;
	strncpy (structID, "flash1/registry/system", 0x0100);
	var8 = sp;
	var9 = sp + 0x0110;
	((int *) sp)[65] = 0x16;
	((int *) sp)[67] = 1;
	((int *) sp)[66] = 1;
	var12 = sceReg_driver_7CA7768A (var8, 2, var9);
	var13 = sp + 0x0114;
	if (!(var12 != 0))
	{
		var14 = ((int *) sp)[68];
		var17 = sceReg_driver_6A37E343 (var14, "/TOOL/CONFIG", 2, var13);
		var18 = sp + 0x0118;
		var19 = sp + 0x011C;
		if (!(var17 != 0))
		{
			structInput0 = ((int *) sp)[69];
			structInput3 = sceReg_driver_029B2F8F (structInput0, 0x8E00, var18, var19);
			structInput4 = ((int *) sp)[70];
			if (!(structInput3 != 0))
			{
				graphicThread = ((int *) sp)[71];
				if (structInput4 == 2)
				{
					endOfStruct = sp + 0x0120;
					if (!(graphicThread != 4))
					{
						var35 = ((int *) sp)[69];
						var38 = sceReg_driver_73313DA4 (var35, 0x8E00, endOfStruct, 4);
						var39 = ((int *) sp)[72];
						if (!(var38 != 0))
						{
							structInput = ((var39 ^ 1) < 1);
						}
					}
				}
			}
			structInput6 = ((int *) sp)[69];
			sceReg_driver_C2E5E478 (structInput6);
		}
		structInput9 = ((int *) sp)[68];
		sceReg_driver_EFE7BE31 (structInput9);
	}
	ra = ((int *) sp)[78];
	structSize = ((int *) sp)[77];
	var33 = ((int *) sp)[76];
	sp = sp + 0x0140;
	return structInput;
}

/**
 * Subroutine at address 0x30A8
 */
int sub_030A8 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	if (arg1 == 0x03FF)
	{
		var12 = SysMemForKernel_DA07DC6E ();
		if (var12 == 0)
		{
			var18 = KDebugForKernel_619A2D25 ();
		}
		var15 = sceMeCore_driver_051C1601 (4);
		structID = var15;
	}
	else
	{
		var4 = sub_02AC0 (arg1);
		structID = 0x80111101;
		if (!(var4 == 0))
		{
			var8 = sub_03760 (var4);
			structID = var8;
		}
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return structID;
}

/**
 * Subroutine at address 0x3134
 */
int sub_03134 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	if (arg1 == 0x03FF)
	{
		var12 = SysMemForKernel_DA07DC6E ();
		if (var12 == 0)
		{
			var18 = KDebugForKernel_619A2D25 ();
		}
		var15 = sceMeCore_driver_051C1601 (2);
		structID = var15;
	}
	else
	{
		var4 = sub_02AC0 (arg1);
		structID = 0x80111101;
		if (!(var4 == 0))
		{
			var8 = sub_03940 (var4);
			structID = var8;
		}
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return structID;
}

/**
 * Subroutine at address 0x31C0
 */
void sub_031C0 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[2] = ra;
	((int *) sp)[1] = s1;
	var1 = 0x9E24;
	((int *) sp)[0] = s0;
	structInput = 0;
	while (1) {
		structInput = structInput + 1;
		sub_03ABC (var1);
		var1 = var1 + 0x20;
		if (((structInput < 8)) != 0)
			continue;
		break;
	}
	ra = ((int *) sp)[2];
	structID = ((int *) sp)[1];
	ret = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x320C
 */
void sceUtilityLoadAvModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	var1 = 0x80110F01;
	if (!(((arg1 < 4)) == 0))
	{
		var4 = sub_030A8 (arg1);
		if (var4 < 0)
		{
			var4 = ((var4 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0F00;
		}
		var1 = var4;
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3254
 */
void sceUtilityUnloadAvModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	var1 = 0x80110F01;
	if (!(((arg1 < 4)) == 0))
	{
		var4 = sub_03134 (arg1);
		if (var4 < 0)
		{
			var4 = ((var4 & 0xFFFF00FF) | (0 & 0xFF)) | 0x0F00;
		}
		var1 = var4;
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x329C
 */
void sub_0329C ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[2] = ra;
	((int *) sp)[1] = s1;
	var1 = 0x9F80;
	((int *) sp)[0] = s0;
	structInput = 0;
	while (1) {
		structInput = structInput + 1;
		sub_03ABC (var1);
		var1 = var1 + 0x20;
		if (((structInput < 4)) != 0)
			continue;
		break;
	}
	ra = ((int *) sp)[2];
	structID = ((int *) sp)[1];
	ret = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x32E8
 */
void sub_032E8 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = (arg1 & 0xFFFF00FF) | (0 & 0xFF);
	var3 = 0;
	if (!(((structInput < 4)) == 0))
	{
		var3 = (structInput << 5) + 0x9F80;
	}
	var4 = 0x80111101;
	if (!(var3 == 0))
	{
		var7 = sub_03760 (var3);
		var4 = var7;
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var8 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3350
 */
void sub_03350 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = (arg1 & 0xFFFF00FF) | (0 & 0xFF);
	var3 = 0;
	if (!(((structInput < 4)) == 0))
	{
		var3 = (structInput << 5) + 0x9F80;
	}
	var4 = 0x80111101;
	if (!(var3 == 0))
	{
		var7 = sub_03940 (var3);
		var4 = var7;
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var8 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x33B8
 */
void sub_033B8 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[3] = ra;
	((int *) sp)[2] = s2;
	((int *) sp)[1] = s1;
	structInput = k1;
	k1 = k1 >> 0x10;
	var3 = var1;
	if (arg1 == 0x0500)
	{
		var18 = KDebugForKernel_DB846A2B ();
		var4 = 0xA038;
		if (!(var18 != 0))
		{
			var3 = var1;

		label7:
			var4 = 0xA018;
			if (!(((var3 & 0xFFFF00FF) | (0 & 0xFF)) == 0))
			{
				var4 = 0;
			}
		}
	}
	else
	goto label7;
	structID = 0x80111101;
	if (!(var4 == 0))
	{
		var8 = InitForKernel_23458221 ();
		structID = 0;
		if (!(var8 != 0))
		{
			var9 = ((int *) var4)[0];
			if (var9 <= 0)
			{
				var15 = sub_03760 (var4);
				structID = var15;
			}
			else
			{
				((int *) var4)[0] = (var9 + 1);
			}
		}
	}
	k1 = structInput;
	ra = ((int *) sp)[3];
	structSize = ((int *) sp)[2];
	var11 = ((int *) sp)[1];
	var12 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3470
 */
void sub_03470 (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = s0;
	var1 = arg1;
	((int *) sp)[3] = ra;
	((int *) sp)[2] = s2;
	((int *) sp)[1] = s1;
	structInput = k1;
	k1 = k1 >> 0x10;
	var3 = var1;
	if (arg1 == 0x0500)
	{
		var18 = KDebugForKernel_DB846A2B ();
		var4 = 0xA038;
		if (!(var18 != 0))
		{
			var3 = var1;

		label7:
			var4 = 0xA018;
			if (!(((var3 & 0xFFFF00FF) | (0 & 0xFF)) == 0))
			{
				var4 = 0;
			}
		}
	}
	else
	goto label7;
	structID = 0x80111101;
	if (!(var4 == 0))
	{
		var8 = InitForKernel_23458221 ();
		structID = 0;
		if (!(var8 != 0))
		{
			var9 = ((int *) var4)[0];
			if (((var9 < 2)) != 0)
			{
				var15 = sub_03940 (var4);
				structID = var15;
			}
			else
			{
				structID = 0;
				((int *) var4)[0] = (var9 + 0xFFFFFFFF);
			}
		}
	}
	k1 = structInput;
	ra = ((int *) sp)[3];
	structSize = ((int *) sp)[2];
	var11 = ((int *) sp)[1];
	var12 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3530
 */
void sub_03530 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[2] = ra;
	((int *) sp)[1] = s1;
	var1 = 0xA018;
	((int *) sp)[0] = s0;
	structInput = 0;
	while (1) {
		structInput = structInput + 1;
		sub_03ABC (var1);
		var1 = var1 + 0x20;
		if (((structInput < 2)) != 0)
			continue;
		break;
	}
	ra = ((int *) sp)[2];
	structID = ((int *) sp)[1];
	ret = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x357C
 */
void sub_0357C (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = (arg1 & 0xFFFF00FF) | (0 & 0xFF);
	var3 = ((arg1 ^ 1) & 0xFFFF00FF) | (0 & 0xFF);
	var4 = 0;
	if (!(((structInput < 2)) == 0))
	{
		var4 = (structInput << 5) + 0xA070;
	}
	structID = 0x80111101;
	ret = 0;
	if (!(var4 == 0))
	{
		if (!(((var3 < 2)) == 0))
		{
			ret = (var3 << 5) + 0xA070;
		}
		var7 = ((int *) ret)[2];
		var8 = ((int *) var7)[2];
		structID = 0x80111102;
		if (var8 < 0)
		{
			var12 = sub_03760 (var4);
			structID = var12;
		}
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var9 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3620
 */
void sub_03620 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[2] = ra;
	((int *) sp)[1] = s1;
	var1 = 0xA070;
	((int *) sp)[0] = s0;
	structInput = 0;
	while (1) {
		structInput = structInput + 1;
		sub_03ABC (var1);
		var1 = var1 + 0x20;
		if (((structInput < 2)) != 0)
			continue;
		break;
	}
	ra = ((int *) sp)[2];
	structID = ((int *) sp)[1];
	ret = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x366C
 */
void sub_0366C (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	structInput = (arg1 & 0xFFFF00FF) | (0 & 0xFF);
	var3 = 0;
	if (!(((structInput < 2)) == 0))
	{
		var3 = (structInput << 5) + 0xA070;
	}
	var4 = 0x80111101;
	if (!(var3 == 0))
	{
		var7 = sub_03940 (var3);
		var4 = var7;
	}
	k1 = var1;
	ra = ((int *) sp)[1];
	var8 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x36D4
 */
void sub_036D4 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	sub_03ABC (0xA0BC);
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x36F8
 */
void sceUtility_private_A1A4A4D3 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	var4 = sub_03760 (0xA0BC);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x372C
 */
void sceUtility_private_6D73DD7C ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = k1;
	k1 = k1 >> 0x10;
	var4 = sub_03940 (0xA0BC);
	k1 = var1;
	ra = ((int *) sp)[1];
	structID = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3760
 */
int sub_03760 (int arg1)
{
	sp = sp + 0xFFFFFF90;
	((int *) sp)[23] = s3;
	var1 = arg1;
	((int *) sp)[24] = ra;
	((int *) sp)[22] = s2;
	((int *) sp)[21] = s1;
	((int *) sp)[20] = s0;
	structInput = ((int *) arg1)[0];
	var3 = 0x80111102;
	if (!(structInput != 0))
	{
		var4 = ((int *) var1)[1];
		structID = 0;
		if (var4 <= 0)
		{

		label10:
			var13 = ((int *) var1)[3];
			if (var13 <= 0)
			{

			label49:

			label50:
				var3 = 0;
				((int *) var1)[0] = 1;
			}
			else
			{
				var14 = ((int *) var1)[5];
				var17 = SysMemForKernel_5630F321 (2, "SceUtilityModule", 0, var14, 0);
				var11 = var17;
				if (var17 < 0)
				{

				label31:
					structSize = ((int *) var1)[1];
					ret0 = structSize + 0xFFFFFFFF;
					if (!(ret0 < 0))
					{
						ret1 = ((ret0 << 1) + ret0) << 2;
						while (1) {
							ret2 = ((int *) var1)[2];
							ret0 = ret0 + 0xFFFFFFFF;
							ret5 = sub_03DAC ((ret2 + ret1));
							ret1 = ret1 + 0xFFFFFFF4;
							if (ret0 >= 0)
								continue;
							break;
						}
					}
					var3 = var11;
				}
				else
				{
					var18 = ((int *) var1)[3];
					var19 = var17;
					structInput0 = 0;
					if (var18 <= 0)
					{
						structInput7 = ((int *) sp)[16];

					label38:
						((int *) var1)[6] = structInput7;
						var30 = sub_03FC0 ();
						if (!(var30 != 0))
							goto label49;
						var37 = sceKernelGetSystemTimeLow ();
						((int *) var1)[7] = var37;
						var38 = sp;
						var39 = ((int *) sp)[16];
						((int *) sp)[0] = 0x38;
						var42 = SysMemForKernel_BFC87793 (var39, var38);
						endOfStruct = ((int *) sp)[10];
						if (var42 < 0)
							goto label49;
						var44 = ((int *) var1)[7];
						structSize = ((int *) sp)[11];
						SysMemForKernel_8D34BBDA (endOfStruct, var44, structSize);
						goto label50;
					}
					else
					{
						while (1) {
							structInput1 = ((int *) var1)[4];
							graphicThreadPrio = sp + 0x40;
							((int *) sp)[16] = 0xFFFFFFFF;
							graphicThread = sub_03E44 ((structInput1 + (structInput0 << 4)), var19);
							structInput0 = structInput0 + 1;
							var11 = graphicThread;
							if (graphicThread < 0)
							{
								structSize = ((int *) var1)[3];
								structSize = structSize + 0xFFFFFFFF;
								structID0 = ((int *) sp)[16];
								if (!(structSize < 0))
								{
									structSize = ((int *) var1)[4];
									while (1) {
										structSize = structSize + 0xFFFFFFFF;
										screenHeight = sub_03F10 ((structSize + (structSize << 4)));
										if (!(structSize >= 0))
											break;
										structSize = ((int *) var1)[4];
										continue;
									}
									structID0 = ((int *) sp)[16];
								}
								if (!(structID0 < 0))
								{
									SysMemForKernel_AFBE8876 (structID0);
								}
								SysMemForKernel_AFBE8876 (var19);
								goto label31;
							}
							else
							{
								structInput6 = ((int *) var1)[3];
								var19 = ((int *) sp)[16];
								structInput7 = var19;
								if (((structInput0 < structInput6)) != 0)
									continue;
								break;
							}
							goto label51;
						}
						goto label38;
					}
				}
			}
		}
		else
		{
			ret = 0;
			var7 = ((int *) var1)[2];
			while (1) {
				structID = structID + 1;
				structSize = sub_03CC8 ((var7 + ret));
				var11 = structSize;
				ret = ret + 12;
				if (structSize < 0)
					break;
				var12 = ((int *) var1)[1];
				if (!(((structID < var12)) != 0))
					goto label10;
				var7 = ((int *) var1)[2];
				continue;
			}
			goto label31;
		}
	}
label51:
	return var3;
}

/**
 * Subroutine at address 0x3940
 */
int sub_03940 (int arg1)
{
	sp = sp + 0xFFFFFFA0;
	((int *) sp)[19] = s3;
	var1 = 0;
	((int *) sp)[18] = s2;
	structInput = 0x80111103;
	((int *) sp)[21] = ra;
	((int *) sp)[20] = s4;
	((int *) sp)[17] = s1;
	((int *) sp)[16] = s0;
	var3 = ((int *) arg1)[0];
	var4 = arg1;
	if (var3 == 0)
	{

	label38:
		ra = ((int *) sp)[21];
	}
	else
	{
		structID = ((int *) arg1)[3];
		ret = structID + 0xFFFFFFFF;
		if (ret < 0)
		{
			var11 = ((int *) var4)[6];
		}
		else
		{
			while (1) {
				var7 = ((int *) var4)[4];
				ret = ret + 0xFFFFFFFF;
				structSize = sub_03F10 ((var7 + (ret << 4)));
				var1 = structSize;
				if (ret >= 0)
					continue;
				break;
			}
			var11 = ((int *) var4)[6];
		}
		if (var11 < 0)
		{
			var18 = ((int *) var4)[1];
		}
		else
		{
			var14 = sub_03FC0 ();
			if (var14 != 0)
			{
				structSize = ((int *) var4)[6];
				var33 = sp;
				((int *) sp)[0] = 0x38;
				var36 = SysMemForKernel_BFC87793 (structSize, var33);
				var37 = 0;
				var38 = ((int *) sp)[11];
				var39 = ((int *) sp)[10];
				if (!((var38 >> 2) == 0))
				{
					while (1) {
						var40 = ((int *) var39)[0];
						structSize = ((int *) var4)[7];
						if (!(var40 == structSize))
						{
							Kprintf ("utility_module reserved memory has been violated 0x%p ... stop\n", var39);
							__asm__ ("break;");
							var38 = ((int *) sp)[11];
						}
						var37 = var37 + 1;
						var39 = var39 + 4;
						if (((var37 < (var38 >> 2))) != 0)
							continue;
						break;
					}
				}
			}
			var15 = ((int *) var4)[6];
			SysMemForKernel_AFBE8876 (var15);
			((int *) var4)[6] = 0xFFFFFFFF;
			var18 = ((int *) var4)[1];
		}
		var19 = var18 + 0xFFFFFFFF;
		if (!(var19 < 0))
		{
			structInput0 = ((var19 << 1) + var19) << 2;
			while (1) {
				structInput1 = ((int *) var4)[2];
				var19 = var19 + 0xFFFFFFFF;
				structInput4 = sub_03DAC ((structInput1 + structInput0));
				var1 = structInput4;
				structInput0 = structInput0 + 0xFFFFFFF4;
				if (var19 >= 0)
					continue;
				break;
			}
		}
		if (var1 < 0)
		{
			var30 = ((int *) var4)[3];
			var31 = ((int *) var4)[1];
			structInput = var1;
			if ((var30 + var31) != 1)
			{

			label37:
				((int *) var4)[0] = 0;
				structInput = 0;
				goto label38;
			}
			else
			{
				ra = ((int *) sp)[21];
			}
		}
		else
		goto label37;
	}
	graphicThread = ((int *) sp)[20];
	structInput6 = ((int *) sp)[19];
	structInput7 = ((int *) sp)[18];
	structInput8 = ((int *) sp)[17];
	structInput9 = ((int *) sp)[16];
	sp = sp + 0x60;
	return structInput;
}

/**
 * Subroutine at address 0x3ABC
 */
void sub_03ABC (int arg1)
{
	var1 = ((int *) arg1)[1];
	((int *) arg1)[6] = 0xFFFFFFFF;
	structInput = 0;
	((int *) arg1)[0] = 0;
	if (!(var1 <= 0))
	{
		var3 = ((int *) arg1)[2];
		var4 = var3 + 8;
		while (1) {
			((int *) var4)[0] = 0xFFFFFFFF;
			structInput = structInput + 1;
			structID = ((int *) arg1)[1];
			var4 = var4 + 12;
			if (((structInput < structID)) != 0)
				continue;
			break;
		}
	}
	ret = ((int *) arg1)[3];
	var7 = 0;
	if (!(ret <= 0))
	{
		var8 = ((int *) arg1)[4];
		while (1) {
			((int *) var8)[2] = 0xFFFFFFFF;
			var7 = var7 + 1;
			((int *) var8)[3] = 0xFFFFFFFF;
			var9 = ((int *) arg1)[3];
			var8 = var8 + 0x10;
			if (((var7 < var9)) != 0)
				continue;
			break;
		}
	}
	return;
}

/**
 * Subroutine at address 0x3B30
 */
void sceUtilityLoadModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	var1 = arg1 & 0xFF00;
	((int *) sp)[0] = ra;
	if (var1 == 0x0300)
	{
		var15 = sub_030A8 (arg1);
		ra = ((int *) sp)[0];
	}
	else
	{
		if (((var1 < 0x0301)) == 0)
		{
			if (var1 == 0x0500)
			{
				sub_033B8 (arg1);
				ra = ((int *) sp)[0];
			}
			else
			{
				if (((var1 < 0x0501)) == 0)
				{
					if (var1 != 0x0600)
					{

					label31:
						ra = ((int *) sp)[0];
					}
					else
					{
						sub_0357C (arg1);
						ra = ((int *) sp)[0];
					}
				}
				else
				{
					if (var1 != 0x0400)
					{
						goto label31;
					}
					else
					{
						sub_032E8 (arg1);
						ra = ((int *) sp)[0];
					}
				}
			}
		}
		else
		{
			if (var1 == 0x0100)
			{
				ret = sub_026EC (arg1);
				ra = ((int *) sp)[0];
			}
			else
			{
				if (var1 == 0x0200)
				{
					sub_02C1C (arg1);
					ra = ((int *) sp)[0];
				}
				else
				{
					goto label31;
				}
			}
		}
	}
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3BFC
 */
void sceUtilityUnloadModule (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	var1 = arg1 & 0xFF00;
	((int *) sp)[0] = ra;
	if (var1 == 0x0300)
	{
		var15 = sub_03134 (arg1);
		ra = ((int *) sp)[0];
	}
	else
	{
		if (((var1 < 0x0301)) == 0)
		{
			if (var1 == 0x0500)
			{
				sub_03470 (arg1);
				ra = ((int *) sp)[0];
			}
			else
			{
				if (((var1 < 0x0501)) == 0)
				{
					if (var1 != 0x0600)
					{

					label31:
						ra = ((int *) sp)[0];
					}
					else
					{
						sub_0366C (arg1);
						ra = ((int *) sp)[0];
					}
				}
				else
				{
					if (var1 != 0x0400)
					{
						goto label31;
					}
					else
					{
						sub_03350 (arg1);
						ra = ((int *) sp)[0];
					}
				}
			}
		}
		else
		{
			if (var1 == 0x0100)
			{
				ret = sub_02854 (arg1);
				ra = ((int *) sp)[0];
			}
			else
			{
				if (var1 == 0x0200)
				{
					sub_02CF4 (arg1);
					ra = ((int *) sp)[0];
				}
				else
				{
					goto label31;
				}
			}
		}
	}
	sp = sp + 0x10;
	return;
}

/**
 * Subroutine at address 0x3CC8
 */
int sub_03CC8 (int arg1)
{
	sp = sp + 0xFFFFFFB0;
	((int *) sp)[16] = s4;
	var1 = 0;
	((int *) sp)[15] = s3;
	structInput = 0;
	((int *) sp)[14] = s2;
	var3 = arg1;
	((int *) sp)[17] = ra;
	((int *) sp)[13] = s1;
	((int *) sp)[12] = s0;
	var4 = ((int *) arg1)[1];
	((int *) sp)[0] = 0x14;
	((int *) sp)[1] = 0;
	((int *) sp)[2] = 0;
	((int *) sp)[3] = 0;
	((int *) sp)[4] = 0;
	if (var4 == 0)
	{
		((int *) sp)[1] = 1;
	}
	else
	{
		structID = ((int *) var4)[0];
		var1 = ((int *) var4)[2];
		((int *) sp)[1] = structID;
		structInput = ((int *) var4)[1];
	}
	ret = ((int *) var3)[0];
	var7 = sp;
	structSize = sceKernelLoadModule (ret, 0, var7);
	var11 = structSize;
	var12 = sp + 0x20;
	if (!(structSize < 0))
	{
		var15 = ModuleMgrForKernel_BB8C8FDF (structSize, structInput, var1, var12, 0);
		PrxToLoad = var15;
		if (var15 <= 0)
		{
			structInput4 = ModuleMgrForKernel_2AFF3E70 (var11);
			structSize = (PrxToLoad) ? PrxToLoad : 0x80111104;
		}
		else
		{
			((int *) var3)[2] = var11;
			structSize = 0;
		}
	}
	ra = ((int *) sp)[17];
	var17 = ((int *) sp)[16];
	var18 = ((int *) sp)[15];
	var19 = ((int *) sp)[14];
	structInput0 = ((int *) sp)[13];
	structInput1 = ((int *) sp)[12];
	sp = sp + 0x50;
	return structSize;
}

/**
 * Subroutine at address 0x3DAC
 */
int sub_03DAC (int arg1)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[4] = s0;
	var1 = arg1;
	((int *) sp)[5] = ra;
	structInput = sp;
	var3 = ((int *) arg1)[2];
	if (var3 < 0)
	{

	label13:
		((int *) var1)[2] = 0xFFFFFFFF;
		var11 = 0;
	}
	else
	{
		ret = ModuleMgrForKernel_E0D3F771 (var3, 0, 0, structInput, 0);
		if (ret < 0)
		{
			if (ret != 0x8002012E)
			{

			label11:
				var7 = ((int *) var1)[2];
				structSize = ModuleMgrForKernel_2AFF3E70 (var7);
				goto label13;
			}
			else
			{
				var15 = SysMemForKernel_2CFF6F90 ();
				var11 = 0x8002012E;
				if (!(((0x307FFFF < var15)) != 0))
				{
					goto label11;
				}
			}
		}
		else
		goto label11;
	}
	ra = ((int *) sp)[5];
	var12 = ((int *) sp)[4];
	sp = sp + 0x20;
	return var11;
}

/**
 * Subroutine at address 0x3E44
 */
int sub_03E44 (int arg1, int arg2)
{
	sp = sp + 0xFFFFFFD0;
	((int *) sp)[9] = s5;
	var1 = 0;
	((int *) sp)[8] = s4;
	((int *) sp)[7] = s3;
	structInput = 0;
	((int *) sp)[6] = s2;
	((int *) sp)[10] = ra;
	((int *) sp)[5] = s1;
	((int *) sp)[4] = s0;
	var3 = ((int *) arg1)[1];
	var4 = arg1;
	if (!(var3 == 0))
	{
		structID = ((int *) var3)[3];
		var1 = ((int *) var3)[1];
		structInput = ((int *) var3)[2];
	}
	ret = ((int *) var4)[0];
	var9 = ModuleMgrForKernel_31757B4D (ret, arg2, arg3, 0, structID);
	structSize = var9;
	var11 = sp;
	if (!(var9 < 0))
	{
		var14 = ModuleMgrForKernel_BB8C8FDF (var9, var1, structInput, var11, 0);
		var15 = var14;
		if (var14 <= 0)
		{
			structInput4 = ModuleMgrForKernel_2AFF3E70 (structSize);
			var9 = (var15) ? var15 : 0x80111104;
		}
		else
		{
			((int *) var4)[3] = arg2;
			var9 = 0;
			((int *) var4)[2] = structSize;
		}
	}
	ra = ((int *) sp)[10];
	PrxToLoad = ((int *) sp)[9];
	var17 = ((int *) sp)[8];
	var18 = ((int *) sp)[7];
	var19 = ((int *) sp)[6];
	structInput0 = ((int *) sp)[5];
	structInput1 = ((int *) sp)[4];
	sp = sp + 0x30;
	return var9;
}

/**
 * Subroutine at address 0x3F10
 */
int sub_03F10 (int arg1)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[4] = s0;
	var1 = arg1;
	((int *) sp)[5] = ra;
	structInput = sp;
	var3 = ((int *) arg1)[2];
	if (var3 < 0)
	{

	label13:
		var11 = ((int *) var1)[3];
		if (!(var11 < 0))
		{
			SysMemForKernel_AFBE8876 (var11);
		}
		((int *) var1)[3] = 0xFFFFFFFF;
		var14 = 0;
		((int *) var1)[2] = 0xFFFFFFFF;
	}
	else
	{
		ret = ModuleMgrForKernel_E0D3F771 (var3, 0, 0, structInput, 0);
		if (ret == 0)
		{

		label11:
			var7 = ((int *) var1)[2];
			structSize = ModuleMgrForKernel_2AFF3E70 (var7);
			goto label13;
		}
		else
		{
			if (!(ret == 0x8002012E))
				goto label11;
			var18 = SysMemForKernel_2CFF6F90 ();
			var14 = 0x8002012E;
			if (!(((0x307FFFF < var18)) != 0))
			{
				goto label11;
			}
		}
	}
	ra = ((int *) sp)[5];
	var15 = ((int *) sp)[4];
	sp = sp + 0x20;
	return var14;
}

/**
 * Subroutine at address 0x3FC0
 */
int sub_03FC0 ()
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[0] = ra;
	var3 = KDebugForKernel_DB846A2B ();
	var4 = 0;
	if (var3 != 0)
	{
		var7 = KDebugForKernel_619A2D25 ();
		if (var7 == 0)
		{
			PrxToLoad = KDebugForKernel_CB91D8EA (0x18);
			var4 = 0;
			if (!(PrxToLoad == 0))
			{

			label15:
				var13 = SysMemForKernel_2CFF6F90 ();
				var4 = (0x306FFFF < var13);
			}
		}
		else
		{
			structSize = KDebugForKernel_CB91D8EA (0x19);
			var4 = 0;
			if (!(structSize != 0))
				goto label15;
		}
	}
	ra = ((int *) sp)[0];
	sp = sp + 0x10;
	return var4;
}

/**
 * Subroutine at address 0x4038
 */
void sceUtilityGameSharingInitStart (int arg1){
	initStart (3, arg1);
}
void sceUtilityGameSharingShutdownStart (){
	shutdownStart (3);
}
void sceUtilityGameSharingUpdate (int arg1){
	update (3, arg1);
}
void sceUtilityGameSharingGetStatus (){
	getStatus (3);
}
void sceUtilityNetconfInitStart (int arg1){
	initStart (4, arg1);
}
void sceUtilityNetconfShutdownStart (){
	shutdownStart (4);
}
void sceUtilityNetconfUpdate (int arg1){
	update (4, arg1);
}
void sceUtilityNetconfGetStatus (){
	getStatus (4);
}
void sceUtilitySavedataInitStart (int arg1){
	initStart (1, arg1);
}
void sceUtilitySavedataShutdownStart (){
	shutdownStart (1);
}
void sceUtilitySavedataUpdate (int arg1){
	update (1, arg1);
}
void sceUtilitySavedataGetStatus (){
	getStatus (1);
}
void sceUtilityMsgDialogInitStart (int arg1){
	initStart (5, arg1);
}
void sceUtilityMsgDialogShutdownStart (){
	shutdownStart (5);
}
void sceUtilityMsgDialogUpdate (int arg1){
	update (5, arg1);
}
void sceUtilityMsgDialogGetStatus (){
	getStatus (5);
}
void sceUtilityMsgDialogAbort (){
	if (CurrentType != 5)return 0x80110005;
	if (Status != 2)return 0x80110001;
	IsBusy = 1;
}
void sceUtilityOskInitStart (int arg1){
	return initStart (6, arg1);
}
void sceUtilityOskShutdownStart (){
	return shutdownStart (6);
}
void sceUtilityOskUpdate (int arg1){
	return update (6, arg1);
}
void sceUtilityOskGetStatus (){
	return getStatus (6);
}
void sceUtilityDNASInitStart (int arg1){
	return initStart (7, arg1);
}
void sceUtilityDNASShutdownStart (){
	return shutdownStart (7);
}
void sceUtilityDNASUpdate (int arg1){
	return update (7, arg1);
}
void sceUtilityDNASGetStatus (){
	return getStatus (7);
}
void sceUtilityAuthDialogInitStart (int arg1){
	return initStart (8, arg1);
}
void sceUtilityAuthDialogShutdownStart (){
	return shutdownStart (8);
}
void sceUtilityAuthDialogUpdate (int arg1){
	return update (8, arg1);
}
void sceUtilityAuthDialogGetStatus (){
	return getStatus (8);
}
void sceUtilityInstallInitStart (int arg1){
	return initStart (9, arg1);
}
void sceUtilityInstallShutdownStart (){
	return shutdownStart (9);
}
void sceUtilityInstallUpdate (int arg1){
	return update (9, arg1);
}
void sceUtilityInstallGetStatus (){
	return getStatus (9);
}
void sceUtility_private_1FD567D4 (int arg1){
	return initStart (10, arg1);
}
void sceUtility_private_4B069019 (){
	return shutdownStart (10);
}
void sceUtility_private_DCCC4CE2 (int arg1){
	return update (10, arg1);
}
void sceUtility_private_8A80D4EE (){
	return getStatus (10);
}
void sceUtilityScreenshotInitStart (int arg1){
	return initStart (11, arg1);
}
void sceUtilityScreenshotShutdownStart (){
	return shutdownStart (11);
}
void sceUtilityScreenshotUpdate (int arg1){
	return update (11, arg1);
}
void sceUtilityScreenshotGetStatus (){
	return getStatus (11);
}
void sceUtilityNpSigninInitStart (int arg1){
	return initStart (12, arg1);
}
void sceUtilityNpSigninShutdownStart (){
	return shutdownStart (12);
}
void sceUtilityNpSigninUpdate (int arg1){
	return update (12, arg1);
}
void sceUtilityNpSigninGetStatus (){
	return getStatus (12);
}
void sceUtilityPS3ScanInitStart (int arg1){
	return initStart (13, arg1);
}
void sceUtilityPS3ScanShutdownStart (){
	return shutdownStart (13);
}
void sceUtilityPS3ScanUpdate (int arg1){
	return update (13, arg1);
}
void sceUtilityPS3ScanGetStatus (){
	return getStatus (13);
}
void sceUtilityRssSubscriberInitStart (int arg1){
	return initStart (14, arg1);
}
void sceUtilityRssSubscriberShutdownStart (){
	return shutdownStart (14);
}
void sceUtilityRssSubscriberUpdate (int arg1){
	return update (14, arg1);
}
void sceUtilityRssSubscriberGetStatus (){
	return getStatus (14);
}
void sceUtilityRssReaderInitStart (int arg1){
	return initStart (15, arg1);
}
void sceUtilityRssReaderShutdownStart (){
	return shutdownStart (15);
}
void sceUtilityRssReaderUpdate (int arg1){
	return update (15, arg1);
}
void sceUtilityRssReaderGetStatus (){
	return getStatus (15);
}
void sceUtilityStoreCheckoutInitStart (int arg1){
	return initStart (0x10, arg1);
}
void sceUtilityStoreCheckoutShutdownStart (){
	return shutdownStart (0x10);
}
void sceUtilityStoreCheckoutUpdate (int arg1){
	return update (0x10, arg1);
}
void sceUtilityStoreCheckoutGetStatus (){
	return getStatus (0x10);
}
void sceUtilityRssReaderContStart (int arg1){
	return contStart (15, arg1);
}
void sceUtilityScreenshotContStart (int arg1){
	return contStart (11, arg1);
}
void sceUtilityHtmlViewerInitStart (int arg1){
	return HVInitStart (1, arg1);
}
void sceUtilityHtmlViewerShutdownStart (){
	return HVInitShutdown (1);
}
void sceUtilityHtmlViewerUpdate (int arg1){
	return HVInitUpdate (1, arg1);
}
void sceUtilityHtmlViewerGetStatus (){
	return HVInitGetStatus (1);
}
void sceNetplayDialogInitStart (){
	return;
}
void sceNetplayDialogShutdownStart (){
	return;
}
void sceNetplayDialogUpdate (){
	return;
}
void sceNetplayDialogGetStatus (){
	return;
}
void sceUtility_2995D020 (){
	return;
}
void sceUtility_B62A4061 (){
	return;
}
void sceUtility_ED0FAD38 (){
	return;
}
void sceUtility_88BC7406 (){
	return;
}
void sceUtilitySetSystemParamInt (int id, int value){
	if (id == 2){
		if (value == 6)
			sub_0525C ("/CONFIG/NETWORK/ADHOC","channel",value);
		else{
			if (value>=7){
				if (value != 11)
					label11:
				else
					goto label13;
			}else{
				if (value>=2)
					goto label11;
				else
					goto label13;
			}
		}
	}
	if (id == 3)
		sub_0525C ("/CONFIG/SYSTEM/POWER_SAVING","wlan_mode",(value>1) ? 1 : value);
}
void sceUtilityGetSystemParamInt (int id, int value){
	if (id > 9)return;
	switch (((int *) ((id << 2) + 0x954C))[0]) {
		case 0:return;
		case 1:return;
		case 2:return sub_04F54 ("/CONFIG/NETWORK/ADHOC", "channel", value);
		case 3:return sub_04F54 ("/CONFIG/SYSTEM/POWER_SAVING", "wlan_mode", value);
		case 4:return sub_04F54 ("/CONFIG/DATE", "date_format", value);
		case 5:return sub_04F54 ("/CONFIG/DATE", "time_format", value);
		case 6:return sub_04F54 ("/CONFIG/DATE", "time_zone_offset", value);
		case 7:return sub_04F54 ("/CONFIG/DATE", "summer_time", value);
		case 8:return sub_04F54 ("/CONFIG/SYSTEM/XMB", "language", value);
		case 9:return sub_04F54 ("/CONFIG/SYSTEM/XMB", "button_assign", value);
	}
}	
void sub_04F54 (char* arg1, char* arg2, int arg3){
	var9 = sceReg_driver_7CA7768A (sp, 2, sp + 0x110);
	structSize = var9;
	if (var9 == 0)
	{
		var17 = ((int *) sp)[68];
		var18 = sp + 0x0114;
		structInput1 = sceReg_driver_6A37E343 (var17, arg1, 2, var18);
		graphicThreadPrio = structInput1;
		if (structInput1 != 0)
		{

		label41:
			structSize = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (structSize);
		}
		else
		{
			structInput3 = ((int *) sp)[69];
			structInput4 = sp + 0x0118;
			graphicThread = sp + 0x011C;
			structInput6 = sp + 0x0120;
			structInput9 = sceReg_driver_821E99EC (structInput3, arg2, structInput4, graphicThread, structInput6);
			graphicThreadPrio = structInput9;
			if (structInput9 != 0)
			{

			label39:
				var38 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var38);
				goto label41;
			}
			else
			{
				var30 = ((int *) sp)[71];
				var31 = ((int *) sp)[72];
				if (var30 != 2)
				{
					ret2 = ((int *) sp)[69];
					sceReg_driver_C2E5E478 (ret2);
					ret5 = ((int *) sp)[68];
					sceReg_driver_EFE7BE31 (ret5);
				}
				else
				{
					if (var31 != 4)
					{
						resolution = ((int *) sp)[69];
						sceReg_driver_C2E5E478 (resolution);
						structSize = ((int *) sp)[68];
						sceReg_driver_EFE7BE31 (structSize);
					}
					else
					{
						structSize = k1 & 0x18;
						var33 = ((int *) sp)[69];
						if ((((arg3 + 4) | arg3) & (0 - structSize)) < 0)
						{
							structID0 = ((int *) sp)[69];
							sceReg_driver_C2E5E478 (structID0);
							screenWidth = ((int *) sp)[68];
							sceReg_driver_EFE7BE31 (screenWidth);
						}
						else
						{
							endOfStruct = ((int *) sp)[70];
							var37 = sceReg_driver_D905CBF9 (var33, endOfStruct, arg3, 4);
							graphicThreadPrio = var37;
							if (!(var37 == 0))
								goto label39;
							var44 = ((int *) sp)[69];
							sceReg_driver_C2E5E478 (var44);
							structSize = ((int *) sp)[68];
							sceReg_driver_EFE7BE31 (structSize);
						}
					}
				}
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", structSize);
	}
	ra = ((int *) sp)[80];
	var13 = ((int *) sp)[79];
	var14 = ((int *) sp)[78];
	var15 = ((int *) sp)[77];
	PrxToLoad = ((int *) sp)[76];
	sp = sp + 0x0150;
	return;
}
void sub_050F0 (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFEB0;
	((int *) sp)[79] = s3;
	((int *) sp)[78] = s2;
	var1 = arg3;
	((int *) sp)[77] = s1;
	structInput = sp;
	((int *) sp)[80] = ra;
	((int *) sp)[76] = s0;
	memset (structInput, 0, 0x0110);
	structID = sp;
	ret = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	var9 = sceReg_driver_7CA7768A (structID, 2, ret);
	structSize = var9;
	if (var9 == 0)
	{
		var17 = ((int *) sp)[68];
		var18 = sp + 0x0114;
		structInput1 = sceReg_driver_6A37E343 (var17, arg1, 2, var18);
		graphicThreadPrio = structInput1;
		if (structInput1 != 0)
		{

		label31:
			structSize = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (structSize);
		}
		else
		{
			structInput3 = ((int *) sp)[69];
			structInput4 = sp + 0x0118;
			graphicThread = sp + 0x011C;
			structInput6 = sp + 0x0120;
			structInput9 = sceReg_driver_821E99EC (structInput3, arg2, structInput4, graphicThread, structInput6);
			graphicThreadPrio = structInput9;
			if (structInput9 != 0)
			{

			label29:
				var38 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var38);
				goto label31;
			}
			else
			{
				var30 = ((int *) sp)[71];
				var31 = ((int *) sp)[72];
				if (var30 != 2)
				{

				label15:
					structID0 = ((int *) sp)[69];
					sceReg_driver_C2E5E478 (structID0);
					screenWidth = ((int *) sp)[68];
					sceReg_driver_EFE7BE31 (screenWidth);
				}
				else
				{
					if (var31 != 4)
						goto label15;
					structSize = k1 & 0x18;
					if (!((((var1 + 4) | var1) & (0 - structSize)) < 0))
					{
						var33 = ((int *) sp)[69];
						endOfStruct = ((int *) sp)[70];
						var37 = sceReg_driver_D905CBF9 (var33, endOfStruct, var1, 4);
						graphicThreadPrio = var37;
						if (!(var37 == 0))
							goto label29;
						var44 = ((int *) sp)[69];
						sceReg_driver_C2E5E478 (var44);
						structSize = ((int *) sp)[68];
						sceReg_driver_EFE7BE31 (structSize);
					}
				}
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", structSize);
	}
	ra = ((int *) sp)[80];
	var13 = ((int *) sp)[79];
	var14 = ((int *) sp)[78];
	var15 = ((int *) sp)[77];
	PrxToLoad = ((int *) sp)[76];
	sp = sp + 0x0150;
	return;
}
void sub_0525C (int arg1, char* arg2, int arg3){
	sp = sp + 0xFFFFFED0;
	((int *) sp)[74] = s2;
	((int *) sp)[72] = s0;
	var1 = sp;
	((int *) sp)[70] = arg3;
	((int *) sp)[75] = ra;
	((int *) sp)[73] = s1;
	memset (var1, 0, 0x0110);
	var4 = sp;
	structID = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	var8 = sceReg_driver_7CA7768A (var4, 2, structID);
	var9 = var8;
	structSize = sp + 0x0114;
	if (var9 == 0)
	{
		PrxToLoad = ((int *) sp)[68];
		var19 = sceReg_driver_6A37E343 (PrxToLoad, arg1, 2, structSize);
		structInput0 = var19;
		structInput1 = sp + 0x0118;
		if (var19 != 0)
		{

		label24:
			structInput9 = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (structInput9);
		}
		else
		{
			graphicThreadPrio = ((int *) sp)[69];
			graphicThread = sceReg_driver_43CF36BC (graphicThreadPrio, arg2, structInput1, 4);
			structInput0 = graphicThread;
			if (graphicThread == 0)
			{
				structSize = ((int *) sp)[69];
				sceReg_driver_FED2B205 (structSize);
				var35 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var35);
				var38 = ((int *) sp)[68];
				sceReg_driver_BC2ECC38 (var38);
				structSize = ((int *) sp)[68];
				sceReg_driver_EFE7BE31 (structSize);
			}
			else
			{
				structInput6 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (structInput6);
				goto label24;
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", var9);
	}
	ra = ((int *) sp)[75];
	var13 = ((int *) sp)[74];
	var14 = ((int *) sp)[73];
	var15 = ((int *) sp)[72];
	sp = sp + 0x0130;
	return;
}
void sub_05358 (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFED0;
	((int *) sp)[74] = s2;
	((int *) sp)[72] = s0;
	var1 = sp;
	((int *) sp)[70] = arg3;
	((int *) sp)[75] = ra;
	((int *) sp)[73] = s1;
	memset (var1, 0, 0x0110);
	var4 = sp;
	structID = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	var8 = sceReg_driver_7CA7768A (var4, 2, structID);
	var9 = var8;
	structSize = sp + 0x0114;
	if (var9 == 0)
	{
		PrxToLoad = ((int *) sp)[68];
		var19 = sceReg_driver_6A37E343 (PrxToLoad, arg1, 2, structSize);
		structInput0 = var19;
		structInput1 = sp + 0x0118;
		if (var19 != 0)
		{

		label24:
			structInput9 = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (structInput9);
		}
		else
		{
			graphicThreadPrio = ((int *) sp)[69];
			graphicThread = sceReg_driver_43CF36BC (graphicThreadPrio, arg2, structInput1, 4);
			structInput0 = graphicThread;
			if (graphicThread == 0)
			{
				structSize = ((int *) sp)[69];
				sceReg_driver_FED2B205 (structSize);
				var35 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var35);
				var38 = ((int *) sp)[68];
				sceReg_driver_BC2ECC38 (var38);
				structSize = ((int *) sp)[68];
				sceReg_driver_EFE7BE31 (structSize);
			}
			else
			{
				structInput6 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (structInput6);
				goto label24;
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", var9);
	}
	ra = ((int *) sp)[75];
	var13 = ((int *) sp)[74];
	var14 = ((int *) sp)[73];
	var15 = ((int *) sp)[72];
	sp = sp + 0x0130;
	return;
}
void sceUtilitySetSystemParamString (){
	return;
}
void sceUtilityGetSystemParamString (int arg1, int arg2, int arg3){
	if (arg1 == 1)
		return sub_054D8 ("/CONFIG/SYSTEM", "owner_name", arg2, arg3);
	return 0x80110103
}
int sub_054D8 (int arg1, int arg2, int arg3, int arg4){
	var1 = arg3;
	var3 = arg4;
	memset (sp, 0, 0x0110);
	var7 = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	ret = sceReg_driver_7CA7768A (sp, 2, var7);
	if (ret)return ret;
	structInput4 = sceReg_driver_6A37E343 (((int *) sp)[68], arg1, 2, sp + 0x0114);
	graphicThread = structInput4;
	if (structInput4 != 0){
	label36:
		sceReg_driver_EFE7BE31 (((int *) sp)[68]);
		var14 = graphicThread;
	}else{
		structInput6 = ((int *) sp)[69];
		structInput7 = sp + 0x0118;
		structInput8 = sp + 0x011C;
		structInput9 = sp + 0x0120;
		structSize = sceReg_driver_821E99EC (structInput6, arg2, structInput7, structInput8, structInput9);
		graphicThread = structSize;
		if (structSize != 0)
		{

		label34:
			structID2 = ((int *) sp)[69];
			sceReg_driver_C2E5E478 (structID2);
			goto label36;
		}
		else
		{
			var33 = ((int *) sp)[71];
			endOfStruct = ((int *) sp)[72];
			if (var33 != 3)
			{
				var70 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var70);
				var73 = ((int *) sp)[68];
				sceReg_driver_EFE7BE31 (var73);
				var14 = 0x80110101;
			}
			else
			{
				if (((var3 < endOfStruct)) != 0){
					sceReg_driver_C2E5E478 (((int *) sp)[69]);
					sceReg_driver_EFE7BE31 (((int *) sp)[68]);
					var14 = 0x80110102;
				}
				else
				{
					var35 = k1 & 0x18;
					var36 = ((int *) sp)[69];
					if (((0 - var35) & (((var1 + var3) | var1) | var3)) < 0){
						sceReg_driver_C2E5E478 (((int *) sp)[69]);
						ret1 = ((int *) sp)[68];
						sceReg_driver_EFE7BE31 (ret1);
						var14 = 0x80110002;
					}
					else
					{
						var37 = ((int *) sp)[70];
						var40 = sceReg_driver_D905CBF9 (var36, var37, var1, var3);
						graphicThread = var40;
						if (var40 != 0)
							goto label34;
						structSize = ((int *) sp)[72];
						var42 = ((char *) (var1 + structSize))[-1];
						if (var42 != 0)
						{
							Kprintf ("registry entry is not terminated correctly.\n");
							structSize = ((int *) sp)[72];
							((char *) (var1 + structSize))[-1] = 0;
						}
						endOfStruct = ((int *) sp)[69];
						sceReg_driver_C2E5E478 (endOfStruct);
						structSize = ((int *) sp)[68];
						sceReg_driver_EFE7BE31 (structSize);
						var14 = 0;
					}
				}
			}
		}
	}
}
void sub_056B0 (int arg1, int arg2, int arg3, int arg4){
	sp = sp + 0xFFFFFEB0;
	((int *) sp)[79] = s3;
	var1 = arg3;
	((int *) sp)[78] = s2;
	((int *) sp)[77] = s1;
	structInput = sp;
	((int *) sp)[81] = ra;
	((int *) sp)[80] = s4;
	var3 = arg4;
	((int *) sp)[76] = s0;
	memset (structInput, 0, 0x0110);
	ret = sp;
	var7 = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	structSize = sceReg_driver_7CA7768A (ret, 2, var7);
	var11 = structSize;
	if (structSize == 0)
	{
		var19 = ((int *) sp)[68];
		structInput0 = sp + 0x0114;
		structInput3 = sceReg_driver_6A37E343 (var19, arg1, 2, structInput0);
		structInput4 = structInput3;
		if (structInput3 != 0)
		{

		label25:
			screenWidth = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (screenWidth);
		}
		else
		{
			graphicThread = ((int *) sp)[69];
			structInput6 = sp + 0x0118;
			structInput7 = sp + 0x011C;
			structInput8 = sp + 0x0120;
			var31 = sceReg_driver_821E99EC (graphicThread, arg2, structInput6, structInput7, structInput8);
			structInput4 = var31;
			if (var31 != 0)
			{

			label23:
				structID0 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (structID0);
				goto label25;
			}
			else
			{
				structSize = ((int *) sp)[71];
				var33 = ((int *) sp)[72];
				if (structSize != 3)
				{

				label15:
					resolution = ((int *) sp)[69];
					sceReg_driver_C2E5E478 (resolution);
					structSize = ((int *) sp)[68];
					sceReg_driver_EFE7BE31 (structSize);
				}
				else
				{
					endOfStruct = ((int *) sp)[69];
					if (((var3 < var33)) != 0)
						goto label15;
					var35 = ((int *) sp)[70];
					var38 = sceReg_driver_D905CBF9 (endOfStruct, var35, var1, var3);
					structInput4 = var38;
					if (var38 != 0)
						goto label23;
					var39 = ((int *) sp)[72];
					var40 = ((char *) (var1 + var39))[-1];
					if (var40 != 0)
					{
						Kprintf ("registry entry is not terminated correctly.\n");
						structSize = ((int *) sp)[72];
						((char *) (var1 + structSize))[-1] = 0;
					}
					structSize = ((int *) sp)[69];
					sceReg_driver_C2E5E478 (structSize);
					var44 = ((int *) sp)[68];
					sceReg_driver_EFE7BE31 (var44);
				}
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", var11);
	}
	ra = ((int *) sp)[81];
	var14 = ((int *) sp)[80];
	var15 = ((int *) sp)[79];
	PrxToLoad = ((int *) sp)[78];
	var17 = ((int *) sp)[77];
	var18 = ((int *) sp)[76];
	sp = sp + 0x0150;
	return;
}
void sceUtilityCheckNetParam (int arg1){
	if (arg1<0)return 0x80110602;
	result = sceKernelExtendKernelStack (0x1000, 0x5F0C, var3);
	return (result >= 0) ? 0 : result;
}
void sceUtility_netparam_internal_F547B8FC (int arg1){
	if (arg1<0)return 0x80110602;
	result = sceKernelExtendKernelStack (0x1000, 0x5F74, arg1);
	return (result<0) ? 0 : result;
}
void sceUtility_netparam_internal_0BA36F3F (int arg1){
	if (arg1<0)return 0x80110602;
	result = sceKernelExtendKernelStack (0x1000, 0x5FCC, arg1);
	return (result<0) ? 0 : result;
}
void sceUtility_netparam_internal_BEE92A0A (int arg1, int arg2){
	if ((arg2 | arg1) < 0)return 0x80110602;
	((int *) sp)[0] = arg1;
	((int *) sp)[1] = arg2;
	((int *) sp)[2] = 0;
	var8 = sceKernelExtendKernelStack (0x1000, 0x6024, sp);
	return (((var8 < 0))) ? var8 : ((int *) sp)[2];
}
void sceUtilityGetNetParam (int arg1, int arg2, int arg3){
	if (arg1<0)return 0x80110602;
	if (!arg3)return 0x80110603;
	if ((((arg3+0x80) | arg3) & (0 - k1&0x18)) < 0)return 0x80110002
	if (arg2>=0x1D)return 0x80110604;
	if ((arg2 + 0xFFFFFFE7)>=4)return 0x80110604;

	((int *) sp)[0] = arg1;
	((int *) sp)[1] = arg2;
	((int *) sp)[3] = arg3;
	((int *) sp)[2] = 0x80;
	((int *) sp)[4] = 0;
	res = sceKernelExtendKernelStack (0x1000, 0x60E4, sp);
	return (res<0) ? 0 : res;
}
void sceUtility_netparam_internal_FD539533 (int arg1, int arg2, int arg3){
	sp = sp + 0xFFFFFFD0;
	((int *) sp)[9] = ra;
	var1 = arg2;
	((int *) sp)[8] = s0;
	structInput = arg3;
	var3 = k1;
	k1 = k1 >> 0x10;
	var4 = 0x80110602;
	if (!(arg1 < 0))
	{
		var4 = 0x80110603;
		if (!(arg3 == 0))
		{
			structID = k1 & 0x18;
			var4 = 0x80110002;
			if (!((((arg3 + 0x80) | structInput) & (0 - structID)) < 0))
			{
				ret = sp;
				var4 = 0x80110604;
				if (!(((var1 < 0x1D)) == 0))
				{
					((int *) sp)[1] = var1;
					((int *) sp)[0] = arg1;
					((int *) sp)[3] = structInput;
					((int *) sp)[2] = 0x80;
					((int *) sp)[4] = 0;
					var9 = sceKernelExtendKernelStack (0x1000, 0x60E4, ret);
					structSize = ((int *) sp)[4];
					var4 = !(((var9 < 0))) ? structSize : var9;
				}
			}
		}
	}
	k1 = var3;
	ra = ((int *) sp)[9];
	var11 = ((int *) sp)[8];
	sp = sp + 0x30;
	return;
}
void sceUtility_netparam_internal_4CBB0CA0 (int arg1, int arg2){
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[5] = ra;
	var1 = arg1;
	((int *) sp)[4] = s0;
	structInput = k1;
	k1 = k1 >> 0x10;
	var3 = 0x80110603;
	if (!(arg2 == 0))
	{
		var4 = k1 & 0x18;
		var3 = 0x80110002;
		if (!((((arg2 + 0x80) | arg2) & (0 - var4)) < 0))
		{
			var3 = 0x80110604;
			if (!(((var1 < 0x1D)) == 0))
			{
				structID = sp;
				var3 = 0x80110604;
				if (!((((var1 + 0xFFFFFFE7) < 4)) != 0))
				{
					((int *) sp)[0] = var1;
					((int *) sp)[1] = arg2;
					((int *) sp)[2] = 0;
					var8 = sceKernelExtendKernelStack (0x1000, 0x6160, structID);
					var9 = ((int *) sp)[2];
					var3 = !(((var8 < 0))) ? var9 : var8;
				}
			}
		}
	}
	k1 = structInput;
	ra = ((int *) sp)[5];
	structSize = ((int *) sp)[4];
	sp = sp + 0x20;
	return;
}
void sceUtility_netparam_internal_F161E17A (int arg1, int arg2){
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[5] = ra;
	var1 = arg1;
	((int *) sp)[4] = s0;
	structInput = k1;
	k1 = k1 >> 0x10;
	var3 = 0x80110603;
	if (!(arg2 == 0))
	{
		var4 = k1 & 0x18;
		var3 = 0x80110002;
		if (!((((arg2 + 0x80) | arg2) & (0 - var4)) < 0))
		{
			structID = sp;
			var3 = 0x80110604;
			if (!(((var1 < 0x1D)) == 0))
			{
				((int *) sp)[0] = var1;
				((int *) sp)[1] = arg2;
				((int *) sp)[2] = 0;
				var8 = sceKernelExtendKernelStack (0x1000, 0x6160, structID);
				var9 = ((int *) sp)[2];
				var3 = !(((var8 < 0))) ? var9 : var8;
			}
		}
	}
	k1 = structInput;
	ra = ((int *) sp)[5];
	structSize = ((int *) sp)[4];
	sp = sp + 0x20;
	return;
}
void sceUtility_ECE1D3E5 (int arg1){
	if (arg1 && !((((arg1 + 0x40) | arg1) & (- k1&0x18)) < 0))
		sub_061E4 ("/CONFIG/NETWORK/GO_MESSENGER", "auth_name", arg1, 0x40);
}
void sceUtility_28D35634 (int arg1){
	if (arg1 && !((((arg1 + 0x40) | arg1) & (- k1&0x18)) < 0))
		sub_056B0 ("/CONFIG/NETWORK/GO_MESSENGER", "auth_name", arg1, 0x40);
}
void sceUtility_70267ADF (int arg1){
	if (arg1 && !((((arg1 + 0x40) | arg1) & (- k1&0x18)) < 0))
		sub_061E4 ("/CONFIG/NETWORK/GO_MESSENGER", "auth_key", var1, 0x40);
}
void sceUtility_EF3582B2 (int arg1){
	if (arg1 && !((((arg1 + 0x40) | arg1) & (- k1&0x18)) < 0))
		sub_056B0 ("/CONFIG/NETWORK/GO_MESSENGER", "auth_key", var1, 0x40);
}
void sceUtility_netparam_internal_0E244DD7 (int arg1){
	sub_05358 ("/CONFIG/NETWORK/INFRASTRUCTURE", "latest_id", arg1);
}
void sceUtilityGetNetParamLatestID (int arg1){
	sub_050F0 ("/CONFIG/NETWORK/INFRASTRUCTURE", "latest_id", arg1);
}
void sub_05F0C (int arg1){
	var4 = sub_07240 ();
	structID = var4;
	if (!(var4 < 0)){
		structID = sub_062F4 (((int *) arg1)[0], sp, 0);
		if (structSize >= 0)
			sub_0664C (sp);
	}
	sub_072C8 ();
	((int *) arg1)[1] = structID;
}
void sub_05F74 (int arg1){
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = s1;
	((int *) sp)[0] = s0;
	((int *) sp)[2] = ra;
	var1 = arg1;
	var4 = sub_07240 ();
	structID = var4;
	if (!(var4 < 0))
	{
		ret = ((int *) var1)[0];
		var9 = sub_064CC (ret);
		structID = var9;
	}
	sub_0734C ();
	sub_072C8 ();
	((int *) var1)[1] = structID;
	ra = ((int *) sp)[2];
	var14 = ((int *) sp)[1];
	var15 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}
void sub_05FCC (int arg1){
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = s1;
	((int *) sp)[0] = s0;
	((int *) sp)[2] = ra;
	var1 = arg1;
	var4 = sub_07240 ();
	structID = var4;
	if (!(var4 < 0))
	{
		ret = ((int *) var1)[0];
		var9 = sub_06418 (ret);
		structID = var9;
	}
	sub_0734C ();
	sub_072C8 ();
	((int *) var1)[1] = structID;
	ra = ((int *) sp)[2];
	var14 = ((int *) sp)[1];
	var15 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}
void sub_06024 (int arg1){
	var1 = 0;
	structInput = arg1;
	structID = sub_07240 ();
	ret = structID;
	var7 = sp;
	if (!(structID < 0))
	{
		var8 = ((int *) structInput)[0];
		var9 = sp + 0x10;
		var12 = sub_062F4 (var8, var7, 0);
		ret = var12;
		if (!(var12 < 0))
		{
			var13 = ((int *) structInput)[1];
			PrxToLoad = sub_062F4 (var13, var9, 0);
			ret = PrxToLoad;
			var17 = sp;
			if (!(PrxToLoad < 0))
			{
				var1 = 1;
				structInput0 = sub_06570 (var17, var9);
				ret = structInput0;
			}
			structInput1 = sp;
			sub_0664C (structInput1);
			if (!(var1 <= 0))
			{
				sub_0664C (var9);
			}
		}
	}
	sub_0734C ();
	sub_072C8 ();
	return;
}
void sub_060E4 (int arg1){
	arg1 = arg1;
	structID = sub_07240 ();
	ret = sp;
	if (tmp >= 0){
		structID = sub_0667C (sub_062F4 (((int *) arg1)[0], ret, 0), ((int *) arg1)[1], ((int *) arg1)[2], ((int *) arg1)[3]);
		sub_0664C (sp);
	}
	sub_072C8 ();
	((int *) arg1)[4] = structID;
	return;
}
void sub_061E4 (int arg1, int arg2, int arg3, int arg4)
{
	sp = sp + 0xFFFFFEC0;
	((int *) sp)[76] = s4;
	((int *) sp)[75] = s3;
	((int *) sp)[72] = s0;
	var1 = sp;
	((int *) sp)[77] = ra;
	((int *) sp)[74] = s2;
	((int *) sp)[73] = s1;
	memset (var1, 0, 0x0110);
	var4 = sp;
	structID = sp + 0x0110;
	((int *) sp)[67] = 1;
	((int *) sp)[0] = 1;
	((int *) sp)[66] = 1;
	var8 = sceReg_driver_7CA7768A (var4, 2, structID);
	var9 = var8;
	structSize = sp + 0x0114;
	if (var9 == 0)
	{
		var18 = ((int *) sp)[68];
		structInput1 = sceReg_driver_6A37E343 (var18, arg1, 2, structSize);
		graphicThreadPrio = structInput1;
		if (structInput1 != 0)
		{

		label24:
			var30 = ((int *) sp)[68];
			sceReg_driver_EFE7BE31 (var30);
		}
		else
		{
			structInput3 = ((int *) sp)[69];
			structInput6 = sceReg_driver_43CF36BC (structInput3, arg2, arg3, arg4);
			graphicThreadPrio = structInput6;
			if (structInput6 == 0)
			{
				var33 = ((int *) sp)[69];
				sceReg_driver_FED2B205 (var33);
				var36 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (var36);
				var39 = ((int *) sp)[68];
				sceReg_driver_BC2ECC38 (var39);
				var42 = ((int *) sp)[68];
				sceReg_driver_EFE7BE31 (var42);
			}
			else
			{
				structInput7 = ((int *) sp)[69];
				sceReg_driver_C2E5E478 (structInput7);
				goto label24;
			}
		}
	}
	else
	{
		Kprintf ("couldn't open registry - 0x%x\n", var9);
	}
	ra = ((int *) sp)[77];
	var13 = ((int *) sp)[76];
	var14 = ((int *) sp)[75];
	var15 = ((int *) sp)[74];
	PrxToLoad = ((int *) sp)[73];
	var17 = ((int *) sp)[72];
	sp = sp + 0x0140;
	return;
}

/**
 * Subroutine at address 0x62F4
 */
int sub_062F4 (int arg1, int arg2, int arg3)
{
	sp = sp + 0xFFFFFFA0;
	((int *) sp)[21] = s5;
	var1 = 0;
	((int *) sp)[19] = s3;
	structInput = arg3;
	((int *) sp)[18] = s2;
	var3 = arg2;
	((int *) sp)[17] = s1;
	((int *) sp)[16] = s0;
	var4 = 0x80110602;
	((int *) sp)[22] = ra;
	((int *) sp)[20] = s4;
	if (arg1 < 0)
	{

	label17:
		if (var1 == 1)
		{
			structInput7 = ((int *) var3)[0];
			sub_0731C (structInput7);
			structInput0 = var4;
		}
		else
		{
			structInput0 = var4;
		}
	}
	else
	{
		structID = sp;
		sprintf (structID, "%s/%d", 0x93CC, arg1, arg5);
		var8 = sp;
		var11 = sub_071D0 (var8, structInput, var3);
		var4 = var11;
		if (var11 < 0)
			goto label17;
		var12 = sp;
		var13 = var3 + 4;
		sprintf (var12, "%s/%d/%s", 0x93CC, arg1, "SUB1");
		PrxToLoad = sp;
		var19 = sub_071D0 (PrxToLoad, structInput, var13);
		var4 = var19;
		var1 = 1;
		if (var19 == 0x80110601)
		{
			var30 = sp;
			var33 = sub_071D0 (var30, 1, var13);
			var4 = var33;
		}
		structInput0 = 0;
		if (var4 < 0)
			goto label17;
	}
	ra = ((int *) sp)[22];
	structInput1 = ((int *) sp)[21];
	graphicThreadPrio = ((int *) sp)[20];
	structInput3 = ((int *) sp)[19];
	structInput4 = ((int *) sp)[18];
	graphicThread = ((int *) sp)[17];
	structInput6 = ((int *) sp)[16];
	sp = sp + 0x60;
	return structInput0;
}

/**
 * Subroutine at address 0x6418
 */
int sub_06418 (int arg1)
{
	sp = sp + 0xFFFFFFB0;
	((int *) sp)[17] = s1;
	((int *) sp)[16] = s0;
	var1 = arg1;
	((int *) sp)[18] = ra;
	structInput = sp;
	var3 = 0x80110602;
	if (!(var1 < 0))
	{
		sprintf (structInput, "%s/%d/%s", 0x93CC, arg1, "SUB1");
		ret = sp;
		var9 = sub_073FC (ret);
		structSize = (var9 >> 0x1F) & ((0 < (var9 ^ 0x80082718)));
		var3 = var9;
		var11 = sp;
		if (!(structSize != 0))
		{
			sprintf (var11, "%s/%d", 0x93CC, var1, structSize);
			var14 = sp;
			var17 = sub_073FC (var14);
			var3 = var17;
		}
	}
	ra = ((int *) sp)[18];
	var18 = ((int *) sp)[17];
	var19 = ((int *) sp)[16];
	sp = sp + 0x50;
	return var3;
}

/**
 * Subroutine at address 0x64CC
 */
int sub_064CC (int arg1)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[5] = s1;
	((int *) sp)[4] = s0;
	((int *) sp)[6] = ra;
	var1 = arg1;
	var4 = sub_06F88 (arg1);
	if (!(var4 < 0))
	{
		structID = sp;
		var4 = 0x80110681;
		if (!(var4 > 0))
		{
			var8 = sub_062F4 (var1, structID, 1);
			var9 = var8;
			structSize = sp;
			if (var8 < 0)
			{

			label23:
				var4 = var9;
			}
			else
			{
				var13 = sub_06788 (structSize);
				var9 = var13;
				if (var13 < 0)
				{
					graphicThreadPrio = ((int *) sp)[1];
					sub_0731C (graphicThreadPrio);
					graphicThread = ((int *) sp)[0];
					sub_0731C (graphicThread);
					var30 = sub_06418 (var1);
					var4 = var9;
				}
				else
				{
					var14 = ((int *) sp)[1];
					sub_0731C (var14);
					var17 = ((int *) sp)[0];
					sub_0731C (var17);
					goto label23;
				}
			}
		}
	}
	ra = ((int *) sp)[6];
	structInput0 = ((int *) sp)[5];
	structInput1 = ((int *) sp)[4];
	sp = sp + 0x20;
	return var4;
}

/**
 * Subroutine at address 0x6570
 */
int sub_06570 (int arg1, int arg2)
{
	sp = sp + 0xFFFFFEF0;
	((int *) sp)[67] = ra;
	((int *) sp)[66] = s2;
	var1 = arg1;
	((int *) sp)[65] = s1;
	structInput = arg2;
	((int *) sp)[64] = s0;
	var3 = 0;
	var4 = 0xFFFFFFE7;
	while (1) {
		structID = var3;
		ret = var1;
		var7 = structInput;
		var8 = sp;
		if (!(((var4 < 4)) != 0))
		{
			structID = var3;
			ret = var1;
			var7 = structInput;
			var8 = sp + 0x80;
		}
		var11 = sub_06C6C (ret, var7, structID, 0x80, var8);
		if (var11 < 0)
			break;
		var3 = var3 + 1;
		var4 = var3 + 0xFFFFFFE7;
		if (((var3 < 0x1D)) != 0)
			continue;
		break;
	}
	ra = ((int *) sp)[67];
	var12 = ((int *) sp)[66];
	var13 = ((int *) sp)[65];
	var14 = ((int *) sp)[64];
	sp = sp + 0x0110;
	return var11;
}

/**
 * Subroutine at address 0x6600
 */
int buildNetRegKey (int n, int buf, int arg3){
	if (arg3 < 0x32)return 0x80110682;
	sprintf (buf, "%s/%d", "/CONFIG/NETWORK/INFRASTRUCTURE", n, (arg3 < 0x32));
	return 0;
}

/**
 * Subroutine at address 0x664C
 */
void sub_0664C (int arg1)
{
	sp = sp + 0xFFFFFFF0;
	((int *) sp)[1] = ra;
	((int *) sp)[0] = s0;
	var1 = ((int *) arg1)[1];
	sub_0731C (var1);
	var4 = ((int *) arg1)[0];
	sub_0731C (var4);
	ra = ((int *) sp)[1];
	var7 = ((int *) sp)[0];
	sp = sp + 0x10;
	return;
}
int sub_0667C (int arg1, int arg2, int arg3, int arg4){
	if ((arg2 + 0xFFFFFFE7) >= 4)
		var1 = ((int *) arg1)[0];
	else
		var1 = ((int *) arg1)[1];
	tmp = (((arg2 << 1) + arg2) << 2) + 0x9574;
	return sub_07044 (var1, ((int *) tmp)[2],((int *) tmp)[0], ((int *) tmp)[1], arg3, arg4);
}
/**
 * Subroutine at address 0x66F4
 */
int sub_066F4 (int arg1, int arg2, int arg3)
{
	sp = sp + 0xFFFFFFE0;
	((int *) sp)[2] = s2;
	var1 = arg3;
	((int *) sp)[4] = ra;
	((int *) sp)[3] = s3;
	((int *) sp)[1] = s1;
	((int *) sp)[0] = s0;
	if ((((arg2 + 0xFFFFFFE7) < 4)) == 0)
	{
		structInput = ((int *) arg1)[0];
	}
	else
	{
		structInput = ((int *) arg1)[1];
	}
	var3 = (((arg2 << 1) + arg2) << 2) + 0x9574;
	var4 = ((int *) var3)[1];
	var7 = sub_06DC0 (arg2, var4, var1);
	if (!(var7 < 0))
	{
		var8 = ((int *) var3)[2];
		var7 = sub_07374 (structInput, var8, var4, var1);
	}
	ra = ((int *) sp)[4];
	var11 = ((int *) sp)[3];
	var12 = ((int *) sp)[2];
	var13 = ((int *) sp)[1];
	var14 = ((int *) sp)[0];
	sp = sp + 0x20;
	return var7;
}
int sub_06788 (int arg1){
	var8 = sub_07398 (((int *) arg1)[0], *((int *) 0x963C), *((int *) 0x9634), *((int *) 0x9638), 4, 0x9724);
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[0], *((int *) 0x9648), *((int *) 0x9640), *((int *) 0x9644), 4, 0x9728);
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[0], *((int *) 0x957C), *((int *) 0x9574), *((int *) 0x9578), (strlen (*((int *) 0x96D4)) + 1), *((int *) 0x96D4));
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[0], ((int *) arg1)[0], *((int *) 0x9580), *((int *) 0x9584), (strlen (*((int *) 0x96D8)) + 1), *((int *) 0x96D8));
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[0], *((int *) 0x9594), *((int *) 0x958C), *((int *) 0x9590), 4, 0x96DC);
	if (var8 < 0)return -1;
	endOfStruct = ((int *) arg1)[0];
	var44 = *((int *) 0x95A0);
	structSize = *((int *) 0x9598);
	structSize = *((int *) 0x959C);
	structSize = *((int *) 0x96F0);
	var8 = sub_07398 (endOfStruct, var44, structSize, structSize, structSize, 0x96E0);
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[0], *((int *) 0x95AC), *((int *) 0x95A4), *((int *) 0x95A8), 4, 0x96F4);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	resolution = *((int *) 0x96F8);
	structSize = strlen (resolution);
	ret0 = ((int *) arg1)[0];
	ret1 = *((int *) 0x95B8);
	ret2 = *((int *) 0x95B0);
	ret3 = *((int *) 0x95B4);
	ret4 = *((int *) 0x96F8);
	var8 = sub_07398 (ret0, ret1, ret2, ret3, (structSize + 1), ret4);
	if (var8 < 0)return -1;
	ret7 = *((int *) 0x96FC);
	var70 = strlen (ret7);
	var71 = ((int *) arg1)[0];
	var72 = *((int *) 0x95C4);
	var73 = *((int *) 0x95BC);
	var74 = *((int *) 0x95C0);
	var75 = *((int *) 0x96FC);
	var8 = sub_07398 (var71, var72, var73, var74, (var70 + 1), var75);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	var78 = *((int *) 0x9700);
	var81 = strlen (var78);
	var82 = ((int *) arg1)[0];
	var83 = *((int *) 0x95D0);
	var84 = *((int *) 0x95C8);
	var85 = *((int *) 0x95CC);
	var86 = *((int *) 0x9700);
	var8 = sub_07398 (var82, var83, var84, var85, (var81 + 1), var86);
	if (var8 < 0)return -1;
	var89 = ((int *) arg1)[0];
	var90 = *((int *) 0x95DC);
	var91 = *((int *) 0x95D4);
	var92 = *((int *) 0x95D8);
	var8 = sub_07398 (var89, var90, var91, var92, 4, 0x9704);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	var95 = *((int *) 0x9708);
	var98 = strlen (var95);
	var99 = ((int *) arg1)[0];
	structSize0 = *((int *) 0x95E8);
	structSize1 = *((int *) 0x95E0);
	structSize2 = *((int *) 0x95E4);
	structSize3 = *((int *) 0x9708);
	var8 = sub_07398 (var99, structSize0, structSize1, structSize2, (var98 + 1), structSize3);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	structSize6 = *((int *) 0x970C);
	structSize9 = strlen (structSize6);
	arg110 = ((int *) arg1)[0];
	arg111 = *((int *) 0x95F4);
	arg112 = *((int *) 0x95EC);
	arg113 = *((int *) 0x95F0);
	arg114 = *((int *) 0x970C);
	var8 = sub_07398 (arg110, arg111, arg112, arg113, (structSize9 + 1), arg114);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	arg117 = *((int *) 0x9710);
	arg120 = strlen (arg117);
	arg121 = ((int *) arg1)[0];
	arg122 = *((int *) 0x9600);
	arg123 = *((int *) 0x95F8);
	arg124 = *((int *) 0x95FC);
	arg125 = *((int *) 0x9710);
	var8 = sub_07398 (arg121, arg122, arg123, arg124, (arg120 + 1), arg125);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	arg128 = *((int *) 0x9714);
	arg131 = strlen (arg128);
	arg132 = ((int *) arg1)[0];
	arg133 = *((int *) 0x960C);
	arg134 = *((int *) 0x9604);
	arg135 = *((int *) 0x9608);
	arg136 = *((int *) 0x9714);
	var8 = sub_07398 (arg132, arg133, arg134, arg135, (arg131 + 1), arg136);
	if (var8 < 0)return -1;
	arg139 = ((int *) arg1)[0];
	arg140 = *((int *) 0x9618);
	arg141 = *((int *) 0x9610);
	arg142 = *((int *) 0x9614);
	var8 = sub_07398 (arg139, arg140, arg141, arg142, 4, 0x9718);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	arg145 = *((int *) 0x971C);
	arg148 = strlen (arg145);
	arg149 = ((int *) arg1)[0];
	arg150 = *((int *) 0x9624);
	arg151 = *((int *) 0x961C);
	arg152 = *((int *) 0x9620);
	arg153 = *((int *) 0x971C);
	var8 = sub_07398 (arg149, arg150, arg151, arg152, (arg148 + 1), arg153);
	if (var8 < 0)return -1;
	arg156 = ((int *) arg1)[0];
	arg157 = *((int *) 0x9630);
	arg158 = *((int *) 0x9628);
	arg159 = *((int *) 0x962C);
	var8 = sub_07398 (arg156, arg157, arg158, arg159, 4, 0x9720);
	if (var8 < 0)return -1;
	PrxToLoad2 = ((int *) arg1)[0];
	PrxToLoad3 = *((int *) 0x9654);
	PrxToLoad4 = *((int *) 0x964C);
	PrxToLoad5 = *((int *) 0x9650);
	var8 = sub_07398 (PrxToLoad2, PrxToLoad3, PrxToLoad4, PrxToLoad5, 4, 0x972C);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	PrxToLoad8 = *((int *) 0x9730);
	arg171 = strlen (PrxToLoad8);
	arg172 = ((int *) arg1)[0];
	arg173 = *((int *) 0x9660);
	arg174 = *((int *) 0x9658);
	arg175 = *((int *) 0x965C);
	arg176 = *((int *) 0x9730);
	var8 = sub_07398 (arg172, arg173, arg174, arg175, (arg171 + 1), arg176);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	arg179 = *((int *) 0x9734);
	arg182 = strlen (arg179);
	arg183 = ((int *) arg1)[0];
	arg184 = *((int *) 0x966C);
	arg185 = *((int *) 0x9664);
	arg186 = *((int *) 0x9668);
	arg187 = *((int *) 0x9734);
	var8 = sub_07398 (arg183, arg184, arg185, arg186, (arg182 + 1), arg187);
	if (var8 < 0)return -1;
	arg190 = ((int *) arg1)[0];
	arg191 = *((int *) 0x9678);
	arg192 = *((int *) 0x9670);
	arg193 = *((int *) 0x9674);
	var8 = sub_07398 (arg190, arg191, arg192, arg193, 4, 0x9738);
	if (var8 < 0)return -1;
	arg196 = ((int *) arg1)[0];
	arg197 = *((int *) 0x9684);
	arg198 = *((int *) 0x967C);
	arg199 = *((int *) 0x9680);
	var8 = sub_07398 (arg196, arg197, arg198, arg199, 0x40, 0x973C);
	if (var8 < 0)return -1;
	structInput02 = ((int *) arg1)[0];
	structInput03 = *((int *) 0x9690);
	structInput04 = *((int *) 0x9688);
	structInput05 = *((int *) 0x968C);
	var8 = sub_07398 (structInput02, structInput03, structInput04, structInput05, 4, 0x977C);
	if (var8 < 0)return -1;
	structInput08 = ((int *) arg1)[0];
	structInput09 = *((int *) 0x969C);
	structInput10 = *((int *) 0x9694);
	structInput11 = *((int *) 0x9698);
	var8 = sub_07398 (structInput08, structInput09, structInput10, structInput11, 4, 0x9780);
	ra = ((int *) sp)[5];
	if (var8 < 0)return -1;
	structInput14 = *((int *) 0x9784);
	structInput17 = strlen (structInput14);
	structInput18 = ((int *) arg1)[1];
	structInput19 = *((int *) 0x96A8);
	graphicThreadPrio0 = *((int *) 0x96A0);
	graphicThreadPrio1 = *((int *) 0x96A4);
	graphicThreadPrio2 = *((int *) 0x9784);
	var8 = sub_07398 (structInput18, structInput19, graphicThreadPrio0, graphicThreadPrio1, (structInput17 + 1), graphicThreadPrio2);
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[1], *((int *) 0x96B4), ((int *) arg1)[1], *((int *) 0x96B0), (strlen (*((int *) 0x9788)) + 1), *((int *) 0x9788));
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[1], *((int *) 0x96C0), *((int *) 0x96B8), *((int *) 0x96BC), 4, 0x978C);
	if (var8 < 0)return -1;
	var8 = sub_07398 (((int *) arg1)[1], *((int *) 0x96CC), *((int *) 0x96C4), *((int *) 0x96C8), (strlen (*((int *) 0x9790)) + 1), *((int *) 0x9790));
	if (var8 < 0)return 0;
	return var8;
}
int sub_06C6C (int arg1, int arg2, int arg3, int arg4, int arg5){
	var4 = arg3;
	structID = arg1;
	if (((arg3 + 0xFFFFFFE7 < 4)) == 0)
		endOfStruct = ((int *) arg1)[0];
	else
		return ((int *) arg1)[1];
	var7 = arg3 << 1;
	var8 = ((int *) (((var7 + arg3) << 2) + 0x9574))[2];
	var11 = sub_07000 ();
	var12 = var11;
	if (var11 < 0)return -1;
	if (!(var11 == 0)){
		if (((arg3 + 0xFFFFFFE7 < 4)) == 0)
			var13 = ((int *) structID)[0];
		else
			var13 = ((int *) structID)[1];
		var14 = ((var7 + arg3) << 2) + 0x9574;
		if (sub_07044 (var13, ((int *) var14)[2], ((int *) var14)[0], ((int *) var14)[1], arg4, arg5) < 0)return -1
		if (arg3 == 0x10){
			if (sub_07044 (((int *) arg2)[0], *((int *) 0x963C), *((int *) 0x9634), *((int *) 0x9638), 0x80, sp) < 0)return -1;
			if (((int *) arg5)[0] < ((int *) sp)[0])return;
			return sub_06EEC (arg2, arg3, arg5);
		}
	}
	return var12;
}
int sub_06DC0 (int arg1, int arg2, int arg3){
	var1 = 0;
	if (((arg1 >= 0x1C)){
	case 0:
	case 1:
	case 5:
	case 6:
	case 7:
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 16:
	case 17:
	case 19:
	case 20:
	case 25:
	case 26:

	label17:
		var3 = var1;
	}
	else
	{
		structInput = ((int *) ((arg1 << 2) + 0x9794))[0];
		switch () {
		goto label17;
		goto label17;
		case 2:
			var4 = LWL (arg3, 0x9794, 3);
			structID = LWR (arg3, var4, 0);
			SWL (sp, structID, 3);
			SWR (sp, structID, 0);
			ret = ((int *) sp)[0];
			var7 = (ret < 5);

		label15:
			if (var7 == 0)
			{

			label16:
				var1 = 0x80110605;
			}
			goto label17;
		case 3:
			var8 = ((0 < (arg2 ^ 5))) & ((0 < (arg2 ^ 13)));

		label11:
			if (var8 == 0)
			{
				var3 = 0;
			}
			else
			{
				goto label16;
			}
		case 4:
			var9 = LWL (arg3, 0x9794, 3);
			structSize = LWR (arg3, var9, 0);
			SWL (sp, structSize, 3);
			SWR (sp, structSize, 0);
			var11 = ((int *) sp)[0];
			var7 = (var11 < 3);
			goto label15;
		goto label17;
		goto label17;
		goto label17;
		case 8:
		case 13:
		case 18:
		case 21:
		case 23:
			var12 = LWL (arg3, 0x9794, 3);
			var13 = LWR (arg3, var12, 0);
			SWL (sp, var13, 3);
			SWR (sp, var13, 0);
			var14 = ((int *) sp)[0];
			var7 = (var14 < 2);
			goto label15;
		goto label17;
		goto label17;
		goto label17;
		goto label17;
		goto label17;
		case 15:
			var15 = LWL (arg3, 0x9794, 3);
			PrxToLoad = LWR (arg3, var15, 0);
			SWL (sp, PrxToLoad, 3);
			SWR (sp, PrxToLoad, 0);
			var17 = ((int *) sp)[0];
			var8 = (0xFFFE < (var17 + 0xFFFFFFFF));
			goto label11;
		goto label17;
		goto label17;
		goto label17;
		goto label17;
		case 22:
			var8 = (arg2 < 9);
			goto label11;
		case 24:
			var18 = LWL (arg3, 0x9794, 3);
			var19 = LWR (arg3, var18, 0);
			SWL (sp, var19, 3);
			SWR (sp, var19, 0);
			structInput0 = ((int *) sp)[0];
			var7 = (structInput0 < 4);
			goto label15;
		goto label17;
		goto label17;
		case 27:
			structInput1 = LWL (arg3, 0x9794, 3);
			graphicThreadPrio = LWR (arg3, structInput1, 0);
			SWL (sp, graphicThreadPrio, 3);
			SWR (sp, graphicThreadPrio, 0);
			structInput3 = ((int *) sp)[0];
			var1 = (((structInput3 & 0xFFFFFFFE) | (0 & 1))) ? 0x80110605 : 0;
			goto label17;
		}
	}
	sp = sp + 0x10;
	return var3;
}
int sub_06EEC (int arg1, int arg2, int arg3){
	if ((arg2 + 0xFFFFFFE7) >= 4)
		var1 = ((int *) arg1)[0];
	else
		var1 = ((int *) arg1)[1];
	var3 = (((arg2 << 1) + arg2) << 2) + 0x9574;
	var7 = sub_06DC0 (arg2, ((int *) var3)[1], arg3);
	if(var7 < 0)return var7;
	return sub_0710C (var1, ((int *) var3)[2], ((int *) var3)[0], ((int *) var3)[1], ((int *) var3)[1], var1);
}
int sub_06F88 (int arg1){
	var4 = buildNetRegKey (arg1, sp, 0x32);
	if (var4 < 0)return var4;
	if (!sceReg_driver_6A37E343 (RegFd, sp, 2, sp + 0x40)){
		var12 = 1;
		sceReg_driver_C2E5E478 (((int *) sp)[16]);
	}
	return (var12 ^ 0x80082718) ? var12 : 0;
}
int sub_07000 (){
	ret = sceReg_driver_029B2F8F (arg1, arg2, sp, structInput);
	if (ret != 0)
		return !((ret ^ 0x8008271D)) ? 0 : ret;
	return 1;
}
int sub_07044 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	ret = sceReg_driver_029B2F8F (arg1, arg2, sp, sp + 4);
	if (!(ret < 0)){
		if (arg3 != ((int *) sp)[0])return 0x80110683
		if (arg4 < ((int *) sp)[1])return 0x80110684;
		if (arg5 < var15)return 0x80110685;
		return sceReg_driver_73313DA4 (arg1, arg2, arg6, arg5);
	}
	return ret;
}
int sub_0710C (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	var9 = sceReg_driver_029B2F8F (arg1, arg2, sp,sp + 4);
	if(!var9){
	label11:
		var9 = sceReg_driver_43CF36BC (arg1, arg2, arg6, arg5);
		ra = ((int *) sp)[10];
	}else{
		if (var9 == 0x8008271D){
			var9 = sceReg_driver_762C35DC (arg1, arg2, arg3, arg4);
			if (var9 < 0){
				ra = ((int *) sp)[10];
			}else{
				goto label11;
			}
		}else{
			ra = ((int *) sp)[10];
		}
	}
	return var9;
}
int sub_071D0 (int arg1, int arg2, int arg3){
	var4 = sceReg_driver_6A37E343 (RegFd, arg1, (!(((0 < arg2))) ? 2 : 1), arg3);
	return (((((arg2 < 1)) & (((var4 ^ 0x80082718) < 1)))) ? 0x80110601 : var4);
}
int sub_07240 (){
	memset (sp, 0, 0x0110);
	((int *) sp)[0] = 1;
	strncpy (sp + 4, "flash2/registry/system", 0x0100);
	((int *) sp)[65] = 0x16;
	((int *) sp)[67] = 1;
	((int *) sp)[66] = 1;
	var11 = sceReg_driver_7CA7768A (sp, 2, sp + 0x0110);
	if (!(var11 < 0)){
		RegFd = ((int *) sp)[68];
		RegUnkA1B8++;
	}
	return var11;
}
void sub_072C8 (){
	if (RegUnkA1B8>0){
		sceReg_driver_BC2ECC38 (RegFd);
		sceReg_driver_EFE7BE31 (RegFd);
		RegUnkA1B8--
	}
}
void sub_0731C (int arg1){
	sceReg_driver_FED2B205 (arg1);
	sceReg_driver_C2E5E478 (arg1);
}
void sub_0734C (){
	return sceReg_driver_BC2ECC38 (RegFd);
}
int sub_07374 (int arg1, int arg2, int arg3, int arg4){
	return sceReg_driver_43CF36BC (arg1, arg2, arg4, arg3);
}
int sub_07398 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6){
	var3 = sceReg_driver_762C35DC (arg1, arg2, arg3, arg4);
	if (!(var3 < 0))var3 = sceReg_driver_43CF36BC (arg1, arg2, arg6, arg5);
	return var3;
}
int sub_073FC (int arg1){
	return sceReg_driver_3579EF34 (RegFd, arg1, 0);
}
void sub_07424 (int arg1, int arg2){
	StrCompRes = 0;
	if (!(SysMemForKernel_9D87D5B3 (sp) < 0)){
		tmp = 0x9804;//list of 0x14 sized struct
		i = 0x10;
		while (i >= 0) {
			if (arg1 == ((int *) tmp)[1])
				if ((arg2 == ((int *) tmp)[2]))
					StrCompRes = (strcmp (sp + 0x44,((int *) tmp)[0])? StrCompRes : tmp);
			tmp+=0x14;
			i--;
		}
	}
}
void sub_074C0 (){
	StrCompRes = 0;
	return;
}
int sub_074CC (){
	if (unkA1C0)
		return unkA1C0[3];
	return 0;
}
void sub_074E8 (int arg1, int arg2){
	if(!StrCompRes)return;
	structInput = ((int *) ((arg2 << 2) + var1))[4];
	if (!structInput)return;
	sceKernelDelayThread (structInput);
	return;
}

