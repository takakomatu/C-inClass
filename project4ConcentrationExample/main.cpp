#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <sys/time.h>
#include "Card.h"
#include "Deck.h"
#include "Board.h"

void PrintUsage() {
   cout << endl;
   cout << "Usage:  P4 [-s <integer>]" << endl;
   cout << endl;
}

int ProcessCommandLine(int argc, char *argv[]) {
   long ttime;
   if ((argc == 2) || (argc > 3)) {  // 1 ok, 2 not ok, 3 ok, >3 not ok
      PrintUsage();
      return -1;
   }

   // at this point argc is either 1 or 3
   if (argc == 1) {
      timeval T;
      gettimeofday(&T, NULL);
      ttime = T.tv_sec * 1000000 + T.tv_usec;
      ttime = abs( (int) ttime);
   }
   else { // at this point there are three arguments
      string arg1(argv[1]);
      if (arg1 != "-s") {
         PrintUsage();
         return -1;
      } 
      // check to make sure 3rd argument is a number
      string arg2(argv[2]);
      bool flag = !arg2.empty() && (arg2.find_first_not_of("0123456789") == arg2.npos);

      if (!flag) {
         PrintUsage();
         return -1;
      }
      else {
         string answer(argv[2]);
         stringstream ss(answer);
         ss >> ttime;
      }
   }
   return ttime;
}

int main(int argc, char *argv[]) {
   string answer;
   int shoesize;
   int shoestartsize;
   long ttime;
   char ch;

   ttime = ProcessCommandLine(argc, argv);
   if (ttime < 0) { 
      cout << "invalid ttime (" << ttime << ") value for seed" << endl;
      return -1;
   }
   cout << "ttime value is: " << ttime << endl;
   cout << "Seed value is: " << (int)ttime << endl;
   srand((int)ttime);

   cout << "Enter any character to continue: ";
   cin >> ch;
   Board B;
   B.playGame();
}





