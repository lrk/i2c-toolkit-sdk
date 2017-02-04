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
#include <unistd.h>

#ifndef __I2C_TK_SDK_I2CIO_H__
#define __I2C_TK_SDK_I2CIO_H__

#define I2CIO_ERROR_OK			0
#define I2CIO_ERROR_ERROR		-1

#define I2CIO_WAIT_TIME			2000 //wait time for response in µSec.

class I2CInputOutput {
private:
	uint8_t _deviceAddress;
protected:

public:
	I2CInputOutput();
	virtual ~I2CInputOutput();
	
	void setDeviceAddress(uint8_t deviceAddress);
	uint8_t getDeviceAddress();
	
	virtual int	setup(uint8_t deviceAddress) = 0; //Initialize I²C communications
	virtual int release() = 0; //Release I²C communications
	
	virtual int read(uint8_t *buffer,uint32_t len) = 0; //Read data from I²C
	virtual int write(uint8_t *data, uint32_t len) = 0; //write data to I²C
	void waitForResponse();
};
#endif //__I2C_TK_SDK_I2CIO_H__