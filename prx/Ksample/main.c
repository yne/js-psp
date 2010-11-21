#include <pspkernel.h>
#include <kubridge.h>
#include <systemctrl.h>
#include <pspsdk.h>
#include <string.h>
#include <malloc.h>

#include "../../main/shared.h"

#define sceSysregGetTachyonVersion sceSysreg_driver_E2A5D1EE
#define sceSysconGetBaryonVersion sceSyscon_driver_7EC5A957
#define sceSysconGetPommelVersion sceSyscon_driver_E7E87741

PSP_MODULE_INFO("KTool",0x1007,1,1);
PSP_NO_CREATE_MAIN_THREAD();

// syscon function for all versions used by silversprings' code
u32 sceSysconCmdExec(void* param, int unk);
u32 sceSysconGetPommelVersion(u32*);
u32 sceSysconGetBaryonVersion(u32*);
u32 sceSysregGetTachyonVersion();
int sceIdStorageReadLeaf(u16 key, void *buf);
/* 
	Battery (code from Open Source Pandora Battery Tool by cory1492)
*/
u16 read_eeprom(u8 addr){ // reversed function by silverspring (more info: http://my.malloc.us/silverspring/2007/12/19/380-and-pandora/)
	if(addr>0x7F)
		return(0);
	u8 param[0x60];
	param[0x0C] = 0x74; // read battery eeprom command
	param[0x0D] = 3;	// tx packet length
	param[0x0E] = addr;	// tx data
 	u32 k1 = pspSdkSetK1(0);
	int res = sceSysconCmdExec(param, 0);
	pspSdkSetK1(k1);
	if (res < 0)
		return(res);
	return((param[0x21]<<8) | param[0x20]);// rx data
}
u32 write_eeprom(u8 addr, u16 data){ // reversed function by silverspring (more info: http://my.malloc.us/silverspring/2007/12/19/380-and-pandora/)
	u32 k1 = pspSdkSetK1(0);
	int res;
	u8 param[0x60];
	if (addr > 0x7F)
		return(0x80000102);
	param[0x0C] = 0x73; // write battery eeprom command
	param[0x0D] = 5;	// tx packet length
	param[0x0E] = addr;// tx data
	param[0x0F] = data;
	param[0x10] = data>>8;
	res = sceSysconCmdExec(param, 0);
	if (res < 0)
		return(res);
	pspSdkSetK1(k1);
	return 0;
}
u32 getDevkitVersion(){
	u32 k1 = pspSdkSetK1(0);
	u32 ver = sceKernelDevkitVersion();
	pspSdkSetK1(k1);
	return ver;
}
int getBatSerial(){
	return (read_eeprom(0x09) | (read_eeprom(0x07)&0xFFFF)<<16);
}
int setBatSerial(int serial){
	if (!write_eeprom(0x07, (serial>>16)))
		write_eeprom(0x09, (serial&0xFFFF)); // lower 16bit
	return getBatSerial(serial);
}
u32 getTachyonVersion(u32 in){
	u32 k1 = pspSdkSetK1(0);
	in = sceSysregGetTachyonVersion();
	pspSdkSetK1(k1);
	return in;
}
u32 getBaryonVersion(u32 in){
	u32 k1 = pspSdkSetK1(0);
	sceSysconGetBaryonVersion(&in);
	pspSdkSetK1(k1);
	return in;
}
u32 getPommelVersion(u32 in){
	u32 k1 = pspSdkSetK1(0);
	sceSysconGetPommelVersion(&in);
	pspSdkSetK1(k1);
	return in;
}
u32 getShippedFW(char* shippedfw){
	char buffer[512];
	memset(buffer, 0, 512);

	u32 k1 = pspSdkSetK1(0);
	memset(buffer, 0, 512);
	sceIdStorageReadLeaf(0x51, buffer);
	pspSdkSetK1(k1);
	u32 fw = 0x00000000;
	fw|=(buffer[0]-0x30)<<24;
	fw|=(buffer[2]-0x30)<<16;
	fw|=(buffer[3]-0x30)<<8;
	return fw;
}
int getKernelInitApitype(){
	return kuKernelInitApitype();
}
int getModel(){
	return sceKernelGetModel();
}
int Ksample_addModule(u32 serial){
	return 5;
}
int getSE(){
	return sctrlHENIsSE();
}
int getHEN(){
	return sctrlHENGetVersion();
}
int getDevhook(){
	return sctrlHENIsDevhook();
}
int getVersion(){
	return sctrlHENGetVersion();
}
int getMBR(){
	int fd = sceIoOpen("msstor:", PSP_O_RDONLY, 0777); // open the input
	char* mbr = malloc(512);
	sceIoRead(fd, mbr, 512);// read the mbr
	sceIoClose(fd);
	fd = sceIoOpen("out.mbr", PSP_O_WRONLY|PSP_O_CREAT, 0777);
	sceIoWrite(fd, mbr, 512);// write the mbr
	sceIoClose(fd);
	free(mbr);
	return 0;
}
int setMBR(){
	int fd = sceIoOpen("in.mbr", PSP_O_RDONLY, 0777); // open the input
	if(fd<1)return -1;
	char* mbr = malloc(512);
	sceIoRead(fd, mbr, 512);// read the mbr
	sceIoClose(fd);
	fd = sceIoOpen("msstor:", PSP_O_WRONLY, 0777);
	sceIoWrite(fd, mbr, 512);// write the mbr
	sceIoClose(fd);
	free(mbr);
	return 0;
}
int setIPL(){//thestarman.pcministry.com/asm/mbr/PartTables.htm
//file part
	SceUID fd = sceIoOpen("in.ipl", PSP_O_RDONLY, 0777);
	if(fd<1)return -1;
	int size = sceIoLseek(fd,0,SEEK_END);
	char* buffer = malloc(size);
	sceIoLseek(fd,0,SEEK_SET);
	sceIoRead(fd,buffer,size);
	sceIoClose(fd);
	if(size!=(size/512)*512){size = (size + 512) & 0xFFFFFE00;}//not a multiple of 512
	if(size<4096)size=4096;
//mbr part
	char* mbr = malloc(512);
	fd = sceIoOpen("msstor:", PSP_O_RDWR, 0777); // open the input
	sceIoRead(fd, mbr, 512);// read the mbr
	u32 part = (mbr[454]|mbr[455]<<8|mbr[456]<<16|mbr[457]<<24);//partion starting offset
	free(mbr);
	if(((part<< 9)-0x2000) < size)return -5;//delta between IPL and partition if not enought : writing will cause a file corruption
//write ipl
	sceIoLseek(fd, 0x2000, 0); // go to the ipl location (mbr@1C0)
	sceIoWrite(fd, buffer, size); // write the ipl
	sceIoClose(fd);
	free(buffer);
	return 0;
}
int getIPL(){
//get size
	char* mbr = malloc(512);
	int fd = sceIoOpen("msstor:", PSP_O_RDONLY, 0777);
	sceIoRead(fd, mbr, 512);// read the mbr
	u32 part = (mbr[454]|mbr[455]<<8|mbr[456]<<16|mbr[457]<<24);//partion starting offset
	free(mbr);
//dump
	char* buffer = malloc((part<< 9)-0x2000);
	sceIoLseek(fd, 0x2000, 0); // go to the ipl location (mbr@1C0)
	sceIoRead(fd, mbr, (part<< 9)-0x2000);// read the IPL
	sceIoClose(fd);
//write
	fd = sceIoOpen("out.ipl", PSP_O_WRONLY|PSP_O_CREAT|PSP_O_NBLOCK, 0777);
	sceIoWrite(fd,buffer,((part<< 9)-0x2000));
	sceIoClose(fd);
	free(buffer);
	return ((part<< 9)-0x2000);
}
int module_start(SceSize args, void *argp){
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
