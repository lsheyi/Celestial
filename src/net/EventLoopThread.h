#ifndef EVENT_LOOP_THREAD_H
#define EVENT_LOOP_THREAD_H

#include <functional>
#include <mutex>
#include <condition_variable>
#include "noncopyable.h"
#include "Thread.h"

// one loop per thread
class EventLoop;
class EventLoopThread : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
                    const std::string &name = std::string());
    ~EventLoopThread();

    EventLoop *startLoop(); // 开启线程池

private:
    // EventLoopThread::threadFunc 会创建 EventLoop
    void threadFunc();

    EventLoop *loop_;               // 句柄           
    bool exiting_;                  // 退出
    Thread thread_;                 // 线程
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallback callback_;

};

#endif // EVENT_LOOP_THREAD_H