#include <iostream>
#include <ctime>
#include <set>
#include <algorithm>


using namespace std;

typedef set<int, less<int> > set_type;
//--------------------------------Задание №1
set_type CWoS (const char &Shop, set_type &ware) // create ware of shop - определение того, что будет в магазине
{
    cout << " Магазин " << Shop << endl;
    cout << " Вводите 0 - если товара нет в магазине" << " \n 1 - если есть" << endl;
    set_type S;
    int k;
    for (set_type::iterator it = ware.begin(); it != ware.end(); it++)
    {
        do {
            cout << "Есть ли в магазине товар " << *it << "? ";
            cin >> k;
        } while ((k < 0) || (k > 1));
        if (k == 1) { S.insert(*it); }
    }
    return S;
}

void SWoS (const set_type &result) // show ware of shop - показ таваров магазина
{
    if (result.size() != 0) {
        set_type::iterator it = result.begin();
        cout << *it;
        it++;
        while(it != result.end())
        {
            cout << ", " << *it;
            it++;
        }
    } else { cout << " Таких товаров нет"; }
    cout << endl;
}

set_type EveryShop (set_type &S1, set_type &S2, set_type &S3)
{
    set_type S12;
    set_type result;
    set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S12, S12.begin()));
    set_intersection(S12.begin(), S12.end(), S3.begin(), S3.end(), inserter(result, result.begin()));
    return result;
}
set_type LeastOne (set_type &S1, set_type &S2, set_type &S3)
{
    set_type result;
    copy(S1.begin(), S1.end(), inserter(result, result.begin()));
    set_difference(S2.begin(), S2.end(), result.begin(), result.end(), inserter(result, result.begin()));
    set_difference(S3.begin(), S3.end(), result.begin(), result.end(), inserter(result, result.begin()));
    return result;
}
set_type OnlyOne (set_type &S1, set_type &S2, set_type &S3)
{
    set_type S12;
    set_type result;
    set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S12, S12.begin()));
    set_difference(S12.begin(), S12.end(), S3.begin(), S3.end(), inserter(result, result.begin()));
    return result;
}
void ex1 ()
{
    set_type ware {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    set_type S1 = CWoS('A', ware);
    set_type S2 = CWoS('B', ware);
    set_type S3 = CWoS('C', ware);

    cout << "Товары, которые продаются в каждом магазине: ";
    SWoS(EveryShop(S1, S2, S3));

    cout << "Товары, которые есть хотя бы в одном магазине: ";
    SWoS(LeastOne(S1, S2, S3));

    cout << "Товары, которые продают только в A: ";
    SWoS(OnlyOne(S1, S2, S3));

    cout << "Товары, которые продают только в B: ";
    SWoS(OnlyOne(S2, S1, S3));

    cout << "Товары, которые продают только в C: ";
    SWoS(OnlyOne(S3, S1, S2));

    system("pause");
}
//--------------------------------Задание №1
//--------------------------------Задание №2
void ShowChar (const set<char> &S)
{
    set<char>::iterator it;
    for(it = S.begin(); it != S.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

set<char> CoOW (string &S) // consonants of one word - соласные, встречающиеся в одном слове
{
    set<char> result;
    string consonants = "бвгджзйклмнпрстфхцчшщ";
    string::iterator n = S.end();
    int c = 0;
    for (string::iterator i = S.begin(); i != n; i++) {
        char c1 = *i;
        if (consonants.find(c1) != consonants.npos)
        {
            string::iterator j = S.begin();
            while ((*j != ' ') && (j != n)) { j++; }
            while (j != n) {
                char c2 = *j;
                if ((c2 == c1) && (i != j)) { c++; }
                j++;
            }
            if (c == 0) { result.insert(c1); }
        }
        c = 0;
    }
    return result;
}
set<char> VoOW (string &S) // vowel of one word - гласные, встречающиеся в одном слове два раза
{
    set<char> result;
    string vowel = "аеёиоуыэюя";
    string::iterator n = S.begin();
    int v = 0;
    string::iterator i = n;
    for (string::iterator i = S.begin(); i != S.end(); i++) {
        char v1 = *i;
        if (vowel.find(v1) != vowel.npos)
        {
            string::iterator j = n;
            while ((*j != ' ') && (j != n)) {
                char v2 = *j;
                if ((v2 == v1) && (i != j)) { v++; }
                j++;
            }
            if (v > 1) { result.insert(v1); }
            n = j++;
        }
        v = 0;
    }
    return result;
}
void string_to_multiset (const string &S, multiset<char> &text)
{
    int n = S.size();
    for (int i=0; i<n; i++) { text.insert(S[i]); }
}
void ex2 ()
{
    string S;
    multiset<char> text;
    cout << "Введите строчными буквами текст на русском языке: ";
    cin.get();
    getline(cin, S);
    string_to_multiset(S, text);
    cout << " Напечатать в алфавитном порядке все согласные буквы, которые входят только в одно слово: ";
    ShowChar(CoOW(S));
    cout << " Напечатать гласные, которые, входят хотя бы в одно слово не менее двух раз: ";
    ShowChar(VoOW(S));
    cout << endl;

}
//--------------------------------Задание №2
//--------------------------------Задание №3
set_type Set_from_Number(int Number)
{
    set_type S;
    while (Number>0)
    {
        S.insert(Number % 10);
        Number /= 10;
    }
    return S;
}
void ex3 ()
{
    cout << "железо + олово = металл" << endl;
    set_type M;
    set_type O;
    set_type MO;
    int n = 1;
    for (int i=100000; i<900001; i++) { // железо
        int i1 = i/100000; // Железо
        int i2 = (i/10000)%10; // жЕлезо/ мЕталл
        int i4 = (i/100)%10; // желЕзо
        int i6 = i%10; // железО
        if ((i6 == 9) && (i2 == i4) && (i1 != 9)) {
            M = Set_from_Number(i);
            if (M.size() == 5) {
                int i3 = (i/1000)%10; // жеЛезо
                int i5 = (i/10)%10; // желеЗо
                for (int j=10000; j<100000; j++) { // олово
                    int j2 = (j/1000)%10; // оЛово
                    if ((i3 == 8) && (i3 == j2)) {
                        int j1 = j/10000; // Олово
                        int j3 = (j/100)%10; // олОво
                        int j5 = j%10; // оловО
                        if ((i6 == j1) && (i6 == j3) && (i6 == j5)) {
                            int j4 = (j/10)%10; // олоВо
                            O = Set_from_Number(j);
                            MO.clear();
                            set_intersection (M.begin(), M.end(), O.begin(), O.end(), inserter(MO, MO.begin()));
                            if (O.size() == 3 && MO.size() == 2) {
                                int ij = i + j; // МЕТАЛЛ
                                if ((ij/100000 == i1+1) && (ij%10 == (ij/10)%10) && (j5 != (ij/100)%10) && (j4 != (ij/100)%10) && (i5 != (ij/100)%10) && (j5 != (ij/1000)%10) && (j4 != (ij/1000)%10) && (i5 != (ij/1000)%10)) {
                                    MO = Set_from_Number(ij);
                                    int ij1 = ij/100000;
                                    if ((MO.size() == 5) && (ij1 == i1+1) && (ij1 != i5) && (ij1 != j4)) {
                                        cout << n << ". " << i << " + " << j <<  " = " << ij << endl;
                                        n++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//--------------------------------Задание №3

void Menu ()
{
    cout << "Задание №1. В трех магазинах продают некоторые товары из имеющегося списка. Определить, какие товары продаются в каждом магазине, какие товары есть только в одном магазине, а какие товары есть хотя бы в одном магазине." << endl;
    cout << "Задание №2. Дан текст на русском языке. Напечатать в алфавитном порядке все согласные буквы, которые входят только в одно слово, и все гласные, которые, входят хотя бы в одно слово не менее двух раз." << endl;
    cout << "Задание №3. Разгадайте ребус:  ЖЕЛЕЗО + ОЛОВО = МЕТАЛЛ (12 решений)." << endl;
    cout << "0. Выход." << endl;
}
int main()
{
    srand(time(0));
    system("chcp 1251 > nul");
    cout << " Лабораторная работа №13, ДИПРБ-11, Вариант №8, Измайлов Наиль" << endl;
    int m = 4;
    while (m != 0)
    {
        Menu();
        do {
            cout << "Ввод: ";
            cin >> m;
        } while ((m < 0) || (m > 3));
        if (m != 0)
        {
            switch (m)
            {
            case 1:
                ex1();
                break;
            case 2:
                ex2();
                break;
            case 3: { ex3(); }
            }
        }
    }
    return 0;
}
