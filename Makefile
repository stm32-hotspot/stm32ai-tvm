#
# @attention
#
# Copyright (c) 2022 STMicroelectronics.
# All rights reserved.
#
# This software is licensed under terms that can be found in the LICENSE file
# in the root directory of this software component.
# If no LICENSE file comes with this software, it is provided AS-IS.
#

# Top level Makefile for the STM32 microcontroller project.

#
# Set the path to your ARM Toolset.
# Only gcc is supported at this time.
#
#export ARM_PATH ?= 
ifndef ARM_PATH
$(error ARM_PATH must be set and point at your GCC ARM compiler installation)
endif

#
# Set the path to your TVM compiler installation
#
#export TVM_PATH ?= 
ifndef TVM_PATH
$(error TVM_PATH must be set and point at your TVM stack installation)
endif

#export X_CUBE_TOOL_PATH ?= 
ifndef X_CUBE_TOOL_PATH
$(error X_CUBE_TOOL_PATH must be set and point at your STM32 Cube Programmer installation)
endif

#
# Choose a board from the list below and setup the firmware path
#

# -----------------------------------
# Disco
# -----------------------------------
#BOARD = disco-h747i
#SERIAL_NUMBER = 
#export X_CUBE_PATH = 

# -----------------------------------
# Nucleao
# -----------------------------------
#BOARD = nucleo-f412zg
#SERIAL_NUMBER = 
#export X_CUBE_PATH = 

# Indicate the revision of the board (if necessary)
#  xyy with x:1 for A, 2 for B ...
#           yy:01 ...
# ex: MB1361-L552ZEQ-C02	-> 302
#     MB1361-L552ZEQ-A02    -> 102
# BOARD_VERSION ?= 102

ifeq ($(BOARD), disco-h747i)
  EXTLOAD = "${X_CUBE_TOOL_PATH}/ExternalLoader/MT25TL01G_STM32H747I-DISCO.stldr"
endif

# 115200
# BAUDRATE = 921600

STM32_PROG ?= ${X_CUBE_TOOL_PATH}/STM32_Programmer_CLI

ifdef EXTLOAD
STM32_PROG += --extload $(EXTLOAD)
endif

BUILD_DIR = ./build/$(BOARD)
BOARDS_DIR = ./Boards

APP_NAME = Project

debug:
	@echo " === Board: $(BOARD) ..."

check:
	$(if $(strip $(MODEL_PATH)), @echo " === Model path: $(MODEL_PATH)", $(error MODEL_PATH must be set and point at your model implementation generated with the TVM compiler))
	@if [ ! -d "$(MODEL_PATH)" ]; then \
		echo "$(MODEL_PATH) does not exist!"; \
		exit 1; \
	fi

info:
	$(MAKE) -f $(BOARDS_DIR)/makefile.$(BOARD) info BUILD_DIR=$(BUILD_DIR) APP_NAME=$(APP_NAME)

perf: check
	@echo " === Perf: Building from TVM sources ..."
	$(MAKE) -f $(BOARDS_DIR)/makefile.$(BOARD) CONFIG=$(LDCONF) BUILD_DIR=$(BUILD_DIR) APP_NAME=$(APP_NAME)

valid: debug check
	@echo " === Validation: Building from TVM sources ..."
	$(MAKE) -f $(BOARDS_DIR)/makefile.$(BOARD) VALID=1 CONFIG=$(LDCONF) BUILD_DIR=$(BUILD_DIR) APP_NAME=$(APP_NAME)

#######################################
# clean up
#######################################

clean: app.clean

app.clean:
	@echo -e "I: Cleaning APP build directory (${BUILD_DIR}/*)..."
	${q}rm -rf $(BUILD_DIR)

clean_nn:
	-rm $(BUILD_DIR)/network.*	
	-rm $(BUILD_DIR)/network_data.*
	-rm $(BUILD_DIR)/network_lib.*

#######################################
# flash
#######################################

flash: $(BUILD_DIR)/$(APP_NAME).elf 
	${STM32_PROG} -c port=swd sn=${SERIAL_NUMBER} mode=UR reset=HWrst -d $(BUILD_DIR)/$(APP_NAME).elf -s
