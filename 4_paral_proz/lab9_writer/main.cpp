#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/shm.h>


int main()
{
    const std::string path = "../lab9_writer/main.cpp";
    std::string str = "Hello from lab9_writer";

    key_t key = ftok(path.c_str(), 0);
    if (key >= 0) {
        int SMemoryID = shmget(key, str.size(), 0666 | IPC_CREAT | IPC_EXCL);

        if (errno == EEXIST) { SMemoryID = shmget(key, str.size(), 0); }

        if (SMemoryID >= 0) {
            char* Memory = (char*)shmat(SMemoryID, nullptr, 0);
            memcpy(Memory, str.c_str(), str.size());

            shmdt(Memory);
        } else { return 2;}
    } else { return 3; }

    return 0;
}
