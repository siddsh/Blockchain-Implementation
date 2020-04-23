#include "Blockchain.h"
#include "sha256.h"
#include <conio.h>
#include <time.h>
#include "MD5.h"
#include "RSA.h"
#include "AES128.h"
using namespace std;
//Block
uint32_t nDifficulty = 4;


void getpWord(string& pWord)
{
    char c = _getch();
    while (c != '\r')
    {
        if (c == '\b' && !pWord.empty()) {
            pWord.pop_back();
            c = _getch();
            continue;
        }
        pWord += c;
        c = _getch();
    }
}
void generateKey(string& e, long long int& d, Blockchain& chain, string& pWord)
{
    RSA rsa("values");
    long long int e1;
    while (true)
    {
        rsa.encryption_key(e1, d);
        //cout << endl << e1 << "\t" << d << endl;
        if (chain.checkKey(d))
        {
            stringstream ss;
            ss << hex << e1;
            e = AESencrypt(md5(pWord), ss.str());
            ss.str(string());
            return;
        }
    }
}
bool regi(Blockchain& bChain)
{
    string pWord, uName;
    cout << "\nRegistration Menu";
    cout << "\nEnter your desired username:";
    cin >> uName;
    //check username
    if (bChain.checkUname(uName))
    {
        cout << "\nEnter your desired password:";
        getpWord(pWord);
        cout << endl;
        cout << "\nCreating User block...\n";
        string e;
        long long int d = NULL;
        generateKey(e, d, bChain, pWord);
        UserBlock b(uName, sha256(pWord), e, d);
        cout << "\nMining User block...\n";
        b.MineBlock(nDifficulty);
        //Validate
        cout << "\nValidating User block\n";
        if (b.validate(nDifficulty))
        {
            //Add block
            cout << "User Block validated" << endl;
            bChain.AddBlock(b);
            cout << "\nUser Block added\n";
        }
        else
        {
            cout << "Invalid User block";
        }
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
bool login(Blockchain &bChain, UserBlock& user)
{
    string pWord, uName;
    cout << "\nLogin Menu";
    cout << "\nEnter your username:";
    cin >> uName;
    cout << "\nEnter your password:";
    getpWord(pWord);
    cout << endl;
    //check
    user = bChain.checkCred(uName, sha256(pWord));
    //correct details
    if (user.getuName() == uName)
    {
        cout << "\nWelcome " << uName;
        return true;
        pWord = "";
    }
    return false;
}
int main()
{    
    srand(time(NULL));
    Blockchain bChain = Blockchain(nDifficulty);
    //CHOOSE
    while (true)
    {
        int choice = -1, iteration = 0;
        choice = -1;
        bool correctUserCred = false;
        UserBlock user;
        while (!(choice >= 1 && choice <= 2))
        {
            if (iteration)
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
                correctUserCred = login(bChain, user);
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
        bool isExit = false;
        while (!isExit)
        {
            //CHOOSE
            while (!(choice >= 1 && choice <= 5))
            {
                if (iteration)
                {
                    cout << "Please enter correct choice";
                }
                cout << "\nMenu" << endl;
                cout << "1: Transfer" << endl;
                cout << "2: Recieved" << endl;
                cout << "3: Show My Shipment (Show User)" << endl;
                cout << "4: Logout" << endl;
                cout << "5: Exit" << endl;
                cout << "Enter your choice: ";
                iteration++;
                cin >> choice;
            }
            iteration = 0;
            if (choice == 1) //Transfer
            {
                choice = -1;
                //Validate
                //Ask
                bool passowrdCorrect = false;
                //check for PK
                //Enter Password
                while (!passowrdCorrect)
                {
                    string pWord;
                    cout << "\nEnter password: ";
                    getpWord(pWord);
                    cout << endl;
                    //check
                    //Check password hash
                    if (user.getHashPword() == sha256(pWord))
                    {
                        passowrdCorrect = true;
                        string id;
                        long long int rPK;
                        cout << "Enter your shipment id:";
                        cin >> id;
                        cout << "Enter recievers username:";
                        string un;
                        cin >> un;
                        rPK = bChain.getPubK(un);
                        if (rPK == user.getPublicKey())
                        {
                            cout << "Cannot Ship to Oneself" << endl;
                        }
                        else if (rPK > 0)
                        {
                            //Decrypt the private key in userblock
                            //cout << "Decrypting the private key in the user block by AES128 where key is SHA1 of your password\n";
                            stringstream ss;
                            string e1 = user.getPrivateKeyHash();
                            e1 = AESdecrypt(md5(pWord), e1);
                            ss << e1;
                            long long int e;
                            ss >> hex >> e;
                            //Create Block
                            cout << "Creating block...\n";
                            Block transaction(id, user.getPublicKey(), rPK, true);
                            //Block transaction(id, user.getPublicKey(), rPK, true);
                            //Mine Block
                            cout << "Mining block...\n";
                            transaction.MineBlock(nDifficulty);
                            vector<long long int> encrhash;
                            RSA rsa("values");
                            rsa.RSAencrypt(e, transaction.sHash, encrhash);
                            transaction.setEncrHash(encrhash);
                            //Encrypt block hash using RSA private key

                            //Validate Block
                            cout << "\nVerifying block...\n";
                            if (transaction.verify())
                            {
                                cout << "Transaction Verified!\n";
                                cout << "Adding block...\n";
                                bChain.AddBlock(transaction);
                                transaction = Block();
                            }
                            else
                            {
                                cout << "Transaction Failed!\n";
                            }
                        }
                        else
                        {
                            cout << "Invalid Recievers Username\n";
                        }
                        //Add Block
                    }
                    else
                    {
                        cout << "Invalid Password, Please Enter correct password\n";
                    }
                }
            }
            else if (choice == 2) //Recieved
            {
                choice = -1;
                //check DEST UNAME == uName
                //Ask PW
                //Validate
                //Ask
                bool passowrdCorrect = false;
                //check for PK
                //Enter Password
                while (!passowrdCorrect)
                {
                    string pWord;
                    cout << "\nEnter password: ";
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
                    //Check password hash
                    if (user.getHashPword() == sha256(pWord))
                    {
                        passowrdCorrect = true;
                        string id;
                        long long int sPK;
                        cout << "Enter your shipment id :";
                        cin >> id;
                        cout << "Enter senders username:";
                        string un;
                        cin >> un;
                        sPK = bChain.getPubK(un);
                        if (sPK > 0)
                        {
                            //Decrypt the private key in userblock
                            stringstream ss;
                            string e1 = user.getPrivateKeyHash();
                            e1 = AESdecrypt(md5(pWord), e1);
                            ss << e1;
                            long long int e;
                            ss >> hex >> e;
                            //Check sent && !received
                            if (bChain.checkAuthenticity(sPK, user.getPublicKey(), id))
                            {
                                //Create Block
                                cout << "Creating block...\n";
                                Block transaction(id, sPK, user.getPublicKey(), false);

                                //Mine Block
                                cout << "Mining block...\n";
                                transaction.MineBlock(nDifficulty);

                                //Encrypt block hash using RSA private key
                                vector<long long int> encrhash;
                                RSA rsa("values");
                                rsa.RSAencrypt(e, transaction.sHash, encrhash);
                                transaction.setEncrHash(encrhash);

                                //Validate Block
                                cout << "\nVerifying block...\n";
                                if (transaction.verify())
                                {
                                    cout << "Transaction Verified!\n";
                                    //ADD BLOCK
                                    cout << "Adding block...\n";
                                    bChain.AddBlock(transaction);
                                    transaction = Block();
                                    choice = -1;
                                }
                                else
                                {
                                    cout << "Transaction Failed!\n";
                                }
                            }
                            else
                            {
                                cout << "Invalid Shipment" << endl;
                            }

                        }
                        else
                        {
                            cout << "Invalid Username, Please Enter Correct Username\n";
                        }
                    }
                    else
                    {
                        cout << "Invalid Password, Please Enter Correct Password\n";
                    }
                }
            }
            else if (choice == 3) //USER
            {
                choice = -1;
                vector<Deets> userDeets;
                userDeets = bChain.getUserDeets(user);
                if (userDeets.size() == 0)
                {
                    cout << "No Packages in History" << endl;
                }
                else
                {
                    //U is sender
                    int count = 0;
                    cout << "\n\nShipments Sent by you:\n";
                    for (int i = 0; i < userDeets.size(); i++)
                    {
                        if (user.getPublicKey() == userDeets[i].blk.getSPubK())
                        {
                            count++;
                            cout << "\t" << count << "." << endl;
                            cout << "\t\tReceiver's Username: " << bChain.getUser(userDeets[i].blk.getRPubK()) << endl;
                            cout << "\t\tShipment ID: " << userDeets[i].blk.getID() << endl;
                            if (userDeets[i].isRec)
                            {
                                cout << "\t\tShipment Received" << endl;
                            }
                            else
                            {
                                cout << "\t\tShipment in Transit" << endl;
                            }
                        }
                    }
                    if (!count)
                    {
                        cout << "\tYou Haven't Sent any Shipments\n";
                    }
                    //U is reciever
                    count = 0;
                    cout << "\nShipments Sent To You:" << endl;
                    for (int i = 0; i < userDeets.size(); i++)
                    {
                        if (user.getPublicKey() == userDeets[i].blk.getRPubK())
                        {
                            count++;
                            cout << "\t" << count << "." << endl;
                            cout << "\t\tSender's Username: " << bChain.getUser(userDeets[i].blk.getSPubK()) << endl;
                            cout << "\t\tShipment ID: " << userDeets[i].blk.getID() << endl;
                            if (userDeets[i].isRec)
                            {
                                cout << "\t\tShipment Received" << endl;
                            }
                            else
                            {
                                cout << "\t\tShipment in Transit" << endl;
                            }
                        }
                    }
                    if (!count)
                    {
                        cout << "\tYou aren't the Recipient of any Shipments\n";
                    }
                }
            }
            else if (choice == 4)
            {
                break;
            }
            else if (choice == 5) //Validate
            {
                return 0;
            }
        }
    }
    
    return 0;
}
