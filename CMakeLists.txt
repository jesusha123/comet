cmake_minimum_required(VERSION 3.16)

project(comet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appcomet
    main.cpp
    NetworkManager.cpp
    NetworkManager.h
    Request.cpp
    Request.h
    Response.cpp
    Response.h
    TableModel.cpp
    TableModel.h
)

qt_add_qml_module(appcomet
    URI comet
    VERSION 1.0
    QML_FILES
        qml/FileTreeView.qml
        qml/Main.qml
        qml/RequestArea.qml
        qml/RequestControlPanel.qml
        qml/RequestPage.qml
        qml/Table.qml
        qml/TransactionPanel.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcomet PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcomet
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcomet
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appcomet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
