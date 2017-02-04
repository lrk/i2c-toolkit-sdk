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
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "RaspberryPi.h"

RPI_I2CInputOutput::RPI_I2CInputOutput(uint8_t i2cPort) :
	_i2cPort(i2cPort)
{

}

RPI_I2CInputOutput::~RPI_I2CInputOutput(){
	this->release();
}

int	RPI_I2CInputOutput::setup(uint8_t deviceAddress) {
	this->setDeviceAddress(deviceAddress);

	switch(this->_i2cPort)
	{
		case 0: this->_fileDescriptor = open(__I2C_TK_SDK_I2CIO_RPI_PORT0,O_RDWR); 
				break;
		case 1: this->_fileDescriptor = open(__I2C_TK_SDK_I2CIO_RPI_PORT1,O_RDWR); 
				break;
		default: 
			//No other port available
		break;
	}

	if (this->_fileDescriptor < 0)
	{
		perror("open: ");
	} else {
		fprintf(stdout,"Filedescriptor: %d\n",this->_fileDescriptor);
	}

	
	int r = ioctl(this->_fileDescriptor, I2C_SLAVE, this->getDeviceAddress());
	if ( r < 0)
	{
		perror("ioctl: ");
	} else {
		fprintf(stdout,"ioctl result: %d\n", r);
	}

	return I2CIO_ERROR_OK;
}

int RPI_I2CInputOutput::release(){
	close(this->_fileDescriptor);
	return I2CIO_ERROR_OK;
}

int RPI_I2CInputOutput::read(uint8_t *buffer,uint32_t len){	
	int count = ::read(this->_fileDescriptor,buffer,sizeof(uint8_t)*len);	
	return count;
}

int RPI_I2CInputOutput::write(uint8_t *data, uint32_t len){
	int count = ::write(this->_fileDescriptor,data,sizeof(uint8_t)*len);
	return count;
}