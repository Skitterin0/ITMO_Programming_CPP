cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp)

include_directories(include/curl)
find_library(LIBCURL libcurl lib)
target_link_libraries(Lab2 LINK_PUBLIC ${LIBCURL})

include_directories(include/json)
find_library(JSONCPP jsoncpp lib)
target_link_libraries(Lab2 LINK_PUBLIC ${JSONCPP})

