#include "spi.h"

Spi::Spi()
{

}

void Spi::Init(int clockPin, int txPin, uint brate, SndBuf* pSndBuf)
{
	pin.clock = clockPin;
	pin.tx = txPin;
	this->pSndBuf = pSndBuf;

	spi = spi1;
	
	// setup spi
	baud = spi_init(spi, brate);
	
	// mode 0
	spi_set_format(
		spi,
		8,	// number  of bits poer transer
		SPI_CPOL_0,	// 平常時Low
		SPI_CPHA_0,	// 立ち上がりエッジ
		SPI_MSB_FIRST
	);

	// init pins
	gpio_set_function(pin.clock, GPIO_FUNC_SPI);
	gpio_set_function(pin.tx, GPIO_FUNC_SPI);

	// bi_decl の行は、picotool というコンパイル後のバイナリから情報を得るツールで・・・、プログラムの動作の本質とは関係ない様です。
}

void Spi::Write(uint8_t data)
{
	// cs select
	// sleep 1ms
	// write_blocking
	// sleep 1ms
	// cd deselect

	spi_write_blocking(spi, &data, 1);
}

void Spi::SendNull(uint8_t dat)
{
	for(int i = 0; i < 384/8; i++){
		Write(dat);
	}
}

uint Spi::SendLine16(uint16_t* pdat)
{
	//int len = spi_write_blocking(spi, pdat, 48);
	//if(len != 48) std::cout << "■■■spi send =" << len << std::endl;

	for(int i = 0; i < 24; i++)
		spi_write16_blocking(spi, pdat+i, 1);

	return 384000000 / baud;
}

uint Spi::SendLine(uint8_t* pdat)
{
	//int len = spi_write_blocking(spi, pdat, 48);
	//if(len != 48) std::cout << "■■■spi send =" << len << std::endl;

	//for(int i = 0; i < 48; i++){
		// busyは見たことない
		//if(spi_is_writable(spi)) spi_write_blocking(spi, pdat+i, 1);
		//else  busy_wait_us(1);
		//else std::cout << "spi is busy." << std::endl;
	//}

	spi_write_blocking(spi, pdat, 48);
	return 384000000 / baud;
}

void Spi::SendTest(const uint8_t buf)
{
	auto test = [&](){
		for(int i = 0; i < 384/8; i++){
			if(i>7 ) Write(0x00);
			else Write(buf);
		}
	};

	auto test2= [&](){
		for(int i = 0; i < 1; i++){
			Write(0xff);
			Write(0x01);
			Write(0x7f);
			Write(0x03);
			Write(0x3f);
			Write(0x07);
			Write(0x1f);
			Write(0x0f);
		}
		for(int i = 1; i < 6; i++){
			for(int j = 0; j < 8; j++) Write(0x00);
		}
	};

	auto test3= [&](){
		uint8_t dat = 0;
		for(int i = 0; i < 6; i++){
			dat |= (1 << i);
			Write(dat);

			for(int j = 1; j < 8; j++)
				Write(0x00);
		}
	};

	auto test4= [&](){
		uint8_t dat = 0;

		for(int i = 0; i < 2; i++){
			// head-1
			dat = 0x00;
			Write(dat);
			dat = 0xff;
			Write(dat);
			dat = 0xff;
			Write(dat);
			dat = 0xff;
			Write(dat);
			dat = 0xff;
			Write(dat);
			dat = 0x00;
			Write(dat);
			dat = 0x00;
			Write(dat);
			dat = 0x00;
			Write(dat);
		}

		for(int j = 2; j < 6; j++){
			for(int i = 0; i < 8; i++){
				Write(0x00);
			}
		}
	};

	auto test5= [&](uint8_t dat){
		for(int i = 0; i < 48; i++){
			Write(dat);
		}
	};

	static int n = 0;
	static uint8_t dat[] = {0x88, 0x44, 0x22, 0x11, };
	test5(dat[n]);
	n = (n + 1) & 3;
}

