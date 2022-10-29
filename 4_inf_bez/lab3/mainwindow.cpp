#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_user("admin_1", rule::admin);
    create_user("admin_2", rule::admin);
    create_user("user_1", rule::user);
    create_user("user_2", rule::user);
    create_user("user_3", rule::user);

    create_object("object_1", "object_1_text");
    create_object("object_2", "object_2_text");
    create_object("object_3", "object_3_text");
    create_object("object_4", "object_4_text");
    create_object("object_5", "object_5_text");

    rule i = P[0][0];

    ui->rights_box->addItem("Нет прав");
    ui->rights_box->addItem("Чтение");
    ui->rights_box->addItem("Модификация");

    P[0][0] = i;
    ui->rights_box->setCurrentIndex(P[0][0]);
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
void MainWindow::view_text(const int &i, const int &j)
{
    if (i < uss.size() && j < objs.size())
    {
        ui->in_object->setText(objs[j].content);
        if (P[i][j+1] == rule::no)
        {
            ui->in_object->clear();
        } else if (P[i][j+1] == rule::read)
        {
            ui->in_object->setReadOnly(true);
        } else { ui->in_object->setReadOnly(false); }
    }
}

void MainWindow::create_user(const QString &name, const rule &role)
{
    uss.emplace_back(name);
    P.emplace_back(rules(objs.size()+1, role));


    ui->user_box->addItem(name);
    ui->user_box_2->addItem(name);
}
void MainWindow::create_object(const QString &name, const QString &content)
{
    objs.emplace_back(object{name, content});

    for (int i=0; i<P.size(); ++i)
    {
        P[i].emplace_back(P[i][0]);
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
    if (i >= 0) { view_text(i, currentRow); }
}
void MainWindow::on_user_box_currentIndexChanged(int index)
{
    int j = ui->object_list->currentRow();
    if (j >= 0) { view_text(index, j); }
    if (P[index][0] == rule::admin) {
        ui->admin_button->setEnabled(true);
    } else { ui->admin_button->setEnabled(false); }
}

void MainWindow::on_in_object_textChanged()
{
    if (P[ui->user_box->currentIndex()][ui->object_list->currentRow()+1] == rule::change) {
        objs[ui->object_list->currentRow()].content = ui->in_object->toPlainText();
    }
}

void MainWindow::on_admin_button_clicked()
{
    int i = ui->user_box->currentIndex();
    qDebug() << i << P[i][0];
    if (P[i][0] == rule::admin) {
        ui->stackedWidget->setCurrentIndex(1);
    }
}



void MainWindow::on_object_edit_but_accepted()
{
    QString tmp = ui->object_init->text();
    if (tmp != "" && !search_obj(tmp))
    {
        create_object(tmp, "");
    }
}
void MainWindow::on_object_edit_but_rejected()
{
    delete_object(ui->object_box->currentIndex());
}


void MainWindow::on_user_edit_but_accepted()
{
    QString tmp = ui->user_init->text();
    rule ru = rule::user;
    if (ui->admin_box->isChecked()) { ru = rule::admin; }
    if (tmp != "" && uss.indexOf(tmp) == -1) { create_user(tmp, ru); }
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
    if (i >= 0) { ui->rights_box->setCurrentIndex(P[i][index+1]); }

}
void MainWindow::on_user_box_2_currentIndexChanged(int index)
{
    int j = ui->object_box->currentIndex();
    if (j >= 0) { ui->rights_box->setCurrentIndex(P[index][j+1]); }
    if (P[index][0] == rule::admin)
    {
        ui->rights_box->setEnabled(false);
    } else { ui->rights_box->setEnabled(true); }
}

void MainWindow::on_rights_box_currentIndexChanged(int index)
{
    P[ui->user_box_2->currentIndex()][ui->object_box->currentIndex()+1] = rule(index);
}

void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

