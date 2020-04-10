#include "Blockchain.h"
#include "sha256.h"
#include <conio.h>
string uName;
bool regi(Blockchain& bChain)
{
    string pWord;
    cout << "\nRegistration Menu";
    cout << "\nEnter your desired username:";
    cin >> uName;
    //check username
    if (bChain.checkUname(uName))
    {
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
        return true;
    }
    else
    {
        cout << "Username taken";
        return false;
    }
}
bool login(Blockchain &bChain)
{
    string pWord;
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
    //correct details
    if (check == 1)
    {
        cout << "\nWelcome " << uName;
        return true;
        pWord = "";
    }
    //wrong pwd
    else if (check == 0)
    {
        cout << "\nInvalid Password";
        pWord = "";
        uName = "";
    }
    //both wrong
    else
    {
        cout << "\nInvalid Username";
        pWord = "";
        uName = "";
    }
    return false;
}
int main()
{
    Blockchain bChain = Blockchain();
    int choice = -1, iteration = 0;
    bool correctUserCred = false;
    //CHOOSE
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
    while (!correctUserCred)//LOGIN OR REG
    {
        if (choice == 1)//Login
        {
            correctUserCred = login(bChain);
        }
        if (choice == 2)//Register
        {
            if (regi(bChain))//Check uname taken 
            {
                choice = 1;
            }
        }
    }
    //USER LOGGED IN
    choice = -1, iteration = 0;
    //CHOOSE
    while (!(choice >= 1 && choice <= 3))
    {
        if (iteration)
        {
            cout << "Please enter correct choice";
        }
        cout << "\nMenu" << endl;
        cout << "1: Transfer" << endl;
        cout << "2: Recieved" << endl;
        cout << "3: Show My Shipment" << endl;
        cout << "4: Logout" << endl;
        cout << "Enter your choice: ";
        iteration++;
        cin >> choice;
    }
    if (choice == 1) //Transfer
    {
        //(uName, DEST UNAME, Shipment details)
        // Ask password

    }
    else if (choice == 2) //Recieved
    {
        //check DEST UNAME == uName
    }
    else if (choice == 3) 
    {
        //check 
    }

    return 0;
}
