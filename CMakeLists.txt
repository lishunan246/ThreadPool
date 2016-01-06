cmake_minimum_required(VERSION 2.6)
project(Threadpool)

add_library(threadpool STATIC 
    Threadpool.cpp
    ThreadpoolTimer.cpp
    ThreadpoolWork.cpp
    ThreadpoolWait.cpp
    ThreadpoolIo.cpp
    Threadpool.h
    ThreadpoolTimer.h
    ThreadpoolWork.h
    ThreadpoolWait.h
    ThreadpoolIo.h
)

add_executable(
    TPTest main.cpp
)

target_link_libraries(TPTest threadpool)