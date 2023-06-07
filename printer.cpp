#include <cstring>
#include "printer.h"

#define USE_PWM
#define MSG 

Ad Printer::iAd;

void Printer::Init(SndBuf* p)
{
	pSndBuf = p;

	//Init(); // motor off

	step = 0;
	phase = 0;

	iSpi.Init(GPIO_10_CLOCK, GPIO_11_SPI, 8*1000*1000, pSndBuf);
	std::cout << "spi baud =" << iSpi.GetBaud() << std::endl;

	gpio_init_mask(
		STROBE_MASK |
		(1 << GPIO_12_LATCH) |
		(1 << GPIO_13_ERR_OUT) |
		MOTOR_MASK |
		ERR_CHECK_MASK
	);

	gpio_set_dir_in_masked(
		ERR_CHECK_MASK
	);

	gpio_set_dir_out_masked(
		STROBE_MASK |
		(1 << GPIO_12_LATCH) |
		(1 << GPIO_13_ERR_OUT)
	);

	gpio_disable_pulls(GPIO_26_HEAD);
	gpio_disable_pulls(GPIO_27_PE);

	gpio_put(GPIO_13_ERR_OUT, 0);

#ifndef USE_PWM
	gpio_set_dir_out_masked(MOTOR_MASK);
#else
	pwmConf = pwm_get_default_config();
	pwm_config_set_clkdiv(&pwmConf, 1.f);
	pwm_config_set_wrap(&pwmConf, 6249);

	for(auto p: {
			GPIO_18_MOT_A,
			GPIO_19_MOT_A2,
			GPIO_20_MOT_B,
			GPIO_21_MOT_B2,
		}){
		gpio_set_function(p, GPIO_FUNC_PWM);
		uint sliceNum = pwm_gpio_to_slice_num(p);
		pwm_init(sliceNum, &pwmConf, true);
	}
#endif

	iAd.Init();

	iCutter.InitIO();
	if(!gpio_get(GPIO_02_DPSW3)){
		mechaType = MECHA_MLT4281;
		//iCutter.InitialRoutine(); // アンコメントすると固まる
		Trace("MECHA_MLT4281");
	}
	else{
		mechaType = MECHA_MLT289;
		Trace("MECHA_MLT289");
	}

	MotorOff();
}

void Printer::Latch(int t)
{
	gpio_put(GPIO_12_LATCH, 0);
	Sleep(t); // これがないと真っ黒になる
	gpio_put(GPIO_12_LATCH, 1);
}

uint64_t Printer::GetTon289(double ndot, double vh, double th, bool mode16)
{
	double v = -0.0321 * vh * vh + 1.8455 * vh - 3.8783;
	double tmp = (ndot * 0.05 + 130 + 15) / v;
	double ton25 =  0.4 * tmp*tmp / 130 * 1000.0;

	double coe;
	if(th >= 25) coe = 1.2 * (25 - th) / 100;
	else coe = 1.5 * (25 - th) / 100;
	coe += 1;

	return static_cast<uint64_t>(ton25 * coe);
}

uint64_t Printer::GetTon(double ndot, double vh, double th, bool mode16)
{
	double v = -0.034 * vh * vh + 1.794 * vh - 4.282;
	double tmp = (ndot * 0.05 + 130 + 15) / v;
	double ton25 =  0.2 * tmp*tmp / 130 * 1000.0;

	double coe = (25 - th) / 100;
	coe *= 1.1;
	coe += 1;

	return static_cast<uint64_t>(ton25 * coe);
}

int Printer::CntActive(uint8_t* d)
{
	uint64_t n = *(reinterpret_cast<uint64_t*>(d));
	n = ((n>> 1) & 0x5555555555555555) + (n & 0x5555555555555555);
	n = ((n>> 2) & 0x3333333333333333) + (n & 0x3333333333333333);
	n = ((n>> 4) & 0x0f0f0f0f0f0f0f0f) + (n & 0x0f0f0f0f0f0f0f0f);
	n = ((n>> 8) & 0x00ff00ff00ff00ff) + (n & 0x00ff00ff00ff00ff);
	n = ((n>>16) & 0x0000ffff0000ffff) + (n & 0x0000ffff0000ffff);
	n = ((n>>32) & 0x00000000ffffffff) + (n & 0x00000000ffffffff);
	return static_cast<int>(n);
};

void Printer::Strobe(uint8_t* dat, int t, int maxDot)
{
	// 分割数
	static const double coeDivTbl[] = {
		0, 1.00, 1.30, 1.30, 1.40, 1.45, 1.50,
	};

	uint64_t ton = 0;
	uint8_t b[6] = {0, 0, 0, 0, 0, 0, };
	//uint8_t d[6] = {0, 0, 0, 0, 0, 0, };
	int dotNum[6] = {0, 0, 0, 0, 0, 0, };
	int cnt = 0;
	int divNum = 0;
	int stNum = 0;

	for(auto i: {0, 1, 2, 3, 4, 5, }){
		cnt = CntActive(dat + i * 8);
		if(cnt > 64) cnt = 0;
		if(!cnt) continue;
		if(dotNum[divNum] + cnt > maxDot){
			divNum += 1;
		}
		dotNum[divNum] += cnt;
		stNum++;
		//d[divNum] += 1;
		b[divNum] |= (1 << i);
	}

	if(dotNum[0] == 0) return;
	divNum += 1;

	double vh = iAd.CulcVolt();
	double th = iAd.GetTempFast();
	//double coe = coeDivTbl[divNum];
	double coe = coeDivTbl[stNum];

	vTaskPrioritySet(NULL, 2);

	for(int i = 0; i < divNum; i++){
		cnt = dotNum[i];

		if(mechaType == MECHA_MLT4281)
			ton = GetTon(cnt, vh, th) * coe;
		else ton = GetTon289(cnt, vh, th);

		if(ton > 9000) ton = 500;

		uint32_t mask = b[i] << 4;
		gpio_set_mask(mask);
		Sleep(ton);
		gpio_clr_mask(mask);
		Sleep(15);
	}

	vTaskPrioritySet(NULL, 1);
}

bool Printer::CheckVolt(double& vOff)
{
	double v = iAd.GetVolt();

	if((v < vOff - 0.1) || (v > vOff + 0.1)){
		vOff = v;
		return false;
	}

	return true;
}

bool Printer::MotorPrepare(double& vOff, int n)
{
	double preV = vOff;
	if(!CheckVolt(vOff)){
		std::cout << "voltage changeed " << preV << " -> " << vOff << std::endl;
		for(int i = 0; i < 5; i++){
			gpio_put(GPIO_25_LED, gpio_get(GPIO_25_LED)^ 1);
			Delay(30);
		}
		gpio_put(GPIO_25_LED, 1);

		return false;
	}

	MotorPwm(1);
	lastPeriod = get_absolute_time();
	off = false;
	double v;
	if(quarityH){
		Sleep(ppsTbl[maxStep]);
		v = iAd.GetVolt();
		MotorWait();
	}
	else
		v = iAd.GetVolt();

	if(mechaType == MECHA_MLT289){
		if(v < 4.5) ppsTbl = m_289tbl_4v; // 4.2 - 4.7
		else if(v < 5.2) ppsTbl = m_289tbl_5v; // 4.8 - 5.5
		else if(v < 6.1) ppsTbl = m_289tbl_6v; // 5.6 - 6.5
		else if(v < 7.2) ppsTbl = m_289tbl_7v; // 6.6 - 7.5
		else if(v < 8.5) ppsTbl = m_289tbl_8v; // 7.6 - 8.5
		//else ppsTbl = m_289tbl_9v;
		else ppsTbl = m_289tbl_8v;

		maxStep = 18;
	}
	else{
		ppsTbl = m_4281tbl;
		if(v > 5) ppsTbl = m_4281tbl2;
		if(v > 6.5) ppsTbl = m_4281tbl_9v;
		maxStep = 47;
	}

#ifdef MSG
	if(off) std::cout << "motor on" << std::endl;
#endif

	//MotorOn();
	//MotorPwm(1);
	//off = false;
	//lastPeriod = get_absolute_time();

	for(int i = 0; i < n; i++){
		NextPhase();
	}

	iAd.GetTemp();

	return true;
}

void Printer::WaitUntilNext()
{
	if(step > maxStep) step = maxStep;

	int64_t diff = absolute_time_diff_us(lastPeriod, get_absolute_time());

	if(!quarityH){
		int64_t minWait = ppsTbl[maxStep] - diff;
		if(minWait > 0){
			Sleep(minWait);
			diff += minWait;
		}
	}

	int64_t stepWait = ppsTbl[step] - diff;
	if(stepWait > 0){
		MotorWait();
		Sleep(stepWait);
	}
	else{
		while(ppsTbl[step] < diff){
			if(step <= 0){
				break;
			}
			step--;
		}
	}
}

void Printer::WaitUntilStop()
{
	if(quarityH){
		Sleep(ppsTbl[maxStep]);
		MotorWait();
	}
}

void Printer::NextPhase()
{
	WaitUntilNext();

	phase = (phase + 1) & 3;
	MotorOn();

	step += 1;
	if(step > maxStep) step = maxStep;
}

void Printer::MotorOn()
{
#ifndef USE_PWM
	int f;
	f = (phaseTbl[phase] & 2) >> 1;
	gpio_put(GPIO_18_MOT_A, f);
	gpio_put(GPIO_19_MOT_A2, f ^ 1);

	f = phaseTbl[phase] & 1;
	gpio_put(GPIO_20_MOT_B, f);
	gpio_put(GPIO_21_MOT_B2, f ^ 1);
#else
	MotorPwm(1);
#endif

	lastPeriod = get_absolute_time();
	off = false;

	WaitUntilStop();
}

void Printer::MotorWait()
{
#ifdef MSG
	//std::cout << "motor wait" << std::endl;
#endif

	MotorPwm(0.65);
}

void Printer::MotorOff()
{
#ifdef MSG
	std::cout << "motor off" << std::endl;
#endif

	step = 0;
	off = true;
	MotorPwm(0);

	//gpio_put(GPIO_18_MOT_A, 0);
	//gpio_put(GPIO_19_MOT_A2, 0);
	//gpio_put(GPIO_20_MOT_B, 0);
	//gpio_put(GPIO_21_MOT_B2, 0);
}

void Printer::MotorPwm(double d)
{
	uint16_t duty = pwmConf.top * d;

	if(phaseTbl[phase] & 2){
		pwm_set_gpio_level(GPIO_18_MOT_A, duty);
		pwm_set_gpio_level(GPIO_19_MOT_A2, 0);
	}
	else{
		pwm_set_gpio_level(GPIO_18_MOT_A, 0);
		pwm_set_gpio_level(GPIO_19_MOT_A2, duty);
	}

	if(phaseTbl[phase] & 1){
		pwm_set_gpio_level(GPIO_20_MOT_B, duty);
		pwm_set_gpio_level(GPIO_21_MOT_B2, 0);
	}
	else{
		pwm_set_gpio_level(GPIO_20_MOT_B, 0);
		pwm_set_gpio_level(GPIO_21_MOT_B2, duty);
	}
}

bool Printer::CheckErr()
{
	uint32_t s = gpio_get_all();

	if(!(s & ERR_CHECK_MASK)) return false;

	if(s & (1 << GPIO_26_HEAD)) Trace("Head-up error.");
	if(s & (1 << GPIO_27_PE)) Trace("\t\tPE error.");

	gpio_put(GPIO_13_ERR_OUT, 0);
	iCutter.Off();
	MotorOff();

	int cnt = 0;

	do{
		Delay(1);
		cnt++;
		if(cnt > 20){
			gpio_put(GPIO_25_LED, gpio_get(GPIO_25_LED)^ 1);
			cnt = 0;
		}
	} while(CheckErr());

	gpio_put(GPIO_25_LED, 0);
	Delay(100);

	gpio_put(GPIO_25_LED, 1);
	gpio_put(GPIO_13_ERR_OUT, 1);

	return true;
}

void Printer::HeadClear(uint8_t dat)
{
	iSpi.SendNull(dat);
	Latch(1); // us
}

void Printer::Worker()
{
	Delay(100);

	double vOn = 0;
	double vOff = 0;
	int checkCnt = 0;

    std::cout << "printer" << std::endl;
	int debugCnt = 0;
	uint8_t* pBuf;
	uint8_t bufTmp[48];
	Line48* pLine = nullptr;
	int l = 0;

	auto action = [&](){
		if((pLine = pSndBuf->GetRowPtr()) == nullptr) return 0;
		if(off && (!MotorPrepare(vOff))) return 0;

		pBuf = pLine->col;

		if(pLine->mode == PMODE_PCUT){
			pSndBuf->FinWork();
			if(mechaType == MECHA_MLT4281){
				Sleep(ppsTbl[maxStep]);
				iCutter.Cut(true);
			}
			return 0;
		}
		else if(pLine->mode == PMODE_FCUT){
			pSndBuf->FinWork();
			if(mechaType == MECHA_MLT4281){
				Sleep(ppsTbl[maxStep]);
				iCutter.Cut(false);
			}
			return 0;
		}
		else if(pLine->mode == PMODE_FEED){
			pSndBuf->FinWork();
			NextPhase();
			//if(!checkDat()) return 0;
			return 1;
		}

		if(pLine->mode == PMODE_LISTER){
			for(int i = 0; i < 48; i++){
				uint8_t tmp = pBuf[47 - i];
				tmp = ((tmp >> 1) & 0x55) | ((tmp << 1) & 0xaa);
				tmp = ((tmp >> 2) & 0x33) | ((tmp << 2) & 0xcc);
				tmp = ((tmp >> 4) & 0x0f) | ((tmp << 4) & 0xf0);
				bufTmp[i] = tmp;
			}
		}
		else memcpy(bufTmp, pBuf, 48);
		pSndBuf->FinWork();
		iSpi.SendLine(bufTmp);
		Latch(1);
		return 2;
	};

	if(mechaType == MECHA_MLT4281)
		iCutter.InitialRoutine();

	auto clrBuf = [&](){
		for(auto& b: bufTmp) b = 0;
	};

	clrBuf();
	vOff = iAd.GetVolt();
	MotorPrepare(vOff);
	if(!quarityH) vOn = iAd.GetVolt();
	std::cout << "start vOff=" << vOff << ", vOn=" << vOn << std::endl;
	MotorOff();
//vTaskPrioritySet(NULL, 3);
//std::cout << "pri=" << uxTaskPriorityGet(NULL) << std::endl;
	while(true){
		//sleep_us(100);
		Delay(1);

		CheckErr();

		if(off){
			if(!checkCnt) CheckVolt(vOff);
			checkCnt = (checkCnt + 1) & 0xff;
		}

#ifdef MSG
		//-------------------
		// infomation
		if(off){
			debugCnt = (debugCnt + 1) & 0x1ff;
			if(debugCnt == 0){
				static absolute_time_t now = get_absolute_time();
				absolute_time_t last = now;
				now = get_absolute_time();
				std::cout << absolute_time_diff_us(last, now)/1000 << " [ms]";

				volatile int v = iAd.GetVoltVal();
				volatile double v2 = iAd.CulcVolt();
				std::cout << " off\t v=(" << v << ") " << v2 << " V \t";

				volatile int t = iAd.GetTempVal();
				volatile double t2 = iAd.CulcTemp();
				std::cout << "temp=(" << t << ") " << t2 << " ℃";

				std::cout << std::endl;
			}
		}
#endif

		l++;
		if(l > 511){
			if(!off){
				MotorOff();
			}
		}

		int act = action();
		if(!act) continue;

		//vTaskPrioritySet(NULL, 2);

		//-------------------
		// Move
		while(true){
			CheckErr();

			//WaitUntilNext();
			NextPhase();
			//WaitUntilStop();

			if(act == 2){ 
				Strobe(bufTmp, 0); // モータ回転中にストローブがかかるとモータへの電圧が低くなる？
			}

			//WaitUntilNext();
			NextPhase();
			//WaitUntilStop();

			act = action();
			if(!act) break;
		}

		//vTaskPrioritySet(NULL, 1);
		MotorWait();
		checkCnt = 0;
		l = 0;
	}
}
