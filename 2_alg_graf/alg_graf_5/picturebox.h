#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <cmath>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    QPoint zero;
    QPoint b;
    int o_R;

    int e_r1;
    int e_r2;

public:
    explicit picturebox(QWidget *parent = nullptr);

    void set_zero_x (int x) { zero.setX(x); }
    void set_zero_y (int y) { zero.setY(y); }

    void set_b_x (int x) { b.setX(x); }
    void set_b_y (int y) { b.setY(y); }

    void set_r (int r) { o_R = r; }

    void set_r1 (int r) { e_r1 = r; }
    void set_r2 (int r) { e_r2 = r; }

    QPoint get_zero () { return zero; }

    QPoint get_b () { return b; }

    int get_r () { return o_R; }

    int get_r1 () { return e_r1; }
    int get_r2 () { return e_r2; }

    void paint_line();
    void paint_cyrcle();
    void paint_ellipse();

    void reset();

protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
