cmake_minimum_required(VERSION 3.10)

set(LAB_NAME "lab3")

project(${LAB_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${LAB_NAME}_lib src/figure.cpp src/rectangle.cpp src/square.cpp src/triangle.cpp src/figure_array.cpp)
add_executable(${LAB_NAME}_exe main.cpp)

target_link_libraries(${LAB_NAME}_exe PRIVATE ${LAB_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(run_tests
    test/test_square.cpp
    test/test_rectangle.cpp
    test/test_triangle.cpp
)
target_link_libraries(run_tests ${LAB_NAME}_lib gtest_main)
