TARGET = ../main
OBJS = main.o functions.o shared.o ../prx/kernel/modK.o

CFLAGS = -G0 -Wall -O2 -DDEBUG_MODE
#-DUSE_KERNEL
ASFLAGS = $(CFLAGS)
#LDFLAGS = -nodefaultlibs -mno-explicit-relocs

PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

USE_USER_LIBC = 1
USE_USER_LIBS = 1

INCDIR = ../

LIBDIR = ../src
LIBS= -lspidermonkey
#add -lm if you builded spidermonkey without VFPU optimisation

PSP_LARGE_MEMORY = 1
BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = JS-PSP

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	rm *.o ${TARGET}.elf ../EBOOT.PBP
	echo y | psp-packer EBOOT.PBP
	mv EBOOT.PBP ../EBOOT.PBP