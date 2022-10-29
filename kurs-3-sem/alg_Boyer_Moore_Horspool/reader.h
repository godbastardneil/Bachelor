#ifndef READER_H
#define READER_H

#include <fstream>
#include <QString>

class reader
{

public:
    reader() {}

    QString get_text () { return text; }
    int get_code () { return code; }

    bool read_text(const QString &fname)
    {
        text.clear();
        std::ifstream in (fname.toStdString().data(), std::ios::binary);
        if (in) {
            std::string block;
            while (getline(in, block)) {
                for (char &i: block) { i ^= code; }
                text += QString::fromStdString(block);
            }
        } else { return 0; }
        in.close();
        return 1;
    }

private:
    const int code = 0xAABBC53; // ключ
    QString text; // текст, который будут выводить

    reader(const reader &)  = delete;
    reader(const reader &&) = delete;
    reader& operator=(const reader &)  = delete;
    reader& operator=(const reader &&) = delete;
};

#endif // READER_H
