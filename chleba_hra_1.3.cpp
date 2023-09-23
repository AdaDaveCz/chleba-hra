#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // for _getch() on Windows (for Linux, you can use ncurses)

using namespace std;

const int mapWidth = 10;
const int mapHeight = 5;

char gameMap[mapHeight][mapWidth];
int chlebaX, chlebaY;
int moneyX, moneyY;
int score = 0;
int moneyCollected = 0;
int currentLevel = 1;
int moneyNeededForNextLevel = 5;

// Function to generate a random number between min and max
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to initialize the game
void initializeGame() {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            gameMap[y][x] = '.';
        }
    }

    chlebaX = mapWidth / 2;
    chlebaY = mapHeight / 2;

    moneyX = random(0, mapWidth - 1);
    moneyY = random(0, mapHeight - 1);
}

// Function to draw the game
void drawGame() {
    system("cls"); // Clear the screen on Windows (use "clear" for Linux)

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            if (x == chlebaX && y == chlebaY) {
                cout << "C";
            } else if (x == moneyX && y == moneyY) {
                cout << "$";
            } else {
                cout << gameMap[y][x];
            }
        }
        cout << endl;
    }

    cout << "Level: " << currentLevel << endl;
    cout << "Celkove penize: $" << score << endl;
    cout << "Penezenka: $" << moneyCollected << endl;
    cout << "Pouzij 'W', 'S', 'A', 'D' aby jsi hybal s CHLEBEM: ";
}

// Function to handle the buying option
void handleBuyingOption() {
    char choice;

    cout << "Sebral si dost penez, kup si neco!" << endl;
    cout << "Vyber si:" << endl;
    cout << "1. NEFLEXIM merch ($10)" << endl;
    cout << "2. COLA z roku 1990 ($5)" << endl;
    cout << "3. Ulozit penize" << endl;
    cout << "4. LAMBORGHINI HURACAN ($50)" << endl;

    cout << "Vyber si moznost (1/2/3/4): ";
    cin >> choice;

    switch (choice) {
        case '1':
            if (moneyCollected >= 10) {
                moneyCollected -= 10;
                cout << "Kopil jsi si NEFLEXIM merch!" << endl;
            } else {
                cout << "Nemas dostatek penez na NEFLEXIM merch." << endl;
            }
            break;
        case '2':
            if (moneyCollected >= 5) {
                moneyCollected -= 5;
                cout << "Koupil jsi si COLU z roku 1990!" << endl;
                // Check for the win condition with a 30% chance of winning and 100 money
                if (moneyCollected >= 100 && random(1, 10) == 1) {
                    cout << "Gratulujeme, nepoblil jsi se a dostal si 100$ za reklamu!" << endl;
                }
            } else {
                cout << "Nemas dostatek penez na COLU" << endl;
            }
            break;
        case '3':
            cout << "Setris penize." << endl;
            break;
        default:
            cout << "Nic jsi si nekoupil a setris." << endl;
            break;
        case '4':
            if (moneyCollected >= 50) {
                moneyCollected -= 50;
                cout << "Kopil jsi si LAMBO!" << endl;
            } else {
                cout << "Nemas dostatek penez na LAMBO." << endl;
            }
            break;
    }

    cout << "Stiskni cokoliv pro pokracovani ve hre";
    _getch(); // Wait for user input before continuing
}

int main() {
    srand(time(0));

    char input;

    initializeGame();
    drawGame();

    while (true) {
        input = _getch(); // Use _getch() on Windows (for Linux, you can use ncurses)

        int newChlebaX = chlebaX;
        int newChlebaY = chlebaY;

        // Handle player input
        switch (input) {
            case 'W':
            case 'w':
                newChlebaY--;
                break;
            case 'S':
            case 's':
                newChlebaY++;
                break;
            case 'A':
            case 'a':
                newChlebaX--;
                break;
            case 'D':
            case 'd':
                newChlebaX++;
                break;
        }

        // Check if the new position is within bounds
        if (newChlebaX >= 0 && newChlebaX < mapWidth && newChlebaY >= 0 && newChlebaY < mapHeight) {
            chlebaX = newChlebaX;
            chlebaY = newChlebaY;
        }

        // Check for collision between CHLEBA and money
        if (chlebaX == moneyX && chlebaY == moneyY) {
            score++;
            moneyCollected++;
            moneyX = random(0, mapWidth - 1);
            moneyY = random(0, mapHeight - 1);

            // Check if the player collected enough money for the next level
            if (moneyCollected >= moneyNeededForNextLevel) {
                currentLevel++;
                moneyNeededForNextLevel += 5; // Increase the money needed for the next level
                cout << "Gratulujeme, postoupil jsi na dalsi level!" << endl;
                _getch(); // Wait for user input before continuing to the next level
            }

            // Check if the player collected enough money to trigger the buying option
            if (moneyCollected >= 5) {
                handleBuyingOption();
            }
        }

        drawGame();
    }

    return 0;
}
