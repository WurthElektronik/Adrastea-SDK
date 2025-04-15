connectivity_MAIN = $(connectivity_ROOT)

connectivity_aws_INC = $(connectivity_MAIN)/aws
connectivity_mosquitto_INC = $(connectivity_MAIN)/mosquitto
connectivity_azure_INC += $(connectivity_MAIN)/azure
connectivity_kaaiot_INC += $(connectivity_MAIN)/kaaiot
connectivity_configuration_INC += $(connectivity_MAIN)/configuration

INC_DIRS +=  $(connectivity_aws_INC) \
				$(connectivity_mosquitto_INC)  \
				$(connectivity_azure_INC) \
				$(connectivity_kaaiot_INC) \
				$(connectivity_configuration_INC)

connectivity_SRC_FILES += $(connectivity_MAIN)/aws/aws_adrastea.c  \
	$(connectivity_MAIN)/azure/azure_adrastea.c \
	$(connectivity_MAIN)/mosquitto/mosquitto_adrastea.c \
	$(connectivity_MAIN)/kaaiot/kaaiot_adrastea.c \
	$(connectivity_MAIN)/configuration/cloud_config.c


$(eval $(call component_compile_rules,connectivity))
