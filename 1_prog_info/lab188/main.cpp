#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void from_string_to_vector (string &S, vector<int> &V)
{
    int n = S.size();
    if (S[0] == '-') {
        V.push_back(-((int)S[1] - 48));
        for (int i=2; i<n; i++) {
            V.push_back((int)S[i] - 48);
        }
    } else {
        for (int i=0; i<n; i++) {
            V.push_back((int)S[i] - 48);
        }
    }
}
string from_vector_to_string (const vector<int> &V)
{
    int n = V.size();
    string S = "";
    for (int i=0; i<n; i++) {
        S += to_string(V[i]);
    }
    return S;
}

void print_vector (const vector<int> &V)
{
    int n = V.size();
    for (int i=0; i<n; i++) {
        cout << V[i] << " ";
    }
    cout << endl;
}

bool bigger (const vector<int> &A, const vector<int> &B)
{
    if (A.size() > B.size()) { return true; }
    if (A.size() < B.size()) { return false; }
    int n = A.size();
    for (int i=0; i<n; i++) {
        if (abs(A[i]) != abs(B[i])) {
            if (abs(A[i]) > abs(B[i])) {
                return true;
            } else { return false; }
        }
    }
    return true;
}

void clean (vector<int> &result)
{
    while (result[0] == 0)
    {
        for (size_t i=0; i<result.size()-1; i++) {
            result[i] = result[i+1];
        }
        result.pop_back();
    }
}
vector<int> division (vector<int> &result, const vector<int> &S)
{
    bool z = 0;
    if (result[0] < 0) {
        z = 1;
        result[0] = -result[0];
    }
    int n = S.size();
    int m = result.size();
    while (bigger(result, S))
    {
        for (int i=0; i<n; i++)
        {
            int s = n-i-1;
            int r = m-i-1;
            if (S[s] > result[r]) {
                result[r-1]--;
                result[r] += 10-S[s];
            } else { result[r] -= S[s]; }
        }
        clean(result);
    }
    if (z) { result[0] = -result[0]; }
    return result;
}

int main()
{
    cout << "  Лабораторная работа №18, Вариант №8\n Измайлов Наиль \n" << endl;
    string S;
    cout << " Найти наиболее часто встречающуюся цифру в остатке от деления двух длиннфх чисел A и B, заданных с клавиатуры." << endl;
    cout << " Введите число A: ";
    getline(cin, S);
    vector<int> A;
    from_string_to_vector (S, A);
    clean(A);
    cout << " Введенное число: ";
    print_vector(A);
    S.clear();
    cout << " Введите число B: ";
    getline(cin, S);
    vector<int> B;
    from_string_to_vector (S, B);
    clean(B);
    cout << " Введенное число: ";
    print_vector (B);
    B[0] = abs(B[0]);
    cout << " Остаток от деления ";
    if (A != B) {
        if (bigger(A, B) == true) {
            cout << "A%B: ";
            print_vector(division(A, B));
        } else {
            cout << "B%A: ";
            print_vector(division(B, A));
        }
        cout << endl;


    } else { cout << " Остаток от деления: 0" << endl; }
    return 0;
}
