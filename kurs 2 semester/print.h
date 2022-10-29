#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

using namespace std;

enum ConsoleColor
{
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15
};

bool ShowConsoleCursor(bool bShow);
void gotoXY (const int &column, const int &line);
void set_col(ConsoleColor foreground, ConsoleColor background);

void color (const string &T);

int maxw (const vector<string> menu, const int &n);

void printMenu (const vector<string> menu, const int &n, const int &col, int line);
void Menu (short int &m, const vector<string> menu, const int &con);

void print_data (const vector<string> &T, const int &con);

#endif // PRINT_H_INCLUDED
