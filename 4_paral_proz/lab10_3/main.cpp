#include <iostream>
#include <string>
#include <sys/sem.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int _parent(int fd[2], sem_t* per_sem, sem_t* cil_sem, const std::string& str, const int &n)
{
    if(write(fd[1], str.c_str(), str.size()) != str.size()) { return 3; }
    close(fd[1]);
    std::cout << "Successful write" << std::endl;

    sem_post(cil_sem);
    sem_wait(per_sem);

    char tmp[n];
    if (read(fd[0], tmp, n) < n) { return 4; }
    close(fd[0]);
    std::cout << "_parent - " << tmp << std::endl;

    return 0;
}
int _child(int fd[2], std::string& str, const int &n)
{
    char tmp[n];
    if (read(fd[0], tmp, n) < n) { return 5; }
    close(fd[0]);
    std::cout << "_child - " << tmp << std::endl;

    if (write(fd[1], str.c_str(), n) != n) { return 6; }
    close(fd[1]);

    return 0;
}

int main()
{
    sem_t* per_sem;
    sem_t* cil_sem;
    int fd[2];
    std::string par_str = "Hello from par!";
    std::string cil_str = "Hello from cil!";

    per_sem = sem_open(par_str.c_str(), O_CREAT | O_EXCL, 0666, 0);
    cil_sem = sem_open(cil_str.c_str(), O_CREAT | O_EXCL, 0666, 0);

    if (pipe(fd) < 0) { return 1; }

    int res = fork();
    if (res > 0) {
        sem_wait(cil_sem);
        sem_unlink(cil_str.c_str());
        sem_close(cil_sem);
        int cil_res = _child(fd, cil_str, par_str.size());
        sem_post(per_sem);
        return cil_res;
    } else if (res == 0){
        int per_res = _parent(fd, per_sem, cil_sem, par_str, cil_str.size());
        sem_unlink(par_str.c_str());
        sem_close(per_sem);
        return per_res;
    } else {
        std::cout << "ERROR ID PROCESS" << std::endl;
        return 2;
    }
    return 0;
}
