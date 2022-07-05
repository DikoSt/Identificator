cmake_minimum_required(VERSION 3.16)
project(Identificator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC_FILES *.cpp)
file(GLOB HEADER_FILES *.h)


add_executable(Identificator ${SRC_FILES} ${HEADER_FILES})