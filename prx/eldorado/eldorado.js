//load libs
var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var ctrl = new Module("prx/sceCtrl.prx");
var io = new Module("prx/sceIo.prx");
var eldorado = new Module("prx/eldorado.prx");
var osk = new Module("prx/lightOsk.prx");
//load the files
var kb1 =    new File("prx/lightOsk/osk.raw").read();//world map
var map =    new File("prx/eldorado/map/world.map").read();//world map
var titles = new File("prx/eldorado/map/titles.raw");//images of titles
var pal =    new File("prx/eldorado/map/titles.rawpal");//titles palette

var player = new File("prx/eldorado/player.raw");//images of the player
var charmap="QR?PTUVSXYZWKL(J    NO)MBC:AEF_DHI-G\n"
//init graphic
sceGuInit(0x4000);
sceGuStart(GU_DIRECT);
sceGuDispBuffer(480,272,0,512);
sceGuDrawBuffer(GU_PSM_8888,0,512);
sceGuDisable(GU_DEPTH_TEST);
sceGuEnable(GU_TEXTURE_2D);
sceGuScissor(0,0,480,272);
sceGuEnable(GU_SCISSOR_TEST);
sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);//activated later
sceGuAlphaFunc(GU_GREATER, 0, 0xff);
//sceGuSetCallback//sceGuCallMode
sceGuFinish();
sceGuDisplay(1);
//main loop
eldorado.setTitle(titles.read());
eldorado.setPal(pal.read());
eldorado.setPlayer(player.read());
var dir=1,step=0;
while(1){
	var btn = ctrl.peekBufferPositive().Buttons;
	gu.start(GU_DIRECT);
	if(btn){
	dir=eldorado.setMove(btn);
		step++;
		step%=32;
	}
	
	eldorado.drawLayer(map);//draw the map
	eldorado.drawPlayer(dir,step,player);//draw the player
	var c=osk.draw(kb1,btn);
	if(c!=undefined){
		printf(charmap[c]+"\n");
	}
	gu.finish();
	display.waitVblankStart();
	gu.swapBuffers();
	//printf(gu.getFPS()+"\n");
	//gu.debugPrint(120,260,0xFFFFFF,gu.getFPS()+"fps");
}
//unload lib
eldorado.unload();
ctrl.unload();
io.unload();
gu.unload();
display.unload();
