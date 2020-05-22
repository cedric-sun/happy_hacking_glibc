cmake_minimum_required(VERSION 3.16)
project(happy_hacking_glibc C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(15_pipe_and_fifo)
add_subdirectory(26_processes)
add_subdirectory(2_error)
add_subdirectory(12_stream_io)
