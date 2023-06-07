#pragma once

#include <iostream>
#include <algorithm>

struct RowBits
{
	uint8_t dat[48];
	int pByte;
	int pBit;

	void Init();
	void Set(const uint8_t*, int);
	void SetBit1(const uint8_t*, int);
	void SetBit2(const uint8_t*, int);
	void Set16(const uint16_t*, int);
	void SetDat2(const uint8_t, int);
};

