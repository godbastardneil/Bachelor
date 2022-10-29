#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <conio.h>

#include "print.h"

using namespace std;

bool ShowConsoleCursor (bool bShow)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hStdOut == INVALID_HANDLE_VALUE)
        return false;
    if(!GetConsoleCursorInfo(hStdOut, &cci))
        return false;
    cci.bVisible = bShow;
    if(!SetConsoleCursorInfo(hStdOut,&cci))
        return false;
    return true;
}
void gotoXY (const int &column, const int &line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
void set_col (ConsoleColor foreground, ConsoleColor background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((short int)background << 4) | (short int)foreground);
}

void color (const string &T)
{
    int n = T.size();
    for (int i=0; i<n; i++) {
        if (T[i] == '[') {
             if (T[i+1] == '[') {
                i+=2;
                set_col(Black, LightGreen);
                while (((T[i] != ']') && (T[i+1] != ']')) || ((T[i] == ']') && (T[i+1] != ']')) || ((T[i] != ']') && (T[i+1] == ']')))
                {
                    cout << T[i];
                    i++;
                }
                i++;
            } else {
                cout << T[i];
            }
        } else if (T[i] == '{') {
            if (T[i+1] == '{') {
                i+=2;
                set_col(Yellow, Black);
                while (((T[i] != '}') && (T[i+1] != '}')) || ((T[i] == '}') && (T[i+1] != '}')) || ((T[i] != '}') && (T[i+1] == '}')))
                {
                    cout << T[i];
                    i++;
                }
                i++;
            } else {
                cout << T[i];
            }
        } else {
            cout << T[i];
        }
        set_col(White, Black);
    }
    set_col(White, Black);
}

int maxw (const vector<string> menu, const int &n)
{
    int maxw = 0;
    for (int i=0; i<n; i++) {
        int size = menu[i].size();
        if (size > maxw) { maxw = size; }
    }
    return maxw;
}

void printMenu (const vector<string> menu, const int &n, const int &max, const int &col, int line)
{
    gotoXY(col, line);
    cout  << "/" << setfill('-') << setw(max-2) << "\\" << endl;
    cout << "\n";
    line++;
    for (int i=0; i<n; i++) {
        gotoXY(col, line);
        int size = menu[i].size();
        cout << "|" << setfill(' ') << setw(size+(max-size-2)/2) << menu[i] << setw((max-size-1)/2) << "|";
        line++;
    }
    gotoXY(col, line);
    cout  << "\\" << setfill('-') << setw(max-2) << "/" << endl;
}
void Menu (short int &m, const vector<string> menu, const int &con)
{
    int comand;
    const int n = menu.size();
    int i = 0;
    int max = maxw(menu, n);
    int line = 16;
    int col = (con-max)/2;
    while(i<n) {
        printMenu(menu, n, max+3, col, 15);
        gotoXY(col, line);
        int k = menu[i].size();
        string punct = "[[" + menu[i] + "]]";
        cout << "|" << setfill(' ') << setw((max-k+3)/2);
        color(punct);
        set_col(Black, LightGreen);
        cout << setw((max-k+2)/2) << "|";
        set_col(White, Black);
        cout << "\b|";
        do {
            comand = _getch();
        } while ((comand != 72) && (comand != 80) && (comand != 13));
        switch (comand)
        {
        case 80 : {
                if (i != n-1) {
                    i++;
                    line++;
                } else {
                    i = 0;
                    line = 16;
                }
            break; }
        case 72 : {
                if (i != 0) {
                    i--;
                    line--;
                } else {
                    i = n-1;
                    line = 16+n-1;
                }
            break; }
        case 13 : {
                m = i+1;
                i = n;
            }
        }
    }
    system("cls");
}

void print_data (const vector<string> &T, const int &con)
{
    int comand;
    int n = T.size();
    int i = 0;
    while(i<n) {
        system("cls");
        gotoXY((con - 4)/2, 0);
        set_col(Black, LightGreen);
        cout << i+1 << "/" << n << endl;
        set_col(White, Black);
        color(T[i]);
        cout << endl << string((con/2) - 34, ' ');
        set_col(Black, LightGreen);
        cout << "<-";
        cout << string(30, ' ') << "Esc";
        cout << string(32, ' ') << "->";
        set_col(White, Black);
        do {
            comand = getch();
        } while ((comand != 27) && (comand != 77) && (comand != 75));
        switch (comand)
        {
        case 27 : {
                i = n;
                return;
            break; }
        case 77 : {
                i++;
            break; }
        case 75 :
            {
                if (i == 0) {
                    i = n;
                    return;
                } else {  i --; }
            break; }
        }
    }
}
