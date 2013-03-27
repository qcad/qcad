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
    io \
    customwidgets \
    scripting

# external modules that need compilation before linking:
exists(../../src) {
    SUBDIRS += ../../src
}

SUBDIRS += run

TEMPLATE = subdirs
OTHER_FILES += api_overview.dox
