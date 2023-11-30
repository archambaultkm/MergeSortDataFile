cmake_minimum_required(VERSION 3.14)
project(Assignment4)

set(CMAKE_CXX_STANDARD 23)

add_executable(merge
        main.cpp
        inc/colours.h
        inc/timer.h
        inc/utils.h
        src/utils.cpp
        inc/entity.h
        src/entity_file_processor.cpp
        inc/entity_file_processor.h
        inc/merge_sort.h
        src/merge_sort.cpp)
