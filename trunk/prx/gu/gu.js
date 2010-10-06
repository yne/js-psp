var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");

gu.init(-0x060000);
gu.start(0);
gu.drawBuffer(      3,0x000000,512);
gu.dispBuffer(480,272,0x088000,512);
gu.depthBuffer(       0x110000,512);
gu.scissor(0,0,480,272);
gu.enable(GU_SCISSOR_TEST);
gu.finish();
gu.display(1);

var val=1;
while(val<2000){
	var fpu = gu.getFPS()
	gu.start(0);
	gu.clearColor(0x444444);
	gu.clear(5);
	gu.color(0xFFFF00);
	gu.drawArray(2,0x00800180,4,0,[
		{x:240+Math.cos((val+000)*(0.017452))*136,y:136+Math.sin((val+000)*(0.017452))*136},// pi/180
		{x:240+Math.cos((val+120)*(0.017452))*136,y:136+Math.sin((val+120)*(0.017452))*136},
		{x:240+Math.cos((val+240)*(0.017452))*136,y:136+Math.sin((val+240)*(0.017452))*136},
		{x:10.0,y:10.0}]
	);
	gu.finish();
	display.waitVblankStart();
	gu.debugPrint(10,10,0xFFFFFF,"FPS:"+fpu);
	gu.swapBuffers();
	val++;
}
gu.term();
gu.unload();
display.unload();
