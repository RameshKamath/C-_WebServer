cmake_minimum_required(VERSION 3.7)

project(cppServer)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(cppServer main.cpp)
target_link_libraries(cppServer ${Boost_LIBRARIES} Threads::Threads)
