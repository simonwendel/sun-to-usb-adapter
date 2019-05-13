ARDUINO_LIBS			= SoftwareSerial \
						  HID \
						  HID-Project

ALTERNATE_CORE			= adafruit
ALTERNATE_CORE_PATH		= $(ARDUINO_DIR)/hardware/adafruit/avr

BOARD_TAG				= itsybitsy32u4_5V
MONITOR_PORT			= /dev/ttyACM0

CFLAGS_STD				= -std=gnu11
CXXFLAGS_STD			= -std=gnu++17
CXXFLAGS				+= -pedantic -Wall -Wextra
LDFLAGS					+= -fdiagnostics-color

# hack to make sure HID-Project.h doesn't throw. should probably match
# the version of your actual Arduino SDK install
CXXFLAGS				+= -DARDUINO=10805 # v1.8.5

# this should be the dir of this Project.mk file
SELF_DIR				:= $(dir $(lastword $(MAKEFILE_LIST)))

CURRENT_DIR				= $(shell basename $(CURDIR))
OBJDIR					= $(SELF_DIR)build/$(CURRENT_DIR)-$(BOARD_TAG)

# check out the rpm from my config github repo at
# https://github.com/simonwendel/configs/tree/master/Packages
include /usr/share/arduino/Arduino.mk
