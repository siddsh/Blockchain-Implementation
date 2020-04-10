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
    UserBlock(const string& uNameIn,const string& hashPwd);
    string getuName();
    string getHashPword();
    void MineBlock(uint32_t nDifficulty);

private:
    uint32_t _nIndex;
    uint32_t _nNonce;
    string uName;
    string pWordHash;
    time_t _tTime;

    string _CalculateHash() const;
};
