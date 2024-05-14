#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <list>
#include <queue>
#include "Teller.h"


using namespace std;
class Client {
	int SSN;
	int AcountNumber;
	double Balance;

public:
	string ClientName;
	int ArrivalTime;
	int RequiredServiceTime;
	int WaitingTime;
	int leaveTime;
	int TellerID;

	bool hasPriority = false;

/*	void setSSN(int ssn) {
		SSN = ssn;
	}
	void setAcountNumber(int AN) {
		AcountNumber = AN;
	}
	int getSSN(int ssn) {
		SSN = ssn;
	}
	int getAcountNumber() {
		return AcountNumber;
	}
	double getBalance() {
		return Balance;
	}*/
	Client() {
		SSN = 0000;
		AcountNumber = 0000;
		ClientName = "";
		Balance = 0000;

		ArrivalTime = 0;
		RequiredServiceTime = 0;
		WaitingTime = 0;
		leaveTime = 0;
		TellerID = -1;
	}
	bool operator<(const Client& other) const {
		// Priority 1: lower arrival time -> higher priority
		if (ArrivalTime != other.ArrivalTime)
			return ArrivalTime > other.ArrivalTime;
		// Priority 2: VIP customers have higher priority
		return hasPriority;
	}
	void takeTurn(Teller *T) {

		T->totalUsageTime += RequiredServiceTime;
		T->clientsServed++;

		leaveTime = ArrivalTime + RequiredServiceTime + WaitingTime;

		T->AvaliableAt = leaveTime;
		TellerID = T->tellerNo;

		T->isAvaliable = false;

	}
};
#endif 

