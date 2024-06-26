
libraries_MAIN = $(libraries_ROOT)



libraries_AdrasteaFeatherWing_INC += $(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src
libraries_AdrasteaFeatherWing_INC += $(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands
libraries_AdrasteaFeatherWing_INC += $(libraries_MAIN)/FeatherWings/Common/Hardware_Libraries/global
libraries_AdrasteaFeatherWing_INC += $(libraries_MAIN)/FeatherWings/Common/Platform_Interfaces/Config

INC_DIRS +=  $(libraries_AdrasteaFeatherWing_INC) 

libraries_SRC_FILES += $(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATDevice.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATEvent.c  \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATGNSS.c   \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATHTTP.c   \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATMQTT.c   \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATPacketDomain.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATPower.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATProprietary.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATSIM.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATSMS.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/ATCommands/ATSocket.c \
	$(libraries_MAIN)/FeatherWings/AdrasteaFeatherWing/software/lib/WE_AdrasteaFeatherWing/src/Adrastea.c \
	$(libraries_MAIN)/FeatherWings/Common/Hardware_Libraries/global/ATCommands.c

$(eval $(call component_compile_rules,libraries))
