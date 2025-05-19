cmake_minimum_required (VERSION 3.16)
project( opennurbs_public_freetype C)

include_directories("include")

set( SOURCES
    src/autofit/autofit.c
    src/base/ftbase.c
    src/base/ftbbox.c
    src/base/ftbdf.c
    src/base/ftbitmap.c
    src/base/ftcid.c
    src/base/ftdebug.c
    src/base/ftfntfmt.c
    src/base/ftfstype.c
    src/base/ftgasp.c
    src/base/ftglyph.c
    src/base/ftgxval.c
    src/base/ftinit.c
    src/base/ftlcdfil.c
    src/base/ftmm.c
    src/base/ftotval.c
    src/base/ftpatent.c
    src/base/ftpfr.c
    src/base/ftstroke.c
    src/base/ftsynth.c
    src/base/ftsystem.c
    src/base/fttype1.c
    src/base/ftwinfnt.c
    src/bdf/bdf.c
    src/bzip2/ftbzip2.c
    src/cache/ftcache.c
    src/cff/cff.c
    src/cid/type1cid.c
    src/gzip/ftgzip.c
    src/lzw/ftlzw.c
    src/pcf/pcf.c
    src/pfr/pfr.c
    src/psaux/psaux.c
    src/pshinter/pshinter.c
    src/psnames/psnames.c
    src/raster/raster.c
    src/sfnt/sfnt.c
    src/smooth/smooth.c
    src/truetype/truetype.c
    src/type1/type1.c
    src/type42/type42.c
    src/winfonts/winfnt.c
)

add_library( opennurbs_public_freetype STATIC
    ${SOURCES}
)

    set( OPENNURBS_FREETYPE_DEFINES
        FT2_BUILD_LIBRARY
    )
    target_compile_definitions(opennurbs_public_freetype PRIVATE ${OPENNURBS_FREETYPE_DEFINES})
    
if( APPLE)
    set_target_properties( opennurbs_public_freetype
        PROPERTIES
        XCODE_ATTRIBUTE_SDKROOT "macosx"
        XCODE_ATTRIBUTE_SUPPORTED_PLATFORMS "macosx iphonesimulator iphoneos"
        XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf"
        XCODE_ATTRIBUTE_HEADER_SEARCH_PATHS "$(PROJECT_DIR)/freetype263/include"
    )
endif()

install( TARGETS opennurbs_public_freetype DESTINATION "lib")
install( FILES ${PUBLIC_HEADERS} DESTINATION "include/opennurbs_public_freetype")
