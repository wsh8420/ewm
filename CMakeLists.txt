cmake_minimum_required(VERSION 3.22)
project(ewm)

set(CMAKE_CXX_STANDARD 14)

add_executable(ewm main.cpp PandasDataFrame.cpp)
#add_executable(ewm main.cpp)