#include <iostream>
#include <cmath>

using namespace std;

double f (const double &x, const double &a, const double &b, const double &c)
{
    if (a*x+b <= 0) { throw "Взят отрезок, на котором функция не существует (логарифм не существует)."; }
    return (log(a*x + b)*(x+c) - 1);
}
double Root (double &xn, double &xk, const double &a, const double &b, const double &c, const double &e)
{
    if (e <= 0) { throw " Введена отрицательная или нулевая точность."; }
    double fn = f(xn,a,b,c);
    double fk = f(xk,a,b,c);
    if ((fn * fk) > 0) throw "Взят отрезок, на котором метод неприменим (функция на левой и на правой границах отрезка имеет одинаковые знаки).";
    double xm = xn+(fk*(xk-xn))/(fk-fn);
    if (fabs(xk-xn) < e) { return xm; }
    if (fn*f(xm,a,b,c) > 0) {
        xn = xm;
    } else { xk = xm; }
    return Root(xn, xk, a, b, c, e);
}


int main()
{
    system("chcp 1251 > nul");
    cout << "Лабораторная работа №15, Вариант 8\n Измайлов Наиль \n" << endl;
    cout << "F(x, a, b, c) = (x+c)*ln(a*x+b)-1 = 0" << endl;
    double a, b, c, xn, xk, e;
    cout << " Введите значение коэффициенты функции a, b, c: ";
    cin >> a >> b >> c;
    cout << " Введите левую границу: ";
    cin >> xn;
    cout << " Введите правую границу: ";
    cin >> xk;
    cout << " Введите точность: ";
    cin >> e;
    try {

        double x = Root(xn, xk, a, b, c, e);
        cout << "Корень функции: " << x;
    }
    catch (const char* er) { cout << " Ошибка: " << er << endl; }
    return 0;
}
