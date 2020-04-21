#pragma once

#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

typedef bitset<8> byte;
typedef bitset<32> word;

word Word(byte& k1, byte& k2, byte& k3, byte& k4);
word RotWord(word& rw);
word SubWord(word& sw);
void KeyExpansion(byte key[16], word w[44]);

void SubBytes(byte mtx[4 * 4]);
void ShiftRows(byte mtx[4 * 4]);
byte GFMul(byte a, byte b);
void MixColumns(byte mtx[4 * 4]);
void AddRoundKey(byte mtx[4 * 4], word k[4]);
void transpose(byte mtx[16]);

void InvSubBytes(byte mtx[4 * 4]);
void InvMixColumns(byte mtx[4 * 4]);

string AESencrypt(string iv, string pt);

string AESdecrypt(string iv, string ct);


void hex_toLL(string hex, long long int out);