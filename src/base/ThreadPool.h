#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "noncopyable.h"
#include "Thread.h"
#include "Logging.h"

#include <deque>
#include <vector>
#include <mutex>
#include <condition_variable>

/**
 * 无界
*/
class ThreadPool : noncopyable
{
public:
    using ThreadFunction = std::function<void()>;

    explicit ThreadPool(const std::string& name = std::string("ThreadPool"));
    ~ThreadPool();

    void start();
    void stop();

    void add(ThreadFunction ThreadFunction);
    
    void setThreadInitCallback(const ThreadFunction& cb) { threadInitCallback_ = cb; }
    void setThreadSize(const int& num) { threadSize_ = num; }
    const std::string& name() const { return name_; }
    size_t queueSize() const;

private:
    bool isFull() const;
    void runInThread();

private:
    std::string name_;                               // 线程池名称
    ThreadFunction threadInitCallback_;              // 线程启动回调函数
    std::vector<std::unique_ptr<Thread>> threads_;   // 池内线程
    size_t threadSize_;                              // 线程数量
    // TODO queue
    std::deque<ThreadFunction> queue_;               // 任务队列
    
    bool running_;                                   // 状态 临界资源
    
    mutable std::mutex mutex_;                       // 互斥量
    std::condition_variable cond_;                   // 条件变量
};

# endif // THREAD_POOL_H
