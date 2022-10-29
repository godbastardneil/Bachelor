#include <iostream>
#include <string>
#include <sys/sem.h>

int main()
{
    const std::string path = "../labb10_11/main.cpp";
    key_t key = ftok(path.c_str(), 0);
    if (key >= 0)
    {
        int shmId = semget(key, 1, 0666 | IPC_CREAT);
        if (shmId >= 0)
        {
            semctl(shmId, 0, SETVAL, 5);
            std::cout << "Значение семафора: " << semctl(shmId, 0, GETVAL) << std::endl;
            sembuf buffer;
            buffer.sem_op = 0;
            buffer.sem_num = 0;
            buffer.sem_flg = 0;
            if (semop(shmId, &buffer, 1) >= 0)
            {
                std::cout << "Конец!" << std::endl;
            } else { return 3; }
        } else { return 2; }
    } else { return 1; }
    return 0;
}
