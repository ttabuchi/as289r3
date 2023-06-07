#include "cg.h"
#include "krom.h"
#include "Cg12x24d.h"
#include "unicode_tbl.h"
#include "hankana.h"

uint8_t ank_table[1] = {0, };
uint8_t han_table[1] = {0, };

uint16_t Cg::Utf8_Utf16_2(uint8_t* dat)
{
	uint16_t code = 0;
	code = (dat[0] & 0x1f) << 6;
	code += dat[1] & 0x3f;
	return code;
}

uint16_t Cg::Utf8_Utf16_3(uint8_t* dat)
{
/*
「半角カナ」と呼ばれる文字はU+FF61〜U+FF9F(いわゆる半角のカナ記号を含む)に存在しますので、
UTF-8表現された場合には3バイト必要となります。
*/
	uint16_t code = 0;
	code = dat[0] << 12;
	code += (dat[1] & 0x3f) << 6;
	code += (dat[2] & 0x3f);
	return code;
}

uint16_t Cg::Utf16_Sjis(uint16_t u_code)
{
	uint16_t uucode = u_code;
	uint16_t key = 0;

	if(u_code < 0xA2)	return(u_code);			// UTF16は0x00A2以上なので、それ未満はそのまま返す

	for(int i = 0; i < 115; i++)				// 以前は114だった。FFE3の文字が印字できないので修正。
	{
		if(uucode < uni_tbl[i])
		{
			// 発見
			if(uni_size_tbl[i] == 0)			// 計算テーブル
			{
				switch(i)
				{
					case 2:
					case 4:		return(u_code + 32782);	break;
					case 3:
					case 5:		return(u_code + 32781);	break;
					case 7:		return(u_code + 32816);	break;
					case 8:		return(u_code + 32817);	break;
					case 9:		return(u_code + 32832);	break;
					case 10:	return(u_code + 32833);	break;
					case 11:	return(u_code + 32834);	break;
					case 19:	return(u_code + 20841);	break;
					case 21:	return(u_code + 21086);	break;
					case 23:	return(u_code + 21151);	break;
					case 24:	return(u_code + 21152);	break;
					case 107:
					case 109:	return(u_code - 31937);	break;
					case 111:	return(u_code - 31936);	break;
					case 113:	return(u_code - 65216);	break;
					default:	return(0);						// Error
				}
			}
			else												// サーチテーブル
			{
				for(int j = 0; j < uni_size_tbl[i]; j++, key++)
				{
					if(uucode == uni_serch_table[key])
					{
						return( (uni_sjis_table[(key * 2)] << 8) + (uni_sjis_table[(key * 2) + 1]) );	// テーブル修正で1増えた。前は6525と6256
					}
				}
				return 0;										// not on the table
			}
		}
		uucode -= uni_tbl[i];
		key += uni_size_tbl[i];
	}
	return 0;  // Not found
}

uint16_t Cg::Sjis_Jis(uint16_t sjisCode)
{
	uint16_t dat1 = (sjisCode >> 8) & 0xff;
	uint16_t dat2 = sjisCode & 0xff;

	dat1 <<= 1;
	dat1 &= 0xff;

	if(dat2 < 0x9f){
		if(dat1 < 0x3f) dat1 += 0x1f;
		else dat1 -= 0x61;
		
		if(dat2 > 0x7e) dat2 -= 0x20;
		else dat2 -= 0x1f;
	}
	else{
		if(dat1 < 0x3f) dat1 += 0x20;
		else dat1 -= 0x60;
		
		dat2 -= 0x7e;
	}

	return (dat1 << 8) | dat2;
}

uint8_t* Cg::Jis_Krom(uint16_t jisCode)
{
	uint32_t kg_cal;
	uint32_t offset;

	kg_cal = (uint32_t)jisCode;

	switch( jisCode & 0x7000 )
	{
		case 0x2000:
			offset = ((kg_cal << 11) & 0x030000)
			+ ((kg_cal <<  5) & 0x00e000)
			+ ((kg_cal <<  6) & 0x0007c0);
			break;					/* set A18=0	*/

		case 0x3000:
		case 0x4000:
			offset = ((kg_cal << 3) & 0x020000)
			+ ((kg_cal << 5) & 0x01e000)
			+ ((kg_cal << 6) & 0x001fc0);
			break;					/* set A18=0	*/

		case 0x5000:
		case 0x6000:
			offset = ((kg_cal << 4) & 0x020000)
			+ ((kg_cal << 5) & 0x01e000)
			+ ((kg_cal << 6) & 0x001fc0)
			+ 0x040000;
			break;					/* set A18=1	*/

		case 0x7000:
			offset = ((kg_cal << 11) & 0x030000)
			+ ((kg_cal <<  5) & 0x00e000)
			+ ((kg_cal <<  6) & 0x0007c0)
			+ 0x040000;
			break;					/* set A18=1	*/
		default:	break;
	}

	return (uint8_t*)krom + 2*offset;
}

// dump用
uint8_t* Cg::GetKromAddr(int n)
{
	return (uint8_t*)krom + 128*n;
}

// 不使用
uint8_t* Cg::Ank_Krom(uint16_t jisCode)
{
	uint32_t kg_cal = (uint32_t)jisCode - 0xa0;
	//ulong kg_cal = (ulong)in_data1- 0xa0;

	uint32_t  addr = (kg_cal << 5) + (kg_cal << 4);

	//addr = (in_data1 - 0x20)*16;
	return ank_table + addr;
}

uint8_t* Cg::Ank_RomAddr16(uint8_t dat)
{
	uint index = dat - 0x20;
	return (uint8_t*)cg8x16d + index*16*2;
}

uint8_t* Cg::Ank_RomAddr24(uint8_t dat)
{
	uint index = dat - 0x20;
	return (uint8_t*)cg12x24d + index*48;
}

uint8_t* Cg::Hankana_RomAddr16(uint16_t index)
{
	return (uint8_t*)hankaku_katakana16 + index * 16;
}

uint8_t* Cg::Hankana_RomAddr24(uint16_t index)
{
	return (uint8_t*)hankaku_katakana24 + index * 48;
}

uint8_t* Cg::Utf8_RomAddr_2(uint8_t* dat)
{
	uint8_t* addr;
	uint16_t code;

	code = Utf8_Utf16_2(dat);
	code = Utf16_Sjis(code);
	code = Sjis_Jis(code);
	addr = Jis_Krom(code);

	return addr;
}

uint8_t* Cg::Utf8_RomAddr_3(uint8_t* dat)
{
	uint8_t* addr;
	uint16_t code;

	code = Utf8_Utf16_3(dat);
	code = Utf16_Sjis(code);
	code = Sjis_Jis(code);
	addr = Jis_Krom(code);

	return addr;
}

/*
void Cg::Worker()
{
	uint16_t jisCode;
	uint16_t sjisCode;
	uint16_t utf16;
	uint8_t* addr;
	//uint8_t* ptrRom;
	bool ed = false;

	static int cnt = 0;
	static uint8_t ar[3];
	bool lf = false;

	while(true){
		if(TaskReady()){
			dat[cnt] = pRcvBuf->Get();
			cnt += 1;

			if(!codeType){
				codeType = CheckCodeType(dat[0]);
			}

			if(codeType == ANK_CODE){
				addr = Ank_Krom(dat[0]);
				cnt = 0;
				codeType = 0;
			}

			if(codeType == UTF8_CODE2){
				if(cnt == 2){
					utf16 = Utf8_Utf16(dat);
					sjisCode = Utf16_Sjis(utf16);
					jisCode = Sjis_Jis(sjisCode);
					addr = Jis_Krom(jisCode);
					cnt = 0;
					SetBuf(addr);
					//Led();
					codeType = 0;
				}
			}
			if(codeType == UTF8_CODE3){
				if(cnt == 3){
					utf16 = Utf8_Utf16(dat);
					sjisCode = Utf16_Sjis(utf16);
					jisCode = Sjis_Jis(sjisCode);
					addr = Jis_Krom(jisCode);
					cnt = 0;
					SetBuf(addr);
					Led();
					codeType = 0;
				}
			}

			// 受信済みなら変換
			vTaskDelay(pdMS_TO_TICKS(5));
			continue;

	//		if(!rcvFull) continue;

			//変換

			// 変換済みなら漢字ロムデータを展開
			if(ed){
			}
		}

		vTaskDelay(pdMS_TO_TICKS(5));
	}
}
*/
