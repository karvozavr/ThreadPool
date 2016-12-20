cmake_minimum_required(VERSION 3.6)
project(thread_pool)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pthread -std=gnu99 -Wall -Wextra")

set(SOURCE_FILES main.c computation.c thread_pool.c wsqueue.c squeue.c queue.c linkedlist.c)
add_executable(thread_pool ${SOURCE_FILES})
