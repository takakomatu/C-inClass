#include "Deck.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void Deck::initPoker() {
   if (size > 0) {
      delete cptr;
   }
   size = 52;
   cptr = new Card[size];

   cptr[0].setCardPoker("2", "C");
   cptr[1].setCardPoker("3", "C");
   cptr[2].setCardPoker("4", "C");
   cptr[3].setCardPoker("5", "C");
   cptr[4].setCardPoker("6", "C");
   cptr[5].setCardPoker("7", "C");
   cptr[6].setCardPoker("8", "C");
   cptr[7].setCardPoker("9", "C");
   cptr[8].setCardPoker("10", "C");
   cptr[9].setCardPoker("J", "C");
   cptr[10].setCardPoker("Q", "C");
   cptr[11].setCardPoker("K", "C");
   cptr[12].setCardPoker("A", "C");

   cptr[13].setCardPoker("2", "D");
   cptr[14].setCardPoker("3", "D");
   cptr[15].setCardPoker("4", "D");
   cptr[16].setCardPoker("5", "D");
   cptr[17].setCardPoker("6", "D");
   cptr[18].setCardPoker("7", "D");
   cptr[19].setCardPoker("8", "D");
   cptr[20].setCardPoker("9", "D");
   cptr[21].setCardPoker("10", "D");
   cptr[22].setCardPoker("J", "D");
   cptr[23].setCardPoker("Q", "D");
   cptr[24].setCardPoker("K", "D");
   cptr[25].setCardPoker("A", "D");

   cptr[26].setCardPoker("2", "H");
   cptr[27].setCardPoker("3", "H");
   cptr[28].setCardPoker("4", "H");
   cptr[29].setCardPoker("5", "H");
   cptr[30].setCardPoker("6", "H");
   cptr[31].setCardPoker("7", "H");
   cptr[32].setCardPoker("8", "H");
   cptr[33].setCardPoker("9", "H");
   cptr[34].setCardPoker("10", "H");
   cptr[35].setCardPoker("J", "H");
   cptr[36].setCardPoker("Q", "H");
   cptr[37].setCardPoker("K", "H");
   cptr[38].setCardPoker("A", "H");

   cptr[39].setCardPoker("2", "S");
   cptr[40].setCardPoker("3", "S");
   cptr[41].setCardPoker("4", "S");
   cptr[42].setCardPoker("5", "S");
   cptr[43].setCardPoker("6", "S");
   cptr[44].setCardPoker("7", "S");
   cptr[45].setCardPoker("8", "S");
   cptr[46].setCardPoker("9", "S");
   cptr[47].setCardPoker("10", "S");
   cptr[48].setCardPoker("J", "S");
   cptr[49].setCardPoker("Q", "S");
   cptr[50].setCardPoker("K", "S");
   cptr[51].setCardPoker("A", "S");
}

void Deck::initBlackJack() {
   if (size > 0) {
      delete [] cptr;
   }
   size = 52;
   cptr = new Card[size];

   cptr[0].setCardBlackJack("2", "C");
   cptr[1].setCardBlackJack("3", "C");
   cptr[2].setCardBlackJack("4", "C");
   cptr[3].setCardBlackJack("5", "C");
   cptr[4].setCardBlackJack("6", "C");
   cptr[5].setCardBlackJack("7", "C");
   cptr[6].setCardBlackJack("8", "C");
   cptr[7].setCardBlackJack("9", "C");
   cptr[8].setCardBlackJack("10", "C");
   cptr[9].setCardBlackJack("J", "C");
   cptr[10].setCardBlackJack("Q", "C");
   cptr[11].setCardBlackJack("K", "C");
   cptr[12].setCardBlackJack("A", "C");

   cptr[13].setCardBlackJack("2", "D");
   cptr[14].setCardBlackJack("3", "D");
   cptr[15].setCardBlackJack("4", "D");
   cptr[16].setCardBlackJack("5", "D");
   cptr[17].setCardBlackJack("6", "D");
   cptr[18].setCardBlackJack("7", "D");
   cptr[19].setCardBlackJack("8", "D");
   cptr[20].setCardBlackJack("9", "D");
   cptr[21].setCardBlackJack("10", "D");
   cptr[22].setCardBlackJack("J", "D");
   cptr[23].setCardBlackJack("Q", "D");
   cptr[24].setCardBlackJack("K", "D");
   cptr[25].setCardBlackJack("A", "D");

   cptr[26].setCardBlackJack("2", "H");
   cptr[27].setCardBlackJack("3", "H");
   cptr[28].setCardBlackJack("4", "H");
   cptr[29].setCardBlackJack("5", "H");
   cptr[30].setCardBlackJack("6", "H");
   cptr[31].setCardBlackJack("7", "H");
   cptr[32].setCardBlackJack("8", "H");
   cptr[33].setCardBlackJack("9", "H");
   cptr[34].setCardBlackJack("10", "H");
   cptr[35].setCardBlackJack("J", "H");
   cptr[36].setCardBlackJack("Q", "H");
   cptr[37].setCardBlackJack("K", "H");
   cptr[38].setCardBlackJack("A", "H");

   cptr[39].setCardBlackJack("2", "S");
   cptr[40].setCardBlackJack("3", "S");
   cptr[41].setCardBlackJack("4", "S");
   cptr[42].setCardBlackJack("5", "S");
   cptr[43].setCardBlackJack("6", "S");
   cptr[44].setCardBlackJack("7", "S");
   cptr[45].setCardBlackJack("8", "S");
   cptr[46].setCardBlackJack("9", "S");
   cptr[47].setCardBlackJack("10", "S");
   cptr[48].setCardBlackJack("J", "S");
   cptr[49].setCardBlackJack("Q", "S");
   cptr[50].setCardBlackJack("K", "S");
   cptr[51].setCardBlackJack("A", "S");
}

Deck::Deck() {
   size = 0;
   cptr = NULL;
}

void Deck::Shuffle() {
bool found;
	Card *deckpointer = new Card[size];
	int numbers[size] = {};
	int num;
	// generate random numbers without any duplicates.
	for(int i=0;i<size;i++){
		do{
		    found = false;
			num = rand() % size;
			// check if we have any duplicates
			for(int j=0;j<i;j++){
				if(num == numbers[j]){
					found = true;
					break;
				}
			}
		}while(found);
		// store the random number to the array
		numbers[i] = num;
	}
	for(int i=0;i<size;i++){
		deckpointer[numbers[i]] = cptr[i];
	}
	// release memory for other tasks
	delete[] cptr;
	cptr = deckpointer;
}

void Deck::Append(Deck &D) {
	Card *sptr = new Card[(size+D.size)];
	for(int i=0;i<size;i++){
		sptr[i] = cptr[i];
	}
	for(int i=0;i<D.size;i++){
		sptr[i+size] = D.cptr[i];
	}
	// update the size
    size = size+D.size;
	// release memory for other tasks
    delete [] cptr;
    cptr = sptr;
}

Card Deck::DrawCard() {
	size--;
	return cptr[size];
}

int Deck::getSize() {
   return size;
}

void Deck::Display() {
   int sum=0;
   for (int i = 0; i < size; i++) {
      sum = sum + cptr[i].getValue();
      cout << " ";
   }
   cout << "sum: " << sum << endl;
}

void Deck::ResetSize(int newsize) {
	size = newsize;
}

Deck::Deck(Deck &D) {
   size = 0;
   cptr = NULL;
   *this = D;
}

Deck & Deck::operator=(Deck &D) {
   if (cptr) {
      delete [] cptr;
      size = 0;
      cptr = NULL;
   }

   size = D.size;
   cptr = new Card[size];
   for (int i = 0; i < size; i++)
	cptr[i] = D.cptr[i];

   return *this;
}

Deck::~Deck() {
   if (size > 0) {
      delete [] cptr;
      cptr = NULL;
   }
}
