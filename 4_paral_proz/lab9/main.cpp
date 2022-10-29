#include <iostream>
#include <atomic>
#include <pthread.h>
#include <stdio.h>
#include <mutex>

std::atomic<int> a = 0;
std::mutex mtx;

void *Task(void *arg)
{
    mtx.lock();

    std::cout << "Thread: " << pthread_self()
              << ", Calculation result = " << ++a << std::endl;

    mtx.unlock();

    return nullptr;
}

int main()
{
    pthread_t first_thr, second_thr;
    int first_result, second_result;

    first_result = pthread_create(&first_thr, nullptr, Task, nullptr);
    second_result = pthread_create(&second_thr, nullptr, Task, nullptr);

    if (first_result != 0 || second_result)
    {
        std::cout << "Error on thread create, return value: " << first_result
                    << ", " << second_result << std::endl;
        return 1;
    }

    mtx.lock();

    std::cout << "Thread created, thid = " << pthread_self() << std::endl;
    std::cout << "Thread: " << pthread_self()
              << ", Calculation result = " << a << std::endl;

    mtx.unlock();

    pthread_join(first_thr, (void **)nullptr);
    pthread_join(second_thr, (void **)nullptr);

    return 0;
}
