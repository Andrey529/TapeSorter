cmake_minimum_required(VERSION 3.21)
project(TapeSorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(TapeSorter src/main.cpp src/Tape.h src/TapeImpl.cpp src/TapeImpl.h src/TapeSorter.cpp src/TapeSorter.h)
