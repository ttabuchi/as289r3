#include "sample.h"

#include <cstring>
#include <cassert>

#define CUT_ENABLE

//std::vector<uint8_t> Sample::dat0 {
//std::string Sample::dat0 =

uint8_t datOld[] =
	u8"\x1b\x20\x01" // 文字間スペース
	u8"\x1b\x33\x04" // 行間スペース
	u8"\x1b\x4e\x30" // 高さ1倍
	u8"\x1b\x57\x30" // 幅1倍
	u8"\x12\x53\x30"
	u8"\x1b\x68\x31" 

	u8"*****************************\n"
	u8" \n"
	u8" \n"

	u8"\x12\x53\x31" // kanji = 16x16
	u8"\x1b\x68\x30" // ank = 8x16

	u8"0123456789\n"
	u8"ABCDEF\n"
	u8"abcdef\n"
	u8"ｱｲｳｴｵｶｷｸｹｺ\n"
	u8" \n"
	u8" \n"

	u8"\x12\x53\x30" // kanji = 24x24
	u8"\x1b\x68\x31" // ank = 12x24

	u8"0123456789\n"
	u8"ABCDEF\n"
	u8"abcdef\n"
	u8"ｱｲｳｴｵｶｷｸｹｺ\n"
	u8" \n"
	u8" \n"
	
	u8"\x12\x53\x31" // kanji = 16x16
	u8"\x1b\x68\x30" // ank = 8x16

	u8"０１２３４５６７８９\n"
	u8"ＡＢＣＤＥＦ\n"
	u8"ａｂｃｄｅｆ\n"
	u8"アイウエオカキクケコ\n"
	u8" \n"
	u8" \n"

	u8"\x12\x53\x30" // kanji = 24x24
	u8"\x1b\x68\x31" // ank = 12x24

	u8"０１２３４５６７８９\n"
	u8"ＡＢＣＤＥＦ\n"
	u8"ＡＢＣＤＥＦ\n"
	u8"ａｂｃｄｅｆ\n"
	u8"アイウエオカキクケコ\n"
	u8" \n"
	u8" \n"
;


uint8_t dat0[] =
	//u8"\x1fl"
	u8"\x1b\x20\x01" // 文字間スペース
	u8"\x1b\x33\x04" // 行間スペース
	u8"\x1b\x4e\x30" // 高さ1倍
	u8"\x1b\x57\x30" // 幅1倍
	u8"\x12\x53\x30" // kanji = 16x16
	u8"\x1b\x68\x31" // ank = 8x16
	u8"\n \nThermal Printer Shield\n \nModel AS-289R3\n \n"		// TEST

	u8"\x1b\x20\x01" // 文字間スペース
	u8"\x1b\x33\x04" // 行間スペース
	u8"\x1b\x4e\x30" // 高さ1倍
	u8"\x1b\x57\x30" // 幅1倍
	u8"\x12\x53\x31" // kanji = 16x16
	u8"\x1b\x68\x30" // ank = 8x16
	u8"Font 8x16\n"
	u8"0123456789\n"
	u8"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
	u8"abcdefghijklmnopqrstuvwxyz\n"
	u8" \nFont 16x16\n"
	u8"あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよわをん\n"
	u8"ぁぃぅぇぉゃゅょ\n"
	u8"アイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨワヲン\n"
	u8"\x1ft"
	u8" \n"
	u8" \n"

	u8"\x1b\x20\x01" // 文字間スペース
	u8"\x1b\x33\x04" // 行間スペース
	u8"\x1b\x4e\x30" // 高さ1倍
	u8"\x1b\x57\x30" // 幅1倍
	u8"\x12\x53\x30" // kanji = 16x16
	u8"\x1b\x68\x31" // ank = 8x16
	u8"Font 12x24\n"
	u8"0123456789\n"
	u8"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
	u8"abcdefghijklmnopqrstuvwxyz\n"
	u8" \nFont 24x24\n"
	u8"あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよわをん\n"
	u8"ぁぃぅぇぉゃゅょ\n"
	u8"アイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨワヲン\n"
	u8"\x1ft"
	u8" \n"
#ifdef CUT_ENABLE
	u8"\x18\x01"
#else
	u8"--------pertial cut--------- \n"
#endif

	u8"*****************************\n"
	u8"Settings and Head Status\n"
	u8"*****************************\n"
	u8" \n"
;

//std::string Sample::dat2 =
//std::vector<uint8_t> Sample::dat2 =
uint8_t dat2[] =
	u8" \n"
	u8"*****************************\n"
	u8"Product Specification\n"
	u8"*****************************\n"
	u8" \n入力電源電圧\n"
	u8"  5〜9V\n"
	u8" \nカッター\n"
	u8"  パーシャルカット／フルカット\n"
	u8" \nインターフェース\n"
	u8"  Arduino Home Factor\n"
	u8"  UART 115200bps or 9600bps\n"
	u8"  3.3V or 5V レベル\n"
	u8"  8Bit NonParity 1Stop\n"
	u8"  UTF-8 or Shift-JIS\n"
	u8" \nフォント\n"
	u8"  ANK JIS160文字\n"
	u8"  第一水準漢字2965文字\n"
	u8"  第二水準漢字3388文字\n"
	u8"  JIS非漢字524文字\n"
	u8"  0-9,A-Zの36文字\n"
	u8"  8x16ドット: ANK\n"
	u8"  12x24ドット: ANK\n"
	u8"  16x16ドット: ANK, 漢字\n"
	u8"  24x24ドット: ANK, 漢字\n"
	u8"  48x96ドット: 0-9 A-Z\n"
	u8" \nバーコード\n"
	u8"  QR\n"

	u8"  UPC-A"
	u8"\x1d\x6b\x30\x01\x02\x03\x04\x05\x06\x07\x08\x09\x00\x01\x00 \n \n" // UPC-A
	u8"  JAN(13)"
	u8"\x1d\x6b\x32\x01\x02\x03\x04\x05\x06\x07\x08\x09\x00\x01\x02\x00 \n \n" // JAN13
	u8"  JAN(8)"
	u8"\x1d\x6b\x33\x01\x02\x03\x04\x05\x06\x07\x00 \n \n" // JAN8
	u8"  3of9(CODE39)"
	u8"\x1d\x6b\x34\x31\x32\x33\x34\x35\x36\x37\x00 \n \n" // CODE39
	//u8"  2of5(ITF)"
	//u8"\x1d\x6b\x35\x31\x32\x33\x34\x35\x36\x37\x00 \n \n" // ITF
	u8"  2of7(NW7)"
	u8"\x1d\x6b\x36\x31\x32\x33\x34\x35\x36\x37\x00 \n \n" // NW7
	u8"\x1d\x78\x00\x17https://www.nada.co.jp/"
	u8"\x1f\x04https://www.nada.co.jp/datamatrix/\x00"
	u8" \n       NADA ELECTRONICS\n"

	u8"\x1fl"

#ifdef CUT_ENABLE
	u8"\x18\x00"
#else
	u8"--------full cut--------- \n"
#endif
;

int Sample::Gen()
{
	/*
	for(auto d: {dat0, dat1, dat2}){
		std::cout << sizeof(d) << std::endl;
		dat.insert(dat.end(), d, d+sizeof(d));
	}
	*/

	//if(dws & 0x02);

//	dat.insert(dat.end(), dat0, dat0+sizeof(dat0));
	//dat.insert(dat.end(), dat1, dat1+sizeof(dat1));
	//dat.insert(dat.end(), dat2, dat2+sizeof(dat2));

	int vh = 10 * Printer::iAd.GetVolt();
	int th = 10 * Printer::iAd.GetTemp();
	uint dsw = gpio_get_all() & DSW_MASK;

	char ver[] = u8"Rom Version: 01.00.00\n";
	char vol[] = u8"Voltage    : ";
	char tmp[] = u8"Thermistor : ";

	char buf[256];
	strcpy(status, ver);
	strcat(status, vol);
	sprintf(buf, u8"%2d.%d V\n", vh / 10, vh % 10);
	strcat(status, buf);
	strcat(status, tmp);
	sprintf(buf, u8"%d.%d ℃\n \n", th / 10, th % 10);
	strcat(status, buf);
	
	char head[]  = u8"       OFF          ON       \n";
	char dsw0T[] = u8"DSW1 ◆9600bps      115200bps\n";
	char dsw0F[] = u8"DSW1   9600bps    ◆115200bps\n";
	char dsw1T[] = u8"DSW2 ◆UTF-8        Shift-JIS\n";
	char dsw1F[] = u8"DSW2   UTF-8      ◆Shift-JIS\n";
	char dsw2T[] = u8"DSW3 ◆None         Cutter   \n";
	char dsw2F[] = u8"DSW3   None       ◆Cutter   \n";
	char dsw3T[] = u8"DSW4 ◆Resrved      Reserved \n";
	char dsw3F[] = u8"DSW4   Resrved    ◆Reserved \n";

	strcat(status, head);

	if(dsw & 1) strcat(status, dsw0T);
	else strcat(status, dsw0F);

	if(dsw & 2) strcat(status, dsw1T);
	else strcat(status, dsw1F);

	if(dsw & 4) strcat(status, dsw2T);
	else strcat(status, dsw2F);

	if(dsw & 8) strcat(status, dsw3T);
	else strcat(status, dsw3F);

	return 0;
}

void Sample::Start()
{
	Gen();

	it = dat.begin();
	mode = 0;
	p = dat0;
	pend = dat0 + sizeof(dat0);
}

void Sample::StartOld()
{
	mode = 0;
	p = datOld;
	pend = datOld + sizeof(datOld);
}

bool Sample::GetOld(uint8_t& c)
{
	c = *p;
	p++;
	
	if(p != pend) return true;

	if(mode == 0){
		p = datOld;
		pend = p + sizeof(datOld);
		return true;
	}

	return false;
}

bool Sample::Get(uint8_t& c)
{
	c = *it;
	c = *p;
	it++;
	p++;
	/*
	if(it == dat.end()){
		mode = false;
		it = dat.begin();
		return false;
	}
	*/
	if(p != pend) return true;

	if(mode == 0){
		mode++;
		p = reinterpret_cast<uint8_t*>(status);
		pend = p + strlen(status);
		return true;
	}
	else if(mode == 1){
		mode++;
		p = dat2;
		pend = dat2 + sizeof(dat2);
		return true;
	}

	return false;
}
