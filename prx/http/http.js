var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
gu.setup();

var net = new Module("prx/sceNet.prx");
net.init(128*1024, 42, 4*1024, 42, 4*1024);
net.inetInit();
net.apctlInit(0x8000, 48);
net.resolverInit();

{// -- -- connect acces point -- -- //
var utility = new Module("prx/sceUtility.prx");
utility.netconfInitStart({action:PSP_NETCONF_ACTION_CONNECTAP_LASTUSED});
var run=1;
while(run){
	gu.start(GU_DIRECT);
	gu.clear(5);
	gu.finish();
	switch(utility.netconfGetStatus()){
		case 0:break;//NONE
		case 1:break;//INIT
		case 2:utility.netconfUpdate(1);break;//VISIBLE
		case 3:utility.netconfShutdownStart();break;//QUIT
		case 4:run=0;break;//FINISHED
		default:break;
	}
	display.WaitVblankStart();
	gu.swapBuffers();
}
utility.unload();
}

var http = new Module("prx/sceHttp.prx");
http.init();
var tpl = http.createTemplate("simple browser 2000");
var cnx = http.createConnection(tpl,"google.com");
var req = http.createRequestWithURL(cnx,PSP_HTTP_METHOD_GET,"http://google.com/ig");
http.sendRequest(req);
var length = http.getContentLength(req);
printf(length+"\n")

//do{
printf(http.readData(req,100)+"\n");

//}

http.deleteRequest(req);
http.deleteConnection(cnx);
http.deleteTemplate(tpl);
http.end();
http.unload();
//stop net services !important!
net.resolverTerm();
net.apctlTerm();
net.inetTerm();
net.term();

// unload js stuf
net.unload();
gu.unload();
display.unload();

exit();