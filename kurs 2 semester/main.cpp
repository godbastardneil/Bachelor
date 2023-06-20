#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

#include "print.h"
#include "struct.h"
#include "theory.h"
#include "stat.h"
#include "test.h"
#include "list.h"
#include "admin.h"

using namespace std;

const string adminlog = "adminlog";

void init (string &nickname)
{
    gotoXY(0, 21);
    cout << " Введите имя проверяемого (Не более двадцати символов): ";
    int i = 0;
    char c;
    while (((c = getch()) != 13) || (nickname.size() == 0)) {
		if ((nickname.size() != 20) && (c !=8) && (c !=13)) {
            nickname.insert(nickname.begin()+i, c);
            cout << nickname[i];
            i++;
        } else if ((c == 8) && (i != 0)) {
            i--;
            nickname.erase(nickname.begin()+i, nickname.end());
            cout << "\b \b";
        }
	}
}
void title (const int &con)
{
    vector<string> t = { "Астраханский государственный технический университет",
                        "Институт Информационных технологий и коммуникаций",
                        "Кафедра",
                        "Автоматизированные системы",
                        "обработки информации и управления",
                        "Курсовой проект по дисциплине",
                        "\"Программирование и информатике\"",
                        "Учебно-демонстрационная программа \"Двусвязный список\"",
                        "Выполнил: Студент группы ДИПРБ-11",
                        "Измайлов Н.Н.",
                        "АСТРАХАНЬ 2019" };
    int i = 0;
    int n = t[i].size();
    gotoXY((con - n)/2, 0);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n)/2, 1);
    cout << t[i];
    i++;
    n = t[4].size();
    gotoXY((con - n), 5);
    cout << t[i];
    i++;
    n = t[4].size();
    gotoXY((con - n), 6);
    cout << t[i];
    i++;
    n = t[4].size();
    gotoXY((con - n), 7);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n)/2, 10);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n)/2, 11);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n)/2, 12);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n), 15);
    cout << t[i];
    i++;
    n = t[i-1].size();
    gotoXY((con - n), 16);
    cout << t[i];
    i++;
    n = t[i].size();
    gotoXY((con - n)/2, 20);
    cout << t[i] << endl;
    system("pause");
}

int main()
{
    int con = 100;
    system ("mode con cols=100 lines=30");
    system("chcp 1251 > nul");
    ShowConsoleCursor(false);
    set_col(White, Black);
    title(con);
    short int m_main;
    short int m_cont;
    vector<string> ContMenu = { "Войти под другим пользователем" ,"Выйти" };
    do {
        string nickname;
        init(nickname);
        if (!checkadmin(nickname, adminlog)) {
            system("cls");
            vector<string> MainMenu = { "Посмотреть теорию", "Пройти тестирование", "Посмотреть статистику", "Работа со списком" ,"Выйти" };
            Menu(m_main, MainMenu, con);
            while (m_main != 5)
            {
                switch (m_main)
                {
                case 1: {
                        take_theory(con);
                    break; }
                case 2: {
                        testing(nickname);
                    break; }
                case 3: {
                        init_stat(nickname, 0, con);
                    break; }
                case 4: { work_with_list(con); }
                }
                cout << endl;
                system("pause");
                system("cls");
                Menu(m_main, MainMenu, con);
            }
        } else { admin_work(con); }
        system("pause");
        system("cls");
        Menu(m_cont, ContMenu, con);
    } while (m_cont!=2);
    cout << " До свидания! " << endl;
    return 0;
}
