CONFIG      += plugin
TARGET      = scripts
include(../../shared.pri)

TEMPLATE    = lib
HEADERS     = RScriptsPlugin.h
SOURCES     = RScriptsPlugin.cpp
DESTDIR     = ../../plugins
RC_FILE     = scripts.rc
LIBS        += -l$${RLIBNAME}core

CONFIG      += resources_big

CONFIG(debug, debug|release) {
    # include development scripts, tests:
    build_pass:message("Using development qrc")
    RESOURCES   = scripts.qrc
}
else {
    # release:
    rtest {
        build_pass:message("Using development qrc")
        RESOURCES   = scripts.qrc
    }
    else {
        build_pass:message("Using release qrc")
        RESOURCES   = scripts_release.qrc
    }
}
