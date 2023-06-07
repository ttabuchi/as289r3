#pragma once

#define CUT_ENABLE

// off, on(low)
#define GPIO_00_DPSW1 0  // 9600bps, 115200bps
#define GPIO_01_DPSW2 1  // UTF-8, SHIFT-JIS
#define GPIO_02_DPSW3 2  // cutter disable, cutter enable
#define GPIO_03_DPSW4 3  // reserved
#define DSW_MASK	 0x0000000f

#define GPIO_04_STROBE1 4 
#define GPIO_05_STROBE2 5 
#define GPIO_06_STROBE3 6 
#define GPIO_07_STROBE4 7 
#define GPIO_08_STROBE5 8 
#define GPIO_09_STROBE6 9 
#define STROBE_MASK	 0x000003f0

#define GPIO_10_CLOCK	10 
#define GPIO_11_SPI	11 

#define GPIO_12_LATCH	12 

#define GPIO_13_ERR_OUT	13 
#define GPIO_14_CUT_SENSOR	14 

#define GPIO_15_CUT_A2	15	
#define GPIO_16_CUT_B2	16	
#define GPIO_17_UART_RX	17 
#define GPIO_18_MOT_A	18 
#define GPIO_19_MOT_A2	19
#define GPIO_20_MOT_B	20
#define GPIO_21_MOT_B2	21 
#define MOTOR_MASK	0x003c0000 
#define GPIO_22_FEED	22 
#define GPIO_23_CUT_A	23
#define GPIO_24_CUT_B	24
#define CUTTER_MASK	0x003c0000 

#define GPIO_25_LED	25 
#define GPIO_26_HEAD	26
#define GPIO_27_PE	27 // 基板ができるまではこれをVinのADCに使う
#define ERR_CHECK_MASK 0x0c000000
#define GPIO_28_ADC_TH	28
#define GPIO_29_ADC_VL	29
