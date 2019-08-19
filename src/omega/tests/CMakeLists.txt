cmake_minimum_required(VERSION 3.8)
project(omega-tests)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        test_main.cpp
        test_vector.cpp
        )

add_executable(omega-tests ${SOURCE_FILES})
#target_link_libraries(omega-tests ${CONAN_LIBS_CATCH})
