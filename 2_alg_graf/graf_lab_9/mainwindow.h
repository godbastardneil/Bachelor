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
    void on_reset_clicked();

    void on_Ok_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    picturebox *pb;

};
#endif // MAINWINDOW_H
