TARGET = libdeflt
OBJS   = main.o gziphdr.o zlibhdr.o deflate.o adler32.o crc.o ../../main/JSE.o

CFLAGS = -G0 -Wall -O2
ASFLAGS= -c -xassembler-with-cpp
LDFLAGS= -mno-crt0 -nostartfiles

PRX_EXPORTS = ../plugin.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
	psp-packer.exe $(TARGET).prx
	rm *.o $(TARGET).elf