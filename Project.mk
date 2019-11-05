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

SOURCE_FOLDERS 			= lib src/hardware src/adapter src/hardware/timers hid
3RD_PARTY_LIBS			= HID-Project
ARDUINO_LIBS			= SoftwareSerial \
						  HID

# defining hardware
ALTERNATE_CORE			= adafruit
ALTERNATE_CORE_PATH		= $(ARDUINO_DIR)/hardware/adafruit/avr
BOARD_TAG				= itsybitsy32u4_5V
MONITOR_PORT			= /dev/ttyACM0

# locate directories relative Project.mk
ROOT_DIR				:= $(dir $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR				= $(shell basename $(CURDIR))
BUILD_DIR				= $(ROOT_DIR)build
OBJDIR					= $(BUILD_DIR)

CFLAGS_STD				= -std=gnu11
CPPFLAGS_STD			= -std=gnu++17
CPPFLAGS				+= -I $(ROOT_DIR)lib/stubs
CPPFLAGS				+= -pedantic -Wall -Wextra
CPPFLAGS				+= $(CPPFLAGS_STD)
LDFLAGS					+= -fdiagnostics-color

# these need to be evaluated before including Arduino.mk or stuff will break
_ := $(shell arduino-cli lib update-index)
_ := $(foreach lib, $(3RD_PARTY_LIBS), $(shell arduino-cli lib install $(lib)))

# check out the Arduino-Makefile RPM from my config github repo at
# https://github.com/simonwendel/configs/tree/master/Packages
ARDUINO_LIBS			+= $(3RD_PARTY_LIBS)
USER_LIB_PATH			+= $(wildcard ~)/Arduino/libraries
include /usr/share/arduino/Arduino.mk

# hack to make sure HID-Project.h doesn't throw. should probably match
# the version of your actual Arduino SDK install
CFLAGS					+= -DARDUINO=10805 # v1.8.5
CPPFLAGS				+= -DARDUINO=10805 # v1.8.5
CPPFLAGS				+= -DUSBCON

# hack for us to be able to stub out Arduino.h if needed for testing
# here we unstub it
CPPFLAGS				+= -USTUB_ARDUINO

# hacks to compile C++ files in some tree structure, instead of 
# all files directly in src/
define find_cpp_files
	$(shell find $(1) -maxdepth 1 -type f -name '*.cpp')
endef

SRCS					= $(foreach dir, $(SOURCE_FOLDERS), $(call find_cpp_files, $(ROOT_DIR)$(dir)))
LOCAL_CPP_SRCS  		+= $(subst $(ROOT_DIR),,$(SRCS))

# and make rules!
$(OBJDIR)/$(TARGET).elf: $(LOCAL_OBJ_FILES)

$(LOCAL_OBJ_FILES): $(LOCAL_CPP_SRCS)

$(LOCAL_CPP_SRCS):
	@$(MKDIR) -p $(OBJDIR)/$(dir $@)
	$(CXX) -MMD -c $(CPPFLAGS) $(ROOT_DIR)$@ -o $(OBJDIR)/$@.o

clean::
	$(shell rm -rf $(BUILD_DIR) &>/dev/null)
