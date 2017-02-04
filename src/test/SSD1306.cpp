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
#include "../main/devices/SSD1306/SSD1306.h"

using namespace std;
int main()
{
	/*
	SSD1306* oled = new SSD1306(1,0x3C);


	cout << "Initializing Screen" << endl;
	oled->boot();
	cout << "Screen Initialized" << endl;


	int dataLen = 1024;
	uint8_t data[dataLen];
	memset(data,0,sizeof(uint8_t)*dataLen);

	for(int i=0;i<dataLen;i++){
		data[i] = i%256;
	}

	oled->setDataMode();
	oled->send(data,dataLen);

	oled->setCommandMode();

	for(double i=0;i<=100;i++)
	{
		oled->setContrast(i/100.0);
		usleep(50000);
	}

	oled->resetContrast();

	int c = 0;
	while(c < 100){
		cout << "Inverting display: " << c%2 << endl;
		oled->invertDisplay(c % 2);
		c++;
		usleep(200000);
	}

	delete(oled);
*/
	return 0;
}