#include "cutter.h"

Cutter::Cutter()
{
}

void Cutter::PinSet(int p, int dir)
{
	gpio_init(p);
	gpio_set_dir(p, dir);
}

void Cutter::InitIO()
{
	cPhase = 0;

	// cutter
	PinSet(GPIO_14_CUT_SENSOR, GPIO_IN);	// cutter sensor
	gpio_disable_pulls(GPIO_14_CUT_SENSOR);

	PinSet(GPIO_23_CUT_A, GPIO_OUT);
	PinSet(GPIO_15_CUT_A2, GPIO_OUT);
	PinSet(GPIO_24_CUT_B, GPIO_OUT);
	PinSet(GPIO_16_CUT_B2, GPIO_OUT);

	pwmConf = pwm_get_default_config();
	pwm_config_set_clkdiv(&pwmConf, 1.f);
	pwm_config_set_wrap(&pwmConf, 6249);

	for(auto p: {
			GPIO_23_CUT_A,
			GPIO_15_CUT_A2,
			GPIO_24_CUT_B,
			GPIO_16_CUT_B2,
		}){
		gpio_set_function(p, GPIO_FUNC_PWM);
		uint sliceNum = pwm_gpio_to_slice_num(p);
		pwm_init(sliceNum, &pwmConf, true);
	}

	Off();
}

void Cutter::MotorPwm(double d)
{
	uint16_t duty = pwmConf.top * d;

	if(cutterPhaseTbl[cPhase] & 2){
		pwm_set_gpio_level(GPIO_23_CUT_A, duty);
		pwm_set_gpio_level(GPIO_15_CUT_A2, 0);
	}
	else{
		pwm_set_gpio_level(GPIO_23_CUT_A, 0);
		pwm_set_gpio_level(GPIO_15_CUT_A2, duty);
	}

	if(cutterPhaseTbl[cPhase] & 1){
		pwm_set_gpio_level(GPIO_24_CUT_B, duty);
		pwm_set_gpio_level(GPIO_16_CUT_B2, 0);
	}
	else{
		pwm_set_gpio_level(GPIO_24_CUT_B, 0);
		pwm_set_gpio_level(GPIO_16_CUT_B2, duty);
	}
}

void Cutter::On()
{
	//vTaskPrioritySet(NULL, 2);
	step = 0;

	/*
	uint8_t f = (cutterPhaseTbl[cPhase] & 2) >> 1;
	gpio_put(GPIO_23_CUT_A, f);
	gpio_put(GPIO_15_CUT_A2, f^1);
	f = cutterPhaseTbl[cPhase] & 1;
	gpio_put(GPIO_24_CUT_B, f);
	gpio_put(GPIO_16_CUT_B2, f^1);
	*/

	MotorPwm(1);
	//busy_wait_us(tbl[maxStep]);
	sleep_us(tbl[maxStep]);
	MotorPwm(0.65);
}

void Cutter::Off()
{
	step = 0;
	MotorPwm(0);

	/*
	//gpio_put(GPIO_16_CUT_OE, 1);
	gpio_put(GPIO_23_CUT_A, 0);
	gpio_put(GPIO_15_CUT_A2, 0);
	gpio_put(GPIO_24_CUT_B, 0);
	gpio_put(GPIO_16_CUT_B2, 0);
	vTaskPrioritySet(NULL, 1);
	*/
}

void Cutter::Move(int d)
{
	//busy_wait_us(tbl[step]);
	//busy_wait_us(tbl[step] - tbl[maxStep]);
	sleep_us(tbl[step] - tbl[maxStep]);
	step++;
	if(step > maxStep) step = maxStep;

	/*
	uint8_t f = (cutterPhaseTbl[cPhase] & 2) >> 1;
	gpio_put(GPIO_23_CUT_A, f);
	gpio_put(GPIO_15_CUT_A2, f^1);
	f = cutterPhaseTbl[cPhase] & 1;
	gpio_put(GPIO_24_CUT_B, f);
	gpio_put(GPIO_16_CUT_B2, f^1);
	*/

	cPhase = (cPhase + d) & 3;
	MotorPwm(1);
	//busy_wait_us(tbl[maxStep]);
	sleep_us(tbl[maxStep]);
	MotorPwm(0.65);
}

void Cutter::MoveToStep(int d, int stepN)
{
	On();

	for(int i = 0; i < stepN; i++){
		Move(d);
	}
	
	Off();
}

bool Cutter::MoveToSensor(int d, int s)
{
	On();

	for(int i = 0; i < 379; i++){
		Move(d);
		if(ChkSens(s)){
			Off();
			return true;
		}
	}

	Off();
	return false;
}

int Cutter::ChkSens(int s)
{
	int c = 0;
	for(int i = 0; i < 20; i++){
		if(gpio_get(GPIO_14_CUT_SENSOR) == s) c++;
		else return 0;
		if(c > 10) return i;
		sleep_ms(10/2);
		//vTaskDelay(1);
	}
	return 0;
}

int Cutter::InitialRoutine()
{
	Trace("Cutter Initialize Start.");
	
	MoveToStep(1, 50);

	if(gpio_get(GPIO_14_CUT_SENSOR) == SENSOR_OFF){
		Trace("detect sensor off");
		if(!MoveToSensor(1, SENSOR_ON)){
			Trace("\t error! can not detect sensor on");
			return 0;
		}
	}
	Trace("detect sensor on");

	if(!MoveToSensor(-1, SENSOR_OFF)){
		Trace("\t error! can not detect sensor off");
		return 0;
	}

	Trace("Cutter Initialize OK.");
	return 0;
}

int Cutter::Cut(bool partial)
{
#ifndef CUT_ENABLE
	return  0;
#endif

	int stepN = 279;
	if(partial) stepN = 196 + 10;

	if(gpio_get(GPIO_14_CUT_SENSOR) != SENSOR_OFF){
//		Trace("\t is sensor init?");
		InitialRoutine();
		return 0;
	}

	if(!MoveToSensor(1, SENSOR_ON)){
//		Trace("\t sensor is not ON within 200 step");
		return 0;
	}
//	Trace("sensor is ON within 200 step");

//	Trace("start positive round");
	MoveToStep(1, stepN);

//	Trace("start negative round");
	bool ret = MoveToSensor(-1, SENSOR_OFF);
//	if(!ret) Trace("\t sensor is not OFF within 379 step");
//	else Trace("sensor is OFF within 379 step");

	return 0;
}
