cmake_minimum_required(VERSION 3.17)

project(bulls-cows-bot)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

include_directories(/usr/local/include ${Boost_INCLUDE_DIR})

set (SRC_LIST
        ${SRC_DIR}/Core.cpp
        ${SRC_DIR}/GameNumber.cpp)


add_executable(main main.cpp ${SRC_LIST})
target_link_libraries(main spdlog::spdlog)