#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>

class picturebox : public QFrame
{
public:
    unsigned int level = 5;
    QRect carpet;
    bool trigger = false;

    picturebox(QWidget *parent);
    void paint(unsigned int l, QRect carpet);
protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
