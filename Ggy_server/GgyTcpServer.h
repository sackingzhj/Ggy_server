#pragma once
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
class GgyTcpServer
{
public:
	GgyTcpServer();

	void doEpoll();
	~GgyTcpServer();
private:
	int serverFd;
	

};
