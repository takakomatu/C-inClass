//************************************  PROGRAM IDENTIFICATION  **************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  test2-6.cpp          ASSIGNMENT #: 2           		            *
//*                                                                                           		  *
//*   PROGRAM AUTHOR:   Takaaki Komatsu													  	  *
//*                                                                                                   *
//*   COURSE #:  CSC 24400 21								   DUE DATE:  Febuary 17, 2018 	  *
//* 																								  *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  ******************************
//*                                                                                                   *
//*   PROCESS: This program is designed to read a list of data consisting of student     *
//*   identification numbers and their test averages. It is then to echo print the       *
//*   original list of students and scores. It is then to find and print the student     *                                                                 *
//*   with the lowest test score along with the students' identification number. It is   *                                                                                               *
//*   also to find the student with the highest test score and print the students' info  *
//*	   Finally, the program is to print the average test score for the entire class       *
//*   																								  *
//*   USER DEFINED                                                                       *
//*   MODULES     :  Header – make a header 								   					  *
//*                  printOriginal – print the original list of student     				  *
//*						bubbleSortForID - do bubble sort for ID							     *
//*                  printSortedByID – print sorted student data by ID	     			  *
//*						printAverage – print student data with their average and grades     *
//*						bubbleSortForAve - do bubble sort for average scores					 *
//*                  printSortedByaverage – print sorted student data by average         *
//*          			Footer – makes a footer 									  				  *
//*																									  *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

//number of rows and columns
const int r = 100;
const int c = 5;
double arrayStudentData[r][c]; //array that stores ID and scores
double arrayAverage[r][1];//array that stores average scores
char arrayLetterGrade[r][1];//array that stores letter grades

// Function prototypes
void Header();
void printOriginal(int size, double arrayStudentData[r][c]);
void bubbleSortForID(int size);
void printSortedByID(int size);
void printAverage(int size);
void bubbleSortForAve(int size);
void printSortedByaverage(int size);
void Footer();

//*************************************  FUNCTION MAIN  **********************************************
int main(){
// Receives – Nothing
// Task – Read an input file and creates 4 lists of students
// Returns – Integer 0
	ifstream file("data2.txt"); //read file whose name is dta2.txt
	int size = 0;
	int testScore = 0;
	double value;
	//store the info from the input file into the array
	while (file >> value) {
		if(value<0) // if the value is negative stop storing
			break;
		arrayStudentData[size][testScore] = value;
		testScore += 1;
		if (testScore >= 5) {//when we have a new ID, put them in the different row
			testScore = 0;
			size += 1;
		}
	}

	Header(); //make a header
	printOriginal(size, arrayStudentData); //print the original student data
	printSortedByID(size);//print the sorted list by ID
	printAverage(size);//print the list with their average score and grade
	printSortedByaverage(size);//print the sorted list by average score
	Footer();//make a header
	return 0;
}
//*************************************END OF FUNCTION MAIN*****************************************

//*************************************  FUNCTION HEADER  **********************************************
void Header() {
// Receives – Nothing
// Task – Prints the header
// Returns – nothing
	cout << "Takaaki Komatsu CSC 24400 Section 21" << endl;
	cout << "Spring 2018 Assignment #2 " << endl;
	cout << "----------------------------------------------------------------------" << endl;
}
//*************************************END OF FUNCTION HEADER  *****************************************

//*************************************  FUNCTION printOriginal  **********************************************
void printOriginal(int size, double arrayArg1[r][c]) {
// Receives – int size holds array's size and double arrayArg1[r][c] holds array of students
// Task – Prints the original student data
// Returns – nothing
	double arrayArg[r][c];//make arrayArg have info of students
	for (int i = 0; i < size; i += 1)
		for (int i2 = 0; i2 <= 4; i2 += 1)
			arrayArg[i][i2] = arrayArg1[i][i2];

	//start printing the list
	cout << "The original student data is:\n";
	cout << "Student ID      Test 1  Test 2   Test 3  Test 4\n";
	cout << "------------     --------  --------  --------  --------";
	cout << endl;

	for (int j = 0; j < size; j += 1) {
        printf("%7.0f    %12.1f   %7.1f   %7.1f   %7.1f", arrayArg[j][0], arrayArg[j][1], arrayArg[j][2], arrayArg[j][3], arrayArg[j][4]);
		 cout << endl;
	}
	cout << endl;
}
//*************************************END OF FUNCTION printOriginal  *****************************************

//*************************************  FUNCTION bubbleSortForID  **********************************************
void bubbleSortForID(int size){
	double buff0, buff1, buff2, buff3, buff4;
	for (int i = 0; i < (size - 1); i++) //do bubble sort from high to low
		for (int j = 0; j < (size - i - 1); j++)
			if (arrayStudentData[j][0] < arrayStudentData[j + 1][0]) {
				buff0 = arrayStudentData[j][0];
				buff1 = arrayStudentData[j][1];
				buff2 = arrayStudentData[j][2];
				buff3 = arrayStudentData[j][3];
				buff4 = arrayStudentData[j][4];

				arrayStudentData[j][0] = arrayStudentData[j + 1][0];
				arrayStudentData[j][1] = arrayStudentData[j + 1][1];
				arrayStudentData[j][2] = arrayStudentData[j + 1][2];
				arrayStudentData[j][3] = arrayStudentData[j + 1][3];
				arrayStudentData[j][4] = arrayStudentData[j + 1][4];

				arrayStudentData[j + 1][0] = buff0;
				arrayStudentData[j + 1][1] = buff1;
				arrayStudentData[j + 1][2] = buff2;
				arrayStudentData[j + 1][3] = buff3;
				arrayStudentData[j + 1][4] = buff4;
			}
}
//*************************************END OF FUNCTION bubbleSortForID  *****************************************

//*************************************  FUNCTION printSortedByID  **********************************************
void printSortedByID(int size) {
// Receives – int size holds array's size
// Task – Prints the list of sorted student data by ID
// Returns – nothing
	cout << "The list of students by ID Number high to low is:\n";//start printing list of students
	cout << "Student ID      Test 1  Test 2   Test 3  Test 4\n";
	cout << "------------     --------  --------  --------  --------\n";

	bubbleSortForID(size);//sort based on ID

	for (int j = 0; j < size; j += 1)//printing the list
       printf("%7.0f    %12.1f   %7.1f   %7.1f   %7.1f\n", arrayStudentData[j][0], arrayStudentData[j][1], arrayStudentData[j][2], arrayStudentData[j][3], arrayStudentData[j][4]);
	cout << endl;
}
//*************************************END OF FUNCTION printSortedByID  *****************************************

//*************************************  FUNCTION printAverage  **********************************************
void printAverage(int size) {
// Receives – int size holds array's size
// Task – Prints the list of student data with their test average and course grade
// Returns – nothing
	double sum = 0; //time to calculate the average scores then store them into arrayAverage
	for (int i = 0; i < size; i += 1) {
		sum = 0;
		for (int i2 = 1; i2 <= 4; i2 += 1) {
			 sum += arrayStudentData[i][i2];
			 if(i2==4)
			 	 arrayAverage[i][0] = sum / 4;
		}
	}
	double mean;
	for (int i = 0; i < size; i += 1) {
		mean = arrayAverage[i][0];//have arrayLetterGrade have the letter grades
		if(mean >= 90)
			arrayLetterGrade[i][0] = 'A';
		else if(mean >= 80)
			arrayLetterGrade[i][0] = 'B';
		else if(mean >= 70)
			arrayLetterGrade[i][0] = 'C';
		else if(mean >= 60)
			arrayLetterGrade[i][0] = 'D';
		else
			arrayLetterGrade[i][0] = 'F';
	}
	cout << "The list of students with their test average and course grade is:\n"
			"Student ID      Test 1  Test 2   Test 3  Test 4   Test Average   Course Grade\n"
			"------------     --------  --------  -------- --------   --------------   --------------\n";
	for (int j = 0; j < size; j += 1)
        printf("%7.0f    %10.1f   %5.1f   %6.1f   %5.1f   %9.2f   %10c\n", arrayStudentData[j][0], arrayStudentData[j][1], arrayStudentData[j][2], arrayStudentData[j][3], arrayStudentData[j][4], arrayAverage[j][0], arrayLetterGrade[j][0]);
	cout << endl;
}
//*************************************END OF FUNCTION printAverage  *****************************************

//*************************************  FUNCTION bubbleSortForAve  **********************************************
void bubbleSortForAve(int size){
	// Receives – int size holds array's size
	// Task – do bubble sort based on average scores
	// Returns – nothing
	double buff0, buff1, buff2, buff3, buff4, buff5, buff6;
	for (int i = 0; i < (size - 1); i++)//do bubble sort from high to low by average
		for (int j = 0; j < (size - i - 1); j++)
			if (arrayAverage[j][0] < arrayAverage[j + 1][0]) {
				buff0 = arrayStudentData[j][0];
				buff1 = arrayStudentData[j][1];
				buff2 = arrayStudentData[j][2];
				buff3 = arrayStudentData[j][3];
				buff4 = arrayStudentData[j][4];
				buff5 = arrayAverage[j][0];
				buff6 = arrayLetterGrade[j][0];

				arrayStudentData[j][0] = arrayStudentData[j + 1][0];
				arrayStudentData[j][1] = arrayStudentData[j + 1][1];
				arrayStudentData[j][2] = arrayStudentData[j + 1][2];
				arrayStudentData[j][3] = arrayStudentData[j + 1][3];
				arrayStudentData[j][4] = arrayStudentData[j + 1][4];
				arrayAverage[j][0] = arrayAverage[j + 1][0];
				arrayLetterGrade[j][0] = arrayLetterGrade[j + 1][0];
				arrayStudentData[j + 1][0] = buff0;
				arrayStudentData[j + 1][1] = buff1;
				arrayStudentData[j + 1][2] = buff2;
				arrayStudentData[j + 1][3] = buff3;
				arrayStudentData[j + 1][4] = buff4;
				arrayAverage[j + 1][0] = buff5;
				arrayLetterGrade[j + 1][0] = buff6;
			}
}
//*************************************END OF FUNCTION bubbleSortForAve  *****************************************

//*************************************  FUNCTION printSortedByaverage  **********************************************
void printSortedByaverage(int size) {
// Receives – int size holds array's size and double arrayArg5[r][c] holds array of students
// Task – Prints the sorted student data by average
// Returns – nothing
	bubbleSortForAve(size); //sort based on average scores

	//print out the list students sorted by test average
	cout << "The list of students sorted by test average high to low is:\n";
	cout << "Student ID      Test 1  Test 2   Test 3  Test 4   Test Average   Course Grade\n";
	cout << "------------     --------  --------  -------- --------   --------------   --------------\n";
	for (int j = 0; j < size; j += 1)
        printf("%7.0f    %10.1f   %5.1f   %6.1f   %5.1f   %9.2f   %10c\n", arrayStudentData[j][0], arrayStudentData[j][1], arrayStudentData[j][2], arrayStudentData[j][3], arrayStudentData[j][4], arrayAverage[j][0], arrayLetterGrade[j][0]);
}
//*************************************END OF FUNCTION printSortedByaverage  *****************************************

//*************************************  FUNCTION FOOTER  **********************************************
void Footer() {
// Receives – Nothing
// Task – prints out END OF PROGRAM OUTPUT
// Returns – Nothing

	cout << " -----------------------------\n";
	cout << "|   END OF PROGRAM OUTPUT |\n";
	cout << " -----------------------------";
}
//*************************************END OF FUNCTION FOOTER  *****************************************
