TARGET = ../Ksample
OBJS = main.o ../../main/JSE.o

CFLAGS = -G0 -Wall -O2
LDFLAGS = -mno-crt0 -nostartfiles
ASFLAGS = $(CFLAGS)

PRX_EXPORTS = Ksample.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS = -lpspkubridge -lpspsystemctrl_kernel

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
#	psp-packer.exe $(TARGET).prx
	rm *.o $(TARGET).elf