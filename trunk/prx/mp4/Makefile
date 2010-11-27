TARGET = main
OBJS = main.o mp4_read.o mp4_file.o time_math.o mpegbase.o cooleyesBridge.o

BUILD_PRX = 1
PSP_FW_VERSION=371

CFLAGS = -G0 -Wall -O2 -DDEVHOOK -DPSPFW3XX
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS= -lmp4info -lpsppower -lpspmpeg -lpspaudiocodec -lpspaudio -lm -lpsprtc -lpspgu

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	rm *.o *.elf