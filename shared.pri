contains(QT_VERSION, ^5\\..*\\..*) {
    cache()
    DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000
    QT += printsupport webkitwidgets
    #INCLUDEPATH += ~/local/qt/include/QtWebKitWidgets
    QMAKE_CXXFLAGS += -I/Users/andrew/local/qt/include/QtWebKitWidgets
}

DEFINES += QCAD_DLL

# output directory:
CONFIG(debug, debug|release) {
    ROUTDIR = debug
} else {
    ROUTDIR = release
}

CONFIG(plugin, plugin) {
    build_pass:CONFIG(debug, debug|release) {
        TARGET = $$join(TARGET,,,_debug)

        # Qt uses '_debug' for unix and 'd' for Windows
        # which is not reliably detectable (e.g.: abcd.dll)
        # unix: TARGET = $$join(TARGET,,,_debug)
        # else: TARGET = $$join(TARGET,,,d)
    }
}

r_no_opennurbs {
    DEFINES += R_NO_OPENNURBS
}

win32-msvc2010 {
    CONFIG+=win32-msvc
}

macx {
    rppc {
        # building for Mac OS X on the PowerPC platform:
        CONFIG += ppc
        CONFIG -= x86
        QMAKE_CFLAGS_X86 =
        QMAKE_CXXFLAGS_X86 =
        QMAKE_OBJECTIVE_CFLAGS_X86 =
        QMAKE_LFLAGS_X86 =
    }
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.6
}

win32 {
    RLIBPRE = 
    RLIBPOST = .lib
}
else {
    RLIBPRE = lib
    RLIBPOST = .a
}

QT += core \
    script \
    scripttools \
    sql \
    svg \
    opengl \
    webkit \
    network \
    xml \
    xmlpatterns

# make sure that the QtHelp framework is included in the app bundle under Mac OS X:
contains(QT_VERSION, ^5\\..*\\..*) {
    QT += help \
        designer \
        uitools
}
else {
    CONFIG += help \
        designer \
        uitools
}

# required for the navel spatial index lib:
!win32 {
    DEFINES += PTHREADS
    DEFINES += HAVE_PTHREAD_H
}

CONFIG -= warn_off
CONFIG += warn_on
CONFIG += debug_and_release ordered embed_manifest_dll embed_manifest_exe

win32-msvc2010 {
    DEFINES += _CRT_SECURE_NO_WARNINGS
}

QMAKE_TARGET_COMPANY = QCAD.org
QMAKE_TARGET_DESCRIPTION = QCAD Application Framework
QMAKE_TARGET_COPYRIGHT = 
QMAKE_TARGET_PRODUCT = QCAD Application Framework

DESTDIR = $$PWD/$$ROUTDIR
UI_DIR = .ui

LIBS += -L$$PWD/$$ROUTDIR

CONFIG(debug, debug|release) {
    !win32 {
        QMAKE_LFLAGS += -rdynamic
    }
}

INCLUDEPATH += \
    $$PWD/src/core \
    $$PWD/src/core/math \
    $$PWD/src/grid \
    $$PWD/src/snap \
    $$PWD/src/gui \
    $$PWD/src/entity \
    $$PWD/src/operations \
    $$PWD/src/scripting \
    $$PWD/src/stemmer \
    $$PWD/src/scripting/ecmaapi \
    $$PWD/src/scripting/ecmaapi/generated \
    $$PWD/src/scripting/ecmaapi/adapters \
    $$PWD/src/io/dxf \
    $$PWD/src/spatialindex \
    $$PWD/src/3rdparty

