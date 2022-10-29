#ifndef SHOW_TEXT_H
#define SHOW_TEXT_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

namespace Ui { class show_text; }

class show_text : public QWidget
{
    Q_OBJECT

public:
    explicit show_text(QWidget *parent = nullptr);
    ~show_text();
    void read_info();

signals:
    void return_to_menu();

private slots:
    void on_return_to_clicked();

private:
    Ui::show_text *ui;
    QString info = "files/info.html";

    show_text(const show_text &)  = delete;
    show_text(const show_text &&) = delete;
    show_text& operator=(const show_text &)  = delete;
    show_text& operator=(const show_text &&) = delete;
};
#endif // SHOW_TEXT_H
