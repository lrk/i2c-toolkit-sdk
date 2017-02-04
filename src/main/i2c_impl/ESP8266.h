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
	I²C communication implementation of I2C Input Output for ESP8266
*/
#ifndef __I2C_TK_SDK_I2CIO_ESP3266_H__
#define __I2C_TK_SDK_I2CIO_ESP3266_H__

#include "I2CInputOutput.h"

class ESP8266_I2CInputOutput : public I2CInputOutput {
private:
protected:
public:
	ESP8266_I2CInputOutput(){ };
	virtual ~ESP8266_I2CInputOutput(){};
	virtual int setup(uint8_t deviceAddress){ this->setDeviceAddress(deviceAddress); return 0;}; //TODO Implementation
	virtual int release(){return 0;}; //TODO Implementation
	virtual int read(uint8_t *buffer,uint32_t len){ return 0;}; //TODO Implementation
	virtual int int write(uint8_t *data, uint32_t len){return 0;}; //TODO Implementation
};
#endif //__I2C_TK_SDK_I2CIO_ESP3266_H__