#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>          // File handling
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iomanip>          // Output manipulation, used for the horizontal table
#include <sstream>          // Used to combine numbers with text in a string
#include "termcolor.hpp"    // Assign color to individual strings/lines


struct player {
    int capital = 100;
    int bet{};
    std::vector <int> cards{};
    int sum() {
        int temp{};
        for (int i{}; i < cards.size(); i++) {
            temp += cards[i];
        }
        return temp;
    }
    std::string sumX() {
        std::stringstream temp{};
        temp << cards[0] << " + X";
        return temp.str();
    }
    std::string printCards() {
        std::stringstream temp{};
        for (int k{}; k < cards.size(); k++)
        {
            temp << cards[k] << " ";
        }
        return temp.str();
    }
    std::string printCardsX() { // Hides the last card
        std::stringstream temp{};
        for (int j{}; j < cards.size(); j++)
        {
            if (j == cards.size() - 1) {
                temp << "X ";
            }
            else {
                temp << cards[j] << " ";
            }
        }
        return temp.str();
    }
} player, dealer;


void login();
void badBoop();                                     // Sound
void goodBoop();                                    // Sound
void mainMenu();
void shuffleDeck(std::vector <int>*);               // Creates the deck of cards and assigns the player and dealer with the two starting cards
void blackjack();                                   // The main game function
void printMenu(int, bool, std::string, bool);       // Prints out the horizontal table and in-game menu
void checkInput(int*, std::vector <int>*, bool*);   // Decides where the cursor should be in the in-game menu, runs the enter() function when user presses enter
void enter(int*, std::vector <int>*, bool*);        // Decides which function to run based on user input while in-game
void drawCard(std::vector <int>*, int);             // Gives a random card to the player or dealer and then erases the card from the deck
void chooseAces();                                  // Lets the places decide, whenever they want, if they have ace(s), if the ace(s) should be 1 or 11
void roundEnding(std::vector <int>*, bool*);        // Function the decides what the dealer should do based on his and the players cards, and determines who wins
bool checkForBust(int i);                           // Checks if the player or dealer has a bust, with consideration towards the fact that aces can count as 1 or 11
bool checkForBlackjack();                           // Checks if the player or dealer has a blackjack at the start of the game
void aiSelection();                                 // Decides if the dealer should switch their ace from 1 to 11 or the other way around
void moneyHandler(char);                            // Gives the the person thir own bet back + the bet of the other player, depending on the winner. Returns bets if there is a tie.
void bettingMenu();                                 // Lets the player decide before the game how much they want to bet
bool playAgain();                                   // Asks the player if they want to play another round


time_t currentTime;


// Color defenitions, printRed, printGreen aso.
#define pR termcolor::bright_red
#define pG termcolor::bright_green
#define pB termcolor::bright_cyan
#define pY termcolor::bright_yellow
#define pW termcolor::bright_white
#define reset termcolor::reset

