add_executable(MyTest test.cpp)
target_link_libraries(MyTest gtest gtest_main pthread)

add_test(NAME SampleTest COMMAND MyTest)
