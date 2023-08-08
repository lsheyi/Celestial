#ifndef ASYNC_LOGGING_H
#define ASYNC_LOGGING_H

#include "noncopyable.h"
#include "Thread.h"
#include "FixedBuffer.h"
#include "LogStream.h"
#include "LogFile.h"


#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

class AsyncLogging
{
public:
    AsyncLogging(const std::string& basename,
                 off_t rollSize,
                 int flushInterval = 3);
    ~AsyncLogging()
    {
        if (running_)
        {
            stop();
        }
    }

    // 前端调用 append 写入日志
    void append(const char* logling, int len);

    void start()
    {
        running_ = true;
        thread_.start();
    }

    void stop()
    {
        running_ = false;
        cond_.notify_one();
        thread_.join();
    }

private:
    using Buffer = FixedBuffer<kLargeBuffer>;
    using BufferVector = std::vector<std::unique_ptr<Buffer>>;
    using BufferPtr = BufferVector::value_type;

    void threadFunc();

    const int flushInterval_;          // 冲刷间隔-3s
    std::atomic<bool> running_;        // 状态-启动
    const std::string basename_;       // LogFile构造参数-名称
    const off_t rollSize_;             // LogFile构造参数-滚动尺寸
    Thread thread_;                    // 后台线程

    BufferPtr currentBuffer_;          // 指向第一块缓存
    BufferPtr nextBuffer_;             // 指向第二块缓存
    BufferVector buffers_;             // 保存所有记录的缓存

    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif // ASYNC_LOGGING_H