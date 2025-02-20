cmake_minimum_required(VERSION 3.25)
project(haffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(haffman main.cpp encoder.cpp encoder.h decode.cpp decode.h fastdec.cpp fastdec.h Decoder.cpp Decoder.h)
