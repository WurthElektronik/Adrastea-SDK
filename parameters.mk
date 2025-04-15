# Parameters for the Altair 125X MCU subsystem make process
#
# You can edit this file to change parameters, but a better option is
# to create a local.mk file and add overrides there. The local.mk file
# can be in the root directory, or the program directory alongside the
# Makefile, or both.
#
-include $(ROOT)local.mk
-include local.mk


FLAVOR ?= debug
#FLAVOR ?= release
DEVICE = ALT1250


# Output directories to store intermediate compiled files
# relative to the program directory
BUILD_DIR ?= $(dir $(PROGRAM_MAKEFILE))$(DEVICE)

SCRIPT_DIR ?= $(ROOT)script/

FLASHMCU ?= $(ROOT)/$(Sony_SDK_folder)/utils/flashmcu.py
ERASEMCU ?= $(ROOT)/$(Sony_SDK_folder)/utils/erasemcu.py
JTAGMCU ?= $(ROOT)/$(Sony_SDK_folder)/utils/jtagmcu.py
GENVER ?= $(ROOT)/$(Sony_SDK_folder)/utils/genver.py
DOXYGEN_GENERATOR ?= doxygen
ADRASTEA_FW_GENERATOR ?= $(ROOT)/$(Sony_SDK_folder)/utils/genfw.sh


# serial port settings for flashmcu.py
FLASHPORT ?= /dev/ttyACM1
FLASHBAUD ?= 115200

# Compiler names, etc. assume gdb
CROSS ?= arm-none-eabi-

AR = $(CROSS)ar
CC = $(CROSS)gcc
CPP = $(CROSS)cpp
LD = $(CROSS)gcc
NM = $(CROSS)nm
C++ = $(CROSS)g++
SIZE = $(CROSS)size
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

# Source components to compile and link. Each of these are subdirectories
# of the root, with a 'component.mk' file.

COMPONENTS     ?= $(EXTRA_COMPONENTS) \
    $(Utils_folder) \
    $(HAL_folder) \
    $(libraries_folder) \
    $(connectivity_folder) \
    $(WurthElectronic_SDK_folder) \
    $(Sony_SDK_folder)/CMSIS/Core \
    $(Sony_SDK_folder)/FreeRTOS \
    $(Sony_SDK_folder)/CMSIS/RTOS2 \
    $(Sony_SDK_folder)/ALT125x/Chipset  \
    $(Sony_SDK_folder)/ALT125x/Driver \
    $(Sony_SDK_folder)/applib \
    
# open source libraries linked in
LIBS ?=

# Set this to zero if you don't want individual function & data sections
# (some code may be slightly slower, linking will be slighty slower,
# but compiled code size will come down a small amount.)
SPLIT_SECTIONS ?= 1

# Set this to 1 to have all compiler warnings treated as errors (and stop the
# build).  This is recommended whenever you are working on code which will be
# submitted back to the main project, as all submitted code will be expected to
# compile without warnings to be accepted.
WARNINGS_AS_ERRORS ?= 0

# Common flags for both C & C++_
C_CXX_FLAGS ?= -Wall -Wextra -Wno-unused-parameter -Wl,-EL -include config.h $(EXTRA_C_CXX_FLAGS)  
# Flags for C only
CFLAGS		?= $(C_CXX_FLAGS) -std=gnu11 $(EXTRA_CFLAGS) -w 
# Flags for C++ only
CXXFLAGS	?= $(C_CXX_FLAGS) -std=c++0x -fno-exceptions -fno-rtti $(EXTRA_CXXFLAGS) 

# these aren't all technically preprocesor args, but used by all 3 of C, C++, assembler
CPPFLAGS	?= -mcpu=cortex-m4 -mthumb -specs=nano.specs $(EXTRA_CPPFLAGS)

LDFLAGS		?= -mcpu=cortex-m4 -mthumb -specs=nano.specs -specs=nosys.specs -Wl,--no-check-sections -Wl,-static -Wl,-Map=$(BUILD_DIR)/$(PROGRAM).map $(EXTRA_LDFLAGS)

ifeq ($(WARNINGS_AS_ERRORS),1)
    C_CXX_FLAGS += -Werror
endif

ifeq ($(SPLIT_SECTIONS),1)
  C_CXX_FLAGS += -ffunction-sections -fdata-sections
  LDFLAGS += -Wl,-gc-sections
endif

ifeq ($(FLAVOR),debug)
    C_CXX_FLAGS += -g -Og -DDEBUG
    LDFLAGS += -g -Og
else
    C_CXX_FLAGS += -g -Os -DNDEBUG
    LDFLAGS += -g -Os
endif

GITSHORTREV=\"$(shell cd $(ROOT); git rev-parse --short -q HEAD 2> /dev/null)\"
ifeq ($(GITSHORTREV),\"\")
  GITSHORTREV="\"(nogit)\"" # (same length as a short git hash)
endif
CPPFLAGS += -DGITSHORTREV=$(GITSHORTREV)

VERSION_TAG=\"$(shell python $(GENVER) --inverpath $(Sony_SDK_folder)/)\"
$(info    VERSION_TAG........ is $(VERSION_TAG))
CPPFLAGS += -DVERSION_TAG=$(VERSION_TAG)


ifeq ($(OS), Windows_NT)
  $(info    Windows Operating System detected.)
else

  OS := $(shell uname -s)
  
  ifeq ($(OS), Linux)

     # Define a file to check
    FILE_TO_CHECK := $(ROOT)/$(Sony_SDK_folder)/utils/genfw.sh
    
    # Check if the file is in Unix format or not.
    IS_UNIX_FORMAT := $(shell file $(FILE_TO_CHECK) | grep -q 'with CRLF line terminators' && echo "no" || echo "yes")

    ifeq ($(IS_UNIX_FORMAT), no) 
        # Convert the dos format util files into Unix Format inside SDK  
        $(info    Conversion is started........ )
        $(shell dos2unix -q $(ROOT)/$(Sony_SDK_folder)/utils/*.sh)
        $(shell dos2unix -q $(ROOT)/$(Sony_SDK_folder)/utils/*.py)
    endif
  endif
endif




