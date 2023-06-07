#include "barcode.h"

int Barcode::GenJan13(const uint8_t* dat, size_t len)
{
	int bPos = 0;
	int rate = 2;
	int code;
	const uint8_t nil = 0x00;

	rb.Init();
	
	/*
	倍率 	0.8(x2) 	1.0(x3) 	1.2(x4) 	2.0(x5)
	ナローバー幅 0.264mm 0.33mm 0.396mm 0.66mm
	バーコードの長さ 29.83mm 37.29mm 44.75mm 74.58mm
	バーコードの高さ 18.29mm 22.86mm 27.43mm 45.72mm
	*/

	// odd: 0, even: 1 に注意
	code = static_cast<uint32_t>(dat[0] & 0x0f);
	int prefix = janPrefixTable[code];

	// left margin
	rb.Set(&nil, 8);
	rb.Set(&nil, 3);

	// left guid bar 
	rb.Set(&(lbar), 8);

	// left data
	for(int i = 1; i < 7; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);

		if(((uint8_t)0x80 >> (i-1)) & prefix){
			rb.Set(&(le[code]), 7);
		}
		else{
			rb.Set(&(lo[code]), 7);
		}
	}
	
	// center bar
	rb.Set(&(cbar), 5);

	// right data
	for(int i = 7; i < 12; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);
		rb.Set(&(re[code]), 7);
	}

	// check digit
	int chk = ChkMod103(dat, len) & 0x0f;
	rb.Set(&(re[chk]), 7);
	
	// right guid bar 
	rb.Set(&(rbar), 8);
	
	// right margin
	rb.Set(&nil, 7);

	return 123;
}

int Barcode::GenJan8(const uint8_t* dat, size_t len)
{
	int bPos = 0;
	int rate = 2;
	int code;
	const uint8_t nil = 0x00;

	rb.Init();
	
	// left margin
	rb.Set(&nil, 8);
	rb.Set(&nil, 3);

	// left guid bar 
	rb.Set(&(lbar), 8);

	// left data
	for(int i = 0; i < 4; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);
		rb.Set(&(lo[code]), 7);
	}
	
	// center bar
	rb.Set(&(cbar), 5);

	// right data
	for(int i = 4; i < 7; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);
		rb.Set(&(re[code]), 7);
	}

	// check digit
	int chk = ChkMod103(dat, len) & 0x0f;
	rb.Set(&(re[chk]), 7);
	
	// right guid bar 
	rb.Set(&(rbar), 8);
	
	// right margin
	rb.Set(&nil, 7);

	return 95;
}

int Barcode::GenUpcA(const uint8_t* dat, size_t len)
{
	int bPos = 0;
	int rate = 2;
	int code;
	const uint8_t nil = 0x00;

	rb.Init();
	
	// left margin
	rb.Set(&nil, 8);
	rb.Set(&nil, 3);

	// left guid bar 
	rb.Set(&(lbar), 8);

	// left data
	for(int i = 0; i < 6; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);
		rb.Set(&(lo[code]), 7);
	}
	
	// center bar
	rb.Set(&(cbar), 5);

	// right data
	for(int i = 6; i < 11; i++){
		code = static_cast<uint32_t>(dat[i] & 0x0f);
		rb.Set(&(re[code]), 7);
	}

	// check digit
	int chk = ChkMod103(dat, len) & 0x0f;
	rb.Set(&(re[chk]), 7);
	
	// right guid bar 
	rb.Set(&(rbar), 8);
	
	// right margin
	rb.Set(&nil, 7);

	return 123;
}

int Barcode::GenItf(const uint8_t* dat, size_t len)
{
	const uint16_t start = (0x00a0<<1);	// 0000 0000 101- ----
	const uint16_t stop = 0xd000;	// 1101 0000 000- ----

	bool odd = len & 1;
	int w = 0;
	rb.Init();

	int chk = ChkMod103(dat, len) & 0x0f;
	
	//rb.Set(reinterpret_cast<const uint8_t*>(&start), 11);
	rb.Set16(reinterpret_cast<const uint16_t*>(&start), 11);
	w += 11;

	int bPos;
	uint16_t buf;
	uint8_t* pb;
	uint8_t* pw;
	int n;

	for(int k = 0; k < (len+1)/2; k++){
		buf = 0;
		bPos = 0;
		pb = const_cast<uint8_t*>(itf[dat[2 * k + 0] & 0x0f]);
		if((k == (len+1)/2-1) && odd) pw = const_cast<uint8_t*>(itf[chk]);
		else pw = const_cast<uint8_t*>(itf[dat[2 * k + 1] & 0x0f]);

		for(int j = 0; j < 5; j++){
			n = pb[j];
			for(int i = 0; i < n; i++){
				buf |= (0x8000 >> bPos);
				bPos += 1;
			}
			
			n = pw[j];
			bPos += n;
		}

		//rb.Set(reinterpret_cast<const uint8_t*>(&buf), 14);
		rb.Set16(reinterpret_cast<const uint16_t*>(&buf), 14);
		w += 14;
	}

	//rb.Set(reinterpret_cast<const uint8_t*>(&stop), 11);
	rb.Set16(reinterpret_cast<const uint16_t*>(&stop), 11);
	w += 11;

	return 2 * w;
}

int Barcode::GenNw7(const uint8_t* dat, size_t len)
{
	const uint16_t barN[10] = {
		0xa980, // 0 1010 1001 1
		0xac80, // 1 1010 1100 1
		0xa580, // 2 1010 0101 1
		0xca80, // 3 1100 1010 1
		0xb480, // 4 1011 0100 1
		0xd480, // 5 1101 0100 1
		0x9580, // 6 1001 0101 1
		0x9680, // 7 1001 0110 1
		0x9a80, // 8 1001 1010 1
		0xd280, // 9 1101 0010 1
	};

	const uint16_t barF[6] = {
		0xa680, // - 1010 0110 1
		0xb280, // $ 1011 0010 1
		0xd6c0, // : 1101 0110 11
		0xdac0, // / 1101 1010 11
		0xdb40, // . 1101 1011 01
		0xb6c0, // + 1011 0110 11
	};
	const uint16_t ss[4] = {
		0xb240, // A 1011 0010 01
		0x92c0, // B 1001 0010 11
		0xa4c0, // C 1010 0100 11
		0xa640, // D 1010 0110 01
	};

	int w = 0;
	rb.Init();

	rb.Set16(&ss[0], 10);
	w += 10;
	rb.SetDat2(0x00, 1);
	w += 1;

	for(int i = 0; i < len; i++){
		int n = dat[i];
		if(('0' <= n) && (n <= '9')){
			rb.Set16(&barN[n & 0x0f], 9);
			w += 9;
		}
		else if(n == '-'){
			rb.Set16(&barF[0], 10);
			w += 10;
		}
		else if(n == '$'){
			rb.Set16(&barF[1], 10);
			w += 10;
		}
		else if(n == ':'){
			rb.Set16(&barF[2], 10);
			w += 10;
		}
		else if(n == '/'){
			rb.Set16(&barF[3], 10);
			w += 10;
		}
		else if(n == '.'){
			rb.Set16(&barF[4], 10);
			w += 10;
		}
		else if(n == '+'){
			rb.Set16(&barF[5], 10);
			w += 10;
		}
		else return 0;

		rb.SetDat2(0x00, 1);
		w += 1;
	}

	rb.Set16(&ss[0], 10);
	w += 10;

	return 2 * w;
}

int Barcode::GenCode39(const uint8_t* dat, size_t len)
{
	const uint16_t ss = 0x96d0;// * 1001 0110 1101
	const uint16_t bar[10] = {
		0xa6d0, // 0 1010 0110 1101
		0xd2b0, // 1 1101 0010 1011
		0xb2b0, // 2 1011 0010 1011
		0xd950, // 3 1101 1001 0101
		0xa6b0, // 4 1010 0110 1011
		0xd350, // 5 1101 0011 0101
		0xb350, // 6 1011 0011 0101
		0xa5b0, // 7 1010 0101 1011
		0xd2d0, // 8 1101 0010 1101
		0xb2d0, // 9 1011 0010 1101
	};
	const uint16_t barA[26] = {
		0xd4b0, // A 1101 0100 1011
		0xb4b0, // B 1011 0100 1011
		0xda50, // C 1101 1010 0101
		0xacb0, // D 1010 1100 1011
		0xd650, // E 1101 0110 0101
		0xb650, // F 1011 0110 0101
		0xa9b0, // G 1010 1001 1011
		0xd4d0, // H 1101 0100 1101
		0xb4d0, // I 1011 0100 1101
		0xacd0, // J 1010 1100 1101
		0xd530, // K 1101 0101 0011
		0xb530, // L 1011 0101 0011
		0xda90, // M 1101 1010 1001
		0xad30, // N 1010 1101 0011
		0xd690, // O 1101 0110 1001
		0xb690, // P 1011 0110 1001
		0xab30, // Q 1010 1011 0011
		0xd590, // R 1101 0101 1001
		0xb590, // S 1011 0101 1001
		0xad90, // T 1010 1101 1001
		0xcab0, // U 1100 1010 1011
		0x9ab0, // V 1001 1010 1011
		0xcd50, // W 1100 1101 0101
		0x96b0, // X 1001 0110 1011
		0xcb50, // Y 1100 1011 0101
		0x9b50, // Z 1001 1011 0101
	};
	const uint16_t barF[7] = {
		0x95b0, // - 1001 0101 1011
		0xcad0, // . 1100 1010 1101
		0x9ad0, //   1001 1010 1101
		0x9250, // $ 1001 0010 0101
		0x9290, // / 1001 0010 1001
		0x9490, // + 1001 0100 1001
		0xc490, // % 1010 0100 1001
	};

	//int chk = ChkMod43(dat, len);

	int w = 0;
	rb.Init();

	rb.SetDat2(0x00, 4);
	w += 4;
	rb.Set16(&ss, 12);
	w += 12;
	rb.SetDat2(0x00, 1);
	w += 1;

	for(int i = 0; i < len; i++){
		int n = dat[i];
		if(('0' <= n) && (n <= '9')){
			rb.Set16(&bar[n & 0x0f], 12);
		}
		else if(('A' <= n) && (n <= 'Z')){
			rb.Set16(&barA[n - 'A'], 12);
		}
		else if(n == '-'){
			rb.Set16(&barF[0], 12);
		}
		else if(n == '.'){
			rb.Set16(&barF[1], 12);
		}
		else if(n == ' '){
			rb.Set16(&barF[2], 12);
		}
		else if(n == '$'){
			rb.Set16(&barF[3], 12);
		}
		else if(n == '/'){
			rb.Set16(&barF[4], 12);
		}
		else if(n == '+'){
			rb.Set16(&barF[5], 12);
		}
		else if(n == '%'){
			rb.Set16(&barF[6], 12);
		}
		else return 0;

		w += 12;
		rb.SetDat2(0x00, 1);
		w += 1;
	}

	rb.Set16(&ss, 12);
	w += 12;
	rb.SetDat2(0x00, 8);
	w += 8;

	return 2 * w;
}
