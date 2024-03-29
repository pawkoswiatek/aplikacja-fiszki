cmake_minimum_required(VERSION 3.20)
project(glownyprojekt)

set(CMAKE_CXX_STANDARD 14)
set(Sources glowny_projekt.cpp)
set(Headers glowny_projekt.cpp)
add_executable(glownyprojekt glowny_projekt.cpp tlumaczenie.h angielski.h francuski.h norweski.h wietnamski.h chinski_uproszczony.h koreanski.h rosyjski.h arabski.h hebrajski.h gruzinski.h wegierski.h hindi.h)

