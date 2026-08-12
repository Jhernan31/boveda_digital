cmake_minimum_required(VERSION 4.2)
project(BovedaDigital)

set(CMAKE_CXX_STANDARD 17)

add_executable(BovedaDigital main.cpp
        Registro.cpp
        Registro.h
        ManejadorDB.cpp
        ManejadorDB.h
        driver.cpp)
