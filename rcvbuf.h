#pragma once
#include "pico/stdlib.h"

#define RCV_BUF_SIZE 1024 

class RcvBuf
{
public:
    int pi = 0;
    int po = 0;
	int alertEmptySize = 0;

public:
	void SetAlertEmptySize(int);
	bool IsFull();
	bool Set(const uint8_t);
	bool Get(uint8_t&);
	uint8_t buf[RCV_BUF_SIZE];
};
