TARGET = ../template_driver
OBJS = main.o

LDFLAGS = -mno-crt0 -nostartfiles

#add the export list to the prx + create the stub list included in the main
PRX_EXPORTS = export.exp
$(shell psp-build-exports -s ${PRX_EXPORTS})

#work both with user/PSPsdk/kernel lib c/s
USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1
#export don't work with KERNEL lib ...
#USE_KERNEL_LIBC = 1
#USE_KERNEL_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
