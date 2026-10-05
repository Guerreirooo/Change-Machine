cmake_minimum_required(VERSION 3.29)
project(TesteProjeto2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TesteProjeto2
    algoritmo.c
    algoritmo.h
    func.c
    func.h
    main.c
    utils.c
    utils.h)
