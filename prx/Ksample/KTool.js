var k = new KModule("prx/Ksample.prx");
printf("act FW :"+k.call("getDevkitVersion").toString(16)+"\n");
printf("shi FW :"+k.call("getShippedFW").toString(16)+"\n");
printf("BatSer :"+k.call("getBatSerial")+"\n");
printf("BatSer :"+k.call("setBatSerial",0x12345678)+"\n");//-1319368834
printf("Tachyon:"+k.call("getTachyonVersion")+"\n");
printf("Baryon :"+k.call("getBaryonVersion")+"\n");
printf("Pommel :"+k.call("getPommelVersion")+"\n");

printf("API    :"+k.call("getKernelInitApitype")+"\n");
printf("model  :"+(k.call("getModel")?"slim+":"fat")+"\n");
printf("SE     :"+k.call("getSE")+"\n");
printf("DevHook:"+k.call("getDevhook")+"\n");
printf("Version:"+k.call("getVersion").toString(16)+"\n");
exit();
 