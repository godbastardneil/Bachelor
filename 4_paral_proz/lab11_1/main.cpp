#include <iostream>
#include <unistd.h>
#include "semaphore.h"
#include <sys/ipc.h>
#include <sys/msg.h>

#define REQUEST_TYPE 1
#define EXIT 255

// Структура контента сообщения
struct MessageContent {
     int64_t sender; // Process ID отправителя
     int16_t value;  // Изменение семафора
};
// Структура сообщения
struct Message {
     int64_t type;           // Тип сообщения
     MessageContent content; // Информация
};

int main()
{
     key_t key = ftok("../lab11_1/main.cpp", 0);
     if (key >= 0)
     {
         // Создание очереди сообщений P.S. АНАЛОГ shmget()
         int queueID = msgget(key, 0666 | IPC_CREAT);
         if (queueID >= 0)
         {
             semaphore sem;
             bool isStart = true;
             std::cout << "Запуск сервера" << std::endl << std::endl;
             while (isStart)
             {
                 Message msg;
                 // Примитив receive
                 msgrcv(queueID, &msg, sizeof(MessageContent), REQUEST_TYPE, 0);
                 std::cout << "PID Отправителя: " << msg.content.sender << " Значение: " << msg.content.value
                           << " Предыдущее: " << sem.GetCurrentVal() << std::endl;
                 if (msg.content.sender == EXIT)
                 {
                     std::cout << std::endl << "Отсановка сервера" << std::endl;
                     // Удаление очереди сообщений из системы
                     msgctl(queueID, IPC_RMID, nullptr);
                     isStart = false;
                 }
                 else {
                     if (sem.ChangeValSem(msg.content.sender, msg.content.value))
                     {
                         int64_t resp;
                         resp = msg.content.sender;
                         // Копирование польз. смс в очередь сообщений
                         msgsnd(queueID, &resp, 0, 0);
                     }
                     std::cout << " Нынешнее: " << sem.GetCurrentVal() << std::endl;
                 }
             }
         } else { return 2; } // Не удалось получить доступ к очереди сообщений
     } else { return 1; } // Не удалось получить ключ
     return 0;
}
