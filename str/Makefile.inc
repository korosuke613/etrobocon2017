mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
util.o \
EtRobocon2017.o \
SonarAlert.o \
LineTracerWalker.o \
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
UserInterface.o \
FirstCode.o \
PuzzleLineTracer.o\
basicWalker.o\
Navigation.o \


SRCLANG := c++

APPL_DIR += $(mkfile_path)apps
APPL_DIR += $(mkfile_path)apps/explorer

INCLUDES += -I$(mkfile_path)apps


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
