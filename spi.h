#pragma once

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "taskbase.h"
#include "sndbuf.h"

struct SpiPin
{
	uint clock;
	uint tx;
};

class Spi
{
	uint pins[2];
	SpiPin pin;
	spi_inst_t* spi;
	void Write(uint8_t data);
	SndBuf* pSndBuf;

	 bool TaskReady(){return true;};
	 void Worker(){};
	 uint8_t buf[48];
	 uint baud;

public:
	Spi();
	void Init(int, int, uint, SndBuf*);
	void SendNull(uint8_t);
	uint SendLine16(uint16_t*);
	uint SendLine(uint8_t*);
	void SendTest(const uint8_t);
	uint GetBaud(){return baud;}
};
