#pragma once

//#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

class Block {
public:
    string sHash;
    string sPrevHash;
    bool isTransfer;
    Block(uint32_t nIndexIn, const string& sDataIn);
    uint32_t getIndex();
    void MineBlock(uint32_t nDifficulty);

private:
    uint32_t _nIndex;
    uint32_t _nNonce;
    string _sData;
    time_t _tTime;

    string _CalculateHash() const;
};
