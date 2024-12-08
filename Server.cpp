#include "Server.h"
#include "ThreadPool.h"//
//#include "MyMutexThreadPool.h"


#pragma comment(lib,"Ws2_32.lib")
#include<stdio.h>
#include<iostream>
#include<WinSock2.h>

#include "AdaptiveLoadBalancer.h"

using namespace std;
Server::Server(int port, const char* address,int capacity)
{
    this->port = port;
    this->address = address;
    this->capacity = capacity;
    this->freeThreads = capacity;

    pool = new ThreadPool(capacity);//  // Creates and manages pool

    pool->taskToPerform = std::bind(&Server::handleClient, this, std::placeholders::_1);


    pool->initPool();


}

void Server::start()
{
	WSADATA wsaData;
	int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Error creating socket.\n");
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(Server::port);
    serverAddress.sin_addr.s_addr = inet_addr(address);

    if (::bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error binding socket.\n");
    }

    if (listen(serverSocket, 5) < 0)
    {
        printf("Error listen socket.\n");
    }

    if (amManager)
    {
        printf("managing server started\n");
    }
	acceptConnections();
    
}

void Server::acceptConnections()
{
	while (true)
	{
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket >= 0) {

            
            pool->addTask(clientSocket);

            if (this->freeThreads > 0)
            {
                this->freeThreads--;
            }
            
        }
        
	}
}


void Server::handleClient(int clientSocket)
{
    if (amManager)// to seperate logic
    {
        char buffer[1024] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);

        int portToReroute = balancer->getMostAvailableServer();
        send(clientSocket, reinterpret_cast<const char*>(&portToReroute), sizeof(int), 0);


        return;
    }//

    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);



    cout << "handled by: "
        << this_thread::get_id() << endl;
    
    this->freeThreads++;

}

int Server::getQueuedTasksCount()
{
    
    return pool->getTasksCount();
}


