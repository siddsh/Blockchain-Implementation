#include "RSA.h"

int RSA::gcd(int a, int b) {
    int t;
    while (1) {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}

//function to generate encryption key
void RSA::encryption_key(long long int& e, long long int& d)
{
    unsigned long long int k;
    k = 0;
    //t = phi
    while (true)
    {
        e = (rand() % (phi - 2)) + 2;
        if (gcd(e, phi) == 1)
        {
            d = cd(e);
            return;
        }
    }
}

unsigned long long int RSA::cd(unsigned long long int a)
{
    unsigned long long int k = 1;
    while (k < phi)
    {
        if ((k * a) % phi == 1)
        {
            return k;
        }
        k++;
    }
    return NULL;
}

//function to encrypt the message
void RSA::RSAencrypt(const long long int& e, string msg, vector<long long int>& en)
{
    long long int pt = 0, k = 0;
    en.clear();
    int len = 0;
    int i = 0;
    len = msg.length();

    while (i < len)
    {
        pt = msg[i];
        k = 1;
        for (int j = 0; j < e; j++)
        {
            k *= pt;
            k %= n;
        }
        //cout << k << "\t";
        en.push_back(k);
        i++;
    }
}


//function to decrypt the message
void RSA::RSAdecrypt(const long long int& d, vector<long long int>& en, string& m)
{
    long long int ct = 0, k = 0;
    m = "";
    int len = en.size();
    int i = 0;
    while (i < len)
    {
        ct = en[i];
        k = 1;
        for (int j = 0; j < d; j++)
        {
            k *= ct;
            k %= n;
        }
        m.push_back(k);
        i++;
    }
    //cout << endl;
}

RSA::RSA(string file)
{
    /*fstream f;
    f.open(file, ios::binary | ios::in);
    f.read((char*)&x, sizeof(x));
    f.read((char*)&y, sizeof(y));
    f.close();*/
    x = 23;
    y = 19;
    n = long long int(x) * long long int(y);
    phi = n - x - y + 1;
}