#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int SIZE = 5;
const int MINES = 5;

vector<vector<char>> board(SIZE, vector<char>(SIZE, '.'));
vector<vector<bool>> revealed(SIZE, vector<bool>(SIZE, false));
vector<vector<bool>> flagged(SIZE, vector<bool>(SIZE, false));

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void initBoard()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            board[i][j] = '.';
        }
    }

    int minesPlaced = 0;
    while (minesPlaced < MINES)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != '*')
        {
            board[x][y] = '*';
            minesPlaced++;
        }
    }
}

int countMinesAround(int x, int y)
{
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == '*')
            {
                count++;
            }
        }
    }
    return count;
}

void displayBoard()
{
    clearScreen();
    cout << "   ";
    for (int i = 0; i < SIZE; ++i)
    {
        cout << setw(2) << i;
    }
    cout << endl;

    for (int i = 0; i < SIZE; ++i)
    {
        cout << setw(2) << i << " ";
        for (int j = 0; j < SIZE; ++j)
        {
            if (revealed[i][j])
            {
                if (board[i][j] == '*')
                {
                    cout << "* ";
                }
                else
                {
                    int minesAround = countMinesAround(i, j);
                    cout << (minesAround > 0 ? to_string(minesAround) : " ") << " ";
                }
            }
            else if (flagged[i][j])
            {
                cout << "F ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

bool checkWin()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] != '*' && !revealed[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void revealEmptyCells(int x, int y)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || revealed[x][y])
    {
        return;
    }

    revealed[x][y] = true;

    if (countMinesAround(x, y) == 0)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                revealEmptyCells(x + dx, y + dy);
            }
        }
    }
}

int main()
{
    srand(time(0));
    initBoard();

    int x, y;
    char action;
    bool gameOver = false;

    while (!gameOver)
    {
        displayBoard();
        cout << "Введите действие (r - открыть, f - флаг): ";
        cin >> action;
        cout << "Введите координаты (x y): ";
        cin >> x >> y;

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        {
            cout << "Некорректные координаты! Попробуйте снова." << endl;
            continue;
        }

        if (action == 'r')
        {
            if (flagged[x][y])
            {
                cout << "Эта клетка помечена флагом! Сначала уберите флаг." << endl;
                continue;
            }

            if (board[x][y] == '*')
            {
                cout << "Вы наступили на мину! Игра окончена." << endl;
                revealed[x][y] = true;
                displayBoard();
                gameOver = true;
            }
            else
            {
                revealEmptyCells(x, y);
                if (checkWin())
                {
                    cout << "Поздравляем! Вы выиграли!" << endl;
                    displayBoard();
                    gameOver = true;
                }
            }
        }
        else if (action == 'f')
        {
            flagged[x][y] = !flagged[x][y];
        }
        else
        {
            cout << "Некорректное действие! Используйте 'r' для открытия или 'f' для установки флага." << endl;
        }
    }

    return 0;
}
