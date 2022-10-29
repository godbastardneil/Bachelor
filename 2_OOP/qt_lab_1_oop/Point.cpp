#include <iostream>
#include "Point.h"

using namespace std;

string Point::toString() const noexcept { return "x = " + to_string(X) + ", y = " + to_string(Y); }

void Point::Display() const noexcept { cout << toString() << endl; }

void Point::Read() noexcept
{
    double x;
    double y;
    cout << " Введите координату X: ";
    cin >> x;
    cout << " Введите координату Y: ";
    cin >> y;
    *this = Point(x, y);
}

double Point::ZeroLenght() const noexcept { return sqrt(X*X+Y*Y); }

int Point::Compare (Point &Sec) const noexcept {
    double r1 = ZeroLenght();
    double r2 = Sec.ZeroLenght();
    if (r1-r2 < 0) {
        return 1;
    } else if (r1-r2 > 0){
        return -1;
    } else { return 0; }
}

double Point::Lenght (const Point &Sec) const noexcept
{
    double x = Sec.X-X;
    double y = Sec.Y-Y;
    return sqrt((x*x)+(y*y));
}

void Point::moveX (const double &x) noexcept { X += x; }
void Point::moveY (const double &y) noexcept { Y += y; }

double Point::Angle() const noexcept {
    if (X > 0) {
        return (atan(Y/X)*180)/(atan(1)*4);
    } else { return 90.0; }
}

bool Point::Sovpad(const Point &Sec) const noexcept { return (X - Sec.X < 0.001) && (Y - Sec.Y < 0.001); }
