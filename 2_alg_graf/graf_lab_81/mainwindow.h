#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>

    #include <QBarSet>
    #include <QBarSeries>
    #include <QBarCategoryAxis>
    #include <QValueAxis>
    #include <QChartView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    uint8_t creat_sets(QtCharts::QBarSeries *qBarS);
    void create_histogram();

private:
    Ui::MainWindow *ui;

    QtCharts::QChartView *cV;
};
#endif // MAINWINDOW_H
