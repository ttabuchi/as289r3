#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#include "ad.h"
#include "iodefine.h"
#include "cutter.h"
#include "taskbase.h"
#include "sndbuf.h"
#include "spi.h"

enum {
	MECHA_MLT289,
	MECHA_MLT4281,
};

class Printer: public TaskBase
{
	uint8_t phaseTbl[4] = {2, 3, 1, 0};
	const int64_t m_289tbl_4v[19] = {	// 19 step
		13330, 10910, 8270, 6940,
		6090, 5500, 5050, 4700,
		4410, 4170, 3960, 3790,
		3630, 3490, 3370, 3260,
		3160, 3070, 2980,
	};
	const int64_t m_289tbl_5vTest[53] = {	// 19 step
		8850, 7300, 5570, 4690, 4130, 3730, 3430, 3190,
		2990, 2830, 2690, 2570, 2470, 2370, 2290, 2220,
		2150, 2080, 2030, 2000, 1970, 1940, 1910, 1880,
		1850, 1820, 1790, 1760, 1730, 1700, 1670, 1640,
		1610, 1580, 1550, 1520, 1490, 1460, 1430, 1400,
		1370, 1340, 1310, 1280, 1250, 1220, 1190, 1160,
		1130, 1100, 1070, 1040, 990,
	};
	const int64_t m_289tbl_5v[19] = {	// 19 step
		8850, 7300, 5570, 4690,
		4130, 3730, 3430, 3190,
		2990, 2830, 2690, 2570,
		2470, 2370, 2290, 2220,
		2150, 2080, 2030,
	};
	const int64_t m_289tbl_6v[19] = {	// 19 step
		6410, 5260, 4000, 3360,
		2960, 2607, 2450, 2280,
		2140, 2020, 1920, 1840,
		1760, 1700, 1640, 1580,
		1530, 1490, 1450,
	};
	const int64_t m_289tbl_7v[19] = {	// 19 step
		4440, 3780, 2980, 2540,
		2250, 2040, 1880, 1760,
		1650, 1560, 1490, 1420,
		1370, 1320, 1270, 1230,
		1190, 1160, 1130,
	};
	const int64_t m_289tbl_8v[19] = {	// 19 step
		3470, 2990, 2390, 2050,
		1820, 1660, 1530, 1430,
		1350, 1280, 1210, 1160,
		1120, 1070, 1040, 1000,
		970, 950, 920,
	};
	const int64_t m_289tbl_9v[19] = {	// 19 step
	//	3300, 2800, 2200, 1900,
	//	1700, 1500, 1400, 1300,
	//	1200, 1100, 1090, 1000,
	//	990, 900, 890, 880,
	//	800, 790, 780,

	//	2659, 2300, 1844, 1584,
	//	1408, 1283, 1183, 1107,
	//	1043, 988, 938, 897,
	//	867, 832, 805, 775,
	//	751, 736, 770,

		2659, 2300, 1844, 1584,
		1408, 1283, 1183, 1107,
		1043, 988, 938, 920,
		920, 920, 920, 920,
		920, 920, 920,
	};

	const int64_t m_4281tbl[48] = {	// 48 step 4.2-6.5V
		7692, 5172, 4157, 3181, 2895, 2675, 2498, 2352,
		2229, 2124, 2032, 1951, 1879, 1815, 1756, 1704,
		1655, 1610, 1569, 1531, 1496, 1463, 1432, 1402,
		1375, 1349, 1325, 1301, 1279, 1259, 1239, 1220,
		1201, 1184, 1167, 1151, 1136, 1121, 1107, 1094,
		1080, 1068, 1056, 1044, 1032, 1021, 1010, 1000,
	};
	const int64_t m_4281tbl2[48] = {	// 48 step 4.2-6.5V
		5172, 4157, 3181, 2895, 2675, 2498, 2352, 2229,
		2124, 2032, 1951, 1879, 1815, 1756, 1704, 1655,
		1610, 1569, 1531, 1496, 1463, 1432, 1402, 1375,
		1349, 1325, 1301, 1279, 1259, 1239, 1220, 1201,
		1184, 1167, 1151, 1136, 1121, 1107, 1094, 1080,
		1068, 1056, 1044, 1032, 1021, 1010, 1000, 1000,
	};
	const int64_t m_4281tbl_9v[48] = {	// 48 step 6.6-8.5V
		2500, 2285, 2118, 1983, 1870, 1775, 1693, 1622,
		1559, 1502, 1452, 1406, 1364, 1326, 1291, 1258,
		1228, 1200, 1173, 1149, 1126, 1104, 1083, 1064,
		1045, 1028, 1011,  995,  980,  966,  952,  939,
		 926,  914,  902,  891,  880,  869,  859,  849,
		 840,  831,  822,  813,  805,  797,  789,  781,
	};

	Cutter iCutter;
	Spi iSpi;
	SndBuf* pSndBuf;

	const int64_t* ppsTbl = m_289tbl_5v;
	int maxStep = 18;

	bool TaskReady(){return true;};
	void Worker();

	void Trace(const char* str){
		std::cout << str << std::endl;
	}

	bool CheckErr();

	absolute_time_t lastPeriod;
	int mechaType = MECHA_MLT4281;

	void HeadClear(uint8_t);
	int CntActive(uint8_t*);
	void Latch(int t = 1);
	void Strobe(uint8_t*, int, int=64);
	uint64_t GetTon289(double ndot, double, double, bool=false);
	uint64_t GetTon(double ndot, double, double, bool=false);

	bool quarityH = true;
	bool off = true;
	uint8_t step = 0;
	int phase = 0;
	pwm_config pwmConf; 
	void MotorPwm(double);
	bool CheckVolt(double&);
	bool MotorPrepare(double&, int=30);
	void NextPhase();
	void MotorOn();
	void MotorWait();
	void MotorOff();

	void WaitUntilNext();
	void WaitUntilStop();

public:
	static Ad iAd;
	//Printer(int p): TaskBase(p){}
	void Init(SndBuf*);
};
