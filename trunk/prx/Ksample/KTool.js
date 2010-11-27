var k = new KModule("prx/Ksample.prx");
printf("actuFW :"+k.call("getDevkitVersion").toString(16)+"\n");
printf("shipFW :"+k.call("getShippedFW").toString(16)+"\n");
/*setBatSerial argument :
0:autoboot
-1:pandora
other:normal
-1319368834 is nice too
*/
//printf("BatSer :"+k.call("setBatSerial",-1)+"\n");
//printf("BatSer :"+k.call("getBatSerial")+"\n");
printf("Tachyon:"+k.call("getTachyonVersion")+"\n");
printf("Baryon :"+k.call("getBaryonVersion")+"\n");
printf("Pommel :"+k.call("getPommelVersion")+"\n");
printf("API    :"+k.call("getKernelInitApitype")+"\n");
printf("model  :"+(k.call("getModel")?"slim+":"fat")+"\n");
printf("SE     :"+k.call("getSE")+"\n");
printf("DevHook:"+k.call("getDevhook")+"\n");
printf("CtrlVer:"+k.call("getVersion").toString(16)+"\n");

printf("setIPL :"+k.call("setIPL")+"\n");
//printf("getIPL :"+k.call("getIPL")+"\n");
//printf("setMBR :"+k.call("setMBR")+"\n");
//printf("getMBR :"+k.call("getMBR")+"\n");

exit();
