#ifndef DEMO_H
#define DEMO_H

#include <QWidget>

namespace Ui { class demo; }

class demo : public QWidget
{
    Q_OBJECT

public:
    explicit demo(QWidget *parent = nullptr);
    ~demo();

signals:
    void return_to_menu();

private slots:
    void on_str_textEdited(const QString &arg1); // ввод математического выражения
    void on_Ok_clicked(); // начало демонстрации
    void on_back_clicked(); // назад по демонстрации
    void on_forward_clicked(); // вперед по демострации

    void on_return_to_clicked(); // возвращение в меню

private:
    Ui::demo *ui;
    int i, n; // номер нынешней страницы и количество страниц

    demo(const demo &)  = delete;
    demo(const demo &&) = delete;
    demo& operator=(const demo &)  = delete;
    demo& operator=(const demo &&) = delete;
};

#endif // DEMO_H
