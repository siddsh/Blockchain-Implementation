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

bool Blockchain::checkID(string id)
{
    for (auto a : _vChain)
    {
        if (a.getID() == id)
            return false;
    }
    return true;
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

string Blockchain::getUser(long long int pub)
{
    for (auto a : _uChain)
    {
        if (a.getPublicKey() == pub)
            return a.getuName();
    }
    return "";
}

vector<Deets> Blockchain::getUserDeets(UserBlock u)
{
    vector<Deets> ret;
    for (Block bk : _vChain)
    {
        if (bk.getSPubK() == u.getPublicKey() && bk.getSender() == true)
        {
            bool rec = false;
            for (Block blk : _vChain)
            {
                if (bk.getID() == blk.getID() && blk.getSender() == false)
                {
                    rec = true;
                }
            }
            Deets tp = { bk, rec };
            ret.push_back(tp);
        }
        else if (bk.getRPubK() == u.getPublicKey() && bk.getSender() == true)
        {
            bool rec = false;
            for (Block blk : _vChain)
            {
                if (bk.getID() == blk.getID() && blk.getSender() == false)
                {
                    rec = true;
                }
            }
            Deets tp = { bk, rec };
            ret.push_back(tp);
        }
    }
    return ret;
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
                cout << "\nInvalid password" << endl;
                //system("pause");
                return out;
            }
        }
       
    }
    cout << "\nInvalid Username" << endl;
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

