cmake_minimum_required (VERSION 3.16)
project( zlib C)


set( INCLUDE_DIRS
.
)

set( PROJECT_HEADERS
crc32.h
deflate.h
inffast.h
inffixed.h
inflate.h
inftrees.h
trees.h
zconf.h
zlib.h
zutil.h
)

set( SOURCES
adler32.c
compress.c
crc32.c
deflate.c
infback.c
inffast.c
inflate.c
inftrees.c
trees.c
uncompr.c
zutil.c
)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC
add_library( zlib STATIC
${SOURCES}
${PROJECT_HEADERS}
${RESOURCES}
)
target_compile_definitions(zlib PRIVATE Z_PREFIX MY_ZCALLOC)

target_include_directories( zlib
   PUBLIC
.
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

install( TARGETS zlib DESTINATION "lib")
install( FILES DESTINATION "include/zlib")
