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
#include <stdio.h>
#include "../I2CDevice.h"

#ifndef __I2C_TK_SDK_I2CIO_SSD1306_H__

#define __I2C_TK_SDK_I2CIO_SSD1306_H__

//Commands
#define __SSD1306_CMD_SET_CONTRAST 					0x81
#define __SSD1306_CMD_ENTIRE_DISPLAY_ON 			0xA4
#define __SSD1306_CMD_DISPLAY_INVERT_NORMAL 		0xA6
#define __SSD1306_CMD_DISPLAY_ON 					0xAE
#define __SSD1306_CMD_SET_MULTIPLEX_RATIO 			0xA8
#define __SSD1306_CMD_SET_DISPLAY_OFFSET 			0xD3
#define __SSD1306_CMD_SET_DISPLAY_START_LINE 		0x40
#define __SSD1306_CMD_SET_SEGMENT_REMAP 			0xA0
#define __SSD1306_CMD_SET_COM_OUT_SCAN_DIR 			0xC0
#define __SSD1306_CMD_SET_COM_PIN_HW_CONFIG 		0xDA
#define __SSD1306_CMD_SET_OSCILLATOR_FREQ			0xD5
#define __SSD1306_CMD_SET_PRE_CHARGE_PERIOD			0xD9
#define __SSD1306_CMD_SET_VCOMH_DESELECT_LVL		0xDB
#define __SSD1306_CMD_NOP							0xE3
#define __SSD1306_CMD_CHARGE_PUMP_SETTING			0x8D
#define __SSD1306_CMD_SET_MEMORY_ADDRESSING_MODE	0x20

#define __SSD1306_RESET_MULTIPLEX_RATIO 		0x3F
#define __SSD1306_DEFAULT_CONTRAST 				0x7F
#define __SSD1306_DEFAULT_DIVID_RATIO	  		0x00
#define __SSD1306_DEFAULT_OSCILLATOR_FREQ  		0x08
#define __SSD1306_RESET_PRECHARGE_PHASE1		0x02
#define __SSD1306_RESET_PRECHARGE_PHASE2		0x02
#define __SSD1306_RESET_VCOMH_DESELECT_LEVEL	0x02
#define __SSD1306_HORIZONTAL_ADDRESSING_MODE	0x00
#define __SSD1306_VERTICAL_ADDRESSING_MODE		0x01
#define __SSD1306_PAGE_ADDRESSING_MODE			0x10

#define __SSD1306_CMD_BUFFER_MAXSIZE			2048

class SSD1306: public I2CDevice {

private:
	int _fileDescriptor;
	uint8_t	_i2cPort;
	uint8_t	_slaveAddress;
	bool	_isCommandMode;
	void init();

	uint8_t _commandBuffer[__SSD1306_CMD_BUFFER_MAXSIZE];
	uint32_t _commandBufferLen;
	bool	_bufferMode;
	void flushBuffer();
	void resetCommandBuffer();

	void setBufferMode(bool bufferEnabled);
public:
	SSD1306(uint32_t i2cPort, uint8_t address);
	~SSD1306();

	void send(uint8_t *data, uint32_t len);

	void boot();
	void displayOn(bool enabled);
	void setContrast(double percentage);
	void resetContrast();
	void entireDisplayOn(bool ignoreRam);
	void invertDisplay(bool invert);
	void setMultiplexRatio(uint8_t ratio); //limit available display lines end
	inline void resetMultiplexRatio(){this->setMultiplexRatio(__SSD1306_RESET_MULTIPLEX_RATIO);};
	void setDisplayOffset(uint8_t offset);
	void setDisplayStartLine(uint8_t value);
	void setSegmentRemap(bool invert);
	void setCOMOutputScanDirection(bool remappedMode); //Flip vertically
	void setCOMPinsHWConfiguration(bool alternativeComConfig, bool enableCOMLeftRightRemap);
	void setOscillatorFrequency(uint8_t divideRatio, uint8_t frequency);
	inline void resetOscillatorFrequency(){this->setOscillatorFrequency(__SSD1306_DEFAULT_DIVID_RATIO,__SSD1306_DEFAULT_OSCILLATOR_FREQ);};
	void setPrechargePeriod(uint8_t phase1, uint8_t phase2);
	void chargePumpOn(bool enabled);
	void setVComhDeselectLevel(uint8_t level);

	inline void setCommandMode(){this->_isCommandMode = true;}
	inline void setDataMode(){this->_isCommandMode = false;}

	void setMemoryAddressingMode(uint8_t mode);
};

#endif //__I2C_TK_SDK_I2CIO_SSD1306_H__