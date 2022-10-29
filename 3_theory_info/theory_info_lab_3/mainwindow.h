#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

struct el
{
    QString sym;
    double n = 0;
    double px = 0;
    QString code1 = "";
    QString code2 = "";


    el(const QString &s) { sym = s; }
};

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
    void on_start_clicked();

private:
    Ui::MainWindow *ui;

    QString qs;
    QVector<QVector<el>> word;

    void set_first_table();


    int find(const QChar &qc, QVector<el> &w);

    void sort(QVector<el> &w);

    void shenofano(const int &start, const int &end);
    void set_shenofano();


    void haffman();
    void set_haffman();
};
#endif // MAINWINDOW_H
