#include <iostream>
#include "sha256.h"
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    unsigned int i = 10;
    cout << "Task Chooser Menu\n";
    while (!(i <= 4))
    {
        cout << "0 Exit :\n";
        cout << "1 Transact(Create Block) \n";
        cout << "2 Verify Transaction \n";
        cout << "3 Mine Block (proof of work)\n";
        cout << "4 View User\n";
        cin >> i;
        if (i > 4)
        {
            cout << "Please input correct information\n";
        }
    }
    if (i == 0)
    {
        return;
    }
    else if (i == 1)
    {
        //Transaction create new block
        string sender, reciever, part_no, ;
    }
    else if (i == 2)
    {
        //verify transaction
    }
    else if (i == 3)
    {
        //mine block
    }
    else if (i == 4)
    {
        //view user
    }
    string output1;
    int a = 0,flag = 1;
    while (flag)
    {
        output1 = sha256(to_string(a));
        a++;
        if (output1[0]=='0' && output1[0] == output1[1] && output1[2]==output1[1])
        {
            flag = 0;
        }
        cout << output1 << endl;
    }
    
    return 0;
}