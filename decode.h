#pragma once

#include <iostream>
#include <vector>
#include "taskbase.h"
#include "rcvbuf.h"
#include "sndbuf.h"
#include "cg.h"
#include "barcode.h"
#include "QR_Encode.h"
#include "sample.h"

#include <cstdlib>
#include <cstdio>

enum {
	NONE_CODE,
	TEST_CODE,
	RAW_CODE,
	UTF8_CODE2,
	UTF8_CODE3,
	UTF8_CODE_HKANA,
	UTF16_CODE,
	//KANA_CODE,
	SJIS_CODE,
	JIS_CODE,
	ANK_CODE,
	CMD_QR,

	CODE0e,
	CODE12,
	CODE14,
	CODE18,
	CODE1b,
	CODE1c,
	CODE1d,

	CODE_LF,

	CODE_TEST, // 0x1f
};

enum class KanjiFontSize{
	size24x24 = 0x30,
	size16x16 = 0x31,
	defaultSize = 0x30,
};
enum class AnkFontSize{
	size8x16 = 0x30,
	size12x24 = 0x31,
	size16x16 = 0x32,
	size24x24 = 0x33,
	defaultSize = 0x31,
};
enum class qrCodeLelel{
	// Error correction lebel L (7%)
	QR_ERR_LVL_L = 0x4C,
	// Error correction lebel M (15%)
	QR_ERR_LVL_M = 0x4D,
	// Error correction lebel Q (25%)
	QR_ERR_LVL_Q = 0x51,
	// Error correction lebel H (30%)
	QR_ERR_LVL_H = 0x48,
};
enum class barcodeMode{
	// UPC-A : 11-digit, d1-d11, C/D.
	BCODE_UPC_A = 0x30,
	// JAN13 : 12-digit, d1-d12, C/D.
	BCODE_JAN13 = 0x32,
	// JAN8 : 7-digit, d1-d7, C/D.
	BCODE_JAN8 = 0x33,
	// CODE39 : variable, d1-d20, C/D.
	BCODE_CODE39 = 0x34,
	// ITF : variable, d1-d20. 
	BCODE_ITF = 0x35,
	// CODABAR (NW7) : variable, d1-d20. 
	BCODE_CODABAR = 0x36,
};

enum class CmdMode{
	none,
	// 0x12
	// 漢字コードのサイズセット？

	// 0x1b
	initialize,
	setLineSpaceing,
	defaultLineSpaceing,
	setPrintDirection,
	putPaperFeed,
	setInterCharacterSpace,
	defaultInterCharacterSpace,
	putPrintPosition,
	setScript,
	clearScript,
	setDoubleSizeHeight,
	clearDoubleSizeHeight,
	setDoubleSizeWidth,
	clearDoubleSizeWidth,
	setLargeFont,
	clearLargeFont,
	setANKFont,

	// 0x1c
	setQuadrupleSize,
	clearQuadrupleSize,
	setEnlargement,
	clearEnlargement,
	printBitmapImage,

	// 0x1d
	setBarCodeHeight,
	defaultBarCodeHeight,
	setBarCodeBarSize,
	defaultBarCodeBarSize,
	printQRCode,
	printBarCode,

	// etc
	clearBuffer,
	setKanjiFont,
};

class Config
{
public:
	// 漢字サイズ
	KanjiFontSize kanjiFontSize = KanjiFontSize::defaultSize;
	// ANKサイズ
	AnkFontSize ankFontSize = AnkFontSize::defaultSize;

	uint8_t lineSpace = 4;
	uint8_t charSpace = 1;

	bool largeFont = false;
	uint8_t fontHeightRate = 1;
	uint8_t fontWidthRate = 1;
	bool fontHeightDouble = false;
	bool fontWidthDouble = false;
	bool quadrupleFont = false; // 必要？

	bool lister = false;
	uint8_t barcodeH = 0x50;

	int align = 0;
	int darkness = 0;

// mode
/*
高さ２倍フォント
幅２倍フォント
ラージフォント(48x96)
行間スペース
印字方向
文字間スペース
４倍サイズ
バーコードの高さ
バーコードのサイズ
*/
};

struct Item
{
	uint8_t* pDat;
	int srcW;
	int bitW;
	int h;
	bool rev;

	Item(uint8_t* p, int sw, int bit, int height, bool r = false)
		: pDat(p), srcW(sw), bitW(bit), h(height), rev(r)
	{
	}
	Item(Item&& si) noexcept
		: pDat(si.pDat), srcW(si.srcW), bitW(si.bitW), h(si.h), rev(si.rev)
	{
		si.pDat = nullptr;
	}
	~Item() {
		delete []pDat;
	}
};

class Decode: public TaskBase
{
	Config conf;
	RcvBuf* pRcvBuf;
	SndBuf* pSndBuf;
	Sample iSample;
	Cg iCg;
	int imgLine = 0;
	uint8_t imgBuf[48 * 2048/4];
	void CmdRegBmp(int);

	bool TaskReady(){return true;};
	void Worker();

	int CheckCodeType(uint8_t);

	bool SetBufDot(uint8_t*, int, int, int, bool=false);

	void GetFontRate(int&, int&);
	void SetBufFont( const uint8_t*, int, int, int);
	void SetBufFont2( const uint8_t*, int, int, int);

	void CheckArea(int, int=0);

	uint8_t* CodeAnk(uint8_t*);
	uint8_t* CodeHKana(uint16_t);
	uint8_t* CodeUtf8_3(uint8_t*);
	uint8_t* CodeUtf8_2(uint8_t*);
	void CmdBmp(uint8_t*);
	void CmdBmpPool(uint8_t*);
	void CmdBmp2(uint8_t*);

	void KanjiDump();

	uint8_t* Code_12(uint8_t*, int);
	uint8_t* Code_18(uint8_t*, int);
	uint8_t* Code_1b(uint8_t*, int);
	uint8_t* Code_1c(uint8_t*, int);
	uint8_t* Code_1d(uint8_t*, int);
	uint8_t* Test(uint8_t*, int);

	uint8_t* Receive(uint8_t*&, int);
	int Receive(uint8_t*&);

	// ----------------------------- for delete
	void CmdBarcode(uint8_t*);
	int GenQR(uint8_t*);
	int GenDM(uint8_t*, size_t);

	int maxH = 0;
	int bitPos = 0;
	std::vector<Item> itemList;
	void SetSndBuf();
	void SetSndBufDirect(uint8_t* addr, int srcW, int datW, int datH, bool=false);

	void AddItem(uint8_t*, int, int, int, bool=false);
	void AddItemFont(uint8_t*, int, int, int);
	void AddItemColSpace(int);

	void SetCr();

	bool modeSample = false;
	bool GetDat(uint8_t&);

public:
	Decode(RcvBuf* r, SndBuf* s): pRcvBuf{r}, pSndBuf{s}{};
};
