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
#include <string.h>
#include "../main/devices/BMP280/BMP280.h"
#include "../main/i2c_impl/RaspberryPi.h"
using namespace std;

int main()
{
	cout << "BPM280 Test" << endl;

	RPI_I2CInputOutput *RPI_IO = new RPI_I2CInputOutput(1);
	BMP280 *bpm280 = new BMP280(0x76,RPI_IO);

	cout << "Initializing Device" << endl;
	bpm280->init();

	cout << "Chip ID: " << bmp280->getChipId() << endl;

	cout << "Clearing resources" << endl;
	delete(bpm280);
	delete(RPI_IO);
	return 0;
}