cmake_minimum_required(VERSION 3.27)
project(comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/max/Qt/6.6.1/macos/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(comet main.cpp
        contenttypecombobox.h
        contenttypecombobox.cpp
        mainwindow.h
        mainwindow.cpp)
target_link_libraries(comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

