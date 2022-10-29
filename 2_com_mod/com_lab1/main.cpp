#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double v0 (0), h;
    double g = 9.806;

    int m;
    cout << " \n 1. Задание №1 \n 2. Задание №3" << endl;
    do {
        cout << " Ввод: ";
        cin >> m;
    } while ((m<1) || (m>2));

    do {
        cout << " Введите необходимую высоту: ";
        cin >> h;
    } while (h <= 0);

    switch (m) {
        case 1: {
            do {
                cout << " Введите начальную скорость: ";
                cin >> v0;
            } while (v0 <= 0);
            double t = v0/g;
            double gh2 = sqrt(2*g*h);
            if (fabs(v0-gh2) < 0.001) {
                cout << " Высота достигается через " << t << ", потому что это максимальная высота, которую он достигнет";
            } else if (v0 < gh2) {
                cout << " Высота недостижима";
            } else {
                double t1 = (v0 - sqrt(v0*v0 - 2*g*h))/g;
                double t2 = (v0 + sqrt(v0*v0 - 2*g*h))/g;
                cout << " Высота достигается 2 раза через " << t1 << " с и " << t2 << " c";
            }
            double H = (v0*v0)/(2*g);
            cout << "\n Максимальная высота: " << H << endl;

            break; }
        case 2: {
                int l;
                do {
                    cout << " Введите необходимое расстояние: ";
                    cin >> l;
                } while (l <= 0);
                double a = 0;
                double yb = 0;
                for (a=(atan(l/h)*180)/(atan(1)*4); a<80; a+=1) {
                    double a0 = (a*(atan(1)*4))/180;
                    v0 = sqrt((g*l*l)/(2*(l*tan(a0)-h)*cos(a0)*cos(a0)));
                    yb = (l-0.01)*tan(a0) - (g*(l-0.01)*(l-0.01))/(2*v0*v0*cos(a0)*cos(a0));
                    if (yb-h > 0) { cout << "Угол = " << a << ", скорость = " << v0 << endl; }
                }
            }
    }

    return 0;
}
