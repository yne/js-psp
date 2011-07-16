LoadModule('jsstd');
LoadModule('jsio');
var print=Print;

String.prototype.haz=function(t){
	for(var i=0;i<t.length;i++)
		if(this.indexOf(t[i])==-1)return 0;
	return 1;
}
Array.prototype.replace=function(src,dst){
	var exp=new RegExp(src,"gm");
	for(var i=0;i<this.length;i++)this[i]=this[i].replace(exp,dst);
}
var file = new File(currentDirectory+'/'+(global.arguments[1]));
if(file.exist){
	file.Open( File.RDONLY );
	parse(file.Read());
	file.Close();
}else{
	print(currentDirectory+'/'+global.arguments[1]+" not found")
};
var res,exported,solved,know,l;
function result(u,n){
	var nid=res[u].substring(res[u].length-8,res[u].length)
	print("0x"+nid+","+n+"\n");
	solved++;
	//todo:update old nid in the source
	//for(var i=0;i<res;i+=2)
	//	res[i+1]=res[i+1].replace(res[u],n)
	res[u+1]="";
}
function c(str){//contain
	return res[2*l+1].indexOf(str)+1
}
function m(reg){//match
	return res[2*l+1].match(reg);
}
function ctrl(){
	solved=0;
	know=0;
	for(var i=0;i<res.length/2;i++){//1st pass
		var name=res[2*i+0];
		var src =res[2*i+1];
		if(!name.match(/[0-F]{6}$/)){//skip export
			     if(src.haz(["0x80000104"])){res.replace(name,"getBuffer");}//reed|peek&pos|neg
		}
	}
	for(var i=0;i<res.length/2;i++){//2nd pass
		if(res[2*i].indexOf("sub_")!=-1)continue;//skip stub
		var src=res[2*i+1];
//		if(res[2*i]=="SysMemForKernel_C5485286")print(src.length+"\n");
		if(src.length==58)result(2*i,"<empty>");
		else if(src.indexOf('"SceCtrl"')+1)result(2*i,"sceCtrlInit");
//		else if((src.length<150)&&(src.indexOf(") = arg4")+1))result(2*i,"sceCtrlSetIdleCancelKey");
		else if(src.indexOf("0x80000107")+1)result(2*i,"sceCtrlSetSamplingMode");
		else if(src.indexOf(") < 0x00000082")+1)result(2*i,"sceCtrlSetIdleCancelThreshold");
		else if(src.indexOf(" == 0x00000081")+1)result(2*i,"sceCtrlGetIdleCancelThreshold");
		else if(src.indexOf("arg4)[0] = var4")+1)result(2*i,"sceCtrlGetIdleCancelKey");
		else if(src.indexOf(", 0x00000000, 0x00000000, 0x00000000);")+1)result(2*i,"sceCtrlSetSamplingCycle");
		else if(src.indexOf("((var8 & var3)) ? 0x00000000 : 0x00000002;")+1)result(2*i,"sceCtrlSetButtonIntercept");
		else if(src.indexOf("((var7 & var2)) ? 0x00000000 : 0x00000002;")+1)result(2*i,"sceCtrlGetButtonIntercept");
		else if((src.indexOf("0x80000102")+1)&&(src.indexOf("0x800001FE")+1))result(2*i,"sceCtrlSetRapidFire");
		else if(src.haz(["[584]"])&&src.length<200)result(2*i,"sceCtrlClearRapidFire");
		else if(src.haz(["(0x0000001E, 0x00000013)",", 0x000003F0, 0x00000000);"])&&src.length<400)result(2*i,"sceCtrlResume");
		else if(src.haz(["(0x0000001E, 0x00000013)"])&&src.length<400)result(2*i,"sceCtrlSuspend");
//		else if(src.haz(["^ 0x00000001)"])&&src.length<350)result(2*i,"sceCtrlGetSamplingCycle/Mode");
		else if(src.match(/ = \(\(int \*\) var[0-9]+\)\[4\]/)&&(src.indexOf("[11]")==-1))result(2*i,"sceCtrlPeekLatch");
		else if(src.haz(["getBuffer (arg1, arg2, 0x00000000);"]))result(2*i,"sceCtrlPeekBufferPositive");
//		else if(src.match(/sub_[0-F]+ \(arg1, arg2, 0x00000000, 0x00000000\);/))result(2*i,"sceCtrlPeekBufferPositive");
		else if(src.haz(["getBuffer (arg1, arg2, 0x00000001);"]))result(2*i,"sceCtrlPeekBufferNegative");
//		else if(src.match(/sub_[0-F]+ \(arg1, arg2, 0x00000000, 0x00000001\);/))result(2*i,"sceCtrlPeekBufferNegative");
		else if(src.haz(["getBuffer (arg1, arg2, 0x00000002);"]))result(2*i,"sceCtrlReadBufferPositive");
//		else if(src.match(/sub_[0-F]+ \(arg1, arg2, 0x00000000, 0x00000002\);/))result(2*i,"sceCtrlReadBufferPositive");
		else if(src.haz(["getBuffer (arg1, arg2, 0x00000000);"]))result(2*i,"sceCtrlReadBufferNegative");
//		else if(src.match(/sub_[0-F]+ \(arg1, arg2, 0x00000000, 0x00000003\);/))result(2*i,"sceCtrlReadBufferNegative");
		else if(src.length==95)result(2*i,"<set>");
		else if(src.length==90&&(src.indexOf("= *")+1))result(2*i,"<get>");
		else if(src.length==90)result(2*i,"<get2>");//get but don't return ...
		else if(src.length<150)result(2*i,res[2*i]+":"+src.length);
	}
	print("\ntotal:"+exported+" solved:"+solved+" %"+Math.round(100*solved/exported)+"\n")
}
function syscon(){
	solved=0;
	know=0;
	/*
	for(var i=0;i<res.length/2;i++){//1st pass
		var name=res[2*i+0];
		var src =res[2*i+1];
		if(!name.match(/[0-F]{6}$/)){//skip export
			     if(src.haz(["0x80000104"])){res.replace(name,"getBuffer");}//reed|peek&pos|neg
		}
	}
		*/
	for(var i=0;i<res.length/2;i++){//2nd pass
		if(res[2*i].indexOf("sub_")!=-1)continue;//skip stub
		var src=res[2*i+1];//some argX, should be removed
		if(src.haz([" (arg1, arg2, 0x00000000);"]))result(2*i,"sceSysconSetLowBatteryCallback");
		else if(src.haz([" (arg1, arg2, 0x00000001);"]))result(2*i,"sceSysconSetPowerSwitchCallback");
		else if(src.haz([" (arg1, arg2, 0x00000002);"]))result(2*i,"sceSysconSetAlarmCallback");
		else if(src.haz([" (arg1, arg2, 0x00000003);"]))result(2*i,"sceSysconSetAcSupplyCallback");
		else if(src.haz([" (arg1, arg2, 0x00000004);"]))result(2*i,"sceSysconSetHPConnectCallback");
		else if(src.haz([" (arg1, arg2, 0x00000005);"]))result(2*i,"sceSysconSetWlanSwitchCallback");
		else if(src.haz([" (arg1, arg2, 0x00000006);"]))result(2*i,"sceSysconSetHoldSwitchCallback");
		else if(src.haz([" (arg1, arg2, 0x00000007);"]))result(2*i,"sceSysconSetUmdSwitchCallback");
		else if(src.haz([" (arg1, arg2, 0x00000008);"]))result(2*i,"sceSysconSetHRPowerCallback");
		else if(src.haz([" (arg1, arg2, 0x00000009);"]))result(2*i,"sceSysconSetWlanPowerCallback");
		else if(src.haz([" (arg1, 0x00000001);"]))result(2*i,"sceSysconGetBaryonVersion");
		else if(src.haz([" (arg1, 0x00000005);"]))result(2*i,"sceSysconGetTachyonTemp");
		else if(src.haz([" (arg1, 0x00000009);"]))result(2*i,"sceSysconReadClock");
		else if(src.haz([" (arg1, 0x0000000A);"]))result(2*i,"sceSysconReadAlarm");
		else if(src.haz([" (arg1, 0x0000000B);"]))result(2*i,"sceSysconGetPowerSupplyStatus");
		else if(src.haz([" (arg1, 0x0000000C);"]))result(2*i,"sceSysconGetTachyonWDTStatus");
		else if(src.haz([" (arg1, 0x0000000E);"]))result(2*i,"sceSysconGetWakeUpFactor");
		else if(src.haz([" (arg1, 0x0000000F);"]))result(2*i,"sceSysconGetWakeUpReq");
		else if(src.haz([" (arg1, 0x00000040);"]))result(2*i,"sceSysconGetPommelVersion");
		else if(src.haz([" (arg1, 0x00000041);"]))result(2*i,"sceSyscon_driver_FB148FB6");
		else if(src.haz([" (arg1, 0x00000046);"]))result(2*i,"sceSysconGetPowerStatus");
		else if(src.haz([" (arg1, 0x0000004A);"]))result(2*i,"sceSysconGetPowerError");
		else if(src.haz([" (0x00000062, arg1);"]))result(2*i,"sceSysconBatteryGetTemp");
		else if(src.haz([" (0x00000063, arg1);"]))result(2*i,"sceSysconBatteryGetVolt");
		else if(src.haz([" (0x00000064, arg1);"]))result(2*i,"sceSysconBatteryGetElec");
		else if(src.haz([" (0x00000065, arg1);"]))result(2*i,"sceSysconBatteryGetRCap");
		else if(src.haz([" (0x00000066, arg1);"]))result(2*i,"sceSysconBatteryGetCap");
		else if(src.haz([" (0x00000067, arg1);"]))result(2*i,"sceSysconBatteryGetFullCap");
		else if(src.haz([" (0x00000068, arg1);"]))result(2*i,"sceSysconBatteryGetIFC");
		else if(src.haz([" (0x00000069, arg1);"]))result(2*i,"sceSysconBatteryGetLimitTime");
		else if(src.haz([" (0x0000006A, arg1);"]))result(2*i,"sceSysconBatteryGetStatus");
		else if(src.haz([" (0x0000006B, arg1);"]))result(2*i,"sceSysconBatteryGetCycle");
		else if(src.haz([" (0x0000006C, arg1);"]))result(2*i,"sceSysconBatteryGetSerial");
		else if(src.haz([" (0x0000006E, arg1);"]))result(2*i,"sceSysconBatteryGetTempAD");
		else if(src.haz([" (0x0000006F, arg1);"]))result(2*i,"sceSysconBatteryGetVoltAD");
		else if(src.haz([" (0x00000070, arg1);"]))result(2*i,"sceSysconBatteryGetElecAD");
		else if(src.haz([" (0x00000071, arg1);"]))result(2*i,"sceSysconBatteryGetTotalElec");
		else if(src.haz([" (0x00000072, arg1);"]))result(2*i,"sceSysconBatteryGetChargeTime");
		else if(src.haz([" (arg1, 0x00000020, 0x00000006);"]))result(2*i,"sceSysconWriteClock");
		else if(src.haz([" (arg1, 0x00000022, 0x00000006);"]))result(2*i,"sceSysconWriteAlarm");
		else if(src.haz([" (arg1, 0x00000033, 0x00000003);"]))result(2*i,"sceSysconCtrlAnalogXYPolling");
		else if(src.haz([" (arg1, 0x00000034, 0x00000003);"]))result(2*i,"sceSysconCtrlHRPower");
		else if(src.haz([" (arg1, 0x00000042, 0x00000005);"]))result(2*i,"sceSysconCtrlVoltage");
		else if(src.haz([" (arg1, 0x00000045, 0x00000005);"]))result(2*i,"sceSysconCtrlPower");
		else if(src.haz([" (arg1, 0x00000047, 0x00000003);"]))result(2*i,"sceSysconCtrlLED");
		else if(src.haz([" (arg1, 0x00000048, 0x00000005);"]))result(2*i,"sceSysconWritePommelReg");
		else if(src.haz([" (arg1, 0x0000004B, 0x00000003);"]))result(2*i,"sceSysconCtrlLeptonPower");
		else if(src.haz([" (arg1, 0x0000004C, 0x00000003);"]))result(2*i,"sceSysconCtrlMsPower");
		else if(src.haz([" (arg1, 0x0000004D, 0x00000003);"]))result(2*i,"sceSysconCtrlWlanPower");
		else if(src.haz([" (arg1, 0x0000004E, 0x00000005);"]))result(2*i,"sceSysconPermitChargeBattery");//0x0000FDFF
		else if(src.haz([" (arg1, 0x0000004E, 0x00000005);"]))result(2*i,"sceSysconForbidChargeBattery");//0x0000FFFF
		else if(src.haz(["0x800001FE"]))result(2*i,"sceSysconCtrlTachyonWDT");
	}
	print("\ntotal:"+exported+" solved:"+solved+" %"+Math.round(100*solved/exported)+"\n")
}
function sysmem(){
	solved=0;
	know=147;
	for(var i=0;i<res.length/2;i++){
		var name=res[2*i];
		var src=res[2*i+1];
		if(res[2*i].indexOf("sub_")!=-1)continue;//skip sub
//		if(res[2*i]=="SysMemForKernel_C5485286")print(src.length+"\n");
		if(src.length==58)result(2*i,"<empty>");
		else if(src.haz(["0x87089863"]))result(2*i,"sceKernelDeleteUID");
		else if(src.haz(["0xB9970352","0x800200CB"]))result(2*i,"sceKernelCallUIDFunction");
		else if(src.haz(["0xB9970352",name]))result(2*i,"sceKernelCallUIDObjFunction");
		else if(src.haz(["0x800200CC"]))result(2*i,"sceKernelGetUIDcontrolBlockWithType");
		else if(src.haz(["0x800200CB","((int *) arg2)[0] = var"]))result(2*i,"sceKernelGetUIDcontrolBlock");
		else if(src.haz(["0x800200CB","var1 = "])&&(src.length<600))result(2*i,"sceKernelGetUIDtype");
		else if(src.haz(["  var1 = arg1;","  var2 = arg2;","SysMemForKernel_"])&&(!src.haz(["0x88000000"])))result(2*i,"sceKernelIsHold");
		else if(src.haz(["0x00000002) + 0xBC000000"]))result(2*i,"sceKernelSetDdrMemoryProtection");
		else if(src.haz(["if (!((var1 & 0x00001000) == 0x00000000))"]))result(2*i,"sceKernelGetCompiledSdkVersion");
		else if(src.haz([", arg1, 0x00000010);"]))result(2*i,"sceKernelSetQTGP3");//todo get QTGP3 offest (1st arg)
		else if(src.haz([" << 0x00000002)), arg2, 0x00000000);"]))result(2*i,"sceKernelAllocHeapMemory");
		else if(src.haz(["sceKernelDeleteUID (arg1);"])&&(src.length<400))result(2*i,"sceKernelDeleteHeap");
		//else if(src.haz([""]))result(2*i,"sceKernelFreeHeapMemory");
		else if(src.haz([") ? 0x00000000 : 0x000000FF), var"]))result(2*i,"sceKernelCreateHeap");
		else if(src.haz(["if (!(var1 == 0x00000000))","0x800200D2","0x800200D6"]))result(2*i,"sceKernelQueryMemoryPartitionInfo");
/*
		else if(src.haz([""]))result(2*i,"sceKernelPartitionMaxFreeMemSize");
		else if(src.haz([""]))result(2*i,"sceKernelPartitionTotalFreeMemSize");
		else if(src.haz([""]))result(2*i,"sceKernelAllocPartitionMemory");
		else if(src.haz([""]))result(2*i,"sceKernelAllocHeapMemoryWithOption");
		else if(src.haz([""]))result(2*i,"sceKernelFreePartitionMemory");
		else if(src.haz([""]))result(2*i,"sceKernelGetBlockHeadAddr");
		else if(src.haz([""]))result(2*i,"sceKernelGetModel");
    else if(src.haz([""]))result(2*i,"sceKernelHeapTotalFreeSize");
    else if(src.haz([""]))result(2*i,"sceKernelGetHeapTypeCB");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_EFF0C6DD");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_EFEEBAC7");
    else if(src.haz([""]))result(2*i,"sceKernelIsValidHeap");
    else if(src.haz([""]))result(2*i,"sceKernelFillFreeBlock");
    else if(src.haz([""]))result(2*i,"sceKernelSizeLockMemoryBlock");
    else if(src.haz([""]))result(2*i,"sceKernelResizeMemoryBlock");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_915EF4AC");
    else if(src.haz([""]))result(2*i,"sceKernelJointMemoryBlock");
    else if(src.haz([""]))result(2*i,"sceKernelQueryMemoryInfo");
    else if(src.haz([""]))result(2*i,"sceKernelQueryBlockSize");
    else if(src.haz([""]))result(2*i,"sceKernelQueryMemoryBlockInfo");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_2F3B7611");
    else if(src.haz([""]))result(2*i,"sceKernelMemoryExtendSize");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_CE05CCB7");
    else if(src.haz([""]))result(2*i,"sceKernelLookupUIDFunction");
    else if(src.haz([""]))result(2*i,"sceKernelCreateUIDtypeInherit");
    else if(src.haz([""]))result(2*i,"sceKernelCreateUIDtype");
    else if(src.haz([""]))result(2*i,"sceKernelDeleteUIDtype");
    else if(src.haz([""]))result(2*i,"sceKernelGetUIDname");
    else if(src.haz([""]))result(2*i,"sceKernelRenameUID");
    else if(src.haz([""]))result(2*i,"sceKernelGetUIDtype");
    else if(src.haz([""]))result(2*i,"sceKernelCreateUID");
    else if(src.haz([""]))result(2*i,"sceKernelDeleteUID");
    else if(src.haz([""]))result(2*i,"sceKernelSearchUIDbyName");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_82D3CEE3");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_FC207849");
    else if(src.haz([""]))result(2*i,"sceKernelHoldUID");
    else if(src.haz([""]))result(2*i,"sceKernelReleaseUID");
    else if(src.haz([""]))result(2*i,"sceKernelSysmemIsValidAccess");
    else if(src.haz([""]))result(2*i,"sceKernelIsValidUserAccess");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemCheckCtlBlk");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemDump");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemDumpBlock");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemDumpTail");
    else if(src.haz([""]))result(2*i,"sceKernelMemset");
    else if(src.haz([""]))result(2*i,"sceKernelMemset32");
    else if(src.haz([""]))result(2*i,"sceKernelMemmove");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemInit");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemMemSize");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemMaxFreeMemSize");
    else if(src.haz([""]))result(2*i,"sceKernelSysMemTotalFreeMemSize");
    else if(src.haz([""]))result(2*i,"sceKernelGetSysMemoryInfo");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_CDA3A2F7");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_960B888C");
    else if(src.haz([""]))result(2*i,"sceKernelGetSystemStatus");
    else if(src.haz([""]))result(2*i,"sceKernelSetSystemStatus");
    else if(src.haz([""]))result(2*i,"sceKernelGetUMDData");
    else if(src.haz([""]))result(2*i,"sceKernelGetUMDData (620 to 639)");
    else if(src.haz([""]))result(2*i,"sceKernelRegisterGetIdFunc");
    else if(src.haz([""]))result(2*i,"sceKernelQueryHeapInfo");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_03808C51");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_BB90D841");
    else if(src.haz([""]))result(2*i,"sceKernelMemmoveWithFill");
    else if(src.haz([""]))result(2*i,"sceKernelCopyGameInfo");
    else if(src.haz([""]))result(2*i,"sceKernelSetUmdData");
    else if(src.haz([""]))result(2*i,"sceKernelGetQTGP2");
    else if(src.haz([""]))result(2*i,"sceKernelSetQTGP2");
    else if(src.haz([""]))result(2*i,"sceKernelGetQTGP3");
    else if(src.haz([""]))result(2*i,"sceKernelGetAllowReplaceUmd");
    else if(src.haz([""]))result(2*i,"sceKernelSetParamSfo");
    else if(src.haz([""]))result(2*i,"sceKernelGetCompilerVersion");
    else if(src.haz([""]))result(2*i,"sceKernelGetDNAS");
    else if(src.haz([""]))result(2*i,"sceKernelSetDNAS");
    else if(src.haz([""]))result(2*i,"sceKernelRebootKernel");
    else if(src.haz([""]))result(2*i,"sceKernelGetId");
    else if(src.haz([""]))result(2*i,"sceKernelMemoryShrinkSize");
    else if(src.haz([""]))result(2*i,"sceKernelMemoryOpenSize");
    else if(src.haz([""]))result(2*i,"sceKernelMemoryCloseSize");
    else if(src.haz([""]))result(2*i,"sceKernelGetSysmemIdList");
    else if(src.haz([""]))result(2*i,"sceKernelSetAllowReplaceUmd");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_2269BFA2");
    else if(src.haz([""]))result(2*i,"sceKernelGetGameInfo");
    else if(src.haz([""]))result(2*i,"sceKernelSetCompilerVersion");
    else if(src.haz([""]))result(2*i,"sceKernelGetInitialRandomValue");
    else if(src.haz([""]))result(2*i,"sceKernelSetRebootKernel");
    else if(src.haz([""]))result(2*i,"sceKernelApiEvaluationInit");
    else if(src.haz([""]))result(2*i,"sceKernelRegisterApiEvaluation");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_1F7F7F40");
    else if(src.haz([""]))result(2*i,"sceKernelApiEvaluationReport");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_39351245");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_D2E3A399");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_4852F8DD");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_4EC43DC4");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_1F01A9E2");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_B9F8561C");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_9452B542");
    else if(src.haz([""]))result(2*i,"SysMemForKernel_EF2EE8C1");
		else if(src.haz([""]))result(2*i,"");
*/
		//<empty func>
		//sceKernelDevkitVersion
		//SysMemForKernel_536AD5E1
		//else if(src.haz([""]))result(2*i,"sceKernelPartitionMaxFreeMemSize");
		
//		else if(src.indexOf("0x800200D9")+1)result(2*i,"sceKernelAllocPartitionMemory");
//		else if(src.indexOf(" ^ arg2")+1)result(2*i,"SysMemForKernel_82D3CEE3");
//		else if(src.indexOf("<< UID list >>")+1)result(2*i,"sceKernelReleaseUID");
//		else if(src.indexOf("SysMemForKernel_82D3CEE3")+1)result(2*i,"sceKernelIsHold");
//		else if(src.match(/\(\(int \*\) var[0-9]+\)\[4\] = \(var[0-9]+ \+ 0x00000001\);/))result(2*i,"sceKernelHoldUID");
		else if(src.length==95)result(2*i,"<set>");
		else if(src.length==90&&(src.indexOf("= *")+1))result(2*i,"<get>");
		else if(src.length==90)result(2*i,"<get?>");//get but don't return ...
	}
	//print("\ntotal:"+exported+" solved:"+solved+" know:"+know+" %"+Math.round(100*(solved+know)/exported)+"\n");
}
function loadcore(){
	solved=0;
	know=0;
	for(l=0;l<res.length/2;l++){
		var src=res[2*l+1];
		if(res[2*l].indexOf("sub_")!=-1)continue;//skip stub
		if(src.length<59)result(2*l,"<empty>");
		else if(c("cache      0x4"))result(2*l,"sceKernelIcacheClearAll");
		else if(c("cache      0x14"))result(2*l,"sceKernelDcacheWBinvAll");
		else if(c(" == 0x5053507E"))result(2*l,"sceKernelCheckPspConfig");
		else if(c("[51] = 0xFFFFFFFF"))result(2*l,"sceKernelCreateModule");
		else if(c("(arg1, 0x00000000);"))result(2*l,"sceKernelRegisterLibrary");
		else if(c("(arg1, 0x00000001);"))result(2*l,"sceKernelRegisterLibraryForUser");
		else if(c("(arg1, arg2, 0x00000000);"))result(2*l,"sceKernelLinkLibraryEntries");
		else if(c("(arg1, arg2, 0x00000001)"))result(2*l,"sceKernelLinkLibraryEntriesForUser");
		else if(c("((arg1 < var1)) != 0x00000000"))result(2*l,"sceKernelUnLinkLibraryEntries");
		else if(c("((int *) arg1)[0] = 0x00000000;")&&c("arg1 == 0x00000000"))result(2*l,"sceKernelAssignModule");
		else if(c("var10 = LoadCoreForKernel")&&c("[18];"))result(2*l,"sceKernelGetLibraryLinkInfo");
		else if(c(") ? 0x00000000 : arg2"))result(2*l,"sceKernelGetLibraryList");
		else if(c("SceModmgrModuleList"))result(2*l,"sceKernelGetModuleListWithAlloc");
		else if(c("[0] = (arg1 + var"))result(2*l,"sceKernelSetBootCallbackLevel");
		else if(c("1)[30];")&&c(")[26];"))result(2*l,"sceKernelFindModuleByAddress2");
		else if(c("1)[30];"))result(2*l,"sceKernelFindModuleByAddress");
		else if(c("((unsigned short *) var5)[18]"))result(2*l,"sceKernelGetModuleIdListForKernel");
		else if(c("var6)[11];")&&c("var6)[0];"))result(2*l,"sceKernelFindModuleByName");
		else if(c("(var6 < arg5)"))result(2*l,"sceKernelApplyElfRelSection");
		else if(c("(arg6 <= 0)"))result(2*l,"sceKernelApplyPspRelSection");
		//else if(c("sp)[2] = ra")&&c(" while (1)"))result(2*l,"sceKernelReleaseLibrary");//find me
		else if(c("var4 = sub_")&&c("var5 = *((int *)")&&c("var5)[11]"))result(2*l,"sceKernelGetModuleFromUID");
		else if(c("var7 = ((int *) var5)[11];"))result(2*l,"sceKernelFindModuleByUID");
		else if(c("0x80020001")&&c("0x4543537E")&&c("0x8002014F"))result(2*l,"sceKernelCheckExecFile");
		else if(c(")[8]")&&c("((int *) arg1)[0]")&&c("sp)[0] = ra"))result(2*l,"sceKernelLoadExecutableObject");//var1 == 0x4543537E
		else if(c("var3 == 0x4543537E"))result(2*l,"sceKernelProbeExecutableObject");
		
	}
	print("\ntotal:"+exported+" solved:"+solved+" %"+Math.round(100*solved/exported)+"\n")
}
function loadexec_01g(){loadexec();}
function loadexec_02g(){loadexec();}
function loadexec_03g(){loadexec();}
function loadexec(){
	solved=0;
	know=0;
	for(l=0;l<res.length/2;l++){
		var src=res[2*l+1];
		if(!res[2*l].match(/[0-F]{6}$/))continue;//skip stub
		if(src.length<59)result(2*l,"<empty>");//sceKernelLoadExecFromHost
		else if(c("0x00000120"))result(2*l,"sceKernelLoadExecVSHDisc");
		else if(c("0x00000121"))result(2*l,"sceKernelLoadExecVSHDiscUpdater");
		else if(c("0x00000122"))result(2*l,"sceKernelLoadExecVSHDiscDebug");
		else if(c("0x00000123"))result(2*l,"sceKernelLoadExec_123");
		else if(c("0x00000124"))result(2*l,"sceKernelLoadExec_124");
		else if(c("0x00000125"))result(2*l,"sceKernelLoadExec_125");
		else if(c("0x00000126"))result(2*l,"sceKernelLoadExec_126");
		else if(c("0x00000130"))result(2*l,"sceKernelLoadExecBufferVSHUsbWlan");
		else if(c("0x00000131"))result(2*l,"sceKernelLoadExecBufferVSHUsbWlanDebug");
		else if(c("0x00000132"))result(2*l,"sceKernelLoadExecBuffer");
		else if(c("0x00000133"))result(2*l,"sceKernelLoadExecBuffer");
		else if(c("0x00000140"))result(2*l,"sceKernelLoadExecVSHMs1");
		else if(c("0x00000141"))result(2*l,"sceKernelLoadExecVSHMs2");
		else if(c("0x00000142"))result(2*l,"sceKernelLoadExecVSHMs3");
		else if(c("0x00000143"))result(2*l,"sceKernelLoadExecVSHMs4");
		else if(c("0x00000144"))result(2*l,"sceKernelLoadExecVSHMs5");
		else if(c("0x00000145"))result(2*l,"sceKernelLoadExecVSHMs6");
		else if(c("0x00000151"))result(2*l,"sceKernelLoadExecEF1");
		else if(c("0x00000152"))result(2*l,"sceKernelLoadExecEF2");
		else if(c("0x00000153"))result(2*l,"sceKernelLoadExecEF3");
		else if(c("0x00000154"))result(2*l,"sceKernelLoadExecEF4");
		else if(c("0x00000155"))result(2*l,"sceKernelLoadExecEF5");
		else if(c("0x00000156"))result(2*l,"sceKernelLoadExecEF6");
		else if(c("0x00000160"))result(2*l,"sceKernelLoadExec_160");
		else if(c("0x00000161"))result(2*l,"sceKernelLoadExec_161");
		else if(c("0x00000200"))result(2*l,"sceKernelLoadExec_200");
		else if(c("0x00000210"))result(2*l,"sceKernelExitGame");//sceKernelExitGameWithStatus
		else if(c("0x00000220"))result(2*l,"sceKernelExitVSHVSH");
		else if(c("0x8002014D"))result(2*l,"sceKernelInvokeExitCallback");
		else if(c("Thread"))result(2*l,"ThreadXXX");
		else if(src.length<100&&m(/\*\(\(int \*\) 0x[0-F]{8}\) = arg1;/))result(2*l,"sceKernelRegisterExitCallback");
		else if(src.length<100&&m(/\*\(\(int \*\) 0x[0-F]{8}\) = 0x00000000;/))result(2*l,"sceKernelUnregisterExitCallback");
		else if(src.length<100&&m(/var1 = \*\(\(int \*\) 0x[0-F]{8}\);/))result(2*l,"sceKernelCheckExitCallback");
		/*
			sceKernelExitVSHKernel
			sceKernelLoadExecVSHFromHost
			sceKernelLoadExecBufferVSHPlain
			sceKernelLoadExecBufferVSHFromHost
			sceKernelLoadExecBufferPlain0
			sceKernelLoadExecBufferPlain
			LoadExecForKernel_11412288
			LoadExecForKernel_6D8D3A3A
		*/
	}
	print("\ntotal:"+exported+" solved:"+solved+" %"+Math.round(100*solved/exported)+"\n")
}
function codec_01g(){codec();}
function codec_02g(){codec();}
function codec_03g(){codec();}
function codec(){
	solved=0;
	know=0;
	for(l=0;l<res.length/2;l++){
		var src=res[2*l+1];
		if(!res[2*l].match(/[0-F]{6}$/))continue;//skip stub
		if(src.length<59)result(2*l,"<empty>");//sceKernelLoadExecFromHost
		else if(c('"SceCodec"'))result(2*l,"sceCodecInitEntry");
		else if(c('arg1 == 0x0000AC44'))result(2*l,"sceCodecSetFrequency");
		else if(c(")[31]"))result(2*l,"sceCodecSetOutputVolume");
		else if(c("arg1 == 0x00000000")&&c("else"))result(2*l,"sceCodecSelectVolumeTable");
		else if(c("var1 = arg1")&&c("0x800001FE"))result(2*l,"sceCodecSetSpeakerVolume");
		else if(c("var1 = *((char *)")&&c("0x800001FE"))result(2*l,"sceCodecSetHeadphoneVolume");
		else if(c("(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF)"))result(2*l,"sceCodecStopEntry");
		else if(c("(0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000)"))result(2*l,"sceCodecInputDisable");
		else if(c("(0x00000000, 0x00000000, 0x00000001, 0x00000001)"))result(2*l,"sceCodecInputEnable");
		else if(c("(0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000)"))result(2*l,"sceCodecOutputDisable");
		else if(c("(((arg1 << 0x00000001) + 0xFFFFFFFF), ((arg2 << 0x00000001) + 0xFFFFFFFF), 0x00000000, 0x00000001)"))result(2*l,"sceCodecOutputEnable");
		else if(c(" << 0x00000005")&&c("sp)[4]"))result(2*l,"sceCodecSetVolumeOffset");
		//else if(c("sceCodec_driver_"))result(2*l,"?");
	}
	print("\ntotal:"+exported+" solved:"+solved+" %"+Math.round(100*solved/exported)+"\n")
}
function display_01g(){display();}
function display_02g(){display();}
function display_03g(){display();}
function display(){
	solved=0;
	know=0;
	for(var i=0;i<res.length/2;i++){
		var src=res[2*i+1];
		if(!res[2*i].match(/[0-F]{6}$/))continue;//skip stub
		else if(src.haz(["0x80000104"]))result(2*i,"sceDisplay_driver_63E22A26");
		else if(src.haz(["sceDisplay_driver_63E22A26 (0x00000002, arg1, arg2, arg3, arg4);"]))result(2*i,"sceDisplaySetFrameBuf");
		else if(src.haz(["sceLcdcGetVsyncFreq"]))result(2*i,"sceDisplayGetFramePerSec");
		//init: 0x........ = 0xFFFFFFFE -> foreground
		else if(src.haz(["if (!(((arg1 < 0x00000004)) == 0x00000000))"]))result(2*i,"sceCtrl_driver_5C56C779");
		else if(src.haz(["((arg1 ^ 0x00000001)) ? 0x00000000 : arg1"]))result(2*i,"sceCtrl_driver_348D99D4");//*((int *) 0x........) -> sceCtrl_driver_AF5960F3
	}
	print("\ntotal:"+res.length/2+" solved:"+solved+" %"+Math.round(100*solved/(res.length/2))+"\n");
}
function me_wrapper(){
	solved=0;
	know=0;
	for(var i=0;i<res.length/2;i++){
		var src=res[2*i+1];
		if(!res[2*i].match(/[0-F]{6}$/))continue;//skip stub
		else if(src.haz(["flash0:/kd/resource/meimg.img"]))result(2*i,"sceMeBootStart");
	}
	print("\ntotal:"+res.length/2+" solved:"+solved+" %"+Math.round(100*solved/(res.length/2))+"\n");
}
function audio(){
	solved=0;
	know=0;
	for(var i=0;i<res.length/2;i++){
		var src=res[2*i+1];
		if(!res[2*i].match(/[0-F]{6}$/))continue;//skip stub
		else if(src.haz(['"SceAudio"']))result(2*i,"sceAudioInit");
		else if(src.haz(["0xBE000040) = 0x00000001"]))result(2*i,"sceAudioSetFrequency");
		else if(src.haz(["(0x00000000, 0x00000000);"]))result(2*i,"sceAudioEnd");
		else if(src.haz(["(((arg1 << 0x00000001) + arg1) << 0x00000001)"]))result(2*i,"sceAudioSetVolumeOffset");
		else if(src.haz(["*((int *) 0xBE000004) = 0x00000007;"]))result(2*i,"sceAudioLoopbackTest");
		else if(src.haz(["*((int *) 0xBE000004) = 0x00000007;"]))result(2*i,"sceAudioLoopbackTest");
	}
	print("\ntotal:"+res.length/2+" solved:"+solved+" %"+Math.round(100*solved/(res.length/2))+"\n");
}
function lowio(){
	solved=0;
	know=80;//there know nid never change...
	//1st pass:find some master subroutine:
	//08//clk:     :0xBC100054,0x00000000 < var
	//32//busClock::0xBC100050
	//22//reset:   :0xBC10004C) =
	//20//clckEn   :0xBC100058
	//26//io       :0xBC100078
	for(var i=0;i<res.length/2;i++){
		var name=res[2*i+0];
		var src =res[2*i+1];
		if(!name.match(/[0-F]{6}$/)){
			     if(src.haz(["0xBC10004C) ="])){res.replace(name,"reset");}
			else if(src.haz(["0xBC100050"])){res.replace(name,"busClock");}
			else if(src.haz(["0xBC100054","0x00000000 < var"])){res.replace(name,"clck");}
			else if(src.haz(["0xBC100058"])){res.replace(name,"clckEn");}
			else if(src.haz(["0xBC100078"])){res.replace(name,"io");}
		}
	}
	//2nd pass 
	for(var i=0;i<res.length/2;i++){
		var name=res[2*i+0];
		var src =res[2*i+1];
		if(!name.match(/[0-F]{6}$/))continue;
		//if(src.length<59)result(2*i,"<empty>");
//ddr
		else if(src.haz(["*((int *) 0xBD000020) = (arg1 | 0x00008000);"]))result(2*i,"sceDdrExecSeqCmd");
		else if(src.haz(["*((int *) 0xBD00002C) = ((((arg1"]))result(2*i,"sceDdrSetPowerDownCounter");
		else if(src.haz(["*((int *) 0xBD000040) = 0x0000002B;"])&&src.length<500)result(2*i,"sceDdrWriteMaxAllocate");
		else if(src.haz([" = *((int *) 0xBD00002C);"]))result(2*i,"sceDdrGetPowerDownCounter");
		else if(src.haz(["(0x00000025, 0x00000000, 0x00000000)"]))result(2*i,"sceDdrResetDevice");
		else if(src.haz(["sceDdrResetDevice ("]))result(2*i,"sceDdrSetup");
		else if(src.haz(["sceDdrFlush ("]))result(2*i,"sceDdrChangePllClock");
		else if(src.haz([" | 0x00000031) ^ 0x00000031) | "]))result(2*i,"sceDdr_driver_19423D2C");
		else if(src.haz([" = *((int *) 0xBD000030);"])&&src.length<100)result(2*i,"sceDdr_driver_F23B7983");
		else if(src.haz(["*((int *) 0xBD000034) = ("]))result(2*i,"sceDdr_driver_D341BACD");
		else if(src.haz(["*((int *) 0xBD000040) = (arg2 | 0x00000010);"]))result(2*i,"sceDdr_driver_6955346C");
//dmacplus
		else if((src.length==96)&&(src.indexOf("*((int *) 0xBC800160) = 0x00000000;")+1))result(2*i,"sceDmacplusAvcSuspend");
		else if(src.haz(["0x80000108","0x80000104","0x80000021"]))result(2*i,"sceDmacplusLcdcSetFormat");
		else if(src.haz(["(0xA0000000 & 0xE0000000)"]))result(2*i,"sceDmacplusSc128LLI");
		else if(src.haz(["(0x00000009)"]))result(2*i,"sceDmacplusSc128Suspend");
		else if(src.haz(["0x81909000"]))result(2*i,"sceDmacplusMe2ScNormal16");
		else if(src.haz(["*((int *) 0xBC8001A8) = "]))result(2*i,"sceDmacplusMe2ScLLI");
		else if(src.haz(["if (!(arg3 == 0x00000000))","var3 = *((int *) 0x0000"])&&src.length<400)result(2*i,"sceDmacplusLcdcGetFormat");
		else if(src.haz(["0xBC800110","0xBC800100","0xBC80010C","0x00007FFF","0x80000103"]))result(2*i,"sceDmacplusLcdcSetBaseAddr");
		else if(src.haz(["0xBC800110","0xBC800100","0xBC80010C","0x00007FFF"]))result(2*i,"sceDmacplusLcdcEnable");//sceKernelCpuSuspendIntr ();\n    var6 = *((int *) 0x........); -> sceDmacplusLcdcGetBaseAddr
		else if(src.haz(["(0x00000015, 0x00000001);"])&&src.length<400)result(2*i,"sceDmacplusLcdcDisable");
		else if(src.haz(["*((int *) 0xBC800110) = 0x00000002;"]))result(2*i,"sceDmacplusLcdcResume");
		else if(src.haz(["*((int *) 0xBC800110) = 0x00000000;"]))result(2*i,"sceDmacplusLcdcSuspend");
		else if(src.haz(["*((int *) 0xBC800150) = var1;"]))result(2*i,"sceDmacplusAvcResume");
		else if(src.haz(["(arg1, arg2, arg3, 0x00000001);"]))result(2*i,"sceDmacplusSc128TryMemcpy");
		else if(src.haz(["(arg1, arg2, arg3, 0x00000000);"]))result(2*i,"sceDmacplusSc128Memcpy");
		else if(src.haz(["*((int *) 0xBC800010) = ("]))result(2*i,"sceDmacplusAcquireIntr");
		else if(src.haz(["sceKernelEnableIntr (0x00000015);"]))result(2*i,"sceDmacplusInit");
		else if(src.haz(["sceKernelEnableSubIntr (0x00000015, 0x00000001);"]))result(2*i,"sceDmacplusLcdcInit");
		else if(src.haz(["sceKernelEnableSubIntr (0x00000015, 0x00000003);"]))result(2*i,"sceDmacplusAvcInit");//get memset(0x........ -> sceDmacplusAvcSync
		else if(src.haz(["sceKernelEnableSubIntr (0x00000015, 0x00000005);"]))result(2*i,"sceDmacplusSc2MeInit");
		else if(src.haz(["sceKernelEnableSubIntr (0x00000015, 0x00000007);"]))result(2*i,"sceDmacplusMe2ScInit");
		else if(src.haz(["sceKernelEnableSubIntr (0x00000015, 0x00000009);"]))result(2*i,"sceDmacplusSc128Init");
		else if(src.haz(["sceKernelReleaseSubIntrHandler (0x00000015, 0x00000009);"]))result(2*i,"sceDmacplusSc128End");//8 9
		else if(src.haz(["sceKernelReleaseSubIntrHandler (0x00000015, 0x00000007);"]))result(2*i,"sceDmacplusMe2ScEnd");//6 7
		else if(src.haz(["sceKernelReleaseSubIntrHandler (0x00000015, 0x00000005);"]))result(2*i,"sceDmacplusSc2MeEnd");//4 5
		else if(src.haz(["sceKernelReleaseSubIntrHandler (0x00000015, 0x00000003);"]))result(2*i,"sceDmacplusAvcEnd");//2 3
		else if(src.haz(["sceKernelReleaseSubIntrHandler (0x00000015, 0x00000001);"]))result(2*i,"sceDmacplusLcdcEnd");//1
		else if(src.haz(["& 0xFFFFFFF7) | ("]))result(2*i,"sceDmacplusMe2ScSync");
		else if(src.haz(["*((int *) 0xBC800188) = 0x00000000;"]))result(2*i,"sceDmacplusSc2MeNormal16");//1
		else if(src.haz(["*((int *) 0xBC800190) = 0x0000C001;"]))result(2*i,"sceDmacplusSc2MeLLI");//2
		else if(src.haz(["sceKernelReleaseIntrHandler (0x00000015);"]))result(2*i,"sceDmacplusEnd");
//sysreg
		//else if(src.haz(["var1 = *((int *) 0xBC100080);"])&&src.length<100)result(2*i,"sceSysregUsbGetConnectStatus/sceSysregUsbQueryIntr");
		//else if(src.haz(["var1 = *((int *) 0xBC100080);"])&&src.length<500)result(2*i,"sceSysregMsifGetConnectStatus/sceSysregMsifQueryConnectIntr");
		//sceSysregAudioClkSelect//
		//sceSysregKeyIoEnable//
		//sceSysregKeyIoDisable//
		//sceSysregKeyClkEnable//
		//sceSysregKeyClkDisable//
		//sceSysregEnableIntr//
		//sceSysregDisableIntr//
		else if(src.haz(["0x80000107"," = *((int *) 0xBC10003C);"]))result(2*i,"sceSysregDoTimerEvent");
		else if(src.haz([" = *((int *) 0xBC100080)"])&&src.length<100)result(2*i,"sceSysregUsbGetConnectStatus/sceSysregUsbQueryIntr");
		else if(src.haz([">> 1) & 0x0000000F"])&&src.length>100)result(2*i,"sceSysregUsbAcquireIntr");
		else if(src.haz(["0xBC100080","sceKernelCpuResumeIntrWithSync"]))result(2*i,"sceSysregIntrInit");
		else if(src.haz(["sceKernelRegisterIntrHandler (0x0000001F"]))result(2*i,"sceSysregIntrEnd");
		else if(src.haz(["0xBC100044) = 0x00000001"]))result(2*i,"sceSysregInterruptToOther");
		else if(src.haz(["0xBC100048) = var"]))result(2*i,"sceSysregSemaTryLock");
		else if(src.haz(["0xBC100048) = 0x00000000"]))result(2*i,"sceSysregSemaUnlock");
		else if(src.haz(["(arg1, 0x00000000)"]))result(2*i,"sceSysregGpioIoDisable");
		else if(src.haz(["(arg1, 0x00000001)"]))result(2*i,"sceSysregGpioIoEnable");
		else if(src.haz(["io (0x00000004, 0x00000001)"]))result(2*i,"sceSysregUsbIoEnable");
		else if(src.haz(["io (0x00000004, 0x00000000)"]))result(2*i,"sceSysregUsbIoDisable");
		else if(src.haz(["io (0x00000008, 0x00000001)"]))result(2*i,"sceSysregAtaIoEnable");
		else if(src.haz(["io (0x00000008, 0x00000000)"]))result(2*i,"sceSysregAtaIoDisable");
		else if(src.haz(["io ((0x00000010 << arg1), 0x00000001)"]))result(2*i,"sceSysregMsifIoEnable");
		else if(src.haz(["io ((0x00000010 << arg1), 0x00000000)"]))result(2*i,"sceSysregMsifIoDisable");
		else if(src.haz(["io (0x00000040, 0x00000001)"]))result(2*i,"sceSysregLcdcIoEnable");
		else if(src.haz(["io (0x00000040, 0x00000000)"]))result(2*i,"sceSysregLcdcIoDisable");
		else if(src.haz(["io ((0x00000080 << arg1), 0x00000001)"]))result(2*i,"sceSysregAudioIoEnable");
		else if(src.haz(["io ((0x00000080 << arg1), 0x00000000)"]))result(2*i,"sceSysregAudioIoDisable");
		else if(src.haz(["io (0x00000200, 0x00000001)"]))result(2*i,"sceSysregIicIoEnable");
		else if(src.haz(["io (0x00000200, 0x00000000)"]))result(2*i,"sceSysregIicIoDisable");
		else if(src.haz(["io (0x00000800, 0x00000001)"]))result(2*i,"sceSysregAudioClkoutIoEnable");
		else if(src.haz(["io (0x00000800, 0x00000000)"]))result(2*i,"sceSysregAudioClkoutIoDisable");
		else if(src.haz(["io (0x00002000, 0x00000001)"]))result(2*i,"sceSysregPwmIoEnable");
		else if(src.haz(["io (0x00002000, 0x00000000)"]))result(2*i,"sceSysregPwmIoDisable");
		else if(src.haz(["busClock (0x00000001, 0x00000001)"]))result(2*i,"sceSysregMeBusClockEnable");
		else if(src.haz(["busClock (0x00000001, 0x00000000)"]))result(2*i,"sceSysregMeBusClockDisable");
		else if(src.haz(["busClock (0x00000002, 0x00000001)"]))result(2*i,"sceSysregAwRegABusClockEnable");
		else if(src.haz(["busClock (0x00000002, 0x00000000)"]))result(2*i,"sceSysregAwRegABusClockDisable");
		else if(src.haz(["busClock (0x00000004, 0x00000001)"]))result(2*i,"sceSysregAwRegBBusClockEnable");
		else if(src.haz(["busClock (0x00000004, 0x00000000)"]))result(2*i,"sceSysregAwRegBBusClockDisable");
		else if(src.haz(["busClock (0x00000008, 0x00000001)"]))result(2*i,"sceSysregAwEdramBusClockEnable");
		else if(src.haz(["busClock (0x00000008, 0x00000000)"]))result(2*i,"sceSysregAwEdramBusClockDisable");
		else if(src.haz(["busClock (0x00000010, 0x00000001)"]))result(2*i,"sceSysregDmacplusBusClockEnable");
		else if(src.haz(["busClock (0x00000010, 0x00000000)"]))result(2*i,"sceSysregDmacplusBusClockDisable");
		else if(src.haz(["busClock ((0x00000020 << arg1), 0x00000001)"]))result(2*i,"sceSysregDmacBusClockEnable");
		else if(src.haz(["busClock ((0x00000020 << arg1), 0x00000000)"]))result(2*i,"sceSysregDmacBusClockDisable");
		else if(src.haz(["busClock (0x00000080, 0x00000001)"]))result(2*i,"sceSysregKirkBusClockEnable");
		else if(src.haz(["busClock (0x00000080, 0x00000000)"]))result(2*i,"sceSysregKirkBusClockDisable");
		else if(src.haz(["busClock (0x00000200, 0x00000001)"]))result(2*i,"sceSysregUsbBusClockEnable");
		else if(src.haz(["busClock (0x00000200, 0x00000000)"]))result(2*i,"sceSysregUsbBusClockDisable");
		else if(src.haz(["busClock ((0x00000400 << arg1), 0x00000001)"]))result(2*i,"sceSysregMsifBusClockEnable");
		else if(src.haz(["busClock ((0x00000400 << arg1), 0x00000000)"]))result(2*i,"sceSysregMsifBusClockDisable");
		else if(src.haz(["busClock (0x00001000, 0x00000001)"]))result(2*i,"sceSysregEmcddrBusClockEnable");
		else if(src.haz(["busClock (0x00001000, 0x00000000)"]))result(2*i,"sceSysregEmcddrBusClockDisable");
		else if(src.haz(["busClock (0x00004000, 0x00000001)"]))result(2*i,"sceSysregApbBusClockEnable");
		else if(src.haz(["busClock (0x00004000, 0x00000000)"]))result(2*i,"sceSysregApbBusClockDisable");
		else if(src.haz(["busClock ((0x00008000 << arg1), 0x00000001)"]))result(2*i,"sceSysregAudioBusClockEnable");
		else if(src.haz(["busClock ((0x00008000 << arg1), 0x00000000)"]))result(2*i,"sceSysregAudioBusClockDisable");
		else if(src.haz(["clckEn ((0x00001000 << arg1), 0x00000001)"]))result(2*i,"sceSysregApbTimerClkEnable");
		else if(src.haz(["clckEn ((0x00001000 << arg1), 0x00000000)"]))result(2*i,"sceSysregApbTimerClkDisable");
		else if(src.haz(["clckEn (0x00040000, 0x00000001)"]))result(2*i,"sceSysregLcdcClkEnable");
		else if(src.haz(["clckEn (0x00040000, 0x00000000)"]))result(2*i,"sceSysregLcdcClkDisable");
		else if(src.haz(["clckEn (0x00080000, 0x00000001)"]))result(2*i,"sceSysregPwmClkEnable");
		else if(src.haz(["clckEn (0x00080000, 0x00000000)"]))result(2*i,"sceSysregPwmClkDisable");
		else if(src.haz(["clckEn ((0x00010000 << arg1), 0x00000001)"]))result(2*i,"sceSysregAudioClkEnable");
		else if(src.haz(["clckEn ((0x00010000 << arg1), 0x00000000)"]))result(2*i,"sceSysregAudioClkDisable");
		else if(src.haz(["clckEn (0x00200000, 0x00000001)"]))result(2*i,"sceSysregIicClkEnable");
		else if(src.haz(["clckEn (0x00200000, 0x00000000)"]))result(2*i,"sceSysregIicClkDisable");
		else if(src.haz(["clckEn (0x00800000, 0x00000001)"]))result(2*i,"sceSysregGpioClkEnable");
		else if(src.haz(["clckEn (0x00800000, 0x00000000)"]))result(2*i,"sceSysregGpioClkDisable");
		else if(src.haz(["clckEn (0x01000000, 0x00000001)"]))result(2*i,"sceSysregAudioClkoutClkEnable");
		else if(src.haz(["clckEn (0x01000000, 0x00000000)"]))result(2*i,"sceSysregAudioClkoutClkDisable");
		else if(src.haz(["reset (0x00000001, 0x00000001)"]))result(2*i,"sceSysregTopResetEnable");
		else if(src.haz(["reset (0x00000002, 0x00000001)"]))result(2*i,"sceSysregScResetEnable");
		else if(src.haz(["reset (0x00000004, 0x00000001)"]))result(2*i,"sceSysregMeResetEnable");
		else if(src.haz(["reset (0x00000004, 0x00000000)"]))result(2*i,"sceSysregMeResetDisable");
		else if(src.haz(["reset (0x00000008, 0x00000001)"]))result(2*i,"sceSysregAwResetEnable");
		else if(src.haz(["reset (0x00000008, 0x00000000)"]))result(2*i,"sceSysregAwResetDisable");
		else if(src.haz(["reset (0x00000010, 0x00000001)"]))result(2*i,"sceSysregVmeResetEnable");
		else if(src.haz(["reset (0x00000010, 0x00000000)"]))result(2*i,"sceSysregVmeResetDisable");
		else if(src.haz(["reset (0x00000020, 0x00000001)"]))result(2*i,"sceSysregAvcResetEnable");
		else if(src.haz(["reset (0x00000020, 0x00000000)"]))result(2*i,"sceSysregAvcResetDisable");
		else if(src.haz(["reset (0x00000040, 0x00000001)"]))result(2*i,"sceSysregUsbResetEnable");
		else if(src.haz(["reset (0x00000040, 0x00000000)"]))result(2*i,"sceSysregUsbResetDisable");
		else if(src.haz(["reset (0x00000080, 0x00000001)"]))result(2*i,"sceSysregAtaResetEnable");
		else if(src.haz(["reset (0x00000080, 0x00000000)"]))result(2*i,"sceSysregAtaResetDisable");
		else if(src.haz(["reset ((0x00000100 << arg1), 0x00000001)"]))result(2*i,"sceSysregMsifResetEnable");
		else if(src.haz(["reset ((0x00000100 << arg1), 0x00000000)"]))result(2*i,"sceSysregMsifResetDisable");
		else if(src.haz(["reset (0x00000400, 0x00000001)"]))result(2*i,"sceSysregKirkResetEnable");
		else if(src.haz(["reset (0x00000400, 0x00000000)"]))result(2*i,"sceSysregKirkResetDisable");
		else if(src.haz(["clck (((arg1 & 0x0000000F) << 0x00000004), 0x00000001)"]))result(2*i,"sceSysregUsbClkEnable");
		else if(src.haz(["clck (((arg1 & 0x0000000F) << 0x00000004), 0x00000000)"]))result(2*i,"sceSysregUsbClkDisable");
		else if(src.haz(["clck (0x00000001, 0x00000001)"]))result(2*i,"sceSysregAtaClkEnable");
		else if(src.haz(["clck (0x00000001, 0x00000000)"]))result(2*i,"sceSysregAtaClkDisable");
		else if(src.haz(["clck ((0x00000100 << arg1), 0x00000001)"]))result(2*i,"sceSysregMsifClkEnable");
		else if(src.haz(["clck ((0x00000100 << arg1), 0x00000000)"]))result(2*i,"sceSysregMsifClkDisable");
		else if(src.haz(["var1 = *((int *) 0xBC100068);"," = *((int *) 0xBC1000FC);"]))result(2*i,"sceSysregPllUpdateFrequency");
//		else if(src.haz(["lwc1       $fpr00, 11264($v1);"]))result(2*i,"sceSysregPllGetFrequency");
		else if(src.haz(["var1 = *((int *) 0xBC100068);"]))result(2*i,"sceSysregPllGetOutSelect");
//		else if(src.haz(["lwc1       $fpr00, 11120($v1);"]))result(2*i,"sceSysregPllGetBaseFrequency");
		else if(src.haz(["(arg2 << 0x00000014)"]))result(2*i,"sceSysregLcdcClkSelect");
		else if(src.haz(["var1) | 0x00000080"]))result(2*i,"sceSysregPllSetOutSelect");
		else if(src.haz(["(arg1 << 0x00000004)"]))result(2*i,"sceSysregAtaClkSelect");
		else if(src.haz(["(arg1 << 0x00000012)"]))result(2*i,"sceSysregAudioClkoutClkSelect");
		else if(src.haz(["(arg1 < 0x00000006)","(arg2 < 0x00000008)"]))result(2*i,"sceSysregSpiClkSelect");
		else if(src.haz(["(arg1 < 0x00000004)","(arg2 < 0x00000008)"]))result(2*i,"sceSysregApbTimerClkSelect");
		else if(src.haz(["(arg1 < 0x00000002)","(arg2 < 0x00000008)"]))result(2*i,"sceSysregMsifDelaySelect");
		else if(src.haz(["0xFFFFFFCF"]))result(2*i,"sceSysregMsifClkSelect");
		else if(src.haz(["sceSysregInterruptToOther"]))result(2*i,"sceSysregRequestIntr");//last
//pwm
		else if(name.match(/scePwm/)&&src.haz(["sceSysregPwmIoDisable"]))result(2*i,"scePwmSuspend");
		else if(name.match(/scePwm/)&&src.haz(["0xBE300000","sceKernelRegisterSysEventHandler"]))result(2*i,"scePwmInit");
		else if(name.match(/scePwm/)&&src.haz(["sceKernelUnregisterSysEventHandler"]))result(2*i,"scePwmEnd");
		else if(name.match(/scePwm/)&&src.haz(["0x00000005) + 0xBE300000)"]))result(2*i,"scePwmIsLoading");
		else if(name.match(/scePwm/)&&src.haz(["0x80000021","arg4"]))result(2*i,"scePwmStart");//1st
		else if(name.match(/scePwm/)&&src.haz(["0x80000021"]))result(2*i,"scePwmChangeDuty");//2nd
		else if(name.match(/scePwm/)&&src.haz(["sceSysregPwmClkEnable"]))result(2*i,"scePwmResume");//2nd
		//else if(name.match(/scePwm/)&&src.haz([""]))result(2*i,"scePwmStop");
		//else if(name.match(/scePwm/)&&src.haz([""]))result(2*i,"scePwmReferDuty");
//i2c
		else if(src.haz(["sceKernelRegisterIntrHandler (0x0000000C"]))result(2*i,"sceI2cInit");
		else if(src.haz(["sceKernelReleaseIntrHandler (0x0000000C)"]))result(2*i,"sceI2cEnd");
		//sceI2cSuspend//sceSysregIicClkDisable
		//sceI2cResume//sceSysregIicClkEnable
		 //sceI2cSetClock//= arg2;
		//sceI2cSetDebugHandlers/sceI2cSetPollingMode// = arg1;
		//sceI2cReset//*((int *) 0xBE200020) = 0x00000001;
		//sceI2cMasterTransmitReceive
		//sceI2cMasterTransmit 0x80000104
		//sceI2cMasterReceive  0x80000104
//lcdc
		else if(name.match(/sceLcdc/)&&src.haz(["0x80000107"]))result(2*i,"sceLcdcCheckMode");
		//sceLcdcSetMode//sceLcdcCheckMode
		//sceLcdcInit//sceKernelRegisterSysEventHandler
		//sceLcdcEnd//sceKernelUnregisterSysEventHandler
		//sceLcdc_driver_E08B076B//*((int *) 0xBE140050)
		//sceLcdcSuspend//size<200 && sceSysregLcdcClkDisable//1
		//sceLcdcDisable//sceLcdcDisable//2
		//sceLcdcResume
		//sceLcdcEnable
		//sceLcdcReset
		//sceLcdcGetPixelClockFreq
		//sceLcdcGetHsyncFreq// = (var1 << 0x00000002) | var2,mov.s
		//sceLcdcGetVsyncFreq
		//sceLcdcReadHPC
		//sceLcdcReadVPC
	}
	print("\ntotal:"+exported+" solved:"+solved+" know:"+know+" %"+Math.round(100*(solved+know)/exported)+"\n");
//	print(res);
}
function countExport(){
	var exp=0;
	for(var i=0;i<res.length-1;i+=2)
		if(res[i].match(/[0-F]{8}$/))exp++
	return exp;
}
function parse(str){
	str = str.replace(/\r/g,'');
	str = str.replace("pspsdk.h","");//hack for later file detection
	res = str.split(/\n[\w]+ ([\w]+) \(.*?\)\n/g);
	var modName = res[0].match(/([\w]+)\.h/)[1];
	print("origin filename : "+res[0].match(/([\w]+)\.h/)[1]+".prx\n");
	res.shift();
	exported= countExport();
	print("sub:"+(((res.length-1)>>1)-exported)+" export:"+exported+" total: "+((res.length-1)>>1) +"\n\n");
	eval(modName+"()");
	//eval(modName+"()");//need a 2nd pass ?
	//print(str.match(/[a-z]+/g).join("\n"));
}
