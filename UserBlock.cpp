#include "UserBlock.h"
#include "sha256.h"
#include <time.h>
#include <vector>
#include "md5.h"
#include "AES128.h"
UserBlock::UserBlock() : uName(""), pWordHash("")
{
    sHash = "";
    _tTime = time(nullptr);
    _nNonce = 0;
}

UserBlock::UserBlock(const string& uNameIn, const string& hashPwd, const string &e, const long long int &d) : uName(uNameIn), pWordHash(hashPwd), _privateKey(e)
{
    _publicKey = d;
    _nNonce = 0;
    _tTime = time(nullptr);
    sHash = _CalculateHash();
    if (uNameIn == "admin")
        return;
}
string UserBlock::getuName()
{
    return uName;
}
string UserBlock::getHashPword()
{
    return pWordHash;
}
long long int UserBlock::getPublicKey()
{
    return _publicKey;
}
string UserBlock::getPrivateKeyHash()
{
    return _privateKey;
}
void UserBlock::MineBlock(uint32_t nDifficulty)
{
    string str;
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        str.push_back('0');
    }

    do
    {
        _nNonce++;
        sHash = _CalculateHash();
    } while (!(str.compare(sHash.substr(0, nDifficulty)) == 0));

    cout << "Block mined: " << sHash << endl;
}

bool UserBlock::validate(uint32_t nd)
{
    string hash = _CalculateHash();
    string n;
    for (uint32_t i = 0; i < nd; i++)
    {
        n += '0';
    }
    if (hash == sHash)
    {
        if (hash.substr(0, nd) == n)
        {
            return true;
        }
    }
    return false;
}

inline string UserBlock::_CalculateHash() const
{
    stringstream ss;
    ss << sPrevHash << _tTime << _nNonce << uName << pWordHash << _publicKey << _privateKey;

    return sha256(ss.str());
}
