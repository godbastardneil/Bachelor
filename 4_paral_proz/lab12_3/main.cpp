#include <signal.h>

int main(void)
{
    /* Выставляем реакцию процесса на сигнал SIGINT на игнорирование */

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN); // 4 задание

    /*Начиная с этого места, процесс будет игнорировать возникновение сигнала SIGINT */

    while(1);
    return 0;
}
