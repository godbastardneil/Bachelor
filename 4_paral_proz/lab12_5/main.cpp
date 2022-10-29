#include <signal.h>
#include <stdio.h>
#include <iostream>

/* Функция my_handler - пользовательский обработчик сигнала */
void my_handler(int nsig)
{
    // задание 5
    std::cout << "Receive signal " << nsig << ", CTRL-C pressed\n";

    // задание 6
/*
    std::cout << "Receive signal " << nsig;
    if (nsig == SIGINT)
    {
        std::cout << ", CTRL-C pressed\n";
    } else if (nsig == SIGQUIT) { std::cout << ", CTRL-4 pressed\n"; }
*/
}

int main(void)
{
    /* Выставляем реакцию процесса на сигнал SIGINT */

    signal(SIGINT, my_handler);
    //signal(SIGQUIT, my_handler); // задание 6

    /*Начиная с этого места, процесс будет печатать сообщение о возникновении сигнала SIGINT */

    while(1);
    return 0;
}
