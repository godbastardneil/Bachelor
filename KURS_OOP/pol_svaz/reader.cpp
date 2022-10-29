#include "reader.h"

bool reader::read_text(const QString &fname)
{
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
