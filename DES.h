#pragma once
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

using std::string;
using std::cout;
using std::hex;

string gen_challenge(string password, long long int* msga);
string encrypt_16b(long long int* msg_, long long int* key_);
long long int sum_8(long long int* num_);
unsigned char reverseBits(unsigned char num);
