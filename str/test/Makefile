#mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

CPP = g++
TARGET := SonarAlertTest

SRCS := $(APPL_CXXOBJS:.o=.cpp)

APPL_CXXOBJS += \
SonarAlertTest.o \
../str/SonarAlert.o\
gtest_main.o \
gtest-all.o

SRCLANG := c++

APPL_DIR += $(mkfile_path)app

INCLUDES += \
-I. \
-I../app \
-I../googletest/googletest/include

# -I$(mkfile_path)/../app \
# -I$(mkfile_path) \
# -I$(mkfile_path)/../googletest/googletest/include
 
.PHONY: all
all: $(TARGET)

$(TARGET): $(APPL_CXXOBJS)
	$(CPP) $(APPL_CXXOBJS) $(INCLUDES) -o $(TARGER)

# ifdef CONFIG_EV3RT_APPLICATION
# 
# # Include libraries
# include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
# 
# endif
