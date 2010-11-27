var gu = new Module("prx/sceGu.prx");
var intra = new Module("prx/intraFont.prx");
var dsp = new Module("prx/sceDisplay.prx");

sceGuSetup();//non-standard function
sceGuClearColor(0xFF888888);
sceGuClearDepth(0);
var font = new Array();
for(var i=0;i<16;i++)
	font[i]=new Font("flash0:/font/ltn"+i+".pgf");

/*
1:0x1:serif
2:0x2:italic
3:0x4:bold
4:0x8:tiny
*/
while(1){
	sceGuStart(GU_DIRECT);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	font[0].print("IntraFont 0.31 by BenHur (JavaScript edition)",0,20);
	for(var i=0;i<8;i++)
		font[i].print("ltn"+i,0,(i+2)*30);
	for(var i=8;i<16;i++){
		font[i].style(2.0,0xFFFFFFFF,0xFF000000,0);
		font[i].print("ltn"+i,240,(i-6)*30);
	}
	sceGuFinish();// End drawing
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();//waiting for vsync
	sceGuSwapBuffers();//Swap buffers
}
//*/
exit();