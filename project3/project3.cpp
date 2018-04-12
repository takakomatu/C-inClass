//************************************  PROGRAM IDENTIFICATION  **************************
//*                                                                                      *
//*   PROGRAM FILE NAME:  project3.cpp          ASSIGNMENT #: 3           		         *
//*                                                                                      *
//*   PROGRAM AUTHOR:   Takaaki Komatsu													 *
//*                                                                                      *
//*   COURSE #:  CSC 24400 21								   DUE DATE:  March 23, 2018 *
//* 																					 *
//****************************************************************************************

//***********************************  PROGRAM DESCRIPTION  ******************************
//*                                                                                      *
//*   PROCESS: This program is designed to read a list of data consisting of student     *
//*   identification numbers, names and their test scores. It is then to echo print the  *
//*   original list of students and scores. It is then to find and print the student     *
//*   with the lowest ID numbers along with the students' other info. It is              *
//*   also to sort the data along the students' last name. It is also to find the        *
//*	  student with the highest test score and print the students' info                   *
//*   Finally, the program is to print the average test score for the entire class.      *
//*																					     *
//*   USER DEFINED                                                                       *
//*   MODULES     :  Header – make a header 								   			 *
//*                  printOriginal – print the original list of student     			 *
//*					 bubbleSortForID - do bubble sort for ID							 *
//*                  printSortedByID – print sorted student data by ID	     			 *
//*					 open_output_file - check if output file is opened					 *
//*					 printData - print original data on the output file					 *
//*					 printOutputSortedByID - print sorted students list by ID on output  *
//*					 printOutputSortedByName - print sorted list by name on output		 *
//*					 printOutputWithAverage - print students list with averages on output*
//*					 printOutputSortedByAverage - print sorted list by average on output *
//*					 close_file - close the output file									 *
//*					 void bubbleSortForName - do bubble sort for last name from A to Z	 *
//*					 void printSortedByName - print sorted student data by last name 	 *
//*					 printAverage – print student data with their average and grades     *
//*					 bubbleSortForAve - do bubble sort for average scores			     *
//*                  printSortedByaverage – print sorted student data by average         *
//*          		 Footer – makes a footer 									     	 *
//*																						 *
//****************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

ofstream output; // for output.txt

const int r = 100; // number of rows
int IDs[r]; // array that stores ID
string *name[r][2]; // string pointer for first and last name
float *scores[r];// float string for scores and average scores
char letter[r];// array that stores letter grades

// Function prototypes
void Header();
void Header(ofstream &Outfile);
bool open_output_file(ofstream &file, string filename);
void printOriginal(int size);
void bubbleSortForID(int size);
void printSortedByID(int size);
void bubbleSortForName(int size);
void printSortedByName(int size);
void printAverage(int size);
void bubbleSortForAve(int size);
void printSortedByaverage(int size);
void Footer();
void Footer(ofstream &Outfile);
void printData(ostream &outfile, int size);
void printOutputSortedByID(ostream &outfile, int size);
void printOutputSortedByName(ostream &outfile, int size);
void printOutputWithAverage(ostream &outfile, int size);
void printOutputSortedByAverage(ostream &outfile, int size);
void close_file(ofstream &file);

int main(){
// Receives – Nothing
// Task – Read an input file and creates lists of students
// Returns – Integer 0
	ifstream file("data3.txt"); //read file whose name is data3.txt
	int size, count = 0; // initialize size of array and count for array
	float testScores = 0; // initialize a variable for test scores
	int id; // a variable for storing a value of ID
	string fname, lname; // variables for storing first name and last name

	// the next block reads info and stores info from data file to arrays
	while(true){
		file >> id;
		if(id>=0) // unless the value of ID is less than 0, read ID and store it into IDs array
			IDs[count] = id;
		else
			break; // if ID is less than 0, stop reading and storing
		file >> fname; // read fist name from the data file
		file >> lname; // read last name from the data file
		name[count][0] = new string; // let the pointer point at an object on heap
		name[count][1] = new string; // let the pointer point at an object on heap
		*(name[count][0]) = fname; // assign first name
		*(name[count][1]) = lname; // assign last name
		float *foo = new float[5]; // make a float pointer that points at an object on heap

		// the loop below is for calculating the average score and storing scores to foo
		for(int j=0;j<4;j++){
			file >> testScores; // read test scores
			foo[j] = testScores; // assign test scores to array foo.
			float sum, average;
			if(j==0) // make sum 0 whenever the loop hits the first test score of a student
				sum = 0;
			sum += testScores;
			if(j==3){ // if the loop meets the last test score of a student, calculate the average
				average = sum / 4.0;
				foo[4] = average;
			}
		}
		scores[count] = foo; // now scores points to an array
		count++;
	}
	size = count; // let size be equal to count

	if (!open_output_file(output, "output.txt")) { // check if the output.txt opens or not
		cout << "Error - Failed to open output file \"output.txt\"" << endl;
		return 1;  // indicate error message for failure to open file
	}
	Header(); // make a header
	Header(output); // print the header info to the output file
	printOriginal(size); // print the original student data
	printData(output, size); // print data on output file
	printSortedByID(size); // print the sorted list by ID
	printOutputSortedByID(output, size); // print data on output file
	printSortedByName(size); // print the sorted list by last names from A to Z
	printOutputSortedByName(output, size); // print data on output file
	printAverage(size); // print the list with their average score and grade
	printOutputWithAverage(output, size); // prints the students record information with average scores and letter grades on the output file
	printSortedByaverage(size); // print the sorted list by average score
	printOutputSortedByAverage(output, size); // prints the sorted students record information with average scores and letter grades on the output file
	Footer(); // make a header
	Footer(output); // print the footer info to the output file
	close_file(output); // close output.txt

	// foo loop is to recover and reuse memory that is no longer being accessed
	for(int i=0;i<size;i++){

		// the block will recover and reuse memory related to foo that is no longer being accessed
		float *foo2 = scores[i];
		delete [] foo2;
		scores[i] = NULL;

		// the block will recover and reuse memory related to name that is no longer being accessed
		delete name[i][0];
		delete name[i][1];
	}

	return 0; // end of main
}

void Header() {
// Receives – Nothing
// Task – Prints the header
// Returns – nothing

	// print a header
	cout << "Takaaki Komatsu CSC 24400 Section 21" << endl;
	cout << "Spring 2018 Assignment #3 " << endl;
	cout << "----------------------------------------------------------------------\n" << endl;
}

void Header(ofstream &Outfile){
   	// Receives - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	// print a header on the output file
	output << "Takaaki Komatsu CSC 24400 Section 21" << endl;
	output << "Spring 2018 Assignment #3 " << endl;
	output << "----------------------------------------------------------------------\n" << endl;
}

void Footer(ofstream &Outfile){
	// Receives - the output file
	// Task - Prints the output salutation on the output file
	// Returns - Nothing

	// make a footer
	output << " -----------------------------\n";
	output << "|   END OF PROGRAM OUTPUT    |\n";
	output << " -----------------------------";
}

bool open_output_file(ofstream &file, string filename) {
	// Receives - ofstream &file holds the output file and string filename has the output file name.
	// Task - check if the output file can be opened or no
	// Returns - boolean

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

void printOriginal(int size) {
// Receives – int size holds array's size and a number of students who were read
// Task – Prints the original student data
// Returns – nothing

	// start printing list of students
	cout << "The original student data is:\n";
	cout << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	cout << "------------ ----------- ----------   --------  --------  --------  --------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
        printf("%8.4i %13s %13s %8.1f %8.1f %9.1f %9.1f", IDs[j], (*(name[j][0])).c_str(), (*(name[j][1])).c_str(), (scores[j])[0], (scores[j])[1], (scores[j])[2], (scores[j])[3]);
        cout << endl;
	}
	cout << endl;
}

void bubbleSortForID(int size){
	// Receives – int size holds array's size
	// Task – do bubble sort based on ID
	// Returns – nothing

	// start doing bubble sort
	double buff0, buff3, buff4, buff5, buff6, buff7; // variables to back up the previous info
	string buff1, buff2; // variables to back up the previous info, names
	for (int i = 0; i < (size - 1); i++) // Proceed until everything is sorted in order
		for (int j = 0; j < (size - i - 1); j++)
			if (IDs[j] < IDs[j + 1]) { // check if adjacent elements need to be swapped
				buff0 = IDs[j]; // back up IDs, names, and scores
				buff1 = *(name[j][0]);
				buff2 = *(name[j][1]);
				buff3 = (scores[j])[0];
				buff4 = (scores[j])[1];
				buff5 = (scores[j])[2];
				buff6 =	(scores[j])[3];
				buff7 = (scores[j])[4];

				IDs[j] = IDs[j + 1]; // swap IDs, names and scores
				*name[j][0] = *(name[j + 1][0]);
				*name[j][1] = *(name[j + 1][1]);
				(scores[j])[0] = (scores[j + 1])[0];
				(scores[j])[1] = (scores[j + 1])[1];
				(scores[j])[2] = (scores[j + 1])[2];
				(scores[j])[3] = (scores[j + 1])[3];
				(scores[j])[4] = (scores[j + 1])[4];

				IDs[j + 1] = buff0; // swap IDs, names, and scores
				*name[j + 1][0] = buff1;
				*name[j + 1][1] = buff2;
				(scores[j + 1])[0] = buff3;
				(scores[j + 1])[1] = buff4;
				(scores[j + 1])[2] = buff5;
				(scores[j + 1])[3] = buff6;
				(scores[j + 1])[4] = buff7;
			}
}

void printSortedByID(int size) {
// Receives – int size holds array's size
// Task – Prints the list of sorted student data by ID
// Returns – nothing

	// start printing list of students
	cout << "The list of students by ID Number high to low is:\n"; // start printing list of students
	cout << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	cout << "------------ ----------- ----------   --------  --------  --------  --------\n";

	bubbleSortForID(size); // do bubble sort based on ID from high to low

	// the loop below is for printing out sorted IDs, names, and scores by ID number
	for (int j = 0; j < size; j += 1){
        printf("%8.4i %13s %13s %8.1f %8.1f %9.1f %9.1f", IDs[j], (*(name[j][0])).c_str(), (*(name[j][1])).c_str(), (scores[j])[0], (scores[j])[1], (scores[j])[2], (scores[j])[3]);
        cout << endl;
	}
	cout << endl;
}

void bubbleSortForName(int size){
	// Receives – int size holds array's size
	// Task – do bubble sort based on one's last name from A to Z
	// Returns – nothing

	// start doing bubble sort for name
	double buff0, buff3, buff4, buff5, buff6, buff7; // variables to back up the previous info
	string buff1, buff2; // variables to back up the previous info, names

	 // The next block proceeds until everything is sorted in order
	for (int i = 0; i < (size - 1); i++) // do bubble sort from high to low
		for (int j = 0; j < (size - i - 1); j++)
			if (*(name[j][1]) > *(name[j+1][1])) { // check if adjacent elements need to be swapped
				buff0 = IDs[j]; // back up IDs, names, and scores
				buff1 = *(name[j][0]);
				buff2 = *(name[j][1]);
				buff3 = (scores[j])[0];
				buff4 = (scores[j])[1];
				buff5 = (scores[j])[2];
				buff6 =	(scores[j])[3];
				buff7 = (scores[j])[4];

				IDs[j] = IDs[j + 1]; // swap IDs, names and scores
				*name[j][0] = *(name[j + 1][0]);
				*name[j][1] = *(name[j + 1][1]);
				(scores[j])[0] = (scores[j + 1])[0];
				(scores[j])[1] = (scores[j + 1])[1];
				(scores[j])[2] = (scores[j + 1])[2];
				(scores[j])[3] = (scores[j + 1])[3];
				(scores[j])[4] = (scores[j + 1])[4];

				IDs[j + 1] = buff0; // swap IDs, names and scores
				*name[j + 1][0] = buff1;
				*name[j + 1][1] = buff2;
				(scores[j + 1])[0] = buff3;
				(scores[j + 1])[1] = buff4;
				(scores[j + 1])[2] = buff5;
				(scores[j + 1])[3] = buff6;
				(scores[j + 1])[4] = buff7;
			}
}

void printSortedByName(int size){
	// Receives – int size holds array's size
	// Task – Prints the sorted student data by last name alphabetically
	// Returns – nothing

	// start printing list of students
	cout << "The list of students by Last Name from A to Z:\n"; // start printing list of students
	cout << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	cout << "------------ ----------- ----------   --------  --------  --------  --------\n";

	bubbleSortForName(size); // sort based on last name from A to Z

	// the loop below is for printing out IDs, names, and scores
	for (int j = 0; j < size; j += 1){
        printf("%8.4i %13s %13s %8.1f %8.1f %9.1f %9.1f", IDs[j], (*(name[j][0])).c_str(), (*(name[j][1])).c_str(), (scores[j])[0], (scores[j])[1], (scores[j])[2], (scores[j])[3]);
        cout << endl;
	}
	cout << endl;
}

void printAverage(int size) {
// Receives – int size holds array's size and the number of students who were read in
// Task – Prints the sorted student data by average
// Returns – nothing

	// the chunk below is for assigning the letter grades to letter array based on the average scores.
	double mean;
	for (int i = 0; i < size; i += 1) {
		mean = (scores[i])[4];
		if(mean >= 90)
			letter[i] = 'A';
		else if(mean >= 80)
			letter[i] = 'B';
		else if(mean >= 70)
			letter[i] = 'C';
		else if(mean >= 60)
			letter[i] = 'D';
		else
			letter[i] = 'F';
	}

	// start printing list of students
	cout << "The list of students with their test average and course grade is:\n";
	cout << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4    Test Average    Course Grade\n";
	cout << "------------ ----------- ----------   --------  --------  --------  --------  ---------------  ---------------\n";

	// the loop below is for printing out IDs, names, scores, average scores, and letter grades.
	for (int j = 0; j < size; j += 1){
        printf("%8.4i %13s %13s %8.1f %8.1f %9.1f %9.1f %13.2f %13c", IDs[j], (*(name[j][0])).c_str(), (*(name[j][1])).c_str(), (scores[j])[0], (scores[j])[1], (scores[j])[2], (scores[j])[3], (scores[j])[4], letter[j]);
        cout << endl;
	}
	cout << endl;
}

void bubbleSortForAve(int size){
	// Receives – int size holds array's size and the number of students data that was read in
	// Task – do bubble sort based on average scores
	// Returns – nothing

	// start doing bubble for for average scores
	double buff0, buff3, buff4, buff5, buff6, buff7; // variables to back up the previous info
	string buff1, buff2; // variables to back up the previous info, names.
	char buff8; // a variable to back up the previous info, letter grades.

	 // The next block proceeds until everything is sorted in order
	for (int i = 0; i < (size - 1); i++) // do bubble sort based on average scores from high to low
		for (int j = 0; j < (size - i - 1); j++)
			if ((scores[j])[4] < (scores[j+1])[4]) { // check if adjacent elements need to be swapped
				buff0 = IDs[j]; // back up IDs, names, scores, average scores, and letter grades.
				buff1 = *(name[j][0]);
				buff2 = *(name[j][1]);
				buff3 = (scores[j])[0];
				buff4 = (scores[j])[1];
				buff5 = (scores[j])[2];
				buff6 =	(scores[j])[3];
				buff7 = (scores[j])[4];
				buff8 = letter[j];

				IDs[j] = IDs[j + 1]; // swap IDs, names, scores, average scores, and letter grades
				*name[j][0] = *(name[j + 1][0]);
				*name[j][1] = *(name[j + 1][1]);
				(scores[j])[0] = (scores[j + 1])[0];
				(scores[j])[1] = (scores[j + 1])[1];
				(scores[j])[2] = (scores[j + 1])[2];
				(scores[j])[3] = (scores[j + 1])[3];
				(scores[j])[4] = (scores[j + 1])[4];
				letter[j] = letter[j+1];

				IDs[j + 1] = buff0; // swap IDs, names, scores, average scores, and letter grades
				*name[j + 1][0] = buff1;
				*name[j + 1][1] = buff2;
				(scores[j + 1])[0] = buff3;
				(scores[j + 1])[1] = buff4;
				(scores[j + 1])[2] = buff5;
				(scores[j + 1])[3] = buff6;
				(scores[j + 1])[4] = buff7;
				letter[j+1] = buff8;
			}
}

void printSortedByaverage(int size) {
// Receives – int size holds array's size and the number of students data that was read in
// Task – Prints the sorted student data by average
// Returns – nothing

	bubbleSortForAve(size); //sort based on average scores

	//print out the list students sorted by test average
	cout << "The list of students sorted by test average high to low is:\n";
	cout << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4    Test Average    Course Grade\n";
	cout << "------------ ----------- ----------   --------  --------  --------  --------  ---------------  ---------------\n";

	// a loop to print out IDs, names, scores, average scores, and letter grades.
	for (int j = 0; j < size; j += 1){
        printf("%8.4i %13s %13s %8.1f %8.1f %9.1f %9.1f %13.2f %13c", IDs[j], (*(name[j][0])).c_str(), (*(name[j][1])).c_str(), (scores[j])[0], (scores[j])[1], (scores[j])[2], (scores[j])[3], (scores[j])[4], letter[j]);
        cout << endl;
	}
	cout << endl;
}

void close_file(ofstream &file) {
	// Receives - the output file stream to be closed
	// Task - close the file stream
	// Returns - Nothing

	// close the file stream
	file.close();
}

void printData(ostream &outfile, int size) {
	// Receives - the output file stream and int size holds array's size and the number of students data that was read in
	// Task - prints the students record information
	// Returns - nothing

	// start printing list of students on the output file
	outfile << "The original student data is:\n";
	outfile << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	outfile << "------------ ----------- ----------   --------  --------  --------  --------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
        outfile << fixed << left << setprecision(1) << setw(13) << IDs[j] << setw(13) << (*(name[j][0])).c_str() << setw(13) << (*(name[j][1])).c_str() << setw(11) << (scores[j])[0] << setw(11) << (scores[j])[1] << setw(11) << (scores[j])[2] << setw(11) << (scores[j])[3] << endl;
	}
	outfile << endl;
}

void printOutputSortedByID(ostream &outfile, int size){
	// Receives - the output file stream and int size holds array's size and the number of students data that was read in
	// Task - prints the students record information
	// Returns - nothing

	// start printing list of students on the output file
	outfile << "The list of students sorted by ID number high to low is:\n";
	outfile << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	outfile << "------------ ----------- ----------   --------  --------  --------  --------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
        outfile << fixed << left << setprecision(1) << setw(13) << IDs[j] << setw(13) << (*(name[j][0])).c_str() << setw(13) << (*(name[j][1])).c_str() << setw(11) << (scores[j])[0] << setw(11) << (scores[j])[1] << setw(11) << (scores[j])[2] << setw(11) << (scores[j])[3] << endl;
	}
	outfile << endl;
}
void printOutputSortedByName(ostream &outfile, int size){
	// Receives - the output file stream and int size holds array's size and the number of students data that was read in
	// Task - prints the sorted students record information by last names from A to Z to the output file
	// Returns - nothing

	// start printing list of students on the output file
	outfile << "The list of students sorted by Last Nmae from A to Z:\n";
	outfile << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4\n";
	outfile << "------------ ----------- ----------   --------  --------  --------  --------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
        outfile << fixed << left << setprecision(1) << setw(13) << IDs[j] << setw(13) << (*(name[j][0])).c_str() << setw(13) << (*(name[j][1])).c_str() << setw(11) << (scores[j])[0] << setw(11) << (scores[j])[1] << setw(11) << (scores[j])[2] << setw(11) << (scores[j])[3] << endl;
	}
	outfile << endl;
}

void printOutputWithAverage(ostream &outfile, int size){
	// Receives - the output file stream and int size holds array's size and the number of students data that was read in
	// Task - prints the students record information with average scores and letter grades on the output file
	// Returns - nothing

	//print out the list students sorted by test average on the output file
	outfile << "The list of students with their test average and course grade is:\n";
	outfile << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4    Test Average    Course Grade\n";
	outfile << "------------ ----------- ----------   --------  --------  --------  --------  ---------------  ---------------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
		outfile << fixed << left << setprecision(1) << setw(13) << IDs[j] << setw(13) << (*(name[j][0])).c_str() << setw(13) << (*(name[j][1])).c_str() << setw(11) << (scores[j])[0] << setw(11) << (scores[j])[1] << setw(11) << (scores[j])[2] << setw(11) << (scores[j])[3] << setw(17) << setprecision(2)<< (scores[j])[4] << setw(17) << letter[j] << endl;
	}
	outfile << endl;
}
void printOutputSortedByAverage(ostream &outfile, int size){
	// Receives - the output file stream and int size holds array's size and the number of students data that was read in
	// Task - prints the sorted students record based on average scores with average scores and letter grades on the output file
	// Returns - nothing

	bubbleSortForAve(size); //sort based on average scores

	//print out the list students sorted by test average on the output file
	outfile << "The list of students sorted by test average high to low is:\n";
	outfile << "Student ID    FirstName    LastName    Test 1     Test 2   Test 3    Test 4    Test Average    Course Grade\n";
	outfile << "------------ ----------- ----------   --------  --------  --------  --------  ---------------  ---------------\n";

	// the loop below prints out the original student data that consists of IDs, names, and test scores.
	for (int j = 0; j < size; j += 1) {
		outfile << fixed << left << setprecision(1) << setw(13) << IDs[j] << setw(13) << (*(name[j][0])).c_str() << setw(13) << (*(name[j][1])).c_str() << setw(11) << (scores[j])[0] << setw(11) << (scores[j])[1] << setw(11) << (scores[j])[2] << setw(11) << (scores[j])[3] << setw(17) << setprecision(2)<< (scores[j])[4] << setw(17) << letter[j] << endl;
	}
	outfile << endl;
}

void Footer() {
// Receives – Nothing
// Task – prints out END OF PROGRAM OUTPUT
// Returns – Nothing

	// these are for printing out footer.
	cout << " -----------------------------\n";
	cout << "|   END OF PROGRAM OUTPUT    |\n";
	cout << " -----------------------------";
}
