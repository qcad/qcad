cmake_minimum_required (VERSION 3.16)
#set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
project(opennurbs CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set( OPENNURBS_PUBLIC_HEADERS
    opennurbs.h
    opennurbs_3dm.h
    opennurbs_3dm_attributes.h
    opennurbs_3dm_properties.h
    opennurbs_3dm_settings.h
    opennurbs_annotationbase.h
    opennurbs_apple_nsfont.h
    opennurbs_arc.h
    opennurbs_arccurve.h
    opennurbs_archivable_dictionary.h
    opennurbs_archive.h
    opennurbs_array.h
    opennurbs_array_defs.h
    opennurbs_base32.h
    opennurbs_base64.h
    opennurbs_beam.h
    opennurbs_bezier.h
    opennurbs_bitmap.h
    opennurbs_bounding_box.h
    opennurbs_box.h
    opennurbs_brep.h
    opennurbs_circle.h
    opennurbs_color.h
    opennurbs_compress.h
    opennurbs_compstat.h
    opennurbs_cone.h
    opennurbs_convex_poly.h
    opennurbs_crc.h
    opennurbs_curve.h
    opennurbs_curveonsurface.h
    opennurbs_curveproxy.h
    opennurbs_cylinder.h
    opennurbs_date.h
    opennurbs_decals.h
    opennurbs_defines.h
    opennurbs_detail.h
    opennurbs_dimension.h
    opennurbs_dimensionformat.h
    opennurbs_dimensionstyle.h
    opennurbs_dithering.h
    opennurbs_ellipse.h
    opennurbs_embedded_file.h
    opennurbs_error.h
    opennurbs_evaluate_nurbs.h
    opennurbs_extensions.h
    opennurbs_file_utilities.h
    opennurbs_font.h
    opennurbs_fpoint.h
    opennurbs_freetype.h
    opennurbs_freetype_include.h
    opennurbs_fsp.h
    opennurbs_fsp_defs.h
    opennurbs_function_list.h
    opennurbs_geometry.h
    opennurbs_gl.h
    opennurbs_ground_plane.h
    opennurbs_group.h
    opennurbs_hash_table.h
    opennurbs_hatch.h
    opennurbs_hsort_template.h
    opennurbs_instance.h
    opennurbs_internal_V2_annotation.h
    opennurbs_internal_V5_annotation.h
    opennurbs_internal_V5_dimstyle.h
    opennurbs_internal_defines.h
    opennurbs_internal_glyph.h
    opennurbs_intersect.h
    opennurbs_ipoint.h
    opennurbs_knot.h
    opennurbs_layer.h
    opennurbs_leader.h
    opennurbs_light.h
    opennurbs_line.h
    opennurbs_linear_workflow.h
    opennurbs_linecurve.h
    opennurbs_linestyle.h
    opennurbs_linetype.h
    opennurbs_locale.h
    opennurbs_lock.h
    opennurbs_lookup.h
    opennurbs_mapchan.h
    opennurbs_material.h
    opennurbs_math.h
    opennurbs_matrix.h
    opennurbs_md5.h
    opennurbs_memory.h
    opennurbs_mesh.h
    opennurbs_mesh_modifiers.h
    opennurbs_model_component.h
    opennurbs_model_geometry.h
    opennurbs_nurbscurve.h
    opennurbs_nurbssurface.h
    opennurbs_object.h
    opennurbs_object_history.h
    opennurbs_objref.h
    opennurbs_offsetsurface.h
    opennurbs_optimize.h
    opennurbs_parse.h
    opennurbs_photogrammetry.h
    opennurbs_plane.h
    opennurbs_planesurface.h
    opennurbs_pluginlist.h
    opennurbs_point.h
    opennurbs_pointcloud.h
    opennurbs_pointgeometry.h
    opennurbs_pointgrid.h
    opennurbs_polycurve.h
    opennurbs_polyedgecurve.h
    opennurbs_polyline.h
    opennurbs_polylinecurve.h
    opennurbs_post_effects.h
    opennurbs_private_wrap.h
    opennurbs_private_wrap_defs.h
    opennurbs_progress_reporter.h
    opennurbs_qsort_template.h
    opennurbs_quacksort_template.h
    opennurbs_quaternion.h
    opennurbs_rand.h
    opennurbs_render_channels.h
    opennurbs_render_content.h
    opennurbs_rendering.h
    opennurbs_revsurface.h
    opennurbs_rtree.h
    opennurbs_safe_frame.h
    opennurbs_sectionstyle.h
    opennurbs_sha1.h
    opennurbs_skylight.h
    opennurbs_sleeplock.h
    opennurbs_sphere.h
    opennurbs_std_string.h
    opennurbs_string.h
    opennurbs_string_value.h
    opennurbs_subd.h
    opennurbs_subd_data.h
    opennurbs_sumsurface.h
    opennurbs_sun.h
    opennurbs_surface.h
    opennurbs_surfaceproxy.h
    opennurbs_symmetry.h
    opennurbs_system.h
    opennurbs_system_compiler.h
    opennurbs_system_runtime.h
    #opennurbs_table.h
    opennurbs_terminator.h
    opennurbs_testclass.h
    opennurbs_text.h
    opennurbs_text_style.h
    opennurbs_textcontext.h
    opennurbs_textdraw.h
    opennurbs_textglyph.h
    opennurbs_textiterator.h
    opennurbs_textlog.h
    opennurbs_textobject.h
    opennurbs_textrun.h
    opennurbs_texture.h
    opennurbs_texture_mapping.h
    opennurbs_topology.h
    opennurbs_torus.h
    opennurbs_unicode.h
    opennurbs_userdata.h
    opennurbs_uuid.h
    opennurbs_version.h
    opennurbs_version_number.h
    opennurbs_viewport.h
    opennurbs_wip.h
    opennurbs_workspace.h
    opennurbs_xform.h
    opennurbs_xml.h
    opennurbs_zlib.h
    )

set( OPENNURBS_PUBLIC_SOURCES
    opennurbs_3dm_attributes.cpp
    opennurbs_3dm_properties.cpp
    opennurbs_3dm_settings.cpp
    opennurbs_annotationbase.cpp
    opennurbs_apple_nsfont.cpp
    opennurbs_arc.cpp
    opennurbs_arccurve.cpp
    opennurbs_archivable_dictionary.cpp
    opennurbs_archive.cpp
    opennurbs_archive_manifest.cpp
    opennurbs_array.cpp
    opennurbs_base32.cpp
    opennurbs_base64.cpp
    opennurbs_beam.cpp
    opennurbs_bezier.cpp
    opennurbs_beziervolume.cpp
    opennurbs_bitmap.cpp
    opennurbs_bounding_box.cpp
    opennurbs_box.cpp
    opennurbs_brep.cpp
    opennurbs_brep_extrude.cpp
    opennurbs_brep_io.cpp
    opennurbs_brep_isvalid.cpp
    opennurbs_brep_region.cpp
    opennurbs_brep_tools.cpp
    opennurbs_brep_v2valid.cpp
    opennurbs_calculator.cpp
    opennurbs_circle.cpp
    opennurbs_color.cpp
    opennurbs_compress.cpp
    opennurbs_compstat.cpp
    opennurbs_cone.cpp
    opennurbs_convex_poly.cpp
    opennurbs_crc.cpp
    opennurbs_curve.cpp
    opennurbs_curveonsurface.cpp
    opennurbs_curveproxy.cpp
    opennurbs_cylinder.cpp
    opennurbs_date.cpp
    opennurbs_decals.cpp
    opennurbs_defines.cpp
    opennurbs_detail.cpp
    opennurbs_dimension.cpp
    opennurbs_dimensionformat.cpp
    opennurbs_dimensionstyle.cpp
    opennurbs_dithering.cpp
    opennurbs_ellipse.cpp
    opennurbs_embedded_file.cpp
    opennurbs_error.cpp
    opennurbs_error_message.cpp
    opennurbs_evaluate_nurbs.cpp
    opennurbs_extensions.cpp
    opennurbs_file_utilities.cpp
    opennurbs_font.cpp
    opennurbs_freetype.cpp
    opennurbs_fsp.cpp
    opennurbs_function_list.cpp
    opennurbs_geometry.cpp
    opennurbs_glyph_outline.cpp
    opennurbs_ground_plane.cpp
    opennurbs_group.cpp
    opennurbs_hash_table.cpp
    opennurbs_hatch.cpp
    opennurbs_instance.cpp
    opennurbs_internal_V2_annotation.cpp
    opennurbs_internal_V5_annotation.cpp
    opennurbs_internal_V5_dimstyle.cpp
    opennurbs_internal_Vx_annotation.cpp
    opennurbs_intersect.cpp
    opennurbs_ipoint.cpp
    opennurbs_knot.cpp
    opennurbs_layer.cpp
    opennurbs_leader.cpp
    opennurbs_light.cpp
    opennurbs_line.cpp
    opennurbs_linear_workflow.cpp
    opennurbs_linecurve.cpp
    opennurbs_linetype.cpp
    opennurbs_locale.cpp
    opennurbs_lock.cpp
    opennurbs_lookup.cpp
    opennurbs_material.cpp
    opennurbs_math.cpp
    opennurbs_matrix.cpp
    opennurbs_md5.cpp
    opennurbs_memory_util.cpp
    opennurbs_mesh.cpp
    opennurbs_mesh_modifiers.cpp
    opennurbs_mesh_ngon.cpp
    opennurbs_mesh_tools.cpp
    opennurbs_mesh_topology.cpp
    opennurbs_model_component.cpp
    opennurbs_model_geometry.cpp
    opennurbs_morph.cpp
    opennurbs_nurbscurve.cpp
    opennurbs_nurbssurface.cpp
    opennurbs_nurbsvolume.cpp
    opennurbs_object.cpp
    opennurbs_object_history.cpp
    opennurbs_objref.cpp
    opennurbs_offsetsurface.cpp
    opennurbs_optimize.cpp
    opennurbs_parse_angle.cpp
    opennurbs_parse_length.cpp
    opennurbs_parse_number.cpp
    opennurbs_parse_point.cpp
    opennurbs_parse_settings.cpp
    opennurbs_photogrammetry.cpp
    opennurbs_plane.cpp
    opennurbs_planesurface.cpp
    opennurbs_pluginlist.cpp
    opennurbs_point.cpp
    opennurbs_pointcloud.cpp
    opennurbs_pointgeometry.cpp
    opennurbs_pointgrid.cpp
    opennurbs_polycurve.cpp
    opennurbs_polyedgecurve.cpp
    opennurbs_polyline.cpp
    opennurbs_polylinecurve.cpp
    opennurbs_post_effects.cpp
    opennurbs_progress_reporter.cpp
    opennurbs_quaternion.cpp
    opennurbs_rand.cpp
    opennurbs_render_channels.cpp
    opennurbs_render_content.cpp
    opennurbs_revsurface.cpp
    opennurbs_rtree.cpp
    opennurbs_safe_frame.cpp
    opennurbs_sectionstyle.cpp
    opennurbs_sha1.cpp
    opennurbs_skylight.cpp
    opennurbs_sleeplock.cpp
    opennurbs_sort.cpp
    opennurbs_sphere.cpp
    opennurbs_statics.cpp
    opennurbs_std_string_format.cpp
    opennurbs_std_string_utf.cpp
    opennurbs_string.cpp
    opennurbs_string_compare.cpp
    opennurbs_string_format.cpp
    opennurbs_string_scan.cpp
    opennurbs_string_values.cpp
    opennurbs_subd.cpp
    opennurbs_subd_archive.cpp
    opennurbs_subd_copy.cpp
    opennurbs_subd_data.cpp
    opennurbs_subd_eval.cpp
    opennurbs_subd_fragment.cpp
    opennurbs_subd_frommesh.cpp
    opennurbs_subd_heap.cpp
    opennurbs_subd_iter.cpp
    opennurbs_subd_limit.cpp
    opennurbs_subd_matrix.cpp
    opennurbs_subd_mesh.cpp
    opennurbs_subd_ref.cpp
    opennurbs_subd_ring.cpp
    opennurbs_subd_sector.cpp
    opennurbs_subd_texture.cpp
    opennurbs_sum.cpp
    opennurbs_sumsurface.cpp
    opennurbs_sun.cpp
    opennurbs_surface.cpp
    opennurbs_surfaceproxy.cpp
    opennurbs_symmetry.cpp
    #opennurbs_table.cpp
    opennurbs_terminator.cpp
    opennurbs_testclass.cpp
    opennurbs_text.cpp
    opennurbs_text_style.cpp
    opennurbs_textcontext.cpp
    opennurbs_textdraw.cpp
    opennurbs_textglyph.cpp
    opennurbs_textiterator.cpp
    opennurbs_textlog.cpp
    opennurbs_textobject.cpp
    opennurbs_textrun.cpp
    opennurbs_topology.cpp
    opennurbs_torus.cpp
    opennurbs_unicode.cpp
    opennurbs_unicode_cpsb.cpp
    opennurbs_units.cpp
    opennurbs_userdata.cpp
    opennurbs_uuid.cpp
    opennurbs_version.cpp
    opennurbs_version_number.cpp
    opennurbs_viewport.cpp
    opennurbs_win_dwrite.cpp
    opennurbs_workspace.cpp
    opennurbs_wstring.cpp
    opennurbs_xform.cpp
    opennurbs_xml.cpp
    opennurbs_zlib.cpp
    opennurbs_zlib_memory.cpp
    )

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/opennurbs_plus.h)
set( OPENNURBS_PLUS_HEADERS
    opennurbsRhino.pch
    opennurbs_plus.h
    opennurbs_plus_crashtest.h
    opennurbs_plus_function.h
    opennurbs_plus_hiddenline.h
    opennurbs_plus_hiddenline_impl.h
    opennurbs_plus_idimage.h
    opennurbs_plus_implicitfn.h
    opennurbs_plus_massprop.h
    opennurbs_plus_mesh_intersection.h
    opennurbs_plus_mesh_marker.h
    opennurbs_plus_meshbooleans_impl.h
    opennurbs_plus_particle.h
    opennurbs_plus_rectpack.h
    opennurbs_plus_rectpack2.h
    opennurbs_plus_registry.h
    opennurbs_plus_sections.h
    opennurbs_plus_sil.h
    opennurbs_plus_sleeplock.h
    opennurbs_plus_squish.h
    opennurbs_plus_subd.h
    opennurbs_plus_trimesh.h
    opennurbs_plus_validate.h
    opennurbs_plus_x.h
    )

if (BUILD_TESTING)
    LIST(APPEND OPENNURBS_PLUS_HEADERS opennurbs_plus_testheader.h)
endif(BUILD_TESTING)

set( OPENNURBS_PLUS_SOURCES
    opennurbs_plus_bezier.cpp
    opennurbs_plus_brep.cpp
    opennurbs_plus_brep_changesrf.cpp
    opennurbs_plus_brep_facegroups.cpp
    opennurbs_plus_brep_kinky.cpp
    opennurbs_plus_ctree.cpp
    opennurbs_plus_fontsub.cpp
    opennurbs_plus_fpu.cpp
    opennurbs_plus_function.cpp
    opennurbs_plus_ginfinity.cpp
    opennurbs_plus_hiddenline.cpp
    opennurbs_plus_idimage.cpp
    opennurbs_plus_implicitfn.cpp
    opennurbs_plus_massprop.cpp
    opennurbs_plus_memory.cpp
    opennurbs_plus_memory_new.cpp
    opennurbs_plus_mesh_clash.cpp
    opennurbs_plus_mesh_intersection.cpp
    opennurbs_plus_mesh_marker.cpp
    opennurbs_plus_mesh_thickness.cpp
    opennurbs_plus_meshbooleans.cpp
    opennurbs_plus_mtree.cpp
    opennurbs_plus_particle.cpp
    opennurbs_plus_rectpack.cpp
    opennurbs_plus_rectpack1.cpp
    opennurbs_plus_rectpack2.cpp
    opennurbs_plus_registry.cpp
    opennurbs_plus_sections.cpp
    opennurbs_plus_sil.cpp
    opennurbs_plus_sleeplock.cpp
    opennurbs_plus_squish.cpp
    opennurbs_plus_stree.cpp
    opennurbs_plus_subd.cpp
    opennurbs_plus_subd_curve.cpp
    opennurbs_plus_subd_eval.cpp
    opennurbs_plus_subd_facegroups.cpp
    opennurbs_plus_subd_fillet.cpp
    opennurbs_plus_subd_limit.cpp
    opennurbs_plus_subd_loft.cpp
    opennurbs_plus_subd_matrix.cpp
    opennurbs_plus_subd_merge.cpp
    opennurbs_plus_subd_mesh.cpp
    opennurbs_plus_subd_symmetry.cpp
    opennurbs_plus_subd_topology.cpp
    opennurbs_plus_subd_weld.cpp
    opennurbs_plus_trimesh.cpp
    opennurbs_plus_validate.cpp
    opennurbs_plus_x.cpp
    opennurbs_plus_xmesh.cpp
    opennurbs_plus_xmeshfast.cpp
    opennurbs_plus_xray.cpp
    )
else()
set( OPENNURBS_PUBLIC_MEMORY
    opennurbs_public_memory.cpp
   )
endif() #OpenNURBS plus source files

if (ANDROID OR LINUX)
  add_subdirectory(android_uuid)
  add_subdirectory(freetype263)
endif()

add_subdirectory(zlib)

## opennurbs static library
add_library( opennurbsStatic STATIC
    ${OPENNURBS_PUBLIC_HEADERS}
    ${OPENNURBS_PUBLIC_SOURCES}
    ${OPENNURBS_PUBLIC_MEMORY}
    ${OPENNURBS_PLUS_HEADERS}
    ${OPENNURBS_PLUS_SOURCES}
    )

## opennurbs shared library
add_library( OpenNURBS SHARED
    ${OPENNURBS_PUBLIC_HEADERS}
    ${OPENNURBS_PUBLIC_SOURCES}
    ${OPENNURBS_PUBLIC_MEMORY}
    ${OPENNURBS_PLUS_HEADERS}
    ${OPENNURBS_PLUS_SOURCES}
    opennurbs_dll.cpp
    )

if (MSVC)
  # opennurbs_brep.cpp requires this flag when compiling with Visual C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
  #add_compile_options(\bigobj)
  add_definitions(-DUNICODE)
  add_definitions(-D_UNICODE)
endif()

add_definitions(-DON_CMAKE_BUILD)

if (ANDROID)
  include_directories("freetype263/include")
endif()

if( APPLE)
   find_library( CORE_GRAPHICS_LIBRARY CoreGraphics)
   message( STATUS "CORE_GRAPHICS_LIBRARY is ${CORE_GRAPHICS_LIBRARY}")
   find_library( CORE_TEXT_LIBRARY CoreText)
   message( STATUS "CORE_TEXT_LIBRARY is ${CORE_TEXT_LIBRARY}")
   find_library( FOUNDATION_LIBRARY Foundation)
   message( STATUS "FOUNDATION_LIBRARY is ${FOUNDATION_LIBRARY}")

   set( OPENNURBS_APPLE_DEPENDENCIES
           ${CORE_GRAPHICS_LIBRARY}
           ${CORE_TEXT_LIBRARY}
           ${FOUNDATION_LIBRARY}
           )

    set( OPENNURBS_APPLE_DEFINES
        ON_COMPILER_CLANG
        ON_RUNTIME_APPLE
        RHINO_APPLE=1
        _GNU_SOURCE
    )
    target_compile_definitions(opennurbsStatic PRIVATE ${OPENNURBS_APPLE_DEFINES})
    target_compile_definitions(OpenNURBS PRIVATE ${OPENNURBS_APPLE_DEFINES})

    # xcode properties are the same for both static and shared libs
    set_target_properties( opennurbsStatic OpenNURBS
        PROPERTIES
        XCODE_ATTRIBUTE_SDKROOT "macosx"
        XCODE_ATTRIBUTE_SUPPORTED_PLATFORMS "macosx iphonesimulator iphoneos"
        XCODE_ATTRIBUTE_SYMROOT "build"
        XCODE_ATTRIBUTE_ALLOW_TARGET_PLATFORM_SPECIALIZATION "YES"
        XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf"
        XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "11.3"
        XCODE_ATTRIBUTE_DYLIB_COMPATIBILITY_VERSION "1"
        XCODE_ATTRIBUTE_DYLIB_CURRENT_VERSION "1"
        XCODE_ATTRIBUTE_INFOPLIST_FILE "opennurbsRhinoInfo.plist"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.mcneel.opennurbs"
        XCODE_ATTRIBUTE_HEADER_SEARCH_PATHS "$(PROJECT_DIR)/freetype263/include"
        XCODE_ATTRIBUTE_CURRENT_PROJECT_VERSION "1"
        XCODE_ATTRIBUTE_MARKETING_VERSION "8 Internal"
        XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN "YES"
        XCODE_ATTRIBUTE_GCC_NO_COMMON_BLOCKS "YES"
        XCODE_ATTRIBUTE_GCC_INPUT_FILETYPE "sourcecode.cpp.objcpp"
        XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
        XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "$(PROJECT_DIR)/opennurbsRhino.pch"
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"
        XCODE_ATTRIBUTE_ENABLE_STRICT_OBJC_MSGSEND "YES"
    )
endif()


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4)
else()
    # These need to be addressed
    add_compile_options(-Wno-inconsistent-missing-override)
    add_compile_options(-Wno-defaulted-function-deleted)
    add_compile_options(-Wno-switch)
    add_compile_options(-Wno-tautological-pointer-compare)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-unsequenced)
    add_compile_options(-Wno-parentheses)
    add_compile_options(-Wno-writable-strings)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch")
endif()


target_compile_definitions(opennurbsStatic PRIVATE ON_COMPILING_OPENNURBS Z_PREFIX MY_ZCALLOC)
target_compile_definitions(OpenNURBS PRIVATE OPENNURBS_EXPORTS Z_PREFIX MY_ZCALLOC)

target_include_directories(opennurbsStatic PUBLIC .)
target_include_directories(OpenNURBS PUBLIC .)

set(PRECOMPILED_HEADERS opennurbs.h)
if (BUILD_TESTING)
    LIST(APPEND PRECOMPILED_HEADERS opennurbs_plus_testheader.h)
endif(BUILD_TESTING)

target_precompile_headers(opennurbsStatic PRIVATE ${PRECOMPILED_HEADERS})
target_precompile_headers(OpenNURBS PRIVATE ${PRECOMPILED_HEADERS})

install( TARGETS opennurbsStatic DESTINATION "lib")
install( FILES ${OPENNURBS_PUBLIC_HEADERS} DESTINATION "include/opennurbsStatic")


if (ANDROID)
target_link_libraries( OpenNURBS zlib opennurbs_public_freetype android_uuid android)
target_link_libraries( opennurbsStatic zlib opennurbs_public_freetype android_uuid android)
endif()
if (LINUX AND NOT ANDROID)
target_link_libraries( OpenNURBS zlib opennurbs_public_freetype android_uuid)
target_link_libraries( opennurbsStatic zlib opennurbs_public_freetype android_uuid)
endif()
if (APPLE)
target_link_libraries( OpenNURBS ${OPENNURBS_APPLE_DEPENDENCIES} zlib)
target_link_libraries( opennurbsStatic ${OPENNURBS_APPLE_DEPENDENCIES} zlib)
endif()
if (WIN32)
target_link_libraries( OpenNURBS Shlwapi Usp10 zlib)
target_link_libraries( opennurbsStatic Shlwapi Usp10 zlib)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(OpenNURBS PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../release)
    set_target_properties(OpenNURBS PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../release)
    set_target_properties(OpenNURBS PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../release)
    set_target_properties(OpenNURBS PROPERTIES OUTPUT_NAME "opennurbs")
    #target_link_libraries(OpenNURBS PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../release)
else()
    set_target_properties(OpenNURBS PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../debug)
    set_target_properties(OpenNURBS PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../debug)
    set_target_properties(OpenNURBS PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../debug)
    set_target_properties(OpenNURBS PROPERTIES OUTPUT_NAME "opennurbs")
    #target_link_libraries(OpenNURBS PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../debug)
endif()

if (APPLE)
   #set_target_properties( OpenNURBS PROPERTIES
#FRAMEWORK TRUE
#FRAMEWORK_VERSION A
# MACOSX_FRAMEWORK_IDENTIFIER "com.mcneel.OpenNURBS"
# VERSION "8.0.0"
# SOVERSION  "8.0.0"
#PUBLIC_HEADER "${OPENNURBS_PUBLIC_HEADERS}"
#)

   #install( TARGETS OpenNURBS DESTINATION "Frameworks")
else()
   install( TARGETS OpenNURBS DESTINATION "lib" )
   install( FILES ${OPENNURBS_PUBLIC_HEADERS} DESTINATION "include/OpenNURBS")
endif()
