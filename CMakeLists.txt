cmake_minimum_required(VERSION 3.19)
project(BrickBreaker LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

include_directories(
    core
    entities
    ui
    utils
)

qt_add_executable(BrickBreaker
    WIN32 MACOSX_BUNDLE
    main.cpp
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
    ui/ventanaprincipal.h ui/ventanaprincipal.cpp
    ui/pantallamenuprincipal.h ui/pantallamenuprincipal.cpp
    ui/pantallalogin.h ui/pantallalogin.cpp
    ui/pantallasignup.h ui/pantallasignup.cpp
)

target_link_libraries(BrickBreaker
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS BrickBreaker
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BrickBreaker
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})