#pragma once

#include <iostream>
#include <vector>
#include "printer.h"

class Sample
{
	int mode = 0;
	std::vector<uint8_t>::iterator it;

	int len;
	uint8_t* p;
	uint8_t* pend;

	char status[256];

public:
	//static uint8_t dat0[];
	//static std::vector<uint8_t> dat1;
	//static std::vector<uint8_t> dat2;
	std::vector<uint8_t> dat;
	int Gen();
	void Start();
	bool Get(uint8_t&);

	void StartOld();
	bool GetOld(uint8_t&);
};
