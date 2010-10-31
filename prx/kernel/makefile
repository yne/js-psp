TARGET = ../Kloader
OBJS = main.o

CFLAGS = -G0 -Wall -O2 -fshort-wchar -fno-pic -mno-check-zero-division
LDFLAGS = -mno-crt0 -nostartfiles
ASFLAGS = $(CFLAGS) -c
#add the export list to the prx + create the stub list included in the main
PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

INCDIR = ../../
LIBS = -lpspsystemctrl_kernel

USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
