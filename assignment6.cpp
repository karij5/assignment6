#include <iostream>
#include <pthread.h>
#include <mutex>
#include <unistd.h>

std::mutex mtx;
int sharedVariable = 0;

void* thread1Function(void* arg) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        sharedVariable = i;
        std::cout << "Thread 1 writing: " << sharedVariable << std::endl;
        mtx.unlock();
        sleep(1);
    }
    return nullptr;
}

void* thread2Function(void* arg) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        std::cout << "Thread 2 reading: " << sharedVariable << std::endl;
        mtx.unlock();
        sleep(1);
    }
    return nullptr;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, nullptr, thread1Function, nullptr);
    pthread_create(&thread2, nullptr, thread2Function, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    return 0;
}