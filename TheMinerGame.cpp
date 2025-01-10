#include <iostream>
#include <cstdlib>
#include <ctime>

#include <string.h>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

const int SIZE {5};
const int MINES {5};

char board[SIZE][SIZE];
bool revealed[SIZE][SIZE] = {false};

void initBoard() {
    for (int i = 0; i < SIZE; ++i) 
        for (int j = 0; j < SIZE; ++j) 
            board[i][j] = '.';

    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != '*') {
            board[x][y] = '*';
            minesPlaced++;
        }
    }
}

void displayBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (revealed[i][j]) printf("%c ", board[i][j]);
            else printf(". ");
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));
    initBoard();

    int x, y;
    while (true) {
        displayBoard();
        printf("Enter the coordinates (x y): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            puts("Incorrect coordinates! Try again.");
            continue;
        }

        if (board[x][y] == '*') {
            puts("You've stepped on a landmine! The game is over.");
            revealed[x][y] = true;
            displayBoard();
            break;
        }

        revealed[x][y] = true;
        board[x][y] = ' ';

        bool win = true;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] != '*' && !revealed[i][j]) {
                    win = false;
                    break;
                }
            }
            if (!win) break;
        }
        if (win) {puts("Congratulations! You've won!"); displayBoard(); break;}
    }

    return 0;
}