include (../../shared.pri)

SUBDIRS = \
    spatialindexnavel \
    stemmer

!r_no_opennurbs {
    SUBDIRS += \
        zlib \
        opennurbs
}
!rs_no_dxf {
    SUBDIRS += \
        dxflib
}

exists(qt-labs-qtscriptgenerator-$${QT_VERSION}) {
    SUBDIRS += \
        qt-labs-qtscriptgenerator-$${QT_VERSION}
}
else {
    error("Script bindings not available for Qt version $${QT_VERSION}. You can add them to src/scripting/qt-labs-qtscriptgenerator-$${QT_VERSION} or use another version of Qt.")
}

TEMPLATE = subdirs
