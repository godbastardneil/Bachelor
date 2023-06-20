#include <iostream>
#include <vector>


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
    cout << " Ââåäèòå èìÿ ïðîâåðÿåìîãî (Íå áîëåå äâàäöàòè ñèìâîëîâ): ";
    int i = 0;
    char c;
    while (((c = getchar()) != 13) || (nickname.size() == 0)) {
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
    vector<string> t = { "Àñòðàõàíñêèé ãîñóäàðñòâåííûé òåõíè÷åñêèé óíèâåðñèòåò",
                        "Èíñòèòóò Èíôîðìàöèîííûõ òåõíîëîãèé è êîììóíèêàöèé",
                        "Êàôåäðà",
                        "Àâòîìàòèçèðîâàííûå ñèñòåìû",
                        "îáðàáîòêè èíôîðìàöèè è óïðàâëåíèÿ",
                        "Êóðñîâîé ïðîåêò ïî äèñöèïëèíå",
                        "\"Ïðîãðàììèðîâàíèå è èíôîðìàòèêå\"",
                        "Ó÷åáíî-äåìîíñòðàöèîííàÿ ïðîãðàììà \"Äâóñâÿçíûé ñïèñîê\"",
                        "Âûïîëíèë: Ñòóäåíò ãðóïïû ÄÈÏÐÁ-11",
                        "Èçìàéëîâ Í.Í.",
                        "ÀÑÒÐÀÕÀÍÜ 2019" };
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
    ShowConsoleCursor(false);
    set_col(White, Black);
    title(con);
    short int m_main;
    short int m_cont;
    vector<string> ContMenu = { "Âîéòè ïîä äðóãèì ïîëüçîâàòåëåì" ,"Âûéòè" };
    do {
        string nickname;
        init(nickname);
        if (!checkadmin(nickname, adminlog)) {
            system("cls");
            vector<string> MainMenu = { "Ïîñìîòðåòü òåîðèþ", "Ïðîéòè òåñòèðîâàíèå", "Ïîñìîòðåòü ñòàòèñòèêó", "Ðàáîòà ñî ñïèñêîì" ,"Âûéòè" };
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
    cout << " Äî ñâèäàíèÿ! " << endl;
    return 0;
}
