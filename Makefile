##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.13.0-B3] date: [Mon Mar 01 18:23:39 MSK 2021] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = output


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources

# C_FILES = src/*.c
C_FILES := $(wildcard src/*.c)

C_LIBS =  \
lib/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc/system_MDR32F9Qx.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_rst_clk.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_timer.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_port.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_ssp.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_adc.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_dma.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_usb.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_uart.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_arinc429r.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_arinc429t.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_audio.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_can.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_comp.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_dac.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_ebc.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_eth.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_i2c.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_iwdg.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_keypad.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_led.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_mil_std_1553.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_power.c \
lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_wwdg.c 
# lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_eeprom.c \
# lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_bkp.c \

C_SOURCES = $(C_FILES) $(C_LIBS)

# ASM sources
ASM_SOURCES =  \
lib/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc/startup_MDR32F9Qx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#Debug
#Instead cflag -O2 set -O0 -ggdb3.

#Select MCU architecture

#Instead cflag -mcpu=cortex-m3 use:

#-mcpu=cortex-m0     # MDR1986BE4
#-mcpu=cortex-m1     # MDR1986VE1T, MDR1986VE3
#-mcpu=cortex-m3     # MDR1986VE9x, MDR1901VC1T
#Instead compiler definition -DUSE_MDR1986VE9x use:

#-DUSE_MDR1901VC1T   # MDR1901VC1T
#-DUSE_MDR1986VE1T   # MDR1986VE1T
#-DUSE_MDR1986VE3    # MDR1986VE3
#-DUSE_MDR1986BE4    # MDR1986BE4
#-DUSE_MDR1986VE9x   # MDR1986VE9x

#######################################
# cpu
CPU = -mcpu=cortex-m3


# mcu
MCU = $(CPU) -mthumb


# C defines
C_DEFS =  \
-DUSE_MDR1986VE9x \
-D__STARTUP_CLEAR_BSS \
-D__START=main

# C includes
C_INCLUDES =  \
-Ilib \
-Ilib/Config \
-Ilib/CMSIS/CM3/DeviceSupport/MDR32F9Qx/inc \
-Ilib/MDR32F9Qx_StdPeriph_Driver/inc \
-Ilib/MDR32F9Qx_StdPeriph_Driver/inc/USB_Library \
-Ilib/CMSIS/CM3/CoreSupport \
-Ilib/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc 


EXTRA_DATA = -Wextra -Wshadow -Wredundant-decls -Wno-missing-field-initializers -Wconversion -Wno-packed-bitfield-compat -pipe

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -flto $(EXTRA_DATA)

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -flto $(EXTRA_DATA)

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = lib/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc/MDR32F9Qx.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 

LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin



#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
