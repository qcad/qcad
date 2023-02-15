cmake_minimum_required(VERSION 3.16)
project(qcadcustomwidgets VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

IF(WIN32)
    SET(RC customwidgets.rc)
ENDIF()
add_library(qcadcustomwidgets SHARED
    RCharacterWidgetPlugin.cpp RCharacterWidgetPlugin.h
    RColorComboPlugin.cpp RColorComboPlugin.h
    RCommandLinePlugin.cpp RCommandLinePlugin.h
    RCustomWidgets.cpp RCustomWidgets.h
    RFontChooserWidgetPlugin.cpp RFontChooserWidgetPlugin.h
    RGraphicsViewQtPlugin.cpp RGraphicsViewQtPlugin.h
    RLinetypeComboPlugin.cpp RLinetypeComboPlugin.h
    RLineweightComboPlugin.cpp RLineweightComboPlugin.h
    RListViewPlugin.cpp RListViewPlugin.h
    RMathComboBoxPlugin.cpp RMathComboBoxPlugin.h
    RMathLineEditPlugin.cpp RMathLineEditPlugin.h
    RMdiChildQtPlugin.cpp RMdiChildQtPlugin.h
    RRulerQtPlugin.cpp RRulerQtPlugin.h
    RShortcutLineEditPlugin.cpp RShortcutLineEditPlugin.h
    RTextEditPlugin.cpp RTextEditPlugin.h
    ${RC}
)
target_include_directories(qcadcustomwidgets PRIVATE
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/gui
)

target_compile_definitions(qcadcustomwidgets PRIVATE
    QCAD_DLL
)

set_target_properties(qcadcustomwidgets PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../plugins/designer)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(qcadcustomwidgets PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    target_link_libraries(qcadcustomwidgets PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

target_link_libraries(qcadcustomwidgets PRIVATE
    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
    qcadgui
)
