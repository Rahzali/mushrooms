cmake_minimum_required(VERSION 3.16)
project(MapViewApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Location Positioning)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
        main.cpp
)

add_subdirectory(MapView)

target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt6::Core Qt6::Quick Qt6::Qml Qt6::Location Qt6::Positioning MapViewLib
)
