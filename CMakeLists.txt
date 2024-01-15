cmake_minimum_required(VERSION 3.27)
project(comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/max/Qt/6.6.1/macos/lib/cmake/Qt6")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dataobject)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/storage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(comet
        src/view/contenttypecombobox.h
        src/view/contenttypecombobox.cpp
        src/network/curlutils.cpp
        src/network/curlutils.h
        src/debuginfoformatter.h
        src/debuginfoformatter.cpp
        src/network/httpclient.cpp
        src/network/httpclient.h
        src/network/httpmethod.cpp
        src/network/httpmethod.h
        src/dataobject/Request.h
        src/storage/RequestStorage.cpp
        src/storage/RequestStorage.h
        src/dataobject/Response.h
        src/main.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/view/methodcombobox.cpp
        src/view/methodcombobox.h
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
