cmake_minimum_required(VERSION 3.26)
project(quoridor)

set(CMAKE_CXX_STANDARD 17)

add_executable(quoridor main.cpp
        board.cpp
        magic.h
        player.h
)
