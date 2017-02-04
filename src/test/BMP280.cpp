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

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "../main/devices/BMP280/BMP280.h"
#include "../main/i2c_impl/RaspberryPi.h"
using namespace std;

int main()
{
	cout << "BMP280 Test" << endl;

	RPI_I2CInputOutput *RPI_IO = new RPI_I2CInputOutput(1);
	BMP280 *bmp280 = new BMP280(0x76,RPI_IO);

	cout << "Full reset of the Device" << endl;
	//bmp280->reset(true);
	cout << "Initializing Device" << endl;
	bmp280->initialize();

	cout << "Chip ID: " <<  hex << setw(2) <<  (int) bmp280->getChipId() << endl;

	BMP280_STATUS status = bmp280->status();
	cout << "Device status: measuring ?"<< status.measuring << ", imUpdate? " << status.imUpdate << endl;
	
	BMP280_CALIBRATION calibration = bmp280->readCalibration();

	cout << "Reading Calibration: " << endl;
	cout << " T1: " <<  hex << setw(2) <<  (uint16_t) calibration.digT1;
	cout << " T2: " <<  hex << setw(2) <<  (int16_t) calibration.digT2;
	cout << " T3: " <<  hex << setw(2) <<  (int16_t) calibration.digT3;

	cout << endl;

	cout << " P1: " <<  hex << setw(2) <<  (uint16_t) calibration.digP1;
	cout << " P2: " <<  hex << setw(2) <<  (int16_t) calibration.digP2;
	cout << " P3: " <<  hex << setw(2) <<  (int16_t) calibration.digP3;
	cout << endl;
	cout << " P4: " <<  hex << setw(2) <<  (int16_t) calibration.digP4;
	cout << " P5: " <<  hex << setw(2) <<  (int16_t) calibration.digP5;
	cout << " P6: " <<  hex << setw(2) <<  (int16_t) calibration.digP6;
	cout << endl;
	cout << " P7: " <<  hex << setw(2) <<  (int16_t) calibration.digP7;
	cout << " P8: " <<  hex << setw(2) <<  (int16_t) calibration.digP8;
	cout << " P9: " <<  hex << setw(2) <<  (int16_t) calibration.digP9;
	cout << endl;

	cout << "Looping through reading T° & hPa" << endl;
	do{
		bmp280->controlMeasure(SKIPPED,SKIPPED,FORCED);
		sleep(1);
    	cout << "Reading Temperature: " << bmp280->temperature() << endl;
    	cout << "Reading Pressure: " << bmp280->pressure() << endl;
    	sleep(1);
    	cout << "Space to quit, Enter to continue" << endl;
    }
    while(getchar() != 32 || getchar() != ' ');
    
    bmp280->reset(true);

	cout << "Clearing resources" << endl;
	delete(bmp280);
	delete(RPI_IO);
	return 0;
}