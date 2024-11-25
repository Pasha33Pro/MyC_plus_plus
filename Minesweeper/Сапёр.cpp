#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

const int BOARD_SIZE = 10;

bool gameOver = false;

void diffcult_choose();
void re_play(bool win);

struct Cell
{
    bool isMine;
    bool isRevealed;
    int adjacentMines;
};

vector<vector<Cell>> board(BOARD_SIZE, vector<Cell>(BOARD_SIZE));

void initializeBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j].isMine = false;
            board[i][j].isRevealed = false;
            board[i][j].adjacentMines = 0;
        }
    }
}

void placeMines(int NUM_MINES)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, BOARD_SIZE - 1);

    int count = 0;
    while (count < NUM_MINES)
    {
        int x = dis(gen);
        int y = dis(gen);

        if (!board[x][y].isMine)
        {
            board[x][y].isMine = true;
            ++count;
        }
    }
}

bool isValid(int x, int y)
{
    return x >= 1 && x <= BOARD_SIZE && y >= 1 && y <= BOARD_SIZE;
}

int countAdjacentMines(int x, int y)
{
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (isValid(nx, ny) && board[nx - 1][ny - 1].isMine)
            {
                ++count;
            }
        }
    }
    return count;
}

void revealCell(int x, int y)
{
    if (isValid(x, y) && !board[x - 1][y - 1].isRevealed)
    {
        board[x - 1][y - 1].isRevealed = true;
        if (board[x - 1][y - 1].adjacentMines == 0)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    revealCell(x + dx, y + dy);
                }
            }
        }
    }
}

void calculateAdjacentMines()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (!board[i][j].isMine)
            {
                board[i][j].adjacentMines = countAdjacentMines(i + 1, j + 1);
            }
        }
    }
}

void displayBoard(bool showMines)
{
    cout << endl;
    cout << "      ";
    SetConsoleTextAttribute(hand, 3);

    for (int j = 1; j <= BOARD_SIZE; ++j)
    {
        cout << j << " ";
    }

    SetConsoleTextAttribute(hand, 10);
    cout << endl;
    cout << "    ";

    for (int j = 1; j <= BOARD_SIZE; ++j)
    {
        SetConsoleTextAttribute(hand, 3);
        if (j <= 9)
        {
            cout << "--";
        }

        else
        {
            cout << "----";
        }
        SetConsoleTextAttribute(hand, 7);
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << endl;
        SetConsoleTextAttribute(hand, 3);
        if (i <= 8)
        {
            cout << " " << i + 1 << "  | ";
        }

        else
        {
            cout << " " << i + 1 << " | ";
        }
        SetConsoleTextAttribute(hand, 7);

        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j].isRevealed)
            {
                if (board[i][j].isMine)
                {
                    cout << "* ";
                }

                else
                {
                    int numMines = board[i][j].adjacentMines;
                    if (numMines == 0)
                    {
                        SetConsoleTextAttribute(hand, 8);
                        cout << numMines << " ";
                        SetConsoleTextAttribute(hand, 7);
                    }

                    else if (numMines == 1)
                    {
                        SetConsoleTextAttribute(hand, 1);
                        cout << numMines << " ";
                        SetConsoleTextAttribute(hand, 7);
                    }

                    else if (numMines == 2)
                    {
                        SetConsoleTextAttribute(hand, 6);
                        cout << numMines << " ";
                        SetConsoleTextAttribute(hand, 7);
                    }

                    else if (numMines == 3)
                    {
                        SetConsoleTextAttribute(hand, 4);
                        cout << numMines << " ";
                        SetConsoleTextAttribute(hand, 7);
                    }
                    else
                    {
                        SetConsoleTextAttribute(hand, 12);
                        cout << numMines << " ";
                        SetConsoleTextAttribute(hand, 7);
                    }
                }
            }

            else if (board[i][j].isMine && showMines)
            {
                SetConsoleTextAttribute(hand, 4);
                cout << "* ";
                SetConsoleTextAttribute(hand, 7);
            }

            else
            {
                cout << "* ";
            }
        }

        SetConsoleTextAttribute(hand, 3);
        cout << "|" << endl;
        SetConsoleTextAttribute(hand, 7);
    }

    SetConsoleTextAttribute(hand, 3);
    cout << "    -----------------------" << endl;
    SetConsoleTextAttribute(hand, 7);
    cout << endl;
}

void playGame(int NUM_MINES)
{
    initializeBoard();
    placeMines(NUM_MINES);
    calculateAdjacentMines();

    // ������ ��� ��� ����
    bool firstMove = true;

    while (true)
    {
        displayBoard(false);

        int x, y;
        cout << "������� ���������� (x, y): ";
        cin >> x >> y;
        Sleep(2000);
        system("cls");

        if (!isValid(x, y))
        {
            cout << "�������� ����������! ���������� ������.\n" << endl;
            Sleep(2000);
            system("cls");
            continue;
        }

        if (firstMove)
        {
            if (board[x - 1][y - 1].isMine)
            {
                int newX, newY;
                do 
                {
                    newX = rand() % BOARD_SIZE;
                    newY = rand() % BOARD_SIZE;
                } 
                while (board[newX][newY].isMine);

                board[newX][newY].isMine = true;
                board[x - 1][y - 1].isMine = false;

                calculateAdjacentMines();
            }
            firstMove = false;
        }

        if (board[x - 1][y - 1].isMine)
        {
            gameOver = true;
            bool win = false;
            re_play(win);

        }

        revealCell(x, y);

        bool allCellsRevealed = true;
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (!board[i][j].isRevealed && !board[i][j].isMine)
                {
                    allCellsRevealed = false;
                    break;
                }
            }

            if (!allCellsRevealed)
            {
                break;
            }
        }

        if (allCellsRevealed)
        {
            bool win = true;
            re_play(win);
        }
    }
}


void re_play(bool win)
{
    if (win == true)
    {
        cout << "����������! �� ��������." << endl;
    }

    else
    {
        SetConsoleTextAttribute(hand, 4);
        cout << "���� ��������! ";
        SetConsoleTextAttribute(hand, 12);
        cout << "�� ������ ����." << endl;
        cout << endl;
    }
    Sleep(2500);

    system("cls");

    SetConsoleTextAttribute(hand, 7);
    cout << "������ ������� ��� ���? (";
    SetConsoleTextAttribute(hand, 2);
    cout << "y";
    SetConsoleTextAttribute(hand, 7);
    cout << " / ";
    SetConsoleTextAttribute(hand, 4);
    cout << "n";
    SetConsoleTextAttribute(hand, 7);
    cout << "): ";

    string choice;
    cin >> choice;

    if (choice == "y")
    {
        system("cls");
        cout << "����, ����������!" << endl;
        Sleep(2500);
        diffcult_choose();
    }

    else
    {
        Sleep(2500);
        system("cls");
        SetConsoleTextAttribute(hand, 10);
        cout << "��� ��� ���� ����������� �����:" << endl;

        cout << endl;

        SetConsoleTextAttribute(hand, 4);
        cout << "* ";
        SetConsoleTextAttribute(hand, 7);
        cout << "- �����" << endl;

        SetConsoleTextAttribute(hand, 7);
        cout << "* ";
        cout << "- �����" << endl;

        cout << endl;

        Sleep(3500);
        SetConsoleTextAttribute(hand, 7);
        displayBoard(true);
        exit(0);
    }
}


void diffcult_choose()
{
    system("cls");
    SetConsoleTextAttribute(hand, 7);
    cout << "��������� ������� ";
    SetConsoleTextAttribute(hand, 4);
    cout << "��������� ����!" << endl;
    cout << endl;
    SetConsoleTextAttribute(hand, 7);
    cout << "������ �� ������� 4 ���������, �������� 1." << endl;
    Sleep(2500);
    system("cls");

    cout << "�������� ���������:" << endl;

    SetConsoleTextAttribute(hand, 8);
    cout << "1) ����� (10 ���)" << endl;

    SetConsoleTextAttribute(hand, 6);
    cout << "2) ��������� (35 ���)" << endl;

    SetConsoleTextAttribute(hand, 12);
    cout << "3) ������ (65 ���)" << endl;

    SetConsoleTextAttribute(hand, 5);
    cout << "4) ������������ (99 ���)" << endl;

    SetConsoleTextAttribute(hand, 7);
    int choose;
    cout << ">> ";
    cin >> choose;
    cout << endl;

    cout << "�������! �� ������� �����: ";

    int NUM_MINES = 0;

    switch (choose)
    {
    case 1:
        SetConsoleTextAttribute(hand, 8);
        cout << "1) ����� (10 ���)" << endl;
        NUM_MINES = 10;
        break;

    case 2:
        SetConsoleTextAttribute(hand, 6);
        cout << "2) ��������� (35 ���)" << endl;
        NUM_MINES = 35;
        break;

    case 3:
        SetConsoleTextAttribute(hand, 12);
        cout << "3) ������ (65 ���)" << endl;
        NUM_MINES = 65;
        break;

    case 4:
        SetConsoleTextAttribute(hand, 5);
        cout << "4) ������������ (99 ���)" << endl;
        NUM_MINES = 99;
        break;

    default:
        system("cls");
        Sleep(2500);
        cout << "����..." << endl;
        cout << "������ ������ ���!" << endl;
        cout << endl;
        SetConsoleTextAttribute(hand, 7);
        cout << "������ ";
        Sleep(100);
        cout << "�� ";
        Sleep(125);
        cout << "����� ";
        Sleep(125);
        cout << "����� ";
        Sleep(125);
        cout << "������ 4 ";
        Sleep(100);
        cout << "��� ";
        Sleep(125);
        cout << "������ 1";
        Sleep(250);
        cout << ".";
        Sleep(100);
        cout << ".";
        Sleep(100);
        cout << "." << endl;

        system("cls");

        cout << "���������� �������������: ";

        SetConsoleTextAttribute(hand, 8);
        cout << "1) ����� (10 ���)" << endl;

        NUM_MINES = 10;

        Sleep(5000);
    }

    SetConsoleTextAttribute(hand, 7);
    const int BOARD_SIZE = 10;
    vector<vector<Cell>> board(BOARD_SIZE, vector<Cell>(BOARD_SIZE));

    Sleep(1500);
    system("cls");

    playGame(NUM_MINES);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // start
    SetConsoleTextAttribute(hand, 7);
    cout << "����: '��Ϩ�'" << endl;
    SetConsoleTextAttribute(hand, 12);
    cout << "DEV: ������ �����" << endl;
    Sleep(2500);

    // diffcult_change
    diffcult_choose();

    return 0;
}