cmake_minimum_required(VERSION 3.16)

SET(LIB_NAME libdxfrw)
project(${LIB_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

AUX_SOURCE_DIRECTORY(. SOURCES)
file(GLOB HEADERS "*.h")
file(GLOB INTERN "intern/*.*")

add_library(${LIB_NAME} STATIC ${HEADERS} ${SOURCES} ${INTERN})

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES FOLDER "3rdparty")
target_link_libraries(${LIB_NAME} PUBLIC iconv)
target_include_directories(${LIB_NAME} PRIVATE ../libiconv/include)