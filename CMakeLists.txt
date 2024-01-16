cmake_minimum_required(VERSION 3.14)
project(supervisor)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS thread system chrono)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(supervisor main.cpp
        Log_reader.cpp
        Log_reader.h
        LogInfo.h
)
target_link_libraries(supervisor ${Boost_LIBRARIES})
