var ctrl = new Module("prx/sceCtrl.prx");
var gu = new Module("prx/sceGu.prx");
var display = new Module("prx/sceDisplay.prx");

gu.init(-0x060000);//0x060000 byte in VRAM
gu.start(0);
gu.drawBuffer(      3,0x000000,512);
gu.dispBuffer(480,272,0x088000,512);
gu.depthBuffer(       0x110000,512);
gu.scissor(0,0,480,272);
gu.enable(GU_SCISSOR_TEST);
gu.finish();
gu.display(1);
var oldpad=0,cursorX=5,cursorY=5,running=1;
/*algo*/
var intGame=0,intHint=0,intComPanel=0,intComCount=0;
var intPanel=new Array(64);
var intStack=new Array(64);
var intEnablePointA=new Array(9,1,6,2,3,7,1,9,1,1,2,1,1,3,1,1,6,2,3,4,5,4,3,7,2,1,4,0,0,5,1,3,3,1,5,0,0,4,1,2,7,3,4,5,4,3,2,6,1,1,3,1,1,2,1,1,9,1,7,3,2,6,1,9);
var intEnablePointB=new Array(9,1,7,3,2,6,1,9,1,1,3,1,1,2,1,1,7,3,4,5,4,3,2,6,3,1,5,0,0,4,1,2,2,1,4,0,0,5,1,3,6,2,3,4,5,4,3,7,1,1,2,1,1,3,1,1,9,1,6,2,3,7,1,9);

function output(i,n){//update the board
drawBoard();
/*	var color="#808080";
	switch(n){
		case 1: color="#000000";break
		case 2: color="#ffffff";break
	}
	document.getElementById("divPanel" + i).style.backgroundColor=color;*/
}
var dbg="";
function info(str){
	//document.title=str;
	printf(str+"\n");
	dbg=str;
	drawBoard();
}
// code found on : dgrfactory.jp/js/othello
function calNextPanel(intMyColor,intYourColor,intEnableA,intEnableB){
	var i=0,j=0,k=0,l=0,intNum=0,intPoint=0,intPointA=0,intPointB=0,intPointC=0,intMaxPoint=-9999,intCount=0;
	var intPanelStackA=new Array(64);
	var intPanelStackB=new Array(64);
	var intPanelStackC=new Array(64);
	var intArray=new Array(64);
	info("thinking...");
	for (i=0; i < 64; i++) if (intPanel[i] == 0){
		intNum=0;
		intNum=getChangePanelAfter(i,-1,-1,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,-1,0,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,-1,1,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,0,-1,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,0,1,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,1,-1,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,1,0,intMyColor,intYourColor);
		intNum += getChangePanelAfter(i,1,1,intMyColor,intYourColor);
		if (intNum > 0){
			info("thinking...  "+Math.floor(i/64*100)+"%");
			intPointA=-9999;
			intPointB=-9999;
			intPointC=-9999;
			for (j=0; j < 64; j++) intPanelStackA[j]=intPanel[j];
			changePanel(i,intMyColor);
			for (j=0; j < 64; j++) if (intPanelStackA[j] == 0 && intPanel[j] == intMyColor && intPointA < intEnableA[j]) intPointA=intEnableA[j];
			for (j=0; j < 64; j++) if (intPanel[j] == 0){
				intNum=0;
				intNum=getChangePanelAfter(j,-1,-1,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,-1,0,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,-1,1,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,0,-1,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,0,1,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,1,-1,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,1,0,intYourColor,intMyColor);
				intNum += getChangePanelAfter(j,1,1,intYourColor,intMyColor);
				if (intNum > 0){
					for (k=0; k < 64; k++) intPanelStackB[k]=intPanel[k];
					changePanel(j,intYourColor);
					for (k=0; k < 64; k++) if (intPanelStackB[k] == 0 && intPanel[k] == intYourColor && intPointB < intEnableB[k]) intPointB=intEnableB[k];
					for (k=0; k < 64; k++) if (intPanel[k] == 0){
						intNum=0;
						intNum=getChangePanelAfter(k,-1,-1,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,-1,0,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,-1,1,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,0,-1,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,0,1,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,1,-1,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,1,0,intMyColor,intYourColor);
						intNum += getChangePanelAfter(k,1,1,intMyColor,intYourColor);
						if (intNum > 0){
							for (l=0; l < 64; l++) intPanelStackC[l]=intPanel[l];
							changePanel(k,intMyColor);
							for (l=0; l < 64; l++) if (intPanelStackC[l] == 0 && intPanel[l] == intMyColor && intPointC < intEnableA[l]) intPointC=intEnableA[l];
							for (l=0; l < 64; l++) intPanel[l]=intPanelStackC[l];
						}
					}
					for (k=0; k < 64; k++) intPanel[k]=intPanelStackB[k];
				}
			}
			for (j=0; j < 64; j++) intPanel[j]=intPanelStackA[j];
			intPoint=intPointA - intPointB - intPointC;
			if (intPoint > intMaxPoint){
				intArray[0]=i;
				intCount=1;
				intMaxPoint=intPoint;
			}else if (intPoint == intMaxPoint){
				intArray[intCount]=i;
				intCount++;
			}
		}
	}
	info("ready ...");
	if(!intCount)info("IA error");
	return intArray[Math.floor(Math.random() * intCount) % intCount];
}
function changePanelStart(intID,intX,intY,intNum,intColor){
	var i,intCheck=intID;
	for (i=0; i < intNum; i++){
		intCheck += intY * 8 + intX;
		intPanel[intCheck]=intColor;
	}
}
function changePanel(intID,intColor){
	intPanel[intID]=intColor;
	changePanelStart(intID,-1,-1,getChangePanel(intID,-1,-1,intColor),intColor);
	changePanelStart(intID,-1,0,getChangePanel(intID,-1,0,intColor),intColor);
	changePanelStart(intID,-1,1,getChangePanel(intID,-1,1,intColor),intColor);
	changePanelStart(intID,0,-1,getChangePanel(intID,0,-1,intColor),intColor);
	changePanelStart(intID,0,1,getChangePanel(intID,0,1,intColor),intColor);
	changePanelStart(intID,1,-1,getChangePanel(intID,1,-1,intColor),intColor);
	changePanelStart(intID,1,0,getChangePanel(intID,1,0,intColor),intColor);
	changePanelStart(intID,1,1,getChangePanel(intID,1,1,intColor),intColor);
	return false;
}
function checkGameOver(){
	var i=0;
	for (i=0; i < 64; i++) if (intPanel[i] == 0) return false;//full board
	if (checkPass(1)&&checkPass(2)) return true;
	if (!(getNum(1)&&getNum(2))) return true;//no more piece
	return false;
}
function checkPanel(intID,intColor){
	if (getChangePanel(intID,-1,-1,intColor) > 0) return true;
	if (getChangePanel(intID,-1,0,intColor) > 0) return true;
	if (getChangePanel(intID,-1,1,intColor) > 0) return true;
	if (getChangePanel(intID,0,-1,intColor) > 0) return true;
	if (getChangePanel(intID,0,1,intColor) > 0) return true;
	if (getChangePanel(intID,1,-1,intColor) > 0) return true;
	if (getChangePanel(intID,1,0,intColor) > 0) return true;
	if (getChangePanel(intID,1,1,intColor) > 0) return true;
	return false;
}
function checkPass(intColor){
	var i=0;
	for (i=0; i < 64; i++) if (intPanel[i] == 0 && checkPanel(i,intColor)) return false;
	return true;
}
function input(intID){// <<< input
	if (intGame != 1) return false;
	if (intPanel[intID] != 0){
		info("already taken");
		return false;
	}
	if (!checkPanel(intID,1)){
		info("bad placement");
		return false;
	}
	intGame=2;
	changePanel(intID,1);
	showPanel();
	clickPanelStep1();
	return true;
}
function clickPanelStep1(){
	if (checkGameOver()){
		intGame=0;
		info("Black:" + getNum(1) + "\nWhite" + getNum(2));
		return true;
	}
	if (checkPass(2)){
		info("IA can't play");
		clickPanelStep4();
		return true;
	}
	intComCount=4;
	clickPanelStep3();
	return true;
}
function clickPanelStep3(){
	switch (intComCount){
		case 4:intComPanel=calNextPanel(2,1,intEnablePointB,intEnablePointA);break;
		case 3:case 1:output(intComPanel,2);break;
		case 2:case 0:output(intComPanel,0);
	}
	switch (intComCount){
		case 4:case 3:case 2:case 1:intComCount--;clickPanelStep3();break;
		case 0:changePanel(intComPanel,2);clickPanelStep4();
	}
	return true;
}
function clickPanelStep4(){
	showPanel();
	if (checkGameOver()){
		intGame=0;
		info("Black:" + getNum(1) + "\nWhite:" + getNum(2));
		return true;
	}
	if (checkPass(1)){
		info("you can't play now");
		clickPanelStep1();
		return true;
	}
	intGame=1;
	return true;
}
function getChangePanel(intID,intX,intY,intColor){
	var intNum=0;
	var intCheckX=intID % 8 + intX;
	var intCheckY=Math.floor(intID / 8) + intY;
	while (intCheckX >= 0 && intCheckX <= 7 && intCheckY >= 0 && intCheckY <= 7){
		if (intPanel[intCheckY * 8 + intCheckX] == 0) return 0;
		if (intPanel[intCheckY * 8 + intCheckX] == intColor) return intNum;
		if (intPanel[intCheckY * 8 + intCheckX] != intColor) intNum++;
		intCheckX += intX;
		intCheckY += intY;
	}
	return 0;
}
function getChangePanelAfter(intID,intX,intY,intMyColor,intYourColor){
	var intNum=getChangePanel(intID,intX,intY,intMyColor);
	if (intNum == 0) return 0;
	var intMinus=0;
	intMinus=getChangePanel(intID + intX * intNum + intY * intNum * 8,intX,intY,intYourColor);
	if (intMinus == 0) return intNum + 10; else return 10 - intNum - intMinus;
}
function getNum(intColor){
	var i=0,intNum=0;
	for (i=0; i < 64; i++) if (intPanel[i] == intColor) intNum++;
	return intNum;
}
function showPanel(){
	var i=0;
	var j=1;
	for (i=0; i < 64; i++){
		if (intPanel[i] != intStack[i]) if (intPanel[i] == 0) output(i,0); else if (intPanel[i] == 1) output(i,1); else output(i,2);
		if (intPanel[i] != 0) j=0;
		intStack[i]=intPanel[i];
	}
	return j == 1;
}
function startGame(){
	if (intGame == 2) return false;
	var i=0;
	//if (intGame == 1) if (!confirm("reload ?")) return true;
	intGame=2;
	for (i=0; i < 64; i++){
		intPanel[i]=0;
		intStack[i]=-1;
	}
	intPanel[27]=2;
	intPanel[28]=1;
	intPanel[35]=1;
	intPanel[36]=2;
	showPanel();
	intGame=1;
	info("you are : black");
}
/*endof algo*/
function drawPlayer(player,color){
	var ret=[],n=0;
	for(var i=0;i<64;i++){
		if(intStack[i]==player){
			ret[n]={x:((i&7)*34+105),y:(i>>3)*34+1}
			ret[n+1]={x:ret[n].x+32,y:ret[n].y+32}
			n+=2;
		}
	}
	gu.color(color);
	gu.drawArray(6,0x00800180,ret.length,0,ret);
}
function drawBoard(){
	gu.start(0);
	gu.clearColor(0x0);
	gu.clear(5);
	gu.color(0x707070);//BBGGRR
	gu.drawArray(6,0x00800180,2,0,[{x:104, y:0},{x:376, y:272}]);//34*8 = 272 bish
	drawPlayer(0,0x808080);
	drawPlayer(1,0x000000);
	drawPlayer(2,0xFFFFFF);
//draw cursor
	gu.color(0x0000FF);
	gu.drawArray(GU_LINE_STRIP,0x00800180,5,0,[//pas de thune, elle a raquer la boufe : j'avais deja claquer 2 places pour fast-n-furious ...
		{x:(cursorX+0)*34+104, y:(cursorY+0)*34},
		{x:(cursorX+1)*34+103, y:(cursorY+0)*34},
		{x:(cursorX+1)*34+103, y:(cursorY+1)*34-1},
		{x:(cursorX+0)*34+104, y:(cursorY+1)*34-1},
		{x:(cursorX+0)*34+104, y:(cursorY+0)*34}
	]);
	gu.finish();//disparition des pandaaaaaas !
	gu.debugPrint(0,10,0xFFFFFF,dbg);
	display.waitVblankStart();
	gu.swapBuffers();
}
function updateCtrl(){
	var pad = ctrl.peekBufferPositive().Buttons;
	if(pad!=oldpad){
		oldpad=pad;
		if(pad&PSP_CTRL_UP){
			cursorY--;
			if(cursorY<0)cursorY=0;
		}
		if(pad&PSP_CTRL_DOWN){
			cursorY++;
			if(cursorY>7)cursorY=7;			
		}
		if(pad&PSP_CTRL_LEFT){
			cursorX--;
			if(cursorX<0)cursorX=0;
		}
		if(pad&PSP_CTRL_RIGHT){
			cursorX++;
			if(cursorX>7)cursorX=7;
		}
		if(pad&PSP_CTRL_CROSS){
			input(cursorX+cursorY*8);
		}
		if(pad&PSP_CTRL_SELECT){
			startGame();
		}
		if(pad&PSP_CTRL_START){
			running=0;
		}
		//printf("x:"+cursorX+" y:"+cursorY+"\n")
	}
}

/*main loop*/
while(running){
	updateCtrl()
	drawBoard();
}

ctrl.unload();
gu.unload();
display.unload();
//exit();