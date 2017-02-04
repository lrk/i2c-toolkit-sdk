#
#Copyright 2017 Cengis KOCAURLU
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#

CC 		= g++
INCLUDE	= -I.
DEBUG	= 
CFLAGS	= $(DEBUG) -Wall

ifneq ($V,1)
Q ?= @
endif

SRC		= $(shell find . -name *.cpp )
HEADERS	= $(shell find . -name *.h )

OBJ	=	$(SRC:.cpp=.o)

.PHONY: all
all: $(OBJ)
	$(CC) -o testBMP280 src/main/devices/BMP280/BMP280.o \
						src/test/BMP280.o \
						src/main/devices/I2CDevice.o \
						src/main/i2c_impl/RaspberryPi.o \
						src/main/i2c_impl/I2CInputOutput.o

%.o: %.cpp
	echo [Compiling] $<
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r $(OBJ)

#.PHONY: tests
#tests:

.PHONY:
