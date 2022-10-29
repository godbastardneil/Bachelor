#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <math.h>

class picturebox : public QFrame
{
    QPixmap m_Pixmap;
    QPixmap m_new;

public:
    bool m = false;

    QPoint a = QPoint(0, 0);
    QPoint b = QPoint(50, 50);
    QPoint c = QPoint(80, 30);

    QPoint t = QPoint(0, 0); // точка вокруг вращения
    double a0 = 0; // угол поворота

    double k = 1; // коэффициент изменения

    explicit picturebox(QWidget *parent = nullptr);
    bool chechtr();
    void paint();
    void reset();
    void mirror();
protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
