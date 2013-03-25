include($$PWD/shared.pri)

LIBS += \
    -lqcadecma \
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
        -lopennurbs
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
    POST_TARGETDEPS += \
        $$PWD/$$ROUTDIR/qcadgui.lib \
        $$PWD/$$ROUTDIR/qcadentity.lib \
        $$PWD/$$ROUTDIR/qcadoperations.lib \
        $$PWD/$$ROUTDIR/qcadspatialindex.lib \
        $$PWD/$$ROUTDIR/spatialindexnavel.lib \
        $$PWD/$$ROUTDIR/qcadcore.lib \
        $$PWD/$$ROUTDIR/qcadstemmer.lib \
        $$PWD/$$ROUTDIR/stemmer.lib \
        $$PWD/$$ROUTDIR/qcadgrid.lib \
        $$PWD/$$ROUTDIR/qcadsnap.lib \
        $$PWD/$$ROUTDIR/qcadmath.lib \
        $$PWD/$$ROUTDIR/qcadecma.lib \
        $$PWD/$$ROUTDIR/qcadecmaapi.lib
        !r_no_opennurbs {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/opennurbs.dll
        }
        !r_no_dxf {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/qcaddxf.lib
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/dxflib.lib
        }
}
else {
    POST_TARGETDEPS += \
        $$PWD/$$ROUTDIR/libopennurbs.dylib \
        $$PWD/$$ROUTDIR/libqcadcore.dylib \
        $$PWD/$$ROUTDIR/libqcadecma.dylib \
        $$PWD/$$ROUTDIR/libqcadecmaapi.dylib \
        $$PWD/$$ROUTDIR/libqcadentity.dylib \
        $$PWD/$$ROUTDIR/libqcadgrid.dylib \
        $$PWD/$$ROUTDIR/libqcadgui.dylib \
        $$PWD/$$ROUTDIR/libqcadoperations.dylib \
        $$PWD/$$ROUTDIR/libqcadsnap.dylib \
        $$PWD/$$ROUTDIR/libqcadspatialindex.dylib \
        $$PWD/$$ROUTDIR/libqcadstemmer.dylib \
        $$PWD/$$ROUTDIR/libspatialindexnavel.dylib \
        $$PWD/$$ROUTDIR/libstemmer.dylib
        !r_no_opennurbs {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/libopennurbs.dylib
        }
        !r_no_dxf {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/libqcaddxf.dylib
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/libdxflib.dylib
        }
}
