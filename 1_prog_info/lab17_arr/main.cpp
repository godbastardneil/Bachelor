#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;

//------------------------------------------------------Задание №1
void push (int *arr, int &top, const int &NewInfo)
{
    top++;
    arr[top] = NewInfo;
}
void pushKaKey (int *arr, const int &k, int &top)
{
    int input;
    for (int i=0; i<k; i++) {
        cout << " Введите значение " << i+1 << ": ";
        cin >> input;
        push(arr, top, input);
    }
}
void pushKaFile (int *arr, const int &k, int &top)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    for (int i=0; i<k; i++)
    {
        inf >> input;
        push(arr, top, input);
    }
    inf.close();
}
void pushKaRand (int *arr, const int &k, int &top, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    for (int i=0; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(arr, top, input);
    }
}

void PrintStack (const int *arr, int &top)
{
    if(top != -1) {
        int i = top;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << arr[i] << endl;
        i--;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != -1) {
            cout << "         "<< arr[i] << endl;
            i--;
        }
    } else { cout << " Стек пуст"; }
    cout << endl;
}

int Sumd (const int &db, const int &de, const int *arr1, int &top1)
{
    int c = 0;
    int i = top1;
    while (i != -1) {
        int s = arr1[i];
        if ((s >= db) && (s <= de)) { c++; }
        i--;
    }
    return c;
}
void Copyd (const int &db, const int &de, const int *arr1, int &top1, int *arr2, int &top2)
{
    int i = top1;
    while (i != -1) {
        int s = arr1[i];
        if ((s >= db) && (s <= de)) { push(arr2, top2, s); }
        i--;
    }
}

void Init (int *arr, const int &k, int &top)
{
    int m_init;
    cout << " Как вы хотите ввести значения элемента: \n  1. Файл \n  2. Клавиатура \n  3. Случайно " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ФАЙЛ
            pushKaFile(arr, k, top);
        break; }
    case 2: { // КЛАВИАТУРА
            pushKaKey(arr, k, top);
        break; }
    case 3: { // СЛУЧАЙНО
            int maxim, minim;
            do {
                do {
                    cout << " Введите минимальное значение [ -32767; 32767]: ";
                    cin >> minim;
                } while ( (minim < -32767) || (minim > 32767) );
                do {
                    cout << " Введите максимальное значение [ -32767; 32767]: ";
                    cin >> maxim;
                } while ( (maxim < -32767) || (maxim > 32767) );
            } while (minim >= maxim);
            pushKaRand(arr, k, top, minim, maxim);
        }
    }
}
//------------------------------------------------------Задание №1
//------------------------------------------------------Задание №2
void CreareQueue (int *arr, const int &NewInfo, int &head, int &tail)
{
    tail = 0;
    head = 0;
    arr[tail] = NewInfo;
}

void pushKaKey (int *arr, const int &k, int &head, int &tail)
{
    int input;
    cout << " Введите значение 1: ";
    cin >> input;
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++) {
        cout << " Введите значение " << i+1 << ": ";
        cin >> input;
        push(arr, tail, input);
    }
}
void pushKaFile (int *arr, const int &k, int &head, int &tail)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    inf >> input;
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++)
    {
        inf >> input;
        push(arr, tail, input);
    }
    inf.close();
}
void pushKaRand (int *arr, const int &k, int &head, int &tail, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    input = minim + rand()%(znam);
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(arr, tail, input);
    }
}

void PrintQueue (const int *arr, const int &head, const int &tail)
{
    if(head != tail+1) {
        int i = head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << arr[i];
        i++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != tail+1) {
            if (i == tail) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
            cout << " " << arr[i];
            i++;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else { cout << " Стек пуст"; }
    cout << endl;
}

void pop (int &head, const int &tail)
{
    if (head != tail+1) { head++; }
}

int kolvot (int *arr, int &head, const int &tail, const int &db, const int &de)
{
    int c = 0;
    int i = head;
    while (i != tail+1) {
        int s = arr[i];
        if ((s < db) && (s > de)) { c++; }
        i++;
    }
    return c;
}
void Takefromt (int *arr, int *tarr, int &tail, int &thead, int &ttail)
{
    while (thead != ttail+1) {
        push(arr, tail, tarr[thead]);
        pop(thead, ttail);
    }
}
void Moved (const int &db, const int &de, const int &k, int *arr, int &head, int &tail)
{
    int n = kolvot(arr, head, tail, db, de);
    int *tarr = new int [n];
    int thead = -1;
    int ttail = -1;
    int i = 0;
    int j = 0;
    while ((head != tail+1) && (i != k)) {
        int s = arr[head];
        if ((s >= db) && (s <= de))
        {
            push(arr, tail, s);
        } else {
            if(j!=0) {
                push(tarr, ttail, s);
            } else { CreareQueue(tarr, s, thead, ttail); }
            j++;
        }
        pop(head, tail);
        i++;
    }
    Takefromt(arr, tarr, tail, thead, ttail);
}

void Init (int *arr, const int &k, int &head, int &tail)
{
    int m_init;
    cout << " Как вы хотите ввести значения элемента: \n  1. Файл \n  2. Клавиатура \n  3. Случайно " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ФАЙЛ
            pushKaFile(arr, k, head, tail);
        break; }
    case 2: { // КЛАВИАТУРА
            pushKaKey(arr, k, head, tail);
        break; }
    case 3: { // СЛУЧАЙНО
            int maxim, minim;
            do {
                do {
                    cout << " Введите минимальное значение [ -32767; 32767]: ";
                    cin >> minim;
                } while ( (minim < -32767) || (minim > 32767) );
                do {
                    cout << " Введите максимальное значение [ -32767; 32767]: ";
                    cin >> maxim;
                } while ( (maxim < -32767) || (maxim > 32767) );
            } while (minim >= maxim);
            pushKaRand(arr, k, head, tail, minim, maxim);
        }
    }
}
//------------------------------------------------------Задание №2

int main()
{
    srand((unsigned)time(0));
    system("chcp 1251 > nul");
    int k;
    int ex;
    cout << "Выберете задание: \n1. Задание №1 \n Создать стек из чисел. Перенести в другой стек все элементы со значением, принадлежащем указанному диапазону. " << endl;
    cout << "2. Задание №2 \n Создать очередь из чисел. Все числа из указанного диапазона переместить в начало очереди. " << endl;
    do {
        cout << " Ввод: ";
        cin >> ex;
    } while ((ex < 1) || (ex > 2));
    do {
        cout << " Введите количество элементов для формирования: ";
        cin >> k;
    } while (k <= 0);
    int db; // начало диапазона
    int de; // конец диапазона
    switch (ex)
    {
    case 1: {
            int *arr1 = new int [k];
            int top1 = -1;
            Init(arr1, k, top1);
            cout << " Стек 1: ";
            PrintStack(arr1, top1);
            do {
                cout << " Введите значение начала диапазона: ";
                cin >> db;
                cout << " Введите значение конца диапазона: ";
                cin >> de;
            } while (db >= de);
            int *arr2 = new int [Sumd(db, de, arr1, top1)];
            int top2 = -1;
            Copyd(db, de, arr1, top1, arr2, top2);
            cout << " Стек 1: ";
            PrintStack(arr1, top1);
            cout << " Стек 2: ";
            PrintStack(arr2, top2);
        break; }
    case 2: {
            int *arr = new int [k];
            int head = -1;
            int tail = -1;
            Init(arr, k, head, tail);
            cout << " Стек 1: ";
            PrintQueue(arr, head, tail);
            do {
                cout << " Введите значение начала диапазона: ";
                cin >> db;
                cout << " Введите значение конца диапазона: ";
                cin >> de;
            } while (db >= de);
            Moved(db, de, k, arr, head, tail);
            cout << " Очередь: ";
            PrintQueue(arr, head, tail);
        }
    }
    return 0;
}
