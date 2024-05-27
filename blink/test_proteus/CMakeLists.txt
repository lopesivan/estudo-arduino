cmake_minimum_required(VERSION 3.5)

project(pull_up)

set(CMAKE_C_STANDARD 99)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(ARDUINO_DIR "/opt/arduino-1.8.1")
set(TOOLCHAIN "${ARDUINO_DIR}/hardware/tools/avr/bin")
set(AVRDUDECONF "/etc/avrdude.conf")

###########
# TOOLCHAIN
###########

set(ARDUINOOTA     "${TOOLCHAIN}/arduinoOTA")
set(AVRDUDE        "${TOOLCHAIN}/avrdude")
set(AVR_ADDR2LINE  "${TOOLCHAIN}/avr-addr2line")
set(AVR_AR         "${TOOLCHAIN}/avr-ar")
set(AVR_AS         "${TOOLCHAIN}/avr-as")
set(AVR_Cpp        "${TOOLCHAIN}/avr-c++")
set(AVR_CppFILT    "${TOOLCHAIN}/avr-c++filt")
set(AVR_CPP        "${TOOLCHAIN}/avr-cpp")
set(AVR_ELFEDIT    "${TOOLCHAIN}/avr-elfedit")
set(AVR_Gpp        "${TOOLCHAIN}/avr-g++")
set(AVR_GCC        "${TOOLCHAIN}/avr-gcc")
set(AVR_GCC_4_9_2  "${TOOLCHAIN}/avr-gcc-4.9.2")
set(AVR_GCC_AR     "${TOOLCHAIN}/avr-gcc-ar")
set(AVR_GCC_NM     "${TOOLCHAIN}/avr-gcc-nm")
set(AVR_GCCr_RANLIB "${TOOLCHAIN}/avr-gcc-ranlib")
set(AVR_GCOV       "${TOOLCHAIN}/avr-gcov")
set(AVR_GDB        "${TOOLCHAIN}/avr-gdb")
set(AVR_GPROF      "${TOOLCHAIN}/avr-gprof")
set(AVR_LD         "${TOOLCHAIN}/avr-ld")
set(AVR_LD_BFD     "${TOOLCHAIN}/avr-ld.bfd")
set(AVR_MAN        "${TOOLCHAIN}/avr-man")
set(AVR_NM         "${TOOLCHAIN}/avr-nm")
set(AVR_OBJCOPY    "${TOOLCHAIN}/avr-objcopy")
set(AVR_OBJDUMP    "${TOOLCHAIN}/avr-objdump")
set(AVR_RANLIB     "${TOOLCHAIN}/avr-ranlib")
set(AVR_READELF    "${TOOLCHAIN}/avr-readelf")
set(AVR_RUN        "${TOOLCHAIN}/avr-run")
set(AVR_SIZE       "${TOOLCHAIN}/avr-size")
set(AVR_STRINGS    "${TOOLCHAIN}/avr-strings")
set(AVR_STRIP      "${TOOLCHAIN}/avr-strip")
set(LIBUSB_CONFIG  "${TOOLCHAIN}/libusb-config")

set(CMAKE_C_COMPILER   "${TOOLCHAIN}/avr-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN}/avr-g++")

set(MCU "atmega328p")
set(F_CPU "16000000UL")
set(PORT "/dev/ttyUSB0")
set(BAUD "115200")
set(PROTOCOL "arduino")
set(PART "ATMEGA328P")

set(WFLAGS "-Wall -Wextra")

set(CMAKE_C_FLAGS      "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os ${WFLAGS} -ffunction-sections -fdata-sections -fno-exceptions -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "-mmcu=${MCU} -Wl,--gc-section")

FILE(GLOB MyCSources *.c)
FILE(GLOB MyCHeaders *.h)
set(SOURCE_FILES ${MyCSources} ${MyCHeaders})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${AVR_OBJCOPY} -O ihex -R.eeprom
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${AVR_OBJCOPY} -O ihex -j .eeprom
            --set-section-flags=.eeprom="alloc,load"
            --change-section-lma .eeprom=0
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${AVR_SIZE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
            --mcu=${MCU}
            --format=avr)

ADD_CUSTOM_TARGET( upload
  COMMAND ${AVRDUDE}
          -C ${AVRDUDECONF}
          -F -V -c ${PROTOCOL} -p ${PART} -P ${PORT} -b ${BAUD}
          -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)

ADD_CUSTOM_TARGET( download
  COMMAND ${AVRDUDE}
          -C ${AVRDUDECONF}
          -F -V -c ${PROTOCOL} -p ${PART} -P ${PORT} -b ${BAUD}
          -U flash:r:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/flash_`date +%Y%m%d%H%M%S`.hex:i)
