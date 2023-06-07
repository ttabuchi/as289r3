#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "iodefine.h"
#include "taskbase.h"

class Cutter
{
	const int tbl[48] = {
		2500, 2285, 2118, 1983, 1870, 1775, 1693, 1622,
		1559, 1502, 1452, 1406, 1364, 1326, 1291, 1258,
		1228, 1200, 1173, 1149, 1126, 1104, 1093, 1064,
		1045, 1028, 1011,  995,  980,  966,  952,  939,
		 926,  914,  902,  891,  880,  869,  859,  849,
		 840,  831,  822,  813,  805,  797,  789,  781,
	};
	uint step = 0;
	const uint maxStep = 47;

	void PinSet(int p, int dir);

	// cutter
	int SENSOR_OFF = 0;
	int SENSOR_ON = 1;

	const uint8_t cutterPhaseTbl[4] = {0, 2, 3, 1, };
	uint8_t cPhase = 0;
	
	void On();
	void MoveToStep(int, int);
	void Move(int);
	int ChkSens(int);
	bool MoveToSensor(int d, int s);

	void Trace(const char* str){
		std::cout << str << std::endl;
	}

	pwm_config pwmConf; 
	void MotorPwm(double);

public:
	int InitialRoutine();
	int Cut(bool=false);
	void Off();

public:
	Cutter();
	void InitIO();
};
