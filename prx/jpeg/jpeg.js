var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var io = new Module("prx/sceIo.prx");
var ctrl = new Module("prx/sceCtrl.prx");

var jpeg = new Module("prx/sceJpeg.prx");
var pic = jpeg.loadJpeg(new File("res/sample2.jpg").read());

gu.setup();

printf("["+pic.imgW+"x"+pic.imgH+"] ("+pic.texW+"x"+pic.texH+")\n");
var x=y=0;
while(1){
	var key = ctrl.ReadBufferPositive().Buttons
	if(key & PSP_CTRL_UP)y--;
	if(key & PSP_CTRL_DOWN)y++;
	if(key & PSP_CTRL_LEFT)x--;
	if(key & PSP_CTRL_RIGHT)x++;
	if(key & PSP_CTRL_START)break;

	gu.start(GU_DIRECT);

	gu.blitImage(pic,x,y);

	gu.finish();
	gu.sync(0,0);
	sceDisplayWaitVblankStart();
	gu.swapBuffers();
}
//

jpeg.unload();
ctrl.unload();
io.unload();
gu.unload();
display.unload();

//exit();