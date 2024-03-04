cmake_minimum_required(VERSION 3.27)
project(Comet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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
find_package(CURL REQUIRED)

# TODO: Re-enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,cppcoreguidelines-*)

add_executable(Comet
        src/view/content_type_combo_box.h
        src/view/content_type_combo_box.cpp
        src/network/curl_utils.cpp
        src/network/curl_utils.h
        src/debug_info_formatter.h
        src/debug_info_formatter.cpp
        src/network/http_client.cpp
        src/network/http_client.h
        src/network/http_method.cpp
        src/network/http_method.h
        src/dataobject/request.h
        src/storage/request_storage.cpp
        src/storage/request_storage.h
        src/dataobject/response.h
        src/main.cpp
        src/main_window.h
        src/main_window.cpp
        src/view/method_combo_box.cpp
        src/view/method_combo_box.h
        src/view/property_table_widget.cpp
        src/view/property_table_widget.h
        src/request_builder.cpp)

target_link_libraries(Comet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CURL::libcurl
)

set_target_properties(Comet PROPERTIES
        MACOSX_BUNDLE TRUE
)
