var kernel = new KModule("prx/Ksample.prx");
printf("FW :"+kernel.call("getDevkitVersion")+"\n");//getDevkitVersion = 0x4F764650 => printf("FW :"+kernel.call(0x4F764650)+"\n");
//printf("bat serial ("+kernel.call("readSerial")+") \n");
//printf("bat write  ("+kernel.call("writeSerial",0x12345678)+") \n");
printf("Pommel ("+kernel.call("getPommelVersion")+") \n");
printf("Baryon ("+kernel.call("getBaryonVersion")+") \n");
printf("Tachyon("+kernel.call("getTachyonVersion")+") \n");
printf("ori FW ("+kernel.call("getShippedFW")+") \n");

exit();
