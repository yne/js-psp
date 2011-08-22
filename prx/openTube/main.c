#include <pspkernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <psputility.h>

#include "core.h"
#include "../../main/shared.h"

PSP_MODULE_INFO("OpenTube.jsBridge",PSP_MODULE_USER,1,1);
unsigned short desc[128];
unsigned short intext[512];
unsigned short outtext[512];
pspUtilityMsgDialogParams dialog;
SceUtilityOskParams params;
SceUtilityOskData data;

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
JS_FUN(edit){
	char*res=Edit(J2I(argv[0]),argc>1?J2S(argv[1]):NULL);
	if(!res)return JS_TRUE;
	int len=strlen(res);
	char*out=js_malloc(len+1);
	memcpy(out,res,len);out[len]=0;
	*rval=S2J(out,len);
	return JS_TRUE;
}
JS_FUN(myopen){
	if(!argc)return JS_TRUE;
	Mode=0;//interrupt draw loop (in case of netconf gui)
	int length=0,ret,fd=Open(J2S(argv[0]),PSP_O_RDONLY,0777);
	Mode=1;
	if(fd<0)return JS_TRUE;
	void*result=js_malloc(1024);
	while((ret=Read(fd,result+length,1024))>0){
		length+=ret;
		result=js_realloc(result,length+1024);
	}
	Close(fd);
	*rval=S2J(result,0);
	return JS_TRUE;
}
JS_FUN(play){
	if(!argc)return JS_TRUE;
	Mode=0;//interrupt draw loop
	char*res=Play(J2S(argv[0]));
	Mode=1;
	if(!res)return JS_TRUE;
	int len=strlen(res);
	char*out=js_malloc(len+1);
	memcpy(out,res,len);out[len]=0;
	*rval=S2J(out,len);
	return JS_TRUE;
}
JS_FUN(alert){
	if(!argc)return JS_TRUE;
	Mode=0;//interrupt draw loop
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
		Draw(1|2);
		switch(sceUtilityMsgDialogGetStatus()){
			case 2:sceUtilityMsgDialogUpdate(1);break;
			case 3:sceUtilityMsgDialogShutdownStart();break;
			case 0:done=1;break;
		}
		Draw(4|8);
	}
	Mode=1;
	return JS_TRUE;
}
JS_FUN(confirm){
	if(!argc)return JS_TRUE;
	Mode=0;//interrupt draw loop
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
		Draw(1|2);
		switch(sceUtilityMsgDialogGetStatus()) {
			case 2:sceUtilityMsgDialogUpdate(1);break;
			case 3:sceUtilityMsgDialogShutdownStart();break;
			case 0:done=1;break;
		}
		Draw(4|8);
	}
	Mode=1;
	*rval = I2J(dialog.buttonPressed);
	return JS_TRUE;
}
JS_FUN(prompt){
	if(argc<2)return JS_TRUE;
	Mode=0;//interrupt draw loop
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
	
	for(int done=0;!done;){
		Draw(1|2);
		switch(sceUtilityOskGetStatus()){
			case PSP_UTILITY_DIALOG_VISIBLE:sceUtilityOskUpdate(1);break;
			case PSP_UTILITY_DIALOG_QUIT:sceUtilityOskShutdownStart();break;
			case PSP_UTILITY_DIALOG_NONE:done = 1;
			default:break;
		}
		Draw(4|8);
	} 
	*rval = STRING_TO_JSVAL(js_newString((void*)packUIStr(outtext,js_malloc(data.outtextlength),data.outtextlength),0));
	Mode=1;
	return JS_TRUE;
}
static JSFunctionSpec fun[] = {
	{"edit",edit,0},
	{0}
};
static JSFunctionSpec gfun[] = {
	{"open",myopen,0},
	{"play",play,0},
	{"alert",alert,0},
	{"prompt",prompt,0},
	{"confirm",confirm,0},
	{0}
};
int module_start(SceSize args, void *argp){
	if((ot=otGetCtx())<0)return 1;//get openTube context
	js_addModule(fun,gfun,0,0);//register bridge function
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
