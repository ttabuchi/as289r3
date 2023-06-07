#pragma once

#include "pico/stdlib.h"

#define SND_BUF_ROW_NUM 1024 

enum {
	PMODE_NORMAL = 0,
	PMODE_LISTER = 1,
	PMODE_PCUT = 2,
	PMODE_FCUT = 3,
	PMODE_16 = 4,	// 16x16, 8x16 の印字
	PMODE_FEED = 5,
};

struct Line48
{
	uint8_t col[48];
	int mode;
};

class SndBuf
{
	int bitN = 0;
	int irow = 0;
	int orow = 0;
	Line48 row[SND_BUF_ROW_NUM];
	
public:
	int reservedLine = 0;
	void ShowStat();

	void SetCut(bool);
	void SetCr();

	bool GetArea(int, int=0);

	void SetColSpace(int);

	void FinWork();
	
	bool SetColDot(const uint8_t*, int, int, int, int, bool, bool=false);

	Line48* GetRowPtr();
};
