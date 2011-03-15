#BUILD PROPERTY HERE
USE_PSPSDK_LIBC = 1
USE_AUTOLOAD = 1
USE_VFPU = 1
USE_PALLOC = 1
DEBUG_MODE = 1
BUILD_PRX = 1

#DO NOT TOUCH THIS PART
ifeq ($(BUILD_PRX),1)
TARGET = libjs
LDFLAGS += -mno-crt0 -nostartfiles
INCDIR += ../main/  ../
OBJS += crt0.o ../main/shared.o ../main/functions.o ../prx/kernel/modK.o
PRX_EXPORTS = ../main/export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})
else
TARGET_LIB = ./libspidermonkey.a
endif
#include malloc in stdlib to avoid lot of undefined warning
ifeq ($(USE_PSPSDK_LIBC),1)
CFLAGS += -DNO_LIBC
LIBS += -lpsprtc
endif

ifeq ($(USE_PALLOC),1)
CFLAGS += -DUSE_PARTITION
endif

ifeq ($(DEBUG_MODE),1)
CFLAGS += -DDEBUG_MODE
endif

ifeq ($(USE_VFPU),1)
CFLAGS += -DUSE_VFPU
OBJS += vfpu.o
endif

ifeq ($(USE_AUTOLOAD),1)
CFLAGS += -DUSE_AUTOLOAD
endif

#COMMON PART

CFLAGS += -G0 -Wall -O2 -DRND_PRODQUOT
ASFLAGS += $(CFLAGS)

OBJS += \
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
		prmjtime.o \
		

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
ifeq ($(BUILD_PRX),1)
	rm -f ../${TARGET}.prx ${TARGET}.elf
	psp-packer ${TARGET}.prx ../libjs
	mv ${TARGET}.prx ..
endif