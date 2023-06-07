#pragma once

#include <FreeRTOS.h>
#include <task.h>
#include "pico/stdlib.h"
#include "iodefine.h"

class TaskBase
{
protected:
	TaskBase* nextTask;
	virtual bool TaskReady();
	void SetTaskFlag(); // 前のタスクにセットしてもらう
	void ChangeTask();
	virtual void Worker() = 0;

	void Led(int s);
	void Led();

	int led = 0;

	void Delay(int);
	void Sleep(int);
	TaskHandle_t hTask;

public:
	TaskBase();
	TaskBase(int);
	bool sig;
	static void Thread(void*);
};

