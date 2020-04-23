#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

class RSA
{
private:
	int x, y;
	long long int n, phi;

	int gcd(int a, int b);
	unsigned long long int cd(unsigned long long int a);

public:
	RSA(string file);
	//RSA(long long int);
	void encryption_key(long long int& e, long long int& d);
	void RSAencrypt(const long long int& e, string msg, vector<long long int>& en);
	void RSAdecrypt(const long long int& d, vector<long long int>& en, string& m);
};