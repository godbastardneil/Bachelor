#ifndef READER_H
#define READER_H

#include <QString>

#include <fstream>

class reader
{

public:
    reader() {}

    static int get_code () { return 0xAABBC53; } // получить код кодировки

    static QString get_warning () { return "error"; } // получить слово ошибки

    static QString read_text(const QString &fname) // чтение из файла
    {
        QString text;
        std::ifstream in (fname.toStdString().data(), std::ios::binary);
        if (in.is_open())
        {
            std::string block;
            while (getline(in, block))
            {
                for (char &i: block) { i ^= 0xAABBC53; }
                text += QString::fromStdString(block);
            }
        } else { text = "error"; }
        in.close();
        return text;
    }

private:

    reader(const reader &)  = delete;
    reader(const reader &&) = delete;
    reader& operator=(const reader &)  = delete;
    reader& operator=(const reader &&) = delete;
};

#endif // READER_H
