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

freebsd-g++ {
    LIBS += -lGLU -lexecinfo
}

macx {
    QMAKE_LFLAGS += -framework ApplicationServices
    LIBS += \
        -framework CoreServices \
        -liconv \
        -lz
}
