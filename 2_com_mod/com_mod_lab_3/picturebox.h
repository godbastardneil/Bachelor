#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <random>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    int steps; // количество шагов
    double l; // размер шага
    int kol; // количество пересчетов

public:
    picturebox(QWidget *parent);

    void set_steps(const int &s) { steps = s; }
    void set_l(const double &L) { l = L*100; }
    void set_kol(const int &k) { kol = k; }

    QPoint work();
    void reset();
    void paint();
protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
