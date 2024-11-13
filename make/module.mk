ifndef MODULE
$(error MODULE variable is not defined)
endif

ifndef BOARD
$(error BOARD variable is not defined)
endif

ifdef TOOLCHAIN_PREFIX
CC := $(TOOLCHAIN_PREFIX)-gcc
CXX := $(TOOLCHAIN_PREFIX)-g++
AR := $(TOOLCHAIN_PREFIX)-ar
LD := $(TOOLCHAIN_PREFIX)-ld
endif

ifdef CPU
CPU_FLAG := -mcpu=$(CPU)
else
CPU_FLAG :=
endif

REPO_ROOT := $(shell git rev-parse --show-toplevel)
MODULE_PATH := $(REPO_ROOT)/$(MODULE)
MODULE_MAKEFILE := $(MODULE_PATH)/Makefile
BUILD_FOLDER := $(REPO_ROOT)/build/$(BOARD)
OBJ_FOLDER := $(BUILD_FOLDER)/obj
LIB_FOLDER := $(BUILD_FOLDER)/lib
EXEC_FOLDER := $(BUILD_FOLDER)/executable

ifeq ("$(wildcard $(MODULE_MAKEFILE))","")
$(error $(MODULE_MAKEFILE) not found)
endif

DEPENDENCIES        := 

GET_ABSOLUTE_PATH = $(foreach path,$(1),$(MODULE_PATH)/$(path))
GET_REPO_RELATIVE_PATH = $(foreach path,$(1),$(MODULE)/$(path))
MAKE_MODULE = $(MAKE) -f $(REPO_ROOT)/make/module.mk MODULE=$(1) BOARD=$(BOARD) CPU=$(CPU) $(2) -s
LOG_INFO = [ $(1) ] $(2)

include $(MODULE_MAKEFILE)

TYPE_MAKEFILE = $(REPO_ROOT)/make/types/$(MODULE_TYPE).mk
include $(TYPE_MAKEFILE)

ifndef MODULE_TYPE
$(error MODULE_TYPE variable is not defined)
endif

$(DEPENDENCIES): FORCE
	@$(call MAKE_MODULE,$@,build)

FORCE: ;