TARGET = ../main
OBJS = main.o

CFLAGS = -G0 -Wall -O2
ASFLAGS = $(CFLAGS)
#LDFLAGS = -nodefaultlibs -mno-explicit-relocs

INCDIR = ../

LIBDIR = ../src
LIBS= -lspidermonkey -lm 

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

