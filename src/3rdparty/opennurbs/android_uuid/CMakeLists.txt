cmake_minimum_required (VERSION 3.4)
project( android_uuid C)


set( INCLUDE_DIRS
.
)


set( SOURCES
    copy.c
    gen_uuid.c
    isnull.c
    pack.c
    parse.c
    unpack.c
    unparse.c
    uuid_time.c
)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC

add_library( android_uuid STATIC
${SOURCES}
)

#target_compile_definitions(android_uuid PRIVATE Z_PREFIX MY_ZCALLOC)

target_include_directories( android_uuid
   PUBLIC
.
)

install( TARGETS android_uuid DESTINATION "lib")
install( FILES DESTINATION "include/android_uuid")
