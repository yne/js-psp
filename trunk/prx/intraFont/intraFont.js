var sceDisplay = new Module("prx/scedisplay.prx");
var sceGu = new Module("prx/scegu.prx");
sceGuInit();
sceGuStart(0);
sceGuDrawBuffer(GU_PSM_8888, 0, BUF_WIDTH);
sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, 0x88000, BUF_WIDTH);
sceGuDepthBuffer(0x110000, BUF_WIDTH);

sceGuOffset(2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
sceGuDepthRange(65535, 0);
sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
sceGuEnable(GU_SCISSOR_TEST);
sceGuDepthFunc(GU_GEQUAL);
sceGuEnable(GU_DEPTH_TEST);
sceGuFrontFace(GU_CW);
sceGuShadeModel(GU_SMOOTH);
sceGuEnable(GU_CULL_FACE);
sceGuEnable(GU_CLIP_PLANES);
sceGuEnable(GU_BLEND);
sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuClearColor(0xFF00FF00);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
sceGuFinish();
sceGuSync(0,0);

var intra = new Module("prx/intrafont.prx");
intra.Init();
var font = intra.Load("flash0:/font/ltn8.pgf",0);
while(1){
	sceGuStart(0);
	intra.Print(font,15,15,"JS intrafont \n alpha release 0.1");
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplay.WaitVblankStart();
	sceGuSwapBuffers();
}