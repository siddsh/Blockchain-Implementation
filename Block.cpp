#include "Block.h"
#include "sha256.h"
#include <time.h>
#include <vector>
#include "RSA.h"

Block::Block()
{
    _isSent = NULL;
    _nNonce = NULL;
    sHash = "";
    _sShipmentID = "";
    _sPubK = NULL;
    _rPubK = NULL;
}

Block::Block(const string &sID, const long long int &sPK, const long long int& rPK, bool send): _sShipmentID(sID), _sPubK(sPK), _rPubK(rPK)
{
    _isSent = send;
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash();   
    if (sID != "")
    {
        cout << "Transaction Block Created with ID: " << _sShipmentID << endl;
    }
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

long long int Block::getSPubK()
{
    return _sPubK;
}

long long int Block::getRPubK()
{
    return _rPubK;
}

string Block::getID()
{
    return _sShipmentID;
}

bool Block::getSender()
{
    return _isSent;
}

void Block::setEncrHash(vector<long long int> &v)
{
    _encryptedHash = v;
}

bool Block::verify()
{
    string n;
    for (int i = 0; i < _nNonce; i++)
    {
        n += '0';
    }
    string file = "values";
    cout << "Decrypting the stored Encrypted hash by RSA with user's Public key\n";
    string decryptedHash;
    decryptedHash = RSADecrypt(file, _sPubK, _encryptedHash);
    if (decryptedHash == sHash && n == sHash.substr(0, _nNonce))
    {
        return true;
    }
    else
    {
        decryptedHash = RSADecrypt(file, _sPubK, _encryptedHash);
        if (decryptedHash == sHash && n == sHash.substr(0, _nNonce))
        {
            return true;
        }
    }
    return false;
}

inline string Block::_CalculateHash() const
{
    stringstream ss;
    ss << sPrevHash << _tTime << _sShipmentID << _sPubK << _rPubK << _nNonce << _isSent;

    return sha256(ss.str());
}
