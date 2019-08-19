cmake_minimum_required (VERSION 3.8)
project (Omega)
set(CMAKE_CXX_STANDARD 17)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_subdirectory(tests)

add_executable(omega main.cpp)
target_link_libraries(omega ${CONAN_LIBS_SFML} ${CONAN_LIBS_YAML-CPP})