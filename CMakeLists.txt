cmake_minimum_required(VERSION 3.15)
project(laba8)
set(CMAKE_CXX_STANDARD 14)

#add_executable(laba8 Procedure/main_procedure.cpp collab/Date.cpp collab/Date.h) #main.cpp
add_executable(laba8 main.cpp OOP/DT.h OOP/DT.cpp collab/Date.cpp collab/Date.h )
