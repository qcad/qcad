cmake_minimum_required(VERSION 3.16)
project(qcadgui VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_library(qcadgui
    RCharacterWidget.cpp RCharacterWidget.h
    RCloseCurrentEvent.h
    RColorCombo.cpp RColorCombo.h
    RCommandLine.cpp RCommandLine.h
    RDockWidget.cpp RDockWidget.h
    REventFilter.cpp REventFilter.h
    REventHandler.cpp REventHandler.h
    RFileSystemModel.cpp RFileSystemModel.h
    RFlowLayout.cpp RFlowLayout.h
    RFocusFrame.cpp RFocusFrame.h
    RFontChooserWidget.cpp RFontChooserWidget.h
    RGraphicsSceneDrawable.cpp RGraphicsSceneDrawable.h
    RGraphicsSceneQt.cpp RGraphicsSceneQt.h
    RGraphicsViewImage.cpp RGraphicsViewImage.h
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
)

target_include_directories(qcadgui PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/gui
)

target_compile_definitions(qcadgui PUBLIC
    QCADGUI_LIBRARY
    QCAD_DLL
)

set_target_properties(qcadgui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

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
    -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
    qcadcore
    qcadentity
)
