cmake_minimum_required(VERSION 3.26)
project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Project main.c
        menu.c
        base.h
        data_utility.c
        question_operation.c
        global_definition.h
        student_operation.c
        score_management.c
        score_management.c
        linsnow.c)
