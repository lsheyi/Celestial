#include "Timestamp.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    auto now = Timestamp::now();
    std::cout << now.toFormattedString() << " from " << now.microSecondsSinceEpoch() << std::endl;
    auto invalid = Timestamp::invalid();
    std::cout << invalid.toFormattedString() << " from " << invalid.microSecondsSinceEpoch() << std::endl;

    return 0;
}
