TARGET = ../intraFont
OBJS = main.o intraFont.o libccc.o ../gu/sceGu.o ../../main/JSE.o

CFLAGS   = -O2 -G0 -Wall
ASFLAGS  = $(CFLAGS)
LDFLAGS  = -mno-crt0 -nostartfiles

PRX_EXPORTS = ../plugin.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS =

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	psp-packer $(TARGET).prx
	rm $(TARGET).elf *.o
