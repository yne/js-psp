TARGET = ../sceNet
OBJS = main.o ../../main/JSE.o

CFLAGS   = -G0 -Wall -O2
ASFLAGS  = $(CFLAGS)
LDFLAGS  = -mno-crt0 -nostartfiles

PRX_EXPORTS = ../plugin.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS = -lpspnet -lpspnet_adhocmatching -lpspnet_adhocctl -lpspnet_adhoc -lpspnet_resolver -lpspwlan

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
	psp-packer.exe $(TARGET).prx
	rm *.o $(TARGET).elf