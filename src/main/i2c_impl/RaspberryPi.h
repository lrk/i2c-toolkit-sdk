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

/*
	I²C communication implementation of I2C Input Output for Raspberry PI
*/
#ifndef __I2C_TK_SDK_I2CIO_RPI_H__
#define __I2C_TK_SDK_I2CIO_RPI_H__

#include "I2CInputOutput.h"

 
#ifndef __I2C_TK_SDK_I2CIO_RPI_PORTS__

#define __I2C_TK_SDK_I2CIO_RPI_PORT0	"/dev/i2c-0"
#define __I2C_TK_SDK_I2CIO_RPI_PORT1 	"/dev/i2c-1"

#endif //__I2C_TK_SDK_I2CIO_RPI_PORTS__


class RPI_I2CInputOutput : public I2CInputOutput {
private:
	uint8_t	_i2cPort;
	int _fileDescriptor;
protected:
public:
	RPI_I2CInputOutput(uint8_t i2cPort);
	virtual ~RPI_I2CInputOutput();
	
	virtual int	setup(uint8_t deviceAddress); //Initialize I²C communications
	virtual int release(); //Release I²C communications
	
	virtual int read(uint8_t *buffer,uint32_t len); //Read data from I²C
	virtual int write(uint8_t *data, uint32_t len); //write data to I²C
};
#endif //__I2C_TK_SDK_I2CIO_RPI_H__