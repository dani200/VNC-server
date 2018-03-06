#include "Server-client.h"


client_server::client_server(server_seetings* set)
{
	this->settings = set;
	this->encoding = 0;
}

void client_server::DispatchM(SOCKET sock,string message)
{
	int type = message[0];
	switch (type)
	{
	case 0:
		this->set_pix_format(message);
		break;
	case 1:
		//color maps not supported in this version
		break;
	case 2:
		this->set_encoding(message);
		break;
	case 3:
		this->frame_buffer_update(message);
		break;
	case 4:
		this->key_event(message);
		break;
	case 5:
		this->pointer_event(message);
		break;
	case 6:
		this->cut_text(message);
		break;
	default:
		cout << "Unkown message from client!\n";
		break;
	}
}

void client_server::set_pix_format(string message)
{
	string s = message.substr(4, message.size() - 3);
	this->settings->pix_format->bits_per_pixel = s[0];
	this->settings->pix_format->depth = s[1];
	this->settings->pix_format->big_endian_flag = s[2];
	this->settings->pix_format->true_color_flag = s[3];
	this->settings->pix_format->red_max = s[4] * 256 + s[5];
	this->settings->pix_format->green_max = s[6] * 256 + s[7];
	this->settings->pix_format->blue_max = s[8] * 256 + s[9];
	this->settings->pix_format->red_shift = s[10];
	this->settings->pix_format->green_shift = s[11];
	this->settings->pix_format->blue_shift = s[12];
}

void client_server::set_encoding(string message)
{
	int num_encoding = message[2] * 256 + message[3];
	string s = message.substr(4, message.size() - 3);
	for (int i = 0; i < num_encoding; i++)
		if (s[i * 4 + 3] != 16)
			this->encoding = s[i * 4 + 3];
}

void client_server::frame_buffer_update(string message)
{
	
}

void client_server::cut_text(string message)
{

}

void client_server::key_event(string message)
{

}

void client_server::pointer_event(string message)
{

}