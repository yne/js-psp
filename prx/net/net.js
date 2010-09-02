var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
gu.init();
gu.start(GU_DIRECT);
gu.drawBuffer(GU_PSM_8888,0,BUF_WIDTH);
gu.dispBuffer(SCR_WIDTH,SCR_HEIGHT,0x88000,BUF_WIDTH);
gu.depthBuffer(0x110000,BUF_WIDTH);
gu.offset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
gu.viewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
gu.depthRange(0xc350,0x2710);
gu.scissor(0,0,SCR_WIDTH,SCR_HEIGHT);
gu.enable(2);
gu.color(0xFFFFFF00);
gu.clearColor(0xff554433);
gu.clearDepth(0);
gu.finish();
gu.sync(0,0);
gu.display(1);

var net = new Module("prx/sceNet.prx");
net.init(128*1024, 42, 4*1024, 42, 4*1024);

net.inetInit();
net.apctlInit(0x8000, 48);

// -- -- connect acces point -- -- //
var utility = new Module("prx/sceUtility.prx");
utility.netconfInitStart({action:PSP_NETCONF_ACTION_CONNECTAP_LASTUSED});
var run=1;
while(run){
	gu.start(GU_DIRECT);
	gu.clear(5);
	gu.finish();
	switch(utility.netconfGetStatus()){
		case 0:break;//NONE
		case 1:break;//INIT
		case 2:utility.netconfUpdate(1);break;//VISIBLE
		case 3:utility.netconfShutdownStart();break;//QUIT
		case 4:run=0;break;//FINISHED
		default:break;
	}
	display.WaitVblankStart();
	gu.swapBuffers();
}
utility.unload();

//resolve google.com domain
net.resolverInit();
var resId = net.resolverCreate();
printf("google.com:"+net.resolverStartNtoA(resId,"google.com")+"\n");
net.resolverDelete(resId);
net.resolverTerm();

//stop net services !important!
net.apctlTerm();
net.inetTerm();
net.term();

// unload js stuf
net.unload();
gu.unload();
display.unload();

exit();