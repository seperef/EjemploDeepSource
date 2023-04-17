cmake_minimum_required(VERSION 3.23)
project(LambertBattin)

set(CMAKE_CXX_STANDARD 14)

add_executable(LambertBattin LAMBERTBATTIN.cpp LAMBERTBATTIN.h testUnitarios.cpp vector.cpp vector.h seebatt.cpp seebatt.h main.cpp seebattk.h seebatk.cpp)
