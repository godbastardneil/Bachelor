#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define REQUEST_TYPE 1
#define EXIT 255

// Структура контента сообщения
struct MessageContent {
    int64_t sender; // PID отправителя
    int16_t value; // Изименение семафора
};
// Структура сообщения
struct Message {
    int64_t type; // Тип сообщения
    MessageContent content; // Информация
};

int main() {
    key_t key = ftok("../lab11_1/main.cpp", 0);
    if (key >= 0)
    {
        int queueID = msgget(key, 0666 | IPC_CREAT);
        if (queueID >= 0)
        {
            Message msg;
            msg.type = REQUEST_TYPE;
            msg.content.sender = EXIT;
            msg.content.value = 0;
            // Добавляет сообщение в очередь сообщений
            msgsnd(queueID, &msg, sizeof(MessageContent), 0);
            int64_t resp;
            // Считывает сообщение из очереди, связанной с идентификатором очереди сообщений, заданным msqid, и помещает его в определяемый пользователем буфер, на который указывает msgp.
            msgrcv(queueID, &resp, 0, getpid(), 0);
        } else { return 2; } // Не удалось получить доступ к очереди сообщений
    } else { return 1; } // Не удалось получить ключ
    return 0;
}
