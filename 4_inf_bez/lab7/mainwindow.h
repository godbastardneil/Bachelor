#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString alfa = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int step = 11;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_crypt_Button_clicked();

private:
    Ui::MainWindow *ui;

    QString crypt(const QString &str, const QString &alf1, const QString &alf2);
};
#endif // MAINWINDOW_H
