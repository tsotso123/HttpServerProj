#include <stdio.h>
#include "Server.h"
#include <vector>
#include "AdaptiveLoadBalancer.h"

using namespace std;
int main()
{
	vector<Server*> servers;



	servers.emplace_back(new Server(8089, "127.0.0.1", 3));
	servers.emplace_back(new Server(8088, "127.0.0.1", 2));
	servers.emplace_back(new Server(8087, "127.0.0.1", 5));
	

	
	AdaptiveLoadBalancer* balancer = new AdaptiveLoadBalancer(servers);


	/*Server* server = new Server(8089, "127.0.0.1", 3);
	server->start();*/

	return 0;
}