include (../../../shared.pri)
TEMPLATE = subdirs
SUBDIRS =

contains(QMAKE_COMPILER_DEFINES, _MSC_VER=1929) {
    # MSVC 2019: use newer spatialindexnavel
}
else {
    # other platforms, older MSVC: use legacy spatialindexnavel
    SUBDIRS += spatialindexnavel
}

lessThan(QT_MAJOR_VERSION, 6) {
    # Qt 5: use legacy opennurbs library
    SUBDIRS += opennurbs
}
