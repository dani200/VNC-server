#pragma once
#include "DES.h"
#include <WinSock2.h>
#include <Windows.h>
#include <vector>

using std::vector;
#define BUFFER_S 1024

typedef struct pixel_format
{
	BYTE bits_per_pixel;
	BYTE depth;
	BYTE big_endian_flag;
	BYTE true_color_flag;
	WORD red_max;
	WORD green_max;
	WORD blue_max;
	BYTE red_shift;
	BYTE green_shift;
	BYTE blue_shift;
	WORD pad[3];
} pixel_format;

typedef struct server_settings
{
	WORD buffer_width;
	WORD buffer_height;
	pixel_format* pix_format;
	DWORD32 name_length;
	WORD* name;
} server_seetings;

void send_(SOCKET sock, string s);
string recv_(SOCKET sock);
bool VNC_auth(SOCKET sock, string password);
template<typename T>
void send_(SOCKET sock, T* data, int size);
string int_to_s(int* arr, int size);
string str_to_hex_s(string s);
bool auth(SOCKET sock, int code, string password);
