#include <iostream>
#include "rcvbuf.h"

bool RcvBuf::IsFull()
{
	//int p = (pi + 1) & (RCV_BUF_SIZE - 1);
	//return (p == po);

	int p = pi; 

	if(p < po) p += RCV_BUF_SIZE;

	return (RCV_BUF_SIZE - (p - po) < alertEmptySize);
}

void RcvBuf::SetAlertEmptySize(int s)
{
	alertEmptySize = s;
}

bool RcvBuf::Set(const uint8_t dat)
{
	int p = (pi + 1) & (RCV_BUF_SIZE - 1);
	if(p == po) return false;

	buf[pi] = dat;
	pi = p;
	
	return true;
}

bool RcvBuf::Get(uint8_t& dat)
{
	if(pi == po) return false;

	dat = buf[po];
	po = (po + 1) & (RCV_BUF_SIZE - 1);

	return true;
}
