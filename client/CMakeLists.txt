cmake_minimum_required (VERSION 3.22.2)

project(client)

set (CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(cppzmq)
find_package(Threads REQUIRED)

add_executable(client main.cpp zhelper.h)

target_link_libraries(client Threads::Threads cppzmq)

add_definitions(-DZMQ_BUILD_DRAFT_API=1)