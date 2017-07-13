mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
util.o \
EtRobocon2017.o \
SonarAlert.o \
LineTracer.o \
pid.o \
Walker.o \
Lifter.o \
Emoter.o

SRCLANG := c++

APPL_DIR += $(mkfile_path)app

INCLUDES += \
-I$(mkfile_path)app


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
