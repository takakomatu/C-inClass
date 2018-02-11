//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  myProject2.cpp          ASSIGNMENT #: 2           					      *
//*                                                                                           		  *
//*   PROGRAM AUTHOR:   																  *
//*                                                                                                   *
//*   COURSE #:  								   DUE DATE:  Febuary 17, 2018 	 		  *
//* 																								  *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:       *
//*
//*     *                                                                 *
//*                                                                                                   *
//*   USER DEFINED                                                                       	          *
//*    MODULES     : openDocument – opens the document   								              *
//*                  Header – make a header             											  *
//*                  outputHeader – outputs Standard Deviation Tutorial, surrounded by h1 tag	      *
//*                  generateFirstRow – generates the first two rows 								  *
//*                  generateRow – makes a row that contains information required to make the table   *
//*                  outputCloseTable – closes the table											  *
//*					 generateSummary – prints out information on data such as sample size and so on   *
//*   				 Footer – prints out END OF PROGRAM OUTPUT, surrounded by horizontal lines 		  *
//*   				 closeDocument – closes the document											  *
//*																									  *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
const int r = 100;
const int c = 4;

// Function prototypes
void Header();
void printOriginal(int size, double arrayArg1[r][c]);

//*************************************  FUNCTION MAIN  **********************************************
int main(){
// Receives – Nothing
// Task – Creates a html document based on the user's input
// Returns – Integer 0
	ifstream file("data2.txt");
	double arrayTestScore[r][c];
	int size = 0;
	int testScore = 0;
	double value;
	while (file >> value) {
		arrayTestScore[size][testScore] = value;
		testScore += 1;
		if (testScore >= 5) {
			testScore = 0;
			size += 1;
		}
	}
	cout << arrayTestScore[0][0] << endl;
	cout << size << endl;

	Header();
	return 0;
}
//*************************************END OF FUNCTION MAIN*****************************************

//*************************************  FUNCTION HEADER  **********************************************
void Header() {
// Receives – Nothing
// Task – Prints the header
// Returns – nothing
	cout << "Takaaki Komatsu CSC 24400 Section 21" << endl;
	cout << "Spring 2018 Assignment #1 " << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "The original student data is:\n";
	cout << "Student ID     Test 1  Test 2  Test 3  Test 4\n";
	cout << "----------     ------  ------  ------  ------";
	cout << endl;
}
//*************************************END OF FUNCTION HEADER  *****************************************

//*************************************  FUNCTION printOriginal  **********************************************
void printOriginal(int size, double arrayArg1[r][c]) {
// Receives – Nothing
// Task – Prints the original student data
// Returns – nothing
	double arrayArg[r][c];
	for (int i = 0; i < 100; i += 1) {
		for (int i2 = 0; i2 <= 3; i2 += 1) {
			arrayArg[i][i2] = arrayArg1[i][i2];
		}
	}

	for (int j = 0; j < size; j += 1) {
         printf("%9.0f      %5.1f   %5.1f   %5.1f   %5.1f", arrayArg[j][0], arrayArg[j][1], arrayArg[j][2], arrayArg[j][3], arrayArg[j][4]);
		 cout << endl;
	}
	cout << endl;
}
//*************************************END OF FUNCTION HEADER  *****************************************

