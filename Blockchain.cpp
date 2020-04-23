#include "Blockchain.h"
#include "sha256.h"
#include "AES128.h"
#include "MD5.h"

Blockchain::Blockchain(uint32_t nd)
{
    _nDifficulty = nd;
    _vChain.emplace_back(Block("", NULL, NULL, NULL));    
    _uChain.emplace_back(UserBlock("admin", sha256("admin"), AESencrypt(md5("admin"), "1"), 1));
    cout << "Blockchain Initialized" << endl;
}
uint32_t Blockchain::getLastIndex()
{
    return _GetLastBlock().getIndex();
}
long long int Blockchain::getPubK(string str)
{
    for (UserBlock ub : _uChain)
    {
        if (ub.getuName() == str)
        {
            return ub.getPublicKey();
        }
    }
    return -1;
}
bool Blockchain::checkKey(long long int d)
{
    for (UserBlock ub : _uChain)
    {
        if (ub.getPublicKey() == d)
        {
            return false;
        }

    }
    return true;
}
bool Blockchain::checkAuthenticity(long long int sender, long long int receiver, string id)
{
    bool a = false;
    for (Block b : _vChain)
    {
        if (b.getSPubK() == sender && b.getRPubK() == receiver && b.getID() == id && b.getSender() == true)
            a = true;
        else if (b.getSPubK() == sender && b.getRPubK() == receiver && b.getID() == id && b.getSender() == false)
            return false;
    }
    return a;
}
void Blockchain::AddBlock(Block bNew)
{
    bNew.sPrevHash = _GetLastBlock().sHash;
    //bNew.MineBlock(_nDifficulty);
   
    _vChain.push_back(bNew);
}
void Blockchain::AddBlock(UserBlock bNew)
{
    bNew.sPrevHash = _GetLastUserBlock().sHash;
    //bNew.MineBlock(_nDifficulty);
    _uChain.push_back(bNew);
}
UserBlock Blockchain::checkCred(string uNameIn, string hashPwd)
{
    UserBlock out;
    for (UserBlock ub : _uChain)
    {
        if (ub.getuName() == uNameIn)
        {
            if (ub.getHashPword() == hashPwd)
            { 
                return ub;
            }
            else
            {
                cout << "Invalid password" << endl;
                return out;
            }
        }
       
    }
    cout << "Invalid Username" << endl;
    return out;
}
bool Blockchain::checkUname(string &uNameIn)
{
    for (UserBlock ub : _uChain)
    {
        if (ub.getuName() == uNameIn)
            return false;
    }
    return true;
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

