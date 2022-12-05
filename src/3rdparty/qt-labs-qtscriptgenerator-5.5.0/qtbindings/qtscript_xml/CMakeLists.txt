cmake_minimum_required(VERSION 3.16)
SET(NAME xml)
set(LIB_NAME qtscript_${NAME})

project(${LIB_NAME} VERSION 1.0 LANGUAGES CXX C)

include(../../../../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml Script)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}/Debug/plugins/script)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}/Release/plugins/script)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH}/MinSizeRel/plugins/script)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH}/RelWithDebInfo/plugins/script)

qt_standard_project_setup()

SET(SOURCES plugin.cpp plugin.h)
FILE(GLOB GENERATED_SRC "../../generated_cpp/com_trolltech_qt_${NAME}/*.cpp")
FILE(GLOB GENERATED_INC "../../generated_cpp/com_trolltech_qt_${NAME}/*.h")

add_library(${LIB_NAME} SHARED 
    ${SOURCES}
    ${GENERATED_SRC}
    ${GENERATED_INC}
    ${RC}
)

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES FOLDER "scripts")

target_include_directories(${LIB_NAME} PRIVATE ./ include ../../generated_cpp/com_trolltech_qt_${NAME})

target_link_libraries(${LIB_NAME} PRIVATE
    Qt::Concurrent
    Qt::Core
    Qt::Widgets
    Qt::PrintSupport
    Qt::Gui
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    Qt::Qml
    Qt::Script
)
