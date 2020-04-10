//
// Created by Dave Nash on 20/10/2017.
//

#include "Blockchain.h"

Blockchain::Blockchain()
{
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _uChain.emplace_back(UserBlock("admin", "admin"));
    _nDifficulty = 3;
}
uint32_t Blockchain::getLastIndex()
{
    return _GetLastBlock().getIndex();
}
void Blockchain::AddBlock(Block bNew)
{
    bNew.sPrevHash = _GetLastBlock().sHash;
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}
void Blockchain::AddBlock(UserBlock bNew)
{
    bNew.sPrevHash = _GetLastUserBlock().sHash;
    bNew.MineBlock(_nDifficulty);
    _uChain.push_back(bNew);
}
uint8_t Blockchain::checkCred(string uNameIn, string hashPwd)
{
    uint8_t out = -1;
    for (UserBlock ub : _uChain)
    {
        if (ub.getuName() == uNameIn)
        {
            out = 0;
            if (ub.getHashPword() == hashPwd)
            {
                out = 1;  
                return out;
            }
            else
            {
                return out;
            }
        }
       
    }
    return out;
    

}
Block Blockchain::_GetLastBlock() const
{
    if (!_vChain.empty())
        return _vChain.back();
}

UserBlock Blockchain::_GetLastUserBlock() const
{
    if (!_uChain.empty())
        return _uChain.back();
}

