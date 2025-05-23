cmake_minimum_required(VERSION 3.16)
project(zlib VERSION 1.0 LANGUAGES C)

add_library(zlib SHARED
    adler32.c
    compress.c
    crc32.c crc32.h
    deflate.c deflate.h
    infback.c
    inffast.c inffast.h
    inffixed.h
    inflate.c inflate.h
    inftrees.c inftrees.h
    trees.c trees.h
    uncompr.c
    zconf.h
    zlib.h
    zutil.c zutil.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(zlib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../../release)
    set_target_properties(zlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../../release)
    target_link_libraries(zlib PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../../release)
else()
    set_target_properties(zlib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../../debug)
    set_target_properties(zlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../../debug)
    target_link_libraries(zlib PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../../debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(zlib PRIVATE
        NDEBUG
    )
endif()
