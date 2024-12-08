#include "MyMutexThreadPool.h"

#include <mutex>
#include <iostream>

#include "Server.h"

MyMutexThreadPool::MyMutexThreadPool(int amountOfThreads)
{
	this->amountOfThreads = amountOfThreads;
	//this->m = MyMutex();
}

void MyMutexThreadPool::addTask(int socket)
{
	//m.LockMyMutex();
	tasks.push(socket);
	//m.UnlockMyMutex();

}

int MyMutexThreadPool::popTask()
{
	
	int result = move(tasks.front());
	tasks.pop();
	return result;
}

void MyMutexThreadPool::initPool()
{
	for (int i = 0; i < amountOfThreads; i++)
	{
		threads.emplace_back(&MyMutexThreadPool::threadFunction, this);
	}
}

int MyMutexThreadPool::getTasksCount()
{
	return tasks.size();
}

void MyMutexThreadPool::threadFunction()
{

	while (true)
	{
		int clientSocket = 0;

		if (!server->amManager)//
			m.LockMyMutex();

		while (tasks.empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			
		}

		clientSocket = popTask();

		if (!server->amManager)//
			m.UnlockMyMutex();

		if (server)
		{
			// perform delegated task
			server->handleClient(clientSocket);
			
		}
		
	}
}
void MyMutexThreadPool::handleClient()
{
	


}