cmake_minimum_required(VERSION 3.16)
project(QCAD VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

IF(WIN32)
    SET(RC qcad.rc)
ENDIF()

add_executable(QCAD WIN32 MACOSX_BUNDLE
    main.cpp ${RC}
)
target_include_directories(QCAD PRIVATE
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/grid
    ../../src/gui
    ../../src/io/dxf
    ../../src/operations
    ../../src/scripting
    ../../src/scripting/ecmaapi
    ../../src/scripting/ecmaapi/adapters
    ../../src/scripting/ecmaapi/generated
    ../../src/snap
    ../../src/spatialindex
    ../../src/stemmer
    ../../src/zip
)

target_compile_definitions(QCAD PRIVATE
    QCAD_DLL
)

set_target_properties(QCAD PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)

target_link_libraries(QCAD PRIVATE
    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    Qt::Qml
    Qt::PrintSupport
    -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
    qcadcore
    qcadentity
    qcadgui
    qcadgrid
    qcadgui
    qcadoperations
    qcadsnap
    qcadspatialindex
    spatialindexnavel
    stemmer
)

IF(NOT BUILD_QT6)
    target_link_libraries(QCAD PRIVATE qcadecmaapi)
ENDIF()

if(APPLE)
    target_sources(QCAD PRIVATE
        removemacmenus.h removemacmenus.mm
    )

    target_link_libraries(QCAD PRIVATE
        "-framework AppKit"
        "-framework CoreServices"
        #WrapIconv::WrapIconv
        #z
    )
endif()

if(WIN32)
    target_link_libraries(QCAD PRIVATE
        Rpcrt4
        advapi32.lib
        comdlg32.lib
        gdi32.lib
        kernel32.lib
        odbc32.lib
        odbccp32.lib
        ole32.lib
        oleaut32.lib
        shell32.lib
        user32.lib
        uuid.lib
        winspool.lib
    )
endif()

if(NOT r_no_opennurbs)
    target_link_libraries(QCAD PRIVATE
        -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
        zlib
        opennurbs
    )
endif()

if(linux-g++)
    target_link_libraries(QCAD PRIVATE
        GLU
    )
endif()


if(MACOS)
    target_link_libraries(QCAD PRIVATE
        Qt::MacExtras
    )
endif()

if(r_no_opennurbs)
    target_compile_definitions(QCAD PRIVATE
        R_NO_OPENNURBS
    )
endif()

if(win32-msvc2010)
    target_compile_definitions(QCAD PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

