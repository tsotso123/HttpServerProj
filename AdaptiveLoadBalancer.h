#pragma once

#include "Server.h"
#include <vector>
#include <thread>


class AdaptiveLoadBalancer
{
public:
	AdaptiveLoadBalancer(std::vector<Server*> servers);
	int getMostAvailableServer(); // returns server port
private:


	std::vector<Server*> serversList;
	Server* manager;
	std::vector<std::thread> serversThreads;
};

