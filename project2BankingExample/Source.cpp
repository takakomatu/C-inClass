#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "Header.h"
using namespace std;

ifstream bankrecs;
ifstream transactions;
ofstream output;

const int rows = 50;
const int cols = 3;

int main() {
	int bank_records[rows][cols];  // 50 rows by 3 columns
	int num_records = 0;


	// open the files
	if (!open_input_file(bankrecs, "bankrecords.txt")) {
		return 1;
	}
	if (!open_input_file(transactions, "transactions.txt")) {
		return 2;
	}
	if (!open_output_file(output, "output.txt")) {
		return 3;
	}
	Header(output);
	read_bankrecs(bankrecs, bank_records, num_records);
	print_bankrecs(output, bank_records, num_records);

	bubble_sort(bank_records, num_records, 0);  // sort records by account number
	print_bankrecs(output, bank_records, num_records);
	bubble_sort(bank_records, num_records, 1);  // sort records by account type
	print_bankrecs(output, bank_records, num_records);
	bubble_sort(bank_records, num_records, 2);  // sort records by account balance
	print_bankrecs(output, bank_records, num_records);
	
	bubble_sort(bank_records, num_records, 0);  // sort by account number so we can process transactions
	read_transactions(transactions, bank_records, num_records);
	bubble_sort(bank_records, num_records, 2);  // sort records by account balance
	print_bankrecs(output, bank_records, num_records);
	Footer(output);
	//cout << "Enter any character to end the program" << endl;
	//char ch;
	//cin >> ch;
}

// -----------------------------------------------------------------------------	
bool open_input_file(ifstream &file, string filename) {

	cout << "opening " << filename << endl;
	file.open(filename.c_str());
	if (file.good()) {  // file input stream is in good shape
		return true;
	}
	else {	// we failed to open the file correctly
		cout << "Failed to open " << filename << " - exiting program" << endl;
		return false;
	}
}

// -----------------------------------------------------------------------------	
bool open_output_file(ofstream &file, string filename) {

	cout << "opening " << filename << endl;
	file.open(filename.c_str());
	if (file.good()) {  // file input stream is in good shape
		return true;
	}
	else {	// we failed to open the file correctly
		cout << "Failed to open " << filename << " - exiting program" << endl;
		return false;
	}
}

// -----------------------------------------------------------------------------
void close_file(ifstream &file, string filename) {

	cout << "closing " << filename << endl;
	file.close();
}

// -----------------------------------------------------------------------------
void Header(ofstream &Outfile)
{              // Receives - the output file
			   // Task - Prints the output preamble
			   // Returns - Nothing
	Outfile << setw(30) << "Lawrence Miller ";
	Outfile << setw(17) << "CSC 24400"; 
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Fall 2017";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(35) << "-----------------------------------";
	Outfile << setw(35) << "-----------------------------------" << endl << endl;
	return;
}

// -----------------------------------------------------------------------------
void Footer(ofstream &Outfile)
{
	// Receives - the output file
	// Task - Prints the output salutation
	// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;

	return;
}

// -----------------------------------------------------------------------------
int read_bankrecs(ifstream &bankrecs, int bank_records[rows][cols], int &num_records) {
	int accountnum, accounttype, accountbalance;

	while (true) {
		// process the next record in the file - we assume each record is complete and correct
		bankrecs >> accountnum;
		if (bankrecs.eof()) {
			return num_records;
		}
		bankrecs >> accounttype;
		bankrecs >> accountbalance;

		bank_records[num_records][0] = accountnum;
		bank_records[num_records][1] = accounttype;
		bank_records[num_records][2] = accountbalance;
		num_records++;
	}
}

// -----------------------------------------------------------------------------
int read_transactions(ifstream &transcations, int bank_records[rows][cols], int num_records) {
	// this function assumes that bank_records is sorted by accountnum
	int accountnum, amount;
	int num_transactions=0;
	int index = 0;
	cout << "Processing Transactions" << endl;
	while (true) {
		// process the next record in the file - we assume each record is complete and correct
		transactions >> accountnum;
		if (transactions.eof()) {
			return num_transactions;
		}
		cout << accountnum;

		transactions >> amount;
		cout << " " << amount << endl;

		index = find_record(bank_records, accountnum, 0, num_records-1);
		if (index >= 0) {
			bank_records[index][2] = bank_records[index][2] + amount;
		}
		else { cout << "account number not found\n"; }
		num_transactions++;
	}
}

// -----------------------------------------------------------------------------
int find_record(int bank_records[rows][cols], int accountnum, int low, int high) {
	// use binary search - assumes bank_records sorted by accountnum
	int mid;

	if (high < low)
		return -1;  // value not found in array
	mid = low + ((high - low) / 2);
//cout << "acctnum: " << accountnum << " low: " << low << " mid: " << mid << " high: " << high << " bank_record[mid][1]: " << bank_records[mid][1] << endl;
	if (bank_records[mid][0] < accountnum)
		return find_record(bank_records, accountnum, low, mid - 1);
	else if (bank_records[mid][1] > accountnum)
		return find_record(bank_records, accountnum, mid + 1, high);
	else return mid;
}

// -----------------------------------------------------------------------------

void bubble_sort(int A[rows][cols], int size, int keyindex) {
	int i, j;
	int buff0, buff1, buff2;

	for (i = 0; i < (size - 1); i++) 
		for (j = 0; j < (size - i - 1); j++) 
			if (A[j][keyindex] < A[j + 1][keyindex]) {
				buff0 = A[j][0];
				buff1 = A[j][1];
				buff2 = A[j][2];

				A[j][0] = A[j + 1][0];
				A[j][1] = A[j + 1][1];
				A[j][2] = A[j + 1][2];

				A[j + 1][0] = buff0;
				A[j + 1][1] = buff1;
				A[j + 1][2] = buff2;
			}
}

// -----------------------------------------------------------------------------
void print_bankrecs(ofstream &outfile, int bank_records[rows][cols], int num_records) {
	output << "Account  Account  Account" << endl;
	output << "Number   Type     Balance" << endl;
	output << "-------  -------  -------" << endl;
	for (int i = 0; i < num_records; i++) {
		outfile << setw(7) << left << bank_records[i][0] << "  " << setw(7) << bank_records[i][1] << "  " << setw(7) << bank_records[i][2] << endl;
	}
	output << endl << endl << endl;
}
