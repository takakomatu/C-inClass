//============================================================================
// Name        : exam2_9a.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int foo( ) {
int *ptr[50];
int j, k, x, result=0;
for (j=0; j<50; j++) {
	x = j / 2;
	ptr[j]= x;
}
for (k=0; k<50; k++)
	result = result + *ptr;
	return result;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
