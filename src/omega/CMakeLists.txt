cmake_minimum_required (VERSION 3.8)
project (Omega)
set(CMAKE_CXX_STANDARD 17)

if(EXISTS ${CMAKE_BINARY_DIR}/../build/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/../build/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_subdirectory(tests)

set(SOURCE_FILES
        main.cpp
        config.cpp
        window.cpp
        objects.cpp
        triangle.cpp
        vector.cpp
        raycaster.cpp
        )

add_executable(omega ${SOURCE_FILES})
target_link_libraries(omega ${CONAN_LIBS_SFML} ${CONAN_LIBS_YAML-CPP})