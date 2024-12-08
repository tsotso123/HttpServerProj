#include "ThreadPool.h"
#include "Server.h"

#include <iostream>


using namespace std;


ThreadPool::ThreadPool(int amountOfThreads)
{
	
	this->currentlyWaitingThreads = 0;
	this->amountOfThreads = amountOfThreads;

}

ThreadPool::~ThreadPool()
{
	// to add
}


void ThreadPool::addTask(int socket)
{
	
	{		
		lock_guard<mutex> lock(m);
		tasks.push(socket);		

	} // unlocks m

	// after the unlock, let a thread know
	cv.notify_one();
}

int ThreadPool::popTask()
{		
	
	// move is not nessecery because we are using a queue of ints, but why not
	int result = move(tasks.front());
	tasks.pop();
	return result;

}

void ThreadPool::initPool()
{
	
	for (int i = 0; i < amountOfThreads; i++)
	{
		threads.emplace_back(&ThreadPool::threadFunction, this);
	}

}

int ThreadPool::getTasksCount()
{
	
	return tasks.size();
}

void ThreadPool::threadFunction()
{
	
	while (true)
	{		
		int clientSocket = 0;

		{
			unique_lock<mutex> uniqueLock(m); // atomically locks m, waits if m is already locked

			cv.wait(uniqueLock, [&] {return !tasks.empty(); });


			clientSocket = popTask();

		} // unique_lock automatically unlocks m at end of scope (allowing other threads to lock m).
		


		if (taskToPerform)
		{
			taskToPerform(clientSocket);
		}
	}
}

