mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
util.o \
EtRobocon2017.o \
SonarAlert.o \
LineTracerWalker.o \
Pid.o \
SpeedControl.o \
TurnControl.o \
Distance.o \
Walker.o \
Lifter.o \
SelfLocalization.o \
Emoter.o \
NormalCourse.o \
Parking.o

ifeq ($(side),right)
    APPL_CXXOBJS += RightNormalCourse.o \
    RightCourse.o \
    BasicWalker.o \
    Shinkansen.o \

endif

ifeq ($(side),left)

    APPL_CXXOBJS += LeftNormalCourse.o \
    LeftCourse.o \
    PuzzleField.o\
    BasicWalker.o \
    UserInterface.o \
    FirstCode.o \
    Block.o \
    Node.o \
    PuzzleCodeConverter.o \
    TargetFigure.o\
    BoardAnalyzer.o\
	PuzzleExplorer.o

endif

SRCLANG := c++

APPL_DIR += $(mkfile_path)apps
APPL_DIR += $(mkfile_path)apps/explorer

INCLUDES += -I$(mkfile_path)apps 

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
