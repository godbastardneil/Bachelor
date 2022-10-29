#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPair>

#include "picturebox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_spinBox_1_valueChanged(double arg1);

    void on_spinBox_2_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;

    picturebox *pb;

    double k1 = 2.0;
    double k2 = 0.5;

    double kl1;
    double kl2;

    double POK1;
    double POK2;

    double step;

    void m_math();
    void math();

};
#endif // MAINWINDOW_H
