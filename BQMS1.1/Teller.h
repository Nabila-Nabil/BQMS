#ifndef TELLER_H
#define TELLER_H
#pragma once
#include <iostream>
#include <list>
#include <queue>
#include "Bank.h"
#include "Client.h"
#include "Teller.h"

class Teller {
public:
	int tellerNo;
	int AvaliableAt;
	bool isAvaliable;
	int totalUsageTime;
	int clientsServed;
	double utlizationRate;

	Teller() {

		tellerNo = 0;
		AvaliableAt = 0;
		isAvaliable = true;
		totalUsageTime = 0;
		 clientsServed = 0;
		 utlizationRate = 0;
	}

	void calcUtlizationRate(int totalTime) {
		if(totalTime)
		utlizationRate = (totalUsageTime / totalTime);

		else
		{
			utlizationRate = 0;
		}
	}

};

#endif 