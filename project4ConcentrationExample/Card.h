#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card {
   int value;
   string face;
   string suit;

public:
   Card();
   Card(string f, string s);
   void setCardPoker(string f, string s);
   void setCardBlackJack(string f, string s);
   void setCardConcentration(string f, string s);
   int getValue();
   string getFace();
   string getSuit();
   void setFace(string f);
   void setSuit(string s);
   void Display();

   friend class Board;
};

#endif
