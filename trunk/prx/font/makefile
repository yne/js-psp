TARGET = font
OBJS = font.o sceLibFont_HV.o

CFLAGS   = -G0 -Wall -O2
ASFLAGS  = $(CFLAGS)
LDFLAGS  = -mno-crt0 -nostartfiles

$(shell psp-build-exports -s libFont.exp)

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1
LIBS = -lpspgu
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all :
	rm *.o $(TARGET).elf