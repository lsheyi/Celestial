add_executable(TimestampTest TimestampTest.cc)
target_link_libraries(TimestampTest network pthread)

add_executable(ThreadTest ThreadTest.cc)
target_link_libraries(ThreadTest network pthread)

add_executable(ThreadPoolTest ThreadPoolTest.cc)
target_link_libraries(ThreadPoolTest network pthread)

add_executable(LogTest LogTest.cc)
target_link_libraries(LogTest network pthread)