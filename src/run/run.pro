include( ../../shared_app.pri )

macx {
    ICON = qcad.icns
}

win32 {
    RC_FILE = qcad.rc
}

win32 {
    QMAKE_LFLAGS_WINDOWS += /FORCE:MULTIPLE
}

linux-g++ {
    QMAKE_CXXFLAGS += -static-libgcc -static-libstdc++
    QMAKE_LFLAGS += -L.
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

SOURCES += main.cpp
TEMPLATE = app
OTHER_FILES += run.dox

win32 {
    TARGET = qcad
}

macx {
    TARGET = QCAD
} 
else {
    unix {
        TARGET = qcad-bin
    }
}

# copy Qt plugins if not copied already:
macx {
    FILES = \
        designer/libqwebview.dylib \
        imageformats/libqgif.dylib \
        imageformats/libqico.dylib \
        imageformats/libqjpeg.dylib \
        imageformats/libqmng.dylib \
        imageformats/libqsvg.dylib \
        imageformats/libqtga.dylib \
        imageformats/libqtiff.dylib \
        sqldrivers/libqsqlite.dylib \
        sqldrivers/libqsqlodbc.dylib

    for(FILE,FILES) {
        system(cp -n $$[QT_INSTALL_PLUGINS]/$${FILE} $${DESTDIR}/../plugins/$${FILE})
    }
}

# TODO: copy Qt plugins under Linux / Windows:

