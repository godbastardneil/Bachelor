#include "picturebox.h"

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    carpet = QRect(0, 0, parent->width(), parent->height());
}

void picturebox::paint(unsigned int l, QRect c)
{
    if (l == 0) {
        QPainter painter(this);
        painter.setPen(Qt::yellow);
        painter.drawRect(c);
    } else {
        int width = c.width()/3;
        int height = c.height()/3;

        int x1 = c.left();
        int y1 = c.top();
        // (x1, y1) - координаты левой верхней вершины прямоугольника, от которой считают остальные прямоугольники

        int x2 = x1 + width;
        int y2 = y1 + height;

        int x3 = x1 + 2*width;
        int y3 = y1 + 2*height;


        paint(l - 1, QRect(x1, y1, width, height)); // левый 1(верхний)
        paint(l - 1, QRect(x2, y1, width, height)); // средний 1
        paint(l - 1, QRect(x3, y1, width, height)); // правый 1

        paint(l - 1, QRect(x1, y2, width, height)); // левый 2
        //paint(l - 1, QRect(x2, y2, width, height)); // если нарисовать средний 2, то все будет просто в желтых квадратах
        paint(l - 1, QRect(x3, y2, width, height)); // правый 2

        paint(l - 1, QRect(x1, y3, width, height)); // левый 3
        paint(l - 1, QRect(x2, y3, width, height)); // средний 3
        paint(l - 1, QRect(x3, y3, width, height)); // правый 3
    }
}


void picturebox::paintEvent(QPaintEvent *)
{
    if (trigger) { paint(level, carpet); } // рисование при нажатии
    trigger = false;
}
