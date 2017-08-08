#
# Makefile to build BTstack library for EV3RT
#

DIR=.
BTSTACK_ROOT=${DIR}/../..
DUMMY=$(shell )

# Tools
GCC_TARGET = arm-none-eabi
AR = $(GCC_TARGET)-ar
CC = $(GCC_TARGET)-gcc -O2 -nostdlib -std=gnu99 -fno-strict-aliasing -mcpu=arm926ej-s -mlittle-endian

LIBRARY_FILE=libBTstack.a

ALL_OBJS += run_loop.o           \
	run_loop_toppers.o			 \
	linked_list.o 				 \
	bnep.o					     \
	bt_control_cc256x.o 		 \
    hci_transport_h4_dma.o       \
	remote_device_db.o           \
	hci.o                        \
	utils.o                      \
	btstack_memory.o             \
	hci_cmds.o					 \
	pan.o						 \
	rfcomm.o					 \
	l2cap.o						 \
	l2cap_signaling.o			 \
	sdp.o						 \
	sdp_util.o					 \
	sdp_query_rfcomm.o			 \
	sdp_parser.o				 \
	sdp_client.o                 \
	memory_pool.o				 \
	bluetooth_spp_slave.o

#
# Include header and source files
#
CFLAGS += -I${BTSTACK_ROOT}/include \
		  -I${BTSTACK_ROOT}/chipset-cc256x \
		  -I${BTSTACK_ROOT}/src \
		  -I.
SRCDIRS = ${BTSTACK_ROOT}/src \
		  ${BTSTACK_ROOT}/chipset-cc256x
vpath %.c $(SRCDIRS)

#BLE_FILES  =  ad_parser.c att.c att_server.c att_dispatch.c att_db_util.c le_device_db_memory.c gatt_client.c
#BLE_FILES  += sm.c l2cap_le.c ancs_client_lib.h ancs_client_lib.c
#PORT_FILES = btstack-config.h bsp_arduino_em9301.cpp BTstack.cpp BTstack.h

#PATHS  = $(addprefix ${BTSTACK_ROOT}/src/, ${SRC_FILES})
PATHS += $(wildcard  ${BTSTACK_ROOT}/src/*.h)
#PATHS += $(addprefix ${BTSTACK_ROOT}/ble/, ${BLE_FILES})
#PATHS += $(wildcard  ${BTSTACK_ROOT}/ble/*.h)
#PATHS += $(wildcard  ${BTSTACK_ROOT}/chipset-cc256x/*)
PATHS += ${BTSTACK_ROOT}/include/btstack
#PATHS += ${BTSTACK_ROOT}/platforms/arduino/examples
#PATHS += $(addprefix ${DIR}/, ${PORT_FILES})

#ARDUINO_LIBS=~/Documents/arduino/libraries/BTstack

all: $(LIBRARY_FILE)

clean:
	rm -f ${ALL_OBJS} dummy dummy.o

realclean: clean
	rm -f ${LIBRARY_FILE}

update_version:
	${BTSTACK_ROOT}/tools/get_version.sh 

dummy: update_version dummy.o $(ALL_OBJS)
	$(CC) -o dummy dummy.o $(ALL_OBJS)

$(LIBRARY_FILE): update_version $(ALL_OBJS)
	$(AR) -rcs $@ $(ALL_OBJS)

$(ALL_OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $<

