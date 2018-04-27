//============================================================================
// Name        : exam2_11.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int *this_ptr, *that_ptr, *other_ptr, *temp_ptr, p_value, q_value, r_value;
	this_ptr = &p_value;
	that_ptr = &q_value;
	other_ptr = &r_value;
	p_value = 1;
	q_value = 2;
	r_value = 3;
	cout << p_value << q_value << r_value;
	cout << *this_ptr << *that_ptr << *other_ptr;
	p_value=(*that_ptr - 9 + r_value - *other_ptr) * 2;
	temp_ptr = that_ptr;
	that_ptr = this_ptr;
	this_ptr = other_ptr;
	other_ptr = temp_ptr;
	r_value=(*that_ptr + 12 - q_value - *other_ptr) * 3;
	cout << " " << *this_ptr << " "<< *that_ptr << " " << *other_ptr;
	*this_ptr = *that_ptr;
	*that_ptr = *other_ptr;
	cout << " " << *this_ptr << " " << *that_ptr << " " << *other_ptr;
	return 0;
}
