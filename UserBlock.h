#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

class UserBlock {
public:
    string sHash;
    string sPrevHash;

    UserBlock();
    UserBlock(const string& uNameIn, const string& hashPwd, const string &e, const long long int &d);

    void MineBlock(uint32_t nDifficulty);
    bool validate(uint32_t nd);
    long long int getPublicKey();
    string getuName();
    string getHashPword();
    string getPrivateKeyHash();

private:
    uint32_t _nNonce;
    string _uName;
    string _pWordHash;
    string _privateKey;
    long long int _publicKey;
    time_t _tTime;

    string _CalculateHash() const;
};
