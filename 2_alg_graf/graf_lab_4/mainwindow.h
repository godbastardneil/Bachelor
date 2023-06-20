#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void draw();

private slots:
    void on_X_A_valueChanged(int arg1);
    void on_Y_A_valueChanged(int arg1);

    void on_X_B_valueChanged(int arg1);
    void on_Y_B_valueChanged(int arg1);

    void on_X_C_valueChanged(int arg1);
    void on_Y_C_valueChanged(int arg1);

    void on_X_T_valueChanged(int arg1);
    void on_Y_T_valueChanged(int arg1);

    void on_Koo_valueChanged(double arg1);

    void on_angle_valueChanged(int arg1);

    void on_mirror_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    picturebox *pb_frame;
};
#endif // MAINWINDOW_H
