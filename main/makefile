TARGET = ../main
OBJS = main.o functions.o ../prx/user/modU.o ../prx/kernel/modK.o

CFLAGS = -G0 -Wall -O2
ASFLAGS = $(CFLAGS)
#LDFLAGS = -nodefaultlibs -mno-explicit-relocs

PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

USE_USER_LIBC = 1
USE_USER_LIBS = 1

INCDIR = ../

LIBDIR = ../src
LIBS= -lspidermonkey -lm 

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
