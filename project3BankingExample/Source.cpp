#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// -----------------------------------------------------------------------------	
ifstream bankrecs;
ifstream transactions;
ofstream output;

// -----------------------------------------------------------------------------	
// the main global data structures
int num_records;  // indicates how many customers there are - i.e., how many entries
                  // in the next 5 arrays are actually in use

int IDs[100];        // holds the customer ID numbers

string * name[100];  // points to memory on the heap to hold the customer name

int num_accts[100];  // Each customer can have up to 20 accounts - this array indicates
                     // how many accounts each customer has - i.e., how many entries the 
                     // arrays on the heap for the account numbers and balances actually have

int *acctnum[100];   // each entry in this array points the array on the heap for the 
                     // corresponding customer's account numbers

float *acctbal[100]; // each entry in this array points to the array on the heap for the 
                     // corresponding customer's account balance for each account number

// -----------------------------------------------------------------------------	
// function prototypes
void init_arrays();
bool open_input_file(ifstream &file, string filename); 
bool open_output_file(ofstream &file, string filename);
void close_file(ofstream &file);
void close_file(ifstream &file);
void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);
int read_bankrecs(ifstream &bankrecs);
int read_transactions(ifstream &transcations, ofstream &outfile); 
bool find_record(int accountnum, int &IDindex, int &acctnumindex);

void bubble_sort_ID();  // sort records by ID number
void bubble_sort_name();  // sort records by name 
void bubble_sort_acctnum();  // sort records by account number
void bubble_sort_acctbal();  // sort records by account balance

void print_ID(ostream &outfile);
void print_acctnum(ostream &outfile);

void deallocate();

// -----------------------------------------------------------------------------	
int main() {
        // start by initializing the arrays to reasonable values
        cout << "Initializing Arrays" << endl;
	init_arrays(); 

	// open the three files
        cout << "Opening Input / Output Files" << endl;
	if (!open_input_file(bankrecs, "bankrecords.txt")) {
                cout << "Error - Failed to open input file \"bankrecords.txt\"" << endl;
		return 1;  // indicate error message for failure to open file
	}
	if (!open_input_file(transactions, "transactions.txt")) {
                cout << "Error - Failed to open input file \"transactions.txt\"" << endl;
		return 2;  // indicate error message for failure to open file
	}
	if (!open_output_file(output, "output.txt")) {
                cout << "Error - Failed to open output file \"output.txt\"" << endl;
		return 3;  // indicate error message for failure to open file
	}
        // print out the required header information
	Header(output);    // print the header info to the output file

        // Now, read in the customer records from the "bankrecords.txt" file
	read_bankrecs(bankrecs);

        // Now, print out the customer records in ID format
	cout << endl << "Printing Records in ID format" << endl;
	print_ID(output);

        // Now, print out the customer records in acctnum format
	cout << endl << "Printing Records in account number format" << endl;
        print_acctnum(output);

	bubble_sort_ID();  // sort records by account number
	cout << endl << "Printing Records in ID format" << endl;
	print_ID(output);  // print records in ID format

	bubble_sort_name();  // sort records by account type
	cout << endl << "Printing Records in ID format" << endl;
	print_ID(output);    // print records in ID format
	
        // read in and process the account transactions from teh file "transactions.txt"
	read_transactions(transactions, output);
	cout << endl << "Printing Records in account number format" << endl;
	print_acctnum(output);  // print records in acctnum format

        // print out the required footer information
	Footer(output);

	deallocate();    // deallocate all the memory on the heap

	// close all of the files
	close_file(bankrecs);
	close_file(transactions);
	close_file(output);
}

// -----------------------------------------------------------------------------	
void init_arrays() {
	for (int i = 0; i < 100; i++) {
		IDs[i] = -1;       // set ID entries to invalid ID number
                name[i] = NULL;	   // set name pointers to NULL
		num_accts[i]=0;    // each customer has 0 accounts at this point
                acctnum[i] = NULL; // there are no arrays on the heap to hold the account numbers
		acctbal[i] = NULL; // there are no arrays on the heap to hold the balances
	}
	num_records = 0;  // there are no customer records yet
}

// -----------------------------------------------------------------------------	
bool open_input_file(ifstream &file, string filename) {

	cout << "opening " << filename << endl;

        // attempt to open the file
	file.open(filename.c_str());
	// check if the file stream is in a good state
	if (file.good()) {  
		return true;  // file input stream is in good shape
	}
	else {	// we failed to open the file correctly
		cout << "Failed to open " << filename << " - exiting program" << endl;
		return false;
	}
}

// -----------------------------------------------------------------------------	
bool open_output_file(ofstream &file, string filename) {

	cout << "opening " << filename << endl;

        // attempt to open the file
	file.open(filename.c_str());
	// check if the file stream is in a good state
	if (file.good()) {  
		return true;  // file input stream is in good shape
	}
	else {	// we failed to open the file correctly
		cout << "Failed to open " << filename << " - exiting program" << endl;
		return false;
	}
}

// -----------------------------------------------------------------------------
void close_file(ofstream &file) {
	// Receives - the output file stream to be closed
	// Task - close the file stream 
	// Returns - Nothing

	cout << "closing output file" << endl;
	// close the file stream
	file.close();
}

// -----------------------------------------------------------------------------
void close_file(ifstream &file) {
	// Receives - the input file stream to be closed
	// Task - close the file stream 
	// Returns - Nothing

	cout << "closing input file" << endl;
	// close the file stream
	file.close();
}

// -----------------------------------------------------------------------------
void Header(ofstream &Outfile)
{    	// Receives - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "Lawrence Miller";
	Outfile << setw(16) << "CSC 24400"; 
	Outfile << setw(17) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2018";
	Outfile << setw(20) << "Assignment #3" << endl;
	Outfile << setw(35) << "-----------------------------------";
	Outfile << setw(35) << "-----------------------------------" << endl << endl;
	return;
}

// -----------------------------------------------------------------------------
void Footer(ofstream &Outfile)
{	// Receives - the output file
	// Task - Prints the output salutation
	// Returns - Nothing

	Outfile << endl;
	Outfile << setw(35) << "---------------------------------- " << endl;
	Outfile << setw(35) << "|   END OF PROGRAM OUTPUT        | " << endl;
	Outfile << setw(35) << "---------------------------------- " << endl;
	return;
}

// -----------------------------------------------------------------------------
int read_bankrecs(ifstream &bankrecs) {
	// Receives - the input file stream for the "bankrecords.txt" file
	// Task - reads in the input file data, populating the global arrays with the data
	// Returns - number of customer records read in from the input file

        int countaccts;           // holds the number of accounts for the current customer
	int accountnum[20];       // temporarily stores the account numbers for the current customer
	float accountbalance[20]; // temporarily stores the account balances for the current customer 
	int id;                   // temporarily holds the customer id for the current customer
        string cname;             // temporarily holds the customer name for the current customer
	string str;               // temporarily holds the customer account number, as a string, for 
                                  // the current customer as its read in

        int number;               // temporarily holds the customer account number for the current customer
	float balance;            // temporarily holds the customer account balance for the current customer

        num_records = 0;	// initially, no customer records have been read in
        // the following loop is an infinite loop, the only way out of the loop is when EOF is encountered
	while (true) {
		// process the next record in the file - we assume each record is complete and correct
		bankrecs >> id;              // read in the customer id
		bankrecs >> ws;              // process any whitespace
		if (bankrecs.eof()) {        // check for EOF
			return num_records;  // if EOF encountered, return the number of records processed
		}
		IDs[num_records] = id;            // store the customer id in the IDs array
		getline(bankrecs, cname);         // read in the customer name
		string *ptr = new string(cname);  // allocate a string on the heap and initialize it to the customer name
		name[num_records] = ptr;          // make the customer's name entry point to the string on the heap

                countaccts = 0;                   // initially no accounts have been read in
                
                // the following loop is an infinite loop, the only way out of the loop is when a '>' is encountered 
                // when reading an account number
		while (true) {
			// process the next account number from the file
			bankrecs >> str;                              // store account number as string so it can be checked for marker '>'
			if (str == ">") {                             // compare the string to the marker '>'
				num_accts[num_records] = countaccts;  // have to store the number of accounts for this customer
				break;                                // we break out of the loop
			}
			stringstream ss1(str);                 // convert the string into a stringstream
                        ss1 >> number;                         // extract the account number from the stringstream
			accountnum[countaccts] = number;       // store the account number in the temporary array
			bankrecs >> balance;                   // read in the account balance
			accountbalance[countaccts] = balance;  // store the account balance in the temporary array
			countaccts++;                          // increment number of accounts for this customer
                }

                // now that we know how many accounts the customer has, allocate arrays of exactly that size on the heap
                // and copy the data from the temporary arrays into the arrays on the heap
		int *numptr = new int[countaccts];      // allocate array on heap for customers account numbers
	 	acctnum[num_records] = numptr;          // make the customers entry in the acctnum array point to this array on the heap
		float *balptr = new float[countaccts];  // allocate array on heap for customers account balances
	 	acctbal[num_records] = balptr;          // make the customers entry in the acctbal array point to this array on the heap

		// now we copy the data from the temporary arrays into the customers arrays on the heap
		for (int i = 0; i < countaccts; i++) {
			numptr[i] = accountnum[i];      // copy account number from temporary array to array on heap for customer
			balptr[i] = accountbalance[i];  // copy account balance from temporary array to array on heap for customer
                }
		num_records++;   // increment number of customer records read in from the input file
	}
}

// -----------------------------------------------------------------------------
int read_transactions(ifstream &transcations, ofstream &outfile) {
	// Receives - the input file stream for the "transactions.txt" file
	// Task - reads in the input file data, searches for the account number, and if found, updates the account balance 
	// Returns - number of transactions read in from the input file

	int accountnum;          // temporarily holds the account number read from the file
	float amount;            // temporarily holds the credit/debit amount read from the file
	int num_transactions=0;  // keeps track of the number of transactions processed
	int IDindex = -1;        // holds the record number for the cusomer if the account number was located
	int acctnumindex=-1;     // holds the record number for the cusomer's account on the heap, if the account number was located
	bool found;              // identifies whether the account number searched for was located or not

	outfile << endl;
	outfile << "==============================================================================================" << endl;

	outfile << endl <<  "Processing Transactions" << endl;
        // the following loop is an infinite loop, the only way out of the loop is when EOF is encountered
        while (true) {
		// process the next record in the file - we assume each record is complete and correct
		transactions >> accountnum;          // read in the account number
		if (transactions.eof()) {
			return num_transactions;     // if we encountered the EOF, then return the number of transactions processed
		}
		outfile << accountnum;               // output the account number to the output file
		transactions >> amount;              // read in the account balance
		outfile << " " << amount << endl;    // output the account balance to the output file

		// now we search for the account number - if found, IDindex indicates which customer record contains the account and
		// acctnumindex indicates which entry in the account numbers and account balance arrays on the heap contain the account number
		found = find_record(accountnum, IDindex, acctnumindex);   
		if (found) {
                        // we found the account - so update the account balance
			outfile << "Account " << accountnum << " found - updating balance from ";
			float *ptr = acctbal[IDindex];                    // get pointer to the customer's account balance array
			outfile << ptr[acctnumindex] << " to ";
			ptr[acctnumindex] = ptr[acctnumindex] + amount;   // update the account balance
			outfile << ptr[acctnumindex] << endl;
		}
		else { 
			outfile << "account number not found\n"; 
		}
		num_transactions++;    // increment the number of transactions processed
	}
}

// -----------------------------------------------------------------------------
bool find_record(int accountnum, int &IDindex, int &acctnumindex) {
	// Receives - the account number to locate, the customer record index variable, and the account number index variable
	// Task - searches each customer's records until we find the account number
	// Returns - true if account number found, otherwise returns false

	// use linear search on the customer records and use linear search on the account numbers for each customer
	for (int i = 0; i < num_records; i++) {            // i indicates the current customer record
		int *ptr = acctnum[i];                     // get a pointer to the customer's account number array on the heap
		for (int j = 0; j < num_accts[i]; j++) {   // j indicates teh current account for the current customer
			if (accountnum == ptr[j]) {        // check if the jth entry of the array contains the account number
				IDindex = i;               // if so, set the array index variables to the correct values
				acctnumindex = j;
				return true;               // we found the record, so return true
			}
		}
	}
	// if we reach this point, we did not find the account number, so set index variables appropriately and return false
	IDindex = -1;
	acctnumindex = -1;
	return false;
}

// -----------------------------------------------------------------------------
void bubble_sort_ID() {
	// Receives - nothing (works on the global arrays)
	// Task - sorts the global arrays into descending order of customer ID
	// Returns - nothing

	int i, j;            // index variables for indexing through the customer records and the customer accounts
	int tempid;          // temp variable to hold customer ID
	int tempnumaccts;    // temp variable to hold customer's number of accounts
	string *tmpnameptr;  // temp variable to hold pointer to customer's name
	int *tmpnumptr;      // temp variable to hold pointer to customer's account numbers
	float *tmpbalptr;    // temp variable to hold pointer to customer's account balances

cout << "executing bubblesort" << endl;
	for (i = 0; i < (num_records - 1); i++) 
		for (j = 0; j < (num_records - i - 1); j++) 
			if (IDs[j] < IDs[j + 1]) {              // check if adjacent elements need to be swapped
				// swap IDs
				tempid = IDs[j];
				IDs[j] = IDs[j+1];
				IDs[j+1] = tempid;

				// swap names
				tmpnameptr = name[j];
				name[j] = name[j+1];
				name[j+1] = tmpnameptr;

				// swap number of accounts
				tempnumaccts = num_accts[j];
				num_accts[j] = num_accts[j+1];
				num_accts[j+1] = tempnumaccts;
				
				//swap account numbers
				tmpnumptr = acctnum[j];
				acctnum[j] = acctnum[j+1];
				acctnum[j+1] = tmpnumptr;

				//swap account balances
				tmpbalptr = acctbal[j];
				acctbal[j] = acctbal[j+1];
				acctbal[j+1] = tmpbalptr;
			}
}

// -----------------------------------------------------------------------------
void bubble_sort_name() {  // sort records by name 
	// Receives - nothing (works on the global arrays)
	// Task - sorts the global arrays into ascending order of customer name
	// Returns - nothing

	int i, j;            // index variables for indexing through the customer records and the customer accounts
	int tempid;          // temp variable to hold customer ID
	int tempnumaccts;    // temp variable to hold customer's number of accounts
	string *tmpnameptr;  // temp variable to hold pointer to customer's name
	int *tmpnumptr;      // temp variable to hold pointer to customer's account numbers
	float *tmpbalptr;    // temp variable to hold pointer to customer's account balances

cout << "executing bubblesort" << endl;
	for (i = 0; i < (num_records - 1); i++) 
		for (j = 0; j < (num_records - i - 1); j++) 
			if (*name[j] > *name[j + 1]) {          // check if adjacent elements need to be swapped
				// swap IDs
				tempid = IDs[j];
				IDs[j] = IDs[j+1];
				IDs[j+1] = tempid;

				// swap names
				tmpnameptr = name[j];
				name[j] = name[j+1];
				name[j+1] = tmpnameptr;

				// swap number of accounts
				tempnumaccts = num_accts[j];
				num_accts[j] = num_accts[j+1];
				num_accts[j+1] = tempnumaccts;
				
				//swap account numbers
				tmpnumptr = acctnum[j];
				acctnum[j] = acctnum[j+1];
				acctnum[j+1] = tmpnumptr;

				//swap account balances
				tmpbalptr = acctbal[j];
				acctbal[j] = acctbal[j+1];
				acctbal[j+1] = tmpbalptr;
			}
}

// -----------------------------------------------------------------------------
void print_ID(ostream &outfile) { 
	// Receives - the output file stream
	// Task - prints the customer record information in ID format
	// Returns - nothing

	int i, j;            // index variables for indexing through the customer records and the customer accounts
	outfile << fixed << setprecision(2) << setfill(' ');
	outfile << endl;
	outfile << "==============================================================================================" << endl;
	outfile << "                                          Account    Account" << endl;
	outfile << "   ID                  Name               Number     Balance" << endl;
	outfile << "--------  ------------------------------  -------  ------------" << endl;

	// loop to process all customer records
	for (int i = 0; i < num_records; i++) {
		// output the customer's ID and name
                outfile << setw(8) << right << IDs[i] << "  " << setw(30) << left << *name[i] << endl;

		// set pointers to the arrays holding the customer's account numbers and balances
                int *numptr = acctnum[i];
                float *balptr = acctbal[i];

		// loop to process a customers accounts
                for (int j = 0; j < num_accts[i]; j++) {
			int anum = numptr[j];           // get the account number from the customer's array on the heap
			float bal = balptr[j];          // get the account balance from the customer's array on the heap

			// generate the output to the file for the account
			outfile << setw(38) << "                                          ";
			outfile << setw(7) << right << anum << "  " << setw(12) << right << bal << endl;
		}
	}
}

// -----------------------------------------------------------------------------
void print_acctnum(ostream &outfile) { 
	// Receives - the output file stream
	// Task - prints the customer record information in acctnum format
	// Returns - nothing

	outfile << fixed << setprecision(2) << setfill(' ');
	outfile << endl;
	outfile << "==============================================================================================" << endl;
	outfile << "                                          Account    Account" << endl;
	outfile << "   ID                  Name               Number     Balance" << endl;
	outfile << "--------  ------------------------------  -------  ------------" << endl;
	// loop to process all customer records
	for (int i = 0; i < num_records; i++) {
		// loop to process a customers accounts
                for (int j = 0; j < num_accts[i]; j++) {
			// output the customer's ID and name
			outfile << setw(8) << right << IDs[i] << "  " << setw(30) << right << *name[i] << "  ";

			// set pointers to the arrays holding the customer's account numbers and balances
               		int *numptr = acctnum[i];
               		float *balptr = acctbal[i];

			int anum = numptr[j];           // get the account number from the customer's array on the heap
			float bal = balptr[j];          // get the account balance from the customer's array on the heap

			// generate the output to the file for the account
			outfile << setw(7) << right << anum << "  " << setw(12) << right << bal << endl;
		}
	}
}

// -----------------------------------------------------------------------------
void deallocate() {
	for (int i = 0; i < num_records; i++) {  // we must do the following for every customer record
		// we have to deallocate the string on the heap
		delete name[i];

		// we have to deallocate the array on the heap for the current record's account numbers
		delete [] acctnum[i];

		// we have to deallocate the array on the heap for the current record's account balances
		delete [] acctbal[i];
	}
}
