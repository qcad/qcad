include (../shared.pri)
SUBDIRS = \
    3rdparty \
    core \
    entity \
    customentity \
    grid \
    scripts \
    snap \
    operations \
    stemmer \
    spatialindex \
    gui \
    io

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS += scripting
}

!r_mobile {
    SUBDIRS += \
        customwidgets \
        run
}

win32 {
    SUBDIRS += \
        console
}

TEMPLATE = subdirs
OTHER_FILES += api_overview.dox
