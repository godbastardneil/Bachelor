#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <QPoint>
#include <cmath>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    int i = 0;

public:
    explicit picturebox(QWidget *parent = nullptr);

    void set_i(int j) { i = j; }

    void reset();

    int f(double x, double z);

    void doit();

protected:
    virtual void paintEvent(QPaintEvent*);

};

#endif // PICTUREBOX_H
