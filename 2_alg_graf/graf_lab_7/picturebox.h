#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QPoint>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    QVector<QPoint> all_p; // все точки фигур
    QVector<QPoint> one; // первая фигура
    QVector<QPoint> two; // вторая фигура
    QVector<QPoint> zatrav; // точка, затравки
    int who = 0;


public:

    explicit picturebox(QWidget *parent = nullptr);
    void draw_set();
    void draw_line(QPoint f, QPoint s, QPainter &painter, const QColor qc, bool w); // w - wall - сторона фишуры

    void postroch_zal();
    void zatravca();

    void check_ckan(QPoint qp, int x_r);
    void postroch_ckan();

    void reset();

protected:
    virtual void paintEvent(QPaintEvent*);

    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // PICTUREBOX_H
