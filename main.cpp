#include "Blockchain.h"
#include "sha256.h"
#include <conio.h>
int main()
{
    Blockchain bChain = Blockchain();
    int choice = -1, iteration = 0;
    string uName, pWord;
    bool correctUserCred = false;
    while (!(choice >= 1 && choice <= 2))
    {
        if (!iteration)
        {
            cout << "Please enter correct choice\n";
        }
        cout << "Menu" << endl;
        cout << "1: Login" << endl;
        cout << "2: Register" << endl;
        cout << "Enter your choice: ";
        iteration++;
        cin >> choice;
    }
    while (!correctUserCred)
    {
        if (choice == 1)
        {
            cout << "\nLogin Menu";
            cout << "\nEnter your username:";
            cin >> uName;
            cout << "\nEnter your password:";
            char c = _getch();
            while (c != '\r')
            {
                if (c == '\b') {
                    pWord.pop_back();
                    c = _getch();
                    continue;
                }
                pWord += c;
                c = _getch();
            }
            cout << endl;
            //check
            uint8_t check = bChain.checkCred(uName, sha256(pWord));
            if (check == 1)
            {
                cout << "\nWelcome " << uName;
                correctUserCred = true;
            }
            else if (check == 0)
            {
                cout << "\nInvalid Password";
            }
            else
            {
                cout << "\nInvalid Username";
            }
            pWord = "";
            uName = "";
        }
        if (choice == 2)
        {
            //REG
            cout << "\nRegistration Menu";
            cout << "\nEnter your desired username:";
            cin >> uName;

            //check username
            cout << "\nEnter your desired password:";
            char c = _getch();
            while (c != '\r')
            {
                if (c == '\b') {
                    pWord.pop_back();
                    c = _getch();
                    continue;
                }
                pWord += c;
                c = _getch();
            }
            cout << endl;
            bChain.AddBlock(UserBlock(uName, sha256(pWord)));
            pWord = "";
            uName = "";
            choice = 1;
        }
    }

    cout << "Mining block 1..." << endl;
    bChain.AddBlock(Block(bChain.getLastIndex() + 1, uName));

    cout << "Mining block 2..." << endl;
    bChain.AddBlock(Block(bChain.getLastIndex() + 1, "Block 2 Data"));

    cout << "Mining block 3..." << endl;
    bChain.AddBlock(Block(bChain.getLastIndex() + 1, "Block 3 Data"));

    return 0;
}
