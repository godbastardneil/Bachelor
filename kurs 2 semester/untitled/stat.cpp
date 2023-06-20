#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#include "print.h"

#include "stat.h"

using namespace std;

void input_stat (const int &stud_r_answer_i, const int &r_answer_i, const string &nickname)
{
    time_t t = time(0);
    string ti;
    ti = asctime(localtime(&t));
    ofstream out ("all_stat.dat", ios::binary | ios::app);
    string temp = "[[";
    int n = 21-nickname.size();
    temp += nickname + "]]" + string(n, ' ') + "|{{" + to_string(stud_r_answer_i) + "/" + to_string(r_answer_i) + "}}|" + " Оценка: ";
    if ((double(stud_r_answer_i)/r_answer_i) > 0.50) {
        temp += "Зачет  |";
    } else { temp += "Незачет|"; }
    temp += " " + ti;
    color(temp);
    for (char &i: temp) { i ^= 0xAABBC53; }
    out.write(temp.data(), temp.size());
    out.close();
}
bool checkdata (const string &nickname, const string &temp)
{
    size_t n = nickname.size();
    for (size_t i=0; i<n; i++) {
        if (temp[i+2] != nickname[i]) { return 0; }
    }
    if (temp[n+3] != ']') { return 0; }
    return 1;
}
void init_stat (const string &nickname, const bool &admin, const int &con)
{
    ifstream in ("all_stat.dat", ios::binary);
    int k = 0;
    int n = 0;
    vector <string> S;
    string temp;
    string blank ((con-66)/2, ' ');
    S.push_back("");
    if (in) {
        while (getline(in, temp, 'Y'))
        {
            for (char &i: temp) { i ^= 0xAABBC53; }
            if ((admin) || (checkdata(nickname, temp))) {
                k++;
                if (k<=10) {
                    S[n] += blank + temp + "\n";
                } else if (k>10) {
                    k = 0;
                    n++;
                    S.push_back("");
                    S[n] += blank + temp + "\n";
                }
            }
        }
        print_data(S, con);
    } else { cout << "Файл не найден" << endl; }
    in.close();
}
