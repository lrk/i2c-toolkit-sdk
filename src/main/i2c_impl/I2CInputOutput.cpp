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

#include "I2CInputOutput.h"

I2CInputOutput::I2CInputOutput() :
	_deviceAddress(0) 
{

}

I2CInputOutput::~I2CInputOutput() {
}

void I2CInputOutput::setDeviceAddress(uint8_t deviceAddress) {
	this->_deviceAddress = deviceAddress;
}

uint8_t I2CInputOutput::getDeviceAddress() {
	return this->_deviceAddress;
}

void I2CInputOutput::waitForResponse()
{
	usleep(I2CIO_WAIT_TIME);
}