#pragma once

#include <iostream>

class Cg
{
	uint16_t Utf8_Utf16_2(uint8_t*);
	uint16_t Utf8_Utf16_3(uint8_t*);
	uint16_t Utf16_Sjis(uint16_t);
	uint16_t Sjis_Jis(uint16_t);

	uint8_t* Jis_Krom(uint16_t);

	// 不使用
	uint8_t* Ank_Krom(uint16_t);

public:
	Cg(){}
	uint8_t* Utf8_RomAddr_2(uint8_t*);
	uint8_t* Utf8_RomAddr_3(uint8_t*);
	
	uint8_t* Ank_RomAddr16(uint8_t);
	uint8_t* Ank_RomAddr24(uint8_t);

	uint8_t* Hankana_RomAddr16(uint16_t);
	uint8_t* Hankana_RomAddr24(uint16_t);

	// dump用
	uint8_t* GetKromAddr(int);
};
