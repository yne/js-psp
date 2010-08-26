var sceDisplay = new Module("prx/sceDisplay.prx");
var ctrl = new Module("prx/sceCtrl.prx");
var gu = new Module("prx/sceGu.prx");
var intra = new Module("prx/intrafont.prx");

gu.Init();
gu.Start(0);
gu.DrawBuffer(GU_PSM_8888, 0, BUF_WIDTH);
gu.DispBuffer(SCR_WIDTH, SCR_HEIGHT, 0x88000, BUF_WIDTH);
gu.DepthBuffer(0x110000, BUF_WIDTH);
gu.Offset(2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
gu.Viewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
gu.Scissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
gu.Enable(GU_SCISSOR_TEST);

gu.Enable(GU_BLEND);
gu.BlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
gu.Finish();

gu.Display(GU_TRUE);

intra.Init();
var ltn8 = new Font("flash0:/font/ltn8.pgf", 0);
intra.SetStyle(ltn8,1.0,0xFFFFFFFF,0xFF000000,INTRAFONT_SCROLL_LEFT);
var x=0,y=0,h=1,v=1,i=1,partyTime=0,tmp=80;
while(1){
	var key = ctrl.ReadBufferPositive().Buttons
	if(key & PSP_CTRL_CROSS)
		partyTime=1;
	if(key & PSP_CTRL_START)
		break;
	i+=0.05;
	var zoom=(2+Math.sin(i)/3);
	if(partyTime)
		intra.SetStyle(ltn8,zoom*zoom,0xFF000000+Math.random()*0xFFFFFF,0xFF000000+Math.random()*0xFFFFFF,0);
	
	if(x==0)h=1;
	if(x==240)h=-1;
	if(y==0)v=1;
	if(y==272)v=-1;
	x+=h;
	y+=v;
	
	gu.Start(GU_DIRECT);
	if(partyTime)
		gu.ClearColor(0xFF000000+Math.random()*0xFFFFFF);
	else
		gu.ClearColor(0xFF888888);
	gu.ClearDepth(0);
	gu.Clear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

	if(partyTime)
		intra.Print(ltn8,x,y,"It's party time !");
	else
		tmp=intra.Print(ltn8,tmp,250,tmp+"if you are epileptic press X\nelse press start to exit",0);
	gu.Finish();
	gu.Sync(0,0);
	sceDisplay.WaitVblankStart();
	gu.SwapBuffers();
}
intra.unload();
printf(gu.unload()+"\n");
ctrl.unload();
sceDisplay.unload();
