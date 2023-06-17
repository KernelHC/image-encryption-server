cmake_minimum_required(VERSION 3.25)
project(imageEncryption C)

set(CMAKE_C_STANDARD 11)

add_executable(imageEncryption
        tree.c queue.c hashf.c caes.c queue.h hashf.h caes.h tree.h queue_test.c)
