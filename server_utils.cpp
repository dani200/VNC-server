#include "server_utils.h"


void send_(SOCKET sock, string s)
{
	send(sock, s.c_str(), s.size(), 0);
}

template<typename T>
void send_(SOCKET sock, T* data, int size)
{
	string s = "";
	for (int i = 0; i < size; i++)
		s += char(data[i]);
	send_(sock, s);
}


string recv_(SOCKET sock)
{
	char buff[BUFFER_S];
	recv(sock, buff, BUFFER_S, 0);
	return string(buff);
}


bool auth(SOCKET sock,int code,string password)
{
	if (code == 0)
	{
		string reason = "Protocol version not supported!";
		int c[5] = { 0,0,0,0,reason.size() };
		send_(sock, int_to_s(c, 5) + reason);
		return true;
	}
	else if (code == 1)
	{
		int c[4] = { 0,0,0,1 };
		send_(sock, int_to_s(c, 4));
		return true;
	}
	else if (code == 2)
	{
		int c[4] = { 0,0,0,2 };
		send_(sock, c, 4);
		return VNC_auth(sock,password);
	}
	return false;
}


string int_to_s(int* arr, int size)
{
	char* s = new char[size]();
	for (int i = 0; i < size; i++)
		s[i] = char(arr[i]);
	string ret(s);
	delete s;
	return ret;
}

string str_to_hex_s(string s)
{
	std::stringstream temp_;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < 16)
			temp_ << "0";
		temp_ << hex << int(s[i]);
	}
	return temp_.str();
}

bool VNC_auth(SOCKET sock,string password)
{
	long long int msga[16] = { 0 };
	string res;
	string s = gen_challenge(password, msga);
	send_(sock, msga, 16);
	res = str_to_hex_s(recv_(sock));
	return res == s;
}

///////////////////////////////////////////////////
void client_handle(vector<string>* blacklist, string password,SOCKET sock)
{
	try
	{
		string s;
		send_(sock, "RFB 003.003\n");
		s = recv_(sock);
		if (s.substr(0, 3) == "RFB")
		{
			if (s[6] == '3' && s[10] == '3')
			{
				if (auth(sock, 2, password))
				{

				}
				else
					auth(sock, 1,"");
			}
			else
				auth(sock, 0,"");
		}
		closesocket(sock);
	}

	catch (const std::exception& e)
	{
		closesocket(sock);
	}
}
///////////////////////////////////////////////////