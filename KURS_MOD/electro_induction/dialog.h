#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "reader.h"

namespace Ui { class dialog; }

class dialog : public QDialog
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();

    QString get_name() { return name; } // получить имя пользователя
    QString get_password() { return password; } // получить пароль пользователя
    uint8_t isCancel() { return c; } // статус входа - отмена/ок

private slots:
    void on_name_textChanged(const QString &arg1) { name = arg1 + "\n"; } // ввод имени
    void on_password_textChanged(const QString &arg1) { password = arg1 + "\n"; } // ввод паролем
    void on_buttonBox_accepted(); // ок
    void on_buttonBox_rejected() { c = 3; close(); } // отмена

    void on_checkBox_clicked(bool checked); // админ или нет

private:
    Ui::dialog *ui;

    QString name; // введеное имя
    QString password; // введеный пароль

    QString data_base; // база данных

    uint8_t c; // с каким модом выключается авторизация
    bool check;  // админ или нет
    QString data = "files/names.txt";

    dialog(const dialog &)  = delete;
    dialog(const dialog &&) = delete;
    dialog& operator=(const dialog &)  = delete;
    dialog& operator=(const dialog &&) = delete;
};

#endif // DIALOG_H
