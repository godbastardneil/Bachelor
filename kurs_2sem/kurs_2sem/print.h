#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

#include <vector>
#include <string>

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

void color (const std::string &T);

int maxw (const std::vector<std::string> menu, const int &n);

void printMenu (const std::vector<std::string> menu, const int &n, const int &col, int line);
void Menu (short int &m, const std::vector<std::string> menu, const int &con);

void print_data (const std::vector<std::string> &T, const int &con);

#endif // PRINT_H_INCLUDED
