#include "semaphore.h"

#include <algorithm>
#include <iostream>
#include <sys/msg.h>

void semaphore::FreeProcess(const int64_t id)
{
     std::cout << "Освобождение процесса: " << id << std::endl;
     msgsnd(sem_QueueID, &id, 0, 0);
}
void semaphore::UpdateNegativeQueue()
{
     for (size_t idx = 0; sem_CurVal != 0 && idx < sem_NegativeQueue.size(); idx++)
     {
         if (sem_NegativeQueue[idx].value <= sem_CurVal)
         {
             FreeProcess(sem_NegativeQueue[idx].PID);
             sem_CurVal -= sem_NegativeQueue[idx].value;
             sem_NegativeQueue.erase(sem_NegativeQueue.begin() + int(idx));
             idx--;
         }
     }
}
void semaphore::FreeWaitList()
{
    std::for_each(sem_WaitList.begin(), sem_WaitList.end(), [this](const int64_t id) { FreeProcess(id); });
    sem_WaitList.clear();
}
bool semaphore::ChangeValSem(int64_t sender, int16_t value) {
     bool isFree = true;
     if (value == 0 && sem_CurVal != 0) {
         sem_WaitList.push_back(sender);
         isFree = false;
     }
     else {
         if (value > 0) {
            sem_CurVal += value;
            UpdateNegativeQueue();
         }
         else if (sem_CurVal + value >= 0)
            sem_CurVal += value;
         else {
            sem_NegativeQueue.push_back(NegativeChange(sender, -value));
            isFree = false;
         }
         if (sem_CurVal == 0)
            FreeWaitList();
     }
     return isFree;
}
int16_t semaphore::GetCurrentVal()
{
    return sem_CurVal;
}
