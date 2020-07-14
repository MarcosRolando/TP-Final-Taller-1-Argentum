cmake_minimum_required(VERSION 3.16)

add_library(config Calculator.cpp ConfigFileReader.cpp Configuration.cpp
            MapFileReader.cpp)