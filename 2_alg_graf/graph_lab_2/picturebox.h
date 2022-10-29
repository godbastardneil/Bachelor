#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <QTimer>

struct Star // звезда
{
    double x, y; // координаты
    double dx, dy; // шаг для расхождения
    int size = 1; // размер
    QColor color; // цвет
};
class PictureBox : public QFrame
{
    Q_OBJECT
    QPixmap m_Pixmap;
    QPixmap m_new;
public:
    explicit PictureBox(QWidget *parent = nullptr);
    void drowS();
    void reset();
    bool trail = false;
protected:
    virtual void paintEvent(QPaintEvent*);
};
#endif // PICTUREBOX_H

