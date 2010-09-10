var gu = new Module("prx/sceGu.prx");
gu.setup();

var video = new Module("prx/video.prx");
video.load("test.mp4");
var i;
do{
	i=video.play();//if succes return the next frame to be played, else return undefined
	sceGuSwapBuffers();
}while(i>0);
video.unload();

gu.term();
gu.unload();
exit();