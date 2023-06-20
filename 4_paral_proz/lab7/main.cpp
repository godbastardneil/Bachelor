#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid = fork();
    if(pid == -1) /* ошибка */
    {
        cout << "при вызове fork() возникла ошибка: "; /*произошла ошибка*/
        exit(EXIT_FAILURE); /*выход из родительского процесса*/
    } else if (pid == 0) /* ребёнок */
    {
        cout << "Процесс-Ребёнок." << endl;
        cout << "\tРеб - Мой PID -- " << getpid() << endl;
        cout << "\tРеб - PID моего родителя -- " << getppid() << endl;

        cout << "\tРеб - Параметры запуска argc=" << argc << ": " << endl;
        for (int i = 0; i < argc; ++i) { cout << "\t\t" << argv[i] <<  endl; }
        cout << endl;

        cout << "\tЧто назодится в папке ../lab7: " << endl;
        execle("/bin/ls", "/bin/ls", "../lab7", 0, envp);

    } else /* родитель */
    {
        cout << "Процесс-Родитель." << endl;
        cout << "\tРод - Мой PID -- " << getpid() << endl;
        cout << "\tРод - PID моего ребёнка -- " << pid << endl;

        cout << "\tРод - Параметры окружающей среды: " << endl;
        char **tmp = envp;
        while (*tmp != NULL) { cout << "\t\t" << *(tmp++) <<  endl; }
        cout << endl;

        cout << "Род - Выход!" << endl;

        sleep(3);

        cout << "Род - Выход!" << endl;
        exit(EXIT_SUCCESS);
    }

    return 0;
}
