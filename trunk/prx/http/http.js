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
var tpl = http.createTemplate("PSP");
var cnx = http.createConnection(tpl,"download.fedoraproject.org");
var req = http.createRequestWithURL(cnx,PSP_HTTP_METHOD_GET,"http://download.fedoraproject.org/pub/fedora/linux/releases/13/Live/i686/Fedora-13-i686-Live.iso");
http.sendRequest(req);
var length = http.getContentLength(req);

var io = new Module("prx/sceIo.prx");
var txt = new File("fedo.iso");
var tmp="";var i=0;//409600
do{//23h02.75 
	txt.write(http.readData(req,1024),1024);
	i++;
	printf(i+"/1728\n");
}while(i<1728);
txt.close();
io.unload();

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
net.unload();

gu.term();
gu.unload();

display.unload();

exit();