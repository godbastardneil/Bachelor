#ifndef CLASSSEMAPHORE_H
#define CLASSSEMAPHORE_H

#include <sys/sem.h>

// Класс для семафоров
class ClassSemaphore
{
int cs_ID;

public:
    ClassSemaphore(int ID) : cs_ID(ID) {}
    // Инициализация семафора
    int Init(short value)
    {
        if (value != 0)
        {
            sembuf buffer;
            buffer.sem_op = value;
            buffer.sem_num = 0;
            buffer.sem_flg = 0;
            return semop(cs_ID, &buffer, 1);
        }
        return -1;
    }
    // Ожидание второй программы (-1)
    int Wait()
    {
        sembuf buffer;
        buffer.sem_num = 0;
        buffer.sem_op = 0;
        buffer.sem_flg = 0;
        return semop(cs_ID, &buffer, 1);
    }
};
#endif // CLASSSEMAPHORE_H
