#include "Logging.h"

int main(int argc, char const *argv[])
{
    LOG_TRACE << "log trace" << 1;
    LOG_DEBUG << "log debug" << 2;
    LOG_INFO << "log info" << 3;
    LOG_WARN << "log warn" << 4;
    // LOG_ERROR << "log error" << 5;
    // LOG_FATAL << 6;
    return 0;
}
