hal_MAIN = $(hal_ROOT)

hal_COMMON_INC_DIR = $(hal_MAIN)/common/inc

hal_PLATFORM_CONFIG_INC_DIR += $(hal_MAIN)/platform/inc
hal_HELPER_INC_DIR += $(hal_MAIN)/helper
hal_PLATFORM_INC_DIR += $(hal_MAIN)/platform
hal_I2C_INC_DIR += $(hal_MAIN)/peripherals/i2c
hal_FLASH_INC_DIR += $(hal_MAIN)/peripherals/flash
hal_UART_INC_DIR += $(hal_MAIN)/peripherals/uart

INC_DIRS += $(hal_COMMON_INC_DIR) $(hal_PLATFORM_CONFIG_INC_DIR) \
			$(hal_PLATFORM_INC_DIR) \
		    $(hal_I2C_INC_DIR) \
			$(hal_UART_INC_DIR) \
			$(hal_FLASH_INC_DIR) \
			$(hal_HELPER_INC_DIR)


hal_SRC_DIR += $(hal_MAIN)/common/src \
			$(hal_MAIN)/platform \
			$(hal_MAIN)/peripherals/i2c \
			$(hal_MAIN)/peripherals/uart \
			$(hal_MAIN)/peripherals/flash \
			$(hal_MAIN)/helper


$(eval $(call component_compile_rules,hal))
