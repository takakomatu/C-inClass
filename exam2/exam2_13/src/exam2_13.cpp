#include <iostream>
using namespace std;

class X {
public:
   X() {cout << "Hello X" << endl;}
   ~X() {cout << "Goodbye X" << endl;}
   void print(){ cout <<" Inside X"; }
};

class Y : public X {
public:
   void YX() { cout << "Hello Y" << endl; }
   ~Y() {cout << "Goodbye Y" << endl;}
   void print() { cout <<" Inside Y"; }
};
class Z: public Y {
public:
   Z() {cout << "Hello Z"<< endl;}
   ~Z() {cout << "Goodbye Z"<< endl;}
   void print() { cout <<" Inside Z"; }
};

int main(void)
{
  Z z;
  cout << endl << "blank" << endl;
  z.print();
  cout << endl << "blank" << endl;
  z.Y::print();
  cout << endl << "blank" << endl;

  return 0;
}
