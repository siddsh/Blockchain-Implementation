#pragma once
#include <vector>
#include "Block.h"
#include "UserBlock.h"
using namespace std;

class Blockchain {
public:
    Blockchain(uint32_t nd);
    uint32_t _nDifficulty;
    void AddBlock(Block bNew);
    void AddBlock(UserBlock bNew);
    UserBlock checkCred(string uNameIn, string hashPwd);
    bool checkUname(string &uNameIn);
    uint32_t getLastIndex();
    long long int getPubK(string str);
    bool checkKey(long long int d);
    bool checkAuthenticity(long long int sender, long long int receiver, string id);
private:
    
    vector<Block> _vChain;

    vector<UserBlock> _uChain;

    Block _GetLastBlock() const;
    UserBlock _GetLastUserBlock() const;
};

