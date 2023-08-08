#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <atomic>
#include "noncopyable.h"

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;
    
    explicit Thread(ThreadFunc, const std::string &name = std::string());
    ~Thread();

    void start(); 
    void join();  

    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }
    bool started() const { return started_; }
    static int numCreated() { return numCreated_; }

private:
    void setDefaultName();  // 设置线程名

private:
    pid_t tid_;                             // 线程tid
    std::string name_;                      // 线程名
    static std::atomic_int32_t numCreated_; // 线程索引
    std::shared_ptr<std::thread> thread_;   // 线程
    ThreadFunc func_;                       // 回调函数 
    
    bool started_;                          // 是否启动线程
    bool joined_;                           // 是否等待该线程
};

#endif // THREAD_H