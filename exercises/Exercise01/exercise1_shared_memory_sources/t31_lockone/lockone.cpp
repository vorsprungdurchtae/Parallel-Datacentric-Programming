#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

bool flag[2] = {false, false}; // global array

void lock(int i) {
    int j = (i + 1) % 2; // calculates the other thread id (0 -> 1, 1 -> 0)
    flag[i] = true;
    while (flag[j]) {};
}

void unlock(int i) {
    flag[i] = false;
}


int main() {
    // first thread gets integer id 0
    int id = 0;
    std::thread t0([id]{
            lock(id);
            std::cout << "Thread 0 is in first critical region" << std::endl;
            unlock(id);
            lock(id);
            std::cout << "Thread 0 is in second critical region" << std::endl;
            unlock(id);
    });
    // second thread gets integer id 1
    id = 1;
    std::thread t1([id]{
            lock(id);
            std::cout << "Thread 1 is in critical region" << std::endl;
            unlock(id);
    });

    t0.join();
    t1.join();

    return 0;
}





