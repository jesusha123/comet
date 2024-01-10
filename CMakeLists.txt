cmake_minimum_required(VERSION 3.27)
project(comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/max/Qt/6.6.1/macos/lib/cmake/Qt6")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(comet
        contenttypecombobox.h
        contenttypecombobox.cpp
        curlutils.cpp
        curlutils.h
        debuginfoformatter.h
        debuginfoformatter.cpp
        httpclient.cpp
        httpclient.h
        httpmethod.cpp
        httpmethod.h
        httprequest.h
        httprequeststorage.cpp
        httprequeststorage.h
        httpresponse.h
        main.cpp
        mainwindow.h
        mainwindow.cpp
        methodcombobox.cpp
        methodcombobox.h
        propertytablewidget.cpp
        propertytablewidget.h
        requestbuilder.cpp)
target_link_libraries(comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        curl
)

