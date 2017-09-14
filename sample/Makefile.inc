mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
util.o 

SRCLANG := c++

APPL_DIR += $(mkfile_path)../str/ev3-api/library/libcpp-ev3/src

INCLUDES += -I$(mkfile_path)../str/ev3-api/library/libcpp-ev3/include


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
