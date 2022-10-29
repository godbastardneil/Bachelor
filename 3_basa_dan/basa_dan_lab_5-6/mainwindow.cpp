#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");

    qvs.push_back({"dealdate", "idProduct", "kolvo", "idCustomer", "isOpt"});
    qvs.push_back({"phone", "name", "address"});
    qvs.push_back({"title", "optprice", "rozprice", "description"});

    tdb = new QSqlTableModel(this);

    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());

    ui->tableView->setModel(tdb);

    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    tdb->clear();
    if (index == 0)
    {
        tdb->setTable("deal");
        tdb->setHeaderData(0, Qt::Horizontal, "idDeal");
    } else if(index == 1)
    {
        tdb->setTable("customer");
        tdb->setHeaderData(0, Qt::Horizontal, "idCustomer");
    } else if(index == 2)
    {
        tdb->setTable("product");
        tdb->setHeaderData(0, Qt::Horizontal, "idProduct");
    }
    tdb->select(); // Делаем выборку данных из таблицы
}

void MainWindow::insert(QSqlQuery &qdb, const QVector<QVector<QString>> &qvs, const QVector<QString> &data, const int &j)
{
    QVector<QString> qs = qvs[j];
    QString table = "INSERT INTO ", what = "VALUES (";
    if (j == 0)
    {
        table += "deal(";
    } else if(j == 1)
    {
        table += "customer(";
    } else if(j == 2) { table += "product("; }

    for (int i=0; i<qs.size(); ++i)
    {
        table += qs[i] + ", ";
        what += ":" + qs[i] + ", ";
    }
    table.remove(table.size()-2, table.size());
    what.remove(what.size()-2, what.size());

    qdb.prepare(table + ") " + what + ")");

    for (int i=0; i<qs.size(); ++i)
    {
        qdb.bindValue(":" + qs[i], data[i]); // :dealdate, 10.12.20
    }

//    if (index == 1)
//    {
//        qdb.prepare("INSERT INTO deal(dealdate, idProduct, kolvo, idCustomer, isOpt) Values(:dealdate, :idProduct, :kolvo, :idCustomer, :isOpt");

//        qdb.bindValue(":dealdate", "10.1202"); // :dealdate, 10.12.20
//        qdb.bindValue(":idProduct", 5); // :dealdate, 10.12.20
//        qdb.bindValue(":kolvo", 6); // :dealdate, 10.12.20
//    }
}

void MainWindow::on_input_clicked()
{
    QSqlQuery qdb;
    qdb.exec("PRAGMA foreign_keys = ON;");

    QVector<QString> data;
    if (ui->tabWidget->currentIndex() == 0)
    {
        data.push_back(ui->date_input->text());
        data.push_back(ui->product_input->text());
        data.push_back(QString::number(ui->kolvo_input->value()));
        data.push_back(ui->customer_input->text());
        data.push_back(QString::number(ui->isopt_input->isTristate()));

        ui->date_input->setDate(QDate(1, 1, 2000));
        ui->product_input->setText("");
        ui->kolvo_input->setValue(1);
        ui->customer_input->setText("");
        ui->isopt_input->setTristate(0);
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        data.push_back(ui->phone_input->text());
        data.push_back(ui->name_input->text());
        data.push_back(ui->address_input->text());

        ui->phone_input->setText("");
        ui->name_input->setText("");
        ui->address_input->setText("");
    } else if (ui->tabWidget->currentIndex() == 2)
    {
        data.push_back(ui->title_input->text());
        data.push_back(QString::number(ui->optprise_input->value()));
        data.push_back(QString::number(ui->rozprise_input->value()));
        data.push_back(ui->descr_input->text());

        ui->title_input->setText("");
        ui->optprise_input->setValue(0);
        ui->rozprise_input->setValue(0);
        ui->descr_input->setText("");
    }

    insert(qdb, qvs, data, ui->tabWidget->currentIndex());
    if(!qdb.exec())
    {
        QMessageBox::warning(this, "Ошибка", qdb.lastError().text());
    } else { tdb->select(); }
}
