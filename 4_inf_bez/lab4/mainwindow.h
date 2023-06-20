#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum rule : uint8_t
{
    no = 0,
    read = 1,
    change = 2
};
enum ad_rule : uint8_t
{
    user = 0,
    admin = 1
};
enum privil : uint8_t
{
    unsecret = 0,
    confidential = 1,
    secret = 2,
    topsecret = 3
};

using rules  = QVector<uint8_t>;
using rights = QVector<rules>;

struct user_t
{
    QString name;
    privil priviluss;
};
using users  = QVector<user_t>;

struct object
{
    QString name;
    QString content;
    privil privilobjs;
};
using objects = QVector<object>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_object_list_currentRowChanged(int currentRow);

    void on_user_box_currentIndexChanged(int index);

    void on_in_object_textChanged();

    void on_init_button_clicked();
    void on_copy_button_clicked();

    void on_admin_button_clicked();


    void on_object_edit_but_accepted();
    void on_object_edit_but_rejected();

    void on_user_edit_but_accepted();
    void on_user_edit_but_rejected();

    void on_object_box_currentIndexChanged(int index);
    void on_user_box_2_currentIndexChanged(int index);

    void on_privilobjs_box_currentIndexChanged(int index);
    void on_priviluss_box_currentIndexChanged(int index);

    void on_rights_box_currentIndexChanged(int index);


    void on_back_button_clicked();

private:
    Ui::MainWindow *ui;

    users uss;      // Массив пользователей
    objects objs;   // Массив значений объектов типа String
    rights P;       // Матрица прав доступа

    QVector<privil> priviluss;      // Привилегии пользователей
    QVector<privil> privilobjs;     // Привилегии объектов

    privil privilbuf = privil::topsecret;   // Буффер привилегий
    QString buf;        // Буффер фрагмента текста

    bool search_obj(const QString &name);
    bool search_uss(const QString &name);

    void view_text(const int &i, const int &j);
    void check_buttons(const int &i, const int &j);

    void create_user(const QString &name, const ad_rule &role, const privil &pr);
    void create_object(const QString &name, const QString &content, const privil &pr);

    void delete_user(const int &i);
    void delete_object(const int &j);
};
#endif // MAINWINDOW_H
