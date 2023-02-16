cmake_minimum_required(VERSION 3.16)
project(dxflib VERSION 1.0 LANGUAGES CXX)

IF(WIN32)
    SET(RC dxflib.rc)
ENDIF()

add_library(dxflib
    src/dl_attributes.h
    src/dl_codes.h
    src/dl_creationadapter.h
    src/dl_creationinterface.h
    src/dl_dxf.cpp src/dl_dxf.h
    src/dl_entities.h
    src/dl_exception.h
    src/dl_extrusion.h
    src/dl_writer.h
    src/dl_writer_ascii.cpp src/dl_writer_ascii.h
    ${RC}
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(dxflib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../release)
else()
    set_target_properties(dxflib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../debug)
endif()

target_include_directories(dxflib PUBLIC
    src
)

target_compile_definitions(dxflib PRIVATE
    DXFLIB_LIBRARY
)


#target_link_libraries(dxflib PUBLIC
#    Qt::Core
#    Qt::Gui
#)

#if(win32-msvc)
#    target_compile_definitions(dxflib PUBLIC
#        _CRT_SECURE_NO_DEPRECATE
#    )
#endif()

#install(TARGETS dxflib
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
