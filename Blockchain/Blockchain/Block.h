#pragma once
#include<iostream>
using namespace std;
class Block
{
	string proof,transaction,previousHash;
	bool verify();
	bool transact(string t);
};

