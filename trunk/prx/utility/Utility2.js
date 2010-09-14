/**
* alert,prompt,confirm have a 2nd argument (optional)
* this argument is evaluated before draw the dialog utility
* - usage :
* alert(str[,cb]);
* - example :
* alert("hello\nworld","drawStuff()");
**/

var display = new Module("prx/sceDisplay.prx");
var gu = new Module("prx/sceGu.prx");
var utility = new Module("prx/sceUtility.prx");

gu.setup();
var choice = 0;//1=yes,2=no,3=cancel
gu.clearColor(0xFFFFFF);//BBGGRR
while(choice!=1){
	var color = prompt("enter a color [hex]","0xBBGGRR");
	if(isNaN(color))
		alert("not a color !");
	else{
		gu.clearColor(color);
		choice = confirm("it is okay ?");
	}
}

gu.term();
utility.unload();
gu.unload();
display.unload();
exit();