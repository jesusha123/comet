cmake_minimum_required(VERSION 3.27)
project(Comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/command)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dataobject)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/model)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/storage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/view)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(CURL REQUIRED)
find_package(yaml-cpp REQUIRED)

# TODO: Re-enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,cppcoreguidelines-*)

add_executable(Comet
        src/command/Command.h
        src/command/CreateRequestCommand.h
        src/command/CreateRequestCommand.cpp
        src/command/DeleteRequestCommand.h
        src/command/DeleteRequestCommand.cpp
        src/command/LoadRequestCommand.h
        src/command/LoadRequestCommand.cpp
        src/command/RenameRequestCommand.h
        src/command/RenameRequestCommand.cpp
        src/command/SaveRequestCommand.h
        src/command/SaveRequestCommand.cpp
        src/command/ShowAboutCommand.cpp
        src/command/ShowAboutCommand.h
        src/dataobject/Request.h
        src/dataobject/Response.h
        src/DebugInfoFormatter.h
        src/DebugInfoFormatter.cpp
        src/icons.qrc
        src/main.cpp
        src/MainWindow.h
        src/MainWindow.cpp
        src/model/FileSystemModel.h
        src/model/FileSystemModel.cpp
        src/network/curl_utils.cpp
        src/network/curl_utils.h
        src/network/HttpClient.cpp
        src/network/HttpClient.h
        src/network/HttpMethod.cpp
        src/network/HttpMethod.h
        src/network/RequestThread.cpp
        src/network/RequestThread.h
        src/RequestWidget.cpp
        src/RequestWidget.h
        src/RequestBuilder.cpp
        src/storage/RequestStorage.cpp
        src/storage/RequestStorage.h
        src/view/CollectionTreeView.h
        src/view/CollectionTreeView.cpp
        src/view/ContentTypeComboBox.h
        src/view/ContentTypeComboBox.cpp
        src/view/MethodComboBox.cpp
        src/view/MethodComboBox.h
        src/view/PropertyTableWidget.cpp
        src/view/PropertyTableWidget.h
        src/view/RequestInfoTableWidget.h
        src/view/RequestInfoTableWidget.cpp
        src/view/RequestTabBar.h
        src/view/RequestTabBar.cpp
        src/view/RequestTabWidget.h
        src/view/RequestTabWidget.cpp
        src/winapp.rc
        src/YamlConversions.h
    )

target_link_libraries(Comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CURL::libcurl
        yaml-cpp::yaml-cpp
)

set_target_properties(Comet PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
