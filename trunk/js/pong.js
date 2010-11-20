var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var ctrl = new Module("prx/sceCtrl.prx");

gu.init(-0x060000);
gu.start(0);
gu.drawBuffer(      3,0x000000,512);
gu.dispBuffer(480,272,0x088000,512);
gu.depthBuffer(       0x110000,512);
gu.scissor(0,0,480,272);
gu.enable(GU_SCISSOR_TEST);
gu.finish();
gu.display(1);

var pad=0,v=3.0,ya=135.0,yb=105.0,bx=240.0,by=136.0,bsx=-3.0,bsy=-3.0,sA=0;sB=0,bg=0x0;
while(!(pad&PSP_CTRL_START)){
	pad = ctrl.peekBufferPositive().Buttons;
//deplacement des players
	if(pad&PSP_CTRL_DOWN)ya+=v;
	if(pad&PSP_CTRL_UP)ya-=v;
	if(pad&PSP_CTRL_CROSS)yb+=v;
	if(pad&PSP_CTRL_TRIANGLE)yb-=v;
//check des positions
	if(ya<32)ya=32;
	if(ya>240)ya=240;
	if(yb<32)yb=32;
	if(yb>240)yb=240;
//check des bordures
	if(by<0||by>272)bsy=-bsy;
//perte de balle
	if(bg)bg--;
	if(bsx<0&&bx<0){
		sA--;
		bsx=-bsx;
		bg=0x0000FF;
	}
	if(bsx>0&&bx>480){
		sB--;
		bsx=-bsx;
		bg=0x0000FF;
	}
//rebond de balle
	if((bsx<0)&&(bx<32)&&(bx>16)&&(by<ya+32)&&(by>ya-32)){
		bsx=-bsx*1.01;
		v*=1.01;
	}
	if((bsx>0)&&(bx>448)&&(bx<464)&&(by<yb+32)&&(by>yb-32)){
		bsx=-bsx*1.01;
		v*=1.01;
	}
//deplacement
	bx+=bsx;
	by+=bsy;
//efface l'ecran
	gu.start(0);
	gu.clearColor(bg);
	gu.clear(5);
//dessine les raquettes
	gu.color(0x00FF00);//BBGGRR
	gu.drawArray(6,0x00800180,6,0,[
		{x:24,  y:ya-32},{x:32,  y:ya+32},//raquette gauche
		{x:456, y:yb-32},{x:448, y:yb+32},//raquette droite
		{x:bx-4,y:by-4 },{x:bx+4,y:by+4 }//balle
		]
	);
//swap des buffer
	gu.finish();
	display.waitVblankStart();
	gu.debugPrint(230,10,0xFFFFFF,"FPS:"+gu.getFPS());
	gu.debugPrint(130,30,0xFFFFFF,"A :"+sA);
	gu.debugPrint(330,30,0xFFFFFF,"B :"+sB);
	gu.swapBuffers();
}

gu.term();
//gu.unload();
//display.unload();
