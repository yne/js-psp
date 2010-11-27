var gu = new Module("prx/sceGu.prx");
var intra = new Module("prx/intraFont.prx");
var dsp = new Module("prx/sceDisplay.prx");

gu.setup();
intraFontInit();
var ltn = intraFontLoad("flash0:/font/ltn0.pgf",0);

while(1){
	sceGuStart(GU_DIRECT);
	sceGuClearColor(0xFF888888);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		intraFontSetStyle(ltn, 1.0,0xFF000000,0xFFFFFFFF,0);
		intraFontPrint(ltn, 180, 80, "IntraFont 0.31 by BenHur");
	sceGuFinish();// End drawing
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();// Swap buffers (waiting for vsync)
	sceGuSwapBuffers();
}

exit();