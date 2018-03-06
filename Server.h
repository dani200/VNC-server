#pragma once
#include "server_utils.h"
#include <WinSock2.h>
#include <Windows.h>



class Server
{
public:
	Server(string);
	~Server();
	void serve(int port);

private:
	string pass;
	vector<string>* black_list;
	void accept();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};

