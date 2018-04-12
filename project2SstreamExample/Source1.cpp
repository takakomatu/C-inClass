 #include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int MaxCust = 100;
ifstream infile("TextFile1.txt");

int ID[MaxCust];
string Name[MaxCust];
float balance[MaxCust];

int main() {
	string str;
	char ch;
	int index = 0;
	infile >> ID[index];

	while (!infile.eof()) {
		infile >> ws;
		string str;
		getline(infile, str);
		Name[index] = str;
		infile >> balance[index];
		cout << "ID: " << ID[index] << endl;
		cout << "Name: " << Name[index] << endl;
		cout << "Balance: " << balance[index] << endl;
		index++;
		infile >> ID[index];
	}

	cout << "There were " << index << "records" << endl;
}
