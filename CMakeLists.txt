cmake_minimum_required(VERSION 2.6)
project(Threadpool)

add_library(threadpool STATIC 
    Threadpool.cpp
    ThreadpoolTimer.cpp
    ThreadpoolWork.cpp
    ThreadpoolWait.cpp
    ThreadpoolIo.cpp
)

add_executable(
    TPTest main.cpp
)

target_link_libraries(TPTest threadpool)