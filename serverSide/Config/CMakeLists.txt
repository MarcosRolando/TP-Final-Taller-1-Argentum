cmake_minimum_required(VERSION 3.10.2)

add_library(config Calculator.cpp ConfigFileReader.cpp Configuration.cpp
            MapFileReader.cpp)
