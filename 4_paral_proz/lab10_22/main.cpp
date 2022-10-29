#include <iostream>
#include <string>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    const std::string path = "../lab10_21/main.cpp";
    bool isNewArray = false;
    size_t memSize = 3 * sizeof(uint32_t);
    key_t key = ftok(path.c_str(), 0);
    if (key >= 0)
    {
        int semId = semget(key, 1, 0666 | IPC_CREAT);
        if (semId >= 0)
        {
            sembuf buffer;
            buffer.sem_num = 0;
            buffer.sem_op = 0;
            buffer.sem_flg = 0;

            if (semop(semId, &buffer, 1) >= 0)
            {
                buffer.sem_op = 1;
                buffer.sem_num = 0;
                buffer.sem_flg = 0;
                semop(semId, &buffer, 1);

                int memoryID = shmget(key, memSize, 0666 | IPC_CREAT | IPC_EXCL);
                if (memoryID < 0)
                {
                    memoryID = shmget(key, memSize, 0);
                    if (memoryID < 0)
                    {
                        buffer.sem_op = -1;
                        buffer.sem_num = 0;
                        buffer.sem_flg = 0;
                        semop(semId, &buffer, 1);
                        return 4;
                    }
                }

                uint32_t* CountOfLaunches = (uint32_t*)shmat(memoryID, nullptr, 0);
                CountOfLaunches[1]++;
                CountOfLaunches[2]++;

                std::cout << "Количество запусков программы №1 - " << CountOfLaunches[0] << std::endl
                            << "Количество запусков программы №2 - " << CountOfLaunches[1] << std::endl
                            << "Общее количество запусков - " << CountOfLaunches[2] << std::endl;
                sleep(4);

                buffer.sem_op = -1;
                buffer.sem_num = 0;
                buffer.sem_flg = 0;
                semop(semId, &buffer, 1);

            } else { return 3; }
        } else { return 2; }
    } else { return 1; }
    return 0;
}
