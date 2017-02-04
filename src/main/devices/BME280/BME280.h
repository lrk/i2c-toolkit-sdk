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

#ifndef __I2C_TK_SDK_BME280_H__
#define __I2C_TK_SDK_BME280_H__

//Valid chip ID
#define __BME280_CHIP_ID	0x60

//Calibration registers for temperature
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T1_LSB		0x88
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T1_MSB		0x89
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T2_LSB		0x8A
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T2_MSB		0x8B
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T3_LSB		0x8C
#define __BME280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T3_MSB		0x8D
//Calibration registers for pressure
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P1_LSB			0x8E
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P1_MSB			0x8F
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P2_LSB			0x90
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P2_MSB			0x91
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P3_LSB			0x92
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P3_MSB			0x93
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P4_LSB			0x94
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P4_MSB			0x95
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P5_LSB			0x96
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P5_MSB			0x97
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P6_LSB			0x98
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P6_MSB			0x99
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P7_LSB			0x9A
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P7_MSB			0x9B
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P8_LSB			0x9C
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P8_MSB			0x9D
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P9_LSB			0x9E
#define __BME280_REGISTER_CALIBRATION_DIG_PRESSURE_P9_MSB			0x9F
//Calibration registers for humidity
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H1_LSB			0xA1
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H2_LSB			0xE1
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H2_MSB			0xE2
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H3_LSB			0xE3
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H4_MSB			0xE4
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H4_LSB			0xE5
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H5_LSB			0xE5
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H5_MSB			0xE6
#define __BME280_REGISTER_CALIBRATION_DIG_HUMITIDY_H6_LSB			0xE7


//Command registers
#define __BME280_REGISTER_CHIP_ID					0xD0
#define __BME280_REGISTER_RESET						0xE0
#define __BME280_REGISTER_STATUS					0xF3
#define __BME280_REGISTER_CTRL_MEASURE				0xF4
#define __BME280_REGISTER_CONFIG					0xF5
#define __BME280_REGISTER_PRESSURE_MSB				0xF7
#define __BME280_REGISTER_PRESSURE_LSB				0xF8
#define __BME280_REGISTER_PRESSURE_XLSB				0xF9
#define __BME280_REGISTER_TEMPERATURE_MSB			0xFA
#define __BME280_REGISTER_TEMPERATURE_LSB			0xFB
#define __BME280_REGISTER_TEMPERATURE_XLSB			0xFC

//Operating Modes
#define __BME280_OPERATING_MODE_SLEEP
#define __BME280_OPERATING_MODE_NORMAL
#define __BME280_OPERATING_MODE_FORCED

typedef struct __BME280_CALIBRATION {
	uint16_t 	digT1;
	int16_t 	digT2;
	int16_t 	digT3;

	uint16_t 	digP1;
	int16_t 	digP2;
	int16_t 	digP3;
	int16_t 	digP4;
	int16_t 	digP5;
	int16_t 	digP6;
	int16_t 	digP7;
	int16_t 	digP8;
	int16_t 	digP9;

	uint16_t 	digH1;
	int16_t 	digH2;
	uint16_t 	digH3;
	int16_t 	digH4;
	int16_t 	digH5;
	int16_t 	digH6;
	

} BME280_CALIBRATION, *PBME280_CALIBRATION;


class BME280: public I2CDevice {
private:
	uint8_t	_chipId;
	uint8_t _operatingMode;
	BME280_CALIBRATION _calibration;

protected:
public:
	BME280(uint8_t address, I2CInputOutput *i2cIO);
	virtual ~BME280();
	int initialize();
};

#endif // __I2C_TK_SDK_BME280_H__
