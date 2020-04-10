#include "Block.h"
#include "sha256.h"
#include <time.h>
#include <vector>

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash();
    
}

void Block::MineBlock(uint32_t nDifficulty)
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
    }
    while (!(str.compare(sHash.substr(0, nDifficulty)) == 0));

    cout << "Block mined: " << sHash << endl;
}

inline string Block::_CalculateHash() const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << _nNonce;

    return sha256(ss.str());
}

uint32_t Block::getIndex()
{
    return _nIndex;
}
