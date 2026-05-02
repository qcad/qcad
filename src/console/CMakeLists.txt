include(../../CMakeInclude.txt)
project(qcadcmd)
include(../run/CMakeInclude.txt)

set_target_properties(qcadcmd PROPERTIES
    OUTPUT_NAME "qcadcmd"
    SUFFIX ".com"
)

set_target_properties(qcadcmd PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)


#add_custom_command(TARGET qcadcmd.com POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E rename
#        $<TARGET_FILE:qcadcmd>
#        $<TARGET_FILE_DIR:qcadcmd>/qcadcmd.com
#    COMMENT "Renaming $<TARGET_FILE_NAME:qcadcmd> to qcadcmd.com"
#)
