#ifndef POINT_H
#define POINT_H

#include <string>
#include <cmath>

class Point
{
    private:
        double X;
        double Y;
    public:
        Point() noexcept : X(0), Y(0) {}
        Point (const double &x, const double &y) noexcept // инициализация
        {
            X = x;
            Y = y;
        }
        void moveX (const double &x) noexcept; // перемещение по X
        void moveY (const double &y) noexcept; // перемещение по Y
        void Display () const noexcept;  // Вывод
        void Read() noexcept; // Ввод
        std::string toString() const noexcept; // Перевод в string
        double ZeroLenght() const noexcept; // растояние от точки до начала координат
        int Compare(Point &Sec) const noexcept; // 1 - первый ближе к началу координат, чем второй, -1 второй ближе первого, 0 - на одном расстоянии
        double Lenght (const Point &Sec) const noexcept; // расстояние между точками
        double Angle() const noexcept; // угол
        bool Sovpad(const Point &Sec) const noexcept; // проверка на совпадение координа двух точек: 1 - совпадают, 0 - не совпадают
};

#endif // POINT_H
