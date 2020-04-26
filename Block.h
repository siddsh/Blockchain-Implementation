#pragma once
//#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Block {
public:
    Block();
    Block(const string& sID, const long long int& sPK, const long long int& rPK, bool send);

    void MineBlock(uint32_t nDifficulty);
    void setEncrHash(vector<long long int> &v);
    bool getSender();
    bool verify();
    long long int getSPubK();
    long long int getRPubK();
    string getID();

    string sHash;
    string sPrevHash;

private:
    bool _isSent;
    uint32_t _nNonce;
    int _nDiff;
    long long int _sPubK;
    long long int _rPubK;
    string _sShipmentID;
    string _CalculateHash() const;
    time_t _tTime;
    vector<long long int> _encryptedHash;
};
