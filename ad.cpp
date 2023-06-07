#include "ad.h"

void Ad::Init()
{
	adc_init();
	adc_gpio_init(GPIO_29_ADC_VL); // 3: head voltage
	adc_gpio_init(GPIO_28_ADC_TH); // 2: head temprature 
}

double Ad::GetVoltVal()
{
	if(lastId != 3) adc_select_input(3);
	while(adc_get_selected_input() != 3){
		std::cout << "!!!!!!!!!!!!!adc 3 err" << std::endl;
		//sleep_us(1);
		busy_wait_us(1);
		adc_select_input(3);
	}
	lastId = 3;
	//sleep_us(1);
	volatile uint16_t ad = adc_read();
	voltVal = static_cast<double>(ad);
	return voltVal;
}

double Ad::GetTempVal()
{
	if(lastId != 2) adc_select_input(2);
	while(adc_get_selected_input() != 2){
		std::cout << "!!!!!!!!!!!!!!!adc 2 err" << std::endl;
		//sleep_us(1);
		busy_wait_us(1);
		adc_select_input(2);
	}
	lastId = 2;
	//sleep_us(1);
	volatile uint16_t ad = adc_read();
	tempVal = static_cast<double>(ad);
	return tempVal;
}

double Ad::GetTempFast()
{
	return -0.02817886169 * adc_read() + 78.7938442;
}

double Ad::CulcVolt()
{
	//return 0.00348632305 * voltVal - 0.173992;
	return 1.27*(0.00348632305 * voltVal - 0.173992);
}

// こっちの方が速くなる
// 5Vでも薄すぎる
double Ad::CulcTemp()
{
	return -0.02817886169 * tempVal + 78.7938442;
}
double Ad::GetVolt()
{
	GetVoltVal();
	return CulcVolt();
}

// 遅くなる
// 5Vではちょうどいい
// 電圧が上がると薄くなる
double Ad::GetTemp()
{
	GetTempVal();
	return CulcTemp();
}
