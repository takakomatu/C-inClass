//============================================================================
// Name        : exam2_10.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int a[10];

	int *b = new int [10];
	const int * x = a;

	x[1] = 7;

	x = b;

	x[2] = 9;

	int * const y = a;

	y[2] = 5;

	y = b;

	y[5] = 99;
	return 0;
}
