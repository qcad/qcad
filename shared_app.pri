include($$PWD/shared.pri)

LIBS += \
    -lqcadecmaapi \
    #-lqcadcustomwidgets \
    -lqcadgui \
    -lqcadentity \
    -lqcadoperations \
    -lqcadspatialindex \
    -lspatialindexnavel \
    -lqcadgrid \
    -lqcadsnap \
    -lqcadcore \
    -lqcadstemmer \
    -lstemmer

!r_no_opennurbs {
    LIBS += \
        -lopennurbs \
        -lzlib
}

!r_no_dxf {
    LIBS += \
        -lqcaddxf \
        -ldxflib
}

win32 {
    LIBS += \
        -lRpcrt4 \
        "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"
}

linux-g++ {
    LIBS += -lGLU
}

macx {
    QMAKE_LFLAGS += -framework ApplicationServices
    LIBS += \
        -framework CoreServices \
        -liconv \
        -lz
}

win32 {
    PFX=
    EXT=dll
}
macx {
    PFX=lib
    EXT=dylib
}
linux {
    PFX=lib
    EXT=so
}
POST_TARGETDEPS += \
    $$PWD/$$ROUTDIR/$${PFX}qcadgui.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadentity.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadoperations.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadspatialindex.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}spatialindexnavel.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadcore.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadstemmer.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadgrid.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadsnap.$$EXT \
    #$$PWD/$$ROUTDIR/$${PFX}qcadecma.$$EXT \
    $$PWD/$$ROUTDIR/$${PFX}qcadecmaapi.$$EXT

#!r_no_opennurbs {
    #POST_TARGETDEPS += $$PWD/$$ROUTDIR/$${PFX}opennurbs.$$EXT
#}

!r_no_dxf {
    POST_TARGETDEPS += $$PWD/$$ROUTDIR/$${PFX}qcaddxf.$$EXT
    #POST_TARGETDEPS += $$PWD/$$ROUTDIR/$${PFX}dxflib.$$EXT
}

exists($$PWD/../shared_app.pri) {
    include($$PWD/../shared_app.pri)
}
