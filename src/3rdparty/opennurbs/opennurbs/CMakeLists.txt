cmake_minimum_required(VERSION 3.16)
project(opennurbs VERSION 1.0 LANGUAGES CXX)

IF(WIN32)
	#SET(RC ../opennurbs.rc)
ENDIF()

add_library(opennurbs SHARED
    ../opennurbs.h
    ../opennurbs_3dm.h
    ../opennurbs_3dm_attributes.cpp ../opennurbs_3dm_attributes.h
    ../opennurbs_3dm_properties.cpp ../opennurbs_3dm_properties.h
    ../opennurbs_3dm_settings.cpp ../opennurbs_3dm_settings.h
    ../opennurbs_annotation.cpp ../opennurbs_annotation.h
    ../opennurbs_annotation2.cpp ../opennurbs_annotation2.h
    ../opennurbs_arc.cpp ../opennurbs_arc.h
    ../opennurbs_arccurve.cpp ../opennurbs_arccurve.h
    ../opennurbs_archive.cpp ../opennurbs_archive.h
    ../opennurbs_array.cpp ../opennurbs_array.h
    ../opennurbs_array_defs.h
    ../opennurbs_base32.cpp ../opennurbs_base32.h
    ../opennurbs_base64.cpp ../opennurbs_base64.h
    ../opennurbs_basic.cpp
    ../opennurbs_beam.cpp ../opennurbs_beam.h
    ../opennurbs_bezier.cpp ../opennurbs_bezier.h
    ../opennurbs_beziervolume.cpp
    ../opennurbs_bitmap.cpp ../opennurbs_bitmap.h
    ../opennurbs_bounding_box.cpp ../opennurbs_bounding_box.h
    ../opennurbs_box.cpp ../opennurbs_box.h
    ../opennurbs_brep.cpp ../opennurbs_brep.h
    ../opennurbs_brep_changesrf.cpp
    ../opennurbs_brep_extrude.cpp
    ../opennurbs_brep_io.cpp
    ../opennurbs_brep_isvalid.cpp
    ../opennurbs_brep_kinky.cpp
    ../opennurbs_brep_region.cpp
    ../opennurbs_brep_tools.cpp
    ../opennurbs_brep_v2valid.cpp
    ../opennurbs_circle.cpp ../opennurbs_circle.h
    ../opennurbs_color.cpp ../opennurbs_color.h
    ../opennurbs_cone.cpp ../opennurbs_cone.h
    ../opennurbs_crashtest.h
    ../opennurbs_crc.cpp ../opennurbs_crc.h
    ../opennurbs_curve.cpp ../opennurbs_curve.h
    ../opennurbs_curveonsurface.cpp ../opennurbs_curveonsurface.h
    ../opennurbs_curveproxy.cpp ../opennurbs_curveproxy.h
    ../opennurbs_cylinder.cpp ../opennurbs_cylinder.h
    ../opennurbs_defines.cpp ../opennurbs_defines.h
    ../opennurbs_detail.cpp ../opennurbs_detail.h
    ../opennurbs_dimstyle.cpp ../opennurbs_dimstyle.h
    ../opennurbs_dll.cpp
    ../opennurbs_dll_resource.h
    ../opennurbs_ellipse.cpp ../opennurbs_ellipse.h
    ../opennurbs_error.cpp ../opennurbs_error.h
    ../opennurbs_error_message.cpp
    ../opennurbs_evaluate_nurbs.cpp ../opennurbs_evaluate_nurbs.h
    ../opennurbs_extensions.cpp ../opennurbs_extensions.h
    ../opennurbs_font.cpp ../opennurbs_font.h
    ../opennurbs_fpoint.h
    ../opennurbs_geometry.cpp ../opennurbs_geometry.h
    ../opennurbs_group.cpp ../opennurbs_group.h
    ../opennurbs_hatch.cpp ../opennurbs_hatch.h
    ../opennurbs_instance.cpp ../opennurbs_instance.h
    ../opennurbs_intersect.cpp ../opennurbs_intersect.h
    ../opennurbs_knot.cpp ../opennurbs_knot.h
    ../opennurbs_layer.cpp ../opennurbs_layer.h
    ../opennurbs_light.cpp ../opennurbs_light.h
    ../opennurbs_line.cpp ../opennurbs_line.h
    ../opennurbs_linecurve.cpp ../opennurbs_linecurve.h
    ../opennurbs_linestyle.h
    ../opennurbs_linetype.cpp ../opennurbs_linetype.h
    ../opennurbs_lookup.cpp ../opennurbs_lookup.h
    ../opennurbs_mapchan.h
    ../opennurbs_massprop.cpp ../opennurbs_massprop.h
    ../opennurbs_material.cpp ../opennurbs_material.h
    ../opennurbs_math.cpp ../opennurbs_math.h
    ../opennurbs_matrix.cpp ../opennurbs_matrix.h
    ../opennurbs_memory.c ../opennurbs_memory.h
    ../opennurbs_memory_new.cpp
    ../opennurbs_memory_util.c
    ../opennurbs_mesh.cpp ../opennurbs_mesh.h
    ../opennurbs_mesh_ngon.cpp
    ../opennurbs_mesh_tools.cpp
    ../opennurbs_morph.cpp
    ../opennurbs_nurbscurve.cpp ../opennurbs_nurbscurve.h
    ../opennurbs_nurbssurface.cpp ../opennurbs_nurbssurface.h
    ../opennurbs_nurbsvolume.cpp
    ../opennurbs_object.cpp ../opennurbs_object.h
    ../opennurbs_object_history.cpp ../opennurbs_object_history.h
    ../opennurbs_objref.cpp ../opennurbs_objref.h
    ../opennurbs_offsetsurface.cpp ../opennurbs_offsetsurface.h
    ../opennurbs_optimize.cpp ../opennurbs_optimize.h
    ../opennurbs_plane.cpp ../opennurbs_plane.h
    ../opennurbs_planesurface.cpp ../opennurbs_planesurface.h
    ../opennurbs_pluginlist.cpp ../opennurbs_pluginlist.h
    ../opennurbs_point.cpp ../opennurbs_point.h
    ../opennurbs_pointcloud.cpp ../opennurbs_pointcloud.h
    ../opennurbs_pointgeometry.cpp ../opennurbs_pointgeometry.h
    ../opennurbs_pointgrid.cpp ../opennurbs_pointgrid.h
    ../opennurbs_polycurve.cpp ../opennurbs_polycurve.h
    ../opennurbs_polyedgecurve.cpp ../opennurbs_polyedgecurve.h
    ../opennurbs_polyline.cpp ../opennurbs_polyline.h
    ../opennurbs_polylinecurve.cpp ../opennurbs_polylinecurve.h
    ../opennurbs_quaternion.cpp ../opennurbs_quaternion.h
    ../opennurbs_rand.cpp ../opennurbs_rand.h
    ../opennurbs_rendering.h
    ../opennurbs_revsurface.cpp ../opennurbs_revsurface.h
    ../opennurbs_rtree.cpp ../opennurbs_rtree.h
    ../opennurbs_sort.cpp
    ../opennurbs_sphere.cpp ../opennurbs_sphere.h
    ../opennurbs_string.cpp ../opennurbs_string.h
    ../opennurbs_sum.cpp
    ../opennurbs_sumsurface.cpp ../opennurbs_sumsurface.h
    ../opennurbs_surface.cpp ../opennurbs_surface.h
    ../opennurbs_surfaceproxy.cpp ../opennurbs_surfaceproxy.h
    ../opennurbs_system.h
    ../opennurbs_textlog.cpp ../opennurbs_textlog.h
    ../opennurbs_texture.h
    ../opennurbs_texture_mapping.h
    ../opennurbs_torus.cpp ../opennurbs_torus.h
    ../opennurbs_userdata.cpp ../opennurbs_userdata.h
    ../opennurbs_uuid.cpp ../opennurbs_uuid.h
    ../opennurbs_version.h
    ../opennurbs_viewport.cpp ../opennurbs_viewport.h
    ../opennurbs_workspace.cpp ../opennurbs_workspace.h
    ../opennurbs_wstring.cpp
    ../opennurbs_x.cpp ../opennurbs_x.h
    ../opennurbs_xform.cpp ../opennurbs_xform.h
    ../opennurbs_zlib.cpp ../opennurbs_zlib.h
    ${RC}
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(opennurbs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../../release)
    set_target_properties(opennurbs PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../../release)
    target_link_libraries(opennurbs PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../../release)
else()
    set_target_properties(opennurbs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../../debug)
    set_target_properties(opennurbs PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../../debug)
    target_link_libraries(opennurbs PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../../debug)
endif()

target_link_libraries(opennurbs PUBLIC
    zlib
)

if(WIN32)
    target_compile_definitions(opennurbs PRIVATE
        NDEBUG
        ON_COMPILING_OPENNURBS
    )

    target_link_libraries(opennurbs PUBLIC
        gdi32
        user32
    )
endif()

if(win32-msvc2010)
    target_compile_definitions(opennurbs PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()
