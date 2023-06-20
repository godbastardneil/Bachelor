#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();

    ui->pushButton->setText(start);

    cell_size = ui->tableWidget->horizontalHeader()->defaultSectionSize();
    cell_in_height = ui->tableWidget->height()/cell_size;
    cell_in_width = ui->tableWidget->width()/cell_size;
    qDebug() << cell_size << cell_in_height << cell_in_width;

    ui->tableWidget->setRowCount(cell_in_height);
    ui->tableWidget->setColumnCount(cell_in_width);

    table.resize(cell_in_height);
    for (size_t i=0; i<cell_in_height; ++i)
    {
        for (size_t j=0; j<cell_in_width; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem());
        }
        table[i].resize(cell_in_width);
    }

    connect(timer, &QTimer::timeout, this, &MainWindow::repaint);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_pushButton_clicked()
{
    if (ui->pushButton->text() == start)
    {
        ui->pushButton->setText(end);
        start_game();
    }
    else
    {
        end_game();
        ui->pushButton->setText(start);
    }
}



bool MainWindow::lifeRules(const size_t &p, const bool &state)
{
    if (p == Potential::alive)
    {
        return true;
    } else if (p == Potential::live)
    {
        return state;
    } else { return false; }
}

size_t MainWindow::calcPotential(const size_t &i, const size_t &j)
{
    size_t p = 0;
    for (size_t x=i-1; x<=i+1; ++x)
    {
        for (size_t y=j-1; y<=j+1; ++y)
        {
            if (!(x<0 || y<0 || x>=cell_in_height
                    || y>=cell_in_width || (x==i && y==j)))
            {
                if (table[x][y]) { p++; }
            }
        }
    }
    return p;
}

bool MainWindow::calcState(const size_t &i, const size_t &j)
{
    size_t p = calcPotential(i, j);
    return lifeRules(p, table[i][j]);
}
void MainWindow::calcStates()
{
    LifeTable tableNew = table;

    QTime tmp = QTime::currentTime();

    //posled(tableNew);
    paral_po_strokam(tableNew);
    //paral_po_stolbzam(tableNew);

    def += tmp.msecsTo(QTime::currentTime())/1000.0;
    ++k;

    table = tableNew;
}

void MainWindow::posled(LifeTable &tableNew)
{
    for(size_t i=0; i<cell_in_height; ++i)
    {
        for(size_t j=0; j<cell_in_width; ++j)
        {
            tableNew[i][j] = calcState(i, j);
        }
    }
}
void MainWindow::paral_po_strokam(LifeTable &tableNew)
{
    auto func = [&](const size_t i)
    {
        for(size_t j=0; j<cell_in_width; ++j)
        {
            tableNew[i][j] = calcState(i, j);
        }
    };
    for(size_t i=0; i<cell_in_height; ++i)
    {
        QThreadPool::globalInstance()->start(
            [i, &func]()
            {
                func(i);
            }
        );
    }

    QThreadPool::globalInstance()->waitForDone();
    QThreadPool::globalInstance()->clear();
}
void MainWindow::paral_po_stolbzam(LifeTable &tableNew)
{
    auto func = [&](const size_t j)
    {
        for(size_t i=0; i<cell_in_height; ++i)
        {
            tableNew[i][j] = calcState(i, j);
        }
    };
    for(size_t j=0; j<cell_in_width; ++j)
    {
        QThreadPool::globalInstance()->start(
            [j, &func]()
            {
                func(j);
            }
        );
    }

    QThreadPool::globalInstance()->waitForDone();
    QThreadPool::globalInstance()->clear();
}


void MainWindow::getTable()
{
    LifeTable tableNew = table;
    for (size_t i=0; i<cell_in_height; ++i)
    {
        for(size_t j=0; j<cell_in_width; ++j)
        {
            tableNew[i][j] = ui->tableWidget->item(i, j)->isSelected();
        }
    }

    table = tableNew;
}
void MainWindow::paintTable()
{
    for (size_t i=0; i<cell_in_height; ++i)
    {
        for(size_t j=0; j<cell_in_width; ++j)
        {
            ui->tableWidget->item(i, j)->setSelected(table[i][j]);
        }
    }
}

void MainWindow::repaint()
{
    calcStates();
    paintTable();
}


void MainWindow::start_game()
{
    getTable();

    ct = QTime::currentTime();
    def = 0, k = 0;
    timer->start(step);
}
void MainWindow::end_game()
{
    timer->stop();

    qDebug() << "ct" << ct.msecsTo(QTime::currentTime())/1000.0;
    qDebug() << "def" << def/k;
    def = 0, k = 0;

    ui->tableWidget->clearSelection();
}

