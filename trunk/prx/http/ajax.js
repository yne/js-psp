var display = new Module("prx/sceDisplay.prx");
var ctrl = new Module("prx/sceCtrl.prx");
var gu = new Module("prx/sceGu.prx");
gu.setup();
/* init Net lib*/
var net = new Module("prx/sceNet.prx");
net.init(128*1024, 42, 4*1024, 42, 4*1024);
net.inetInit();
net.apctlInit(0x8000, 48);
net.resolverInit();
/* Connect to last AccesPoint */
var utility = new Module("prx/sceUtility.prx");
utility.connectAP();
utility.unload();
/* AJAX stuff */
var wait = 1,page="";
var http = new Module("prx/sceHttp.prx");
var xhr = new XMLHttpRequest("myUserAgent");//non-standard parameter to specifie PSP's UA
xhr.onreadystatechange = function(){//called after each : open(0),connect(1),request(2),download(4)
	if(xhr.readyState==4){
		wait = 0;//will break the wait look
		page=xhr.responseText;
	}
}
xhr.open('GET',"http://eldorado.psp-online.net/env.pl", true);//methode,url,asynchrone
xhr.send("POST ARGUMENT");//only used if the open methode == 'POST'
while(wait){
	display.waitVblankStart();
}
printf(xhr.responseText+"\n");
/* unload+exit stuff */
http.unload();
net.unload();
gu.unload();
ctrl.unload();
display.unload();

exit();