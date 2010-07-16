TARGET = ../aalib
OBJS = main.o \
	pspaalib.o \
	pspaalibwav.o \
	pspaalibscemp3.o \
	pspaalibat3.o \
	pspaalibeffects.o \
	id3.o \
	pspaalibogg.o \
	../../main/JSE.o

CFLAGS = -G0 -Wall -O2
ASFLAGS = $(CFLAGS)
LDFLAGS = -mno-crt0 -nostartfiles

PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

USE_USER_LIBC = 1
USE_USER_LIBS = 1

INCDIR = ../../

BUILD_PRX = 1

LIBS = -lpsputility -lpspaudio -lpspmp3 -lpsppower -lpspatrac3 -lvorbisidec -lm

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	rm *.o $(TARGET).elf
	psp-packer $(TARGET).prx