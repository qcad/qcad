include( ../../../../shared.pri )
TEMPLATE = subdirs
SUBDIRS = qtscript_core \
          qtscript_gui \
          qtscript_widgets \
          qtscript_printsupport \
          qtscript_network \
          qtscript_opengl \
          qtscript_sql \
          qtscript_uitools \
          qtscript_xml \
          qtscript_xmlpatterns

!r_mobile {
    SUBDIRS += \
          qtscript_webkit \
          qtscript_webkitwidgets
}

#          qs_eval

#          qtscript_multimedia \
#      qtscript_svg \
