cmake_minimum_required(VERSION 3.10)
project(MatrixLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(matrix sparse_matrix block_matrix)

add_library(matrix_lib
    matrix/matrix.cpp
    sparse_matrix/sparse_matrix.cpp
    block_matrix/block_matrix.cpp
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests tests/matrix_tests.cpp tests/sparse_matrix_tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread matrix_lib)
add_test(NAME matrix_tests COMMAND tests)
