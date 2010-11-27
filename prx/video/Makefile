TARGET = ../video
OBJS = main.o ../../main/JSE.o util.o atom.o mp4_read.o mp4_file.o mp4info.o time_math.o mpegbase.o mem64.o cooleyesBridge.o 

CFLAGS   = -G0 -Wall -O2
ASFLAGS  = $(CFLAGS)
LDFLAGS  = -mno-crt0 -nostartfiles

PRX_EXPORTS = ../plugin.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS = -lpspmpeg -lm -lpsprtc

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
	psp-packer.exe $(TARGET).prx
	rm *.o $(TARGET).elf