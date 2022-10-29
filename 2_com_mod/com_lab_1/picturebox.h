#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <QString>
#include <QMessageBox>
#include <cmath>


class PictureBox : public QFrame
{
    Q_OBJECT

public:
    explicit PictureBox(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // PICTUREBOX_H
