#ifndef SHOW_TEXT_H
#define SHOW_TEXT_H

#include <QWidget>
#include <QMessageBox>
#include "reader.h"

namespace Ui { class show_text; }

class show_text : public QWidget
{
    Q_OBJECT

public:
    explicit show_text(QWidget *parent = nullptr);
    ~show_text();
    void write_text(const QString &fname);
    void write_stat(const QString &fname, const std::string &qs);

private:
    Ui::show_text *ui;
    reader writer;

    show_text(const show_text &)  = delete;
    show_text(const show_text &&) = delete;
    show_text& operator=(const show_text &)  = delete;
    show_text& operator=(const show_text &&) = delete;
};

#endif // SHOW_TEXT_H
