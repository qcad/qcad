include (../shared.pri)
SUBDIRS = \
    3rdparty \
    core \
    entity \
    grid \
    scripts \
    snap \
    operations \
    stemmer \
    spatialindex \
    gui \
    io

!r_mobile {
    SUBDIRS += \
        customwidgets \
        #scripting \
        run
}

win32 {
    SUBDIRS += \
        console
}

TEMPLATE = subdirs
OTHER_FILES += api_overview.dox
