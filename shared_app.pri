include($$PWD/shared.pri)

LIBS += \
    -lqcadecma \
    -lqcadecmaapi \
    -lqcadcustomwidgets \
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
    POST_TARGETDEPS += \
        $$PWD/$$ROUTDIR/qcadgui.lib \
        $$PWD/$$ROUTDIR/qcadentity.lib \
        $$PWD/$$ROUTDIR/qcadoperations.lib \
        $$PWD/$$ROUTDIR/qcadspatialindex.lib \
        $$PWD/$$ROUTDIR/spatialindexnavel.lib \
        $$PWD/$$ROUTDIR/qcadcore.lib \
        $$PWD/$$ROUTDIR/qcadstemmer.lib \
        $$PWD/$$ROUTDIR/qcadgrid.lib \
        $$PWD/$$ROUTDIR/qcadsnap.lib \
        $$PWD/$$ROUTDIR/qcadecma.lib \
        $$PWD/$$ROUTDIR/qcadecmaapi.lib
        !r_no_opennurbs {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/opennurbs.lib
        }
        !r_no_dxf {
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/qcaddxf.lib
            POST_TARGETDEPS += $$PWD/$$ROUTDIR/dxflib.lib
        }
}
else {
    POST_TARGETDEPS += \
        $$PWD/$$ROUTDIR/libopennurbs.a \
        $$PWD/$$ROUTDIR/libqcadcore.a \
        $$PWD/$$ROUTDIR/libqcadecma.a \
        $$PWD/$$ROUTDIR/libqcadecmaapi.a \
        $$PWD/$$ROUTDIR/libqcadentity.a \
        $$PWD/$$ROUTDIR/libqcadgrid.a \
        $$PWD/$$ROUTDIR/libqcadgui.a \
        $$PWD/$$ROUTDIR/libqcadoperations.a \
        $$PWD/$$ROUTDIR/libqcadsnap.a \
        $$PWD/$$ROUTDIR/libqcadspatialindex.a \
        $$PWD/$$ROUTDIR/libqcadstemmer.a \
        $$PWD/$$ROUTDIR/libstemmer.a

    macx {
        POST_TARGETDEPS += $$PWD/$$ROUTDIR/libspatialindexnavel.dylib
    }
    else {
        POST_TARGETDEPS += $$PWD/$$ROUTDIR/libspatialindexnavel.so
    }

    !r_no_opennurbs {
        POST_TARGETDEPS += $$PWD/$$ROUTDIR/libopennurbs.a
    }
    !r_no_dxf {
        POST_TARGETDEPS += $$PWD/$$ROUTDIR/libqcaddxf.a
        POST_TARGETDEPS += $$PWD/$$ROUTDIR/libdxflib.a
    }
}

exists($$PWD/../shared_app.pri) {
    include($$PWD/../shared_app.pri)
}
