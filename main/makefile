TARGET = ../main
OBJS = main.o boot.o functions.o shared.o ../prx/kernel/modK.o

CFLAGS = -G0 -Wall -O2
# -DDEBUG_MODE -DUSE_KERNEL
ASFLAGS = $(CFLAGS)
#LDFLAGS = -nostdlib -nodefaultlibs -mno-explicit-relocs

PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

USE_USER_LIBC = 1
USE_USER_LIBS = 1

INCDIR = ../

LIBDIR = ../src
LIBS= -lspidermonkey
#add -lm if you builded spidermonkey without VFPU optimisation

#PSP_LARGE_MEMORY = 1
BUILD_PRX = 1

#EXTRA_TARGETS = EBOOT.PBP
#PSP_EBOOT_TITLE = JS-PSP
#PSP_EBOOT_ICON1 = ../prx/Kloader.prx
#PSP_EBOOT_PSAR = ../js/pong.js

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	mksfoex.exe JS-PSP PARAM.SFO -d MEMSIZE=1 -s DISC_ID=SPDR00000 -d JS_RT_SIZE=14336 -d JS_CX_SIZE=8192 -s JS_FILE=main.js
	pack-pbp EBOOT.PBP PARAM.SFO NULL ../prx/Kloader.prx NULL NULL NULL ../main.prx ../js/pong.js
	rm -f *.o ${TARGET}.elf ../EBOOT.PBP
	echo y | psp-packer EBOOT.PBP
	mv EBOOT.PBP ..
	