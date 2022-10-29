#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <math.h>

class picturebox : public QFrame
{
private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    int w, h;
    QString name = ":/windows.jpg";
    int r=100;
    int g=100;
    int b=100;
    double l=1.0;

public:

    void set_level (const double &L) { l = L; }
    void set_name (const QString &qs) { name = qs; }

    explicit picturebox(QWidget *parent = nullptr);
    void pic();
    void draw();
    void reset();

protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
