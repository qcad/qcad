greaterThan(QT_MAJOR_VERSION, 4) {
    cache()
    DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000
    QT += printsupport
    macx {
        QT += macextras
    }
}
else {
    QT += webkit
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

android-* {
    CONFIG += r_static_libs
    CONFIG += r_mobile
}

macx-ios-* {
    CONFIG += r_static_libs
    CONFIG += r_mobile
}

!r_mobile {
    greaterThan(QT_MAJOR_VERSION, 4) {
        greaterThan(QT_MINOR_VERSION, 5) {
            # Qt >= 5.6
            QT += webenginewidgets
        }
        else {
            QT += webkitwidgets
        }
    }
}

win32-msvc2010 {
    CONFIG+=win32-msvc
}

# building for Mac OS X on the PowerPC platform:
macx {
    rppc {
        CONFIG += ppc
        CONFIG -= x86
        QMAKE_CFLAGS_X86 =
        QMAKE_CXXFLAGS_X86 =
        QMAKE_OBJECTIVE_CFLAGS_X86 =
        QMAKE_LFLAGS_X86 =
    }
}

# settings for all Mac OS X builds:
macx {
    QMAKE_CXXFLAGS_X86 += -Werror=return-type
    macx-clang* {
        QMAKE_CXXFLAGS += -mmacosx-version-min=10.6
        exists(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk) {
            QMAKE_MAC_SDK = macosx10.9
        }
        else:exists(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk) {
            QMAKE_MAC_SDK = macosx10.11
        }
        #exists(/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1) {
        #    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1
        #}
    }

    greaterThan(QT_MAJOR_VERSION, 4) {
        QMAKE_LFLAGS += -F/System/Library/Frameworks
    }
}

win32 {
    RLIBPRE =
    RLIBPOST = .lib
    RLIBPOSTDLL = .dll
}
else {
    RLIBPRE = lib
    RLIBPOST = .a
    macx {
        RLIBPOSTDLL = .dylib
    }
    else {
        RLIBPOSTDLL = .so
    }
}

#defined(r_libname, var) {
!isEmpty(r_libname) {
    message(got prefix $$r_libname)
    RLIBNAME = $$r_libname
}
else {
    message("default prefix")
    RLIBNAME = "qcad"
}

QT += core \
    script \
    scripttools \
    sql \
    svg \
    opengl \
    network \
    xml \
    xmlpatterns

# make sure that the QtHelp framework is included in the app bundle under Mac OS X:
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += help \
        uitools
    !r_mobile {
        QT += designer
    }
}
else {
    CONFIG += help \
        designer \
        uitools
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
    $$PWD/src/3rdparty \
    $$PWD/src/zip
