cmake_minimum_required(VERSION 3.26)
project(drink_wholesale_management_system C)

set(CMAKE_C_STANDARD 11)

add_executable(drink_wholesale_management_system main.c
        user.c
        user.h
        manager.c
        manager.h
        public.c
        public.h
)
