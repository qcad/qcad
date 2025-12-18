cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(qcadgui VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

if(WIN32)
    set(RC gui.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadgui SHARED
    RCharacterWidget.cpp RCharacterWidget.h
    RCadToolBar.cpp RCadToolBar.h
    RCadToolBarPanel.cpp RCadToolBarPanel.h
    RColumnLayout.cpp RColumnLayout.h
    RCloseCurrentEvent.h
    RColorCombo.cpp RColorCombo.h
    RComboBox.cpp RComboBox.h
    RCommandLine.cpp RCommandLine.h
    RDockWidget.cpp RDockWidget.h
    REventFilter.cpp REventFilter.h
    RToolOptionEventFilter.cpp RToolOptionEventFilter.h
    REventHandler.cpp REventHandler.h
    RFileSystemModel.cpp RFileSystemModel.h
    RFlowLayout.cpp RFlowLayout.h
    RFocusFrame.cpp RFocusFrame.h
    RFontChooserWidget.cpp RFontChooserWidget.h
    RGraphicsSceneDrawable.cpp RGraphicsSceneDrawable.h
    RGraphicsSceneQt.cpp RGraphicsSceneQt.h
    RGraphicsViewImage.cpp RGraphicsViewImage.h
    RGraphicsViewWorker.cpp RGraphicsViewWorker.h
    RGraphicsViewWorkerPainter.cpp RGraphicsViewWorkerPainter.h
    RGraphicsViewQt.cpp RGraphicsViewQt.h
    RLinetypeCombo.cpp RLinetypeCombo.h
    RLinetypeComboDelegate.cpp RLinetypeComboDelegate.h
    RLineweightCombo.cpp RLineweightCombo.h
    RListView.cpp RListView.h
    RListWidget.cpp RListWidget.h
    RMainWindowQt.cpp RMainWindowQt.h
    RMathComboBox.cpp RMathComboBox.h
    RMathLineEdit.cpp RMathLineEdit.h
    RMdiArea.cpp RMdiArea.h
    RMdiChildQt.cpp RMdiChildQt.h
    RRulerQt.cpp RRulerQt.h
    RShortcutLineEdit.cpp RShortcutLineEdit.h
    RTextEdit.cpp RTextEdit.h
    RToolButton.cpp RToolButton.h
    RToolMatrixItemDelegate.cpp RToolMatrixItemDelegate.h
    RTreeWidget.cpp RTreeWidget.h
    ${RC}
)

target_include_directories(qcadgui PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/gui
)

target_compile_definitions(qcadgui PRIVATE
    QCADGUI_LIBRARY
    QCAD_DLL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadgui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadgui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadgui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadgui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()

target_link_libraries(qcadgui PUBLIC
    Qt::Concurrent
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
    qcadentity
)
