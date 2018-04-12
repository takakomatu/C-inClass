#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include "Board.h"
using namespace std;

// -------------------------------------------------------------------
Board::Board() {
   cout << "Board::Board - initializing deck for concentration" << endl;
   D.initConcentration();  // initialize the deck
   cout << "Board::Board - shuffling deck" << endl;
   D.Shuffle();            // shuffle the deck

   cout << "Board::Board - puting cards into slots in c and setting state" << endl;
   // put the cards into their slots in the board
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 13; j++) {
         c[i][j] = D.cptr + (i*13+j);
         state[i][j] = hidden;
         //state[i][j] = visible;
      }
   }
}

// -------------------------------------------------------------------
void Board::Display() {
   cout << endl;
   cout << "     0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12" << endl;
   cout << "  +----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl; 
   for (int i=0; i < 4; i++) {
      cout << i << " |";
      for (int j = 0; j < 13; j++) {
          if (state[i][j] == hidden) {
             cout << " xx";
          }
          else {
             c[i][j]->Display();
          }
          cout << " |"; 
      }
      cout << endl;
      cout << "  +----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl; 
   }

}

// -------------------------------------------------------------------
void Board::DisplayState() {
   cout << endl;
   cout << "     0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12" << endl;
   cout << "  +----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl; 
   for (int i=0; i < 4; i++) {
      cout << i << " |";
      for (int j = 0; j < 13; j++) {
          if (state[i][j] == hidden) {
             cout << " H ";
          }
          else if (state[i][j] == visible) {
             cout << " V ";
          }
          else if (state[i][j] == matched) {
             cout << " M ";
          }
          else {
             cout << " - ";
          }
          cout << " |"; 
      }
      cout << endl;
      cout << "  +----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl; 
   }

}

// -------------------------------------------------------------------
States Board::getState(int row, int col) {
   return state[row][col];
}

// -------------------------------------------------------------------
void Board::makeVisible(int row, int col) {
   state[row][col] = visible;
}

// -------------------------------------------------------------------
void Board::makeHidden(int row, int col) {
   state[row][col] = hidden;
}

// -------------------------------------------------------------------
void Board::makeMatched(int row, int col) {
   state[row][col] = matched;
}

// -------------------------------------------------------------------
void Board::clearScreen() {
   system("clear");
}

// -------------------------------------------------------------------
bool Board::checkFinished() {
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 13; j++)
         if (state[i][j] != matched)
            return false;
   return true;
}
   
// -------------------------------------------------------------------
bool Board::checkMatched(int x1, int y1, int x2, int y2) {
   string f1, f2;
   string s1, s2;

   if ((state[x1][y1] == matched) || (state[x2][y2] == matched)) {
      return false;
   }

   f1 = c[x1][y1]->getFace();
   s1 = c[x1][y1]->getSuit();
   f2 = c[x2][y2]->getFace();
   s2 = c[x2][y2]->getSuit();
   if (f1 == f2) {
      if ((s1 == "S")&&(s2=="C"))
         return true;
      else if ((s1 == "H")&&(s2 == "D"))
         return true;
      else if ((s1 == "D")&&(s2 == "H"))
         return true;
      else if ((s1 == "C")&&(s2 == "S"))
         return true;
   }
   return false;
}
   
// -------------------------------------------------------------------
void Board::playGame() {
   bool finished;
   finished = checkFinished();
   while(!finished) {
      playTurn();
      finished = checkFinished();
   }
   cout << endl << "************ You finished the game!! ************" << endl;
}

// -------------------------------------------------------------------
void Board::playTurn() { 
   char ch;
   bool match;
   int x1, y1, x2, y2;

   clearScreen();
   round1(x1, y1);
   round2(x2, y2);
   match = checkMatched(x1, y1, x2, y2);
   if (match) {
      makeMatched(x1, y1);
      makeMatched(x2, y2);
      cout << "You found a matching pair!" << endl;
   } 
   else {
      clearRound();
      cout << "Sorry, the cards don't match" << endl;
   }
   cout << "Enter any character to continue: ";
   cin >> ch;
}

// -------------------------------------------------------------------
void Board::round1(int &x, int &y) {
   string str;
   char c;
   
   Display();
   while (true) {
      cout << "Please enter the grid coordinate for your first card: ";
      cin.clear();
      cin >> str;
      cout << endl;

      stringstream ss(str);
      ss >> x;
      ss >> ws;
      ss >> c;
      ss >> y;
      if (!((x < 0) || (x > 3) || (y < 0) || (y > 12))) {
         if (getState(x, y) != matched) 
            break;
      }
      cout << "That was an invalid card!! Please try again!" << endl;
   }
   if (getState(x, y) != matched) {
      makeVisible(x, y);
   }
   Display();
}

// -------------------------------------------------------------------
void Board::round2(int &x, int &y) {
   string str;
   char c;

   while (true) {
      cout << "Please enter the grid coordinate for your second card: ";
      cin.clear();
      cin >> str;
      cout << endl;

      stringstream ss(str);
      ss >> x;
      ss >> ws;
      ss >> c;
      ss >> y;
      if (!((x < 0) || (x > 3) || (y < 0) || (y > 12))) {
         if (getState(x, y) != matched) 
            break;
      }
      cout << "That was an invalid card!! Please try again!" << endl;
   }
   if (getState(x, y) != matched) {
      makeVisible(x, y);
   }
   Display();

}

// -------------------------------------------------------------------
void Board::clearRound() {
   // reset any unmatched cards to be hidden
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 13; j++)
         if (state[i][j] == visible)
            state[i][j] = hidden;
}
