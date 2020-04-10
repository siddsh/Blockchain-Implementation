#include "UserBlock.h"
#include "sha256.h"
#include <time.h>
#include <vector>

UserBlock::UserBlock(const string& uNameIn, const string& hashPwd) : uName(uNameIn), pWordHash(hashPwd)
{
    _nNonce = 0;
    _tTime = time(nullptr);
    sHash = _CalculateHash();
}
string UserBlock::getuName()
{
    return uName;
}
string UserBlock::getHashPword()
{
    return pWordHash;
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

inline string UserBlock::_CalculateHash() const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _nNonce << uName << pWordHash ;

    return sha256(ss.str());
}
