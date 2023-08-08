#include "ThreadPool.h"
#include "CurrentThread.h"

#include <unistd.h>
#include <iostream>
#include <chrono>

int main(int argc, char const *argv[])
{
    ThreadPool tpool("pool");
    tpool.setThreadSize(4);

    auto dwim = []() {
        std::cout << "Thread" <<CurrentThread::tid() << " start" << std::endl;
    };

    auto plus = []() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread" <<CurrentThread::tid() << std::endl;
    };

    tpool.setThreadInitCallback(dwim);    
    tpool.start();

    for (int i = 0; i < 10; ++i) {
        tpool.add(plus);
    }
    tpool.stop();
    std::cout << "end" << std::endl;
    return 0;
}
