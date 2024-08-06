cmake_minimum_required(VERSION 3.5.0)
project(Notebook VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Notebook main.cpp Manager.cpp Note.cpp Encryptor.cpp)
