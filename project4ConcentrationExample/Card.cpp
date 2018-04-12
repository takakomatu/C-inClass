#include <iostream>
#include <iomanip>
#include <string>
#include "Card.h"
using namespace std;

Card::Card() {
   value = 0;  // invalid value
   face = " ";  // invalid face
   suit = " ";  // invaled suit
}

Card::Card(string f, string s) {
   setCardBlackJack(f, s);
}

void Card::setCardBlackJack(string f, string s) {
   if ((s != "H") && (s != "D") && (s != "C") && (s != "S")) {
      value = 0;  // invalid value
      face = " "; // invalid face
      suit = " "; // invalid suit
      return;
   }

   if (f == "2") {
      value = 2;  
      face = "2";
      suit = s; 
   }
   else if (f == "3") {
      value = 3;  
      face = "3";
      suit = s; 
   }
   else if (f == "4") {
      value = 4;  
      face = "4";
      suit = s; 
   }
   else if (f == "5") {
      value = 5;  
      face = "5";
      suit = s; 
   }
   else if (f == "6") {
      value = 6;  
      face = "6";
      suit = s; 
   }
   else if (f == "7") {
      value = 7;  
      face = "7";
      suit = s; 
   }
   else if (f == "8") {
      value = 8;  
      face = "8";
      suit = s; 
   }
   else if (f == "9") {
      value = 9;  
      face = "9";
      suit = s; 
   }
   else if (f == "10") {
      value = 10;  
      face = "10";
      suit = s; 
   }
   else if (f == "J") {
      value = 10;  
      face = "J";
      suit = s; 
   }
   else if (f == "Q") {
      value = 10;  
      face = "Q";
      suit = s; 
   }
   else if (f == "K") {
      value = 10;  
      face = "K";
      suit = s; 
   }
   else if (f == "A") {
      value = 11;  
      face = "A";
      suit = s; 
   }
   else {
      value = 0;  // invalid value
      face = " "; // invalid face
      suit = " "; // invalid suit
   }
}

void Card::setCardPoker(string f, string s) {
   if ((s != "H") && (s != "D") && (s != "C") && (s != "S")) {
      value = 0;  // invalid value
      face = " "; // invalid face
      suit = " "; // invalid suit
      return;
   }

   if (f == "2") {
      value = 2;  
      face = "2";
      suit = s; 
   }
   else if (f == "3") {
      value = 3;  
      face = "3";
      suit = s; 
   }
   else if (f == "4") {
      value = 4;  
      face = "4";
      suit = s; 
   }
   else if (f == "5") {
      value = 5;  
      face = "5";
      suit = s; 
   }
   else if (f == "6") {
      value = 6;  
      face = "6";
      suit = s; 
   }
   else if (f == "7") {
      value = 7;  
      face = "7";
      suit = s; 
   }
   else if (f == "8") {
      value = 8;  
      face = "8";
      suit = s; 
   }
   else if (f == "9") {
      value = 9;  
      face = "9";
      suit = s; 
   }
   else if (f == "10") {
      value = 10;  
      face = "10";
      suit = s; 
   }
   else if (f == "J") {
      value = 11;  
      face = "J";
      suit = s; 
   }
   else if (f == "Q") {
      value = 12;  
      face = "Q";
      suit = s; 
   }
   else if (f == "K") {
      value = 13;  
      face = "K";
      suit = s; 
   }
   else if (f == "A") {
      value = 14;  
      face = "A";
      suit = s; 
   }
   else {
      value = 0;  // invalid value
      face = " "; // invalid face
      suit = " "; // invalid suit
   }
}

void Card::setCardConcentration(string f, string s) {
   value = 0;
   if ((s != "H") && (s != "D") && (s != "C") && (s != "S")) {
      face = " "; // invalid face
      suit = " "; // invalid suit
      return;
   }

   if (f == "2") {
      value = 0;  
      face = "2";
      suit = s; 
   }
   else if (f == "3") {
      value = 0;  
      face = "3";
      suit = s; 
   }
   else if (f == "4") {
      value = 0;  
      face = "4";
      suit = s; 
   }
   else if (f == "5") {
      value = 0;  
      face = "5";
      suit = s; 
   }
   else if (f == "6") {
      value = 0;  
      face = "6";
      suit = s; 
   }
   else if (f == "7") {
      value = 0;  
      face = "7";
      suit = s; 
   }
   else if (f == "8") {
      value = 0;  
      face = "8";
      suit = s; 
   }
   else if (f == "9") {
      value = 0;  
      face = "9";
      suit = s; 
   }
   else if (f == "10") {
      value = 0;  
      face = "10";
      suit = s; 
   }
   else if (f == "J") {
      value = 0;  
      face = "J";
      suit = s; 
   }
   else if (f == "Q") {
      value = 0;  
      face = "Q";
      suit = s; 
   }
   else if (f == "K") {
      value = 0;  
      face = "K";
      suit = s; 
   }
   else if (f == "A") {
      value = 0;  
      face = "A";
      suit = s; 
   }
   else {
      value = 0;  // invalid value
      face = " "; // invalid face
      suit = " "; // invalid suit
   }
}

int Card::getValue() {
   return value;
}

string Card::getFace() {
   return face;
}

string Card::getSuit() {
   return suit;
}

void Card::setFace(string f) {
   string s;
   s = getSuit();
   setCardBlackJack(f, s);
}

void Card::setSuit(string s) {
   string f;
   f = getFace();
   setCardBlackJack(f, s);
}

void Card::Display() {
   cout << right << setw(2) << face << suit;
}
