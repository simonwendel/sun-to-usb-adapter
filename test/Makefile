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

GOOGLE_TEST_LIB		= gtest
GOOGLE_MOCK_LIB		= gmock
GOOGLE_TEST_INCLUDE	= /usr/include

CXX					= g++

CXX_FLAGS			= -c -I $(GOOGLE_TEST_INCLUDE) -I ../lib/stubs
CXX_FLAGS			+= -pedantic -Wall -Wextra -std=gnu++1z

CXX_FLAGS			+= -DSTUB_ARDUINO

LD_FLAGS			= -L /usr/local/lib 
LD_FLAGS			+= -l $(GOOGLE_TEST_LIB) 
LD_FLAGS			+= -l $(GOOGLE_MOCK_LIB) 
LD_FLAGS			+= -l pthread

BUILD_DIR			= ../build
OBJDIR				= $(BUILD_DIR)/test

define find_cpp_files
	$(shell find $(1) -type f -name '*.cpp')
endef

SOURCE_FOLDERS 		= ../lib/ ../src/ ./

SRCS			= $(foreach dir, $(SOURCE_FOLDERS), $(call find_cpp_files, $(dir)))
OBJECTS			= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET				= $(OBJDIR)/test_runner.bin

all: ensure-dir $(TARGET)

ensure-dir:	$(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

$(OBJDIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $< -o $@

clean:
	$(shell rm -rf $(BUILD_DIR))

.PHONY: all clean
