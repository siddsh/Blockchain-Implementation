#pragma once

//#include <cstdint>
#include <vector>
#include "Block.h"
#include "UserBlock.h"
using namespace std;

class Blockchain {
public:
    Blockchain();

    void AddBlock(Block bNew);
    void AddBlock(UserBlock bNew);
    uint8_t checkCred(string uNameIn, string hashPwd);
    uint32_t getLastIndex();
private:
    uint32_t _nDifficulty;
    vector<Block> _vChain;

    vector<UserBlock> _uChain;

    Block _GetLastBlock() const;
    UserBlock _GetLastUserBlock() const;
};

