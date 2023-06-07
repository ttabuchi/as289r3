#include <iostream>
#include <FreeRTOS.h>
#include <task.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "iodefine.h"
#include "rcvbuf.h"
#include "decode.h"
#include "sndbuf.h"
#include "printer.h"

RcvBuf* spRcvBuf;

void OnRx()
{
	//while(!spRcvBuf->IsFull() && uart_is_readable(uart0)){
	if(!spRcvBuf->IsFull() && uart_is_readable(uart0)){
		uint8_t ch = uart_getc(uart0);
		spRcvBuf->Set(ch);
	}
}

void InitSerial(RcvBuf* pRcvBuf)
{
	spRcvBuf = pRcvBuf;
	int baud = 115200;

	if(gpio_get(GPIO_00_DPSW1)) baud = 9600;
	uart_init(uart0, baud);

	gpio_set_function(GPIO_17_UART_RX, GPIO_FUNC_UART);

	irq_set_exclusive_handler(UART0_IRQ, OnRx);
	irq_set_enabled(UART0_IRQ, true);
	uart_set_irq_enables(uart0, true, false); // IRQ-RTX enable
}

int main()
{
	SndBuf iSndBuf;
	RcvBuf iRcvBuf;
	
	stdio_init_all();
	sleep_us(1000*1000);
	
	//-------------------
	// led
	gpio_init(GPIO_25_LED);
	gpio_set_dir(GPIO_25_LED, GPIO_OUT);

	//-------------------
	// feed-dw
	gpio_init(GPIO_22_FEED);
	gpio_set_dir(GPIO_22_FEED, GPIO_IN);
	gpio_pull_up(GPIO_22_FEED);

	//-------------------
	// dpsw
	gpio_init_mask(DSW_MASK);
	gpio_set_dir_in_masked(DSW_MASK);
	for(auto p: {
			GPIO_00_DPSW1,
			GPIO_01_DPSW2,
			GPIO_02_DPSW3,
			GPIO_03_DPSW4,
		}){
		gpio_pull_up(p);
		//sleep_us(1);
	}

	Decode iDecode(&iRcvBuf, &iSndBuf);
	
	Printer iPrinter;
	iPrinter.Init(&iSndBuf);

	gpio_put(GPIO_25_LED, 1);

	InitSerial(&iRcvBuf);
	iRcvBuf.SetAlertEmptySize(64);

	vTaskStartScheduler();

	while(true);
	return 0;
}
