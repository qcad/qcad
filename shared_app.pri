include($$PWD/shared.pri)

LIBS += \
    -lqcadecmaapi \
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

win32 {
    LIBS += \
        -lRpcrt4 \
        "kernel32.lib" \
        "user32.lib" \
        "gdi32.lib" \
        "winspool.lib" \
        "comdlg32.lib" \
        "advapi32.lib" \
        "shell32.lib" \
        "ole32.lib" \
        "oleaut32.lib" \
        "uuid.lib" \
        "odbc32.lib" \
        "odbccp32.lib"
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
    $$PWD/$$ROUTDIR/$${PFX}qcadecmaapi.$$EXT


exists($$PWD/../shared_app.pri) {
    include($$PWD/../shared_app.pri)
}
