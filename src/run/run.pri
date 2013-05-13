include( ../../shared_app.pri )

macx {
    ICON = $$PWD/qcad.icns
}

win32 {
    RC_FILE = $$PWD/qcad.rc
}

win32 {
    QMAKE_LFLAGS_WINDOWS += /FORCE:MULTIPLE
}

#linux-g++ {
#    QMAKE_CXXFLAGS += -static-libgcc -static-libstdc++
#    QMAKE_LFLAGS += -L.
#    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
#}

SOURCES += $$PWD/main.cpp
TEMPLATE = app
OTHER_FILES += $$PWD/run.dox

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

# copy Qt plugins to QCAD plugin folder:
!build_pass {
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
            !exists("$${DESTDIR}/../plugins/$${FILE}") {
                system(cp "$$[QT_INSTALL_PLUGINS]/$${FILE}" "$${DESTDIR}/../plugins/$${FILE}")
            }
        }
    }

    win32 {
        FILES = \
            designer\\qwebview.dll \
            imageformats\\qgif4.dll \
            imageformats\\qico4.dll \
            imageformats\\qjpeg4.dll \
            imageformats\\qmng4.dll \
            imageformats\\qsvg4.dll \
            imageformats\\qtga4.dll \
            imageformats\\qtiff4.dll \
            sqldrivers\\qsqlite4.dll

        DESTDIR_WIN = $${DESTDIR}
        DESTDIR_WIN ~= s,/,\\,g

        for(FILE,FILES) {
            !exists("$$[QT_INSTALL_PLUGINS]\\$${FILE}") {
                error("File $$[QT_INSTALL_PLUGINS]\\$${FILE} not found. This Qt plugin is required by QCAD.")
            }
            !exists("$${DESTDIR_WIN}\\..\\plugins\\$${FILE}") {
                message(Copying $${FILE})
                system(copy "$$[QT_INSTALL_PLUGINS]\\$${FILE}" "$${DESTDIR_WIN}\\..\\plugins\\$${FILE}")
            }
        }

        # copy Qt libraries into same dir as exe to avoid Qt version mixup:
        system(copy "$$[QT_INSTALL_LIBS]\\*.dll" "$${DESTDIR_WIN}")
    }
}

