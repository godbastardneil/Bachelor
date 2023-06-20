#include <iostream>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    pid_t pid;
    for (int i = 0; i < 5; i++)
    {
        if ((pid = fork()) < 0)
        {
            return 1;
        } else if (pid == 0) { return 100 + i; }
    }
    int status;
    pid_t waitPid;
    while ((waitPid = wait(&status)) > 0)
    {
        std::cout << "Completed PID: " << waitPid << std::endl;
    }
    return 0;
}
