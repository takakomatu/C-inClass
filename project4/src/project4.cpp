//************************************  PROGRAM IDENTIFICATION  **************************
//*                                                                                      *
//*   PROGRAM FILE NAME:  project4.cpp          ASSIGNMENT #: 4           		         *
//*                                                                                      *
//*   PROGRAM AUTHOR:   Takaaki Komatsu													 *
//*                                                                                      *
//*   COURSE #:  CSC 24400 21								   DUE DATE:  April 19, 2018 *
//* 																					 *
//****************************************************************************************

//***********************************  PROGRAM DESCRIPTION  ******************************
//*                                                                                      *
//*   PROCESS: This program will implement the game of Blackjack.This program, there will*
//*   only be one player (the user), and the dealer (the program). This program should   *
//*   allow game play with anywhere from 1 deck up to 20 decks.                          *
//*																					     *
//*   USER DEFINED                                                                       *
//*   MODULES     :  Header – makes a header 								   			 *
//*                  PrintUsage – print the usage message    			                 *
//*        			 ProcessCommandLine – process the command line arguments             *
//*          		 Footer – makes a footer 									     	 *
//*																						 *
//****************************************************************************************

#include "Deck.h"
#include "Hand.h"
#include <string>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

Deck shoe;
Hand DealerHand;
Hand PlayerHand;
Hand H;
Deck D;
int intDecks;
int wins, loses, ties = 0;

void Header() {
// Receives – Nothing
// Task – Prints the header
// Returns – nothing

	// print a header
	cout << "Takaaki Komatsu CSC 24400 Section 21" << endl;
	cout << "Spring 2018 Assignment #4 " << endl;
	cout << "----------------------------------------------------------------------\n" << endl;
}

void PrintUsage(){
	// Receives - nothing
	// Task - prints the usage
	// Returns - nothing
	cout << "Usage: project4[-s<number>]\n";
}

void Footer() {
// Receives – Nothing
// Task – prints out END OF PROGRAM OUTPUT
// Returns – Nothing

	// these are for printing out footer.
	cout << " -----------------------------\n";
	cout << "|   END OF PROGRAM OUTPUT    |\n";
	cout << " -----------------------------";
}

int ProcessCommandLine(int argc, char * argv[]){
	// Receives - int argc holds the argment c and char * argv[] holds the argment v
	// Task - process the command line
	// Returns - int
  struct timeval t;
  long ttime;
  int time;

  if (argc == 1) {
    gettimeofday(&t, NULL);
    ttime = t.tv_sec * 1000000 + t.tv_usec;
    time = abs((int) ttime);
    return time;
  }

  else if (argc == 3) {
    string arg1(argv[1]);

    // display a usage message and the program terminates
    if (arg1 != "-s") {
      PrintUsage();
      return -1;
    }

    string arg2(argv[2]);

    if (!arg2.empty() && (arg2.find_first_not_of("0123456789") != arg2.npos)) {
      PrintUsage();
      return -1;
    }

    stringstream ss(arg2);
    ss >> time;
    return time;
  }

  // if the argument isn't a legal long number, display a usage message and terminate
  else {
    PrintUsage();
    return -1;
  }
}

int main (int argc, char * argv[]) {

	// create header
	Header();

	int seed;
	seed = ProcessCommandLine(argc, argv);
	if (seed < 0)
		return 1;

	// print the seed value
	srand(seed);
	cout << "The Seed Value is: " << seed << endl;

	// keeps prompting the user for how many decks he wants to use until he inputs the number from 1 to 20
	string numDecks;
	bool check1to20;
	while(true){
		cout << "How many decks do you wish to play with (max 20)?";
		cin >> numDecks; // store the input into str
		stringstream ss(numDecks);
		ss >> intDecks;
		check1to20 = false; // store the input as int
		for(int i=1;i<=20;i++){
			if(intDecks == i){
				check1to20 = true;
				break;
			}
		}

		// if the input is an integer from 1 to 20, break out of the loop
		if(check1to20){
			break;
		}
	}

	// print the number of decks used in this program
	cout << "The number of decks used: " << intDecks << endl;

	// create a deck of cards, and then append that deck to the shoe the number of times specified.
	D.initBlackJack();
	for(int i=1;i<=intDecks;i++){
		shoe.Append(D);
	}
	int originalShoeSize = shoe.getSize();
	shoe.Shuffle();

	// keep asking if a user wants to play blackjack until the user input y, yes, n, or no.
	string yesNo;
	while(true){
		cout << "Do you wish to play blackJack?";
		cin >> yesNo; //store the input into str
		cout << yesNo << endl;

		// convert the input to uppercase letters
		int length = yesNo.length();
		for(int j=0;j<length;j++){
			yesNo[j] = toupper(yesNo[j]);
		}

		// if the input is N or NO, print summary statistics and terminate
		if(yesNo == "NO" || yesNo == "N"){
			cout << "********************************************************\n";
			cout << "********************************************************\n";
			cout << "A total of " << (wins+loses+ties) << " hands were played\n";
			cout << "Dealer won " << loses << " hands\n";
			cout << "Player won " << wins << " hands\n";
			cout << "The number of ties " << ties << " hands\n";
			break;
		}

		// if the input is YES or Y, play Blackjack
		else if(yesNo == "YES" || yesNo == "Y"){
			// check if the deck is to be re-shuffled or no. If so re-shuffle.
			if((shoe.getSize()<52)||(shoe.getSize()<.3*originalShoeSize)){
				shoe.ResetSize(originalShoeSize);
				shoe.Shuffle();
			}

			// reset PlayerHand DealerHand and set BJsum = 0
			PlayerHand = H;
			DealerHand = H;

			// Deal the first card to player deal the second card to the dealer
			Card card;
			card = shoe.DrawCard();
			DealerHand.Append(card);
			card = shoe.DrawCard();
			PlayerHand.Append(card);

			// display the hands of dealer and player
			cout << "=================================================================\n";
			cout << "=================================================================\n";
			cout << "Dealer Hand:     ";
			DealerHand.Display();
			cout << "Player Hand:     ";
			PlayerHand.Display();

			// deal the 3rd card to player, 4th to dealer
			card = shoe.DrawCard();
			DealerHand.Append(card);
			card = shoe.DrawCard();
			PlayerHand.Append(card);

			cout << "=================================================================\n";
			// display the hands of dealer with hole cards
			cout << "Dealer Hand:     ";
			DealerHand.DisplayNoHole();

			// display the hands of player
			cout << "Player Hand:     ";
			PlayerHand.Display();

			// check if both have blackjack. If so, display the final hands and increment ties by 1.
			if(DealerHand.calcSum()==21 && PlayerHand.calcSum()==21){
				cout << "=================================================================\n";
				cout << "=================================================================\n";
				cout << "Dealer Hand:     ";
				DealerHand.Display();
				cout << "Player Hand:     ";
				PlayerHand.Display();
				cout << "It's a tie!";
				ties++;
			}

			// check if the dealer has blackjack. If so, display the final hands and increment loses by 1.
			else if(DealerHand.calcSum()==21){
				cout << "=================================================================\n";
				cout << "=================================================================\n";
				cout << "Dealer Hand:     ";
				DealerHand.Display();
				cout << "Player Hand:     ";
				PlayerHand.Display();
				cout << "**** Dealer has BlackJack - Dealer Wins ****\n";
				loses++;
			}

			// check if the player has blackjack. If so, display the final hands and increment wins by 1.
			else if(PlayerHand.calcSum()==21){
				// display the final hands
				cout << "=================================================================\n";
				cout << "=================================================================\n";
				cout << "Dealer Hand:     ";
				DealerHand.Display();
				cout << "Player Hand:     ";
				PlayerHand.Display();
				cout << "**** Player has BlackJack - Player Wins ****\n";
				wins++;
			}

			// if no one has blackJack
			else{
				string hitStand;
				bool checkHitStand;
				// keeps prompting the user for Hit or stand until his input is valid
				while(true){
					cout << "Hit or stand?";
					cin >> hitStand; //store the value into str
					checkHitStand = false;

					// convert the input to uppercase letters
					int length = hitStand.length();
					for(int j=0;j<length;j++){
						hitStand[j] = toupper(hitStand[j]);
					}

					// if the answer is hit, give an additional card to player and display his hand and dealer's cards except for hole card
					if(hitStand == "HIT" || hitStand == "H"){
						cout << "Player hits\n";
						checkHitStand = true;
						card = shoe.DrawCard();
						PlayerHand.Append(card);
						cout << "=================================================================\n";
						cout << "Dealer Hand:     ";
						DealerHand.DisplayNoHole();
						cout << "Player Hand:     ";
						PlayerHand.Display();

						// check if he busted. If so, display both hands and increment loses by 1 and dont ask hit or stand again
						if(PlayerHand.calcSum()>21){
							cout << "=================================================================\n";
							cout << "Dealer Hand:     ";
							DealerHand.Display();
							cout << "Player Hand:     ";
							PlayerHand.Display();
							cout << "Player busted!\n";
							cout << "Player loses\n";
							loses++;
						}

						// if he didnt bust, ask hit or stand again.
						else{
							checkHitStand = false;
						}
					}

					// if the answer is stand, display both hands, including hole card.
					else if(hitStand == "STAND" || hitStand == "S"){
						cout << "Player stands\n";
						cout << "=================================================================\n";
						cout << "=================================================================\n";
						checkHitStand = true;

						cout << "Dealer Hand:     ";
						DealerHand.Display();
						cout << "Player Hand:     ";
						PlayerHand.Display();

						// now its dealer's turn
						// when dealer needs to hit, keep giving an additional card to dealer and show both all cards
						if(DealerHand.calcSum()<17)
							while(DealerHand.calcSum()<17){
								cout << "Dealer Hits\n";
								cout << "=================================================================\n";
								card = shoe.DrawCard();
								DealerHand.Append(card);
								cout << "Dealer Hand:     ";
								DealerHand.Display();
								cout << "Player Hand:     ";
								PlayerHand.Display();
								// the dealer keeps hitting as long as the sum is less than 17
							}

						// when dealer needs to stand
						else
							cout << "Dealer stands\n";

						cout << "=================================================================\n";
						cout << "=================================================================\n";

						// if dealer busts, display messages and increment wins by 1.
						if(DealerHand.calcSum()>21){
							cout << "Dealer busted!\n";
							cout << "Player Wins\n";
							wins++;
						}

						// if player has winning hand, display messages and increment wins by 1.
						else if(DealerHand.calcSum() < PlayerHand.calcSum()){
							cout << "Player has winning hand!\n";
							cout << "Player wins!\n";
							wins++;
						}

						// if player doesnt have winning hand, display messages and increment loses by 1.
						else if(DealerHand.calcSum() > PlayerHand.calcSum()){
							cout << "Dealer has winning hand!\n";
							cout << "Dealer wins!\n";
							loses++;
						}

						// if both have winning hands, display messages and increment ties by 1.
						else{
							cout << "Both have winning hands!\n";
							cout << "It's  a tie!\n";
							ties++;
						}
					}

					if(checkHitStand){
						break;
					}
				}
			}
		}
	}

	// print the footer
	Footer();

	// end of main
	return 1;
}
