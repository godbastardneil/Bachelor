#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <vector>
#include <stdint.h>

class semaphore
{
     // Запрос процесса на изменение значения семафора, приводящий к отрицательному значению
     struct NegativeChange {
        int64_t PID; // Process ID
        int16_t value;   // Изменяемое значение
        NegativeChange(int64_t processID, int16_t val) : PID(processID), value(val) {}
     };
     int sem_QueueID; // ID очереди, по которой отправляется ответ
     int16_t sem_CurVal; // Текущее значение семафора
     std::vector<int64_t> sem_WaitList; // Процессы, ожидающие обнуления значения
     std::vector<NegativeChange> sem_NegativeQueue; // Очередь процессов, уменьшающих значение до отрицательного

     // Освобождение процесса
     void FreeProcess(const int64_t id);
     // Обновление очереди процессов, уменьшающих значение до отрицательного
     void UpdateNegativeQueue();
     // Освобождение всех процессов в очереди ожидающих обнуления
     void FreeWaitList();
public:
     semaphore() : sem_CurVal(0) {}
     // Изменение значения семафора
     bool ChangeValSem(int64_t sender, int16_t value);
     // Запрос текущего значения семафора
     int16_t GetCurrentVal();
};

#endif // SEMAPHORE_H
