var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var io = new Module("prx/sceIo.prx");
var ctrl = new Module("prx/sceCtrl.prx");
/*
var jpeg = new Module("prx/libJpeg.prx");

var pic = jpeg.open(new File("res/sample.jpg"));
jpeg.unload();
printf("["+pic.imgW+"x"+pic.imgH+"] ("+pic.texW+"x"+pic.texH+")\n");

gu.setup();

////printf(pic.data.charCodeAt(0)+" "+pic.data.charCodeAt(1)+" "+pic.data.charCodeAt(2)+" "+pic.data.charCodeAt(3)+"\n")
var x=y=0;
while(1){
	var key = ctrl.peekBufferPositive().Buttons
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
*/
var tmp = io.open("res/sample.jpg");
for(i in tmp)
	printf(i+" "+tmp[i]+"\n")
ctrl.unload();
io.unload();
gu.unload();
display.unload();

//exit();