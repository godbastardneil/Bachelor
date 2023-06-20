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
    void on_steps_valueChanged(int arg1);

    void on_L_vol_valueChanged(double arg1);

    void on_kol_valueChanged(int arg1);

    void on_Ok_clicked();

private:
    Ui::MainWindow *ui;
    picturebox *pb;
};
#endif // MAINWINDOW_H
