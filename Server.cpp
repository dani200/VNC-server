#include <exception>
#include "Server.h"


Server::Server(string password)
{
	this->pass = password;
	this->black_list = new vector<string>();
	_serverSocket = ::socket(AF_INET,  SOCK_STREAM,  IPPROTO_TCP); 
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	delete this->black_list;
	try
	{
		::closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port); 
	sa.sin_family = AF_INET;   
	sa.sin_addr.s_addr = INADDR_ANY;
	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	if (::listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	cout << "Listening on port " << port << "\n";

	while (true)
	{
		cout << "Waiting for client connection request\n";
		accept();
	}
}


void Server::accept()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	cout << "Client accepted." << "\n";
	clientHandler(client_socket);
}


void Server::clientHandler(SOCKET clientSocket)
{
	
}
