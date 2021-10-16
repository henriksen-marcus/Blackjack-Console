// Compulsory 2, Marcus Henriksen, Blackjack
// This program simulates a game of blackjack with 2 players, player and dealer. The rules follow the task, meaning it only vaguely follows the official rules.
// The game is centered around multiple menu systems, made for the best possible user experience and ease-of-use, in consideration of new players.
// In addition there are multiple fail-safes in place so that the user cannot make any errors or crash the program by accident or will. 
// The structure of the code is centered around splitting all chunks of code into seperate funtions, for better readibility and understanding.
// In this task I have chosen to use pointers and references to avoid global variables, and as an excersise for myself.
// Function explanations are found in the delarations header file.

#include "declarations.h";


int main()
{
    srand((unsigned)time(&currentTime));
    system("color F");
    login();
    mainMenu();
    blackjack();
    return 0;
}



void login()
{
    int count{};
    std::string username{};
    std::string password{};
    std::fstream file("users.txt");

    struct user
    {
        std::string username;
        std::string password;
    };

    std::vector <std::string> userInfoArr{};
    std::vector <user> users{};

    if (file.is_open() == false)
    {
        file.open("users.txt", std::ios::in);
    }

    std::string line{};
    while (std::getline(file, line))
    {
        userInfoArr.push_back(line);
    }
    file.close();

    for (int i = 0; i < userInfoArr.size(); i += 2)
    {
        user temp;
        temp.username = userInfoArr[i];
        temp.password = userInfoArr[i + 1];
        users.push_back(temp);
    }

    while (count < 3)
    {
        std::cout << "Please log in:" << std::endl << std::endl;
        std::cout << "Username: " << pB;
        std::getline(std::cin, username);
        std::cout << reset << "Password: " << pB;
        std::getline(std::cin, password);
        std::cout << std::endl;

        for (int k{}; k < users.size(); k++)
        {
            if (users[k].username == username && users[k].password == password) {
                std::cout << pW << "Succesfully logged in as " << pB << username << reset << std::endl;
                goodBoop();
                Sleep(600);
                system("cls");
                return;
            }
        }

        std::cout << pR << "Wrong username and/or password." << reset << std::endl << std::endl;
        badBoop();
        count++;
    }

    std::cout << termcolor::on_red << "Too many attemps, closing program." << reset << std::endl;
    exit(0);
}


void badBoop()
{
    Beep(700, 30);
    Sleep(50);
    Beep(400, 150);
}


void goodBoop()
{
    Beep(400, 30);
    Sleep(50);
    Beep(700, 150);
}


void mainMenu()
{
    int pos = 1;
    while (true) {
        system("cls");
        std::cout << "Main Menu" << std::endl << std::endl;
        std::cout << "Select an option:" << reset << std::endl << std::endl;
        if (pos == 1) { std::cout << pB << " > "; }
        std::cout << "Play Blackjack" << reset << std::endl;
        if (pos == 2) { std::cout << pB << " > "; }
        std::cout << "Reset Cash" << reset << std::endl;
        if (pos == 3) { std::cout << pB << " > "; }
        std::cout << "Exit" << reset << std::endl;

        char ch = _getch();
        switch (ch) {
        case 'W':
        case 'w':
            if (pos == 1) {
                pos = 3;
                break;
            }
            pos--;
            break;
        case 'S':
        case 's':
            if (pos == 3) {
                pos = 1;
                break;
            }
            pos++;
            break;
        case 13:
            switch (pos) {
            case 1:
                blackjack();
                break;
            case 2:
                player.capital = 100;
                dealer.capital = 100;
                std::cout << std::endl;
                std::cout << pY << "Cash reset." << reset << std::endl;
                Sleep(800);
                break;
            case 3:
                exit(0);
                break;
            }
        }
    }
}


void shuffleDeck(std::vector <int>* deck)
{
    deck->clear(); // Clear array

    // Face cards: 16  ---> 16 instead of 12, as the four "10" cards have a value of 10, similar to the face cards (kings etc.)
    // Number cards: 4 + 4 + 4 + 4 + 4 + 4 + 4 + 4 = 32 ---> Which is why there is 32 and not 36 on this line
    // Aces: 4
    // Total: 52 cards

    // {number of cards to add (iterations), card value}
    std::vector <std::vector <int>> arr = { {16, 10}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 1} };
    for (int i{}; i < arr.size(); i++) // Create deck
    {
        for (int k{}; k < arr[i][0]; k++)
        {
            deck->push_back(arr[i][1]);
        }
    }

    // Give player and dealer two cards each
    int rnd1 = rand() % (deck->size() - 1);
    player.cards.push_back(deck->at(rnd1));
    deck->erase(deck->begin() + rnd1);

    int rnd2 = rand() % (deck->size() - 1);
    dealer.cards.push_back(deck->at(rnd2));
    deck->erase(deck->begin() + rnd2);

    int rnd3 = rand() % (deck->size() - 1);
    player.cards.push_back(deck->at(rnd3));
    deck->erase(deck->begin() + rnd3);

    int rnd4 = rand() % (deck->size() - 1);
    dealer.cards.push_back(deck->at(rnd4));
    deck->erase(deck->begin() + rnd4);
}


void blackjack() {
    std::vector <int> deck{};
    int pos = 1; 
    int* posPtr = &pos;
    bool gameWon = false;
    bool* gameWonPtr = &gameWon;
    bool hasGameStarted = false;
    
    while (true) {
        if (player.capital == 0) { // Check if either player is no longer able to bet, thus not being able to play
            std::cout << std::endl;
            std::cout << "You have no money left. Dealer won the game." << std::endl;
            system("pause");
            return;
        }
        else if (dealer.capital == 0) {
            std::cout << std::endl;
            std::cout << "Dealer has no money left. You won the game." << std::endl;
            system("pause");
            return;
        }

        if (hasGameStarted && !playAgain()) { // Check if player wants to play another round
            return;
        }

        hasGameStarted = true;
        gameWon = false;
        pos = 1;

        player.cards.clear(); // Clear cards and reset deck for each round
        dealer.cards.clear();
        shuffleDeck(&deck); 
        bettingMenu();

        //Check if player got an instant blackjack
        if (checkForBlackjack() == true) {
            continue;
        }

        while (true) { // Game loop
            if (gameWon) { break; }
            printMenu(pos, false, "", false);
            if (checkForBust(0) == true) {  // Check if player has a bust
                moneyHandler('d'); // Give players bet to the dealer
                break; 
            } 
            checkInput(posPtr, &deck, gameWonPtr);
        }
    }
}


void printMenu(int pos, bool reveal, std::string instaBlackjack, bool blink)
{
    int width = 18;
    // Avoiding int-string conversion issues
    std::stringstream playerCapital{}, dealerCapital{}, playerBet{}, dealerBet{};
    playerCapital << "$ " << player.capital;
    dealerCapital << "$ " << dealer.capital;
    playerBet << "$ " << player.bet;
    dealerBet << "$ " << dealer.bet;

    system("cls");

    // Info about player and dealer
    std::cout << "In-game: Blackjack" << std::endl << std::endl;

    std::cout << std::left << std::setw(width) << "Your cards:";
    std::cout << std::left << std::setw(width * 2) << player.printCards();

    if (reveal == true) {
        if (blink == true) { // Takes the users attention when dealer cards are updated, used in the roundEnding() function
            std::cout << std::left << std::setw(width) << "Dealers cards:";
            std::cout << pB << dealer.printCards() << reset;
        }
        else {
            std::cout << std::left << std::setw(width) << "Dealers cards:";
            std::cout << dealer.printCards();
        }
        std::cout << std::endl;
    }
    else { // Hide last card
        std::cout << std::left << std::setw(width) << "Dealers cards:";
        std::cout << dealer.printCardsX();
        std::cout << std::endl;
    }

    std::cout << std::left << std::setw(width) << "Your sum:";

    if (player.sum() > 21) { // Print player sum in red if it is over 21, golden if it is 21
        std::cout << std::left << std::setw(width * 2) << pR << player.sum() << reset;
    }
    else if (player.sum() == 21) {
        std::cout << std::left << std::setw(width * 2) << pY << player.sum() << reset;
    }
    else {
        std::cout << std::left << std::setw(width * 2) << player.sum();
    }
    
    if (reveal == true) {
        std::cout << std::left << std::setw(width) << "Dealers sum:";
        std::cout << dealer.sum() << std::endl << std::endl;
    }
    else { // Hide sum
        std::cout << std::left << std::setw(width) << "Dealers sum:";
        std::cout << dealer.sumX() << std::endl << std::endl;
    }
    
    std::cout << std::left << std::setw(width) << "Your capital:";
    std::cout << std::left << std::setw(width * 2) << pY << playerCapital.str() << reset;
    std::cout << std::left << std::setw(width) << "Dealers capital:";
    std::cout << pY << dealerCapital.str() << reset << std::endl;

    std::cout << std::left << std::setw(width) << "Your bet:";
    std::cout << std::left << std::setw(width * 2) << pY << playerBet.str() << reset;
    std::cout << std::left << std::setw(width) << "Dealers bet:";
    std::cout << pY << dealerBet.str() << reset << std::endl;

    std::cout << std::endl << std::endl;


    if (reveal == false) {
        // Menu options
        std::cout << "Select an option:" << std::endl << std::endl;
        if (pos == 1) { std::cout << pB << " > "; }
        std::cout << "Hit (draw card)" << reset << std::endl;
        if (pos == 2) { std::cout << pB << " > "; }
        std::cout << "Stay (dealers turn)" << reset << std::endl;
        if (pos == 3) { std::cout << pB << " > "; }
        std::cout << "Switch Aces" << reset << std::endl;
        std::cout << std::endl << std::endl << std::endl;
    }

    if (instaBlackjack != "") { // Print out the message given by the checkForBlackjack function, if there was an instant blackjack
        std::cout << instaBlackjack;
    }
}


void checkInput(int *pos, std::vector <int> *deck, bool *gameWonPtr) 
{
    char ch = _getch();
    switch (ch) {
    case 'W':
    case 'w':
        if (*pos == 1) {
            *pos = 3; 
            break; 
        }
        *pos -= 1;
        break;
    case 'S':
    case 's':
        if (*pos == 3) { 
            *pos = 1; 
            break; 
        }
        *pos += 1;
        break;
    case 13:
        enter(pos, deck, gameWonPtr);
        break;
    }
}


void enter(int *pos, std::vector <int> *deck, bool *gameWonPtr) 
{
    switch (*pos) {
    case 1: // Hit
        drawCard(deck, 0);
        break;
    case 2: // Stay
        roundEnding(deck, gameWonPtr);
        break;
    case 3: // Switch aces
        chooseAces();
        break;
    }
}


void drawCard(std::vector <int> *deck, int i) 
{
    if (i == 0) {
        int rnd = rand() % (deck->size() - 1);
        player.cards.push_back(deck->at(rnd));
        deck->erase(deck->begin() + rnd);
    }
    else {
        int rnd = rand() % (deck->size() - 1);
        dealer.cards.push_back(deck->at(rnd));
        deck->erase(deck->begin() + rnd);
    }
}


void roundEnding(std::vector <int>* deck, bool* gameWonPtr) 
{

    // Check if player has a bust, and is able to change that with their aces
    bool hasAce = false;
    for (int i{}; i < player.cards.size(); i++) {
        if (player.cards[i] == 1 || player.cards[i] == 11) {
            hasAce = true;
        }
    }

    if (checkForBust(0) == false && hasAce == true && player.sum() > 21) {
        std::cout << "You currently have a bust. You need to switch your aces before you can continue." << std::endl << std::endl;
        system("pause");
        return;
    }

    aiSelection();
    printMenu(0, true, "", false);

    // Does the dealer already have a higher sum than the player?
    if (dealer.sum() > player.sum()) {
        std::cout << "Dealer has higher sum than player, dealer wins!" << std::endl;
        moneyHandler('d');
    }
    // Does the dealer have a sum of 16 or lower?
    else if (dealer.sum() < 17) {
        // Draw cards
        while (true) {
            printMenu(0, true, "", false); // Reveal dealer cards
            Sleep(1000);
            drawCard(deck, 1); // Dealer draws 1 card
            printMenu(0, true, "", true); // Reveal new card
            std::cout << "Dealer has drawn a new card!" << std::endl;
            Sleep(800);
            printMenu(0, true, "", false);
            std::cout << "Dealer has drawn a new card!" << std::endl;
            Sleep(1000);
            aiSelection();  // Ace cards are arranged in the optimal order, if the dealer has an ace
            printMenu(0, true, "", false);

            if (checkForBust(1) == true) { // Does the dealer have a bust?
                std::cout << "Dealer bust! Player wins!" << std::endl;
                moneyHandler('p');
                break;
            }
            else if (dealer.sum() > player.sum() && dealer.sum() <= 21) { // Does the dealer have a higher sum than the player?
                printMenu(0, true, "", false);
                std::cout << "Dealer has beaten the player by drawing better cards, dealer wins!" << std::endl;
                moneyHandler('d');
                break;
            }
            else if (dealer.sum() > 16) {
                printMenu(0, true, "", false);
                if (player.sum() == dealer.sum()) {
                    std::cout << "Draw!" << std::endl;
                    moneyHandler('t');
                }
                else {
                    std::cout << "Dealer cannot draw more cards! Player wins!" << std::endl;
                    moneyHandler('p');
                }
                break;
            }
        }
    }
    else if (dealer.sum() == player.sum()) { // Does the player and dealer have equal sums?
        std::cout << "Player and Dealer have equal sums, and dealer can't draw more cards. Draw!" << std::endl;
        moneyHandler('t');
    }
    else { // The dealer cannot draw more cards, and they don't have equals sums. The player has a higher sum, player wins
        std::cout << "Player wins!" << std::endl;
        moneyHandler('p');
    }
    *gameWonPtr = true;
}


void chooseAces() 
{
    std::vector <int> indexes{};
    int arrowPos{};
    int index{};

    // Find at which indexes of the player cards array there is a 1 or 11
    for (int i{}; i < player.cards.size(); i++) {
        if (player.cards[i] == 1 || player.cards[i] == 11) {
            indexes.push_back(i);
        }
    }

    if (indexes.size() == 0) {
        std::cout << pR << "You have no aces." << reset << std::endl;
        system("pause");
        return;
    }

    arrowPos = indexes.front();

    while (true) {
        system("cls");
        std::cout << "Use A and D to navigate, change between 1 and 11 with ENTER." << std::endl;
        std::cout << "Press ESC or BACKSPACE to go back." << std::endl;
        std::cout << std::endl;

        // Print the players cards
        for (int k{}; k < player.cards.size(); k++) {
            if (player.cards[k] < 10) {
                std::cout << player.cards[k] << "  ";
            }
            else {
                std::cout << player.cards[k] << " ";
            }
        }

        std::cout << std::endl;

        // Print the ^ arrow that indicates the position of the cursor
        for (int j{}; j < player.cards.size(); j++) {
            if (j == arrowPos) {
                std::cout << pB << "^" << reset;
                break;
            }
            else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl << std::endl;
        std::cout << "Your sum: " << player.sum() << std::endl;

        char ch = _getch();
        switch (ch) {
        case 'A':
        case 'a':
            if (arrowPos == indexes.front()) {
                arrowPos = indexes.back();
                index = indexes.size() - 1;
                break;
            }
            index--;
            arrowPos = indexes[index];
            
            break;
        case 'D':
        case 'd':
            if (arrowPos == indexes.back()) {
                arrowPos = indexes.front();
                index = 0;
                break;
            }
            index++;
            arrowPos = indexes[index];
            break;
        case 13: //Enter
            if (player.cards.at(arrowPos) == 1) {
                player.cards.at(arrowPos) = 11;
            }
            else {
                player.cards.at(arrowPos) = 1;
            }
            break;
        case 27: // Escape key
        case 8:  // Backspace key
            return;
            break;
        }
    }
}


bool checkForBust(int x) 
{
    if (x == 0) {
        int sum{};
        for (int i{}; i < player.cards.size(); i++) {
            if (player.cards[i] == 11) {
                sum++;
            }
            else {
                sum += player.cards[i];
            }
        }
        if (sum > 21) {
            std::cout << "Player BUST! You got a sum that is higher than 21. Dealer wins!" << std::endl;
            return true;
        }
        else {
            return false;
        }
    }
    else if (x == 1) {
        int sum{};
        for (int k{}; k < dealer.cards.size(); k++) {
            if (dealer.cards[k] == 11) {
                sum++;
            }
            else {
                sum += dealer.cards[k];
            }
        }

        if (sum > 21) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool checkForBlackjack() 
{
    bool pBlackjack = false;
    bool dBlackjack = false;
    // This function only runs at the start of the game to check if the player got an instant blackjack
    if (player.cards[0] == 1 && player.cards[1] + 11 == 21) {
        player.cards[0] = 11;
        pBlackjack = true;
    }
    else if (player.cards[1] == 1 && player.cards[0] + 11 == 21) {
        player.cards[1] = 11;
        pBlackjack = true;
    }

    if (dealer.cards[0] == 1 && dealer.cards[1] + 11 == 21) {
        dealer.cards[0] = 11;
        dBlackjack = true;
    }
    else if (dealer.cards[1] == 1 && dealer.cards[0] + 11 == 21) {
        dealer.cards[1] = 11;
        dBlackjack = true;
    }

    if (pBlackjack && dBlackjack) {
        printMenu(0, true, "Both player and dealer got an instant blackjack.", false);
        std::cout << std::endl;
        moneyHandler('t');
        return true;
    }
    else if (pBlackjack) {
        printMenu(0, true, "Player has got an instant blackjack!", false);
        std::cout << std::endl;
        moneyHandler('p');
        return true;
    }
    else {
        return false;
    }
}


void aiSelection() 
{
    int index{}, sum{};
    bool hasAce = false;

    for (int i{}; i < dealer.cards.size(); i++) {
        if (dealer.cards[i] == 1 || dealer.cards[i] == 11) {
            index = i;
            hasAce = true;
            break; // It is important to remember that 11 + 11 = 22, so there is no use in checking more than 1 ace
        }
    }

    if (hasAce == false) { // The point  of this function is to switch the aces so if there are none, return
        return;
    }

    for (int k{}; k < dealer.cards.size(); k++) {
        sum += dealer.cards[k];
    }

    if (sum > 21) { // If sum is a bust
        dealer.cards[index] = 1;
    }
    else if (sum <= 10) { // If sum is less than or 10
        dealer.cards[index] = 11;
    }
    else if (sum > 10 && sum <= 21) { // If sum is between 11 and 21
        return;
    }
}


void bettingMenu() 
{
    if (player.capital < 10) {
        player.bet = player.capital;
        player.capital = 0;
    }
    else {
        player.capital -= 10;
        player.bet = 10;
    }
    while (true) {
        system("cls");
        std::cout << "Betting Menu" << std::endl << std::endl;
        std::cout << "Use W and S or + and - to increase/decrease your bet." << std::endl;
        std::cout << "Minimum bet is $10." << std::endl << std::endl;
        std::cout << std::left << std::setw(15) << "Your capital:" << pY << "$ " << player.capital << reset << std::endl;
        std::cout << std::left << std::setw(15) << "Your bet:" << pY << "$ " << player.bet << reset << std::endl << std::endl;
        std::cout << pB << "Confirm [ENTER]" << reset << std::endl;
       

        char ch = _getch();
        switch (ch) {
        case 'W':
        case 'w':
        case '+':
            if (player.bet >= 100 || player.capital < 5) {
                break;
            }
            player.capital -= 5;
            player.bet += 5;
            break;
        case 'S':
        case 's':
        case '-':
            if (player.bet <= 10) {
                break;
            }
            player.capital += 5;
            player.bet -= 5;
            break;
        case 13:
            Sleep(100);
            if (dealer.capital < player.bet) {
                dealer.bet = dealer.capital;
                dealer.capital = 0;
            }
            else {
                dealer.capital -= player.bet;
                dealer.bet = player.bet;
            }
            return;
            break;
        }
    }
}


void moneyHandler(char plr) 
{ // money money
    if (plr == 'p') { // Player won (p)
        player.capital += player.bet + dealer.bet;
        std::cout << std::endl;
        std::cout << pG << "You gained $" << dealer.bet << "." << reset << std::endl;
    }
    else if (plr == 'd') { // Dealer won (d)
        dealer.capital += dealer.bet + player.bet;
        std::cout << std::endl;
        std::cout << pR <<"You lost $" << player.bet << "." << reset << std::endl;
    }
    else { // Tie (t)
        player.capital += player.bet;
        dealer.capital += dealer.bet;
        std::cout << std::endl;
        std::cout << pY << "Bets have been returned." << reset << std::endl;
    }
    player.bet = 0;
    dealer.bet = 0;
}


bool playAgain()
{
    while (true) {
        std::cout << std::endl;
        std::cout << "Play another round? " << pB << "(y/n)" << reset << std::endl << std::endl;
        char ch = _getch();
        switch (ch) {
        case 'Y':
        case 'y':
            return true;
            break;
        case 'N':
        case 'n':
            return false;
            break;
        default:
            std::cout << pR << "Please press Y or N." << reset << std::endl;
            break;
        }
    }
}