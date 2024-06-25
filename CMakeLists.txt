cmake_minimum_required(VERSION 3.0)

project(A10_memory_allocator LANGUAGES C)

include_directories(include)

add_executable(alloc src/main.c src/alloc.c)
