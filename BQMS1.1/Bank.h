#pragma once
#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <climits> 
#include <list>
#include <queue>
#include "Client.h"
#include "Teller.h"

using namespace std;

class Bank
{
	priority_queue<Client> WaitingClients;
	priority_queue<Client> ClientsLog;
	vector<Teller> tellers;

public:
	double averageWaiting,
		averageService,
		totalWaiting,
		totalService;

	Bank() {

		SystemIntialize();

		averageWaiting = 0;
		averageService = 0;
		totalWaiting = 0;
		totalService = 0;
	}

	void SystemIntialize() {

		int clientsCount = 0;
		int tellerCount = 0;

		cout << "\t\t\t\tWelcome to The Bank Queue Management System Simulation\n\n\n\n" << endl;
		cout << "To Get Started\n\nEnter the number of tellers :";
		cin >> tellerCount;

		cout << "Enter the number of clients :";
		cin >> clientsCount;

		intializeTellers(tellerCount);
		QueueClients(clientsCount);
		runSimulation();

	}
	void runSimulation() {

		int clientCounter = 1;
		while (!WaitingClients.empty()) {

			Client CurrentClient = WaitingClients.top();
			Teller* CurrentTeller = getAvailableTeller();

			if (CurrentTeller == NULL) {
				CurrentTeller = getNextAvailableTeller();
				//waiting time?
				if (CurrentTeller->AvaliableAt < CurrentClient.ArrivalTime)
					CurrentClient.WaitingTime = 0;

				else if ((CurrentTeller->AvaliableAt - CurrentClient.ArrivalTime) >= 0)
					CurrentClient.WaitingTime = CurrentTeller->AvaliableAt - CurrentClient.ArrivalTime;

				else
					CurrentClient.WaitingTime = 0;
			}


			CurrentClient.takeTurn(CurrentTeller);
			//PrintCurrentClientRecord(CurrentClient, clientCounter);
			clientCounter++;

			ClientsLog.push(CurrentClient);
			WaitingClients.pop();
		}

		PrintClientsLog(ClientsLog);
		PrintReport();
	}


	Teller* getNextAvailableTeller() {

		int min = INT_MAX;
		Teller* T = nullptr;

		for (int i = 0; i < tellers.size(); i++)
		{
			if (tellers[i].AvaliableAt < min) {
				min = tellers[i].AvaliableAt;
				T = &tellers[i];
				//	return T;
			}

		}
		return T;
	}
	Teller* getAvailableTeller() {

		Teller* T = nullptr;

		for (int i = 0; i < tellers.size(); i++)
		{
			if (tellers[i].isAvaliable) {

				T = &tellers[i];
				return T;
			}

		}
		return T;
	}
	void intializeTellers(int count) {
		for (int i = 1; i <= count; i++)
		{
			Teller temp;
			temp.tellerNo = i;
			tellers.push_back(temp);
		}
	}
	void QueueClients(int Count) {

		system("cls");

		for (int i = 1; i <= Count; i++)
		{
			Client temp;

			cout << "\n\t\t-: Client #" << i << " information :-";

			cout << "\n\nEnter Client Name : ";
			cin >> temp.ClientName;
			cout << "Enter Client Arrival Time : ";
			cin >> temp.ArrivalTime;
			cout << "Enter Client Required Service Time : ";
			cin >> temp.RequiredServiceTime;
			cout << "Does Client has special needs ,is  elderly, or premium account holder? ";
			cin >> temp.hasPriority;

			WaitingClients.push(temp);
			system("cls");
		}


	}
	void PrintCurrentClientRecord(Client CurrentClient, int i) {
		cout << "Client # " << i << "\tName : " << CurrentClient.ClientName
			<< "\n\nArrival Time : " << CurrentClient.ArrivalTime
			<< "\t Waiting Time : " << CurrentClient.WaitingTime
			<< "\t Service Time : " << CurrentClient.RequiredServiceTime
			<< "\t leave Time : " << CurrentClient.leaveTime
			<< "\t Assigned to Teller # " << CurrentClient.TellerID << "\n"
			<< "\t\t\t\t\t\t**************************************\n";
	}
	void PrintClientsLog(priority_queue<Client>QLog) {

		int i = 1;
		while (!QLog.empty())
		{
			Client current = QLog.top();
			cout << "\t\tClient # " << i << "\tName : " << current.ClientName
				<< "\n\nArrival Time : " << current.ArrivalTime
				<< "\tWaiting Time : " << current.WaitingTime
				<< "\tService Time : " << current.RequiredServiceTime
				<< "\tleave Time : " << current.leaveTime
				<< "\tAssigned to Teller # " << current.TellerID << "\n"
				<< "\t\t\t\t**************************************\n";

			QLog.pop();
			i++;
		}
	}
	void PrintReport() {

		calculateReport(ClientsLog);

		cout << "\n\n\t\t\t\t*******************Report*******************\n\n"
			<< "\t\tTotal Clients : " << ClientsLog.size()
			<< "\t\tAvarage Waiting Time : " << averageWaiting
			<< "\t\tAvarage Service Time : " << averageService;

		cout << "\n\n\t\t\t\t**************************************\n";
		for (int i = 0; i < tellers.size(); i++)
		{
			cout << "Teller No." << i << " Utlization Rate = " <<
				tellers[i].utlizationRate << " %\n";
		}

	}



	void calculateReport(priority_queue<Client>Log) {

		const int numOfClients = Log.size();
		while (!Log.empty())
		{
			totalService += Log.top().RequiredServiceTime;
			totalWaiting += Log.top().WaitingTime;

			Log.pop();
		}

		for (int i = 0; i < tellers.size(); i++)
		{
			tellers[i].calcUtlizationRate(totalService);
		}

		if (totalService && numOfClients)
			averageService = totalService / numOfClients;

		else
			averageService = 0;

		if (averageWaiting && numOfClients)
		averageWaiting = totalWaiting / numOfClients;

		else
			averageWaiting = 0;
	}



};
#endif 

