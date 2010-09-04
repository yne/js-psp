var wlan = new Module("prx/sceWlan.prx");
printf(wlan.getEtherAddr()+"\n");
wlan.unload();
exit();
