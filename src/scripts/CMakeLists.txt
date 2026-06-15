cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(qcadscripts VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

# Regenerate scripts.qrc / scripts_release.qrc from the current files on disk
# at build time. The .qrc files are declared as outputs so ninja tracks them
# directly and re-runs rcc in the same build whenever they change. The extra,
# never-created output forces the command to run on every build; update_qrc.sh
# only rewrites a .qrc when its content actually changed (via its diff check),
# so rcc is only re-invoked when there is a real change.
# Regenerate the .qrc files at build time, wrapped in a dedicated custom target
# (qcadscripts_qrc) rather than attached to the qcadscripts library target.
#
# This decoupling is what avoids a dependency cycle. qt_add_resources() below
# registers each .qrc as a configure-time dependency (CMAKE_LIST_FILES), and
# cmake_autogen records all of those in its depfile, so qcadscripts_autogen ends
# up depending on scripts_release.qrc. If the command that *produces* the .qrc
# were attached to qcadscripts, CMake would also give it an order-only dependency
# on qcadscripts_autogen, closing the loop:
#   scripts_release.qrc -> qcadscripts_autogen -> .../timestamp -> scripts_release.qrc
# Owning the producer with a separate target (no AUTOGEN) breaks the forward edge.
#
# The extra, never-created output forces the command to run on every build;
# update_qrc.sh only rewrites a .qrc when its content actually changed (via its
# diff check), so rcc is only re-invoked when there is a real change.
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts_release.qrc
        ${CMAKE_CURRENT_BINARY_DIR}/update_qrc_always_run
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/update_qrc.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Updating scripts.qrc / scripts_release.qrc"
    VERBATIM
)

add_custom_target(qcadscripts_qrc
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts_release.qrc
        ${CMAKE_CURRENT_BINARY_DIR}/update_qrc_always_run
)

if(rtest)
    qt_add_resources(SOURCES scripts.qrc)
else()
    qt_add_resources(SOURCES scripts_release.qrc)
endif()

if(WIN32)
    set(RC scripts.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadscripts SHARED
    RScriptsPlugin.cpp RScriptsPlugin.h
    ${SOURCES}
    ${RC}
)

target_include_directories(qcadscripts PRIVATE
    ../../src/core
    ../../src/core/math
)

target_compile_definitions(qcadscripts PRIVATE
    QCAD_DLL
)

# Ensure the .qrc files are regenerated before this target's resources are
# compiled (the rcc command also depends on the .qrc files directly).
add_dependencies(qcadscripts qcadscripts_qrc)

set_target_properties(qcadscripts PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins)
set_target_properties(qcadscripts PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins)
set_target_properties(qcadscripts PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins)

target_link_libraries(qcadscripts PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
)


