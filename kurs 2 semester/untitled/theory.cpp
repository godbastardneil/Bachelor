#include <fstream>
#include <iostream>
#include <vector>

#include "print.h"

#include "theory.h"

using namespace std;

void take_theory (const int &con)
{
    ifstream in ("all_text.dat");
    vector <string> T;
    string temp;
    int j = 0;
    T.push_back("");
    string blank ((con-70)/2, ' ');
    if (in) {
        while (getline(in, temp, 'Y'))
        {
            for (char &i: temp) { i ^= 0xAABBC53; }
            T[j] += blank + temp + "\n";
            int n = temp.size()-2;
            if (temp[n] == '@') {
                T[j].erase(T[j].end()-3);
                T.push_back("");
                j++;
            }
        }
        T.erase(T.end());
        print_data(T, con);
    } else { cout << "Файл не найден" << endl; }
    in.close();
}
