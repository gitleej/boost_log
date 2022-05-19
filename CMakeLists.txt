cmake_minimum_required(VERSION 3.21)
project(boost_log_test)

set(CMAKE_CXX_STANDARD 11)

file(COPY conf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY conf DESTINATION ${CMAKE_BINARY_DIR}/test)

add_subdirectory(./example)
add_subdirectory(./MVPRLog)
add_subdirectory(./test)
