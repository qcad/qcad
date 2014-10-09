include (../shared.pri)
SUBDIRS = \
    3rdparty \
    core \
    entity \
    grid \
    snap \
    operations \
    stemmer \
    spatialindex \
    gui \
    io

!r_mobile {
    SUBDIRS += \
        customwidgets \
        scripting \
        run
}

TEMPLATE = subdirs
OTHER_FILES += api_overview.dox
