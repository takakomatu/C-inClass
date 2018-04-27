//============================================================================
// Name        : exam2_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int *a = new int[10];
	cout << a << endl;
	int *b = new int[10];
	a = b;
	cout << a << b;
}
