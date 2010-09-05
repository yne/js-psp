var flv = new Module("prx/FLV1.prx");
var info = flv.open("res/video1.flv");
for(i in info){
	printf(i+"="+info[i]+"\n");
}
flv.close(info);
flv.unload();
exit();