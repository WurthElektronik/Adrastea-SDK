# Makefile

PROGRAM := adrastea_sensor_app
ROOT := $(dir $(lastword $(MAKEFILE_LIST)))

Sony_SDK_folder := $(ROOT)sdk/Sony/version2_2/altair_mcu/SDK
WurthElectronic_SDK_folder := $(ROOT)sdk/WuerthElektronik/Sensor
Utils_folder := $(ROOT)utils
HAL_folder := $(ROOT)hal
TEST_folder := $(ROOT)tests
libraries_folder := $(ROOT)libraries
connectivity_folder := $(ROOT)connectivity
Settings_folder := $(ROOT)settings

EXTRA_CFLAGS += -DDEBUG -DALT1250 -D__ENABLE_MQTT_API__=1 -D__ENABLE_AWS_API__=1 -D__ENABLE_CERTMGMT_API__=1 -DWE_USE_FLOAT -lm

EXTRA_COMPONENTS = $(Sony_SDK_folder)/middleware/printf \
		   $(Sony_SDK_folder)/middleware/osal \
		   $(Sony_SDK_folder)/middleware/hifc \
		   $(Sony_SDK_folder)/middleware/serial \
		   $(Sony_SDK_folder)/middleware/miniconsole \
		   $(Sony_SDK_folder)/middleware/pwrmanager
		   
include common.mk


