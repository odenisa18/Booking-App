#include<iostream>
#include"CBooking.h"
int main()
{
	CBooking* instance = CBooking::getInstance();
	instance->startAPPBooking();
	return 0;
}