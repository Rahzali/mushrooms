cmake_minimum_required(VERSION 3.16)
project(MapViewApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_definitions(/FI"cstdint")
else()
    # GCC or Clang
    add_definitions(-include cstdint)
endif()

include(Thirdparty.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Location Positioning)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        main.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt6::Core Qt6::Quick Qt6::Qml Qt6::Location Qt6::Positioning MapViewLib connector
)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER com.zofikar.mushromapp
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
    )
elseif (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(MapView)

qt_finalize_executable(${PROJECT_NAME})


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "$<TARGET_FILE_DIR:Qt6::Core>/windeployqt6.exe"
        "--qmldir=${CMAKE_SOURCE_DIR}/MapView"
        "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Running windeployqt6 after build")