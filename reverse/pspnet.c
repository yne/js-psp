//data
char*GlobalA//0xB150
int sceNet_lib_DA02F383 (char*name, int*result){
	int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  int ret = _sce_pspnet_ifioctl (0, 0xC01469D8, msg, 1);
  GlobalA = NULL;
  if (!ret)
    *result = msg[4];
  return ret;
}
int sceNet_lib_83FE280A (char*name, int unk){
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  return _sce_pspnet_ifioctl (0, 0x801469E4, msg, 1);
}
int sceNet_lib_891723D5 (char*name, int arg2){//set
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg2;
  return _sce_pspnet_ifioctl (0, 0x801469DF, msg, 1);
}
void sceNet_lib_F355C73B (int arg1, int arg2, int arg3);
int sceNet_lib_A55C914F (char*name, int arg){
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg;
  return _sce_pspnet_ifioctl (0, 0xC01469D7, msg, 1);
}
void sceNet_lib_7BA3ED91 (char*name, int arg2, int*arg3, int arg4, int*arg5){
  int msg[8];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg2;
  msg[5] = *arg3;
  msg[6] = arg4;
  if (!_sce_pspnet_ifioctl (0, 0xC02069D4, msg, 1)){
    *arg3 = msg[5];
    *arg5 = msg[7];
  }
}
void sceNet_lib_03164B12 (char*name, int arg2,int*result){
  int msg[6];
  sceNetMemset (msg, 0, 0x18);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg2;
  if (!_sce_pspnet_ifioctl (0, 0xC01869D5, msg, 1))
    *result = msg[5];
}
void sceNet_lib_389728AB (char*name, int arg2,int*result){
  int msg[6];
  sceNetMemset (msg, 0, 0x18);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg2;
  if (!_sce_pspnet_ifioctl (0, 0xC01869D6, msg, 1))
    *result = msg[5];
}
void sceNet_lib_B755FA98 (int arg1, int arg2, int arg3, int arg4, int arg5){
  sceNet_lib_43EE76EC (arg1, arg2, arg3, arg4, arg5, 1);
}
void sceNet_lib_EB38431E (int arg1, int arg2){
  p = GlobalA;
  if (!p)return 0x80410185;
	sceNetMemcpy (arg2, (p+4), 0x5C);
  return 0;
}
void sceNet_lib_AFA11338 (char*name, int arg){
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg;
  return _sce_pspnet_ifioctl (0, 0x801469D2, msg, 1);
}
void sceNet_lib_B20F84F8 (char*name, int arg){
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg;
  return _sce_pspnet_ifioctl (0, 0x401469D3, msg, 1);
}
void sceNet_lib_4F8F3808 (char*name, int arg){
  int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg;
  _sce_pspnet_ifioctl (0, 0x401469DE, msg, 1);
}
void sceNet_lib_0DFF67F9 (char*name, int*arg){//get
	int msg[5];
  sceNetMemset (msg, 0, 0x14);
  sceNetStrncpy (msg, name, 0x10);
  if (!_sce_pspnet_ifioctl (0, 0x401469E0, msg, 1))
    *arg2 = msg[4];
}
void sceNet_lib_0D633F53 (char*name, int arg2, int arg3, int*arg4){
  int msg[7];
  sceNetMemset (msg, 0, 0x1C);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = arg2;
  msg[5] = arg3;
  if (!_sce_pspnet_ifioctl (0, 0xC01C69E1, msg, 1))
    *arg4 = msg[6];
}
void sceNet_lib_AB375964 (char*name,char*target){
	unsigned short msg[24];
  sceNetMemset (msg, 0, 0x30);
  sceNetStrncpy (msg, name, 0x10);
  sceNetMemcpy (msg+10, target, 0x20);
  _sce_pspnet_ifioctl (0, 0x803069E2, msg, 1);
}
void sceNet_lib_8DA79EB0 (char*name,char*target){
	unsigned short msg[24];
  sceNetMemset (msg, 0, 0x30);
  sceNetStrncpy (msg, name, 0x10);
  sceNetMemcpy (msg+10, target, 0x20);
  _sce_pspnet_ifioctl (0, 0x803069E3, msg, 1);
}
void sceNetConfigUpInterface (char*name){
  unsigned short * msg[0x20];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  if (_sce_pspnet_ifioctl (0, 0xC0206911, msg, 1))return;
	msg[8] |= 1;
	_sce_pspnet_ifioctl (0, 0x80206910, msg, 1);
}
void sceNetConfigDownInterface (char*name){
  unsigned short * msg[0x20];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  if (_sce_pspnet_ifioctl (0, 0xC0206911, msg, 1))return;
	msg[8] &= -2;
	_sce_pspnet_ifioctl (0, 0x80206910, msg, 1);
}
int sceNetConfigGetEtherAddr (char*ip,char*ether){
  int*ret=_sce_pspnet_ifunit (ip);
  if (!ret)return 0x80410180;
	sceNetMemcpy (ether,ret[56] + ((u8*)ret[56])[5] + 8, 6);
	return 0;
}
void sceNetGetLocalEtherAddr (char*ether){
  if (sceKernelCheckThreadStack()<0x3F0)return 0x80410005;
	int*ret = _sce_pspnet_ifunit ("wlan");
	if (!ret)return 0x80410180;
	sceNetMemcpy (ether,ret[56] + ((u8*)ret[56])[5] + 8, 6);
  return 0;
}
void sceNetConfigGetIfEvent (char*name, int*get1, int*get2){//get
  int msg[8+2];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = msg+0x20;
  sceNetMemset (msg+0x20, 0, 8);
  if (!_sce_pspnet_ifioctl (0, 0xC020693D, msg, 1)){
    *get1 = msg[8];
    *get2 = msg[9];
  }
}
void sceNetConfigSetIfEventFlag (char*name, int set1, int set2){//set
  int msg[8];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  msg[8] = set1;
  msg[9] = set2;
  msg[4] = &msg[8];
  return _sce_pspnet_ifioctl (0, 0x8020693E, msg, 1);
}
void sceNetConfigGetIfEventFlag (char*name, int*get1, int*get2){
  int msg[5+2];
  sceNetMemset (msg, 0, 0x20);
  sceNetStrncpy (msg, name, 0x10);
  msg[4] = msg + 0x20;
  sceNetMemset (&msg[4], 0, 8);
  if (!_sce_pspnet_ifioctl (0, 0xC020693E, msg, 1)){
    *get1 = msg[8];
    *get2 = msg[9];
  }
}
void sceNet_lib_C1D2A7FB (char*name, int val){
  int msg[5+2];
  sceNetMemset (msg, 0, 0x16);
  sceNetStrncpy (msg, name, 0x10);
  sceNetMemcpy (msg + 0x10, val, 6);
  return _sce_pspnet_ifioctl (0, 0x801669FA, msg, 1);
}
void sceNet_lib_CFA79880 (char*name, int val){
  int msg[5];
  sceNetMemset (msg, 0, 0x16);
  sceNetStrncpy (msg, name, 0x10);
  sceNetMemcpy (msg+0x10, val, 6);
  return _sce_pspnet_ifioctl (0, 0x801669FB, msg, 1);
}
