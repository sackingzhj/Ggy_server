#include "GgyTcpServer.h"
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>

constexpr int INVALID_NUM = -1;
constexpr int PORT = 12000;

GgyTcpServer::GgyTcpServer()
{
	int opt = 1;
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));

	serverFd = socket(AF_INET, SOCK_STREAM, NULL);

	if (INVALID_NUM == serverFd)
	{
		std::cout << "socketFd init failed! "<< std::endl;
		return;
	}
	std::cout << "socketFd init sucessed!" << "the socketfd = " << serverFd << std::endl;

	sockaddr_in sockAddr;
	sockAddr.sin_addr.s_addr = INADDR_ANY;
	sockAddr.sin_port = htons(PORT);
	sockAddr.sin_family = AF_INET;

	if (INVALID_NUM == bind(serverFd, (sockaddr*)&sockAddr, socklen_t(sizeof(sockAddr))))
	{
		std::cout << "socketFd bind port failed!" << std::endl;
		return;
	}
	std::cout << "socketFd bind port sucessed!" << std::endl;


	if (INVALID_NUM == listen(serverFd, 128))
	{
		std::cout << "socketFd listen failed!" << std::endl;
		return;
	}
	std::cout << "socketFd listen sucessed!" << std::endl;
}

void GgyTcpServer::doEpoll()
{
	int epFd = epoll_create(10);
	if (INVALID_NUM == epFd)
	{
		std::cout << "epoll_create is failed!" << std::endl;
		return;
	}
	std::cout << "epoll_create is sucessed!" << std::endl;

	epoll_event ev;
	ev.data.fd = serverFd;
	ev.events = EPOLLIN;
	int rec = epoll_ctl(epFd, EPOLL_CTL_ADD, serverFd, &ev);

	if (INVALID_NUM == rec)
	{
		std::cout << "epoll_ctl is failed!" << std::endl;
		return;
	}
	std::cout << "epoll_ctl is sucessed!" << std::endl;

	epoll_wait(epFd, &ev, 1024, -1);

}

GgyTcpServer::~GgyTcpServer()
{
}
