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

#
# Default options
#

# Indicates how to build the AI lib (see ../Nucleo-Lib/GCC/Makefile)
#
#   AI_DEBUG,AI_RELEASE
#  -------------------------------------------------
# 	1, x					-g3 -O0 -DDEBUG
# 	0, 0					-g3 -O3 -DNDEBUG 
# 	0, 1					-O3 -DNDEBUG -DRELEASE 
AI_DEBUG ?= 0
AI_RELEASE ?= 0

APP_OPTIM ?= -O3
APP_DEBUG ?= 0

