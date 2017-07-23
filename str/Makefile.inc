mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
BalancerCpp.o \
SonarAlert.o \
SelfLocalization.o

SRCLANG := c++

APPL_DIR += $(mkfile_path)app

INCLUDES += \
    -I$(mkfile_path)app