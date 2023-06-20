#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

typedef double (*Pfun)(const double);  // указатель на функцию
typedef double (&Lfun)(const double);  // ссылка на функцию

const double e = 0.0001;

double integral_P (Pfun f, const double &a, const double &b)
{
    double S(0), S1, y, h;
    int n = 2;
    do {
        S1 = S;
        h = (b-a)/n;
        y = 0;
        for (int i=1; i<n; i++) { y += f(a+h*i); }
        S = h*((f(a)+f(b))/2+y);
        n++;
    } while (fabs(S-S1) >= e);
    return S;
}
double integral_L (Lfun f, const double &a, const double &b)
{
    double S(0), S1, y, h;
    int n = 2;
    do {
        S1 = S;
        h = (b-a)/n;
        y = 0;
        for (int i=1; i<n; i++) { y += f(a+h*i); }
        S = h*((f(a)+f(b))/2+y);
        n++;
    } while (fabs(S-S1) >= e);
    return S;
}

double f1 (double x) { return fabs((8/(4+x*x))-((x*x)/4)); }
double f2 (double x) {
    double f = log(x);
    if (f == 0) { throw "Взят отрезок, на котором функция не существует (знаменатель равен 0)."; }
    return fabs(1/f);
}
double f3 (double x) { return fabs(x*x-x-6); }

int main() {
    system("chcp 1251 > nul");
	double a, b;
	int fun;
	cout << " Выберете площадь чего вы хотите выбрать: \n\t 1. f(x) = 8/(4+x^2), g(x) = (x^2)/4 \n\t 2. f(x) = 1/ln(x) \n\t 3. f(x) = x+6, g(x) = x^2" << endl;
	do {
        cout << " Ввод: ";
        cin >> fun;
	} while ((fun < 0) || (fun > 3));
	cout << " Введите левую и правую границу через пробел: ";
	cin >> a >> b;
    switch (fun)
    {
    case 1: {
            printf("S через указатель = %f\n", integral_P(f1, a, b));
            printf("S через ссылку    = %f", integral_L(f1, a, b));
        break; }
    case 2: {
            try {
                if ((a <= 1) || (b <= 1)) { throw "Взят отрезок, на котором функция не существует (логарифм не существует)."; }
                printf("S через указатель = %f\n", integral_P(f2, a, b));
                printf("S через ссылку    = %f", integral_L(f2, a, b));
            }
            catch (const char* er) { cout << " Ошибка: " << er << endl; }
        break; }
    case 3: {
            printf("S через указатель = %f\n", integral_P(f3, a, b));
            printf("S через ссылку    = %f", integral_L(f3, a, b));
        }
    }
    return 0;
}



