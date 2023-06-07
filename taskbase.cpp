#include "taskbase.h"

TaskBase::TaskBase()
{
	sig = false;
	xTaskCreate(
		Thread,	// タスクを実行する関数へのポインタ
		"",	// タスク名(デバッグ用)
		 2560,	// タスクに割り当てられるスタックのサイズ
		 this,	// タスクに渡される引数へのポインタ
		 1,		// 優先度。大きい方が優先度が高い。
		 &hTask);	// ハンドラ。優先度を変更するときに使う。
}

TaskBase::TaskBase(int pri)
{
	sig = false;
	xTaskCreate(
		Thread,	// タスクを実行する関数へのポインタ
		"",	// タスク名(デバッグ用)
		 2560,	// タスクに割り当てられるスタックのサイズ
		 this,	// タスクに渡される引数へのポインタ
		 pri,		// 優先度。大きい方が優先度が高い。
		 &hTask);	// ハンドラ。優先度を変更するときに使う。
}

void TaskBase::SetTaskFlag()
{
	sig = false;
}

bool TaskBase::TaskReady()
{
//	return fOnWork && !nextTask->fOnWork;

	if(sig){
		if(nextTask) return !nextTask->sig;
		else return true;
	}

	return false;
}

void TaskBase::ChangeTask()
{
	sig = false;
	if(nextTask) nextTask->sig = true;
}

void TaskBase::Thread(void* p)
{
	((TaskBase*)p)->Worker();
}

void TaskBase::Led(int s)
{
	gpio_put(25, s);
}

void TaskBase::Led()
{
	led ^= 1;
	gpio_put(25, led);
}

void TaskBase::Delay(int n)
{
	for(int i = 0; i < n; i++) vTaskDelay(1);
}

void TaskBase::Sleep(int n)
{
	//sleep_us(n);
	busy_wait_us(n);
}
