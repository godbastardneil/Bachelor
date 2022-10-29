#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QMessageBox>

#include "reader.h"

namespace Ui { class admin; }

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    void show_text(const QString s);

private slots:
    void on_r_Main_clicked(); // открыть для редактирования "титульник"
    void on_r_Theory_clicked(); // открыть для редактирования "теория"
    void on_r_Slovo_clicked(); // открыть для редактирования "словарь"
    void on_r_Test_clicked(); // открыть для редактирования "тест"
    void on_r_Statistic_clicked(); // открыть для удаления "статистика"
    void on_r_Rules_clicked(); // открыть для редактирования "правила"
    void on_r_Exercise_clicked(); // открыть для редактирования "задача"
    void on_r_Names_clicked(); // открыть для редактирования "имена"
    void on_Do_clicked(); // сохранить изменения

private:
    Ui::admin *ui;
    QString fname; // путь до файла
    QString text; // текст

    void setEnabl();

    admin(const admin &)  = delete;
    admin(const admin &&) = delete;
    admin& operator=(const admin &)  = delete;
    admin& operator=(const admin &&) = delete;
};

#endif // ADMIN_H
