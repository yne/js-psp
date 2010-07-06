TARGET_LIB = ./libspidermonkey.a
OBJS = \
		jsapi.o \
		jsarena.o \
		jsarray.o \
		jsatom.o \
		jsbool.o \
		jscntxt.o \
		jsdate.o \
		jsdbgapi.o \
		jsdhash.o \
		jsdtoa.o \
		jsemit.o \
		jsexn.o \
		jsfun.o \
		jsgc.o \
		jshash.o \
		jsinterp.o \
		jsinvoke.o \
		jsiter.o \
		jslock.o \
		jslog2.o \
		jslong.o \
		jsmath.o \
		jsnum.o \
		jsobj.o \
		jsopcode.o \
		jsparse.o \
		jsprf.o \
		jsregexp.o \
		jsscan.o \
		jsscope.o \
		jsscript.o \
		jsstr.o \
		jsutil.o \
		jsxdrapi.o \
		jsxml.o \
		prmjtime.o

CFLAGS = -G0 -Wall -O2 -Wno-format
ASFLAGS = $(CFLAGS)

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
