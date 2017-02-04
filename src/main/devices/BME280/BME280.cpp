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
#include "BME280.h"

BME280::BME280(uint8_t address, I2CInputOutput *i2cIO) : 
	I2CDevice(address,i2cIO),
	_operatingMode(__BME280_OPERATING_MODE_SLEEP)
{

}

BME280::~BME280(){

}

int BME280::initialize(){
	I2CDevice::initialize();
	//Read chip id
	return 0;
}