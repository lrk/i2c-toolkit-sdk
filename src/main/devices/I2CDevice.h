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
#include <stdint.h>

#ifndef __I2C_TK_SDK_ABSTRACT_DEVICE_H__
#define __I2C_TK_SDK_ABSTRACT_DEVICE_H__

#include "../i2c_impl/I2CInputOutput.h"

/*
	Abstract I²C Device
*/
class I2CDevice {
private:
	uint8_t	_deviceAddress;	//unsigned short for device I²C Address
	I2CInputOutput *_i2cIO; //Underlaying I2CInputOutput instance
	void setup();
protected:
	int read(uint8_t *buffer,uint32_t len); //Read data from underlaying I²C IO instance
	int write(uint8_t *data, uint32_t len); //write data to underlaying I²C IO instance

public:
	I2CDevice(uint8_t address, I2CInputOutput *i2cIO);
	virtual ~I2CDevice(){};
	void waitForResponse(){ this->_i2cIO->waitForResponse(); };

	virtual int initialize(); //Send initialization commands to device

	
};

#endif //__I2C_TK_SDK_ABSTRACT_DEVICE_H__