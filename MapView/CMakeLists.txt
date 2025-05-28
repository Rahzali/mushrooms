project(MapViewLib LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Gui)

add_library(MapViewLib STATIC
        MapView.cpp
        MapView.h
)

target_link_libraries(MapViewLib PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::Gui)

qt_add_resources(QML_RCC_FILES qml.qrc)
target_sources(MapViewLib PRIVATE ${QML_RCC_FILES})

target_include_directories(MapViewLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
