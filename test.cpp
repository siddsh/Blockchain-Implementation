#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream f;
	string file = "values";
    f.open(file, ios::binary | ios::out);
	int x;
	cin >> x;
	f.write((char*)&x, sizeof(x));
	cin >> x;
	f.write((char*)&x, sizeof(x));
	f.close();
}