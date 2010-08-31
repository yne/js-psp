var io = new Module("prx/sceIo.prx");
var txt = new File("fichier.txt");

txt.pos = txt.size;//set the position to the end of file
txt.write("!");
printf(txt.read()+"\n");
printf("mod :"+txt.modified+"\n");
printf("acc :"+txt.accessed+"\n");
printf("cre :"+txt.created +"\n");
txt.rename("old");
txt.close();
txt.remove();

io.unload();
exit();
