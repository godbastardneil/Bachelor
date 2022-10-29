#include <iostream>

#include <unistd.h>
#include <array>

using namespace std;

int _parent(const int fd[], const string& str)
{
    close(fd[0]);

    int size = write(fd[1], str.c_str(), str.size());

    if(size != str.size())
    {
        /* Если записалось меньшее количество байт, сообщаем об ошибке */
        cout << ("write - Can\'t write all string\n");
        return -1;
    }

    if(size != str.size())
    {
        /* Если записалось меньшее количество байт, сообщаем об ошибке */
        cout << ("write - Can\'t write all string\n");
        return -1;
    }

    if(close(fd[1]) < 0)
    {
        cout << ("write - Can\'t close file\n");
        return -1;
    }

    return 0;
}
int _read(const int fd[], string& str)
{
    close(fd[1]);

    char tmp[1];
    int size;

    size = read(fd[0], tmp, 1);
    while (size > 0)
    {
        str += tmp[0];
        size = read(fd[0], tmp, 1);
    }

    if(close(fd[0]) == -1)
    {
        cout << ("read - Can\'t close file\n");
        return -1;
    }

    return 0;
}


int main()
{
    int par_fd[2], cil_fd[2], result;
    size_t size;
    string par_str = "Hello from par!";
    string cil_str = "Hello from cil!";


    /* Попытаемся создать pipe */
    if(pipe(par_fd) < 0)
    {
        /* Если создать pipe не удалось, печатаем об этом сообщение и прекращаем работу */
        printf("Can\'t create par_pipe\n");
        return -1;
    }
    if(pipe(cil_fd) < 0)
    {
        /* Если создать pipe не удалось, печатаем об этом сообщение и прекращаем работу */
        printf("Can\'t create cil_pipe\n");
        return -1;
    }


    /* Порождаем новый процесс */
    result = fork();

    if(result < 0)
    {
        /* Если создать процесс не удалось, сообщаем об этом и завершаем работу */
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0)
    {
        _parent(par_fd, par_str);
        string res_par_str;
        _read(cil_fd, res_par_str);
        cout << ("Parent exit - ") << res_par_str << endl;
    } else
    {
        _parent(cil_fd, cil_str);
        string res_cil_str;
        _read(par_fd, res_cil_str);
        cout << ("Children exit - ") << res_cil_str << endl;
    }

    return 0;
}
