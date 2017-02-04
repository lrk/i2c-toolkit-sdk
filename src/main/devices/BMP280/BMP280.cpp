/*
 * Copyright 2017 Cengis KOCAURLU
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "BMP280.h"

BMP280::BMP280(uint8_t address, I2CInputOutput *i2cIO) : I2CDevice(address,i2cIO)
{
}

BMP280::~BMP280(){

}

int BMP280::initialize(){
	I2CDevice::initialize();
	//Read chip id
	this->_chipId = this->readChipId();
	return 0;
}


uint8_t BMP280::readChipId()
{
	uint8_t buffer[1] = {__BMP280_REGISTER_CHIP_ID};
	I2CDevice::write(buffer,1);
	I2CDevice::waitForResponse();
	I2CDevice::read(buffer,1);
	return buffer[0];
}

BMP280_VALUES BMP280::read()
{
	BMP280_VALUES values;

	return values;
}