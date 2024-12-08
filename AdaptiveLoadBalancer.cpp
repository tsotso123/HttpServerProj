#include "AdaptiveLoadBalancer.h"

#include "MyMutexThreadPool.h"
#include "Server.h"
#include <iostream>

AdaptiveLoadBalancer::AdaptiveLoadBalancer(std::vector<Server*> servers)
{

	for (int i = 0; i < servers.size(); i++)
	{
		serversThreads.emplace_back(&Server::start, servers[i]);
		printf("%d started\n", servers[i]->port);

	}

	this->manager = new Server(8080, "127.0.0.1", 1);
	this->manager->amManager = true;
	this->manager->balancer = this;

	this->serversList = servers;

	
	manager->start();
	

	
}

int AdaptiveLoadBalancer::getMostAvailableServer()
{
	int port = 0;
	int maxFreeThreads = 0;
	
	int maxCapacityIfAllBusy = 1000000;
	int allBusyPort = 0;

	for (int i = 0; i < this->serversList.size(); i++)
	{
		if (serversList[i]->freeThreads > maxFreeThreads)
		{
			maxFreeThreads = serversList[i]->freeThreads;
			port = serversList[i]->port;
		}

		if ((serversList[i]->getQueuedTasksCount() - serversList[i]->capacity) < maxCapacityIfAllBusy)
		{
			maxCapacityIfAllBusy = (serversList[i]->getQueuedTasksCount() - serversList[i]->capacity);
			allBusyPort = serversList[i]->port;
		}
	}

	// if all servers are busy, then go by (queue size - capacity) lowest value is least busy
	if (!port)
	{
		port = allBusyPort;

		printf("all busy");
		
		cout<< maxCapacityIfAllBusy << endl;
		
	}

	return port;
}
