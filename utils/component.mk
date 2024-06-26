
utils_MAIN = $(utils_ROOT)

utils_cJSON_INC += $(utils_MAIN)/cJSON/inc
utils_cString_INC += $(utils_MAIN)/cString/inc

INC_DIRS +=  $(utils_cJSON_INC)  $(utils_cString_INC)

utils_SRC_FILES += $(utils_MAIN)/cJSON/src/cJSON.c \
	$(utils_MAIN)/cJSON/src/cJSON_Utils.c \
	$(utils_MAIN)/cString/src/cString.c

$(eval $(call component_compile_rules,utils))

