#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCustomPlot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_init_A_valueChanged(double arg1) { a = arg1; }
    void on_init_B_valueChanged(double arg1) { b = arg1; }
    void on_init_C_valueChanged(double arg1) { c = arg1; }

    void on_init_alpha_valueChanged(double arg1) { alpha = arg1; }
    void on_init_beta_valueChanged (double arg1) { beta = arg1; }
    void on_init_gamma_valueChanged(double arg1) { gamma = arg1; }

    void on_init_key_textEdited(const QString &arg1);

    void on_OK_Button_clicked();

private:
    Ui::MainWindow *ui;

    double a, b, c;
    double alpha, beta, gamma;
    QVector<double> k;
    const int size = 10;

    double X(const double &t);
    void fun_print(QCustomPlot *qcp, const QVector<double> &x, const QVector<double> &y);
};
#endif // MAINWINDOW_H
