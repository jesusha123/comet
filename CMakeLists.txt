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
        src/view/ContentTypeComboBox.h
        src/view/ContentTypeComboBox.cpp
        src/network/curlutils.cpp
        src/network/curlutils.h
        src/DebugInfoFormatter.h
        src/DebugInfoFormatter.cpp
        src/network/HttpClient.cpp
        src/network/HttpClient.h
        src/network/HttpMethod.cpp
        src/network/HttpMethod.h
        src/dataobject/request.h
        src/storage/RequestStorage.cpp
        src/storage/RequestStorage.h
        src/dataobject/response.h
        src/main.cpp
        src/MainWindow.h
        src/MainWindow.cpp
        src/view/MethodComboBox.cpp
        src/view/MethodComboBox.h
        src/view/PropertyTableWidget.cpp
        src/view/PropertyTableWidget.h
        src/RequestBuilder.cpp)

target_link_libraries(comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        curl
)

set_target_properties(comet PROPERTIES
        MACOSX_BUNDLE TRUE
)
