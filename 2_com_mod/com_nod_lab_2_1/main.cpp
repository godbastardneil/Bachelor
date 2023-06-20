#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double k = 0.1;
    double m1;
    double t1;
    double m2;
    double t2;
    double t;
    double time;

    do {
        cout << " Введите температуру октружающей среды: ";
        cin >> t;
    } while (t<-273);

    do {
        cout << " Введите массу первой жидкости: ";
        cin >> m1;
    } while (m1<0);
    do {
        cout << " Введите температуру первой жидкости: ";
        cin >> t1;
    } while (t1<-273);

    do {
        cout << " Введите массу второй жидкости: ";
        cin >> m2;
    } while (m2<0);
    do {
        cout << " Введите температуру второй жидкости: ";
        cin >> t2;
    } while (t2<-273);

    do {
        cout << " Введите время ожидания: ";
        cin >> time;
    } while (time<=0);

    double T = t1;
    double M = m1;
    double i = m2/10;

    T = t + (T - t)*exp(-k*time);
    while (M < m1+m2) {
        T = (M*T+i*t2)/(M + i);
        M += i;
        T = t + (T - t)*exp(-k*0.1);
    }
    cout << " Если ждать, а только потом влить №2 в №1, то температура смеси: " << T << endl;

    T = t1;
    M = m1;
    i = m2/10;

    while (M < m1+m2) {
        T = (M*T+i*t1)/(M + i);
        M += i;
        T = t + (T - t)*exp(-k*0.1);
    }
    T = t + (T - t)*exp(-k*time);
    cout << " Если сначала влить №2 в №1, а только потом подождть, то температура смеси: " << T << endl;


    return 0;
}
