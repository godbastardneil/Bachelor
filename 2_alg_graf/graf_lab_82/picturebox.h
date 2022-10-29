#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <QPoint>
#include <cmath>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    const double pi = std::atan(1.0)*4;

public:

    explicit picturebox(QWidget *parent = nullptr);

    inline int get_x(double t);
    inline int get_y(double t);

    void draw_set();
    void paintit();

    void reset();

protected:
    virtual void paintEvent(QPaintEvent*);

};

#endif // PICTUREBOX_H
