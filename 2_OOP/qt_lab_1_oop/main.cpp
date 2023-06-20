#include <iostream>
#include "Point.h"

using namespace std;

int menu () {
    int n;
    cout << endl;
    cout << "1. Переместить точку p1 по X" << endl;
    cout << "2. Переместить точку p1 по Y" << endl;
    cout << "3. Растояние от точки p1 до начала координат" << endl;
    cout << "4. Преобразование точку p1 в полярные координаты" << endl;
    cout << "5. Сравнение точек p1 и p2 по совпадению" << endl;
    cout << "6. Сравнение точек p1 и p2 по растоянию до начала координат" << endl;
    cout << "7. Растояние между точками p1 и p2" << endl;
    cout << "0. Выход" << endl; // завершение выполнения программы
    do {
        cout << "Ввод: ";
        cin >> n;
    } while ((n<0) || (n>7));
    return n;
}
int main()
{
    cout << " Лабораторная работа №1, вариант №12. Измайлов Наиль" << endl;
    cout << "Инициализация точки pt1 значениями 1 и 2" << endl;
    Point pt1(1, 2);
    pt1.Display();
    cout << "Размер класса: " << sizeof(pt1) << endl;

    Point p1;
    cout << " Введите координаты точки p1:" << endl;
    p1.Read();

    cout << "Инициализация точки pt2 точкой p1 (pt2(p1)): " << endl;
    Point pt2(p1);
    pt2.Display();

    cout << "Инициализация точки pt3 точкой p1 (pt3 = p1): " << endl;
    Point pt3 = pt2;
    pt3.Display();

    cout << "Инициализация точки  pt4 (pt4{}): " << endl;
    Point pt4 {};
    pt4.Display();

    int m = menu();
    while (m != 0)
    {
        if (m<5) { // первые 4 задания не нуждаются в создании второй точки
            switch (m)
            {
                case 1: { // Переместить точку p1 по X
                        double nx;
                        cout << " На сколько переместить X: ";
                        cin >> nx;
                        p1.moveX(nx);
                        p1.Display();
                    break; }
                case 2: { // Переместить точку p1 по Y
                        double ny;
                        cout << " На сколько переместить Y: ";
                        cin >> ny;
                        p1.moveY(ny);
                        p1.Display();
                    break; }
                case 3: { // Расстояние от точки p1 до начала координат
                        cout << "Точка находится на расстоянии от начала координат = " << p1.ZeroLenght() << endl;
                    break; }
                case 4: { cout << " Полярные координаты 1: r = " << p1.ZeroLenght() << "; угол = " << p1.Angle(); } // Преобразование точку p1 в полярные координаты
            }
        } else { // здесь задания, для которых необходима вторая точка
            Point p2;
            cout << " Введите координаты точки p2: " << endl;
            p2.Read();
            switch (m)
            {
                case 5: { // Сравнение точек p1 и p2 по совпадению
                        if (p1.Sovpad(p2)) {
                            cout << "Совпадают";
                        } else { cout << "Не совпадают"; }
                    break; }
                case 6: { // Сравнение точек p1 и p2 по растоянию до начала координат
                        int who = p1.Compare(p2);
                        if (who == 1) {
                            cout << "Точка p1 ближе к началу координат";
                        } else if (who == -1){
                            cout << "Точка p2 ближе к началу координат";
                        } else { cout << "Точки на одном расстоянии до начала координат"; }
                    break; }
                case 7: { cout << " Точки находится на растоянии = " << p1.Lenght(p2); } // Растояние между точками p1 и p2
            }
        }
        m = menu();
    }
    return 0;
}
