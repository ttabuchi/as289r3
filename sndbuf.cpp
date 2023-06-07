#include <iostream>
#include "sndbuf.h"

const uint8_t expandW[] = {
	0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f,
	0xc0, 0xc3, 0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff,
};

void SndBuf::ShowStat()
{
    std::cout << ", irow = " << irow;
    std::cout << ", orow = " << orow;
    std::cout << std::endl;
}

bool SndBuf::GetArea(int line, int bit)
{
	if(line >= SND_BUF_ROW_NUM) return false;
	if(bit > 384) return false;
	
	if(bitN + bit > 384) SetCr();

	if(reservedLine >= line) return true;

	int diff = line - reservedLine;
   
	int p = (irow + reservedLine) & (SND_BUF_ROW_NUM - 1);

	for(int i = 0; i < diff; i++){
		p = (p + 1) & (SND_BUF_ROW_NUM - 1);
		if(p == orow) return false;
	}

	p = (irow + reservedLine) & (SND_BUF_ROW_NUM - 1);

	for(int i = 0; i < diff; i++){
		row[p].mode = PMODE_NORMAL;
		uint64_t* p64 = reinterpret_cast<uint64_t*>(row[p].col);
		for(int j = 0; j < 6; j++) *(p64 + j) = 0;
		p = (p + 1) & (SND_BUF_ROW_NUM - 1);
	}

	reservedLine = line;

	return true;
}

bool SndBuf::SetColDot(
	const uint8_t* srcDat,
	int srcWidth,
	int datBit,
	int datH, // font-space込み
	int rOffset,
	bool lister, 
	bool rev
	)
{
	int icol = bitN / 8;
	int rbit = bitN & 7;
	int srcByte = (datBit+ 7) / 8;
	//int srcOddBit = datBit & 7; // 取得データが＋１回になるかどうか
	//uint8_t mask[48] = {1, };
	uint8_t dat;

	for(int i = 0; i < datH; i++){
		int r = (irow + rOffset + i) & (SND_BUF_ROW_NUM - 1);
		if(lister) row[r].mode = PMODE_LISTER;
		uint8_t* p = row[r].col + icol;
		for(int j = 0; j < srcByte; j++){
			if(lister) dat = srcDat[(datH - i - 1) * srcWidth + j];
			else dat = srcDat[i * srcWidth + j];
			if(rev) dat ^= 0xff;

			if(rbit){
				*p |= (dat >> rbit);
				*(p+1) = (dat << (8-rbit));
			}
			else *p = dat;
			p++;
		}
	}

	bitN += datBit;
	if(bitN >= 384){
		SetCr();
		return true;
	}

	return false;
}

void SndBuf::SetColSpace(int datBit)
{
	bitN += datBit;
	if(bitN >= 384) SetCr();
}

Line48* SndBuf::GetRowPtr()
{
    if(orow == irow) return nullptr;

	Line48* ret = row + orow;
    //orow = (orow + 1) & (SND_BUF_ROW_NUM - 1);
    
    return ret;
}

void SndBuf::FinWork()
{
    orow = (orow + 1) & (SND_BUF_ROW_NUM - 1);
}

void SndBuf::SetCut(bool partial)
{
	int mode = partial? PMODE_PCUT: PMODE_FCUT;
	row[irow].mode = mode;

	irow = (irow + 1) & (SND_BUF_ROW_NUM - 1);
	bitN = 0;
	reservedLine = 0;
	row[irow].mode = PMODE_NORMAL;
}

void SndBuf::SetCr()
{
	if(!reservedLine){
		bitN = 0; // clear offset
		return;
	}

	if(!bitN){
		for(int i = 0; i < reservedLine; i++){
			int p = (irow + i) & (SND_BUF_ROW_NUM - 1);
			row[p].mode = PMODE_FEED;
		}
	}

	irow = (irow + reservedLine) & (SND_BUF_ROW_NUM - 1);
	bitN = 0;
	reservedLine = 0;
}
