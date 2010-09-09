var hprm = new Module("prx/sceHprm.prx");

while(1){
	printf("PCK:"+ hprm.PeekCurrentKey() +"\n");
	printf("PL :"+ hprm.PeekLatch() +"\n");//unusable
	printf("RL :"+ hprm.ReadLatch() +"\n");//unusable
	printf("---------------------\n");
	printf("Hp :"+ hprm.IsHeadphoneExist() +"\n");
	printf("Rm :"+ hprm.IsRemoteExist() +"\n");
	printf("Mic:"+ hprm.IsMicrophoneExist() +"\n");
}

hprm.unload();