#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_user("admin_1", ad_rule::admin, privil::topsecret);
    create_user("admin_2", ad_rule::admin, privil::topsecret);
    create_user("user_1", ad_rule::user, privil::confidential);
    create_user("user_2", ad_rule::user, privil::secret);
    create_user("user_3", ad_rule::user, privil::unsecret);

    create_object("object_1", "object_1_text", privil::topsecret);
    create_object("object_2", "object_2_text", privil::topsecret);
    create_object("object_3", "object_3_text", privil::secret);
    create_object("object_4", "object_4_text", privil::confidential);
    create_object("object_5", "object_5_text", privil::unsecret);

    rule p = rule(P[0][1]);
    privil pro = objs[0].privilobjs;
    privil pru = uss[0].priviluss;

    ui->rights_box->addItem("Нет прав");
    ui->rights_box->addItem("Чтение");
    ui->rights_box->addItem("Модификация");

    ui->privilobjs_box->addItem("Не секретно");
    ui->privilobjs_box->addItem("Конфиденциально");
    ui->privilobjs_box->addItem("Сектерно");
    ui->privilobjs_box->addItem("Совершенно секретно");

    ui->priviluss_box->addItem("Не секретно");
    ui->priviluss_box->addItem("Конфиденциально");
    ui->priviluss_box->addItem("Сектерно");
    ui->priviluss_box->addItem("Совершенно секретно");


    P[0][1] = p;
    objs[0].privilobjs = pro;
    uss[0].priviluss = pru;

    ui->rights_box->setCurrentIndex(P[0][1]);
    ui->priviluss_box->setCurrentIndex(uss[0].priviluss);
    ui->privilobjs_box->setCurrentIndex(objs[0].privilobjs);

}
MainWindow::~MainWindow() { delete ui; }


bool MainWindow::search_obj(const QString &name)
{
    for (int i=0; i<objs.size(); ++i)
    {
        if (objs[i].name == name) { return true; }
    }
    return false;
}
bool MainWindow::search_uss(const QString &name)
{
    for (int i=0; i<uss.size(); ++i)
    {
        if (uss[i].name == name) { return true; }
    }
    return false;
}

void MainWindow::view_text(const int &i, const int &j)
{
    if (i < uss.size() && j < objs.size())
    {
        ui->in_object->setText(objs[j].content);
        qDebug() << P[i][j+1] << uss[i].priviluss << objs[j].privilobjs;
        if (P[i][j+1] == rule::no || uss[i].priviluss < objs[j].privilobjs)
        {
            ui->in_object->clear();
            ui->in_object->setReadOnly(true);
        } else if (P[i][j+1] == rule::read)
        {
            ui->in_object->setReadOnly(true);
        } else { ui->in_object->setReadOnly(false); }
    }
}
void MainWindow::check_buttons(const int &i, const int &j)
{
    if (i < uss.size() && j < objs.size())
    {
        if (P[i][0] == ad_rule::admin) {
            ui->admin_button->setEnabled(true);
        } else { ui->admin_button->setEnabled(false); }

        if (uss[i].priviluss > objs[j].privilobjs)
        {
            ui->copy_button->setEnabled(true);
        } else { ui->copy_button->setEnabled(false); }

        if (privilbuf < objs[j].privilobjs && P[i][j+1] == rule::change)
        {
            ui->init_button->setEnabled(true);
        } else { ui->init_button->setEnabled(false); }
    }
}

void MainWindow::create_user(const QString &name, const ad_rule &role, const privil &pr)
{
    uss.emplace_back(user_t{name, pr});
    rule r = rule::no;
    if (role == ad_rule::admin) { r = rule::change; }
    P.emplace_back(rules(objs.size()+1, r));
    P[uss.size()-1][0] = role;


    ui->user_box->addItem(name);
    ui->user_box_2->addItem(name);
}
void MainWindow::create_object(const QString &name, const QString &content, const privil &pr)
{
    objs.emplace_back(object{name, content, pr});

    rule p;
    for (int i=0; i<P.size(); ++i)
    {
        p = rule::no;
        if (P[i][0] == ad_rule::admin) { p = rule::change; }
        P[i].emplace_back(p);
    }


    ui->object_list->addItem(name);
    ui->object_box->addItem(name);
}

void MainWindow::delete_user(const int &i)
{
    uss.remove(i);
    P.remove(i);

    ui->user_box->removeItem(i);
    ui->user_box_2->removeItem(i);
}
void MainWindow::delete_object(const int &j)
{
    objs.remove(j);

    for (int i=0; i<P.size(); ++i) { P[i].remove(j+1); }

    delete ui->object_list->item(j);
    ui->object_box->removeItem(j);
}


void MainWindow::on_object_list_currentRowChanged(int currentRow)
{
    int i = ui->user_box->currentIndex();
    if (i >= 0) { view_text(i, currentRow); check_buttons(i, currentRow); }
}
void MainWindow::on_user_box_currentIndexChanged(int index)
{
    int j = ui->object_list->currentRow();
    buf.clear();
    privilbuf = privil::topsecret;
    if (j >= 0) { view_text(index, j); check_buttons(index, j); }
}

void MainWindow::on_in_object_textChanged()
{
    if (P[ui->user_box->currentIndex()][ui->object_list->currentRow()+1] == rule::change) {
        objs[ui->object_list->currentRow()].content = ui->in_object->toPlainText();
    }
}
void MainWindow::on_init_button_clicked()
{
    ui->in_object->setText(ui->in_object->toPlainText()+buf);
}
void MainWindow::on_copy_button_clicked()
{
    privilbuf = objs[ui->object_list->currentRow()].privilobjs;
    buf = ui->in_object->toPlainText();
}

void MainWindow::on_admin_button_clicked()
{
    int i = ui->user_box->currentIndex();
    if (P[i][0] == ad_rule::admin) { ui->stackedWidget->setCurrentIndex(1); }
}








void MainWindow::on_object_edit_but_accepted()
{
    QString tmp = ui->object_init->text();
    privil pr = privil(ui->privilobjs_box->currentIndex());
    if (tmp != "" && !search_obj(tmp)) { create_object(tmp, "", pr); }
}
void MainWindow::on_object_edit_but_rejected()
{
    delete_object(ui->object_box->currentIndex());
}


void MainWindow::on_user_edit_but_accepted()
{
    QString tmp = ui->user_init->text();
    ad_rule ru = ad_rule::user;
    privil pr = privil(ui->priviluss_box->currentIndex());
    if (ui->admin_box->isChecked()) { ru = ad_rule::admin; }
    if (tmp != "" && !search_uss(tmp)) { create_user(tmp, ru, pr); }
}
void MainWindow::on_user_edit_but_rejected()
{
    int i = ui->user_box_2->currentIndex();
    if (i != ui->user_box->currentIndex()) {
        delete_user(i);
    }
}


void MainWindow::on_object_box_currentIndexChanged(int index)
{
    int i = ui->user_box_2->currentIndex();
    if (i >= 0)
    {
        ui->rights_box->setCurrentIndex(P[i][index+1]);
        ui->privilobjs_box->setCurrentIndex(objs[index].privilobjs);
    }

}
void MainWindow::on_user_box_2_currentIndexChanged(int index)
{
    int j = ui->object_box->currentIndex();
    if (j >= 0)
    {
        ui->rights_box->setCurrentIndex(P[index][j+1]);
        ui->priviluss_box->setCurrentIndex(uss[index].priviluss);
    }
    if (P[index][0] == ad_rule::admin)
    {
        ui->rights_box->setEnabled(false);
        ui->priviluss_box->setEnabled(false);
    } else
    {
        ui->rights_box->setEnabled(true);
        ui->priviluss_box->setEnabled(true);
    }
}


void MainWindow::on_privilobjs_box_currentIndexChanged(int index)
{
    objs[ui->object_box->currentIndex()].privilobjs = privil(index);
}
void MainWindow::on_priviluss_box_currentIndexChanged(int index)
{
    uss[ui->user_box_2->currentIndex()].priviluss = privil(index);
}

void MainWindow::on_rights_box_currentIndexChanged(int index)
{
    P[ui->user_box_2->currentIndex()][ui->object_box->currentIndex()+1] = rule(index);
}

void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

