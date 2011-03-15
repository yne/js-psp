#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <psputility.h>
#include <psputility_msgdialog.h>
#include <psputility_netconf.h>
#include <psputility_netparam.h>
#include <psputility_savedata.h>
#include <psputility_gamesharing.h>
#include <psputility_htmlviewer.h>
#include <psputility_sysparam.h>
#include <psputility_osk.h>
#include <psputility_netmodules.h>
#include <psputility_avmodules.h>
#include <psputility_usbmodules.h>
#include <psputility_modules.h>

#include "../gu/pspgu.h"
#include "../../main/shared.h"

PSP_MODULE_INFO("sceUtility",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();
PSP_HEAP_SIZE_KB(0);

/* modules */
JS_FUN(LoadModule){
	*rval = I2J(sceUtilityLoadAvModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(UnloadModule){
	*rval = I2J(sceUtilityUnloadAvModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(LoadAvModule){
	*rval = I2J(sceUtilityLoadAvModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(UnloadAvModule){
	*rval = I2J(sceUtilityUnloadAvModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(LoadUsbModule){
	*rval = I2J(sceUtilityLoadUsbModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(UnloadUsbModule){
	*rval = I2J(sceUtilityUnloadUsbModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(LoadNetModule){
	*rval = I2J(sceUtilityLoadNetModule(J2I(argv[0])));
	return JS_TRUE;
}
JS_FUN(UnloadNetModule){
	*rval = I2J(sceUtilityUnloadNetModule(J2I(argv[0])));
	return JS_TRUE;
}
/* Common */
pspUtilityDialogCommon objectToBase(JSObject* bobj,pspUtilityDialogCommon* base,size_t size){
	int value;//used to store result from get sys param;
	
	int doy=0;
	if((u32)bobj==0x80000000)doy=1;//base object object not specified

	base->size=size;
	if(!doy)base->language=J2I(js_getProperty(bobj,"language"));
	if(doy||base->language==UNDEFINED){
		sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,&value);
		base->language = value;
	}
	if(!doy)base->buttonSwap=J2I(js_getProperty(bobj,"buttonSwap"));
	if(doy||base->buttonSwap==UNDEFINED){
		sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,&value);
		base->buttonSwap = value;
	}
	if(!doy)base->soundThread=J2I(js_getProperty(bobj,"soundThread"));
	if(doy||base->soundThread==UNDEFINED)base->soundThread=16;
	if(!doy)base->graphicsThread=J2I(js_getProperty(bobj,"graphicsThread"));
	if(doy||base->graphicsThread==UNDEFINED)base->graphicsThread=17;
	if(!doy)base->fontThread=J2I(js_getProperty(bobj,"fontThread"));
	if(doy||base->fontThread==UNDEFINED)base->fontThread=18;
	if(!doy)base->accessThread=J2I(js_getProperty(bobj,"accessThread"));
	if(doy||base->accessThread==UNDEFINED)base->accessThread=19;
	//base->result=J2I(js_getProperty(bobj,"result"));
	return *base;
}
/* Game sharing */
pspUtilityGameSharingParams sharing;
JS_FUN(GameSharingInitStart){
	JSObject* param = J2O(argv[0]);
	memset(&sharing,0,sizeof(sharing));//set all unknow parameter to 0
	pspUtilityDialogCommon base;
	sharing.base=objectToBase(J2O(js_getProperty(param,"base")),&base,sizeof(sharing));
	//int reserved1;
	//int reserved2;
	memcpy(sharing.name,J2S(js_getProperty(param,"name")),8);
	//reserved3;
	//optarg;
	//uploadFunc(void*, const char**, int *);
	//result
	sharing.filepath=J2S(js_getProperty(param,"filepath"));
	sharing.mode=J2I(js_getProperty(param,"mode"));
  sharing.datatype=J2I(js_getProperty(param,"datatype"));
  sharing.data=(void*)J2S(js_getProperty(param,"datatype"));
	sharing.datasize=J2I(js_getProperty(param,"datasize"));
	*rval = I2J(sceUtilityGameSharingInitStart(&sharing));
	return JS_TRUE;
}
JS_FUN(GameSharingUpdate){
	sceUtilityGameSharingUpdate(1);
	return JS_TRUE;
}
JS_FUN(GameSharingShutdownStart){
	sceUtilityGameSharingShutdownStart();
	return JS_TRUE;	
}
JS_FUN(GameSharingGetStatus){
	*rval = I2J(sceUtilityGameSharingGetStatus());//NONE:0;INIT:1;VISIBLE:2;QUIT:3;FINISHED:4;
	return JS_TRUE;	
}
/* Msg Dialog */
pspUtilityMsgDialogParams dialog;
JS_FUN(MsgDialogInitStart){
	JSObject* param = J2O(argv[0]);
	memset(&dialog,0,sizeof(dialog));
	pspUtilityDialogCommon base;
	dialog.base=objectToBase(J2O(js_getProperty(param,"base")),&base,sizeof(dialog));
	dialog.mode=J2I(js_getProperty(param,"mode"));
	dialog.options=J2I(js_getProperty(param,"options"));
  dialog.errorValue=J2I(js_getProperty(param,"errorValue"));
	dialog.buttonPressed=0;
	char* msg = J2S(js_getProperty(param,"message"));
	//printf("msg:%s\n\n",msg);
	strncpy(dialog.message,msg,512);
	*rval = I2J(sceUtilityMsgDialogInitStart(&dialog));
	return JS_TRUE;	
}
JS_FUN(MsgDialogUpdate){
	sceUtilityMsgDialogUpdate(1);
	return JS_TRUE;	
}
JS_FUN(MsgDialogGetStatus){
	*rval = I2J(sceUtilityMsgDialogGetStatus());
	return JS_TRUE;	
}
JS_FUN(MsgDialogAbort){
	*rval = I2J(sceUtilityMsgDialogAbort());
	return JS_TRUE;	
}
JS_FUN(MsgDialogShutdownStart){
	sceUtilityMsgDialogShutdownStart();
	return JS_TRUE;	
}
JS_FUN(MsgDialogPressed){
	*rval = I2J(dialog.buttonPressed);
	return JS_TRUE;	
}
/* System param */
JS_FUN(GetSystemParamInt){
	int value;
	sceUtilityGetSystemParamInt(J2I(argv[0]), &value);
	*rval = I2J(value);
	return JS_TRUE;
}
JS_FUN(SetSystemParamInt){
	*rval = I2J(sceUtilitySetSystemParamInt(J2I(argv[0]),J2I(argv[1])));
	return JS_TRUE;
}
JS_FUN(GetSystemParamString){
	char* ParamString = js_malloc(25);
	sceUtilityGetSystemParamString(J2I(argv[0]),ParamString,25);
	*rval = STRING_TO_JSVAL(js_newString(ParamString,0));//0 = strlen
	return JS_TRUE;
}
JS_FUN(SetSystemParamString){
	*rval = I2J(sceUtilitySetSystemParamString(J2I(argv[0]),J2S(argv[0])));//0x80110103
	return JS_TRUE;
}
/* Netconf */
typedef struct _pspUtilityNetconfAdhoc{
	unsigned char name[8];
	unsigned int timeout;
} pspUtilityNetconfAdhoc;
pspUtilityNetconfData Netconf;
struct pspUtilityNetconfAdhoc adhocparam;
JS_FUN(NetconfInitStart){
	JSObject* param = J2O(argv[0]);
	memset(&Netconf,0,sizeof(Netconf));
	pspUtilityDialogCommon base;
	Netconf.base=objectToBase(J2O(js_getProperty(param,"base")),&base,sizeof(Netconf));
	Netconf.action=J2I(js_getProperty(param,"action"));
	if(Netconf.action==PSP_NETCONF_ACTION_CONNECT_ADHOC){
		memset(&adhocparam, 0, sizeof(adhocparam));
		memcpy(&adhocparam.name, "GameShar", 8);
		adhocparam.timeout = 60;
		Netconf.adhocparam = &adhocparam;

	/*
		JSObject* aparam = J2O(js_getProperty(param,"adhocparam"));
		memcpy(adhocparam.name,J2S(js_getProperty(aparam,"name")),8);
		adhocparam.timeout=J2I(js_getProperty(aparam,"timeout"));
		Netconf.adhocparam = (void*)&adhocparam;
		Netconf.hotspot=J2I(js_getProperty(param,"hotspot"));
		Netconf.hotspot_connected=J2I(js_getProperty(param,"hotspot_connected"));
		Netconf.wifisp=J2I(js_getProperty(param,"wifisp"));
	*/
	}
	*rval = I2J(sceUtilityNetconfInitStart(&Netconf));
	return JS_TRUE;	
}
JS_FUN(NetconfShutdownStart){
	*rval = I2J(sceUtilityNetconfShutdownStart());
	return JS_TRUE;	
}
JS_FUN(NetconfUpdate){
	*rval = I2J(sceUtilityNetconfUpdate(J2I(argv[0])));//index of the next frame to draw
	return JS_TRUE;	
}
JS_FUN(NetconfGetStatus){
	*rval = I2J(sceUtilityNetconfGetStatus());
	return JS_TRUE;	
}
/* OSK */
SceUtilityOskParams OskParams;
char* packUIStr(unsigned short* int_str, char* chr_str, int string_size) { //Converts and int string to a char string. (OSK)
	int c;
	memset(chr_str, 0, string_size);
	for(c = 0; int_str[c]; c++)
		chr_str[c] = int_str[c];
	return chr_str;
}
unsigned short* expandChrStr(char* chr_str, unsigned short* int_str) { //Converts a char string to an int string. (OSK)
  int c;
  memset(int_str, 0, (sizeof(unsigned short)*strlen(chr_str))+1);
	for(c = 0; chr_str[c]; c++)
    int_str[c] = chr_str[c];
	return int_str;
}
// i dunno how to dynamicaly malloc a unsigned short* and handle it ...
unsigned short desc[128];
unsigned short intext[512];
unsigned short outtext[512];
SceUtilityOskData data;
SceUtilityOskParams params;
JS_FUN(OskInitStart){
	JSObject* param = J2O(argv[0]);
	pspUtilityDialogCommon base;
	params.base=objectToBase(J2O(js_getProperty(param,"base")),&base,sizeof(params));

	memset(&data, 0, sizeof(SceUtilityOskData));
	
	JSObject* odata = J2O(js_getProperty(param,"data"));
	data.unk_00=J2I(js_getProperty(odata,"type"));
		if(data.unk_00==UNDEFINED)data.unk_00=0;
	data.unk_04=J2I(js_getProperty(odata,"attributes"));
		if(data.unk_04==UNDEFINED)data.unk_04=0;
	data.language=J2I(js_getProperty(odata,"language"));
		if(data.language==UNDEFINED)data.language=PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
	data.unk_12=J2I(js_getProperty(odata,"hidemode"));
		if(data.unk_12==UNDEFINED)data.unk_12=0;// or 1 : no difference
	data.inputtype=J2I(js_getProperty(odata,"inputtype"));
		if(data.inputtype==UNDEFINED)data.inputtype=PSP_UTILITY_OSK_INPUTTYPE_ALL;
	data.lines=J2I(js_getProperty(odata,"lines"));
		if(data.lines==UNDEFINED)data.lines=50;
	data.unk_24=J2I(js_getProperty(odata,"kinsoku"));
		if(data.unk_24==UNDEFINED)data.unk_24=0;
	data.desc = expandChrStr(J2S(js_getProperty(odata,"desc")),desc);
		//"undefined"
	data.intext = expandChrStr(J2S(js_getProperty(odata,"intext")),intext);
		//"undefined"
	data.outtextlength = J2I(js_getProperty(odata,"outtextlength"));
		if(data.outtextlength==UNDEFINED)data.outtextlength=js_getStringLength(JSVAL_TO_STRING(js_getProperty(odata,"intext")))+1;
	data.outtextlimit = J2I(js_getProperty(odata,"outtextlimit"));
		if(data.outtextlimit==UNDEFINED)data.outtextlimit=data.outtextlength;

	data.outtext = outtext;
	params.datacount = J2I(js_getProperty(param,"datacount"));
		if(params.datacount==UNDEFINED)params.datacount=1;
	params.data = &data;
	//errorcode & result are unusable
	sceUtilityOskInitStart(&params);
	return JS_TRUE;
}
JS_FUN(OskShutdownStart){
	sceUtilityOskShutdownStart();
	*rval = STRING_TO_JSVAL(js_newString((void*)packUIStr(outtext,js_malloc(data.outtextlength),data.outtextlength),0));
	return JS_TRUE;	
}
JS_FUN(OskUpdate){
	*rval = I2J(sceUtilityOskUpdate(J2I(argv[0])));
	return JS_TRUE;	
}
JS_FUN(OskGetStatus){
	*rval = I2J(sceUtilityOskGetStatus());
	return JS_TRUE;	
}
JS_FUN(Alert){
	if(!argc)return JS_TRUE;
//test gu
	if(sceGuGetAllStatus()==0x8002013A)
		js_evaluateScript("sceGuSetup()");
	memset(&dialog, 0, sizeof(dialog));
	dialog.base.size = sizeof(dialog);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,&dialog.base.language); // Prompt language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,&dialog.base.buttonSwap); // X/O button swap
	dialog.base.graphicsThread = 0x61;
	dialog.base.accessThread = 0x63;
	dialog.base.fontThread = 0x62;
	dialog.base.soundThread = 0x60;
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;
	strcpy(dialog.message, J2S(argv[0]));
	int done=sceUtilityMsgDialogInitStart(&dialog);
	while(!done){
		if(argc==1){
			sceGuStartJs(GU_DIRECT);
			sceGuClear(5);
			sceGuFinish();
		}else js_evaluateScript(J2S(argv[2]));
		switch(sceUtilityMsgDialogGetStatus()){
			case 2:sceUtilityMsgDialogUpdate(1);break;
			case 3:sceUtilityMsgDialogShutdownStart();break;
			case 0:done=1;break;
		}
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}
	return JS_TRUE;
}
JS_FUN(Confirm){
	if(!argc)return JS_TRUE;
//test gu
	if(sceGuGetAllStatus()==0x8002013A)
		js_evaluateScript("sceGuSetup()");

	memset(&dialog, 0, sizeof(dialog));
	dialog.base.size = sizeof(dialog);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,&dialog.base.language); // Prompt language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,&dialog.base.buttonSwap); // X/O button swap
	dialog.base.graphicsThread = 0x61;
	dialog.base.accessThread = 0x63;
	dialog.base.fontThread = 0x62;
	dialog.base.soundThread = 0x60;
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;
	dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS|PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;		
	strcpy(dialog.message, J2S(argv[0]));
	int done = sceUtilityMsgDialogInitStart(&dialog);
	while(!done){
		if(argc==1){
			sceGuStartJs(GU_DIRECT);
			sceGuClear(5);
			sceGuFinish();
			sceGuSync(0,0); 
		}else js_evaluateScript(J2S(argv[2]));
		switch(sceUtilityMsgDialogGetStatus()) {
			case 2:sceUtilityMsgDialogUpdate(1);break;
			case 3:sceUtilityMsgDialogShutdownStart();break;
			case 0:done=1;break;
		}
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}
	*rval = I2J(dialog.buttonPressed);
	return JS_TRUE;
}
JS_FUN(Prompt){
	if(argc<2)return JS_TRUE;
//test gu
	if(sceGuGetAllStatus()==0x8002013A)
		js_evaluateScript("sceGuSetup()");

	memset(&data, 0, sizeof(SceUtilityOskData));
	data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT; // Use system default for text input
	data.lines = 1;
	data.unk_24 = 1;
	data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL; // Allow all input types
	data.desc = expandChrStr(J2S(argv[0]),desc);
	data.intext = expandChrStr(J2S(argv[1]),intext);
	data.outtextlength = 128;
	data.outtextlimit = 32; // Limit input to 32 characters
	data.outtext = outtext;
	
	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	params.base.graphicsThread = 0x61;
	params.base.accessThread = 0x63;
	params.base.fontThread = 0x62;
	params.base.soundThread = 0x60;
	params.datacount = 1;
	params.data = &data;
	sceUtilityOskInitStart(&params);
	int done=0;
	while(!done){
		if(argc==2){//no CB
			sceGuStartJs(GU_DIRECT);
			sceGuClear(5);
			sceGuFinish();
      sceGuSync(0,0); 
		}else js_evaluateScript(J2S(argv[2]));
		switch(sceUtilityOskGetStatus()){
			case PSP_UTILITY_DIALOG_VISIBLE:sceUtilityOskUpdate(1);break;
			case PSP_UTILITY_DIALOG_QUIT:sceUtilityOskShutdownStart();break;
			case PSP_UTILITY_DIALOG_NONE:done = 1;
			default:break;
		}
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	} 
	*rval = STRING_TO_JSVAL(js_newString((void*)packUIStr(outtext,js_malloc(data.outtextlength),data.outtextlength),0));
	return JS_TRUE;
}
JS_FUN(Connect){
//test gu
	if(sceGuGetAllStatus()==0x8002013A)
		js_evaluateScript("sceGuSetup()");
//test net
	#include <pspnet.h>
	SceNetMallocStat stat;
	if(sceNetGetMallocStat(&stat)<0)//netlib !loaded || !inited
		js_evaluateScript("sceNetInit(128*1024, 42, 4*1024, 42, 4*1024);sceNetInetInit();sceNetApctlInit(0x8000, 48);");

	memset(&Netconf,0,sizeof(Netconf));
	pspUtilityDialogCommon base;
	int value=0;
	base.size=sizeof(Netconf);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,&value);
	base.language = value;
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,&value);
	base.buttonSwap = value;
	base.soundThread=16;
	base.graphicsThread=17;
	base.fontThread=18;
	base.accessThread=19;
	Netconf.base=base;
	Netconf.action=3;
	value=sceUtilityNetconfInitStart(&Netconf);
	*rval = I2J(value);
	if(value<0)return JS_TRUE;
	value=0;
	while(!value){
		if(!argc){
			sceGuStartJs(GU_DIRECT);
			sceGuClear(5);
			sceGuFinish();
			sceGuSync(0,0);
		}else js_evaluateScript(J2S(argv[2]));
		switch(sceUtilityNetconfGetStatus()){
			case 0:break;//NONE
			case 1:break;//INIT
			case 2:sceUtilityNetconfUpdate(1);break;//VISIBLE
			case 3:sceUtilityNetconfShutdownStart();break;//QUIT
			case 4:value=1;break;//FINISHED
			default:break;
		}
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}
	return JS_TRUE;
}
static JSPropertiesSpec var[] = {
	{"PSP_UTILITY_ACCEPT_CIRCLE",I2J(PSP_UTILITY_ACCEPT_CIRCLE)},
	{"PSP_UTILITY_ACCEPT_CROSS",I2J(PSP_UTILITY_ACCEPT_CROSS)},
	{"PSP_UTILITY_DIALOG_NONE",I2J(PSP_UTILITY_DIALOG_NONE)},
	{"PSP_UTILITY_DIALOG_INIT",I2J(PSP_UTILITY_DIALOG_INIT)},
	{"PSP_UTILITY_DIALOG_VISIBLE",I2J(PSP_UTILITY_DIALOG_VISIBLE)},
	{"PSP_UTILITY_DIALOG_QUIT",I2J(PSP_UTILITY_DIALOG_QUIT)},
	{"PSP_UTILITY_DIALOG_FINISHED",I2J(PSP_UTILITY_DIALOG_FINISHED)},
	{"PSP_SYSTEMPARAM_ID_STRING_NICKNAME",I2J(PSP_SYSTEMPARAM_ID_STRING_NICKNAME)},
	{"PSP_SYSTEMPARAM_ID_INT_ADHOC_CHANNEL",I2J(PSP_SYSTEMPARAM_ID_INT_ADHOC_CHANNEL)},
	{"PSP_SYSTEMPARAM_ID_INT_WLAN_POWERSAVE",I2J(PSP_SYSTEMPARAM_ID_INT_WLAN_POWERSAVE)},
	{"PSP_SYSTEMPARAM_ID_INT_DATE_FORMAT",I2J(PSP_SYSTEMPARAM_ID_INT_DATE_FORMAT)},
	{"PSP_SYSTEMPARAM_ID_INT_TIME_FORMAT",I2J(PSP_SYSTEMPARAM_ID_INT_TIME_FORMAT)},
	{"PSP_SYSTEMPARAM_ID_INT_TIMEZONE",I2J(PSP_SYSTEMPARAM_ID_INT_TIMEZONE)},
	{"PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS",I2J(PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS)},
	{"PSP_SYSTEMPARAM_ID_INT_LANGUAGE",I2J(PSP_SYSTEMPARAM_ID_INT_LANGUAGE)},
	{"PSP_SYSTEMPARAM_ID_INT_UNKNOWN",I2J(PSP_SYSTEMPARAM_ID_INT_UNKNOWN)},
	{"PSP_SYSTEMPARAM_ID_INT_CTRL_ASSIGN",I2J(PSP_SYSTEMPARAM_ID_INT_UNKNOWN)},// SCE_UTILITY_SYSTEM_PARAM_CTRL_ASSIGN
	{"PSP_SYSTEMPARAM_RETVAL_OK",I2J(PSP_SYSTEMPARAM_RETVAL_OK)},
	{"PSP_SYSTEMPARAM_RETVAL_FAIL",I2J(PSP_SYSTEMPARAM_RETVAL_FAIL)},
	{"PSP_SYSTEMPARAM_ADHOC_CHANNEL_AUTOMATIC",I2J(PSP_SYSTEMPARAM_ADHOC_CHANNEL_AUTOMATIC)},
	{"PSP_SYSTEMPARAM_ADHOC_CHANNEL_1",I2J(PSP_SYSTEMPARAM_ADHOC_CHANNEL_1)},
	{"PSP_SYSTEMPARAM_ADHOC_CHANNEL_6",I2J(PSP_SYSTEMPARAM_ADHOC_CHANNEL_6)},
	{"PSP_SYSTEMPARAM_WLAN_POWERSAVE_OFF",I2J(PSP_SYSTEMPARAM_WLAN_POWERSAVE_OFF)},
	{"PSP_SYSTEMPARAM_WLAN_POWERSAVE_ON",I2J(PSP_SYSTEMPARAM_WLAN_POWERSAVE_ON)},
	{"PSP_SYSTEMPARAM_DATE_FORMAT_YYYYMMDD",I2J(PSP_SYSTEMPARAM_DATE_FORMAT_YYYYMMDD)},
	{"PSP_SYSTEMPARAM_DATE_FORMAT_MMDDYYYY",I2J(PSP_SYSTEMPARAM_DATE_FORMAT_MMDDYYYY)},
	{"PSP_SYSTEMPARAM_DATE_FORMAT_DDMMYYYY",I2J(PSP_SYSTEMPARAM_DATE_FORMAT_DDMMYYYY)},
	{"PSP_SYSTEMPARAM_TIME_FORMAT_24HR",I2J(PSP_SYSTEMPARAM_TIME_FORMAT_24HR)},
	{"PSP_SYSTEMPARAM_TIME_FORMAT_12HR",I2J(PSP_SYSTEMPARAM_TIME_FORMAT_12HR)},
	{"PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_STD",I2J(PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_STD)},
	{"PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_SAVING",I2J(PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_SAVING)},
	{"PSP_SYSTEMPARAM_LANGUAGE_JAPANESE",I2J(PSP_SYSTEMPARAM_LANGUAGE_JAPANESE)},
	{"PSP_SYSTEMPARAM_LANGUAGE_ENGLISH",I2J(PSP_SYSTEMPARAM_LANGUAGE_ENGLISH)},
	{"PSP_SYSTEMPARAM_LANGUAGE_FRENCH",I2J(PSP_SYSTEMPARAM_LANGUAGE_FRENCH)},
	{"PSP_SYSTEMPARAM_LANGUAGE_SPANISH",I2J(PSP_SYSTEMPARAM_LANGUAGE_SPANISH)},
	{"PSP_SYSTEMPARAM_LANGUAGE_GERMAN",I2J(PSP_SYSTEMPARAM_LANGUAGE_GERMAN)},
	{"PSP_SYSTEMPARAM_LANGUAGE_ITALIAN",I2J(PSP_SYSTEMPARAM_LANGUAGE_ITALIAN)},
	{"PSP_SYSTEMPARAM_LANGUAGE_DUTCH",I2J(PSP_SYSTEMPARAM_LANGUAGE_DUTCH)},
	{"PSP_SYSTEMPARAM_LANGUAGE_PORTUGUESE",I2J(PSP_SYSTEMPARAM_LANGUAGE_PORTUGUESE)},
	{"PSP_SYSTEMPARAM_LANGUAGE_RUSSIAN",I2J(PSP_SYSTEMPARAM_LANGUAGE_RUSSIAN)},
	{"PSP_SYSTEMPARAM_LANGUAGE_KOREAN",I2J(PSP_SYSTEMPARAM_LANGUAGE_KOREAN)},
	{"PSP_SYSTEMPARAM_LANGUAGE_CHINESE_TRADITIONAL",I2J(PSP_SYSTEMPARAM_LANGUAGE_CHINESE_TRADITIONAL)},
	{"PSP_SYSTEMPARAM_LANGUAGE_CHINESE_SIMPLIFIED",I2J(PSP_SYSTEMPARAM_LANGUAGE_CHINESE_SIMPLIFIED)},
	{"PSP_USB_MODULE_PSPCM",I2J(PSP_USB_MODULE_PSPCM)},
	{"PSP_USB_MODULE_ACC",I2J(PSP_USB_MODULE_ACC)},
	{"PSP_USB_MODULE_MIC",I2J(PSP_USB_MODULE_MIC)},
	{"PSP_USB_MODULE_CAM",I2J(PSP_USB_MODULE_CAM)},
	{"PSP_USB_MODULE_GPS",I2J(PSP_USB_MODULE_GPS)},
	{"PSP_AV_MODULE_AVCODEC",I2J(PSP_AV_MODULE_AVCODEC)},
	{"PSP_AV_MODULE_SASCORE",I2J(PSP_AV_MODULE_SASCORE)},
	{"PSP_AV_MODULE_ATRAC3PLUS",I2J(PSP_AV_MODULE_ATRAC3PLUS)},
	{"PSP_AV_MODULE_MPEGBASE",I2J(PSP_AV_MODULE_MPEGBASE)},
	{"PSP_AV_MODULE_MP3",I2J(PSP_AV_MODULE_MP3)},
	{"PSP_AV_MODULE_VAUDIO",I2J(PSP_AV_MODULE_VAUDIO)},
	{"PSP_AV_MODULE_AAC",I2J(PSP_AV_MODULE_AAC)},
	{"PSP_AV_MODULE_G729",I2J(PSP_AV_MODULE_G729)},
	{"PSP_NET_MODULE_COMMON",I2J(PSP_NET_MODULE_COMMON)},
	{"PSP_NET_MODULE_ADHOC",I2J(PSP_NET_MODULE_ADHOC)},
	{"PSP_NET_MODULE_INET",I2J(PSP_NET_MODULE_INET)},
	{"PSP_NET_MODULE_PARSEURI",I2J(PSP_NET_MODULE_PARSEURI)},
	{"PSP_NET_MODULE_PARSEHTTP",I2J(PSP_NET_MODULE_PARSEHTTP)},
	{"PSP_NET_MODULE_HTTP",I2J(PSP_NET_MODULE_HTTP)},
	{"PSP_NET_MODULE_SSL",I2J(PSP_NET_MODULE_SSL)},
	{"PSP_UTILITY_GAMESHARING_MODE_SINGLE",I2J(PSP_UTILITY_GAMESHARING_MODE_SINGLE)},
	{"PSP_UTILITY_GAMESHARING_MODE_MULTIPLE",I2J(PSP_UTILITY_GAMESHARING_MODE_MULTIPLE)},
	{"PSP_UTILITY_GAMESHARING_DATA_TYPE_FILE",I2J(PSP_UTILITY_GAMESHARING_DATA_TYPE_FILE)},
	{"PSP_UTILITY_GAMESHARING_DATA_TYPE_MEMORY",I2J(PSP_UTILITY_GAMESHARING_DATA_TYPE_MEMORY)},
	{"PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_ENABLE",I2J(PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_ENABLE)},
	{"PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_DISABLE",I2J(PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_DISABLE)},
	{"PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_CONFIRM",I2J(PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_CONFIRM)},
	{"PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL",I2J(PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL)},
	{"PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_LIMITED",I2J(PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_LIMITED)},
	{"PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_NONE",I2J(PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_NONE)},
	{"PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DISABLED",I2J(PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DISABLED)},
	{"PSP_UTILITY_HTMLVIEWER_COOKIEMODE_ENABLED",I2J(PSP_UTILITY_HTMLVIEWER_COOKIEMODE_ENABLED)},
	{"PSP_UTILITY_HTMLVIEWER_COOKIEMODE_CONFIRM",I2J(PSP_UTILITY_HTMLVIEWER_COOKIEMODE_CONFIRM)},
	{"PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DEFAULT",I2J(PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DEFAULT)},
	{"PSP_UTILITY_HTMLVIEWER_TEXTSIZE_LARGE",I2J(PSP_UTILITY_HTMLVIEWER_TEXTSIZE_LARGE)},
	{"PSP_UTILITY_HTMLVIEWER_TEXTSIZE_NORMAL",I2J(PSP_UTILITY_HTMLVIEWER_TEXTSIZE_NORMAL)},
	{"PSP_UTILITY_HTMLVIEWER_TEXTSIZE_SMALL",I2J(PSP_UTILITY_HTMLVIEWER_TEXTSIZE_SMALL)},
	{"PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_NORMAL",I2J(PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_NORMAL)},
	{"PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_FIT",I2J(PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_FIT)},
	{"PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_SMART_FIT",I2J(PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_SMART_FIT)},
	{"PSP_UTILITY_HTMLVIEWER_CONNECTMODE_LAST",I2J(PSP_UTILITY_HTMLVIEWER_CONNECTMODE_LAST)},
	{"PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ONCE",I2J(PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ONCE)},
	{"PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ALL",I2J(PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ALL)},
	{"PSP_UTILITY_HTMLVIEWER_OPEN_SCE_START_PAGE",I2J(PSP_UTILITY_HTMLVIEWER_OPEN_SCE_START_PAGE)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_EXIT_DIALOG",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_EXIT_DIALOG)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_CURSOR",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_CURSOR)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_COMPLETE_DIALOG",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_COMPLETE_DIALOG)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_START_DIALOG",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_START_DIALOG)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_DESTINATION_DIALOG",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_DESTINATION_DIALOG)},
	{"PSP_UTILITY_HTMLVIEWER_LOCK_DOWNLOAD_DESTINATION_DIALOG",I2J(PSP_UTILITY_HTMLVIEWER_LOCK_DOWNLOAD_DESTINATION_DIALOG)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_TAB_DISPLAY",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_TAB_DISPLAY)},
	{"PSP_UTILITY_HTMLVIEWER_ENABLE_ANALOG_HOLD",I2J(PSP_UTILITY_HTMLVIEWER_ENABLE_ANALOG_HOLD)},
	{"PSP_UTILITY_HTMLVIEWER_ENABLE_FLASH",I2J(PSP_UTILITY_HTMLVIEWER_ENABLE_FLASH)},
	{"PSP_UTILITY_HTMLVIEWER_DISABLE_LRTRIGGER",I2J(PSP_UTILITY_HTMLVIEWER_DISABLE_LRTRIGGER)},
	{"PSP_UTILITY_SAVEDATA_AUTOLOAD",I2J(PSP_UTILITY_SAVEDATA_AUTOLOAD)},
	{"PSP_UTILITY_SAVEDATA_AUTOSAVE",I2J(PSP_UTILITY_SAVEDATA_AUTOSAVE)},
	{"PSP_UTILITY_SAVEDATA_LOAD",I2J(PSP_UTILITY_SAVEDATA_LOAD)},
	{"PSP_UTILITY_SAVEDATA_SAVE",I2J(PSP_UTILITY_SAVEDATA_SAVE)},
	{"PSP_UTILITY_SAVEDATA_LISTLOAD",I2J(PSP_UTILITY_SAVEDATA_LISTLOAD)},
	{"PSP_UTILITY_SAVEDATA_LISTSAVE",I2J(PSP_UTILITY_SAVEDATA_LISTSAVE)},
	{"PSP_UTILITY_SAVEDATA_LISTDELETE",I2J(PSP_UTILITY_SAVEDATA_LISTDELETE)},
	{"PSP_UTILITY_SAVEDATA_DELETE",I2J(PSP_UTILITY_SAVEDATADELETE)},
	{"PSP_UTILITY_SAVEDATADELETE",I2J(PSP_UTILITY_SAVEDATADELETE)},/*missing underline ?*/
	{"PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN",I2J(PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_FIRSTLIST",I2J(PSP_UTILITY_SAVEDATA_FOCUS_FIRSTLIST)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_LASTLIST",I2J(PSP_UTILITY_SAVEDATA_FOCUS_LASTLIST)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_LATEST",I2J(PSP_UTILITY_SAVEDATA_FOCUS_LATEST)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_OLDEST",I2J(PSP_UTILITY_SAVEDATA_FOCUS_OLDEST)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN2",I2J(PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN2)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN3",I2J(PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN3)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY",I2J(PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY)},
	{"PSP_UTILITY_SAVEDATA_FOCUS_LASTEMPTY",I2J(PSP_UTILITY_SAVEDATA_FOCUS_LASTEMPTY)},
	{"PSP_UTILITY_MSGDIALOG_MODE_ERROR",I2J(PSP_UTILITY_MSGDIALOG_MODE_ERROR)},
	{"PSP_UTILITY_MSGDIALOG_MODE_TEXT",I2J(PSP_UTILITY_MSGDIALOG_MODE_TEXT)},
	{"PSP_UTILITY_MSGDIALOG_OPTION_ERROR",I2J(PSP_UTILITY_MSGDIALOG_OPTION_ERROR)},
	{"PSP_UTILITY_MSGDIALOG_OPTION_TEXT",I2J(PSP_UTILITY_MSGDIALOG_OPTION_TEXT)},
	{"PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS",I2J(PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS)},
	{"PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO",I2J(PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO)},
	{"PSP_UTILITY_MSGDIALOG_RESULT_UNKNOWN1",I2J(PSP_UTILITY_MSGDIALOG_RESULT_UNKNOWN1)},
	{"PSP_UTILITY_MSGDIALOG_RESULT_YES",I2J(PSP_UTILITY_MSGDIALOG_RESULT_YES)},
	{"PSP_UTILITY_MSGDIALOG_RESULT_NO",I2J(PSP_UTILITY_MSGDIALOG_RESULT_NO)},
	{"PSP_UTILITY_MSGDIALOG_RESULT_BACK",I2J(PSP_UTILITY_MSGDIALOG_RESULT_BACK)},
	{"PSP_NETCONF_ACTION_CONNECTAP",I2J(0)},
	{"PSP_NETCONF_ACTION_DISPLAYSTATUS",I2J(1)},
	{"PSP_NETCONF_ACTION_CONNECT_ADHOC",I2J(2)},
	{"PSP_NETCONF_ACTION_CONNECTAP_LASTUSED",I2J(3)},
	{"PSP_NETPARAM_NAME",I2J(PSP_NETPARAM_NAME)},
	{"PSP_NETPARAM_SSID",I2J(PSP_NETPARAM_SSID)},
	{"PSP_NETPARAM_SECURE",I2J(PSP_NETPARAM_SECURE)},
	{"PSP_NETPARAM_WEPKEY",I2J(PSP_NETPARAM_WEPKEY)},
	{"PSP_NETPARAM_IS_STATIC_IP",I2J(PSP_NETPARAM_IS_STATIC_IP)},
	{"PSP_NETPARAM_IP",I2J(PSP_NETPARAM_IP)},
	{"PSP_NETPARAM_NETMASK",I2J(PSP_NETPARAM_NETMASK)},
	{"PSP_NETPARAM_ROUTE",I2J(PSP_NETPARAM_ROUTE)},
	{"PSP_NETPARAM_MANUAL_DNS",I2J(PSP_NETPARAM_MANUAL_DNS)},
	{"PSP_NETPARAM_PRIMARYDNS",I2J(PSP_NETPARAM_PRIMARYDNS)},
	{"PSP_NETPARAM_SECONDARYDNS",I2J(PSP_NETPARAM_SECONDARYDNS)},
	{"PSP_NETPARAM_PROXY_USER",I2J(PSP_NETPARAM_PROXY_USER)},
	{"PSP_NETPARAM_PROXY_PASS",I2J(PSP_NETPARAM_PROXY_PASS)},
	{"PSP_NETPARAM_USE_PROXY",I2J(PSP_NETPARAM_USE_PROXY)},
	{"PSP_NETPARAM_PROXY_SERVER",I2J(PSP_NETPARAM_PROXY_SERVER)},
	{"PSP_NETPARAM_PROXY_PORT",I2J(PSP_NETPARAM_PROXY_PORT)},
	{"PSP_NETPARAM_UNKNOWN1",I2J(PSP_NETPARAM_UNKNOWN1)},
	{"PSP_NETPARAM_UNKNOWN2",I2J(PSP_NETPARAM_UNKNOWN2)},
	{"PSP_NETPARAM_ERROR_BAD_NETCONF",I2J(PSP_NETPARAM_ERROR_BAD_NETCONF)},
	{"PSP_NETPARAM_ERROR_BAD_PARAM",I2J(PSP_NETPARAM_ERROR_BAD_PARAM)},
	{"PSP_UTILITY_OSK_LANGUAGE_DEFAULT",I2J(PSP_UTILITY_OSK_LANGUAGE_DEFAULT)},
	{"PSP_UTILITY_OSK_LANGUAGE_JAPANESE",I2J(PSP_UTILITY_OSK_LANGUAGE_JAPANESE)},
	{"PSP_UTILITY_OSK_LANGUAGE_ENGLISH",I2J(PSP_UTILITY_OSK_LANGUAGE_ENGLISH)},
	{"PSP_UTILITY_OSK_LANGUAGE_FRENCH",I2J(PSP_UTILITY_OSK_LANGUAGE_FRENCH)},
	{"PSP_UTILITY_OSK_LANGUAGE_SPANISH",I2J(PSP_UTILITY_OSK_LANGUAGE_SPANISH)},
	{"PSP_UTILITY_OSK_LANGUAGE_GERMAN",I2J(PSP_UTILITY_OSK_LANGUAGE_GERMAN)},
	{"PSP_UTILITY_OSK_LANGUAGE_ITALIAN",I2J(PSP_UTILITY_OSK_LANGUAGE_ITALIAN)},
	{"PSP_UTILITY_OSK_LANGUAGE_DUTCH",I2J(PSP_UTILITY_OSK_LANGUAGE_DUTCH)},
	{"PSP_UTILITY_OSK_LANGUAGE_PORTUGESE",I2J(PSP_UTILITY_OSK_LANGUAGE_PORTUGESE)},
	{"PSP_UTILITY_OSK_LANGUAGE_RUSSIAN",I2J(PSP_UTILITY_OSK_LANGUAGE_RUSSIAN)},
	{"PSP_UTILITY_OSK_LANGUAGE_KOREAN",I2J(PSP_UTILITY_OSK_LANGUAGE_KOREAN)},
	{"PSP_UTILITY_OSK_DIALOG_NONE",I2J(PSP_UTILITY_OSK_DIALOG_NONE)},
	{"PSP_UTILITY_OSK_DIALOG_INITING",I2J(PSP_UTILITY_OSK_DIALOG_INITING)},
	{"PSP_UTILITY_OSK_DIALOG_INITED",I2J(PSP_UTILITY_OSK_DIALOG_INITED)},
	{"PSP_UTILITY_OSK_DIALOG_VISIBLE",I2J(PSP_UTILITY_OSK_DIALOG_VISIBLE)},
	{"PSP_UTILITY_OSK_DIALOG_QUIT",I2J(PSP_UTILITY_OSK_DIALOG_QUIT)},
	{"PSP_UTILITY_OSK_DIALOG_FINISHED",I2J(PSP_UTILITY_OSK_DIALOG_FINISHED)},
	{"PSP_UTILITY_OSK_RESULT_UNCHANGED",I2J(PSP_UTILITY_OSK_RESULT_UNCHANGED)},
	{"PSP_UTILITY_OSK_RESULT_CANCELLED",I2J(PSP_UTILITY_OSK_RESULT_CANCELLED)},
	{"PSP_UTILITY_OSK_RESULT_CHANGED",I2J(PSP_UTILITY_OSK_RESULT_CHANGED)},
	{"PSP_UTILITY_OSK_INPUTTYPE_ALL",I2J(PSP_UTILITY_OSK_INPUTTYPE_ALL)},
	{"PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT",I2J(PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT)},
	{"PSP_UTILITY_OSK_INPUTTYPE_LATIN_SYMBOL",I2J(PSP_UTILITY_OSK_INPUTTYPE_LATIN_SYMBOL)},
	{"PSP_UTILITY_OSK_INPUTTYPE_LATIN_LOWERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_LATIN_LOWERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_LATIN_UPPERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_LATIN_UPPERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_DIGIT",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_DIGIT)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_SYMBOL",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_SYMBOL)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_LOWERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_LOWERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_UPPERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_UPPERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HIRAGANA",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HIRAGANA)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HALF_KATAKANA",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HALF_KATAKANA)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KATAKANA",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KATAKANA)},
	{"PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KANJI",I2J(PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KANJI)},
	{"PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_LOWERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_LOWERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_UPPERCASE",I2J(PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_UPPERCASE)},
	{"PSP_UTILITY_OSK_INPUTTYPE_KOREAN",I2J(PSP_UTILITY_OSK_INPUTTYPE_KOREAN)},
	{"PSP_UTILITY_OSK_INPUTTYPE_URL",I2J(PSP_UTILITY_OSK_INPUTTYPE_URL)},
	{"PSP_MODULE_NET_COMMON",I2J(PSP_MODULE_NET_COMMON)},
	{"PSP_MODULE_NET_ADHOC",I2J(PSP_MODULE_NET_ADHOC)},
	{"PSP_MODULE_NET_INET",I2J(PSP_MODULE_NET_INET)},
	{"PSP_MODULE_NET_PARSEURI",I2J(PSP_MODULE_NET_PARSEURI)},
	{"PSP_MODULE_NET_PARSEHTTP",I2J(PSP_MODULE_NET_PARSEHTTP)},
	{"PSP_MODULE_NET_HTTP",I2J(PSP_MODULE_NET_HTTP)},
	{"PSP_MODULE_NET_SSL",I2J(PSP_MODULE_NET_SSL)},
	{"PSP_MODULE_USB_PSPCM",I2J(PSP_MODULE_USB_PSPCM)},
	{"PSP_MODULE_USB_MIC",I2J(PSP_MODULE_USB_MIC)},
	{"PSP_MODULE_USB_CAM",I2J(PSP_MODULE_USB_CAM)},
	{"PSP_MODULE_USB_GPS",I2J(PSP_MODULE_USB_GPS)},
	{"PSP_MODULE_AV_AVCODEC",I2J(PSP_MODULE_AV_AVCODEC)},
	{"PSP_MODULE_AV_SASCORE",I2J(PSP_MODULE_AV_SASCORE)},
	{"PSP_MODULE_AV_ATRAC3PLUS",I2J(PSP_MODULE_AV_ATRAC3PLUS)},
	{"PSP_MODULE_AV_MPEGBASE",I2J(PSP_MODULE_AV_MPEGBASE)},
	{"PSP_MODULE_AV_MP3",I2J(PSP_MODULE_AV_MP3)},
	{"PSP_MODULE_AV_VAUDIO",I2J(PSP_MODULE_AV_VAUDIO)},
	{"PSP_MODULE_AV_AAC",I2J(PSP_MODULE_AV_AAC)},
	{"PSP_MODULE_AV_G729",I2J(PSP_MODULE_AV_G729)},
	{"PSP_MODULE_NP_COMMON",I2J(PSP_MODULE_NP_COMMON)},
	{"PSP_MODULE_NP_SERVICE",I2J(PSP_MODULE_NP_SERVICE)},
	{"PSP_MODULE_NP_MATCHING2",I2J(PSP_MODULE_NP_MATCHING2)},
	{"PSP_MODULE_NP_DRM",I2J(PSP_MODULE_NP_DRM)},
	{"PSP_MODULE_IRDA",I2J(PSP_MODULE_IRDA)},
	{0}
};
static JSFunctionSpec lfun[] = {
	{"connectAP",Connect,0},

	{"loadAvModule",LoadAvModule,1},
	{"unloadAvModule",UnloadAvModule,1},
	{"loadNetModule",LoadNetModule,1},
	{"unloadNetModule",UnloadNetModule,1},
	{"loadUsbModule",LoadUsbModule,1},
	{"unloadUsbModule",UnloadUsbModule,1},
	{"loadModule",LoadModule,1},
	{"unloadModule",UnloadModule,1},
	{"gameSharingUpdate",GameSharingUpdate,0},
	{"gameSharingGetStatus",GameSharingGetStatus,0},
	{"gameSharingShutdownStart",GameSharingShutdownStart,0},
	{"msgDialogInitStart",MsgDialogInitStart,1},
	{"msgDialogShutdownStart",MsgDialogShutdownStart,0},
	{"msgDialogGetStatus",MsgDialogGetStatus,0},
	{"msgDialogUpdate",MsgDialogUpdate,0},
	{"msgDialogAbort",MsgDialogAbort,0},
	{"msgDialogPressed",MsgDialogPressed,0},
	{"getSystemParamInt",GetSystemParamInt,1},
	{"setSystemParamInt",SetSystemParamInt,2},
	{"getSystemParamString",GetSystemParamString,1},
	{"setSystemParamString",SetSystemParamString,2},
	{"netconfInitStart",NetconfInitStart,2},
	{"netconfShutdownStart",NetconfShutdownStart,0},
	{"netconfUpdate",NetconfUpdate,1},
	{"netconfGetStatus",NetconfGetStatus,0},
	{"oskInitStart",OskInitStart,1},
	{"oskGetStatus",OskGetStatus,0},
	{"oskUpdate",OskUpdate,1},
	{"oskShutdownStart",OskShutdownStart,0},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"connect",Connect,0},
	{"prompt",Prompt,3},
	{"alert",Alert,2},
	{"confirm",Confirm,2},
	{0}
};
int module_start(SceSize args, void *argp){
	js_addModule(lfun,gfun,0,var);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
