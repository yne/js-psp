var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var utility = new Module("prx/sceUtility.prx");

var param={
	base:{
		language:utility.getSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE),
		buttonSwap:utility.getSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN),
		soundThread:16,
		graphicsThread:17,
		fontThread:18,
		accessThread:19,
	}
}

gu.Init();
gu.Start(GU_DIRECT);
gu.DrawBuffer(GU_PSM_8888,0,BUF_WIDTH);
gu.DispBuffer(SCR_WIDTH,SCR_HEIGHT,0x88000,BUF_WIDTH);
gu.DepthBuffer(0x110000,BUF_WIDTH);
gu.Offset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
gu.Viewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
gu.DepthRange(0xc350,0x2710);
gu.Scissor(0,0,SCR_WIDTH,SCR_HEIGHT);
gu.Enable(2);
gu.Color(0xFFFFFF00);
gu.ClearColor(0xff554433);
gu.ClearDepth(0);
gu.Finish();
gu.Sync(0,0);
gu.Display(1);

// ~ ~ ~ ~ ~ ~ ~ ~ UTILITY>OSK ~ ~ ~ ~ ~ ~ ~ ~ //
//param.datacount = 1;
param.data = {
	//type:0,
	//attributes:0,
	//language:PSP_UTILITY_OSK_LANGUAGE_DEFAULT,
	//hidemode:0,
	//inputtype:PSP_UTILITY_OSK_INPUTTYPE_ALL,
	//lines:0,
	//kinsoku:0,
	intext:"yooooooooooooooou",
	//outtextlength:16,//max displayed/returned bytes (input is shrinked)
	//outtextlimit:8,//max displayed/returned characters (if ascii : bytes=char)
	desc:"moi",//displayed a bottom
};

utility.oskInitStart(param);
var run=1;
var result = "";
while(run){
	gu.Start(GU_DIRECT);
	gu.Clear(5);
	gu.Finish();
	switch(utility.oskGetStatus()){
		case 1:break;//INIT
		case 2:utility.oskUpdate(1);break;//VISIBLE
		case 3:result=utility.oskShutdownStart();break;//QUIT
		case 4:break;//FINISHED
		case 0:run = 0;//NONE
		default:break;
	}
	display.WaitVblankStart();
	gu.SwapBuffers();
}

// ~ ~ ~ ~ ~ ~ ~ ~ UTILITY>MsgDialog ~ ~ ~ ~ ~ ~ ~ ~ //
param.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
param.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT|PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS|PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;
param.message = "you have wrote : "+result;

utility.msgDialogInitStart(param);
run=1;
while(run){
	gu.Start(GU_DIRECT);
	gu.Clear(5);
	gu.Finish();
	switch(utility.msgDialogGetStatus()){
		case 0:break;//NONE
		case 1:break;//INIT
		case 2:utility.msgDialogUpdate(1);break;//VISIBLE
		case 3:utility.msgDialogShutdownStart();break;//QUIT
		case 4:run=0;break;//FINISHED
		default:break;
	}
	display.WaitVblankStart();
	gu.SwapBuffers();
}
printf(utility.msgDialogPressed()+"\n");

// ~ ~ ~ ~ ~ ~ ~ ~ UTILITY>NET ~ ~ ~ ~ ~ ~ ~ ~ //
var ifhandle = new Module("flash0:/kd/ifhandle.prx");//sceNetInterface_Service : avoid sceNetInit 0x8002013A error
var pspnet = new Module("flash0:/kd/pspnet.prx");//COMMON
var pspnet_inet = new Module("flash0:/kd/pspnet_inet.prx");//INET
var pspnet_apctl = new Module("flash0:/kd/pspnet_apctl.prx");//APCTL
var net = new Module("prx/sceNet.prx");

net.Init(128*1024, 42, 4*1024, 42, 4*1024);
net.InetInit();
net.ApctlInit(0x8000, 48);

// -- -- connect acces point -- -- //
param.action=PSP_NETCONF_ACTION_CONNECTAP;
utility.netconfInitStart(param);

run=1;
while(run){
	gu.Start(GU_DIRECT);
	gu.Clear(5);
	gu.Finish();
	switch(utility.netconfGetStatus()){
		case 0:break;//NONE
		case 1:break;//INIT
		case 2:utility.netconfUpdate(1);break;//VISIBLE
		case 3:utility.netconfShutdownStart();break;//QUIT
		case 4:run=0;break;//FINISHED
		default:break;
	}
	display.WaitVblankStart();
	gu.SwapBuffers();
}

// -- -- display status -- -- //
param.action=PSP_NETCONF_ACTION_DISPLAYSTATUS;
utility.netconfInitStart(param);
run=1;
while(run){
	gu.Start(GU_DIRECT);
	gu.Clear(5);
	gu.Finish();
	switch(utility.netconfGetStatus()){
		case 0:break;//NONE
		case 1:break;//INIT
		case 2:utility.netconfUpdate(1);break;//VISIBLE
		case 3:utility.netconfShutdownStart();break;//QUIT
		case 4:run=0;break;//FINISHED
		default:break;
	}
	display.WaitVblankStart();
	gu.SwapBuffers();
}

net.ApctlTerm();
net.InetTerm();
net.Term();
net.unload();

ifhandle.unload();
pspnet.unload();
pspnet_inet.unload();
pspnet_apctl.unload();

exit();
/**/