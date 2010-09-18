/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/*
 * JS math package.
 */
#include "jsstddef.h"
#include "jslibmath.h"
#include <stdlib.h>
#include "jstypes.h"
#include "jslong.h"
#include "prmjtime.h"
#include "jsapi.h"
#include "jsatom.h"
#include "jscntxt.h"
#include "jsconfig.h"
#include "jslock.h"
#include "jsmath.h"
#include "jsnum.h"
#include "jsobj.h"

#ifndef M_E
#define M_E             2.7182818284590452354
#endif
#ifndef M_LOG2E
#define M_LOG2E         1.4426950408889634074
#endif
#ifndef M_LOG10E
#define M_LOG10E        0.43429448190325182765
#endif
#ifndef M_LN2
#define M_LN2           0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10          2.30258509299404568402
#endif
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif
#ifndef M_SQRT2
#define M_SQRT2         1.41421356237309504880
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2       0.70710678118654752440
#endif

static JSConstDoubleSpec math_constants[] = {
    {M_E,       "E",            0, {0,0,0}},
    {M_LOG2E,   "LOG2E",        0, {0,0,0}},
    {M_LOG10E,  "LOG10E",       0, {0,0,0}},
    {M_LN2,     "LN2",          0, {0,0,0}},
    {M_LN10,    "LN10",         0, {0,0,0}},
    {M_PI,      "PI",           0, {0,0,0}},
    {M_SQRT2,   "SQRT2",        0, {0,0,0}},
    {M_SQRT1_2, "SQRT1_2",      0, {0,0,0}},
    {0,0,0,{0,0,0}}
};

JSClass js_MathClass = {
    js_Math_str,
    JSCLASS_HAS_CACHED_PROTO(JSProto_Math),
    JS_PropertyStub,  JS_PropertyStub,  JS_PropertyStub,  JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub,   JS_ConvertStub,   JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSBool
math_abs(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vabs.s			s000, s000\n"			// s000 = abs(s000)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		#else
    z = fd_fabs(x);
		#endif
    return js_NewNumberInRootedValue(cx, z, vp);
}

static JSBool
math_acos(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
#if !JS_USE_FDLIBM_MATH && defined(SOLARIS) && defined(__GNUC__)
    if (x < -1 || 1 < x) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
#endif
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_SQRT1_2\n"	// s001 = VFPU_SQRT1_2 = 1 / sqrt(2)
			"vcst.s			s002, VFPU_PI_2\n"		// s002 = VFPU_PI_2    = PI / 2
			"vcmp.s			LT, s000[|x|], s001\n"	// CC[0] = |s000| < s001
			"vmul.s			s003, s000, s000\n"		// s003 = s000 * s000
			"vsgn.s			s001, s000\n"			// s001 = sign(s000)
			"bvtl			0, 0f\n"				// if (CC[0]!=0) goto 0f
			"vasin.s		s000, s000\n"			// s000 = asin(s000)
			"vocp.s			s003, s003\n"			// s003 = 1.0 - s003
			"vsqrt.s		s003, s003\n"			// s003 = sqrt(s003)
			"vasin.s		s003, s003\n"			// s003 = asin(s003)
			"vocp.s			s000, s003\n"			// s000 = 1.0 - s003
			"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001
		"0:\n"
			"vocp.s			s000, s000\n"			// s000 = 1.0 - s000
			"vmul.s			s000, s000, s002\n"		// s000 = s000 * s002
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		#else
    z = fd_acos(x);
		#endif
    return js_NewNumberInRootedValue(cx, z, vp);
}

static JSBool
math_asin(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
#if !JS_USE_FDLIBM_MATH && defined(SOLARIS) && defined(__GNUC__)
    if (x < -1 || 1 < x) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
#endif
    #ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_SQRT1_2\n"	// s001 = VFPU_SQRT1_2 = 1 / sqrt(2)
			"vcst.s			s002, VFPU_PI_2\n"		// s002 = VFPU_PI_2    = PI / 2
			"vcmp.s			LT, s000[|x|], s001\n"	// CC[0] = |s000| < s001
			"vmul.s			s003, s000, s000\n"		// s003 = s000 * s000
			"vsgn.s			s001, s000\n"			// s001 = sign(s000)
			"bvtl			0, 0f\n"				// if (CC[0]!=0) goto 0f
			"vasin.s		s000, s000\n"			// s000 = asin(s000)
			"vocp.s			s003, s003\n"			// s003 = 1.0 - s003
			"vsqrt.s		s003, s003\n"			// s003 = sqrt(s003)
			"vmul.s			s002, s002, s001\n"		// s002 = s002 * s001
			"vasin.s		s003, s003\n"			// s003 = asin(s003)
			"vocp.s			s000, s003\n"			// s000 = 1.0 - s003
		"0:\n"
			"vmul.s			s000, s000, s002\n"		// s000 = s000 * s002
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
    return JS_NewNumberValue(cx, z, vp);
		#else
		z = fd_asin(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}
#ifdef USE_VFPU
float vfpu_atanf(float x) {
	float result;
	__asm__ (
		"mtv      %1, S000\n"
		"vmul.s   S001, S000, S000\n"
		"vadd.s   S001, S001, S001[1]\n"
		"vrsq.s   S001, S001\n"
		"vmul.s   S000, S000, S001\n"
		"vasin.s  S000, S000\n"
		"vcst.s   S001, VFPU_PI_2\n"
		"vmul.s   S000, S000, S001\n"
		"mfv      %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;//asinf(x/sqrt(x*x+1))
}

float fabsf(float x) {
	float r;
	__asm__ ( "abs.s %0, %1" : "=f"(r) :"f"(x):"memory");
	return r;
}
#endif
static JSBool
math_atan(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float s=x;
		z=vfpu_atanf(s);
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_atan(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_atan2(JSContext *cx, uintN argc, jsval *vp)
{//need VFPU equivalent
    jsdouble x, y, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
    y = js_ValueToNumber(cx, &vp[3]);
    if (JSVAL_IS_NULL(vp[3]))
        return JS_FALSE;
#if !JS_USE_FDLIBM_MATH && defined(_MSC_VER)
    /*
     * MSVC's atan2 does not yield the result demanded by ECMA when both x
     * and y are infinite.
     * - The result is a multiple of pi/4.
     * - The sign of x determines the sign of the result.
     * - The sign of y determines the multiplicator, 1 or 3.
     */
    if (JSDOUBLE_IS_INFINITE(x) && JSDOUBLE_IS_INFINITE(y)) {
        z = fd_copysign(M_PI / 4, x);
        if (y < 0)
            z *= 3;
        return js_NewDoubleInRootedValue(cx, z, vp);
    }
#endif

#if !JS_USE_FDLIBM_MATH && defined(SOLARIS) && defined(__GNUC__)
    if (x == 0) {
        if (JSDOUBLE_IS_NEGZERO(y)) {
            z = fd_copysign(M_PI, x);
            return js_NewDoubleInRootedValue(cx, z, vp);
        }
        if (y == 0) {
            z = x;
            return js_NewDoubleInRootedValue(cx, z, vp);
        }
    }
#endif
		#ifdef USE_VFPU
		#define PI   3.14159265358979f
		#define PI_2 1.57079632679489f
		
		float d,s=x,t=y;
		if (fabsf(x) >= fabsf(t)) {
			d = vfpu_atanf(t/s);
			if   (s < 0.0f) d += (t>=0.0f ? PI : -PI);
		} else {
			d = -vfpu_atanf(s/t);
			d += (t < 0.0f ? -PI_2 : PI_2);
		}
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_atan2(x, y);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_ceil(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vf2iu.s		s000, s000, 0\n"		// s000 = (int)ceil(s000)
			"vi2f.s			s000, s000, 0\n"		// s000 = (float)s000
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_ceil(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_cos(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_2_PI\n"		// s001 = VFPU_2_PI = 2 / PI
			"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001
			"vcos.s			s000, s000\n"			// s000 = cos(s000)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_cos(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_exp(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
#ifdef _WIN32
    if (!JSDOUBLE_IS_NaN(x)) {
        if (x == *cx->runtime->jsPositiveInfinity) {
            *vp = DOUBLE_TO_JSVAL(cx->runtime->jsPositiveInfinity);
            return JS_TRUE;
        }
        if (x == *cx->runtime->jsNegativeInfinity) {
            *vp = JSVAL_ZERO;
            return JS_TRUE;
        }
    }
#endif
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_LOG2E\n"		// s001 = VFPU_LOG2E
			"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001 = s * log2(e)
			"vexp2.s		s000, s000\n"			// s000 = pow(2.0f, s000)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_exp(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_floor(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vf2id.s		s000, s000, 0\n"		// s000 = (int)floor(s000)
			"vi2f.s			s000, s000, 0\n"		// s000 = (float)s000
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_floor(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_log(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
#if !JS_USE_FDLIBM_MATH && defined(SOLARIS) && defined(__GNUC__)
    if (x < 0) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
#endif
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vlog2.s		s000, s000\n"			// s000 = log2(s000)
			"vcst.s			s001, VFPU_LOG2E\n"		// s001 = VFPU_LOG2E
			"vdiv.s			s000, s000, s001\n"		// s000 = s000 / s001 = log2(s000) / log2(e)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_log(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_max(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z = *cx->runtime->jsNegativeInfinity;
    jsval *argv;
    uintN i;

    if (argc == 0) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNegativeInfinity);
        return JS_TRUE;
    }
    argv = vp + 2;
    for (i = 0; i < argc; i++) {
        x = js_ValueToNumber(cx, &argv[i]);
        if (JSVAL_IS_NULL(argv[i]))
            return JS_FALSE;
        if (JSDOUBLE_IS_NaN(x)) {
            *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
            return JS_TRUE;
        }
        if (x == 0 && x == z && fd_copysign(1.0, z) == -1)
            z = x;
        else
            z = (x > z) ? x : z;
    }
    return js_NewNumberInRootedValue(cx, z, vp);
}

static JSBool
math_min(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z = *cx->runtime->jsPositiveInfinity;
    jsval *argv;
    uintN i;

    if (argc == 0) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsPositiveInfinity);
        return JS_TRUE;
    }
    argv = vp + 2;
    for (i = 0; i < argc; i++) {
        x = js_ValueToNumber(cx, &argv[i]);
        if (JSVAL_IS_NULL(argv[i]))
            return JS_FALSE;
        if (JSDOUBLE_IS_NaN(x)) {
            *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
            return JS_TRUE;
        }
        if (x == 0 && x == z && fd_copysign(1.0,x) == -1)
            z = x;
        else
            z = (x < z) ? x : z;
    }
    return js_NewNumberInRootedValue(cx, z, vp);
}

static JSBool
math_pow(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, y, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
    y = js_ValueToNumber(cx, &vp[3]);
    if (JSVAL_IS_NULL(vp[3]))
        return JS_FALSE;
#if !JS_USE_FDLIBM_MATH
    /*
     * Because C99 and ECMA specify different behavior for pow(),
     * we need to wrap the libm call to make it ECMA compliant.
     */
    if (!JSDOUBLE_IS_FINITE(y) && (x == 1.0 || x == -1.0)) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
    /* pow(x, +-0) is always 1, even for x = NaN. */
    if (y == 0) {
        *vp = JSVAL_ONE;
        return JS_TRUE;
    }
#endif
		#ifdef USE_VFPU
		float d,s=x,t=y;
	__asm__ (
		"lv.s			s000, %1\n"				// s000 = x
		"lv.s			s001, %2\n"				// s001 = y
		"vlog2.s		s000, s000\n"			// s000 = log2(x)
		"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001 = log2(x) * y
		"vexp2.s		s000, s000\n"			// s000 = pow(2.0f, s000)
		"sv.s			s000, %0\n"				// d    = s000
		: "=m"(d) : "m"(s), "m"(t)
	);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_pow(x, y);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

/*
 * Math.random() support, lifted from java.util.Random.java.
 */
static void
random_setSeed(JSRuntime *rt, int64 seed)
{
    int64 tmp;

    JSLL_I2L(tmp, 1000);
    JSLL_DIV(seed, seed, tmp);
    JSLL_XOR(tmp, seed, rt->rngMultiplier);
    JSLL_AND(rt->rngSeed, tmp, rt->rngMask);
}

static void
random_init(JSRuntime *rt)
{
    int64 tmp, tmp2;

    /* Do at most once. */
    if (rt->rngInitialized)
        return;
    rt->rngInitialized = JS_TRUE;

    /* rt->rngMultiplier = 0x5DEECE66DL */
    JSLL_ISHL(tmp, 0x5, 32);
    JSLL_UI2L(tmp2, 0xDEECE66DL);
    JSLL_OR(rt->rngMultiplier, tmp, tmp2);

    /* rt->rngAddend = 0xBL */
    JSLL_I2L(rt->rngAddend, 0xBL);

    /* rt->rngMask = (1L << 48) - 1 */
    JSLL_I2L(tmp, 1);
    JSLL_SHL(tmp2, tmp, 48);
    JSLL_SUB(rt->rngMask, tmp2, tmp);

    /* rt->rngDscale = (jsdouble)(1L << 53) */
    JSLL_SHL(tmp2, tmp, 53);
    JSLL_L2D(rt->rngDscale, tmp2);

    /* Finally, set the seed from current time. */
    random_setSeed(rt, PRMJ_Now());
}

static uint32
random_next(JSRuntime *rt, int bits)
{
    int64 nextseed, tmp;
    uint32 retval;

    JSLL_MUL(nextseed, rt->rngSeed, rt->rngMultiplier);
    JSLL_ADD(nextseed, nextseed, rt->rngAddend);
    JSLL_AND(nextseed, nextseed, rt->rngMask);
    rt->rngSeed = nextseed;
    JSLL_USHR(tmp, nextseed, 48 - bits);
    JSLL_L2I(retval, tmp);
    return retval;
}

static jsdouble
random_nextDouble(JSRuntime *rt)
{
    int64 tmp, tmp2;
    jsdouble d;

    JSLL_ISHL(tmp, random_next(rt, 26), 27);
    JSLL_UI2L(tmp2, random_next(rt, 27));
    JSLL_ADD(tmp, tmp, tmp2);
    JSLL_L2D(d, tmp);
    return d / rt->rngDscale;
}

static JSBool
math_random(JSContext *cx, uintN argc, jsval *vp)
{
    JSRuntime *rt;
    jsdouble z;

    rt = cx->runtime;
    JS_LOCK_RUNTIME(rt);
    random_init(rt);
    z = random_nextDouble(rt);
    JS_UNLOCK_RUNTIME(rt);
    return js_NewNumberInRootedValue(cx, z, vp);
}

#if defined _WIN32 && !defined WINCE && _MSC_VER < 1400
/* Try to work around apparent _copysign bustage in VC6 and VC7. */
double
js_copysign(double x, double y)
{
    jsdpun xu, yu;

    xu.d = x;
    yu.d = y;
    xu.s.hi &= ~JSDOUBLE_HI32_SIGNBIT;
    xu.s.hi |= yu.s.hi & JSDOUBLE_HI32_SIGNBIT;
    return xu.d;
}
#endif

static JSBool
math_round(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
 		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vf2iz.s		s000, s000, 0\n"		// s000 = (int)truncf(s000)
			"vi2f.s			s000, s000, 0\n"		// s000 = (float)s000
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_copysign(fd_floor(x + 0.5), x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_sin(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_2_PI\n"		// s001 = VFPU_2_PI = 2 / PI
			"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001
			"vsin.s			s000, s000\n"			// s000 = sin(s000)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_sin(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_sqrt(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vsqrt.s		s000, s000\n"			// s000 = sqrt(s000)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
    z = fd_sqrt(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

static JSBool
math_tan(JSContext *cx, uintN argc, jsval *vp)
{
    jsdouble x, z;

    x = js_ValueToNumber(cx, &vp[2]);
    if (JSVAL_IS_NULL(vp[2]))
        return JS_FALSE;
 		#ifdef USE_VFPU
		float d,s=x;
		__asm__ (
			"lv.s			s000, %1\n"				// s000 = s
			"vcst.s			s001, VFPU_2_PI\n"		// s001 = VFPU_2_PI = 2 / PI
			"vmul.s			s000, s000, s001\n"		// s000 = s000 * s001
			"vrot.p			c002, s000, [c, s]\n"	// s002 = cos(s) , s003 = sin(s)
			"vdiv.s			s000, s003, s002\n"		// s000 = s003 / s002 = tan(s)
			"sv.s			s000, %0\n"				// d    = s000
			: "=m"(d) : "m"(s)
		);
		z=d;
		return JS_NewNumberValue(cx, z, vp);
		#else
		z = fd_tan(x);
    return js_NewNumberInRootedValue(cx, z, vp);
		#endif
}

#if JS_HAS_TOSOURCE
static JSBool
math_toSource(JSContext *cx, uintN argc, jsval *vp)
{
    *vp = ATOM_KEY(CLASS_ATOM(cx, Math));
    return JS_TRUE;
}
#endif

static JSFunctionSpec math_static_methods[] = {
#if JS_HAS_TOSOURCE
    JS_FN(js_toSource_str,  math_toSource,      0, 0, 0),
#endif
    JS_FN("abs",            math_abs,           1, 1, 0),
    JS_FN("acos",           math_acos,          1, 1, 0),
    JS_FN("asin",           math_asin,          1, 1, 0),
    JS_FN("atan",           math_atan,          1, 1, 0),
    JS_FN("atan2",          math_atan2,         2, 2, 0),
    JS_FN("ceil",           math_ceil,          1, 1, 0),
    JS_FN("cos",            math_cos,           1, 1, 0),
    JS_FN("exp",            math_exp,           1, 1, 0),
    JS_FN("floor",          math_floor,         1, 1, 0),
    JS_FN("log",            math_log,           1, 1, 0),
    JS_FN("max",            math_max,           0, 2, 0),
    JS_FN("min",            math_min,           0, 2, 0),
    JS_FN("pow",            math_pow,           2, 2, 0),
    JS_FN("random",         math_random,        0, 0, 0),
    JS_FN("round",          math_round,         1, 1, 0),
    JS_FN("sin",            math_sin,           1, 1, 0),
    JS_FN("sqrt",           math_sqrt,          1, 1, 0),
    JS_FN("tan",            math_tan,           1, 1, 0),
    JS_FS_END
};

JSObject *
js_InitMathClass(JSContext *cx, JSObject *obj)
{
    JSObject *Math;

    Math = JS_DefineObject(cx, obj, js_Math_str, &js_MathClass, NULL, 0);
    if (!Math)
        return NULL;
    if (!JS_DefineFunctions(cx, Math, math_static_methods))
        return NULL;
    if (!JS_DefineConstDoubles(cx, Math, math_constants))
        return NULL;
    return Math;
}
