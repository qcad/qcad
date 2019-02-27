include (../../shared.pri)
TEMPLATE = subdirs
SUBDIRS = \
    spatialindexnavel \
    stemmer

!r_no_opennurbs {
    SUBDIRS += opennurbs
}
!rs_no_dxf {
    SUBDIRS += dxflib
}

!r_mobile {
    exists(qt-labs-qtscriptgenerator-$${QT_VERSION}) {
        SUBDIRS += qt-labs-qtscriptgenerator-$${QT_VERSION}
    }
    else {
        error("Script bindings not available for Qt version $${QT_VERSION}. You can add them to src/3rdparty/qt-labs-qtscriptgenerator-$${QT_VERSION} or use another version of Qt.")
    }
}
