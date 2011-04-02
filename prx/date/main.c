#include <pspkernel.h>
#include <psprtc.h>
#include <psputility.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../main/shared.h"

PSP_MODULE_INFO("Date",PSP_MODULE_USER,1,1);
PSP_NO_CREATE_MAIN_THREAD();

const char* tick_str="_tk";
//const char* timeZone_str="_tz";
int timeZone=0;//in minutes

int get(u64 tick,int elem,int local){//1=year ... 7:ms
	pspTime t;
	if(local)sceRtcTickAddMinutes(&tick,&tick,timeZone);
	sceRtcSetTick(&t,&tick);
	switch(elem){
		case 1 :return t.year;
		case 2 :return t.month;
		case 3 :return t.day;
		case 4 :return sceRtcGetDayOfWeek(t.year,t.month,t.day);
		case 5 :return t.hour;
		case 6 :return t.minutes;
		case 7 :return t.seconds;
		case 8 :return t.microseconds/1000;
		default:return 0;
	}
	return 0;
}
u64 set(u64 tick,int elem,int value,int local){//1=year ... 7:ms
	pspTime t;
	if(local)sceRtcTickAddMinutes(&tick,&tick,timeZone);//localize tick
	sceRtcSetTick(&t,&tick);
	switch(elem){
		case 1 :t.year=value;break;
		case 2 :t.month=value;break;
		case 3 :t.day=value;break;
		case 5 :t.hour=value;break;
		case 6 :t.minutes=value;break;
		case 7 :t.seconds=value;break;
		case 8 :t.microseconds=value*1000;break;
		default:return 0;
	}
	sceRtcGetTick(&t,&tick);
	if(local)tick-= timeZone*60*1000*1000;//go back to UTC
	return tick;
}
JS_METH(date_getTime){
	time_t time;
	pspTime date;
	double tmp = J2D(js_getProperty(J2O(ARGV[-1]),tick_str));
	u64 tick = tmp;
	sceRtcSetTick(&date,&tick);
	sceRtcGetTime_t(&date,&time);
	tmp=time;
	*(vp) = D2J(time*1000.0);
	return JS_TRUE;
}
JS_METH(date_getYear){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,1)%100);
	return JS_TRUE;
}
JS_METH(date_getFullYear){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,1));
	return JS_TRUE;
}
JS_METH(date_getMonth){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),2,1));
	return JS_TRUE;
}
JS_METH(date_getDate){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),3,1));
	return JS_TRUE;
}
JS_METH(date_getDay){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),4,1));
	return JS_TRUE;
}
JS_METH(date_getHours){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),5,1));
	return JS_TRUE;
}
JS_METH(date_getMinutes){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),6,1));
	return JS_TRUE;
}
JS_METH(date_getUTCFullYear){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,0));
	return JS_TRUE;
}
JS_METH(date_getUTCMonth){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),2,0));
	return JS_TRUE;
}
JS_METH(date_getUTCDay){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),4,0));
	return JS_TRUE;
}
JS_METH(date_getUTCDate){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),3,0));
	return JS_TRUE;
}
JS_METH(date_getUTCHours){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),5,0));
	return JS_TRUE;
}
JS_METH(date_getUTCMinutes){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),6,0));
	return JS_TRUE;
}
JS_METH(date_getUTCSeconds){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),7,0));
	return JS_TRUE;
}
JS_METH(date_getUTCMilliseconds){
	*(vp) = I2J(get(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),8,0)%100);
	return JS_TRUE;
}
JS_METH(date_getTimezoneOffset){
	*(vp) = I2J(timeZone);
	return JS_TRUE;
}
JS_METH(date_setYear){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,(J2I(ARGV[0])%1000)+2000,0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setFullYear){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,J2I(ARGV[0]),1)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setMonth){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),2,J2I(ARGV[0]),1)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setDate){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),3,J2I(ARGV[0]),1)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setHours){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),5,J2I(ARGV[0]),1)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setMinutes){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),6,J2I(ARGV[0]),1)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCFullYear){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),1,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCMonth){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),2,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCDate){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),3,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCHours){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),5,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCMinutes){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),6,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCSeconds){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),7,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setUTCMilliseconds){
	js_setProperty(J2O(THIS),tick_str,D2J(set(J2D(js_getProperty(J2O(ARGV[-1]),tick_str)),8,J2I(ARGV[0]),0)));
	*(vp) = THIS;
	return JS_TRUE;
}
JS_METH(date_setTime){
	pspTime date;
	u64 tick=0;
	double time = J2D(ARGV[0])/1000.0f;
	sceRtcSetTime_t(&date,time);//set date from arg
	sceRtcGetTick(&date,&tick);//set a tick from date
	js_setProperty(J2O(THIS),tick_str,D2J(tick));//update tick
	*(vp) = THIS;
	return JS_TRUE;
}
char* day[]={"Sun","Mon","Tue","Wen","Thu","Fri","Sat"};
char* month[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
JS_METH(date_toString){//Sun Mar 27 2011 18:12:29 GMT+0200 (firefox)
	*(vp) = ARGV[-1];
	return JS_TRUE;
}
static JSFunctionSpec date_methods[] = {
	JS_FN("getTimezoneOffset",   date_getTimezoneOffset,  0,0,0),
	JS_FN("getTime",             date_getTime,            0,0,0),
	JS_FN("getYear",             date_getYear,            0,0,0),
	JS_FN("getFullYear",         date_getFullYear,        0,0,0),
	JS_FN("getUTCFullYear",      date_getUTCFullYear,     0,0,0),
	JS_FN("getMonth",            date_getMonth,           0,0,0),
	JS_FN("getUTCMonth",         date_getUTCMonth,        0,0,0),
	JS_FN("getDate",             date_getDate,            0,0,0),
	JS_FN("getUTCDate",          date_getUTCDate,         0,0,0),
	JS_FN("getDay",              date_getDay,             0,0,0),
	JS_FN("getUTCDay",           date_getUTCDay,          0,0,0),
	JS_FN("getHours",            date_getHours,           0,0,0),
	JS_FN("getUTCHours",         date_getUTCHours,        0,0,0),
	JS_FN("getMinutes",          date_getMinutes,         0,0,0),
	JS_FN("getUTCMinutes",       date_getUTCMinutes,      0,0,0),
	JS_FN("getSeconds",          date_getUTCSeconds,      0,0,0),
	JS_FN("getUTCSeconds",       date_getUTCSeconds,      0,0,0),
	JS_FN("getMilliseconds",     date_getUTCMilliseconds, 0,0,0),
	JS_FN("getUTCMilliseconds",  date_getUTCMilliseconds, 0,0,0),
	JS_FN("setTime",             date_setTime,            1,1,0),
	JS_FN("setYear",             date_setYear,            1,1,0),
	JS_FN("setFullYear",         date_setFullYear,        1,3,0),
	JS_FN("setUTCFullYear",      date_setUTCFullYear,     1,3,0),
	JS_FN("setMonth",            date_setMonth,           1,2,0),
	JS_FN("setUTCMonth",         date_setUTCMonth,        1,2,0),
	JS_FN("setDate",             date_setDate,            1,1,0),
	JS_FN("setUTCDate",          date_setUTCDate,         1,1,0),
	JS_FN("setHours",            date_setHours,           1,4,0),
	JS_FN("setUTCHours",         date_setUTCHours,        1,4,0),
	JS_FN("setMinutes",          date_setMinutes,         1,3,0),
	JS_FN("setUTCMinutes",       date_setUTCMinutes,      1,3,0),
	JS_FN("setSeconds",          date_setUTCSeconds,      1,2,0),
	JS_FN("setUTCSeconds",       date_setUTCSeconds,      1,2,0),
	JS_FN("setMilliseconds",     date_setUTCMilliseconds, 1,1,0),
	JS_FN("setUTCMilliseconds",  date_setUTCMilliseconds, 1,1,0),
/*
	JS_FN("toUTCString",         date_toGMTString,        0,0,0),
	JS_FN("toLocaleString",      date_toLocaleString,     0,0,0),
	JS_FN("toLocaleDateString",  date_toLocaleDateString, 0,0,0),
	JS_FN("toLocaleTimeString",  date_toLocaleTimeString, 0,0,0),
	JS_FN("toLocaleFormat",      date_toLocaleFormat,     0,0,0),
	JS_FN("toDateString",        date_toDateString,       0,0,0),
	JS_FN("toTimeString",        date_toTimeString,       0,0,0),
*/
	JS_FN("toString",            date_toString,           0,0,0),
	JS_FN("valueOf",             date_getTime,            0,0,0),
	JS_FS_END
};
JS_FUN(Date){
	pspTime date;
	u64 tick=0;
	if(!argc){
		sceRtcGetCurrentTick(&tick);
	}
	if(argc==1){
		switch(js_typeOfValue(argv[0])){
			case JSTYPE_STRING :
				sceRtcParseDateTime(&tick,J2S(argv[0]));//-1 on failed parsing (must be RFC3339 compliant)
			break;
			case JSTYPE_NUMBER :
				sceRtcSetTime_t(&date,J2I(argv[0]));
				sceRtcGetTick(&date,&tick);
			break;
			default:;
		}
	}
//	u64 converted;
//	sceRtcConvertUtcToLocalTime(&converted,&tick);
	js_setProperty(obj,tick_str,D2J(tick));
//	js_setProperty(obj,timeZone_str,I2J(timeZone));
	return JS_TRUE;
}
int module_start(SceSize args, void *argp){
	pspTime ori,me;
	sceRtcGetCurrentClock(&ori,0);
	sceRtcGetCurrentClockLocalTime(&me);
	timeZone = 60*(me.hour-ori.hour)+(me.minutes-ori.minutes);//daylight included
	js_addClass(NULL,NULL,Date,0,NULL,date_methods,NULL,NULL,"Date",
		JSCLASS_NEW_RESOLVE,0,0,0,0,0,0,0,0,JSCLASS_NO_OPTIONAL_MEMBERS,NULL);
	return 0;
}
int module_stop(SceSize args, void *argp){
	return 0;
}
