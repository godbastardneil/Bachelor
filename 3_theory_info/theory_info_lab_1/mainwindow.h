#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>

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

    void on_ex_1_clicked();
    void on_start_1_clicked();


    std::vector<double> entro_val_2(const double &p_);
    void on_ex_2_clicked();
    void on_start_2_clicked();


    void on_ex_3_clicked();

    std::vector<double> entro_val_3(const int &n, const int &m, const int &k, const double &t);
    void on_start_31_clicked();

    void on_start_32_clicked();


    void on_M_3_valueChanged(int arg1);
    void on_K_3_valueChanged(int arg1);

    void on_to_menu_clicked();

private:
    Ui::MainWindow *ui;

    double C_(const int &n, const int &k);

    void draw_graph(const QVector<double> x, const QVector<double> y);
};
#endif // MAINWINDOW_H
