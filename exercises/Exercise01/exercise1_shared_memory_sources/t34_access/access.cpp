#include <iostream>
#include <thread>
#include <mutex>

int A[100]; /* global variable */

void access_one(int tid)
{
    A[tid] = rand();
}

void access_two(int tid)
{
    A[tid % 10] = rand();
}

void access_three(int tid)
{
    A[rand() % 100] = tid;
}


int main()
{
    // start 100 threads
    std::thread t[100];
    for (int i = 0; i < 100; i++) {
        t[i] = std::thread(access_one, i);
        //t[i] = std::thread(access_two, i);
        //t[i] = std::thread(access_three, i);
    }

    for (int i = 0; i < 100; i++) {
        t[i].join();
    }

    return 0;
}
