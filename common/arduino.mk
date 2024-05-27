ifeq (${PROG},)
$(error Please specify PROG = ... in your main Makefile.)
endif

ifeq (${SRC},)
$(error Please specify SRC += ... in your main Makefile.)
endif

# First target is default target.
all:

##############################################################################
##############################################################################
##############################################################################
# The path of Arduino IDE
ARDUINO_DIR = /opt/arduino-1.8.1
# NATIVE
#TOOLCHAIN   = /usr/bin
# OR
TOOLCHAIN   = $(ARDUINO_DIR)/hardware/tools/avr/bin
##############################################################################
##############################################################################
##############################################################################

AVRDUDECONF = /etc/avrdude.conf
AVRDUDE     = avrdude -C $(AVRDUDECONF)
CC          = avr-gcc
CPP         = avr-g++
OBJCOPY     = avr-objcopy
OBJDUMP     = avr-objdump
AVR_SIZE    = avr-size

MCU         = atmega328p
F_CPU       = 16000000UL

PORT        = /dev/ttyUSB0
BAUD        = 115200
PROTOCOL    = arduino
PART        = ATMEGA328P
COM_SPEED   = 9600

ifeq ($(DEBUG),1)
CFLAGS       += -g3 -gdwarf-2
endif

AVRDUDEFLAGS  = -F -V -c ${PROTOCOL} -p ${PART} -P ${PORT} -b ${BAUD}
CPPFLAGS     += -DF_CPU=${F_CPU}
TARGET_ARCH   = -mmcu=${MCU}
COPTFLAG      = -std=gnu99 -Os
CFLAGS       += ${COPTFLAG}
#LDFLAGS += -Xlinker -Map=$(PROG).map
WFLAGS       += -Wall -Wextra
CFLAGS       += ${WFLAGS} ${INCLUDE}
LDFLAGS      += ${WFLAGS}
ASFLAGS      += ${WFLAGS}

SRC_C = $(filter %.c,${SRC})
SRC_s = $(filter %.s,${SRC})
SRC_S = $(filter %.S,${SRC})

OBJ = $(SRC_C:.c=.o) $(SRC_s:.s=.o) $(SRC_S:.S=.o)

##############################################################################
PWD  := $(shell pwd)
PATH := ${TOOLCHAIN}:${PATH}
##############################################################################

.PHONY: all clean upload download

%.hex: %
	${OBJCOPY} -O ihex -R .eeprom $< $@
	${AVR_SIZE} --format=avr --mcu=${MCU} ${PROG}

%.bin: %
	${OBJCOPY} -O binary -R .eeprom $< $@

%.code: %
	${OBJDUMP} -S $< >$@

%.lst: %
	${OBJDUMP} -d $< >$@

${PROG}: ${OBJ}

all: ${PROG} ${PROG}.hex

clean:
	rm -f ${PROG} $(addprefix ${PROG}, .hex .map .code .lst .bin) ${OBJ}

upload: ${PROG}.hex
	${AVRDUDE} ${AVRDUDEFLAGS} -U flash:w:$<

download:
	${AVRDUDE} ${AVRDUDEFLAGS} -U flash:r:flash_`date +%Y%m%d%H%M%S`.hex:i

cpp:
	${CC} ${CFLAGS} -E ${SRC}

version:
	${CC} -v

serial:
	miniterm.py $(PORT) $(COM_SPEED)

connect:
	# exit: ^a ^x
	picocom -b $(COM_SPEED) --omap crcrlf $(PORT)
