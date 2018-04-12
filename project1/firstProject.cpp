//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  firstProject.cpp          ASSIGNMENT #: 1           					      *
//*                                                                                           		  *
//*   PROGRAM AUTHOR:   Takaaki Komatsu																  *
//*                                                                                                   *
//*   COURSE #:  CSC 24400 21								   DUE DATE:  January 25, 2018 	 		  *
//* 																								  *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program is designed to prompt a user to input values and processes the data.      *
//*   It is then to output an HTML file that has a header, horizontal line spanning the entire web    *
//*   page, and a title of "Standard Deviation Tutorial" in the HTML body. After the title is shown   *
//*   the output file is to show the table that displays index, value, square of the value, sum of	  *
//*   values, sum of square of values, lowest value and highest value of the inputs.			      *
//*   Then, that output html file is to show the sample size, sample mean, sample variance and sample *
//*	  standard deviation of the values that the user entered on four separate lines after the table.  *
//*   Then, that output file is to have a horizontal line spanning the entire web page and have a 	  *
//*   footer. "END OF PROGRAM OUTPUT" must appear after all information has been printed.    		  *                                                                 *
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
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>
using namespace std; 

// Function prototypes
void generateFirstRow();
void generateRow(int count, double value, double square, double sum, double sumSquare, double min, double max);
void openDocument();
void Header();
void outputHeader();
void outputCloseTable();
void Footer();
void closeDocument();
void generateSummary(int count, double mean, double variance, double std);

//*************************************  FUNCTION MAIN  **********************************************
int main(){
// Receives – Nothing
// Task – Creates a html document based on the user's input
// Returns – Integer 0
   string str;
   double value;
   double sum =0; //sum of user's input. For now it's zero.
   double sumSquare = 0; //sum of the square of user's input. For now, its zero.
   int count = 0; //count how many times the user enters numbers
   double mean, variance, std, max, min; //mean, variance, standard deviation, max, min of of user's input
   openDocument(); //open document
   Header(); //create the header
   outputHeader(); //create Standard Deviation Tutorial, surrounded by h1 tag
   generateFirstRow(); //create the first two rows of the table
   cerr<<"Enter a value ";//prompt the user to enter a value
   cin>>str; //store the value into str
   stringstream ss(str);
   ss>>value; //change it into a integer  and store the integer into value
   min=value; //assign that value to min for now
   max=value; //assign that value to max for now
   while(str!="done"){ //the loop doesnt stop as long as the input isnt "done"
	   if(min>value) //if the input is blow the current min set the input as min
	   	   min=value;
	   if(max<value) //if the input is above the current max set the input as min
		   max=value;
	   double square = value * value; //define square as value times value
	   sum +=value; //sum is the sum of the value
	   count++; //count goes by +1
	   sumSquare += square; //sumSquare is the sum of square
	   generateRow(count, value, square, sum, sumSquare, min, max);
	   //generate a new row on the table based on the information of the arguments
	   cerr<<"Enter a value"; //prompt user to enter a value
	   cin>>str; //store the value into str
	   stringstream ss(str);
	   ss>>value; //change it into a integer and store the integer into value.
   }

   outputCloseTable();//close table
   mean = sum/count; //the mean is sum of the values that the user inputs divided by the number of values
   variance = (sumSquare-((sum*sum)/count))/(count-1);//the variance of the numbers that user entered is calculated
   std = pow(variance, 0.5);//the standard deviation of the numbers that user entered is calculated
   generateSummary(count, mean, variance, std);
   //prints out sample size, sample mean, sample variance, and ample standard deviation
   Footer();//create a footer
   closeDocument();//close the document
   return 0;
}
//*************************************END OF FUNCTION MAIN*****************************************

//*************************************  FUNCTION GENERATEFIRSTROW  ********************************
void generateFirstRow(){
// Receives – nothing
// Task – generates the first two rows
// Returns – nothing
	cout << "<table border=" << '"' << 1 << '"' << ">" << endl;
	cout << "<tr><td>i</td> <td>x<sub>i</sub></td><td>x<sub>i</sub><sup>2</sup></td> <td>SUM(x<sub>i</sub>)</td><td>SUM(x<sub>i</sub><sup>2</sup>)</td><td>MIN(x<sub>i</sub>)</td> <td>MAX(x<sub>i</sub>)</td></tr>" << endl;
	cout << "<tr><td>---</td> <td>---</td> <td>---</td><td>0.0<td>0.0</td> <td>none</td><td>none</td></tr>" << endl;
}
//*************************************END OF FUNCTION GENERATEFIRSTROW  *****************************************

//*************************************  FUNCTION GENERATEROW  **********************************************
void generateRow(int count, double value, double square, double sum, double sumSquare, double min, double max) {
// Receives – int count holds sample size, double value holds the value the user enters, double
// square holds the square of the value the user enters, double sum holds the sum of the value the user enters,
// double sumSquare holds the sum of square of the value the user enters, double min holds the smallest value that user enters, double max holds the smallest value that user enters
// Task – generates a row to make the table based on the information of receives
// Returns – nothing
	cout << "<tr><td>" << count << "</td> <td>" << value << "</td> <td>" << square << "</td><td>" << sum << "</td><td>" << sumSquare << "</td><td>"<< min << "</td><td>" << max << "</td></tr>"<< endl;
}
//*************************************END OF FUNCTION GENERATEROW  *****************************************

//*************************************  FUNCTION GENERATESUMMARY  **********************************************
void generateSummary(int count, double mean, double variance, double std) {
// Receives – int count holds sample size, double mean holds sample mean, double variance holds sample variance,
// double std holds sample standard deviation
// Task – prints out sample size, sample mean, sample variance, and sample standard deviation
// Returns – nothing
	cout<<"<br>" << endl;
	cout<<"Sample size is: " << fixed << setprecision(3) << count << "<br>" <<endl;
	cout<<"Sample mean is: " << mean << "<br>" <<endl;
	cout<<"Sample variance is: " << variance << "<br>" <<endl;
	cout<<"Sample standard deviation is: " << std << "<br>" <<endl;
}
//*************************************END OF FUNCTION GENERATESUMMARY  *****************************************

//*************************************  FUNCTION OPENDOCUMENT  **********************************************
void openDocument() {
// Receives – Nothing
// Task – Opens a document whose name is Standard Deviation Tutorial
// Returns – nothing
   cout << "<!DOCTYPE html>" << endl;
   cout << "<head>" << endl;
   cout << "<title> Standard Deviation Tutorial </title>" << endl;
   cout << "</head>" << endl;
   cout << "<body>" << endl;
}
//*************************************END OF FUNCTION OPENDOCUMENT  *****************************************

//*************************************  FUNCTION HEADER  **********************************************
void Header() {
// Receives – Nothing
// Task – Prints the output preamble
// Returns – nothing
   cout << "Takaaki Komatsu <br>" << endl;
   cout << "CSC 24400 <br>" << endl;
   cout << "Section 21<br>" << endl;
   cout << "Spring 2018<br>" << endl;
   cout << "Assignment #1 <br>" << endl;
   cout << "<hr>" << endl;
}
//*************************************END OF FUNCTION HEADER  *****************************************

//*************************************  FUNCTION OUTPUTHEADER  **********************************************
void outputHeader() {
// Receives – Nothing
// Task – prints out Standard Deviation Tutorial, surrounded by h1 tag
// Returns – Nothing
   cout << "<h1>Standard Deviation Tutorial</h1>" << endl;
}
//*************************************END OF FUNCTION OUTPUTHEADER  *****************************************

//*************************************  FUNCTION OUTPUTCLOSETABLE  **********************************************
void outputCloseTable() {
// Receives – Nothing
// Task – closes the table
// Returns – Nothing
   cout << "</table>" << endl;
}
//*************************************END OF FUNCTION OUTPUTCLOSETABLE  *****************************************

//*************************************  FUNCTION FOOTER  **********************************************
void Footer() {
// Receives – Nothing
// Task – prints out END OF PROGRAM OUTPUT, surrounded by horizontal lines
// Returns – Nothing
   cout << "<hr>" << endl;
   cout << "END OF PROGRAM OUTPUT" << endl;
   cout << "<hr>" << endl;
}
//*************************************END OF FUNCTION FOOTER  *****************************************

//*************************************  FUNCTION CLOSEDOCUMENT  **********************************************
void closeDocument() {
// Receives – Nothing
// Task – closes the document, by having </body> and </html>
// Returns – Nothing
   cout << "</body>" << endl;
   cout << "</html>" << endl;
}
//*************************************END OF FUNCTION CLOSEDOCUMENT  *****************************************
