
#pragma once


class ThreadPool;//

class AsyncIO;

//class MyMutexThreadPool;
class AdaptiveLoadBalancer;

class Server
{
	public:
		Server(int port,const char* address,int capacity);
		void start();
		void handleClient(int clientSocket);
		int getQueuedTasksCount();

		int freeThreads;
		int port;
		bool amManager = false;
		int capacity;

		AdaptiveLoadBalancer* balancer;
	private:
		
		void acceptConnections();
				
		const char* address;
		int serverSocket;
		
		ThreadPool* pool;//
		AsyncIO* asyncIo;
		//MyMutexThreadPool* pool;
};

