#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_orig_text_textChanged();

    void on_M_Edit_valueChanged(int arg1);
    void on_K_Edit_valueChanged(int arg1);

    void on_crypt_but_clicked();

private:
    Ui::MainWindow *ui;

    int M = 0, K = 0, p = 0, tmp_p = 0;

    void write_lat();

    void check_mk();

    bool check_init_lat();

    void crypt();
    void decrypt();
};
#endif // MAINWINDOW_H
