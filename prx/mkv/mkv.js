var mkv = new Module("prx/MKV.prx");
var info = mkv.open("res/video1.mkv");
for(i in info){
	printf(i+"="+info[i]+"\n");
}
mkv.close(info);
mkv.unload();
exit();