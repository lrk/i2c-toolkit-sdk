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

#include "I2CDevice.h"

I2CDevice::I2CDevice(uint8_t address, I2CInputOutput *i2cIO) :
	_deviceAddress(address)
{
	if (i2cIO == 0)
	{
		//Fatal Error
	}
	this->_i2cIO = i2cIO;
}
int I2CDevice::initialize()
{
	this->setup();
	return 0;
}

void I2CDevice::setup()
{
	if (this->_i2cIO != 0)
	{
		this->_i2cIO->setup(_deviceAddress);
	}
}

int I2CDevice::read(uint8_t *buffer, uint32_t len){
	if (this->_i2cIO == 0)
	{
		return I2CIO_ERROR_ERROR;
	}

	return this->_i2cIO->read(buffer,len);
}

int I2CDevice::write(uint8_t *data, uint32_t len){
	if (this->_i2cIO == 0)
	{
		return I2CIO_ERROR_ERROR;
	}

	return this->_i2cIO->write(data,len);
}