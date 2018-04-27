#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
  int size;
  Card *cptr;

  public:
  void initBlackJack();
  void initPoker();

void Shuffle();
void Display();
void Append(Deck & D);
Card DrawCard();
int getSize();
void ResetSize(int newsize);

Deck();
Deck(Deck & D);
Deck & operator=(Deck & D);
~Deck();
};

#endif
