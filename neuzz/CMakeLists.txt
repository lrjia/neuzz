cmake_minimum_required(VERSION 3.19)
project(neuzz C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(neuzz
        neuzz.c connect.c connect.h seed_persist.c seed_persist.h neuzz.h gen_bitmap.c gen_bitmap.h)
