cmake_minimum_required(VERSION 3.27)
project(Comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/action)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dataobject)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/storage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(CURL REQUIRED)

# TODO: Re-enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,cppcoreguidelines-*)

add_executable(Comet
        src/action/Command.h
        src/icons.qrc
        src/view/ContentTypeComboBox.h
        src/view/ContentTypeComboBox.cpp
        src/network/curl_utils.cpp
        src/network/curl_utils.h
        src/DebugInfoFormatter.h
        src/DebugInfoFormatter.cpp
        src/network/HttpClient.cpp
        src/network/HttpClient.h
        src/network/HttpMethod.cpp
        src/network/HttpMethod.h
        src/dataobject/Request.h
        src/storage/RequestStorage.cpp
        src/storage/RequestStorage.h
        src/dataobject/Response.h
        src/main.cpp
        src/MainWindow.h
        src/MainWindow.cpp
        src/RequestWidget.cpp
        src/RequestWidget.h
        src/view/MethodComboBox.cpp
        src/view/MethodComboBox.h
        src/view/PropertyTableWidget.cpp
        src/view/PropertyTableWidget.h
        src/RequestBuilder.cpp
        src/action/ShowAboutCommand.cpp
        src/action/ShowAboutCommand.h
        src/network/RequestThread.cpp
        src/network/RequestThread.h)

target_link_libraries(Comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CURL::libcurl
)

set_target_properties(Comet PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
