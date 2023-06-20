#include "widget.h"
#include "./ui_widget.h"
#include <QTimer>

#include <algorithm>

//#include "../utils.hpp"

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , renderTimer(std::make_unique<QTimer>())
{
    ui->setupUi(this);
    this->setMaximumSize(this->widgetSize, this->widgetSize);
    this->setMinimumSize(this->widgetSize, this->widgetSize);

    const auto buttonOffset = 10;
    ui->pushButton->setGeometry(this->widgetSize - this->buttonW - buttonOffset,
                                this->widgetSize - this->buttonH - buttonOffset,
                                this->buttonW,
                                this->buttonH);

    ui->tableWidget->setRowCount(this->cellCount);
    ui->tableWidget->setColumnCount(this->cellCount);

    for (int32_t i = 0; i < this->cellCount; ++i)
    {
        for (int32_t j = 0; j < this->cellCount; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem());
        }
    }

    connect(renderTimer.get(), &QTimer::timeout, this, &Widget::doOneStep);
}

Widget::~Widget()
{
    delete ui;
}

Widget::State Widget::lifeRules(Potential p,
                                State state
                                ) const
{
    if (p == 3)
    {
        return 1;
    }

    if (p == 2)
    {
        return state;
    }

    return 0;
}

Widget::Potential Widget::calcPotential(const LifeTable &table,
                                        int32_t i,
                                        int32_t j
                                        ) const
{
    Potential p = 0;

    /*for (int i = 0; i < 50000; ++i)
    {
        p = sqrt(p) * p * 0.001;
        p += 1;
    }*/

    for (int32_t x = i-1; x <= i+1; ++x)
    {
        for (int32_t y = j-1; y <= j+1; ++y)
        {
            // Рассматриваем пограничные случаи
            if (    x < 0 || y < 0
                    || x >= this->cellCount
                    || y >= this->cellCount
                    || ((x == i) && (y == j))    )
            {
                continue;
            }

            if (table[size_t(x)][size_t(y)])
            {
                ++p;
            }
        }
    }

    return p;
}

Widget::LifeTable Widget::getInitTable() const
{
    LifeTable table(cellCount);
    for (int32_t i = 0; i < cellCount; ++i)
    {
        const auto si = size_t(i);
        table[si].resize(cellCount);
        for (int32_t j = 0; j < cellCount; ++j)
        {
            const auto sj = size_t(j);

            bool isSelected = ui->tableWidget->item(i, j)->isSelected();

            if (isSelected)
            {
                table[si][sj] = 1;
            }
        }
    }
    return table;
}

Widget::LifeTable Widget::seqCalcNewTable(const LifeTable &oldTable) const
{
    LifeTable newTable(cellCount);

    for (int32_t i = 0; i < cellCount; ++i)
    {
        const auto si = size_t(i);
        newTable[si].resize(cellCount);
        for (int32_t j = 0; j < cellCount; ++j)
        {
            const auto sj = size_t(j);
            const Potential p = calcPotential(oldTable, i, j);
            newTable[si][sj] = lifeRules(p, oldTable[si][sj]);
        }
    }

    return newTable;
}

Widget::LifeTable Widget::parCalcNewTableByRow(const LifeTable &oldTable) const
{
    LifeTable newTable(cellCount);

    auto func = [&](const int32_t i)
    {
        const auto si = size_t(i);
        newTable[si].resize(cellCount);
        for (int32_t j = 0; j < cellCount; ++j)
        {
            const auto sj = size_t(j);
            const Potential p = calcPotential(oldTable, i, j);
            newTable[si][sj] = lifeRules(p, oldTable[si][sj]);
        }
    };

    for (int32_t i = 0; i < cellCount; ++i)
    {
        std::function<void()> f {[i, &func](){ func(i); }};
        QThreadPool::globalInstance()->start(f);
    }

    QThreadPool::globalInstance()->waitForDone();
    QThreadPool::globalInstance()->clear();

    return newTable;
}

Widget::LifeTable Widget::parCalcNewTableByColumn(const LifeTable &oldTable) const
{
    LifeTable newTable(cellCount);

    for (size_t i = 0; i < cellCount; ++i)
    {
        newTable[i].resize(cellCount);
    }

    auto func = [&](const int32_t j)
    {
        const auto sj = size_t(j);
        for (int32_t i = 0; i < cellCount; ++i)
        {
            const auto si = size_t(i);
            const Potential p = calcPotential(oldTable, i, j);
            newTable[si][sj] = lifeRules(p, oldTable[si][sj]);
        }
    };

    for (int32_t j = 0; j < cellCount; ++j)
    {
        std::function<void()> f {[j, &func](){ func(j); }};
        QThreadPool::globalInstance()->start(f);
    }

    QThreadPool::globalInstance()->waitForDone();
    QThreadPool::globalInstance()->clear();

    return newTable;
}

void Widget::renderLifeTable(const LifeTable &table) const
{
    ui->tableWidget->clearSelection();
    for (int32_t i = 0; i < cellCount; ++i)
    {
        const auto si = size_t(i);
        for (int32_t j = 0; j < cellCount; ++j)
        {
            const auto sj = size_t(j);

            if (table[si][sj])
            {
                ui->tableWidget->item(i, j)->setSelected(true);
            }
        }
    }
}

void Widget::doOneStep()
{
    //    auto res = timeBenchmarkForMemberFunc
    //            <d_milliseconds, Widget::LifeTable>
    //            (&Widget::seqCalcNewTable, this, this->latestTable);

    /*auto res = timeBenchmarkForMemberFunc
            <d_milliseconds, Widget::LifeTable>
            (&Widget::parCalcNewTableByRow, this, this->latestTable);

    qDebug() << res.first;
    this->latestTable = res.second;
    this->renderLifeTable(this->latestTable);*/
}

void Widget::start()
{
    this->latestTable = this->getInitTable();
    renderTimer->start(this->oneStepTime);
}

void Widget::stop()
{
    renderTimer->stop();
    ui->tableWidget->clearSelection();
}

void Widget::on_pushButton_clicked()
{
    if (!isStarted)
    {
        this->start();
        isStarted = true;
        ui->pushButton->setText("Отмена");
    }
    else
    {
        this->stop();
        isStarted = false;
        ui->pushButton->setText("Старт");
    }
}
