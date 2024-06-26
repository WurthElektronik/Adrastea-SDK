

Sensor_MAIN = $(Sensor_ROOT)

Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_HIDS_2525020210001
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_HIDS_2525020210002
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_ISDS_2536030320001
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_ITDS_2533020201601
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_PADS_2511020213301
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_PDUS_25131308XXX01
Sensor_SensorSDK_INC += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_TIDS_2521020222501

INC_DIRS +=  $(Sensor_SensorSDK_INC) 

Sensor_SRC_DIR += $(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_HIDS_2525020210001 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_HIDS_2525020210001 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_HIDS_2525020210002 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_ISDS_2536030320001 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_ITDS_2533020201601 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_PADS_2511020213301 \
				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_PDUS_25131308XXX01 \
 				$(Sensor_MAIN)/Sensors-SDK_STM32/SensorsSDK/WSEN_TIDS_2521020222501

$(eval $(call component_compile_rules,Sensor))
