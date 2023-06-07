#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "iodefine.h"

class Ad
{
public:
	double voltVal;
	double tempVal;
	int lastId = 0;
	
public:
	void Init();
	double GetVoltVal();
	double GetTempVal();
	double CulcVolt();
	double CulcTemp();
	double GetVolt();
	double GetTemp();
	double GetTempFast();
};

