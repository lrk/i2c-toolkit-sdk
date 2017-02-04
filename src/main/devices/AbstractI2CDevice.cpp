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

#include "AbstractI2CDevice.h"

AbstractI2CDevice::AbstractI2CDevice(uint8_t address, I2CInputOutput *i2cIO)
	_deviceAddress(address)
{
	if (i2cIO == NULL)
	{
		//Fatal Error
	}
	this->_i2cIO = i2cIO;
}