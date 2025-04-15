# This makefile is adapted from the esp-open-rtos makefile
# https://github.com/SuperHouse/esp-open-rtos, but it has changed very significantly
# since then.

# assume the 'root' directory (ie top of the tree) is the directory common.mk is in



include $(ROOT)parameters.mk

ifndef PROGRAM
$(error "Set the PROGRAM environment variable in your Makefile before including common.mk")
endif

# hacky way to get a single space value
empty :=
space := $(empty) $(empty)

# GNU Make lowercase function, bit of a horrorshow but works (courtesy http://stackoverflow.com/a/665045)
lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

# assume the program dir is the directory the top-level makefile was run in
PROGRAM_DIR := $(dir $(firstword $(MAKEFILE_LIST)))applications
SETTINGS_DIR := Settings_folder

# derive various parts of compiler/linker arguments
LIB_ARGS      = $(addprefix -l,$(LIBS))
PROGRAM_OUT   = $(BUILD_DIR)/$(PROGRAM).elf

# Custom partitions addresses on flash for cloud settings 
LINKER_SCRIPTS += $(Settings_folder)/cloud_settings_def.ld
LDFLAGS      += $(addprefix -T,$(LINKER_SCRIPTS))

ADRASTEA_FW_FILE = $(addprefix $(BUILD_DIR)/,$(PROGRAM).bin)
DOXYFILE = $(ROOT)/Doxyfile

# Common include directories, shared across all "components"
# components will add their include directories to this argument
#
# Placing $(PROGRAM_DIR) and $(PROGRAM_DIR)include first allows
# programs to have their own copies of header config files for components
# , which is useful for overriding things.
INC_DIRS     += $(PROGRAM_DIR)/source $(PROGRAM_DIR)/include $(ROOT)/include

CONFIG_H := $(shell grep "\#define" "$(PROGRAM_DIR)/include/config.h")


ifeq ("$(V)","1")
Q :=
vecho := @true
else
Q := @
vecho := @echo
endif


.PHONY: all clean flash erase_flash size rebuild 


all: $(PROGRAM_OUT) $(ADRASTEA_FW_FILE) 

$(ADRASTEA_FW_FILE): $(PROGRAM_OUT) $(BUILD_DIR)
	$(vecho) "FW $@"
	$(Q) $(ADRASTEA_FW_GENERATOR) $@


# component_compile_rules: Produces compilation rules for a given
# component
#
# For user-facing documentation, see:
# https://github.com/SuperHouse/esp-open-rtos/wiki/Build-Process#adding-a-new-component
#
# Call arguments are:
# $(1) - component name
#
# Expects that the following component-specific variables are defined:
#
# $(1)_ROOT    = Top-level dir containing component. Can be in-tree or out-of-tree.
#                (if this variable isn't defined, directory containing component.mk is used)
# $(1)_SRC_DIR = List of source directories for the component. All must be under $(1)_ROOT
# $(1)_INC_DIR = List of include directories specific for the component
#
#
# Each call appends to COMPONENT_ARS or WHOLE_ARCHIVES which are lists of archive files for compiled components
COMPONENT_ARS =
WHOLE_ARCHIVES =
define component_compile_rules
$(1)_DEFAULT_ROOT := $(dir $(lastword $(MAKEFILE_LIST)))

$(1)_ROOT ?= $$($(1)_DEFAULT_ROOT:/=)
$(1)_OBJ_DIR   = $(BUILD_DIR)/$(1)
### determine source files and object files ###
$(1)_SRC_FILES ?= $$(foreach sdir,$$($(1)_SRC_DIR), 				\
			$$(wildcard $$(sdir)/*.c) $$(wildcard $$(sdir)/*.S) 	\
			$$(wildcard $$(sdir)/*.cpp)) 				\
			$$($(1)_EXTRA_SRC_FILES)
$(1)_REAL_EXCLUDED_SRC_FILES = $$(foreach sfile,$$($(1)_EXCLUDED_SRC_FILES),$$(sfile))
$(1)_REAL_SRC_FILES = $$(filter-out $$($(1)_REAL_EXCLUDED_SRC_FILES), $$(foreach sfile,$$($(1)_SRC_FILES),$$(sfile)))
$(1)_REAL_ROOT = $$($(1)_ROOT)
# patsubst here substitutes real component root path for the relative OBJ_DIR path, making things short again
$(1)_OBJ_FILES_CXX = $$(patsubst $$($(1)_REAL_ROOT)%.cpp,$$($(1)_OBJ_DIR)%.o,$$($(1)_REAL_SRC_FILES))
$(1)_OBJ_FILES_C = $$(patsubst $$($(1)_REAL_ROOT)%.c,$$($(1)_OBJ_DIR)%.o,$$($(1)_OBJ_FILES_CXX))
$(1)_OBJ_FILES = $$(patsubst $$($(1)_REAL_ROOT)%.S,$$($(1)_OBJ_DIR)%.o,$$($(1)_OBJ_FILES_C))
# the last included makefile is our component's component.mk makefile (rebuild the component if it changes)
$(1)_MAKEFILE ?= $(lastword $(MAKEFILE_LIST))

### determine compiler arguments ###
$(1)_CC_BASE = $(Q) $(CC) $$(addprefix -I,$$(INC_DIRS)) $$(addprefix -I,$$($(1)_INC_DIR)) $$(CPPFLAGS) $$($(1)_CPPFLAGS)
$(1)_AR = $(BUILD_DIR)/$(1).a

$$($(1)_OBJ_DIR)%.o: $$($(1)_REAL_ROOT)%.c $$($(1)_MAKEFILE) $(wildcard $(ROOT)*.mk) | $$($(1)_SRC_DIR)
	$(vecho) "CC $$<"
	$(Q) mkdir -p $$(dir $$@)
	$$($(1)_CC_BASE) $$(CFLAGS) $$($(1)_CFLAGS) -c $$< -o $$@
	$$($(1)_CC_BASE) $$(CFLAGS) $$($(1)_CFLAGS) -MM -MT $$@ -MF $$(@:.o=.d) $$<

$$($(1)_OBJ_DIR)%.o: $$($(1)_REAL_ROOT)%.cpp $$($(1)_MAKEFILE) $(wildcard $(ROOT)*.mk) | $$($(1)_SRC_DIR)
	$(vecho) "C++ $$<"
	$(Q) mkdir -p $$(dir $$@)
	$$($(1)_CC_BASE) $$(CXXFLAGS) $$($(1)_CXXFLAGS) -c $$< -o $$@
	$$($(1)_CC_BASE) $$(CXXFLAGS) $$($(1)_CXXFLAGS) -MM -MT $$@ -MF $$(@:.o=.d) $$<

$$($(1)_OBJ_DIR)%.o: $$($(1)_REAL_ROOT)%.S $$($(1)_MAKEFILE) $(wildcard $(ROOT)*.mk) | $$($(1)_SRC_DIR)
	$(vecho) "AS $$<"
	$(Q) mkdir -p $$(dir $$@)
	$$($(1)_CC_BASE) -c $$< -o $$@
	$$($(1)_CC_BASE) -MM -MT $$@ -MF $$(@:.o=.d) $$<

$(1)_AR_IN_FILES = $$($(1)_OBJ_FILES)

$$($(1)_AR): $$($(1)_AR_IN_FILES)
	$(vecho) "AR $$@"
	$(Q) mkdir -p $$(dir $$@)
	$(Q) $(AR) cru $$@ $$^

ifdef $(1)_WHOLE_ARCHIVE
   WHOLE_ARCHIVES += $$($(1)_AR)
else
   COMPONENT_ARS += $$($(1)_AR)
endif

-include $$($(1)_OBJ_FILES:.o=.d)
endef

# include "dummy component" for the 'program' object files, defined in the Makefile
PROGRAM_SRC_DIR ?= $(PROGRAM_DIR)/source
PROGRAM_ROOT ?= $(PROGRAM_DIR)
PROGRAM_MAKEFILE = $(firstword $(MAKEFILE_LIST))
$(eval $(call component_compile_rules,PROGRAM))


## Include other components (this is where the actual compiler sections are generated)
##
## if component directory exists relative to $(ROOT), use that.
## otherwise try to resolve it as an absolute path
$(foreach component,$(COMPONENTS), 					\
	$(if $(wildcard $(ROOT)$(component)),				\
		$(eval include $(ROOT)$(component)/component.mk), 	\
		$(eval include $(component)/component.mk)		\
	)								\
)

# final linking step to produce .elf
$(PROGRAM_OUT): $(WHOLE_ARCHIVES) $(COMPONENT_ARS) $(LINKER_SCRIPTS) 
	$(vecho) "LD $@"
	$(Q) $(LD) $(LDFLAGS) -Wl,--whole-archive $(WHOLE_ARCHIVES) -Wl,--no-whole-archive -Wl,--start-group  $(COMPONENT_ARS) $(LIB_ARGS) -Wl,--end-group -o $@

$(BUILD_DIR):
	$(Q) mkdir -p $@

flash: all
	$(Q) $(FLASHMCU) -B $(FLASHBAUD) -L $(FLASHPORT) $(FW_FILE)

erase_flash:
	$(Q) $(ERASEMCU) -L $(FLASHPORT)

size: $(PROGRAM_OUT)
	$(Q) $(CROSS)size --format=berkeley $(PROGRAM_OUT)

doxgen_docs:
	$(Q) $(DOXYGEN_GENERATOR) $(DOXYFILE)

# the rebuild target is written like this so it can be run in a parallel build
# environment without causing weird side effects
rebuild:
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) clean
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) all

clean:
	$(Q) rm -rf $(BUILD_DIR)

# prevent "intermediate" files from being deleted
.SECONDARY:

# print some useful help stuff
help:
	@echo "Altair 125X MCU Subsystem make"
	@echo ""
	@echo "Other targets:"
	@echo ""
	@echo "all"
	@echo "Default target. Will build firmware including any changed source files."
	@echo
	@echo "clean"
	@echo "Delete all build output."
	@echo ""
	@echo "rebuild"
	@echo "Build everything fresh from scratch."
	@echo ""
	@echo ""
	@echo "size"
	@echo "Build, then print a summary of built firmware size."
	@echo ""
	@echo "TIPS:"
	@echo "* You can use -jN for parallel builds. Much faster! Use 'make rebuild' instead of 'make clean all' for parallel builds."
	@echo "* You can create a local.mk file to create local overrides of variables like FLASHPORT & FLASHBAUD."
	@echo ""
	@echo "SAMPLE COMMAND LINE:"
	@echo "make -j$$(getconf _NPROCESSORS_ONLN) flash FLASHPORT=/dev/ttyACM1"
	@echo ""


