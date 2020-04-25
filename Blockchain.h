#pragma once
#include <vector>
#include "Block.h"
#include "UserBlock.h"
using namespace std;

struct Deets
{
    Block blk;
    bool isRec;
};

class Blockchain {
public:
    Blockchain(uint32_t nd);

    void AddBlock(Block bNew);
    void AddBlock(UserBlock bNew);
    bool checkID(string id);
    bool checkKey(long long int d);
    bool checkAuthenticity(long long int sender, long long int receiver, string id);
    bool checkUname(string& uNameIn);
    long long int getPubK(string str);
    string getUser(long long int pub);
    UserBlock checkCred(string uNameIn, string hashPwd);
    vector<Deets> getUserDeets(UserBlock u);

    uint32_t _nDifficulty;
private:
    Block _GetLastBlock() const;
    UserBlock _GetLastUserBlock() const;

    vector<Block> _vChain;
    vector<UserBlock> _uChain;
};

