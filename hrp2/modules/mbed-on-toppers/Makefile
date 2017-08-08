#
# Makefile to build mbed library
#

DIR=.
DUMMY=$(shell )
OBJDIR=build
KERNELDIR=../..

# Tools
GCC_TARGET = arm-none-eabi
AR = $(GCC_TARGET)-ar
CC = $(GCC_TARGET)-gcc -O2 -nostdlib -std=gnu99 -fno-strict-aliasing -mcpu=arm926ej-s -mlittle-endian
CXX = $(GCC_TARGET)-g++ -O2 -nostdlib -std=gnu++11 -fno-strict-aliasing -mcpu=arm926ej-s -mlittle-endian -fpermissive

LIBRARY_FILE=libmbed.a

ALL_OBJS +=

# FIXME: dummy
CFLAGS += -I${DIR}/dummy
#ALL_CXX_OBJS += dummy/dummy.o dummy/rt_CMSIS.o dummy/Thread.o
ALL_CXX_OBJS += dummy/rt_CMSIS.o dummy/Thread.o
ALL_OBJS += dummy/syscall.o dummy/us_ticker.o
CFLAGS += -I${KERNELDIR}/include

# FIXME: hard-coded files for EV3RT
CFLAGS += -I${KERNELDIR}/target/ev3_gcc \
		  -I${KERNELDIR}/arch \
		  -I${KERNELDIR}/arch/arm_gcc/am1808 \
		  -I${KERNELDIR}/arch/arm_gcc/common \
		  -I${KERNELDIR}/modules/btstack/platforms/ev3rt \
		  -I${DIR}/arch/ev3rt
ALL_OBJS += ${DIR}/arch/ev3rt/btstack_emac.o \
			${DIR}/arch/ev3rt/lwip_httpd_handler.o
ALL_CXX_OBJS += ${DIR}/arch/ev3rt/mbed-interface.o

# mbed-os
CFLAGS += -I${DIR}/mbed-os \
		  -I${DIR}/mbed-os/hal \
		  -I${DIR}/mbed-os/hal/hal \
		  -I${DIR}/mbed-os/platform \
		  -I${DIR}/mbed-os/rtos \
		  -I${DIR}/mbed-os/drivers
ALL_CXX_OBJS += mbed-os/platform/retarget.o \
				mbed-os/drivers/FileBase.o \
				mbed-os/drivers/FileLike.o \
				mbed-os/drivers/FilePath.o \
				mbed-os/drivers/FileSystemLike.o \
				mbed-os/drivers/Stream.o \
				mbed-os/rtos/Mutex.o \
				mbed-os/rtos/Semaphore.o
ALL_OBJS += mbed-os/platform/mbed_error.o \
			mbed-os/platform/mbed_interface.o

#include Makefile.USBHost
include Makefile.lwIP

#
# Include header and source files
#
vpath %.c $(SRCDIRS)

all: prepare-obj-folder $(LIBRARY_FILE)

clean:
	cd ${OBJDIR}; \
	rm -f ${ALL_OBJS} dummy.o

realclean: clean
	cd ${OBJDIR}; \
	rm -f ${LIBRARY_FILE}

dummy: dummy.o $(ALL_OBJS)
	$(CC) -o dummy dummy.o $(ALL_OBJS)

define print_cmd
  @printf "  %-7s %s\n" $1 $2 1>&2
endef

$(LIBRARY_FILE): $(ALL_OBJS) $(ALL_CXX_OBJS)
	$(call print_cmd, "AR", $@)
	@cd $(OBJDIR) && \
	$(AR) -rcs $@ $(ALL_OBJS) $(ALL_CXX_OBJS)
	@#arm-none-eabi-g++  $(ALL_OBJS) $(ALL_CXX_OBJS)

$(ALL_OBJS): %.o: %.c
	$(call print_cmd, "CC", $<)
	@mkdir -p $(shell dirname $(OBJDIR)/$@)
	@$(CC) -c $(CFLAGS) -c $< -o $(OBJDIR)/$@

$(ALL_CXX_OBJS): %.o: %.cpp
	$(call print_cmd, "CXX", $<)
	@mkdir -p $(shell dirname $(OBJDIR)/$@)
	@$(CXX) -c $(CFLAGS) -c $< -o $(OBJDIR)/$@

prepare-obj-folder:
	@mkdir -p $(OBJDIR)

.PHONY: prepare-obj-folder
