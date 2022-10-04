cmake_minimum_required(VERSION 3.16)
project(3rdparty VERSION 1.0 LANGUAGES CXX C)

include(../../CMakeInclude.txt)

add_subdirectory(dxflib)
add_subdirectory(opennurbs)
add_subdirectory(spatialindexnavel)
add_subdirectory(stemmer)
