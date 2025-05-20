cmake_minimum_required(VERSION 3.16)

project(MapViewLib LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Gui)

qt_add_resources(QML_RESOURCES qml.qrc)

add_library(MapViewLib SHARED
        MapView.cpp
        MapView.h
        ${QT_RESOURCES}
)

target_link_libraries(MapViewLib PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::Gui)

target_include_directories(MapViewLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(MapViewLib PRIVATE ${QML_RESOURCES})