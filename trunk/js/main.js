/*
simple script to show simultaneous procsses (ogg decoding/playing + graphic stuff)
*/
var display = include("prx/sceDisplay.prx");
var gu = include("prx/sceGu.prx");
var Aalib = include("prx/aalib.prx");

/*init audio part*/
Aalib.Init();
Aalib.Load("res/loop.ogg",7,1);//Masayoshi Minoshima - Moonlives
Aalib.Play(7);
Aalib.SetAutoloop(7,1);

/*init graph part*/
gu.Init();
gu.Start(GU_DIRECT);
gu.DrawBuffer(3,0x000000,512);//Pixel Format
gu.DispBuffer(480,272,0x088000,512);
gu.DepthBuffer(0x110000,512);
gu.Offset(2048-(480/2),2048-(272/2));
gu.Viewport(2048,2048,480,272);
gu.DepthRange(0xFFFF,0);
gu.Scissor(0,0,480,272);
gu.Enable(2);//States
gu.Finish();
gu.Sync(0,0);
gu.Display(1);

/*main part*/
var val=1;
const cos=Math.cos;
const sin=Math.sin;
while(val<2000){
	gu.Start(GU_DIRECT);
	gu.ClearColor(0x00444444);
	gu.Clear(5);
	gu.Color(0xFFFFFF00);
	gu.DrawArray(Math.floor(val/500),GU_VERTEX_32BITF|GU_TRANSFORM_2D,4,0,[
		{x:240+cos((val+000)*(3.1415/180))*136,y:136+sin((val+000)*(3.1415/180))*136},
		{x:240+cos((val+120)*(3.1415/180))*136,y:136+sin((val+120)*(3.1415/180))*136},
		{x:240+cos((val+240)*(3.1415/180))*136,y:136+sin((val+240)*(3.1415/180))*136},
		{x:10.0,y:10.0}]
	);
	gu.Finish();
	display.WaitVblankStart();
	gu.SwapBuffers();
	val++;
}
//while(1){
//AalibGetStatus(7)==-3)
//}