#include <iostream>
using namespace std;

void foo(int X[2][5], int rows, int cols) {
	int k;
	int *list = (int *) X;
	for (k = 0; k < (rows*cols); k++) {
		if (k == 0){
			*(list + k) = k;
			cout << *(list + k) << endl;
		}
		else{
			*(list + k) = k + *(list + k-1);
			cout << *(list + k) << endl;
		}
	}
}
int main ( ) {
	int bar[2][5];
	foo(bar, 2, 5);
	for (int n = 0; n < 2; n++) {
		for (int m = 0; m < 5; m++) {
			cout << bar[n][m] << " ";
		}
		cout << endl;
	}
}
