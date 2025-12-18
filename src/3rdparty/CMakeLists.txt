cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(3rdparty VERSION 1.0 LANGUAGES CXX C)

add_subdirectory(dxflib)
add_subdirectory(opennurbs)
add_subdirectory(spatialindexnavel)
add_subdirectory(stemmer)

IF(NOT BUILD_QT6)
	add_subdirectory(qt-labs-qtscriptgenerator-5.5.0)
ENDIF()
