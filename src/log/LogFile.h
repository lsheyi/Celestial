#ifndef LOG_FILE_H
#define LOG_FILE_H

#include "FileUtil.h"

#include <mutex>
#include <memory>

class LogFile
{
public:
    LogFile(const std::string& basename,
            off_t rollSize,
            int flushInterval = 3,
            int checkEveryN = 1024);
    ~LogFile();

    void append(const char* data, int len);   // 调用appendInlock写入缓冲区 (满足条件滚动日志)
    void flush();    // 数据落盘
    bool rollFile(); // 滚动日志

private:
    // 文件名 basename.YMDHMS.log 
    static std::string getLogFileName(const std::string& basename, time_t* now);
    void appendInLock(const char* data, int len);

private:
    const std::string basename_;

    //日志回滚条件
    const off_t rollSize_;           // 滚动条件-日志大小 off_t - long int
    time_t startOfPeriod_;           

    const int flushInterval_;        // 数据落盘间隔 
    const int checkEveryN_;          // 次数
    int count_;                      // 计算次数
    time_t lastRoll_;
    time_t lastFlush_;

    std::unique_ptr<FileUtil> file_;
    std::unique_ptr<std::mutex> mutex_;

    const static int kRollPerSeconds_ = 60*60*24;
};

#endif // LOG_FILE_H