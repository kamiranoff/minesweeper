cmake_minimum_required(VERSION 3.15)
project(MineSweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(MineSweeper main.cpp MineField/MineField.cpp MineField/MineField.h procedural/MineSweeper.cpp procedural/MineSweeper.h)