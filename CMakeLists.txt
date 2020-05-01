cmake_minimum_required(VERSION 3.9)

project(bulls-cows-bot)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(THIRD_PARTY ${CMAKE_SOURCE_DIR}/3rdparty)

add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/spdlog)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(range-v3 REQUIRED)


include_directories(/usr/local/include ${Boost_INCLUDE_DIR})
include_directories(${THIRD_PARTY}/ranges/include)
include_directories(${THIRD_PARTY}/spdlog/include/spdlog)
include_directories(${THIRD_PARTY}/doctest/doctest)

set (SRC_LIST
        ${SRC_DIR}/algo/Algorithm.cpp
        ${SRC_DIR}/algo/GameNumber.cpp
        ${SRC_DIR}/algo/NumberGenerator.cpp
        ${SRC_DIR}/algo/BullsCows.cpp
        ${SRC_DIR}/Game.cpp
        ${SRC_DIR}/Logger.cpp
        ${SRC_DIR}/ConsoleGame.cpp
        ${SRC_DIR}/Utils.cpp
        )

option(BUILD_TESTS ON)

if (BUILD_TESTS)
    add_executable(tests tests.cpp ${SRC_LIST})
    target_link_libraries(tests PRIVATE spdlog::spdlog)
endif()

add_executable(main main.cpp ${SRC_LIST})
target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(main PRIVATE range-v3)
