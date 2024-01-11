cmake_minimum_required(VERSION 3.27)
project(comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/max/Qt/6.6.1/macos/lib/cmake/Qt6")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(comet
        src/view/contenttypecombobox.h
        src/view/contenttypecombobox.cpp
        src/curlutils.cpp
        src/curlutils.h
        src/debuginfoformatter.h
        src/debuginfoformatter.cpp
        src/httpclient.cpp
        src/httpclient.h
        src/httpmethod.cpp
        src/httpmethod.h
        src/httprequest.h
        src/httprequeststorage.cpp
        src/httprequeststorage.h
        src/httpresponse.h
        src/main.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/methodcombobox.cpp
        src/methodcombobox.h
        src/view/propertytablewidget.cpp
        src/view/propertytablewidget.h
        src/requestbuilder.cpp)

target_link_libraries(comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        curl
)

set_target_properties(comet PROPERTIES
        MACOSX_BUNDLE TRUE
)
