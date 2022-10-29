#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <picturebox.h>

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
    void on_rep_clicked();

    void on_zalit_clicked();

    void on_skan_clicked();

    void on_zatravka_clicked();

private:
    Ui::MainWindow *ui;
    picturebox *pb;
};
#endif // MAINWINDOW_H
