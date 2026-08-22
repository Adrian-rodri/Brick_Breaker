cmake_minimum_required(VERSION 3.16)

project(Brick_Breaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Brick_Breaker main.cpp)

include(GNUInstallDirs)
install(TARGETS Brick_Breaker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
