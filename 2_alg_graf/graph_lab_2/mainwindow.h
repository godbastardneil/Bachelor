#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <random>
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

    void Rand();
    double newY_Coord(double x1, double y1, double x);
    QTimer *paintTimer;

private slots:

    void convergence(); // схождение
    void discrepancy(); // расхождение

    void on_Remove_clicked(); // кнопка расхождения
    void on_Start_clicked(); // кнопка схождения
    void on_Stop_clicked(); // кнопка стоп

    void on_Speed_valueChanged(int value); // скорость движения точек
    void on_Num_valueChanged(int arg1); // количество точек
    void on_Min_valueChanged(int arg1); // минимально возможный размер
    void on_Max_valueChanged(int arg1); // максимально возможный размер

    void on_Line_toggled(bool checked); // кнопка рисования следа
    void on_Ok_clicked(); // начало генерации и рисования

private:
    Ui::MainWindow *ui;
    PictureBox *pb_frame;
    int N = 1; // количетсво звезд
    int speed = 1; // скорость
    int min = 1;
    int max = 1;
};


#endif // MAINWINDOW_H
