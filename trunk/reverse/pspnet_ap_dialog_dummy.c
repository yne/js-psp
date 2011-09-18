#include <pspsdk.h>
#include "pspnet_ap_dialog_dummy.h"

/*
 * Imports from library: sceUtility_netparam_internal
 */
extern int sceUtility_netparam_internal_072DEBF2 (int arg1);
extern void sceUtility_netparam_internal_9CE50172 (int arg1);
extern int sceUtilitySetNetParam (int arg1, int arg2);

/*
 * Imports from library: sceNetApctl
 */
extern int sceNetApctlGetState (int arg1);
extern int sceNetApctlConnect (int arg1);

/*
 * Imports from library: sceNetApctl_lib
 */
extern int sceNetApctlAddInternalHandler (int arg1, int arg2);
extern void sceNetApctlDelInternalHandler (int arg1);

/*
 * Imports from library: sceNet_lib
 */
extern void sceNetStrncpy (int arg1, int arg2, int arg3);

/*
 * Imports from library: Kernel_Library
 */
extern void sceKernelMemcpy (int arg1, int arg2, int arg3);

void sceNetApDialogDummyConnect (int param){//connect(struct param) sizeof(param)=0x21
  if (!param)return 0x80000103;
	_ErrorCode = 0;
	_CBState = 0;
	state = sceNetApctlGetState (var2);
	if(state < 0)return state;
	if(state == 4)_CBState |= 2;
	if(state)return 0x80000021;
	ret = _connect(param);
	if(ret<0)return ret;
	if (sceNetApctlConnect (0) >= 0)
		_State = 1;
  return;
}
void sceNetApDialogDummyInit(){//register handler
  var1 = _Inited;
  if (_Inited>0)return 0x80000020;
	int ret = sceNetApctlAddInternalHandler (CBhandler, 0);
	if (ret < 0){
		if (_Handler>=0)
			sceNetApctlDelInternalHandler (_Handler);
		_Handler = -1;
		return ret;
	}else{
		var2 = 0;
		_Handler = ret;
		_Inited = 1;
		_State = 0;
	}
}
void sceNetApDialogDummyTerm (){//remove handler
  if (!_Inited)return;
  if (_Handler >=0)
    sceNetApctlDelInternalHandler(_Handler);
  _Inited = 0;
  _Handler = -1;
  return;
}
void sceNetApDialogDummyGetState (int* ret){//get state
  if (!ret)return 0x80000103;
	var3 = _CBState;
	if ((var3 & 2) == 0){
		if (!((var3 & 4) == 0)){
			_CBState = ((var3 & 0xFFFFFFFB) | (0 & 1));
			var4 = 3;
		label7:
			_State = var4;
		}
	}else{
		var4 = 2;
		_CBState = ((var3 & 0xFFFFFFFD) | (0 & 1));
		goto label7;
	}
	ret[0] = _State;
	ret[1] = _ErrorCode;
  return 0;
}
void CBhandler (int prev, int new, int event, int error){
  if (event == 6) _ErrorCode = error;
  if (!(((prev ^ 1) < 1) & (new < 1))){
    if (new == 4) _CBState |= 2;
    else if (new==0) _CBState |= 4;
  }else _CBState |= 1;
}
int _connect (int arg1){//arg for setNetParam (finish him !)
  sceUtility_netparam_internal_9CE50172 (0);
  if((ret=sceUtility_netparam_internal_072DEBF2(0)) < 0)return ret;
  label126:return

    sceKernelMemcpy (sp, arg1, 0x00000021);
    ((char *) sp)[32] = 0;
    if ((sceUtilitySetNetParam(1,sp))<0)return;

		var13 = ((int *) arg1)[9];
      if (var13 >= 5)
      {
        ((int *) sp)[0] = 0;

      label38:
        var15 = sp;
        if((ret=sceUtilitySetNetParam (2, var15)) < 0)return ret;
        if (((int *) arg1)[14] == 1){
          sceNetStrncpy (sp, (arg1 + 0x0000003C), 16);
          if ((ret=sceUtilitySetNetParam (5, sp)) < 0)return ret;
          sceNetStrncpy (sp, (arg1 + 0x0000004C), 16);
          if ((ret=sceUtilitySetNetParam (6, sp)) < 0)return ret;
          sceNetStrncpy (sp, (arg1 + 0x0000005C), 16);
        label67:
          if ((ret=sceUtilitySetNetParam (0x0000000C, sp)) < 0)return ret;
        label72:
          (ret=sceUtilitySetNetParam (4, sp));
          if ((ret=sceUtilitySetNetParam (4, sp)) < 0)return ret;
					switch(((int *) arg1)[79]){
						case 0 : ((int *) sp)[0] = 0;break;
						case 1 : ((int *) sp)[0] = 1;break;
						default: ((int *) sp)[0] = 0;break;
					}
						if ((ret=sceUtilitySetNetParam (0x00000008, sp)) < 0)return ret;
						sceNetStrncpy (sp, (arg1 + 0x00000140), 0x00000010);
						if ((ret = sceUtilitySetNetParam (0x00000009, sp);) < 0)return ret;
						sceNetStrncpy (sp, (arg1 + 0x00000150), 0x00000010);
						(ret = sceUtilitySetNetParam (0x0000000A, sp));
						if ((ret = sceUtilitySetNetParam (0x0000000A, sp)) < 0))
						{
							var38 = ((int *) arg1)[88];
							if (var38 == 0)
							{
								((int *) sp)[0] = 0;

							label106:
								var39 = sp;
								ret = sceUtilitySetNetParam (0x0000000D, var39);
								ra = ((int *) sp)[34];
								if (!(ret < 0))
								{
									var42 = ((int *) arg1)[122];
									if (var42 == 0)
									{
										((int *) sp)[0] = 0;

									label124:
										var43 = sp;
										ret = sceUtilitySetNetParam (0x00000012, var43);
										goto label126;
									}
									else
									{
										if (var42 == 1)
										{
											var48 = sp;
											sceNetStrncpy (var48, (arg1 + 0x000001EC), 0x00000080);
											var51 = sp;
											ret = sceUtilitySetNetParam (0x00000013, var51);
											var54 = sp;
											if (ret < 0)
												goto label126;
											sceNetStrncpy (var54, (arg1 + 0x0000026C), 0x00000080);
											var57 = sp;
											ret = sceUtilitySetNetParam (0x00000014, var57);
											ra = ((int *) sp)[34];
											if (!(ret < 0))
											{
												((int *) sp)[0] = var42;
												goto label124;
											}
										}
										else
										{
											((int *) sp)[0] = 0;
											goto label124;
										}
									}
								}
							}
							else
							{
								if (var38 == 1)
								{
									var60 = sp;
									sceNetStrncpy (var60, (arg1 + 0x00000164), 0x00000080);
									var63 = sp;
									ret = sceUtilitySetNetParam (0x0000000E, var63);
									if (ret < 0)
										goto label126;
									var66 = ((unsigned short *) arg1)[242];
									var67 = sp;
									((int *) sp)[0] = var66;
									ret = sceUtilitySetNetParam (0x0000000F, var67);
									ra = ((int *) sp)[34];
									if (!(ret < 0))
									{
										((int *) sp)[0] = var38;
										goto label106;
									}
								}
								else
								{
									((int *) sp)[0] = 0;
									goto label106;
								}
							}
						}
					}
        }
        else
        {
          if (var18 == 0)
          {
            ((int *) sp)[0] = 0;
            goto label72;
          }
          else
          {
            if (var18 == 2)
            {
              sceNetStrncpy (sp, (arg1 + 0x0000003C), 0x00000080);
              if ((ret = sceUtilitySetNetParam (0x0000000B, sp)) < 0)return ret;
              sceNetStrncpy (sp, (arg1 + 0x000000BC), 0x00000080);
              goto label67;
            }
            else
            {
              ((int *) sp)[0] = 0;
              goto label72;
            }
          }
        }
      }
      else
      {
        var14 = ((int *) ((var13 << 2) + 0x00000804))[0];
        switch () {
        case 0:
          ((int *) sp)[0] = 0;
          goto label38;
        case 1:
          var97 = sp;
          sceKernelMemcpy (var97, (arg1 + 0x00000028), 0x0000000D);
          var100 = sp;
          ret = sceUtilitySetNetParam (3, var100);
          ra = ((int *) sp)[34];
          if (!(ret < 0))
          {
            var103 = 1;

          label36:
            ((int *) sp)[0] = var103;
            goto label38;
          }
        case 2:
          var104 = sp;
          sceKernelMemcpy (var104, (arg1 + 0x00000028), 0x0000000D);
          var107 = sp;
          ret = sceUtilitySetNetParam (3, var107);
          ra = ((int *) sp)[34];
          if (!(ret < 0))
          {
            var103 = 2;
            goto label36;
          }
        case 3:
        case 4:
          var110 = ((int *) arg1)[187];
          var111 = sp;
          ((int *) sp)[0] = var110;
          if (sceUtilitySetNetParam (0x00000015, var111) < 0)return;
          sceKernelMemcpy (sp, (arg1 + 0x000002F0), 0x00000040);
          ret = sceUtilitySetNetParam (0x00000016, sp);
          ra = ((int *) sp)[34];
          if (!(ret < 0))
          {
            ((int *) sp)[0] = var13;
            goto label38;
          }
        }
      }
    }
  }
  var46 = ((int *) sp)[33];
  var47 = ((int *) sp)[32];
  sp = sp + 0x00000090;
  return ret;
}

