#include <iostream>
#include <algorithm>
#include "rowBits.h"

void RowBits::Init()
{
	for(int i = 0; i < 48; i++) dat[i] = 0;
	pByte = 0;
	pBit = 0;
}

void RowBits::SetBit1(const uint8_t* d, int datLen)
{
	while(datLen > 0){
		int setLen = (std::min)(datLen, 8 - pBit); // for windows
		dat[pByte] |= (d[0] >> pBit);

		pBit += setLen;
		datLen -= setLen;

		if(pBit == 8){
			pByte += 1;
			pBit = 0;
		}
	}
}

void RowBits::Set(const uint8_t* d, int datLen)
{
	return SetBit2(d, datLen);
}

void RowBits::SetDat2(const uint8_t d, int datLen)
{
	int inBit = 0;

	while(datLen > 0){
		int getLen = (std::min)(datLen, 8);
		int setLen = (std::min)(getLen * 2, 8 - pBit); // for windows
		getLen = setLen / 2;

		for(int i = 0; i < getLen; i++){
			if(d & (0x80 >> inBit)){
				dat[pByte] |= (0xc0 >> pBit);
			}
			inBit += 1;
			pBit += 2;
		}

		//pBit += setLen;
		if(pBit == 8){
			pByte += 1;
			pBit = 0;
		}

		//inBit += getLen;
		datLen -= getLen;
	}
}

void RowBits::SetBit2(const uint8_t* d, int datLen)
{
	int inByte = 0;
	int inBit = 0;

	while(datLen > 0){
		int getLen = (std::min)(datLen, 8);
		int setLen = (std::min)(getLen * 2, 8 - pBit); // for windows
		getLen = setLen / 2;

		for(int i = 0; i < getLen; i++){
			if(d[inByte] & (0x80 >> inBit)){
				dat[pByte] |= (0xc0 >> pBit);
			}
			inBit += 1;
			pBit += 2;
		}

		//pBit += setLen;
		if(pBit == 8){
			pByte += 1;
			pBit = 0;
		}

		//inBit += getLen;
		datLen -= getLen;
		if(inBit >= 8){
			inByte += 1;
			inBit = 0;
		}
	}
}

void RowBits::Set16(const uint16_t* d, int datLen)
{
	int inByte = 0;
	int inBit = 0;

	while(datLen > 0){
		int getLen = (std::min)(datLen, 8);
		int setLen = (std::min)(getLen * 2, 8 - pBit); // for windows
		getLen = setLen / 2;

		for(int i = 0; i < getLen; i++){
			if(d[inByte] & (0x8000 >> inBit)){
				dat[pByte] |= (0xc0 >> pBit);
			}
			inBit += 1;
			pBit += 2;
		}

		//pBit += setLen;
		if(pBit == 8){
			pByte += 1;
			pBit = 0;
		}

		//inBit += getLen;
		datLen -= getLen;
		if(inBit >= 16){
			inByte += 1;
			inBit = 0;
		}
	}
}

