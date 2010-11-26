var sce = new Module("prx/deflt/libdeflt.prx");
printf("--GZIP--");
printf("\nvalid:"+sceGzipIsValid("res/text.txt.gz"));
printf("\nname :"+sceGzipGetName("res/text.txt.gz"));
printf("\ninfo :"+sceGzipGetInfo("res/text.txt.gz"));
printf("\ncomm :"+sceGzipGetComment("res/text.txt.gz"));
printf("\n--GZIP--");
printf("\n"+sceZlibIsValid("res/text.zip")+"\n");
exit();