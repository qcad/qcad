TEMPLATE = subdirs
SUBDIRS = qtscript_core \
          qtscript_gui \
          qtscript_opengl \
          qtscript_sql \
          qtscript_xml \
          qtscript_svg \
          qtscript_webkit \
          qtscript_xmlpatterns \
          qtscript_uitools

!win32 {
    SUBDIRS += qtscript_network
}

!unix {
    SUBDIRS += qtscript_phonon
}
