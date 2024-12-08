#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>
#include <functional>



using namespace std;

class ThreadPool
{
	public:
		ThreadPool(int amountOfThreads);
		~ThreadPool();
		void addTask(int socket);
		int popTask();
		void initPool();
		int getTasksCount();

		function<void(int)> taskToPerform;
	private:
		int amountOfThreads;

		int currentlyWaitingThreads;
		
		void threadFunction();	
		
		mutex m;
		condition_variable cv;
		queue<int> tasks;
		vector<thread> threads;
};

