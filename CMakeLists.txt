cmake_minimum_required(VERSION 3.27)
project(untitled1 C)
set(CMAKE_C_STANDARD 11)
add_executable(untitled1 main.c
        modified/loc.c
        modified/loc.h
        modified/moves.c
        modified/moves.h
        modified/map.c
        modified/map.h
        modified/queue.c
        modified/queue.h
        created/node.c
        created/node.h
        created/tree.c
        created/tree.h
        menu.c
        menu.h
)