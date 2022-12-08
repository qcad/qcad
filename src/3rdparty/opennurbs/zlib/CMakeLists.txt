cmake_minimum_required(VERSION 3.16)
project(zlib VERSION 1.0 LANGUAGES C)

add_library(zlib
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

if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(zlib PRIVATE
        NDEBUG
    )
endif()

SET_TARGET_PROPERTIES(zlib PROPERTIES FOLDER "3rdparty")