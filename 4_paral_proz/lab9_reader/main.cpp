#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    const std::string path = "../lab9_writer/main.cpp";
    key_t key = ftok(path.c_str(), 0);
    int SMemoryID = shmget(key, 0, 0);
    if (SMemoryID >= 0)
    {
        char* Memory = (char*)shmat(SMemoryID, nullptr, 0);

        std::cout << "Вывод: " << Memory << std::endl;
        shmctl(SMemoryID, IPC_RMID, nullptr);
    }

    return 0;
}
