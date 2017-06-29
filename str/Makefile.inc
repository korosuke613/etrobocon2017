mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
<<<<<<< HEAD

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
BalancerCpp.o \
SonarAlert.o
=======

APPL_CXXOBJS += \
util.o \
EtRobocon2017.o \
SonarAlert.o \
LineTracer.o \
pid.o \
Walker.o \
Lifter.o \
Emoter.o
>>>>>>> 8068413fa9c3f18cac400d47730f7be1b12edc78

SRCLANG := c++

APPL_DIR += $(mkfile_path)app

INCLUDES += \
<<<<<<< HEAD
    -I$(mkfile_path)app
=======
-I$(mkfile_path)app


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
>>>>>>> 8068413fa9c3f18cac400d47730f7be1b12edc78
