cmake_minimum_required(VERSION 3.8)
project(omega-tests)
set(CMAKE_CXX_STANDARD 17)

set(TEST_SOURCE_FILES
        test_main.cpp

        test_vector.cpp
        ../vector.cpp
        )

add_executable(omega-tests ${TEST_SOURCE_FILES})
