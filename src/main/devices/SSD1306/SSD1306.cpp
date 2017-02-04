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
#include "SSD1306.h"

SSD1306::SSD1306(uint8_t address, I2CInputOutput *i2cIO) : I2CDevice(address,i2cIO)
	
{
	this->_bufferMode=false;
	this->_isCommandMode = true;
	this->resetCommandBuffer();

	this->init();
}

SSD1306::~SSD1306(){
	this->displayOn(false);
}

void SSD1306::resetCommandBuffer()
{
	fprintf(stdout,"Reseting command buffer...\n");
	memset(this->_commandBuffer,0,sizeof(uint8_t)*__SSD1306_CMD_BUFFER_MAXSIZE);
	this->_commandBufferLen = 0;
}

void SSD1306::setBufferMode(bool bufferEnabled){
	if ((!bufferEnabled) && (this->_bufferMode))
	{
		this->flushBuffer();
	}
	this->_bufferMode = bufferEnabled;
 }

void SSD1306::flushBuffer(){
	fprintf(stdout,"Flushing command buffer...\n");
	bool bmode = this->_bufferMode;
	this->_bufferMode = false;
	this->send(this->_commandBuffer,this->_commandBufferLen);
	this->resetCommandBuffer();
	this->_bufferMode = bmode;
}

void SSD1306::send(uint8_t *data, uint32_t len)
{
	if (this->_bufferMode){
		fprintf(stdout,"Adding data to command buffer...\n");
		for(int i=0;i<len;i++){
			fprintf(stdout, "0x%02x ",data[i]);
		}
		fprintf(stdout, "\n");

		memcpy(&this->_commandBuffer[this->_commandBufferLen],data,sizeof(uint8_t)*len);
		this->_commandBufferLen += len;

	}else{
		fprintf(stdout,"Sending %s: \n",this->_isCommandMode?"command":"data");

		int plen = len+1;
		uint8_t packet[plen];
		memset(packet,0,sizeof(uint8_t)*plen);
		memcpy(&packet[1],data,sizeof(uint8_t)*len);
		packet[0] = (this->_isCommandMode)?0x00:0x40;

		for(int i=0;i<plen;i++){
			fprintf(stdout, "0x%02x ",packet[i]);
		}
		fprintf(stdout, "\n");


		if (this->write(packet,sizeof(uint8_t)*plen) != plen){
			perror("write: ");
		}
	}
}

void SSD1306::resetContrast()
{
	uint8_t data[] = {__SSD1306_CMD_SET_CONTRAST,__SSD1306_DEFAULT_CONTRAST};
	this->send(data,2);
}

void SSD1306::setContrast(double percentage)
{
	uint8_t contrast = (uint8_t)(percentage * 255.0);
	uint8_t data[] = {__SSD1306_CMD_SET_CONTRAST,contrast};
	this->send(data,2);
}

void SSD1306::entireDisplayOn(bool ignoreRam)
{
	uint8_t data[]={__SSD1306_CMD_ENTIRE_DISPLAY_ON | ignoreRam};
	this->send(data,1);
};

void SSD1306::displayOn(bool enabled)
{
	uint8_t data[] = {__SSD1306_CMD_DISPLAY_ON | enabled};
	this->send(data,1);
}

void SSD1306::invertDisplay(bool invert)
{
	
	uint8_t data[] = {__SSD1306_CMD_DISPLAY_INVERT_NORMAL | invert};
	this->send(data,1);
}

void SSD1306::setMultiplexRatio(uint8_t ratio)
{
	uint8_t data[] = {__SSD1306_CMD_SET_MULTIPLEX_RATIO, ratio & 0x3F};
	this->send(data,2);	
}

void SSD1306::setDisplayOffset(uint8_t offset)
{
	uint8_t data[] = {__SSD1306_CMD_SET_DISPLAY_OFFSET, offset & 0x3F};
	this->send(data,2);	
}

void SSD1306::setDisplayStartLine(uint8_t value)
{
	uint8_t data[] = {__SSD1306_CMD_SET_DISPLAY_START_LINE | (value & 0x3F)};
	this->send(data,1);	
}

void SSD1306::setSegmentRemap(bool invert)
{
	uint8_t data[] = {__SSD1306_CMD_SET_SEGMENT_REMAP | invert};
	this->send(data,1);	
}

void SSD1306::setCOMOutputScanDirection(bool remappedMode)
{
	uint8_t data[] = {__SSD1306_CMD_SET_COM_OUT_SCAN_DIR | (((uint8_t)remappedMode)<< 3 )};
	this->send(data,1);	
}

void SSD1306::setCOMPinsHWConfiguration(bool alternativeComConfig, bool enableCOMLeftRightRemap)
{
	uint8_t alternative = ((uint8_t)alternativeComConfig) << 4;
	uint8_t leftRightRemap = ((uint8_t)enableCOMLeftRightRemap) << 5;
	uint8_t value = 0x02 | alternative | leftRightRemap;

	uint8_t data[] = {__SSD1306_CMD_SET_COM_PIN_HW_CONFIG, value};
	this->send(data,2);	
}

void SSD1306::setOscillatorFrequency(uint8_t divideRatio, uint8_t frequency)
{
	uint8_t value = ((frequency & 0x0F)<<4) | (divideRatio & 0x0F);
	uint8_t data[] = {__SSD1306_CMD_SET_OSCILLATOR_FREQ, value};
	this->send(data,2);	
}

void SSD1306::setPrechargePeriod(uint8_t phase1, uint8_t phase2)
{
	//0 is an invalid value for phase1 and phase2 => set to RESET value
	if (phase1 == 0) { phase1 = __SSD1306_RESET_PRECHARGE_PHASE1;}
	if (phase2 == 0) { phase2 = __SSD1306_RESET_PRECHARGE_PHASE2;}

	uint8_t value = ((phase2 & 0x0F)<<4) | (phase1 & 0x0F);
	uint8_t data[] = {__SSD1306_CMD_SET_PRE_CHARGE_PERIOD, value};
	this->send(data,2);	
}

void SSD1306::setVComhDeselectLevel(uint8_t level)
{
	uint8_t value = (level & 0x03) << 4;
	uint8_t data[] = {__SSD1306_CMD_SET_VCOMH_DESELECT_LVL, value};
	this->send(data,2);	
}

void SSD1306::chargePumpOn(bool enabled)
{
	uint8_t value = 0x10 | (((uint8_t) enabled) << 2);
	uint8_t data[] = {__SSD1306_CMD_CHARGE_PUMP_SETTING, value};
	this->send(data,2);	
}

void SSD1306::setMemoryAddressingMode(uint8_t mode){
	uint8_t data[] = {__SSD1306_CMD_SET_MEMORY_ADDRESSING_MODE, mode};
	this->send(data,2);	
}

void  SSD1306::boot()
{
	fprintf(stdout,"Booting SSD1306\n");
	
	this->setBufferMode(true);
	
	//Initialzation sequence
	
	this->displayOn(false);

	//Set Display Offset D3h, 00h
	this->setDisplayOffset(0);

	//Set Display Start Line 40h
	this->setDisplayStartLine(0);
	//Enable charge pump regulator 8Dh, 14h
	this->chargePumpOn(true);

	//Set MUX Ratio A8h, 3Fh
	this->resetMultiplexRatio();

	//Set Segment re-map A0h/A1h
	this->setSegmentRemap(false);

	//Set COM Output Scan Direction C0h/C8h
	this->setCOMOutputScanDirection(false);

	//Set COM Pins hardware configuration DAh, 02
	this->setCOMPinsHWConfiguration(false,false);

	//Set Contrast Control 81h, 7Fh
	this->resetContrast();

	//Set Osc Frequency D5h, 80h
	this->resetOscillatorFrequency();

	this->setPrechargePeriod(0x01,0x0F);
	this->setVComhDeselectLevel(2);

	this->setMemoryAddressingMode(__SSD1306_HORIZONTAL_ADDRESSING_MODE);

	//Set Normal Display A6h
	this->invertDisplay(false);

	//Disable Entire Display On A4h
	this->entireDisplayOn(false);

	//Display On AFh
	this->displayOn(true);

	this->setBufferMode(false);
	this->flushBuffer();
	
}