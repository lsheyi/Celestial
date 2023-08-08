#include <iostream>

#include "Thread.h"
#include "CurrentThread.h"


int main(int argc, char const *argv[])
{
    auto dwim = [&](){
        std::cout << CurrentThread::tid() << std::endl; 
    };
    Thread t(dwim);
    t.start();
    t.join();
    std::cout << "name:" << t.name() << " tid:" << t.tid() << std::endl;

    return 0;
}
