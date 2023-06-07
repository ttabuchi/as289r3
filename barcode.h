#pragma once

#include <iostream>
#include "rowBits.h"

class Barcode
{
	const uint8_t janPrefixTable[42] = { // odd: 0, even: 1 に注意
		0x00, 0x2c, 0x34, 0x38, 0x4c, 0x64, 0x70, 0x54, 0x58, 0x68, 	// 0～9
		0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40,						// 0x3a～0x40 (不使用)
		0x14, 0x18, 0x24, 0x28, 0x30, 0x44, 0x48, 0x50, 0x60, 			// A～I
		0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,								// J～O(不使用)
		0x80, 0xac, 0xb4, 0xb8, 0xcc, 0xe4, 0xf0, 0xd4, 0xd8, 0xe8,		// P～Y
	};

	// total 113dot
	// left margin 11
	const uint8_t lbar = 0x05; // ---- -101
	// left char 42
	const uint8_t cbar = 0x50; // 0101 0---
	// left char 35 
	// check char 7 
	const uint8_t rbar = 0xa0; // 101- ----
	// right margin 7 

	const uint8_t lo[10] = {
		0x1a, // 0	0001	101-
		0x32, // 1	0011	001-
		0x26, // 2	0010	011-
		0x7a, // 3	0111	101-
		0x46, // 4	0100	011-
		0x62, // 5	0110	001-
		0x5e, // 6	0101	111-
		0x76, // 7	0111	011-
		0x6e, // 8	0110	111-
		0x16, // 9	0001	011-
	};
	const uint8_t le[10] = {
		0x4E, 0x66,
		0x36, 0x42,
		0x3A, 0x72,
		0x0A, 0x22,
		0x12, 0x2E,
	};
	const uint8_t re[10] = {
		0xE4, 0xCC,
		0xD8, 0x84,
		0xB8, 0x9C,
		0xA0, 0x88,
		0x90, 0xE8,
	};

	const uint8_t itf[10][5] = {
		{1, 1, 2, 2, 1, }, // 0
		{2, 1, 1, 1, 2, }, // 1
		{1, 2, 1, 1, 2, }, // 2
		{2, 2, 1, 1, 1, }, // 3
		{1, 1, 2, 1, 2, }, // 4
		{2, 1, 2, 1, 1, }, // 5
		{1, 2, 2, 1, 1, }, // 6
		{1, 1, 1, 2, 2, }, // 7
		{2, 1, 1, 2, 1, }, // 8
		{1, 2, 1, 2, 1, }, // 9
	};

	int ChkMod103(const uint8_t* dat, int len){
		int chk = 0;
		int w = 1;
		if(len & 1) w = 3;

		for(int i = 0; i < len; i++){
			chk += dat[i] * w;
			w ^= 2;
		}

		chk %= 10;
		chk = 10 - chk;
		if(chk == 10) chk = 0;

		//std::cout << "chk=" << chk << std::endl;
		
		return chk;
	}

	RowBits& rb;

public:
	int GenJan13(const uint8_t* dat, size_t len);
	int GenJan8(const uint8_t* dat, size_t len);
	int GenUpcA(const uint8_t* dat, size_t len);
	int GenItf(const uint8_t* dat, size_t len);
	int GenNw7(const uint8_t* dat, size_t len);
	int GenCode39(const uint8_t* dat, size_t len);

	Barcode(RowBits& _rb): rb(_rb){rb.Init();}
};

