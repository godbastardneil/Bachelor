#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include<QMessageBox>
#include <test_comp.h>

namespace Ui { class test; }

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();
    void set_name(const QString &qs) { name = qs; }
    QString get_name() { return name; }
    QString get_fname() { return fname; }
    void write_test(const QString u_name);
    void show_test();

private slots:
    void on_checkBox_0_clicked(bool checked);
    void on_checkBox_1_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_stud_c_textChanged(const QString &arg1);

    void on_l_back_clicked();
    void on_l_forward_clicked();

    void on_end_test_clicked();

private:
    Ui::test *ui;
    QString fname = "files/test.txt"; // путь до файла
    QString name; // имя тестируемого
    QVector<quest> testing; // тест
    QVector<QString> ans; // ответы пользователя
    int i, n;

    reader writer;

    test(const test &)  = delete;
    test(const test &&) = delete;
    test& operator=(const test &)  = delete;
    test& operator=(const test &&) = delete;
};

#endif // TEST_H
