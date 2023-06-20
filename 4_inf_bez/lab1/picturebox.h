#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

class picturebox : public QGraphicsView
{
private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsPixmapItem *item;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;


    QPixmap m_Pixmap;

    QRect window[2];
    QRect goal;

    int p_x = 0;

    int y = 30;
    int pix_x = 190;

    int size = 10;
    int hsize = (size/2);

    int g_y = 80;
    int ty = (g_y+hsize);

    int w_x1 = 30;
    int tx1 = (w_x1+hsize);
    int mx1 = pix_x+tx1;
    int w_x2 = 60;
    int tx2 = (w_x2+hsize);
    int mx2 = pix_x+tx2;

    double g_length1 = sqrt(g_y*g_y + w_x1*w_x1);
    double g_length2 = sqrt(g_y*g_y + w_x2*w_x2);

public:
    explicit picturebox(QWidget *parent = nullptr);

    void draw_set();
    void reset();

    void move_build(const int &_y);
    int get_y() { return y; }

    void move_start_point(const int &_x);
    int set_start_point() { return p_x; }

    int get_w_x1() { return mx1; }
    int get_w_x2() { return mx2; }

    double get_w_length1() { return sqrt(y*y + (mx1-p_x)*(mx1-p_x)); }
    double get_w_length2() { return sqrt(y*y + (mx2-p_x)*(mx2-p_x)); }

    double get_g_length1() { return g_length1; }
    double get_g_length2() { return g_length2; }

};

#endif // PICTUREBOX_H
