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

#ifndef __I2C_TK_SDK_BMP280_H__
#define __I2C_TK_SDK_BMP280_H__

//Valid chip ID
#define __BMP280_CHIP_ID1	0x56
#define __BMP280_CHIP_ID2	0x57
#define __BMP280_CHIP_ID3	0x58

//Calibration registers for temperature
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T1_LSB		0x88
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T1_MSB		0x89
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T2_LSB		0x8A
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T2_MSB		0x8B
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T3_LSB		0x8C
#define __BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T3_MSB		0x8D
//Calibration registers for pressure
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P1_LSB			0x8E
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P1_MSB			0x8F
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P2_LSB			0x90
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P2_MSB			0x91
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P3_LSB			0x92
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P3_MSB			0x93
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P4_LSB			0x94
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P4_MSB			0x95
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P5_LSB			0x96
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P5_MSB			0x97
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P6_LSB			0x98
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P6_MSB			0x99
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P7_LSB			0x9A
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P7_MSB			0x9B
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P8_LSB			0x9C
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P8_MSB			0x9D
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P9_LSB			0x9E
#define __BMP280_REGISTER_CALIBRATION_DIG_PRESSURE_P9_MSB			0x9F


//Command registers
#define __BMP280_REGISTER_CHIP_ID					0xD0
#define __BMP280_REGISTER_RESET						0xE0
#define __BMP280_REGISTER_STATUS					0xF3
#define __BMP280_REGISTER_CTRL_MEASURE				0xF4
#define __BMP280_REGISTER_CONFIG					0xF5
#define __BMP280_REGISTER_PRESSURE_MSB				0xF7
#define __BMP280_REGISTER_PRESSURE_LSB				0xF8
#define __BMP280_REGISTER_PRESSURE_XLSB				0xF9
#define __BMP280_REGISTER_TEMPERATURE_MSB			0xFA
#define __BMP280_REGISTER_TEMPERATURE_LSB			0xFB
#define __BMP280_REGISTER_TEMPERATURE_XLSB			0xFC

typedef struct __BMP280_CALIBRATION {
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

} BMP280_CALIBRATION, *PBMP280_CALIBRATION;


class BMP280: public I2CDevice {
private:
	uint8_t	chipId;
	BMP280_CALIBRATION _calibration;

	void init();
protected:
public:
	BMP280(uint8_t address, I2CInputOutput *i2cIO);
	~BMP280();
};

#endif // __I2C_TK_SDK_BMP280_H__
