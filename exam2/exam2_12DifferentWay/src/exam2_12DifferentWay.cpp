#include <iostream>
using namespace std;

int* foo(int* X, int size) {
for (int k = 0; k < size; k++) {
if (k == 0){
X[k] = 0;
}else{
X[k] = k + X[k-1];
}
}

return X;
}

int main ( void ) {
int bar[10];
foo(bar, 10);

for (int n = 0; n < 10; n++) {
cout << bar[n] << " ";
}
cout << endl;

return 0;
}
