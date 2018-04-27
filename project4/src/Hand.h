#ifndef HAND_H
#define HAND_H

#include "Card.h"

class Hand {
   int BJsum;
   int size;
   Card *cptr;

public:
   void DisplayNoHole();
   void Display();
   void Append(Card &C);
   int  ComputeBJsum();
   int  ComputeBJsumNoHole();
   int  getSize();
   int  calcSum();

   Hand();
   Hand(Hand &H);
   Hand & operator=(Hand &H);
   ~Hand();
};

#endif
