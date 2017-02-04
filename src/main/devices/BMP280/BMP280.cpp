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
#include "BMP280.h"

BMP280::BMP280(uint8_t address, I2CInputOutput *i2cIO) : 
	I2CDevice(address,i2cIO),
	_fineTemperature(0)
{
}

BMP280::~BMP280(){

}

int BMP280::initialize(){
	I2CDevice::initialize();
	//Read chip id
	this->_chipId = this->readChipId();

	//Read calibration
	this->_calibration = this->readCalibration();

	return 0;
}

/*
 * Register 0xD0 “id”
 * The “id” register contains the chip identification number chip_id[7:0], which is 0x58. 
 * This number can be read as soon as the device finished the power-on-reset.
 */
uint8_t BMP280::readChipId()
{
	uint8_t buffer[1] = {__BMP280_REGISTER_CHIP_ID};
	I2CDevice::write(buffer,1);
	I2CDevice::waitForResponse();
	I2CDevice::read(buffer,1);
	return buffer[0];
}
/*
 * Register 0xE0 “reset”
 * The “reset” register contains the soft reset word reset[7:0]. If the value 0xB6 is written to the
 * register, the device is reset using the complete power-on-reset procedure. Writing other values
 * than 0xB6 has no effect. The readout value is always 0x00.
 */
void BMP280::reset(bool completeReset)
{
	uint8_t buffer[2] = {__BMP280_REGISTER_RESET, completeReset ? __BMP280_CONST_COMPLETE_RESET : 0x00};
	I2CDevice::write(buffer,2);
}

/*
 * Register 0xF3 “status”
 * The “status” register contains two bits which indicate the status of the device.
 *
 * Register 0xF3	Name 			Description
 * “status”
 * 
 * Bit 3 			measuring[0] 	Automatically set to ‘1’ whenever a conversion is running 
 * 									and back to ‘0’ when the results have been transferred 
 * 									to the data registers.
 * 								
 * Bit 0 			im_update[0] 	Automatically set to ‘1’ when the NVM data are being
 * 									copied to image registers and back to ‘0’ when the
 * 									copying is done. The data are copied at power-on-reset
 * 									and before every conversion.
 */
BMP280_STATUS BMP280::status()
{
	uint8_t buffer[1] = {__BMP280_REGISTER_STATUS};
	I2CDevice::write(buffer,1);
	I2CDevice::waitForResponse();
	I2CDevice::read(buffer,1);

	BMP280_STATUS status;
	status.measuring 	= (buffer[0] & 0x04) > 0;
	status.imUpdate 	= (buffer[0] & 0x01) > 0;
	return status;
}

/*
 * Register 0xF4 “ctrl_meas”
 * The “ctrl_meas” register sets the data acquisition options of the device.
 * Table 20: Register 0xF4 “ctrl_meas”
 * 
 * Register 0xF4		Name 			Description
 * “ctrl_meas”
 * Bit 7, 6, 5 			osrs_t[2:0] 	Controls oversampling of temperature data. See chapter 3.3.2 for details.
 * Bit 4, 3, 2 			osrs_p[2:0] 	Controls oversampling of pressure data. See chapter 3.3.1 for details.
 * Bit 1, 0 			mode[1:0] 		Controls the power mode of the device. See chapter 3.6 for details.
 */

void BMP280::controlMeasure(BMP280_OVERSAMPLING pressureOversampling, BMP280_OVERSAMPLING temperatureOversampling, BMP280_OPERATING_MODE operatingMode)
{
	uint8_t value = ((pressureOversampling & 0x07) << 5) | 
					((temperatureOversampling & 0x07) << 2) |
					(operatingMode & 0x03);

	uint8_t buffer[2] = {__BMP280_REGISTER_CTRL_MEASURE, value};
	I2CDevice::write(buffer,2);
}

/*
 * Register 0xF5 “config”
 * The “config” register sets the rate, filter and interface options of the device. Writes to the “config”
 * register in normal mode may be ignored. In sleep mode writes are not ignored.
 * 
 * Register 0xF5		Name 				Description
 * “config”
 * Bit 7, 6, 5 			t_sb[2:0] 			Controls inactive duration tstandby in normal mode. See chapter 3.6.3 for details.
 * Bit 4, 3, 2 			filter[2:0] 		Controls the time constant of the IIR filter. See chapter 3.3.3 for details.
 * Bit 0 				spi3w_en[0] 		Enables 3-wire SPI interface when set to ‘1’. See chapter 5.3 for details.
 */
void BMP280::config()
{
	//TODO Implementation
}

/*
 * Register 0xF7…0xF9 “press” (_msb, _lsb, _xlsb)
 * The “press” register contains the raw pressure measurement output data up[19:0]. For details
 * on how to read out the pressure and temperature information from the device, please consult
 * chapter3.9.
 */
double BMP280::pressure()
{
	uint8_t buffer[3] = {__BMP280_REGISTER_PRESSURE_MSB,__BMP280_REGISTER_PRESSURE_LSB,__BMP280_REGISTER_PRESSURE_XLSB};
	I2CDevice::write(buffer,3);
	I2CDevice::waitForResponse();
	I2CDevice::read(buffer,3);
	int32_t rawPressure = (buffer[0] << 12) | (buffer[1] << 4) | ((buffer[2] & 0xF0) >> 4);
	return this->compensatePressure(rawPressure);
}

double BMP280::compensatePressure(int32_t rawValue){
	return (double)rawValue;
}

/*
 * Register 0xFA…0xFC “temp” (_msb, _lsb, _xlsb)
 * The “temp” register contains the raw temperature measurement output data ut[19:0]. For details
 * on how to read out the pressure and temperature information from the device, please consult
 * chapter 3.9.
 */
double BMP280::temperature()
{
	uint8_t buffer[3] = {__BMP280_REGISTER_TEMPERATURE_MSB,__BMP280_REGISTER_TEMPERATURE_LSB,__BMP280_REGISTER_TEMPERATURE_XLSB};
	I2CDevice::write(buffer,3);
	I2CDevice::waitForResponse();
	I2CDevice::read(buffer,3);
	int32_t rawTemp =  (buffer[0] << 12) | (buffer[1] << 4) | ((buffer[2] & 0xF0) >> 4);
	return this->compensateTemperature(rawTemp);
}

double BMP280::compensateTemperature(int32_t rawValue){

	double x1 = ( ((double) rawValue) / 16384.0 - ((double) this->_calibration.digT1) / 1024.0 ) *
				((double)this->_calibration.digT2);

	double x2 = ( ((double) rawValue) / 131072.0 - ((double) this->_calibration.digT1) / 8192.0 ) *
				( ((double) rawValue) / 131072.0 - ((double) this->_calibration.digT1) / 8192.0 ) * 
				((double)this->_calibration.digT3);

	this->_fineTemperature = (int32_t) (x1 + x2);
	double temperature = (x1 + x2) / 5120.0;
	return temperature;
}

/*
 * 	Trimming parameter readout
 * 	The trimming parameters are programmed into the devices’ non-volatile memory (NVM) during
 * 	production and cannot be altered by the customer. Each compensation word is a 16-bit signed
 * 	or unsigned integer value stored in two’s complement. As the memory is organized into 8-bit
 * 	words, two words must always be combined in order to represent the compensation word. The
 * 	8-bit registers are named calib00…calib25 and are stored at memory addresses 0x88…0xA1.
 * 	The corresponding compensation words are named dig_T# for temperature compensation
 * 	related values and dig_P# for pressure compensation related values. The mapping is shown in
 * 	Table 17.
 */
BMP280_CALIBRATION BMP280::readCalibration()
{
	uint8_t buffer[1] = {	__BMP280_REGISTER_CALIBRATION_DIG_TEMPERATURE_T1_LSB};
	I2CDevice::write(buffer,1);
	I2CDevice::waitForResponse();
	uint8_t data[24];
	memset(&data[0], 0, sizeof(uint8_t)*24);
	I2CDevice::read(data,24);

	BMP280_CALIBRATION calibration;
	calibration.digT1 = (uint16_t)((((uint16_t)data[1]) << 8) | data[0]);
	calibration.digT2 = (int16_t)((((int16_t)((int8_t)data[3])) << 8) | data[2]);
	calibration.digT3 = (int16_t)((((int16_t)((int8_t)data[5])) << 8) | data[4]);

	calibration.digP1 = (uint16_t)((((uint16_t)data[7]) << 8) | data[6]);
	calibration.digP2 = (int16_t)((((int16_t)((int8_t)data[9])) << 8) | data[8]);
	calibration.digP3 = (int16_t)((((int16_t)((int8_t)data[11])) << 8) | data[10]);
	calibration.digP4 = (int16_t)((((int16_t)((int8_t)data[13])) << 8) | data[12]);
	calibration.digP5 = (int16_t)((((int16_t)((int8_t)data[15])) << 8) | data[14]);
	calibration.digP6 = (int16_t)((((int16_t)((int8_t)data[17])) << 8) | data[16]);
	calibration.digP7 = (int16_t)((((int16_t)((int8_t)data[19])) << 8) | data[18]);
	calibration.digP8 = (int16_t)((((int16_t)((int8_t)data[21])) << 8) | data[20]);
	calibration.digP9 = (int16_t)((((int16_t)((int8_t)data[23])) << 8) | data[22]);

	return calibration;
}