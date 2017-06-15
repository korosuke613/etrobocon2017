mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
SonarAlert.o

SRCLANG := c++

APPL_DIR += $(mkfile_path)app

INCLUDES += \
-I$(mkfile_path)app
