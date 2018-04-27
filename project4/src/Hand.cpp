#include "Hand.h"
#include "Deck.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

Hand::Hand() {
   size = 0;
   cptr = NULL;
   BJsum = 0;
}

void Hand::Append(Card &C) {
	Card *sptr = new Card[(size+1)];
	for(int i=0;i<size;i++){
		sptr[i] = cptr[i];
	}
	sptr[size] = C;
	// update the size
	size++;
	// release memory for other tasks
	delete[] cptr;
	cptr = sptr;
}

int Hand::getSize() {
   return size;
}

void Hand::Display() {
	BJsum = 0;
	int numberOfAce = 0;
	// display the hand
	for (int i = 0; i < size; i++) {
	  BJsum = BJsum + cptr[i].getValue();
      cptr[i].Display();
      cout << " ";
      // count the number of aces in a hand
	  if(cptr[i].getFace()=="A"){
		  numberOfAce++;
	  }
	}

	// as long as the sum of a hand is over 21 and number of aces is over of equal to 1, reduce the sum by 10
	while(BJsum>21 && numberOfAce>=1){
		BJsum = BJsum - 10;
		numberOfAce--;
	}

	// display the sum
	cout << endl << "sum: " << BJsum << endl;
}

void Hand::DisplayNoHole() {
	   int sum=0;
	   int numberOfAce = 0;
	   // display the hand
	   for (int i = 0; i < size; i++) {
	      sum = sum + cptr[i].getValue();
	      if(i != (size-1))
	    	  cptr[i].Display();
	      cout << " ";
	      if(i == (size-1)){
	    	  cout << "XX";
	    	  sum = sum - cptr[i].getValue();
	      }
	      // count the number of aces in a hand
		  if(cptr[i].getFace()=="A"){
			  numberOfAce++;
		  }
	   }

	   // as long as the sum of a hand is over 21 and number of aces is over of equal to 1, reduce the sum by 10
	   while(sum >21 && numberOfAce >=1){
		   sum = sum - 10;
		   numberOfAce--;
	   }

	   // display the sum
	   cout << endl << "sum: " << sum << endl;
}

int Hand::calcSum(){
	BJsum = 0;
	int numberOfAce = 0;
	for (int i = 0; i < size; i++) {
		BJsum = BJsum + cptr[i].getValue();
	    // count the number of aces in a hand
		if(cptr[i].getFace()=="A"){
			numberOfAce++;
		}
	}
	// as long as the sum of a hand is over 21 and number of aces is over of equal to 1, reduce the sum by 10
	while(BJsum >21 && numberOfAce >=1){
		BJsum = BJsum - 10;
		numberOfAce--;
	}
	return BJsum;
}

Hand & Hand::operator=(Hand &H) {
   if (cptr) {
      delete [] cptr;
      size = 0;
      cptr = NULL;
   }

   size = H.size;
   cptr = new Card[size];
   for (int i = 0; i < size; i++)
	cptr[i] = H.cptr[i];
   BJsum = H.BJsum;
   return *this;
}

Hand::~Hand() {
   if (size > 0) {
      delete [] cptr;
      cptr = NULL;
   }
}
