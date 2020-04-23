#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

class UserBlock {
public:
    string sHash;
    string sPrevHash;
    int index;
    UserBlock();
    UserBlock(const string& uNameIn, const string& hashPwd, const string &e, const long long int &d);
    string getuName();
    string getHashPword();
    long long int getPublicKey();
    string getPrivateKeyHash();
    void MineBlock(uint32_t nDifficulty);
    bool validate(uint32_t nd);

private:
    uint32_t _nIndex;
    uint32_t _nNonce;
    string uName;
    string pWordHash;
    string _privateKey;
    long long int _publicKey;
    time_t _tTime;

    string _CalculateHash() const;
};
