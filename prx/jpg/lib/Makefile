PSPSDK=$(shell psp-config --pspsdk-path)
TARGET_LIB = libjpeg.a
OBJS =	jcmainct.o jctrans.o jdhuff.o jdsample.o jidctint.o jcapimin.o \
	jcmarker.o jdapimin.o jdinput.o  jdtrans.o jidctred.o jcapistd.o \
	jcmaster.o jdapistd.o jdmainct.o jerror.o jmemmgr.o jccoefct.o \
	jcomapi.o jdatadst.o jdmarker.o jfdctflt.o jmemnobs.o jccolor.o \
	jcparam.o jdatasrc.o jdmaster.o jfdctfst.o jquant1.o jcdctmgr.o \
	jcphuff.o jdcoefct.o jdmerge.o jfdctint.o jquant2.o jchuff.o \
	jcprepct.o jdcolor.o jdphuff.o jidctflt.o jutils.o jcinit.o \
	jcsample.o jddctmgr.o jdpostct.o jidctfst.o memsrc.o

CFLAGS = -O2 -G0

include $(PSPSDK)/lib/build.mak

all:
	rm *.o
	mv $(TARGET_LIB) ../$(TARGET_LIB)