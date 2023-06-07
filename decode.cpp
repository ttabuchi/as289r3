#include "decode.h"

#include <cstring>
#include <cassert>
#include <cmath>
#include "libdmtx/dmtx.h"

#include "image_IIFES.h"
//extern const uint8_t IIFES_bmp[48*132];
extern const uint8_t IIFES_bmp[48*884];

int Decode::CheckCodeType(uint8_t dat)
{
	//int type = RAW_CODE;
	int type = NONE_CODE;

	if(dat == 0x12) type = CODE12;
	else if(dat == 0x0a) type = CODE_LF;
	else if(dat == 0x1f) type = CODE_TEST;
	else if(dat == 0x14) type = CODE14; // 横倍幅拡大解除
	else if(dat == 0x0e) type = CODE0e; // 横倍幅拡大指定
	else if(dat == 0x18) type = CODE18;
	else if(dat == 0x1b) type = CODE1b;
	else if(dat == 0x1c) type = CODE1c;
	else if(dat == 0x1d) type = CODE1d;
	else if((0x20 <= dat) && (dat <= 0x7f)) type = ANK_CODE;
	else if((0xc0 <= dat) && (dat <= 0xdf)) type = UTF8_CODE2;
	else if((0xe0 <= dat) && (dat <= 0xef)) type = UTF8_CODE3;
	//else if((0xef <= dat) && (dat <= 0xff)) type = UTF8_CODE_HKANA;

	return type;
}

void Decode::CheckArea(int line, int bit)
{
	while(true){
		if(pSndBuf->GetArea(line, bit)) break;

		Delay(1);
		//sleep_us(100);
	}

//	if(maxH < line) maxH = line;
}

void Decode::AddItem(uint8_t* addr, int srcW, int datW, int datH, bool rev)
{
	// 384を超えるときだけ先に印字
	// 収まりきらない
	if(bitPos + datW > 384) SetSndBuf();

	if(maxH < datH) maxH = datH;
	itemList.push_back(Item(addr, srcW, datW, datH, rev));
	bitPos += datW;
	if(bitPos >= 384) SetSndBuf();
}

void Decode::AddItemFont(uint8_t* addr, int srcW, int datW, int datH)
{
	// 384を超えるときだけ先に印字
	// 収まりきらない
	if(bitPos + datW > 384) SetSndBuf();

	if(maxH < datH + conf.lineSpace) maxH = datH + conf.lineSpace;
	itemList.push_back(Item(addr, srcW, datW, datH, false));
	bitPos += datW;
	if(bitPos >= 384) SetSndBuf();
	else AddItemColSpace(conf.charSpace);
}

void Decode::AddItemColSpace(int datW)
{
	if(bitPos + datW >= 384){
		SetSndBuf();
		return;
	}

	itemList.push_back(Item(nullptr, 0, datW, 0, false));
	bitPos += datW;
}

void Decode::SetCr()
{
	pSndBuf->SetCr();

	bitPos = 0;
	maxH = 0;
	itemList.clear();
}

void Decode::SetSndBuf()
{
	CheckArea(maxH);

	int offsetH = 0;
	int sp = 0;

	if(conf.align % 3 == 1) offsetH = (384 - bitPos) / 2;	
	else if(conf.align % 3 == 2) offsetH = 384 - bitPos;

	pSndBuf->SetColSpace(offsetH);

	for(auto& v: itemList){
		if(v.pDat == nullptr) pSndBuf->SetColSpace(v.bitW);
		else{
			if(conf.align / 3 == 1) sp = (maxH - v.h) / 2;	
			else if(conf.align / 3 == 2) sp = maxH - v.h;	

			pSndBuf->SetColDot(v.pDat, v.srcW, v.bitW, v.h, sp, conf.lister, v.rev);
		}
	}

	pSndBuf->SetCr();

	bitPos = 0;
	maxH = 0;
	itemList.clear();
}

void Decode::SetSndBufDirect(uint8_t* addr, int srcW, int bitW, int datH, bool rev)
{
	if(bitPos + bitW > 384) SetSndBuf();

	if(maxH < datH) maxH = datH;
	CheckArea(maxH);

	int sp = 0;
	pSndBuf->SetColDot(addr, srcW, bitW, datH, sp, conf.lister, rev);

	pSndBuf->SetCr();

	bitPos = 0;
	maxH = 0;
}

bool Decode::SetBufDot(uint8_t* addr, int srcW, int datWDot, int datH, bool rev)
{
	CheckArea(datH, datWDot);
	pSndBuf->SetColDot(addr, srcW, datWDot, datH, 0, conf.lister, rev);
	//itemList.push_back(Item(addr, srcW, datWDot, datH, rev));

	return true;
}

void Decode::GetFontRate(int& w, int& h)
{
	w = 1;
	h = 1;

	if(conf.largeFont){
		w = 2;
		h = 2;
	}
	else if(conf.quadrupleFont){
		w = 2;
		h = 2;
	}
	else{
		if(conf.fontWidthRate != 1) w = conf.fontWidthRate;
		else if(conf.fontWidthDouble) w = 2;
		if(conf.fontHeightRate != 1) h = conf.fontHeightRate;
		else if(conf.fontHeightDouble) h = 2;
	}
}
void Decode::SetBufFont(
	const uint8_t* addr,
	int srcW,
	int bitw,
	int datH
)
{
	static const uint8_t expandW[] = {
		0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f,
		0xc0, 0xc3, 0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff,
	};

	int byteW = (bitw + 7) / 8;
	int w = bitw;
	int h = datH;
	int tw = 1;
	int th = 1;

	GetFontRate(tw, th);
	w *= tw;
	h *= th;

	uint8_t* pBuf = new uint8_t[48 * h];
	uint8_t* p;

	if(tw == 2){
		if(th == 2){
			for(int i = 0; i < datH; i++){
				p = pBuf + (2 * i) * 48;
				for(int j = 0; j < byteW; j++){
					uint8_t dat = addr[i * srcW + j];
					*p = expandW[dat >> 4];
					*(p + 48) = *p;
					*(p +  1) = expandW[dat & 0x0f];
					*(p + 49) = *(p + 1);
					p += 2;
				}
			}
		}
		else{
			for(int i = 0; i < datH; i++){
				p = pBuf + i * 48;
				for(int j = 0; j < byteW; j++){
					uint8_t dat = addr[i * srcW + j];
					*p = expandW[dat >> 4];
					*(p +  1) = expandW[dat & 0x0f];
					p += 2;
				}
			}
		}
	}
	else{
		if(th == 2){
			for(int i = 0; i < datH; i++){
				p = pBuf + (2 * i) * 48;
				for(int j = 0; j < byteW; j++){
					*p = addr[i * srcW + j];
					*(p + 48) = *p;
					p += 1;
				}
			}
		}
		else{
			for(int i = 0; i < datH; i++){
				p = pBuf + i * 48;
				for(int j = 0; j < byteW; j++){
					*p = addr[srcW * i + j];
					p += 1;
				}
			}
		}
	}

	AddItemFont(pBuf, 48, w, h);
}

void Decode::SetBufFont2(
	const uint8_t* addr,
	int srcW,
	int bitw,
	int datH
)
{
	static const uint8_t expandW[] = {
		0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f,
		0xc0, 0xc3, 0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff,
	};

	int byteW = (bitw + 7) / 8;
	int w = bitw;
	int h = datH;
	
	int tw = 1;
	int th = 1;

	GetFontRate(tw, th);
	w *= tw;
	h *= th;

	uint8_t* pBuf = new uint8_t[48 * h];
	uint8_t* p;

	if(tw == 2){
		if(th == 2){
			for(int i = 0; i < datH; i++){
				p = pBuf + (2 * i) * 48;
				for(int j = byteW - 1; j >= 0; j--){
					uint8_t dat = addr[i * srcW + j];
					*p = expandW[dat >> 4];
					*(p + 48) = *p;
					*(p +  1) = expandW[dat & 0x0f];
					*(p + 49) = *(p + 1);
					p += 2;
				}
			}
		}
		else{
			for(int i = 0; i < datH; i++){
				p = pBuf + i * 48;
				for(int j = byteW - 1; j >= 0; j--){
					uint8_t dat = addr[i * srcW + j];
					*p = expandW[dat >> 4];
					*(p +  1) = expandW[dat & 0x0f];
					p += 2;
				}
			}
		}
	}
	else{
		if(th == 2){
			for(int i = 0; i < datH; i++){
				p = pBuf + (2 * i) * 48;
				for(int j = byteW - 1; j >= 0; j--){
					*p = addr[i * srcW + j];
					*(p + 48) = *p;
					p += 1;
				}
			}
		}
		else{
			for(int i = 0; i < datH; i++){
				p = pBuf + i * 48;
				for(int j = byteW - 1; j >= 0; j--){
					*p = addr[srcW * i + j];
					p += 1;
				}
			}
		}
	}

	AddItemFont(pBuf, 48, w, h);
}

bool Decode::GetDat(uint8_t& buf)
{
	if(modeSample){
		modeSample = iSample.Get(buf);
		return true;
	}
	return pRcvBuf->Get(buf);
}

void Decode::Worker()
{
	Delay(100);

	std::cout << "decode" << std::endl;

	int len = 0;
	int codeType = NONE_CODE;
	uint8_t dat[8];
	uint8_t buf;

	modeSample = false;

	while(true){
		//Delay(1);
		//vTaskDelay(pdMS_TO_TICKS(2));
		//sleep_us(1); //なくても動く
		if(!gpio_get(GPIO_03_DPSW4)){
			if(!modeSample){
				int c = 0;
				while(!gpio_get(GPIO_22_FEED)){
					Delay(1);
					c++;
					if(c > 50) break;
				}
				if(c > 50){
					iSample.Start();
					modeSample = true;
				}
			}
		}
		else{
			if(!gpio_get(GPIO_22_FEED)){
				CheckArea(1);
				SetCr(); 
			}
		}

		if(!GetDat(buf)){
			Delay(1);
			continue;
		}

		dat[len] = buf;
		len += 1;

		if(codeType == NONE_CODE){
			codeType = CheckCodeType(buf);
		}

		if(codeType == CODE_LF){
			SetSndBuf();
		}
		else if(codeType == RAW_CODE){
			//pSndBuf->SetCr(datH); // 処理がおかしい
			if((buf == 0x0a) || (buf == 0x0d)){
				SetSndBuf();
			}
		}
		else if(codeType == CODE_TEST){
			if(len < 2) continue;
			Test(dat, len);
		}

		// フォント処理
		else if(codeType == ANK_CODE){
			CodeAnk(dat);
		}
		else if(codeType == UTF8_CODE3){
			if(len < 3) continue;
			CodeUtf8_3(dat);
		}
		else if(codeType == UTF8_CODE2){
			if(len < 2) continue;
			CodeUtf8_2(dat);
		}

		// コマンド処理
		else if(codeType == CODE0e){
			conf.fontWidthDouble = true;
		}
		else if(codeType == CODE14){
			conf.fontWidthDouble = false;
		}
		else if(codeType == CODE12){
			if(len < 3) continue;
			Code_12(dat, len);
		}
		else if(codeType == CODE18){
			if(len < 2) continue;
			Code_18(dat, len);
		}
		else if(codeType == CODE1b){
			if(len < 2) continue;
			Code_1b(dat, len);
		}
		else if(codeType == CODE1c){
			if(len < 2) continue;
			Code_1c(dat, len);
		}
		else if(codeType == CODE1d){
			if(len < 2) continue;
			Code_1d(dat, len);
		}

		len = 0;
		codeType = NONE_CODE;
	}
}

uint8_t* Decode::Receive(uint8_t*& pBuf, int len)
{
	int l = 0;
	uint8_t buf;

	pBuf = new uint8_t[len];

	while(l < len){
		Delay(1);
		//if(!pRcvBuf->Get(buf)){
		if(!GetDat(buf)){
		//	Delay(1);
			continue;
		}

		pBuf[l] = buf;
		l += 1;
	}

	return nullptr;
}

int Decode::Receive(uint8_t*& pBuf)
{
	int l = 0;
	uint8_t buf;
	int len = 256;

	pBuf = new uint8_t[len];

	while(l < len){
		Delay(1);
		//if(!pRcvBuf->Get(buf)){
		if(!GetDat(buf)){
		//	Delay(1);
			continue;
		}

		if(buf == 0) break;
		pBuf[l] = buf;
		l += 1;
	}

	return l;
}

uint8_t* Decode::Code_12(uint8_t* dat, int len)
{
	switch(static_cast<int>(dat[1])){
		case 0x53:
			if(dat[2] == static_cast<int>(KanjiFontSize::size16x16)){
				conf.kanjiFontSize = KanjiFontSize::size16x16;
			}
			else{
				conf.kanjiFontSize = KanjiFontSize::size24x24;
			}
			break;	
	}

	return nullptr;
}

uint8_t* Decode::Code_18(uint8_t* dat, int len)
{
	// バッファのクリア
	
	bool partial = false;
	int cutmode = static_cast<int>(dat[1]);
	if(cutmode) partial = true;

	SetSndBuf();

	CheckArea(112);
	SetCr(); 
	
	CheckArea(1);
	pSndBuf->SetCut(partial);

	return nullptr;
}

uint8_t* Decode::Code_1b(uint8_t* dat, int len)
{
	// len = 2;
	uint8_t* pBuf = nullptr;

	switch(static_cast<int>(dat[1])){
		case 0x20: // 文字間スペース設定
			Receive(pBuf, 1);
			conf.charSpace = pBuf[0];
			break;
		case 0x33: // 行間設定
			Receive(pBuf, 1);
			conf.lineSpace = pBuf[0];
			break;
		case 0x40: // 初期化
			break;
		case 0x49: // 印字方向設定
			Receive(pBuf, 1);
			conf.lister = !(pBuf[0] & 0x0f);
			break;
		case 0x4a: // 紙送り
			SetSndBuf();

			Receive(pBuf, 1);
			CheckArea(pBuf[0]);
			//SetSndBuf();
			SetCr(); 
			break;
		case 0x4c: // ラージフォント
			Receive(pBuf, 1);
			conf.largeFont = pBuf[0] & 0x0f;
			break;
		case 0x4e: // フォント高さ２倍
		case 0x77:
			Receive(pBuf, 1);
			conf.fontHeightDouble = pBuf[0] & 0x0f;
			break;
		case 0x57: // フォント幅２倍
			Receive(pBuf, 1);
			conf.fontWidthDouble = pBuf[0] & 0x0f;
			break;
		case 0x0e: // フォント幅２倍指定
			conf.fontWidthDouble = true;
			break;
		case 0x0f: // フォント幅２倍解除
			conf.fontWidthDouble = false;
			break;
		case 0x68: // ANKフォント設定
			Receive(pBuf, 1);

			if(pBuf[0] == static_cast<int>(AnkFontSize::size8x16)){
				conf.ankFontSize = AnkFontSize::size8x16;
			}
			else if(pBuf[0] == static_cast<int>(AnkFontSize::size12x24)){
				conf.ankFontSize = AnkFontSize::size12x24;
			}
			else if(pBuf[0] == static_cast<int>(AnkFontSize::size16x16))
				conf.ankFontSize = AnkFontSize::size16x16;
			else if(pBuf[0] == static_cast<int>(AnkFontSize::size24x24))
				conf.ankFontSize = AnkFontSize::size24x24;
			else{
				conf.ankFontSize = AnkFontSize::size12x24;
			}

			break;
		case 0x6c: // プリンタ位置設定
			Receive(pBuf, 1);
			pSndBuf->SetColSpace(static_cast<int>(pBuf[0]));
			break;
		case 0x73: // スクリプトの設定
			break;
		default:
			std::cout << "unknown command (hex): " << std::hex << dat[1] << std::endl;
	}

	delete []pBuf;
	return nullptr;
}

uint8_t* Decode::Code_1c(uint8_t* dat, int len)
{
	// len = 4?;
	uint8_t* pBuf = nullptr;

	switch(static_cast<int>(dat[1])){
		case 0x2a: // ビットマップの印字
			Receive(pBuf, 3);
			CmdBmp(pBuf);
			break;
		case 0x57: // ４倍サイズ設定
			Receive(pBuf, 1);
			conf.quadrupleFont = pBuf[0] & 0x0f;
			break;
		case 0x0e: // フォント幅２倍指定
			conf.fontWidthDouble = true;
			break;
		case 0x14: // フォント幅２倍解除
			conf.fontWidthDouble = false;
			break;
		case 0x65: // 拡大設定
			Receive(pBuf, 2);
			conf.fontHeightRate = pBuf[0] & 0x0f;
			if(conf.fontHeightRate == 0) conf.fontHeightRate = 1;
			else if(conf.fontHeightRate > 4) conf.fontHeightRate = 1;
			conf.fontWidthRate = pBuf[1] & 0x0f;
			if(conf.fontWidthRate == 0) conf.fontWidthRate = 1;
			else if(conf.fontWidthRate > 4) conf.fontWidthRate = 1;
			break;
	}

	delete []pBuf;
	return nullptr;
}

uint8_t* Decode::Code_1d(uint8_t* dat, int len)
{
	// len = 2;
	uint8_t* pBuf = nullptr;
	uint8_t mode;

	switch(static_cast<int>(dat[1])){
		case 0x68: // バーコードの高さ設定
			Receive(pBuf, 1);
			conf.barcodeH = pBuf[0];
			if(conf.barcodeH > 0x60) conf.barcodeH = 0x60;
			break;
		case 0x6b: // バーコードの印字
			CmdBarcode(dat);
			break;
		case 0x77: // バーコードの幅設定
			break;
		case 0x78: // QRコードの印字
			Receive(pBuf, 2);
			GenQR(pBuf);
			break;
	}

	delete []pBuf;
	return nullptr;
}

uint8_t* Decode::Test(uint8_t* dat, int len)
{
	uint8_t* pBuf = nullptr;
	int l = 0;

	switch(static_cast<int>(dat[1])){
		case 0x01:
			Receive(pBuf, 1);
			conf.align = pBuf[0];
			break;
		case 0x02:
			Receive(pBuf, 1);
			conf.darkness = pBuf[0];
			break;
		case 0x03:
			break;
		case 0x04:
			l = Receive(pBuf);
			GenDM(pBuf, l);
			break;
		case 't':
			KanjiDump();
			break;
		case 's':
			iSample.Start();
			modeSample = true;
			break;
		case 'l':
			uint8_t* p = new uint8_t[48*884];
			memcpy(p, IIFES_bmp, 48*884);
			AddItem(p, 48, 384, 884);
			break;
	}

	delete []pBuf;
	return nullptr;
}

uint8_t* Decode::CodeAnk(uint8_t* dat)
{
	uint8_t* addr;

	if(conf.ankFontSize == AnkFontSize::size8x16){
		addr = iCg.Ank_RomAddr16(dat[0]);

		SetBufFont(addr +1, 2, 8, 16);
	}
	else{
		addr = iCg.Ank_RomAddr24(dat[0]);

		// 分割して処理して、間にcharSpaceを入れると、
		// スキマができると思っていたが、
		// ビットマップの印字までもくずれてしまう。
		// 意味がわからない。
		//SetBufFont(addr +1, 2, 8, 24);
		//SetBufFont(addr +0, 2, 4, 24);
		SetBufFont2(addr +0, 2, 12, 24);
	}

	return nullptr;
}

uint8_t* Decode::CodeHKana(uint16_t index)
{
	uint8_t* addr;

	if(conf.kanjiFontSize == KanjiFontSize::size16x16){
		addr = iCg.Hankana_RomAddr16(index);
		//SetBufFont(addr, 2, 8, 16);
		SetBufFont(addr, 2, 8, 8);
	}
	else{
		addr = iCg.Hankana_RomAddr24(index);
		SetBufFont(addr, 2, 12, 24);
	}

	return nullptr;
}

uint8_t* Decode::CodeUtf8_3(uint8_t* dat)
{
	if(dat[0] == 0xef){
		uint16_t index = (dat[1] << 8);
		index |= dat[2];

		index -= 0xbda0;
		if(index <= 0x1f){ // 0xefbda0..0xefbdbf
			return CodeHKana(index);
		}
		if((0xe0 <= index) && (index <= 0xff)){ // 0xefbe80..0xefbe9f
			return CodeHKana(index - 0xc0);
		}
	}

	uint8_t* addr = iCg.Utf8_RomAddr_3(dat);

	if(conf.kanjiFontSize == KanjiFontSize::size16x16){
		SetBufFont(addr + 96, 2, 16, 16);
	}
	else{
		SetBufFont(addr, 4, 24, 24);
	}

	return nullptr;
}

uint8_t* Decode::CodeUtf8_2(uint8_t* dat)
{
	uint8_t* addr = iCg.Utf8_RomAddr_3(dat);

	if(conf.kanjiFontSize == KanjiFontSize::size16x16){
		SetBufFont(addr + 96, 2, 16, 16);
	}
	else{
		SetBufFont(addr, 4, 24, 24);
	}

	return nullptr;
}

void Decode::CmdBarcode(uint8_t* rd)
{
	uint8_t* pBuf = nullptr;
	RowBits rb;
	Barcode bc(rb);

	Receive(pBuf, 1);
	int type = static_cast<int>(pBuf[0]);
	delete []pBuf;
	pBuf = nullptr;
	int bitW = 0;
	int len;

	switch(type){
		case 0x30: // UPC-A
			Receive(pBuf, 11);
			bitW = bc.GenUpcA(pBuf, 11);
			break;
		case 0x32: // JAN13
			Receive(pBuf, 12);
			bitW = bc.GenJan13(pBuf, 12);
			break;
		case 0x33: // JAN8
			Receive(pBuf, 7);
			bitW = bc.GenJan8(pBuf, 7);
			break;
		case 0x34: // CODE39 長さ可変
			// C/Dあり
			// スタート/ストップの * 不要
			len = Receive(pBuf);
			bitW = bc.GenCode39(pBuf, len);
			break;
		case 0x35: // ITF 長さ可変(偶数桁のみ可) 13桁＋チェック固定？
			// C/Dなし
			len = Receive(pBuf);
			bitW = bc.GenItf(pBuf, len);
			break;
		case 0x36: // NW7 長さ可変
			// C/Dなし
			// スタート/ストップの * 必要
			len = Receive(pBuf);
			bitW = bc.GenNw7(pBuf, len);
			break;
	}
	delete []pBuf;
	if(bitW == 0) return;

	int line = conf.barcodeH;
	pBuf = new uint8_t[48 * line];

	for(int i = 0; i < line; i++){
		for(int j = 0; j < 48; j++)
			pBuf[i*48 + j] = rb.dat[j];
	}
	
	AddItem(pBuf, 48, bitW * 2, line);
}

void Decode::CmdBmp2(uint8_t* rd)
{
	uint8_t buf;

	int wBit = static_cast<int>(rd[0]) * 256 + static_cast<int>(rd[1]);
	int line = static_cast<int>(rd[2]) * 256 + static_cast<int>(rd[3]);
	uint8_t* pBuf = new uint8_t[48 * line];

	int wByte = (wBit + 7) / 8;
	wByte = (wByte + 3) & 0xfc;

	for(int i = 0; i < line; i++){
		int n = 0;
		uint8_t* p = pBuf + (48 * i);

		while(true){
			if(!pRcvBuf->Get(buf)){
				Delay(1);
				continue;
			}

			p[n] = buf;
			n += 1;
			if(n == wByte) break;
		}
	}

	AddItem(pBuf, 48, wBit, line, true);
}

void Decode::CmdBmp(uint8_t* rd)
{
	bool regist = false;
	bool print = false;
	int mode = static_cast<int>(rd[0]);
	int line = static_cast<int>(rd[1]) * 256 + static_cast<int>(rd[2]);
	uint8_t buf;
	uint8_t pBuf[48];

	switch(mode){
		case 0x61:
			return CmdRegBmp(line);
		case 0x62:
			regist = true;
			break;
		case 0x63:
			print = true;
			regist = true;
			break;
		case 0x64:
			print = true;
			regist = true;
			break;
		case 0x65:
			print = true;
			break;
	}

	if(regist){ 
		if(line > 480) imgLine = 480;
		else imgLine = line;
	}

	for(int i = 0; i < line; i++){
		int n = 0;

		while(true){
			if(!pRcvBuf->Get(buf)){
				Delay(1);
				//sleep_us(1);
				continue;
			}

			pBuf[n] = buf;
			n += 1;
			if(n == 48){
				if(regist && (i < imgLine)) memcpy(imgBuf + 48*i, pBuf, 48);
				if(print) SetSndBufDirect(pBuf, 48, 384, 1, true);
				break;
			}
		}
	}
}

void Decode::CmdRegBmp(int line)
{
	for(int i = 0; i < imgLine; i++){
		SetSndBufDirect(imgBuf + 48*i, 48, 384, 1, true);
	}
}

void Decode::CmdBmpPool(uint8_t* rd)
{
	uint8_t buf;

	int line = static_cast<int>(rd[0]) * 256 + static_cast<int>(rd[1]);
	uint8_t* pBuf = new uint8_t[48 * line];

	for(int i = 0; i < line; i++){
		int n = 0;
		uint8_t* p = pBuf + (48 * i);

		while(true){
			if(!pRcvBuf->Get(buf)){
				Delay(1);
				continue;
			}

			p[n] = buf;
			n += 1;
			if(n == 48){
				//SetBufDot(dat, 48, 1, true);
				break;
			}
		}
	}

	AddItem(pBuf, 48, 384, line, true);
}

void Decode::KanjiDump()
{
	uint8_t* addr = nullptr;
	//int testCnt = 33;
	int testCnt = 0;
	int cnt = 33;
	int testCnt1 = 2965;
	int testCntAll = 8190;
	//int testCntUb = testCnt1/10 + 3;
	int testCntUb = 50;

	int codeType = UTF8_CODE3;

	auto chkDat = [](uint8_t* addr)
	{
		addr += 96;
		for(int i = 0; i < 16; i++){
			if(*addr) return true;
			addr += 1;
		}
		return false;
	};

	while(true){
		addr = iCg.GetKromAddr(cnt);
		if(chkDat(addr)){
			if(conf.kanjiFontSize == KanjiFontSize::size16x16){
				SetBufFont(addr + 96, 2, 16, 16);
			}
			else{
				SetBufFont(addr, 4, 24, 24);
			}
			
			testCnt += 1;
			if(testCnt >= testCntUb) return;
		}

		cnt += 1;
		if(cnt > testCntAll) return;
	}	
}

int Decode::GenQR(uint8_t* dat)
{
	static CQR_Encode iQR;

	int errLv = static_cast<int>(dat[0]);
	int len = static_cast<int>(dat[1]);

	uint8_t* qrStr;
	Receive(qrStr, len);

	bool ret = iQR.EncodeData(
		QR_LEVEL_H,		//	int nLevel
		0,				//	int nVersion
		true,			//	BOOL bAutoExtent
		-1,				//	int nMaskingNo
		reinterpret_cast<char*>(qrStr),			//	LPCSTR lpsSource
		len				//	int ncSource
	);

	delete []qrStr;

	if (!ret) return -1;

	uint8_t bPos;

	int rate = 1;
	if (iQR.m_nSymbleSize <= 50) rate = 4;
	else if (iQR.m_nSymbleSize <= 100) rate = 4;
	else rate = 4;
	rate = 3;

	int bitmapSize = iQR.m_nSymbleSize * rate;
	uint8_t* pBuf = new uint8_t[48 * bitmapSize];

	for (int j = 0; j < iQR.m_nSymbleSize; ++j) {
		uint8_t* p = pBuf + (j * rate * 48);

		for(int k = 0; k < 48; k++){
			for (int r = 0; r < rate; r++) {
				p[r*48 + k] = 0;
			}
		}
		bPos = 0;

		for (int i = 0; i < iQR.m_nSymbleSize; ++i) {
			if (iQR.m_byModuleData[i][j]) {
				for (int k = 0; k < rate; k++) {
					uint8_t d = ((uint8_t)0x80 >> (bPos % 8));
					for (int r = 0; r < rate; r++) {
						p[r*48 + bPos / 8] |= d;
					}
					bPos += 1;
				}
			}
			else bPos += rate;
		}
	}

	AddItem(pBuf, 48, bitmapSize, bitmapSize); // addr, datW, datH

	return 0;
}

int Decode::GenDM(uint8_t* qrStr, size_t len)
{
	auto set = [&](uint8_t* p, int w, int h){
		uint8_t* pBuf = new uint8_t[48 * h];
		uint8_t bPos;

		for (int j = 0; j < h; j+=1) {
			for(int k = 0; k < 48; k++){
				pBuf[j*48 + k] = 0;
			}
			bPos = 0;

			for (int i = 0; i < w; i+=1) {
				//if(p[j*w + i]){
				if(p[(j*w + i)*1] == 0){
					pBuf[j*48 + bPos / 8] |= ((uint8_t)0x80 >> (bPos % 8));
				}
				bPos += 1;
			}
		}

		AddItem(pBuf, 48, w, h); // addr, datW, datH
	};

	size_t	width, height, bytesPerPixel;
	//unsigned char	str[] = "30Q324343430794<OQQ";
	//unsigned char str[] = u8"https://www.datamatrix.co.jp/";
	unsigned char* str = qrStr;
	unsigned char *pxl;
	DmtxEncode *enc;

	enc = dmtxEncodeCreate();
	dmtxEncodeSetProp(enc, DmtxPropPixelPacking, DmtxPack8bppK);
	dmtxEncodeSetProp(enc, DmtxPropModuleSize, 4);

	dmtxEncodeDataMatrix(enc, strlen((const char *)str), str);
	width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

	pxl = (unsigned char *)malloc(width * height * bytesPerPixel);
	assert(pxl != NULL);
	memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);

	dmtxEncodeDestroy(&enc);

	set(pxl, width, height);

	free(pxl);

	return 0;
}
