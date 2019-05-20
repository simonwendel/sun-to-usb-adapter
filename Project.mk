# Sun to USB keyboard adapter
# Copyright (C) 2019  Simon Wendel
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

ARDUINO_LIBS			= SoftwareSerial \
						  HID \
						  HID-Project

ALTERNATE_CORE			= adafruit
ALTERNATE_CORE_PATH		= $(ARDUINO_DIR)/hardware/adafruit/avr

BOARD_TAG				= itsybitsy32u4_5V
MONITOR_PORT			= /dev/ttyACM0

# this should be the dir of this Project.mk file
SELF_DIR				:= $(dir $(lastword $(MAKEFILE_LIST)))
BUILD_DIR				= $(SELF_DIR)build

CURRENT_DIR				= $(shell basename $(CURDIR))
OBJDIR					= $(BUILD_DIR)/$(CURRENT_DIR)

CFLAGS_STD				= -std=gnu11
CXXFLAGS_STD			= -std=gnu++17
CXXFLAGS				+= -I $(SELF_DIR)/lib
CXXFLAGS				+= -pedantic -Wall -Wextra
LDFLAGS					+= -fdiagnostics-color

# hack to make sure HID-Project.h doesn't throw. should probably match
# the version of your actual Arduino SDK install
CXXFLAGS				+= -DARDUINO=10805 # v1.8.5

# check out the Arduino-Makefile RPM from my config github repo at
# https://github.com/simonwendel/configs/tree/master/Packages
include /usr/share/arduino/Arduino.mk

clean::
	$(info Removing $(BUILD_DIR) if empty...)
	$(shell rmdir $(BUILD_DIR) &>/dev/null)
