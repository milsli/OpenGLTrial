cmake_minimum_required(VERSION 3.5)

project(Wahadlo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(glut)

# include_directories(Wahadlo_SOURCE_DIR/GL)

add_executable(Wahadlo main.cpp
    Wahadlo.h
    Wahadlo2Niezal.h)

# target_link_libraries(Wahadlo PRIVATE glut)

include(GNUInstallDirs)
install(TARGETS Wahadlo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
