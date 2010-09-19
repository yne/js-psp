//load libs
var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var ctrl = new Module("prx/sceCtrl.prx");
var io = new Module("prx/sceIo.prx");
var eldorado = new Module("prx/eldorado.prx");
//load the files
var titles = new File("res/titles.img").read();//images of titles
var pal = new File("res/titles.pal").read();//titles palette
var map = new File("res/world.map").read();//world map
//init graphic
gu.init(0x4000);
gu.start(GU_DIRECT);
gu.dispBuffer(480,272,0x000000,512);
gu.drawBuffer(GU_PSM_8888,0x088000,512);
gu.disable(GU_DEPTH_TEST);
gu.enable(GU_SCISSOR_TEST);
gu.enable(GU_TEXTURE_2D);
gu.scissor(0,0,480,272);
//set image+palette
gu.clutMode(GU_PSM_5551,0,255,0);
gu.clutLoad(8/8,pal);
gu.texMode(GU_PSM_T4,0,0,1);
gu.texFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
gu.texImage(0,256,512,256,titles);

gu.finish();
gu.display(1);
//main loop
var x=y=2048;
while(1){
	gu.start(GU_DIRECT);
	var btn = ctrl.peekBufferPositive().Buttons;
	if(btn){
		if(btn&PSP_CTRL_UP)y--;
		if(btn&PSP_CTRL_DOWN)y++;
		if(btn&PSP_CTRL_LEFT)x--;
		if(btn&PSP_CTRL_RIGHT)x++;
		if(btn&PSP_CTRL_START)break;
	}
	eldorado.mapToArray(x,y,map);//draw the map
	gu.finish();
	display.waitVblankStart();
	gu.swapBuffers();
}
//unload lib
eldorado.unload();
ctrl.unload();
io.unload();
gu.term();
gu.unload();
display.unload();
