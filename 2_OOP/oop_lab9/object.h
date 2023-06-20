#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class object
{
    static unsigned int count;        // статическое поле - счетчик
public:
    object();
    virtual ~object();
    static unsigned int Count();   // выдача счетчика
};

#endif // OBJECT_H
