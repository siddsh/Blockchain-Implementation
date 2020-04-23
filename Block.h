#pragma once
//#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Block {
public:
    string sHash;
    string sPrevHash;
    Block();
    Block(const string& sID, const long long int& sPK, const long long int& rPK, bool send);
    uint32_t getIndex();
    void MineBlock(uint32_t nDifficulty);
    void setEncrHash(vector<long long int> &v);
    long long int getSPubK();
    long long int getRPubK();
    string getID();
    bool getSender();
    bool verify();

private:
    bool _isSent;
    uint32_t _nIndex;
    uint32_t _nNonce;
    string _sShipmentID;
    long long int _sPubK;
    long long int _rPubK;
    time_t _tTime;
    vector<long long int> _encryptedHash;
    string _CalculateHash() const;
};
