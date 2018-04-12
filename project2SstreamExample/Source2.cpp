#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int MaxCust = 100;
ifstream infile("TextFile2.txt");

int ID[MaxCust];
string Name[MaxCust];
float balance[MaxCust];

int main() {
	string str;
	char ch;
	int index = 0;
	getline(infile, str, ':');  // read a line into string str
	while (!infile.eof()) {
		stringstream ss(str); // convert string str to a stream ss
		ss >> ID[index];   // extract integer from stream ss
		infile >> ws;
		getline(infile, str, ':');   // read a line into string str
		Name[index] = str;
		getline(infile, str);	// read a line into string str
		stringstream ss2(str);	// convert string str to a stream ss
		ss2 >> balance[index];  // extract float from stream ss
		cout << "ID: " << ID[index] << " Name: " << Name[index] << " balance: " << balance[index] << endl;
		index++;
		getline(infile, str, ':');  // read a line into string str
	}
	cout << "There were " << index << "records" << endl;
}
