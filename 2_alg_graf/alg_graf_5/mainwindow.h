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

private slots:
    void on_X2_valueChanged(int arg1);

    void on_Y2_valueChanged(int arg1);

    void on_R0_valueChanged(int arg1);

    void on_Ok_cyrcle_clicked();

    void on_Ok_line_clicked();

    void on_R1_valueChanged(int arg1);

    void on_R2_valueChanged(int arg1);

    void on_Ok_ellipse_clicked();

private:
    Ui::MainWindow *ui;
    picturebox *pb_frame;
};
#endif // MAINWINDOW_H
