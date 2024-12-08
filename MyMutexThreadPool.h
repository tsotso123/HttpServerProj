#pragma once

#include "MyMutex.h"
#include <mutex>
#include <vector>
#include <queue>

using namespace std;

class Server;

class MyMutexThreadPool
{
public:
	MyMutexThreadPool(int amountOfThreads);
	
	void addTask(int socket);
	int popTask();
	void initPool();
	int getTasksCount();

	Server* server;


private:
	int amountOfThreads;
	int currentlyWaitingThreads;

	void threadFunction();

	void handleClient();


	MyMutex m;
	
	queue<int> tasks;
	vector<thread> threads;
	vector<thread> waitingList;

	
};

