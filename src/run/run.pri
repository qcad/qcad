include( ../../shared_app.pri )

macx {
    ICON = $$PWD/qcad.icns
}

win32 {
    !isEmpty(r_iconrc) {
        RC_FILE = $$r_iconrc
    }
    else {
        RC_FILE = $$PWD/qcad.rc
    }
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

macx {
    OBJECTIVE_SOURCES += $$PWD/removemacmenus.mm
    OBJECTIVE_HEADERS += $$PWD/removemacmenus.h
}

TEMPLATE = app
OTHER_FILES += $$PWD/run.dox

win32 {
    TARGET = $${RLIBNAME}
}

macx {
    TARGET = QCAD
} 
else {
    unix {
        TARGET = $${RLIBNAME}-bin
    }
}

# copy Qt plugins to QCAD plugin folder:
!build_pass {
    macx {
        FILES = \
            imageformats/libqgif.dylib \
            imageformats/libqico.dylib \
            imageformats/libqjpeg.dylib \
            imageformats/libqsvg.dylib \
            imageformats/libqtiff.dylib \
            sqldrivers/libqsqlite.dylib \
            sqldrivers/libqsqlodbc.dylib

        greaterThan(QT_MAJOR_VERSION, 4) {
            FILES += imageformats/libqtga.dylib
            FILES += printsupport/libcocoaprintersupport.dylib
        }
        else {
            FILES += \
                codecs/libqcncodecs.dylib \
                codecs/libqjpcodecs.dylib \
                codecs/libqkrcodecs.dylib \
                codecs/libqtwcodecs.dylib
        }

        contains(QT_VERSION, ^4\\.8\\..*) {
            FILES += imageformats/libqtga.dylib
        }

        for(FILE,FILES) {
            !exists("$${DESTDIR}/../plugins/$${FILE}") {
                message("copying file $$[QT_INSTALL_PLUGINS]/$${FILE}")
                system(cp "$$[QT_INSTALL_PLUGINS]/$${FILE}" "$${DESTDIR}/../plugins/$${FILE}")
            }
        }
    }

    else:unix {
        FILES = \
            imageformats/libqgif.so \
            imageformats/libqico.so \
            imageformats/libqjpeg.so \
            imageformats/libqsvg.so \
            imageformats/libqtiff.so \
            sqldrivers/libqsqlite.so

        greaterThan(QT_MAJOR_VERSION, 4) {
            FILES += imageformats/libqtga.so
            FILES += printsupport/libcupsprintersupport.so
        }
        else {
            FILES += \
                codecs/libqcncodecs.so \
                codecs/libqjpcodecs.so \
                codecs/libqkrcodecs.so \
                codecs/libqtwcodecs.so
        }

        contains(QT_VERSION, ^4\\.8\\..*) {
            FILES += imageformats/libqtga.so
        }

        for(FILE,FILES) {
            !exists("$${DESTDIR}/../plugins/$${FILE}") {
                system(cp "$$[QT_INSTALL_PLUGINS]/$${FILE}" "$${DESTDIR}/../plugins/$${FILE}")
            }
        }

        greaterThan(QT_MAJOR_VERSION, 4) {
            system(cp "$$[QT_INSTALL_PLUGINS]/platforms/libqxcb.so" "$${DESTDIR}/../platforms")
            system(cp "$$[QT_INSTALL_PLUGINS]/platforms/libqoffscreen.so" "$${DESTDIR}/../platforms")
            system(cp "$$[QT_INSTALL_PLUGINS]/platforms/libqminimal.so" "$${DESTDIR}/../platforms")
            system(cp "$$[QT_INSTALL_PLUGINS]/platforms/libqlinuxfb.so" "$${DESTDIR}/../platforms")
            system(cp "$$[QT_INSTALL_PLUGINS]/platforminputcontexts/*.so" "$${DESTDIR}/../platforminputcontexts")
            system(cp "$$[QT_INSTALL_PLUGINS]/xcbglintegrations/*.so" "$${DESTDIR}/../xcbglintegrations")
        }
    }

    else:win32 {
        greaterThan(QT_MAJOR_VERSION, 4) {
            FILES += \
                imageformats\\qgif.dll \
                imageformats\\qico.dll \
                imageformats\\qjpeg.dll \
                imageformats\\qsvg.dll \
                imageformats\\qtga.dll \
                imageformats\\qtiff.dll \
                imageformats\\qwbmp.dll \
                sqldrivers\\qsqlite.dll \
                printsupport\\windowsprintersupport.dll
        }

        contains(QT_VERSION, ^4\\..*\\..*) {
            FILES += \
                imageformats\\qgif4.dll \
                imageformats\\qico4.dll \
                imageformats\\qjpeg4.dll \
                imageformats\\qsvg4.dll \
                imageformats\\qtiff4.dll \
                sqldrivers\\qsqlite4.dll \
                codecs\\qcncodecs4.dll \
                codecs\\qjpcodecs4.dll \
                codecs\\qkrcodecs4.dll \
                codecs\\qtwcodecs4.dll
        }

        contains(QT_VERSION, ^4\\.8\\..*) {
            FILES += imageformats\\qtga4.dll
        }

        DESTDIR_WIN = $${DESTDIR}
        DESTDIR_WIN ~= s,/,\\,g
        QT_INSTALL_PLUGINS_WIN = $$[QT_INSTALL_PLUGINS]
        QT_INSTALL_PLUGINS_WIN ~= s,/,\\,g
        QT_INSTALL_BINS_WIN = $$[QT_INSTALL_BINS]
        QT_INSTALL_BINS_WIN ~= s,/,\\,g
        QT_INSTALL_LIBS_WIN = $$[QT_INSTALL_LIBS]
        QT_INSTALL_LIBS_WIN ~= s,/,\\,g

        for(FILE,FILES) {
            !exists("$${QT_INSTALL_PLUGINS_WIN}\\$${FILE}") {
                error("File $${QT_INSTALL_PLUGINS_WIN}\\$${FILE} not found. This Qt plugin is required by QCAD.")
            }
            !exists("$${DESTDIR_WIN}\\..\\plugins\\$${FILE}") {
                message(Copying $${FILE})
                system(copy "$${QT_INSTALL_PLUGINS_WIN}\\$${FILE}" "$${DESTDIR_WIN}\\..\\plugins\\$${FILE}")
            }
        }

        # copy Qt libraries into same dir as exe to avoid Qt version mixup:
        greaterThan(QT_MAJOR_VERSION, 4) {
            system(copy "$${QT_INSTALL_BINS_WIN}\\*.dll" "$${DESTDIR_WIN}")
            system(copy "$${QT_INSTALL_PLUGINS_WIN}\\platforms\\*.dll" "$${DESTDIR_WIN}\\..\\platforms")
        }
        else {
            system(copy "$${QT_INSTALL_LIBS_WIN}\\*.dll" "$${DESTDIR_WIN}")
        }
    }
}

