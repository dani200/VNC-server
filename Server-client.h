#pragma once
#include "server_utils.h"

class client_server
{
public:
	client_server(server_seetings* set);
	void DispatchM(SOCKET sock,string message);
private:
	server_seetings* settings;
	int encoding;
	void set_pix_format(string);
	void set_encoding(string);
	void frame_buffer_update(string);
	void key_event(string);
	void pointer_event(string);
	void cut_text(string);
};


