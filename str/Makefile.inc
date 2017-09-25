mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
util.o \
EtRobocon2017.o \
SonarAlert.o \
LineTracer.o \
Pid.o \
NormalCourse.o \
LeftNormalCourse.o \
RightNormalCourse.o \
SpeedControl.o \
TurnControl.o \
Distance.o \
Walker.o \
Lifter.o \
SelfLocalization.o \
Emoter.o \
LeftCourse.o \
RightCourse.o \
PuzzleLineTracer.o\
BasicWalker.o

SRCLANG := c++

APPL_DIR += $(mkfile_path)apps

INCLUDES += -I$(mkfile_path)apps


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
