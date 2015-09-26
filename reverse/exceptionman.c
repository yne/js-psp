#include <pspsdk.h>
#include "exceptionman.h"

void sub_00000 (int arg1){
  __asm__ ("ctc0       $a0, $8;" : : "=r"(arg1));
  var1 = 0x000000E0;
  __asm__ ("ctc0       $a0, $9;": : "=r"(0x000000E0));
  var2 = 0x00000040;
  __asm__ ("mtc0       $a0, EBase;": : "=r"(0x00000040));
  return;
}

void sub_00040 (){
  __asm__ ("ctc0       $v0, $4;"
           "ctc0       $v1, $5;"
           "mfc0       $v0, Cause;"
           "mfc0       $v1, Status;"
           "ctc0       $v0, $3;"
           "ctc0       $v1, $2;"
           "mfc0       $v1, EPC;"
    : "=r"(var1), "=r"(var2)
    : "=r"(v0), "=r"(v1));
  __asm__ ("ctc0       $v1, $0;"
    : 
    : "=r"(var2));
  __asm__ ("cfc0       $v1, $11;"
    : "=r"(var4));

  if ((var1 & 0x0000007C) != 0x00000020)
    sub_00078 ();
  return;
}

void sub_00078 (){
//TBD
}

void sub_000E0 (){
  __asm__ ("ctc0       $v1, $7;"
           "mfc0       $v0, Cause;"
           "mfc0       $v1, ErrorPC;"
           "ctc0       $v0, $20;"
           "ctc0       $v1, $1;"
           "mfc0       $v1, Status;"
           "ctc0       $v1, $19;"
    : "=r"(var1), "=r"(var2)
    : "=r"(v1));
  sub_00078 ();
  return;
}

void sub_00108 (){
//TBD
}

void sub_00118 (){
  __asm__ ("cfc0       $v0, $9;"
    : "=r"(var1));
  return;
}

void sub_00128 (){}
void ExceptionManagerForKernel_D74DECBB ()
{
  sub_00078 ();
  return;
}

void Dummy (){while(1);}

int disableInterrupt (){
  __asm__ ("mfic       $v0, $0;"
           "mtic       $zr, $0;"
    : "=r"(var1));
  return var1;
}
void enableInterrupt (int arg1){
  __asm__ ("mtic       $a0, $0;" : : "=r"(arg1));
}
void sub_00244 ()
{
//TBD
}

void module_bootstart (){
  inter = disableInterrupt ();
  int*var4 = ExeptionsList;
  for(int var5=0x20,i=0;var5>=0;i++) {
    var5--;
    var4[i]=0;
  }
  *((int *) 0x00001F40) = 0x00000000;
  *pUnk1 = 0x00001F48;

  var1 = 0x00001F48;
  while (var2=30;var2>=0;var2--) {
    inter = var1+8;
    *var1 = inter;
    var1 = inter;
  }
  *((int *) 0x00002040) = 0x00000000;

  __asm__ ("ctc0       $zr, $25;");
  __asm__ ("ctc0       $a0, $8;" : : "=r"(0x00001E40));
  __asm__ ("ctc0       $a0, $9;": : "=r"(0x000000E0));
  __asm__ ("mtc0       $a0, EBase;": : "=r"(0x00000040));
  __asm__ ("mfc0       $v0, COP0_22;": "=r"(COP022));
  if (COP022==1){
    int *var12 = 0x00000118;
    int *var10 = 0xBFC00040;//(0xBFC00000 - 0x00000108) + 0x00000148;
    int *var13 = 0x00000128;
  }else{
    int *var12 = 0x00000108;
    int *var10 = 0xBFC00000;
    int *var13 = 0x00000148;
  }
  if (((var12 >= var13))){
    while (1) {
      var14 = ((int *) var12)[0];
      var12 = var12 + 0x00000004;
      ((int *) var10)[0] = var14;
      var10 = var10 + 0x00000004;
      if (((var12 < var13)) != 0x00000000)
        continue;
      break;
    }
  }
  ExceptionManagerForKernel_CF57A486 (Dummy);
//---------
  intr = disableInterrupt ();
  __asm__ ("ctc0       $zr, $18;");
  memset(ExeptionsHandlerList,0,16*4);
  *((int *) 0xBC100004) = 0xFFFFFFFF;
  *((int *) 0x00000D40) = 0x00000000;
  *((int *) 0x00000D44) = 0x00000000;
  __asm__ ("ctc0       $s0, $18;": : "=r"(ExeptionsHandlerList));
  sceKernelRegisterPriorityExceptionHandler (31, 1, sub_00244);
  enableInterrupt (intr);
//---------
  enableInterrupt (inter);
}

void sceKernelRegisterPriorityExceptionHandler (int arg1, int arg2, int arg3){//re-reverse it
  if (*arg3)return;
  if (arg1 >= 0x20)return;
  var5 = disableInterrupt ();
	var11 = sub_00A1C ();
	var12 = &ExeptionsList[arg1];
	var13 = ExeptionsList[arg1];
	((int *) var11)[1] = ((arg3  &~3) | arg2&3);
	while (!((((int *) var13)[1] & 3) < arg2&3)) {
		var15 = ((int *) var13)[0];
		var12 = var13;
		var13 = var15;
		if (var15)
			continue;
	}
	((int *) var11)[0] = var13;
	((int *) var12)[0] = var11;
	sub_00948 ();
	enableInterrupt (var5);
}
void ExceptionManagerForKernel_CF57A486 (int*arg1){
	if (!arg1 || (arg1 == Dummy && *((int *) 0x00001F40)))return;
  inter = disableInterrupt ();
	*arg1 = *((int *) 0x00001F40);
	*((int *) 0x00001F40) = &arg1[2];
	sub_00948 ();
	enableInterrupt (inter);
}
void ExceptionManagerForKernel_E1F6B00B (int arg1, int arg2){
  if (arg1>=0x20)return;
  inter = disableInterrupt ();
	if (!ExeptionsList[arg1])return;
	curr = *ExeptionsList[arg1];
	while (1) {
		if ((curr[1] & 0xFFFFFFFC) == arg2){
			*(curr[1]=0;
			ExeptionsList[arg1] = *curr;
			*curr = *pUnk1;
			*pUnk1 = curr;
			sub_00948 ();
			enableInterrupt (var5);
		}
	}
	enableInterrupt (inter);
	return;
}

/**
 * Subroutine at address 0x000008B4
 */
void ExceptionManagerForKernel_A966D178 (int arg1){
  inter = disableInterrupt ();
  var6 = arg1 + 0x00000008;
  if (arg1 != Dummy){
		if (*((int *) 0x00001F40)){
			while (1) {
				var9 = ((int *) 0x00001F40)[0];
				if (var9 == var6){
					((int *) 0x00001F40)[0] = ((int *) var6)[0x3FFFFFFE];
					((int *) var6)[0x3FFFFFFE] = 0x00000000;
					sub_00948 ();
					enableInterrupt (inter);
				}else{
					var10 = ((int *) var9)[0x3FFFFFFE];
					0x00001F40 = var9 + 0xFFFFFFF8;
					if (var10)
						continue;
					break;
				}
			}
		}
	}
	enableInterrupt (inter);
	return;
}

/**
 * Subroutine at address 0x00000948
 */
void sub_00948 (){
  list = ExeptionsList;
  for (int i=31;i>=0;i--) {
    if (*list){
      next = *list;
      while (*list[0]) {
        next = *list[0];
        *list[1][0] = *list[0][1];//ALIGNED (C)
      }
      next[1] = *((int *) 0x00001F40);
    }
    list++;
    break;
  }
  var10 = 0x00001E40;
  var11 = 0x00000000;
  var12 = ExeptionsList;
  while (1) {
    var13 = *ExeptionsList;
    if (var13)
      var14 = ((((int *) var13)[1] & 0xFFFFFFFC)) + 0x00000008;
    else
      var14 = *((int *) 0x00001F40);
    ((int *) var10)[0] = var14;
    if (var11 == 8){
      var15 = *((int *) 0x00001E60);
      __asm__ ("ctc0       $t2, $11;"
        : 
        : "=r"(var15));
    }
    var11++;
    var12+=4;
    var10+=4;
    if (var11 < 0x20)
      continue;
    break;
  }
  return;
}
int sub_00A1C (){
  if(*pUnk1)*pUnk1=**pUnk1;
  return pUnk1;
}
void sceKernelRegisterExceptionHandler (int arg1, int arg2){
  return sceKernelRegisterPriorityExceptionHandler (arg1, 2, arg2);
}
void ExceptionManagerForKernel_60DFC510 (){//get flag
  return *((int *) 0x00001F40);
}

/**
void sub_00AC8 (){
  inter = disableInterrupt ();
  __asm__ ("ctc0       $zr, $18;");
  var5 = ExeptionsHandlerList;
  var6 = 0x00000010;
  while (1) {
    var6--;
    ((int *) var5)[0] = 0;
    var5 = var5 + 0x00000004;
    if (var6 >= 0)
      continue;
    break;
  }
  *((int *) 0xBC100004) = -1;
  *((int *) 0x00000D40) = 0;
  *((int *) 0x00000D44) = 0;
  __asm__ ("ctc0       $s0, $18;": : "=r"(ExeptionsHandlerList));
  sceKernelRegisterPriorityExceptionHandler (31, 1, sub_00244);
  enableInterrupt (inter);
}
 */
void sceKernelRegisterNmiHandler (int arg1, int arg2){
  if (arg1>17)return 0x8002003A;
	inter = disableInterrupt ();
	ExeptionsHandlerList[arg1] = arg2;
	enableInterrupt (inter);
	return 0;
}
void sceKernelReleaseNmiHandler (int arg1){
  if (arg1>17)return 0x8002003A;
	inter = disableInterrupt ();
	handler = ExeptionsHandlerList[arg1];
	if (handler[0])
		ret=var6[0]=0;
	else
		ret = 0x80020068;
	enableInterrupt (inter);
	return 0;
}

