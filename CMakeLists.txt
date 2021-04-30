cmake_minimum_required(VERSION 3.19)
project(Othello C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Othello
        board.h
        main.c
        output.h
        structures.h
        user_input.h
        Validation.h)
